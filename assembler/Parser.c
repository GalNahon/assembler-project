
#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include <ctype.h>
#include <string.h>
#include "ParseCommand.h"
#include "ParseData.h"
#include "PrintToFile.h"

#define MAX_LEN 31
RESULT analyze_line(char *line, LinkedList *commandList, LinkedList *dataList, LinkedList *symbolList, LinkedList* externList, LinkedList* entryList, int *IC, int *DC);
int memory_amount_for_command(char *source);
int is_command(char *line);
int is_string_declare(char *line);
int is_data_declare(char *line);
RESULT extract_label(LinkedList *symbolList, Symbol *newSymbol, char *labelToAdd, int indexOfEndLabel, int lineIndex, int address, SymbolType typeOfSymbol);
CommandProperties* extract_command(Symbol *newSymbol, char *line, int *IC);
DataProperties* extract_data(Symbol *newSymbol, char *line, int *DC, typeOfDataDeclaration dataType);
RESULT extract_declaration(LinkedList* externList, LinkedList* entryList, Symbol* newSymbol, char* line);
RESULT fill_entry_list_addresses(LinkedList *entryList, LinkedList *symbolList);
int is_entry_declare(char *line);
void fix_symbol_address(LinkedList *symbolList, int ICF);
int is_extern_declare(char *line);
int is_comment (const char *line, int lineIndex);
int is_reserved_word(char *firstToken);
int is_legal_label (char *line, int indexOfEndLabel, int labelIndex);
int detect_label_ending(char *line , int lineIndex);
void insert_operands(char **pString, int operands, char *line);

void data_properties_free(void* dataProperties);
void command_properties_free(void* commandProperties);


RESULT parse(FILE *fp, char* fileName) {
    int IC;
    int DC;
    int ICF;
    int DCF;
    char line[100];
    FILE * objFile;
    char* objFileName;
    LinkedList *commandsList;
    LinkedList *dataList;
    LinkedList *symbolList;
    LinkedList *externList;
    LinkedList *externListToPrint;
    LinkedList *entryList;
    Node *dataListFinalNode;
    Node *entryListCurrentNode;
    Node *externListCurrentNode;
    Node *commandListFinalNode;

    objFileName = malloc(strlen(fileName) + 4);
    DC = 0;
    IC = 100;
    strcpy(objFileName, fileName);
    strcat(objFileName, ".ob");
    objFile = fopen(objFileName, "w");
    commandsList = create_linked_list();
    dataList = create_linked_list();
    symbolList = create_linked_list();
    externList = create_linked_list();
    externListToPrint = create_linked_list();
    entryList = create_linked_list();
    while (fgets(line, 100, fp) != NULL) {
        RESULT resAnalyzeLine;
        char noLineDropLine[100];
        strcpy(noLineDropLine, line);
        if (strlen(line) >= 2) {
            noLineDropLine[strlen(line)] = '\0';
        }
        resAnalyzeLine = analyze_line(noLineDropLine, commandsList, dataList, symbolList, externList, entryList, &IC, &DC);
        if (resAnalyzeLine != SUCCESS) {
            printf("%s", get_error(resAnalyzeLine));
        }
    }
    /**find and print DCF and ICF **/
    commandListFinalNode = get_last_item(commandsList);
    if(commandListFinalNode != NULL){
        CommandProperties* commandFinalNode;
        commandFinalNode = commandListFinalNode->data;
        ICF = commandFinalNode->endIC;
    } else ICF = 100;

    dataListFinalNode = get_last_item(dataList);
    if(dataListFinalNode!= NULL){
        DataProperties* dataFinalNode;
        dataFinalNode = dataListFinalNode->data;
        DCF = dataFinalNode->endDC;
    } else DCF = 0;
    fix_symbol_address(symbolList, ICF);
    ICF++;
    DCF++;
    fprintf(objFile, "\t%d %d", ICF -100, DCF);
    /** translating and printing commands list translations to file .obj **/
    if(commandListFinalNode != NULL){
        RESULT resParseCommand;
        resParseCommand = parse_command(objFile, commandsList, dataList, symbolList, externList, &IC, &ICF, &DC, externListToPrint);
        if (resParseCommand != SUCCESS)
            printf("%s", get_error(resParseCommand));
    }
    /** translating and printing data list translations to file .obj */
    if(dataListFinalNode != NULL){
        RESULT resParseData;
        resParseData = parse_data(objFile, dataList, symbolList, externList, entryList, ICF);
        if(resParseData != SUCCESS) {
            free(objFileName);
            return resParseData;
        }
    }
    fill_entry_list_addresses(entryList, symbolList);

    entryListCurrentNode = entryList->head;
    if(entryListCurrentNode != NULL){
        FILE * entFile;
        char* entFileName;
        entFileName = malloc(strlen(fileName) + 4);
        strcpy(entFileName, fileName);
        strcat(entFileName, ".ent");

        entFile = fopen(entFileName, "w");
        print_entry_to_entry_file(entFile, entryList);
        fclose(entFile);
        free(entFileName);
    }

    externListCurrentNode = externListToPrint->head;
    if(externListCurrentNode != NULL){
        FILE * extFile;
        char* extFileName;
        extFileName = malloc(strlen(fileName) + 4);
        strcpy(extFileName, fileName);
        strcat(extFileName, ".ext");
        extFile = fopen(extFileName, "w");
        print_extern_to_extern_file(extFile, externListToPrint);
        fclose(extFile);
        free(extFileName);
    }
    destroy_linked_list(commandsList, command_properties_free);
    destroy_linked_list(dataList, data_properties_free);
    destroy_linked_list(symbolList, symbol_free);
    destroy_linked_list(externList, symbol_free);
    destroy_linked_list(externListToPrint, symbol_free);
    destroy_linked_list(entryList, symbol_free);
    free(objFileName);
    return SUCCESS;
}
void fix_symbol_address(LinkedList *symbolList,int ICF) {
    int index;
    Symbol *symbol;
    index = 0;
    while ((symbol = get_item_by_index(symbolList, index)) != NULL) {
        if(symbol->type == DATA_SYMBOL_TYPE){
            int newAddress;
            newAddress = symbol->address + ICF + 1;
            symbol->address  = newAddress;
        }
        index++;
    }
}

RESULT fill_entry_list_addresses(LinkedList *entryList, LinkedList *symbolList) {
    Symbol *entrySymbol;
    int index;
    index = 0;

    while ((entrySymbol = get_item_by_index(entryList, index)) != NULL) {
        Symbol *originalSymbol;
        originalSymbol = get_item(symbolList, entrySymbol->name, symbol_predicate);
        if (originalSymbol == NULL) {
            return ENTRY_DOESNT_REFERENCE_A_DEFINED_SYMBOL;
        }
        entrySymbol->address = originalSymbol->address;
        index++;
    }
    return SUCCESS;
}

void fill_extern_list_address(LinkedList *externListToPrint, int addressToUpdate, const int *index) {
    Symbol *externSymbol;
    if((externSymbol = get_item_by_index(externListToPrint, *index)) != NULL){
        externSymbol->address = addressToUpdate;
    }
}


RESULT analyze_line(char *line,
                    LinkedList *commandList, LinkedList *dataList,
                    LinkedList *symbolList,
                    LinkedList *externList, LinkedList *entryList,
                    int *IC, int *DC) {
    int lineIndex;
    char *label;
    Symbol *newSymbol;
    int indexEndOfLabel;
    LabelFlag labelFlag;
    char *lineCopy;
    CommandProperties *commandProperties;

    lineIndex = skip_white_spaces(line, 0);
    labelFlag = OFF;
    lineCopy = malloc(strlen(line) + 1);

    /** If line is empty return SUCCESS and continue to next line. */
    if (lineIndex == -1) {
        free(lineCopy);
        return SUCCESS;
    }
    if (is_comment(line, lineIndex) == 1) {
        free(lineCopy);
        return SUCCESS;
    }
    newSymbol = NULL;
    /**find if there is a label and extract it **/
    indexEndOfLabel = detect_label_ending(line, lineIndex);
    if (indexEndOfLabel != 0) {
        labelFlag = ON;
        label = strtok(line, " \t:");
        line = line + strlen(label) + 1;
    }
    strcpy(lineCopy, line);
    /**find if it is a command sentence, if it is then extract the command and the operands. **/
    commandProperties = extract_command(newSymbol, lineCopy, IC);
    if (commandProperties != NULL) {
        int ICBeforeExtractingCommand;
        add_item(commandList, commandProperties);
        ICBeforeExtractingCommand = commandProperties->beginIC;
        if(labelFlag == ON){
            RESULT resExtractLabel;
            resExtractLabel = extract_label(symbolList, newSymbol, label, indexEndOfLabel, lineIndex, ICBeforeExtractingCommand, CODE_SYMBOL_TYPE);
            labelFlag = OFF;
            if (resExtractLabel != SUCCESS) {
                free(lineCopy);
                return resExtractLabel;
            }
        }
        free(lineCopy);
        return SUCCESS;
    }
    /**find if it is a declare sentence, if it is then find if the declare is string and extract the declaration. */
    if (is_string_declare(line)) {
        RESULT resStringDeclaration;
        strtok(line, " \t");
        line = strtok(NULL, "\n");
        line[strlen(line)] = '\0';
        resStringDeclaration = is_string_declaration_legal(line);
        if (resStringDeclaration == SUCCESS) {
            DataProperties *dataProperties;
            dataProperties = extract_data(newSymbol, line, DC, STRING);
            if (dataProperties != NULL){
                int DCBeforeExtractingCommand;
                add_item(dataList, dataProperties);
                DCBeforeExtractingCommand = dataProperties->beginDC;
                if(labelFlag == ON) {
                    RESULT resExtractLabel;
                    resExtractLabel = extract_label(symbolList, newSymbol, label, indexEndOfLabel, lineIndex, DCBeforeExtractingCommand,DATA_SYMBOL_TYPE);
                    labelFlag = OFF;
                    if (resExtractLabel != SUCCESS) {
                        free(lineCopy);
                        return resExtractLabel;
                    }
                }
                free(lineCopy);
                return SUCCESS;
            }
        } else {
            free(lineCopy);
            return resStringDeclaration;
        }

    }
    /**find if it is a declare sentence, if it is then find if the declare is string and extract the declaration. **/
    if (is_data_declare(line)) {
        RESULT resDataDeclaration;
        strtok(line, " \t");
        line = strtok(NULL, "\n");
        resDataDeclaration = is_numeric_string_legal(line);
        if (resDataDeclaration == SUCCESS) {
            DataProperties *dataProperties;
            int DCBeforeExtractingCommand;
            dataProperties = extract_data(newSymbol, line, DC, DATA);
            if (dataProperties != NULL){
                add_item(dataList, dataProperties);
                DCBeforeExtractingCommand = dataProperties->beginDC;
                if(labelFlag == ON) {
                    RESULT resExtractLabel;
                    resExtractLabel = extract_label(symbolList, newSymbol, label, indexEndOfLabel, lineIndex, DCBeforeExtractingCommand, DATA_SYMBOL_TYPE);
                    labelFlag = OFF;
                    if (resExtractLabel != SUCCESS) {
                        free(lineCopy);
                        return resExtractLabel;
                    }
                }
                free(lineCopy);
                return SUCCESS;
            }
        } else {
            free(lineCopy);
            return resDataDeclaration;
        }
    } else {
        RESULT resExtractDeclaration;
        resExtractDeclaration = extract_declaration(externList, entryList, newSymbol, line);
        if (resExtractDeclaration != SUCCESS) {
            free(lineCopy);
            return resExtractDeclaration;
        }
    }
    free(lineCopy);
    return SUCCESS;
}

/**The amount of memory to allocate to IC counter.*/
int memory_amount_for_command(char *source) {
    char *command;
    command = strtok(source, " \t");
    if (strncmp(command, "mov", 3) == 0 || strncmp(command, "cmp", 3) == 0 || strncmp(command, "add", 3) == 0 ||
        strncmp(command, "sub", 3) == 0 || strncmp(command, "lea", 3) == 0)
        return 3;
    if (strncmp(command, "clr", 3) == 0 || strncmp(command, "not", 3) == 0 || strncmp(command, "inc", 3) == 0 ||
        strncmp(command, "dec", 3) == 0 || strncmp(command, "jmp", 3) == 0 || strncmp(command, "bne", 3) == 0 ||
        strncmp(command, "jsr", 3) == 0 || strncmp(command, "red", 3) == 0 || strncmp(command, "prn", 3) == 0)
        return 2;
    if (strncmp(command, "rts", 3) == 0 || strncmp(command, "stop", 4) == 0)
        return 1;
    return -1;
}

int is_command(char *source) {
    char* lineCopy = malloc(strlen(source) + 1);
    char *command;
    strcpy(lineCopy, source);
    command = strtok(source, " \t");
    if (strncmp(command, "mov", 3) == 0 || strncmp(command, "cmp", 3) == 0 ||
        strncmp(command, "add", 3) == 0 || strncmp(command, "sub", 3) == 0 || strncmp(command, "lea", 3) == 0 ||
        strncmp(command, "clr", 3) == 0 || strncmp(command, "not", 3) == 0 || strncmp(command, "inc", 3) == 0 ||
        strncmp(command, "dec", 3) == 0 || strncmp(command, "jmp", 3) == 0 || strncmp(command, "bne", 3) == 0 ||
        strncmp(command, "jsr", 3) == 0 || strncmp(command, "red", 3) == 0 || strncmp(command, "prn", 3) == 0 ||
        strncmp(command, "rts", 3) == 0 || strncmp(command, "stop", 4) == 0) {
        free(lineCopy);
        return 1;
    }
    else {
        free(lineCopy);
        return 0;
    }
}

int is_comment(const char *line, int lineIndex) {
    if (line[lineIndex] == ';')
        return 1;
    else return 0;
}


int is_string_declare(char *line) {
    char* lineCopy = malloc(strlen(line) + 1);
    char *firstToken;
    strcpy(lineCopy, line);
    firstToken = strtok(lineCopy, " \t");
    if (strncmp(firstToken, ".string", 7) == 0) {
        free(lineCopy);
        return 1;
    }
    else {
        free(lineCopy);
        return 0;
    }
}

int is_data_declare(char *line) {
    char* lineCopy = malloc(strlen(line) + 1);
    char *firstToken;
    strcpy(lineCopy, line);
    firstToken = strtok(lineCopy, " \t");
    if (strncmp(firstToken, ".data", 5) == 0) {
        free(lineCopy);
        return 1;
    }
    else {
        free(lineCopy);
        return 0;
    }
}

int is_extern_declare(char *line) {
    char* lineCopy = malloc(strlen(line) + 1);
    char *firstToken;
    strcpy(lineCopy, line);
    firstToken = strtok(lineCopy, " \t");
    if (strncmp(firstToken, ".extern", 7) == 0) {
        free(lineCopy);
        return 1;
    }
    else {
        free(lineCopy);
        return 0;
    }
}

int is_entry_declare(char *line) {
    char* lineCopy = malloc(strlen(line) + 1);
    char *firstToken;
    strcpy(lineCopy, line);
    firstToken = strtok(lineCopy, " \t");
    if (strncmp(firstToken, ".entry", 7) == 0) {
        free(lineCopy);
        return 1;
    }
    else {
        free(lineCopy);
        return 0;
    }
}

/**extracts the label into the line properties and returns a pointer to the rest of the instruction.*/
RESULT extract_label(LinkedList *symbolList, Symbol *newSymbol, char *labelToAdd, int indexOfEndLabel, int lineIndex, int address, SymbolType typeOfSymbol) {
    char *label;
    if (is_legal_label(labelToAdd, indexOfEndLabel, lineIndex) == 0)
        return ILLEGAL_LABEL;
    if (is_reserved_word(labelToAdd) == 1)
        return ERROR_TRYING_TO_ADD_RESERVED_WORD;
    label = malloc(strlen(labelToAdd));
    strncpy(label, labelToAdd, strlen(labelToAdd));
    label[strlen(labelToAdd)] = '\0';
    if (get_item(symbolList, label, symbol_predicate)) {
        free(label);
        return ERROR_TRYING_TO_ADD_EXISTING_SYMBOL;
    }
    newSymbol = malloc(sizeof(Symbol));
    newSymbol->name = label;
    newSymbol->address = address;
    newSymbol->type = typeOfSymbol;
    add_item(symbolList, newSymbol);
    return SUCCESS;
}

/**if a label ending is detected return the index of the label ending. else there is no label detected, return 0*/
int detect_label_ending(char *line, int lineIndex) {
    int i;
    i = lineIndex;
    while (i < strlen(line) - 1) {
        if (line[i] == ':')
            return i;
        i++;
    }
    return 0;
}

/**if the label has no white spaces between characters and ':' then its legal return 1. else illegal, return 0.*/
int is_legal_label(char *line, int indexOfEndLabel, int lineIndex) {
    if (line[indexOfEndLabel - 1] != ' ' && line[indexOfEndLabel - 1] != '\t') {
        if (isalpha(line[lineIndex]))
            return 1;
    } else return 0;
    return 0;
}

/**extracts the command, advances IC and returns whether it was a command*/
CommandProperties *extract_command(Symbol *newSymbol, char *line, int *IC) {
    char *lineCopy;
    check_space_before_char(line);
    lineCopy = line;
    if (is_command(lineCopy) == 1) {
        char *commandNoSpaces;
        int memorySize;
        char *command;
        CommandProperties *res;
        commandNoSpaces = strtok(lineCopy, " \t");
        memorySize = memory_amount_for_command(commandNoSpaces);
        res = malloc(sizeof(CommandProperties));
        res->beginIC = *IC;
        if (newSymbol != NULL) {
            newSymbol->type = CODE_SYMBOL_TYPE;
            newSymbol->address = *IC;
        }

        command = malloc(strlen(commandNoSpaces) + 1);
        strcpy(command, commandNoSpaces);
        line = line + strlen(line) + 1;
        res->command = command;
        res->beginIC = *IC;
        res->numOperands = memorySize - 1;
        res->operands = malloc(memorySize);
        insert_operands(res->operands, res->numOperands, line);
        *IC += memorySize;
        res->endIC = *IC - 1;
        return res;
    }
    return NULL;
}

void insert_operands(char **operands, int numOperands, char *line) {
    if (numOperands == 0) {
        return;
    } else if (numOperands == 1) {
        char *temp;
        temp = strtok(line, " \t");
        operands[0] = malloc(sizeof(strlen(temp) + 1));
        strcpy(operands[0], temp);
    } else if (numOperands == 2) {
        char *temp0;
        char *temp2;
        if (check_comma_in_operands(line) != SUCCESS)
            return;
        temp0 = strtok(line, ",");
            operands[0] = malloc(strlen(temp0) + 1);
            strcpy(operands[0], temp0);
        temp2 = strtok(NULL, ",");
        if (temp2 != NULL){
            char *temp2NoWhiteChars = strtok(temp2, "\t\n ");
            operands[1] = malloc(strlen(temp2NoWhiteChars) + 1);
            strcpy(operands[1], temp2NoWhiteChars);
        }
    }
}

/**extracts data or string declarations, advances DC. */
DataProperties *extract_data(Symbol *newSymbol, char *line, int *DC, typeOfDataDeclaration dataType) {
    int newSymbolIsDefined;
    newSymbolIsDefined = 0;
    if (newSymbol != NULL) {
        newSymbolIsDefined = 1;
    }
    if (dataType == STRING) {
        char *string;
        DataProperties *res;
        res = malloc(sizeof(DataProperties));
        res->beginDC = *DC;
        if (newSymbolIsDefined) {
            newSymbol->type = DATA_SYMBOL_TYPE;
            newSymbol->address = *DC;
        }
        res->declare = STRING_DECLARE;
        string = strtok(line, "\n");
        res->charArray = malloc(strlen(string) + 1);
        *DC += (int) strlen(string) - 1;
        strcpy(res->charArray, string);
        res->endDC = *DC - 1;
        return res;
    } else if (dataType == DATA) {
        DataProperties *res;
        char *data;
        int arrayLength;
        char *token;
        int index = 0;
        strtok(line, "");
        res = malloc(sizeof(DataProperties));
        res->beginDC = *DC;
        if (newSymbolIsDefined) {
            newSymbol->type = DATA_SYMBOL_TYPE;
            newSymbol->address = *DC;
        }
        res->declare = DATA_DECLARE;
        data = strtok(line, "");
        res->dataArrayLength = num_of_delimiter(data, ',') + 1;
        arrayLength = res->dataArrayLength;
        res->dataArray = malloc(arrayLength *sizeof (int));
        token = strtok(data, ", \t");
        while (token != NULL) {
            char *endptr;
            res->dataArray[index] = strtol(token, &endptr, 10);
            index++;
            token = strtok(NULL, ", \t");
        }
        *DC += arrayLength;
        res->endDC = *DC - 1;
        return res;
    }
    return NULL;
}
/**extracts entry or external declarations. */
RESULT extract_declaration(LinkedList *externList, LinkedList *entryList, Symbol *newSymbol, char *line) {
    if (is_extern_declare(line)) {
        Symbol *newExternSymbol;
        char *labelToExternName;
        if (newSymbol != NULL) {
            return EXTERN_CANNOT_HAVE_A_LABEL;
        }
        strtok(line, " \t");
        newExternSymbol = malloc(sizeof(Symbol));
        newExternSymbol->address = 0;
        newExternSymbol->type = EXTERNAL_SYMBOL_TYPE;
        labelToExternName = strtok(NULL, " \t\n");
        newExternSymbol->name = malloc(strlen(labelToExternName) + 1);
        strcpy(newExternSymbol->name, labelToExternName);
        add_item(externList, newExternSymbol);
        return SUCCESS;
    } else if (is_entry_declare(line)) {
        char *labelToEntryName;
        Symbol *newEntrySymbol;
        if (newSymbol != NULL) {
            return ENTRY_CANNOT_HAVE_A_LABEL;
        }
        strtok(line, " \t");
        labelToEntryName = strtok(NULL, " \t\n");
        newEntrySymbol = malloc(sizeof(Symbol));
        newEntrySymbol->address = 0;
        newEntrySymbol->type = ENTRY_SYMBOL_TYPE;
        newEntrySymbol->name = malloc(strlen(labelToEntryName) + 1);
        strcpy(newEntrySymbol->name, labelToEntryName);
        add_item(entryList, newEntrySymbol);
        return SUCCESS;
    }
    return ERROR_EXTRACTING_EXTERN_OR_ENTRY_SYMBOLS;
}


/** table of reserved words that can't be used as labels**/
char reserved_words[][MAX_LEN] = {
        "mov", "cmp", "add", "sub", "lea", "clr",
        "not", "inc", "dec", "jmp", "bne", "jsr",
        "red", "prn", "rts", "stop", "data", "string",
        "entry", "extern", "r0", "r1", "r2", "r3",
        "r4", "r5", "r6", "r7", "ascii", ""
};

int is_reserved_word(char *firstToken) {
    int i;
    i = 0;
    while (reserved_words[i][0] != '\0') {
        if (strcmp(firstToken, reserved_words[i]) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

void command_properties_free(void* commandProperties) {
    CommandProperties* c;
    int i;
    c = (CommandProperties*) commandProperties;
    free(c->command);
    for (i = 0; i < c->numOperands; i++) {
        free(c->operands[i]);
    }
    free(c->operands);
}

void data_properties_free(void* dataProperties) {
    DataProperties* d;
    d = (DataProperties*) dataProperties;
    if (d->declare == DATA_DECLARE)
        free(d->dataArray);
    else if (d->declare == STRING_DECLARE)
        free(d->charArray);
}
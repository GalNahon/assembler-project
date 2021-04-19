
#include "PrintToFile.h"
#include <stdio.h>
#include <string.h>

RESULT print_command_to_obj_file (FILE *objFile, char *totalCommandTranslation, char *translateSourceOperand, char *translateTargetOperand,
                                  int numOperands, char *firstOperand_A_R_E, char *secondOperand_A_R_E, int currentAddress, LinkedList *externListToPrint, int *externalOperandsCounter){
    char hexTotalCommandTranslation[4];
    char hexSourceOperandTranslation[4];
    char hexTargetOperandTranslation[4];
    hexTotalCommandTranslation[0] = '\0';
    hexSourceOperandTranslation[0] = '\0';
    hexTargetOperandTranslation[0] = '\0';


    if(numOperands == 0){
        translate_binary_string_to_hex(hexTotalCommandTranslation, totalCommandTranslation);
        fprintf(objFile, "\n0%d %s A", currentAddress, hexTotalCommandTranslation);
    }
    if (numOperands == 1) {
        translate_binary_string_to_hex(hexTotalCommandTranslation, totalCommandTranslation);
        translate_binary_string_to_hex(hexTargetOperandTranslation, translateTargetOperand);
        fprintf(objFile,"\n0%d %s A", currentAddress, hexTotalCommandTranslation);
        currentAddress++;
        fprintf(objFile,"\n0%d %s %s", currentAddress, hexTargetOperandTranslation, secondOperand_A_R_E);
        if(secondOperand_A_R_E[0] == 'E'){
            fill_extern_list_address(externListToPrint, currentAddress, externalOperandsCounter);
            *externalOperandsCounter = *externalOperandsCounter + 1;
        }
    }
    if (numOperands == 2) {
        translate_binary_string_to_hex(hexTotalCommandTranslation, totalCommandTranslation);
        translate_binary_string_to_hex(hexSourceOperandTranslation, translateSourceOperand);
        translate_binary_string_to_hex(hexTargetOperandTranslation, translateTargetOperand);
        fprintf(objFile,"\n0%d %s A", currentAddress, hexTotalCommandTranslation);
        currentAddress++;
        fprintf(objFile,"\n0%d %s %s", currentAddress, hexSourceOperandTranslation, firstOperand_A_R_E);
        if(firstOperand_A_R_E[0] == 'E'){
            fill_extern_list_address(externListToPrint, currentAddress, externalOperandsCounter);
            *externalOperandsCounter = *externalOperandsCounter + 1;
        }
        currentAddress++;
        fprintf(objFile,"\n0%d %s %s", currentAddress, hexTargetOperandTranslation, secondOperand_A_R_E);
        if(secondOperand_A_R_E[0] == 'E'){
            fill_extern_list_address(externListToPrint, currentAddress, externalOperandsCounter);
            *externalOperandsCounter = *externalOperandsCounter + 1;
        }
    }
    memset(hexTotalCommandTranslation, 0, sizeof hexTotalCommandTranslation);
    memset(hexSourceOperandTranslation, 0, sizeof hexSourceOperandTranslation);
    memset(hexTargetOperandTranslation, 0, sizeof hexTargetOperandTranslation);
    return SUCCESS;
}

RESULT print_data_to_obj_file (FILE *objFile, char *hexTranslation, int address){
    fprintf(objFile,"\n0%d %s A", address, hexTranslation);
    return SUCCESS;
}

RESULT print_entry_to_entry_file(FILE *entFile, LinkedList *entryList){
    Node *entryListCurrentNode;
    entryListCurrentNode = entryList->head;
    while (entryListCurrentNode != NULL){
        Symbol *entryListCurrentData;
        char *symbolName;
        int address;
        entryListCurrentData = entryListCurrentNode->data;
        symbolName = entryListCurrentData->name;
        address = entryListCurrentData->address;
        fprintf(entFile,"\n%s 0%d", symbolName, address);
        entryListCurrentNode = entryListCurrentNode->next;
    }
    return SUCCESS;


}
RESULT print_extern_to_extern_file(FILE *extFile, LinkedList *externListToPrint) {
    Node *externListCurrentNode;
    externListCurrentNode = externListToPrint->head;
    while (externListCurrentNode != NULL) {
        Symbol *externListCurrentData;
        char *symbolName;
        int address;
        externListCurrentData = externListCurrentNode->data;
        symbolName = externListCurrentData->name;
        address = externListCurrentData->address;
        fprintf(extFile, "\n%s 0%d", symbolName, address);
        externListCurrentNode = externListCurrentNode->next;
    }
    return SUCCESS;
}



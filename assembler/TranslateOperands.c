

#include "TranslateOperands.h"
#include "ParsAddressingMode.h"
#include "ParsAddressingMode.h"
#include "ParseCommand.h"

#define REGISTER_LENGTH 2
#define OPERAND_LENGTH 12


#define r0_ADDRESS 1
#define r1_ADDRESS 2
#define r2_ADDRESS 4
#define r3_ADDRESS 8
#define r4_ADDRESS 16
#define r5_ADDRESS 32
#define r6_ADDRESS 64
#define r7_ADDRESS 128

RESULT translate_operand(operandOrder operandOrder, int currentAddress, char *operandStr, addressingMode addressingMode, char *translateOperand, LinkedList *symbolList, LinkedList *externList, char *A_R_E, LinkedList *externListToPrint){

    if(addressingMode == IMMEDIATE_MOD){
        char *stringToTranslate;
        int numToTranslate;
        RESULT res;
        stringToTranslate = strtok(operandStr, " \n#");
        numToTranslate = string_to_int(stringToTranslate);
        res = decimal_to_binary_string(translateOperand, numToTranslate, OPERAND_LENGTH);
        if(res != SUCCESS){
            return res;
        }
        return SUCCESS;
    }
    if(addressingMode == DIRECT_MOD){
        int symbolAddress;
        char *operandToAnalyze;
        Symbol *checkIfItemInSymbolList;
        Symbol *checkIfItemInExternList;
        operandToAnalyze = strtok(operandStr, " \t%\n");
        checkIfItemInSymbolList = get_item(symbolList, operandToAnalyze, symbol_predicate);
        checkIfItemInExternList = get_item(externList, operandToAnalyze, symbol_predicate);
        if(checkIfItemInSymbolList!= NULL){
            RESULT res;
            symbolAddress = checkIfItemInSymbolList->address;
            res = decimal_to_binary_string(translateOperand, symbolAddress, OPERAND_LENGTH);
            if(res != SUCCESS){
                return res;
            }
                A_R_E [0]= 'R';
                return SUCCESS;
        }
        else if(checkIfItemInExternList != NULL){
            Symbol* copySymbol;
            RESULT res;
            symbolAddress = checkIfItemInExternList->address;
            /**adding item to extern list to print */
            copySymbol = malloc(sizeof (Symbol));
            memcpy(copySymbol, checkIfItemInExternList, sizeof(Symbol));
            add_item(externListToPrint, copySymbol);
            res = decimal_to_binary_string(translateOperand, symbolAddress, OPERAND_LENGTH);
            if(res != SUCCESS){
                return res;
            }
            A_R_E [0]= 'E';
            return SUCCESS;
        }
            return ERROR_NOT_AN_EXISTING_LABEL;
    }

    if(addressingMode == RELATIVE_MOD){
        int symbolAddress;
        char *operandToAnalyze;
        int distance;
        Symbol *checkIfItemInSymbolList;
        Symbol *checkIfItemInExternList;
        operandToAnalyze = strtok(operandStr, " \t%\n");
        checkIfItemInSymbolList = get_item(symbolList, operandToAnalyze, symbol_predicate);
        checkIfItemInExternList = get_item(externList, operandToAnalyze, symbol_predicate);
        if(checkIfItemInSymbolList!= NULL) {
            RESULT res;
            symbolAddress = checkIfItemInSymbolList->address;
            distance = symbolAddress - (currentAddress +1);
            res = decimal_to_binary_string(translateOperand, distance, OPERAND_LENGTH);
            if (res != SUCCESS) {
                return res;
            }
            A_R_E [0]= 'A';
            return SUCCESS;
        } else if(checkIfItemInExternList != NULL) {
            RESULT res;
            symbolAddress = checkIfItemInExternList->address;
            /**adding item to extern list to print */
            add_item(externListToPrint, checkIfItemInExternList);
            distance = symbolAddress - (currentAddress +1);
            res = decimal_to_binary_string(translateOperand, distance, OPERAND_LENGTH);
            if (res != SUCCESS) {
                return res;
            }
            A_R_E [0]= 'E';
            return SUCCESS;
        }
            return ERROR_NOT_AN_EXISTING_LABEL;
    }

    if (addressingMode == REGISTER_MOD){
        char *operandToAnalyze;
        RESULT res;
        operandToAnalyze = strtok(operandStr, " \n");
        res = translate_register(operandToAnalyze, translateOperand);
        if (res != SUCCESS)
            return res;
        return SUCCESS;
    }
    if(addressingMode == NO_OPERAND_ADDRESS){
        return SUCCESS;
    }
    return SUCCESS;
}
RESULT translate_register(char *operator, char* operatorTranslation) {
    char operatorCopy[REGISTER_LENGTH + 1];
    operatorCopy[0] = '\0';
    strcpy(operatorCopy, operator);
    strtok(operatorCopy, " \t");
    if (strncmp(operatorCopy, "r0", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r0_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;
    }
    if (strncmp(operatorCopy, "r1", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r1_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;

    }
    if (strncmp(operatorCopy, "r2", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r2_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;
    }
    if (strncmp(operatorCopy, "r3", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r3_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;
    }
    if (strncmp(operatorCopy, "r4", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r4_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;
    }
    if (strncmp(operatorCopy, "r5", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r5_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;
    }
    if (strncmp(operatorCopy, "r6", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r6_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;
    }
    if (strncmp(operatorCopy, "r7", 2) == 0) {
        RESULT res;
        res = decimal_to_binary_string(operatorTranslation, r7_ADDRESS, OPERAND_LENGTH);
        if(res != SUCCESS)
            return res;
        return SUCCESS;
    }
    else return ERROR_ILLEGAL_REGISTER;
}
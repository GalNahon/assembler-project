
#include<string.h>
#include <ctype.h>
#include "errors.h"
#include "Utils.h"
#include "stdlib.h"


#define SUB_ARRAY_LENGTH 4
#define HEX_CHAR_LENGTH 2

#define LAST_INDEX_OF_FIRST_SUB_ARRAY 3
#define LAST_INDEX_OF_SECOND_SUB_ARRAY 7
#define LAST_INDEX_OF_THIRD_SUB_ARRAY 11
#define FIRST_INDEX_OF_FIRST_SUB_ARRAY 0
#define FIRST_INDEX_OF_SECOND_SUB_ARRAY 4
#define FIRST_INDEX_OF_THIRD_SUB_ARRAY 8


void init_binary_number(char *binaryNumArray, int length) {
    int i;
    for (i = 0; i < length ; i++)
    {
        binaryNumArray[i] = '0';
    }
    binaryNumArray[length] = '\0';
}
void translate_binary_string_to_hex(char *dest, char *binaryNumberString) {
    int binaryStringIndex;
    int subArrayIndex;
    int binaryStringIndexCopy;

    char firstSubArrayToTranslateToHex[SUB_ARRAY_LENGTH];
    char secondSubArrayToTranslateToHex[SUB_ARRAY_LENGTH];
    char thirdTSubArrayToTranslateToHex[SUB_ARRAY_LENGTH];
    char firstTranslatedBinaryStringToHexChar[HEX_CHAR_LENGTH];
    char secondTranslatedBinaryStringToHexChar[HEX_CHAR_LENGTH];
    char thirdTranslatedBinaryStringToHexChar[HEX_CHAR_LENGTH];

    firstSubArrayToTranslateToHex[0] = '\0';
    secondSubArrayToTranslateToHex[0] = '\0';
    thirdTSubArrayToTranslateToHex[0] = '\0';
    firstTranslatedBinaryStringToHexChar[0] = '\0';
    secondTranslatedBinaryStringToHexChar[0] = '\0';
    thirdTranslatedBinaryStringToHexChar[0] = '\0';
    subArrayIndex = 1;

    for (binaryStringIndex = 0; binaryStringIndex < strlen(binaryNumberString); binaryStringIndex++) {

        if (binaryStringIndex == LAST_INDEX_OF_FIRST_SUB_ARRAY) {
            binaryStringIndexCopy = binaryStringIndex;
            subArrayIndex = 3;
            for (binaryStringIndexCopy = LAST_INDEX_OF_FIRST_SUB_ARRAY; binaryStringIndexCopy >= FIRST_INDEX_OF_FIRST_SUB_ARRAY; binaryStringIndexCopy--) {
                firstSubArrayToTranslateToHex[subArrayIndex] = binaryNumberString[binaryStringIndexCopy];
                subArrayIndex--;
            }
            hex_translation(firstTranslatedBinaryStringToHexChar, firstSubArrayToTranslateToHex);
        }
        if (binaryStringIndex == LAST_INDEX_OF_SECOND_SUB_ARRAY) {
            binaryStringIndexCopy = binaryStringIndex;
            subArrayIndex = 3;
            for (binaryStringIndexCopy = LAST_INDEX_OF_SECOND_SUB_ARRAY; binaryStringIndexCopy >= FIRST_INDEX_OF_SECOND_SUB_ARRAY; binaryStringIndexCopy--) {
                secondSubArrayToTranslateToHex[subArrayIndex] = binaryNumberString[binaryStringIndexCopy];
                subArrayIndex--;
            }
            hex_translation(secondTranslatedBinaryStringToHexChar, secondSubArrayToTranslateToHex);
        }
        if (binaryStringIndex == LAST_INDEX_OF_THIRD_SUB_ARRAY) {
            binaryStringIndexCopy = binaryStringIndex;
            subArrayIndex = 3;
            for (binaryStringIndexCopy = LAST_INDEX_OF_THIRD_SUB_ARRAY; binaryStringIndexCopy >= FIRST_INDEX_OF_THIRD_SUB_ARRAY; binaryStringIndexCopy--) {
                thirdTSubArrayToTranslateToHex[subArrayIndex] = binaryNumberString[binaryStringIndexCopy];
                subArrayIndex--;
            }
            hex_translation(thirdTranslatedBinaryStringToHexChar, thirdTSubArrayToTranslateToHex);
        }
    }
    strcat(dest, firstTranslatedBinaryStringToHexChar);
    strcat(dest, secondTranslatedBinaryStringToHexChar);
    strcat(dest, thirdTranslatedBinaryStringToHexChar);

}

void hex_translation (char *translatedBinaryStringToHexChar, char *translateToHex) {
    translatedBinaryStringToHexChar[1] = '\0';

    if (strncmp(translateToHex, "0000", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '0';
        return;
    }
    if (strncmp(translateToHex, "0001", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '1';
        return;
    }
    if (strncmp(translateToHex, "0010", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '2';
        return;
    }
    if (strncmp(translateToHex, "0011", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '3';
        return;
    }
    if (strncmp(translateToHex, "0100", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '4';
        return;
    }
    if (strncmp(translateToHex, "0101", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '5';
        return;
    }
    if (strncmp(translateToHex, "0110", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '6';
        return;
    }
    if (strncmp(translateToHex, "0111", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '7';
        return;
    }
    if (strncmp(translateToHex, "1000", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '8';
        return;
    }
    if (strncmp(translateToHex, "1001", 4) == 0) {
        translatedBinaryStringToHexChar[0] = '9';
        return;
    }
    if (strncmp(translateToHex, "1010", 4) == 0) {
        translatedBinaryStringToHexChar[0] = 'A';
        return;
    }
    if (strncmp(translateToHex, "1011", 4) == 0) {
        translatedBinaryStringToHexChar[0] = 'B';
        return;
    }
    if (strncmp(translateToHex, "1100", 4) == 0) {
        translatedBinaryStringToHexChar[0] = 'C';
        return;
    }
    if (strncmp(translateToHex, "1101", 4) == 0) {
        translatedBinaryStringToHexChar[0] = 'D';
        return;
    }
    if (strncmp(translateToHex, "1110", 4) == 0) {
        translatedBinaryStringToHexChar[0] = 'E';
        return;
    }
    if (strncmp(translateToHex, "1111", 4) == 0) {
        translatedBinaryStringToHexChar[0] = 'F';
        return;
    }
}


RESULT decimal_to_binary_string(char *dest, int decimalNum, int length)
{
    int negativeNumberFlag;
    int flipNegativeSignToPositive;
    int j;
    int i;
    j = 0;
    i = 1;
    /**initialize binary array with 0.**/
    init_binary_number(dest, length);
    negativeNumberFlag = 0;
    flipNegativeSignToPositive = 0;
    /**counter for binary array**/
    if(decimalNum < 0){
        decimalNum += 1;
        flipNegativeSignToPositive = decimalNum * (-2);
        decimalNum += flipNegativeSignToPositive;
        negativeNumberFlag = 1;
    }
    do {
        if (i > length) {
            return FAILURE_NUMBER_TOO_BIG;
        }

        if (decimalNum % 2 == 1) {
            dest[length - i] = '1';
        } else {
            dest[length - i] = '0';
        }
        decimalNum = decimalNum / 2;
        i++;
    } while (decimalNum > 0);
    /**if negative number then we need to flip all bits*/
    if(negativeNumberFlag == 1){
        while (j < length){
            if (dest[j] == '0'){
                dest[j] = '1';
                j++;
            }
            if (dest[j] == '1'){
                dest[j] = '0';
                j++;
            }
        }
    }
    return SUCCESS;
}

int string_to_int (char *str){
    char *ptr;
    int result;
    result = strtol(str, &ptr, 10);
    return result;
}

int num_of_delimiter(char* string, char delimiter) {
    int counter;
    char* curr;
    int i;

    curr = string;
    counter = 0;
    i = 0;
    while(i < strlen(string)) {
        if (*curr == delimiter) {
            counter++;
        }
        curr ++;
        i++;
    }
    return counter;
}
int isDigit(char s) {
    if(s >= '0' && s <= '9') {
        return 1;
    }
    return 0;
}
RESULT is_numeric_string_legal(char *string) {
    int allowSign;
    int allowComma;
    int allowSpace;
    int index;
    char* stringCopy = malloc(strlen(string));

    allowSign = 1;
    allowComma = 0;
    allowSpace = 1;
    index = 0;
    strcpy(stringCopy, string);
    while(index < strlen(string)){
        if((stringCopy[index] == ' ' || stringCopy[index] == '\t') && allowSpace == 1){
            index ++;
        }
        else if (isDigit(stringCopy[index])) {
            allowComma = 1;
            allowSign = 0;
            allowSpace = 1;
            index ++;
        }
        else if((stringCopy[index] == '+' || stringCopy[index] == '-') && allowSign == 1){
            allowSign = 0;
            allowComma = 0;
            allowSpace = 0;
            index ++;
        }
        else if (stringCopy[index] == ',' && allowComma == 1) {
            allowSign = 1;
            allowComma = 0;
            allowSpace = 1;
            index ++;
            }
        else {
            free(stringCopy);
            return ILLEGAL_NUMERIC_STRING;
        }
    }
    free(stringCopy);
    return SUCCESS;
}

RESULT is_string_declaration_legal(char * string) {
    int index;
    char* stringCopy = malloc(strlen(string));
    index = 1;
    strcpy(stringCopy, string);
    if (stringCopy[0] != '"' || stringCopy[strlen(string)-1] != '"') {
        free(stringCopy);
        return ERROR_ILLEGAL_STRING_DECLARATION;
    }
    while (index < strlen(stringCopy) - 2){
        int asciiTranslation = (int)stringCopy[index];
        if(asciiTranslation >= 32 && asciiTranslation <= 126)
            index++;
        else {
            free(stringCopy);
            return ERROR_ILLEGAL_STRING_DECLARATION;
        }
    }
    free(stringCopy);
    return SUCCESS;

}


int skip_white_spaces(char *str, int index){
    while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n'){
        if(index == strlen(str) -1 ){
            return -1;
        }
        index ++;
    }
    return index;
}

RESULT check_space_before_char(char* str){
    int i;
    i = 0;
    if(str[i] == ' ' || (str[i] == '\t' && i < strlen(str) -1))
        return SUCCESS;
    return NO_SPACE_OR_TAB_BEFORE_COMMAND;
}

RESULT check_comma_in_operands(char* str){
    int i;
    int numberOfCommas;
    i = 0;
    numberOfCommas = 0;
    while(str[i] == ' ' || str[i] == '\t')
        i++;
    /**check if the first char or last are ",":**/
    if(str[i] ==',' || str[strlen(str)-1] == ','){
        return ILLEGAL_COMMA_IN_BEGINNING_OR_END_OF_SENTENCE;
    }

    for(i=0; i < strlen(str)-1;i++)
    {
        if(numberOfCommas > 1){
            return ILLEGAL_NUMBER_OF_COMMAS_BETWEEN_NUMBERS;
        }
        if(str[i] == ',' )
            numberOfCommas ++;
    }
    return SUCCESS;
}

const char* get_error (RESULT result)
{
    switch (result)
    {
        case FAILURE_NUMBER_TOO_BIG: return "\nFAILURE_NUMBER_TOO_BIG \n";
        case FAILURE_MISSING_OPERAND: return "\nFAILURE_MISSING_OPERAND \n";
        case FAILURE_NOT_A_LEGAL_NUMBER: return "\nFAILURE_NOT_A_LEGAL_NUMBER \n";
        case FAILURE_NOT_A_LEGAL_STRING: return "\nFAILURE_NOT_A_LEGAL_STRING \n";
        case ILLEGAL_ADDRESSING_MODE: return "\nILLEGAL_ADDRESSING_MODE \n";
        case ILLEGAL_COMMA_IN_BEGINNING_OR_END_OF_SENTENCE: return "\nILLEGAL_COMMA_IN_BEGINNING_OR_END_OF_SENTENCE \n";
        case ILLEGAL_NUMBER_OF_COMMAS_BETWEEN_NUMBERS: return "\nILLEGAL_NUMBER_OF_COMMAS_BETWEEN_NUMBERS \n";
        case ILLEGAL_OPERAND_TO_ADDRESSING_MODE: return "\nILLEGAL_OPERAND_TO_ADDRESSING_MODE \n";
        case ERROR_NOT_AN_EXISTING_LABEL: return "\nERROR_NOT_AN_EXISTING_LABEL \n";
        case ERROR_TRYING_TO_ADD_EXISTING_SYMBOL: return "\nERROR_TRYING_TO_ADD_EXISTING_SYMBOL \n";
        case ERROR_TRYING_TO_ADD_RESERVED_WORD: return "\nERROR_TRYING_TO_ADD_RESERVED_WORD \n";
        case ENTRY_DOESNT_REFERENCE_A_DEFINED_SYMBOL: return "\nENTRY_DOESNT_REFERENCE_A_DEFINED_SYMBOL \n";
        case EXTERN_CANNOT_HAVE_A_LABEL: return "\nEXTERN_CANNOT_HAVE_A_LABEL \n";
        case ENTRY_CANNOT_HAVE_A_LABEL: return "\nENTRY_CANNOT_HAVE_A_LABEL \n";
        case ILLEGAL_LABEL: return "\nILLEGAL_LABEL \n";
        case ERROR_ILLEGAL_STRING_DECLARATION: return "\nERROR_ILLEGAL_STRING_DECLARATION \n";
        case ERROR_IN_COMMAND_TRANSLATION: return "\nERROR_IN_COMMAND_TRANSLATION \n";
        case ERROR_ILLEGAL_DATA_DECLARATION: return "\nERROR_ILLEGAL_DATA_DECLARATION \n";
        case NO_SPACE_OR_TAB_BEFORE_COMMAND: return "\nNO_SPACE_OR_TAB_BEFORE_COMMAND \n";
        case ERROR_ILLEGAL_REGISTER: return "\nERROR_ILLEGAL_REGISTER \n";
        case ERROR_EXTRACTING_EXTERN_OR_ENTRY_SYMBOLS: return "\nERROR_EXTRACTING_EXTERN_OR_ENTRY_SYMBOLS \n";
        case SUCCESS: return "\nSUCCESS \n";
        case ILLEGAL_NUMERIC_STRING: return "\nILLEGAL_NUMERIC_STRING \n";
        case EXTERN_DOESNT_REFERENCE_A_DEFINED_SYMBOL:return "\nEXTERN_DOESNT_REFERENCE_A_DEFINED_SYMBOL \n";
        default: return "UNKNOWN_ERROR";
    }
    return "UNKNOWN_ERROR";
}







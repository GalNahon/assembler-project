
#include "ParsAddressingMode.h"
#include "Utils.h"


#define ADDRESSING_MODE_OPERAND_LENGTH 2
#define LINE_MAX_LENGTH 81

#define SOURCE_OPERAND 0
#define TARGET_OPERAND 1


#define r0_ADDRESS 1
#define r1_ADDRESS 2
#define r2_ADDRESS 4
#define r3_ADDRESS 8
#define r4_ADDRESS 16
#define r5_ADDRESS 32
#define r6_ADDRESS 64
#define r7_ADDRESS 128


RESULT parse_addressing_mode(addressingMode *addressingMode, char *translateSourceOperand, char *translateTargetOperand,
                             char *operand, int operandOrder, COMMAND command,
                             LinkedList *commandList, LinkedList *dataList, LinkedList *symbolList,
                             LinkedList *externList) {
    char sourceCopy[LINE_MAX_LENGTH];
    char *operandCopy = malloc(strlen(operand) + 1);
    char *operandWithoutWhiteSpaces;
    if (operand == NULL) {
        printf("FAILURE_MISSING_OPERAND");
        return FAILURE_MISSING_OPERAND;
    }

    strcpy(operandCopy, operand);
    operandWithoutWhiteSpaces = strtok(operandCopy, " \t\n");
    strcpy(sourceCopy, operandWithoutWhiteSpaces);

    if (strncmp(operandWithoutWhiteSpaces, "NO_OPERAND", 10) == 0) {
        *addressingMode = NO_OPERAND_ADDRESS;
        if (operandOrder == SOURCE_OPERAND) {
            RESULT resSourceOperand;
            RESULT resDecimalToBinary;
            resSourceOperand = is_source_operand_legal(command, NO_OPERAND_ADDRESS, 0);
            if (resSourceOperand != SUCCESS) {
                free(operandCopy);
                return resSourceOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateSourceOperand, 0,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        } else {
            RESULT resTargetOperand;
            RESULT resDecimalToBinary;
            resTargetOperand = is_target_operand_legal(command, NO_OPERAND_ADDRESS, 0);
            if (resTargetOperand != SUCCESS) {
                free(operandCopy);
                return resTargetOperand;
            }

            resDecimalToBinary = decimal_to_binary_string(translateTargetOperand, 0,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        }
    }

    if (strncmp(operandWithoutWhiteSpaces, "#", 1) == 0) {
        char *operandToAnalyze;
        *addressingMode = IMMEDIATE_MOD;
        operandToAnalyze = strtok(sourceCopy, " \t#\n");
        if (operandOrder == SOURCE_OPERAND) {
            RESULT resSourceOperand;
            RESULT resDecimalToBinary;
            resSourceOperand = is_source_operand_legal(command, IMMEDIATE_MOD, operandToAnalyze);
            if (resSourceOperand != SUCCESS) {
                free(operandCopy);
                return resSourceOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateSourceOperand, IMMEDIATE_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        } else {
            RESULT resTargetOperand;
            RESULT resDecimalToBinary;
            resTargetOperand = is_target_operand_legal(command, IMMEDIATE_MOD, operandToAnalyze);
            if (resTargetOperand != SUCCESS) {
                free(operandCopy);
                return resTargetOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateTargetOperand, IMMEDIATE_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        }
    }

    if (strncmp(operandWithoutWhiteSpaces, "%", 1) == 0) {
        char *operandToAnalyze;
        *addressingMode = RELATIVE_MOD;
        operandToAnalyze = strtok(sourceCopy, " \t%\n");
        if (operandOrder == SOURCE_OPERAND) {
            RESULT resSourceOperand;
            RESULT resDecimalToBinary;
            resSourceOperand = is_source_operand_legal(command, RELATIVE_MOD, operandToAnalyze);
            if (resSourceOperand != SUCCESS) {
                free(operandCopy);
                return resSourceOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateSourceOperand, RELATIVE_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            if (resDecimalToBinary != SUCCESS) {
                free(operandCopy);
                return resDecimalToBinary;
            }
        } else {
            RESULT resTargetOperand;
            RESULT resDecimalToBinary;
            resTargetOperand = is_target_operand_legal(command, RELATIVE_MOD, operandToAnalyze);
            if (resTargetOperand != SUCCESS) {
                free(operandCopy);
                return resTargetOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateTargetOperand, RELATIVE_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        }
    }

    if (is_register_addressing_mod(operandWithoutWhiteSpaces) == 1) {
        *addressingMode = REGISTER_MOD;
        if (operandOrder == SOURCE_OPERAND) {
            RESULT resSourceOperand;
            RESULT resDecimalToBinary;
            resSourceOperand = is_source_operand_legal(command, REGISTER_MOD, 0);
            if (resSourceOperand != SUCCESS) {
                free(operandCopy);
                return resSourceOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateSourceOperand, REGISTER_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        } else {
            RESULT resTargetOperand;
            RESULT resDecimalToBinary;
            resTargetOperand = is_target_operand_legal(command, REGISTER_MOD, 0);
            if (resTargetOperand != SUCCESS) {
                free(operandCopy);
                return resTargetOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateTargetOperand, REGISTER_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        }
    }

        /**if not any of the addressing mode above then check if direct:**/
    else {
        char *operandToAnalyze;
        operandToAnalyze = strtok(sourceCopy, " \t\n");
        *addressingMode = DIRECT_MOD;
        if (operandOrder == SOURCE_OPERAND) {
            RESULT resSourceOperand;
            RESULT resDecimalToBinary;
            resSourceOperand = is_source_operand_legal(command, DIRECT_MOD, operandToAnalyze);
            if (resSourceOperand != SUCCESS) {
                free(operandCopy);
                return resSourceOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateSourceOperand, DIRECT_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            if (resDecimalToBinary != SUCCESS) {
                free(operandCopy);
                return resDecimalToBinary;
            }
        } else {
            RESULT resTargetOperand;
            RESULT resDecimalToBinary;
            resTargetOperand = is_target_operand_legal(command, DIRECT_MOD, operandToAnalyze);
            if (resTargetOperand != SUCCESS) {
                free(operandCopy);
                return resTargetOperand;
            }
            resDecimalToBinary = decimal_to_binary_string(translateTargetOperand, DIRECT_MOD,
                                                          ADDRESSING_MODE_OPERAND_LENGTH);
            free(operandCopy);
            return resDecimalToBinary;
        }
    }
    free(operandCopy);
    return SUCCESS;
}

RESULT is_source_operand_legal(COMMAND command, int addressingMode, char *operandToAnalyze) {
    if (addressingMode == NO_OPERAND_ADDRESS) {
        if (command == mov || command == cmp || command == add || command == sub || command == lea)
            return ILLEGAL_ADDRESSING_MODE;
        else return SUCCESS;
    }

    if (addressingMode == IMMEDIATE_MOD) {
        RESULT isLegalOperandToAddressingMode;
        if (!(command == mov || command == cmp || command == add || command == sub))
            return ILLEGAL_ADDRESSING_MODE;
        isLegalOperandToAddressingMode = is_legal_numeric_operand(operandToAnalyze);
        if (isLegalOperandToAddressingMode != SUCCESS)
            return ILLEGAL_OPERAND_TO_ADDRESSING_MODE;
        else return SUCCESS;
    }

    if (addressingMode == DIRECT_MOD) {
        RESULT isLegalOperandToAddressingMode;
        if (!(command == mov || command == cmp || command == add || command == sub || command == lea))
            return ILLEGAL_ADDRESSING_MODE;
        isLegalOperandToAddressingMode = is_alpha_operand(command, addressingMode, operandToAnalyze);
        if (isLegalOperandToAddressingMode != SUCCESS)
            return ILLEGAL_OPERAND_TO_ADDRESSING_MODE;
        else return SUCCESS;

    }

    if (addressingMode == RELATIVE_MOD) {
        return ILLEGAL_ADDRESSING_MODE;
    }

    if (addressingMode == REGISTER_MOD) {
        if (!(command == mov || command == cmp || command == add || command == sub))
            return ILLEGAL_ADDRESSING_MODE;
        else return SUCCESS;
    }
    return SUCCESS;
}


RESULT is_target_operand_legal(COMMAND func, int addressingMode, char *operandToAnalyze) {
    if (addressingMode == NO_OPERAND_ADDRESS) {
        if (!(func == rts || func == stop))
            return ILLEGAL_ADDRESSING_MODE;
        else return SUCCESS;
    }

    if (addressingMode == IMMEDIATE_MOD) {
        RESULT isLegalOperandToAddressingMode;
        if (!(func == cmp || func == prn || func == rts || func == stop))
            return ILLEGAL_ADDRESSING_MODE;
        isLegalOperandToAddressingMode = is_legal_numeric_operand(operandToAnalyze);
        if (isLegalOperandToAddressingMode != SUCCESS)
            return ILLEGAL_OPERAND_TO_ADDRESSING_MODE;
        else return SUCCESS;
    }

    if (addressingMode == DIRECT_MOD) {
        RESULT isLegalOperandToAddressingMode;
        if (func == rts || func == stop)
            return ILLEGAL_ADDRESSING_MODE;
        isLegalOperandToAddressingMode = is_alpha_operand(func, addressingMode, operandToAnalyze);
        if (isLegalOperandToAddressingMode != SUCCESS)
            return ILLEGAL_OPERAND_TO_ADDRESSING_MODE;
        else return SUCCESS;
    }

    if (addressingMode == RELATIVE_MOD) {
        RESULT isLegalOperandToAddressingMode;
        if (!(func == jmp || func == bne || func == jsr))
            return ILLEGAL_ADDRESSING_MODE;
        isLegalOperandToAddressingMode = is_alpha_operand(func, addressingMode, operandToAnalyze);
        if (isLegalOperandToAddressingMode != SUCCESS)
            return ILLEGAL_OPERAND_TO_ADDRESSING_MODE;
        else return SUCCESS;
    }

    if (addressingMode == REGISTER_MOD) {
        if ((func == jmp || func == bne || func == jsr || func == rts || func == stop))
            return ILLEGAL_ADDRESSING_MODE;
        else return SUCCESS;
    }
    return SUCCESS;
}


int is_register_addressing_mod(char *addressingMode) {
    if (strncmp(addressingMode, "r0", 2) == 0 || strncmp(addressingMode, "r1", 2) == 0 ||
        strncmp(addressingMode, "r2", 2) == 0 || strncmp(addressingMode, "r3", 2) == 0 ||
        strncmp(addressingMode, "r4", 2) == 0 || strncmp(addressingMode, "r5", 2) == 0 ||
        strncmp(addressingMode, "r6", 2) == 0 || strncmp(addressingMode, "r7", 2) == 0) {
        return 1;
    } else return 0;
}


RESULT is_alpha_operand(COMMAND func, int addressingMode, char *operandToAnalyze) {
    int i;
    for (i = 0; operandToAnalyze[i]; i++) {

        if (!isalpha(operandToAnalyze[i])) {
            if (!isDigit(operandToAnalyze[i]))
                return FAILURE_NOT_A_LEGAL_STRING;
        }
    }
    return SUCCESS;
}

RESULT is_legal_numeric_operand(char *string) {
    int allowSign;
    char *token;
    int i;
    int length;
    allowSign = 1;
    i = 0;
    token = strtok(string, " \t");
    length = strlen(token);
    while (i < length) {
        if (isDigit(*token)) {
            token++;
            i++;
            allowSign = 0;
        } else if (allowSign == 1 && (*token == '+' || *token == '-')) {
            token++;
            i++;
            allowSign = 0;
        } else {
            return FAILURE_NOT_A_LEGAL_NUMBER;
        }
    }
    return SUCCESS;
}




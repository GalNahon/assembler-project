

#ifndef MMN_14_PARSADDRESSINGMODE_H
#define MMN_14_PARSADDRESSINGMODE_H
#include "errors.h"
#include "Utils.h"
#include "TranslateCommand.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum e_addressingMode{
IMMEDIATE_MOD = 0,
DIRECT_MOD = 1,
RELATIVE_MOD = 2,
REGISTER_MOD = 3,
NO_OPERAND_ADDRESS = 4
}addressingMode;




int is_register_addressing_mod(char *addressingMode);
RESULT parse_addressing_mode(addressingMode *addressingMode, char *translateSourceOperand,char *translateTargetOperand, char *operand, int operandOrder,COMMAND command,
                             LinkedList *commandList, LinkedList *dataList, LinkedList *symbolList, LinkedList *externList);
RESULT is_source_operand_legal(COMMAND func, int addressingMode, char* operandToAnalyze);
RESULT is_target_operand_legal(COMMAND func, int addressingMode, char* operandToAnalyze);
RESULT is_alpha_operand (COMMAND func, int addressingMode, char* operandToAnalyze);
RESULT is_legal_numeric_operand(char* string);





#endif

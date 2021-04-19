

#ifndef MMN_14_TRANSLATEOPERANDS_H
#define MMN_14_TRANSLATEOPERANDS_H

#include "errors.h"
#include "LinkedList.h"
#include "Symbol.h"
#include "ParsAddressingMode.h"
#include "ParseCommand.h"

typedef enum e_operandOrder{
    FIRST_OPERAND,
    SECOND_OPERAND
}operandOrder;

RESULT translate_register(char *operator, char* operatorTranslation);
RESULT translate_operand(operandOrder operandOrder, int currentAddress, char *operandStr, addressingMode addressingMode, char *translateOperand, LinkedList *symbolList, LinkedList *externList, char *A_R_E, LinkedList *externListToPrint);
#endif

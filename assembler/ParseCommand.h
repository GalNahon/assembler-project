

#ifndef MMN_14_PARSECOMMAND_H
#define MMN_14_PARSECOMMAND_H
#include "ParseCommand.h"
#include "TranslateCommand.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"
#include "errors.h"
#include "ParsAddressingMode.h"

RESULT parse_command (FILE *objFile, LinkedList *commandList, LinkedList *dataList, LinkedList *symbolList, LinkedList *externList, int *IC, int *ICF, int *DC, LinkedList *externListToPrint);

RESULT handleNoOperands(char *sourceAndTargetOperandsTranslation, int currentAddress, COMMAND command, int numOperands, char **operand, LinkedList *commandList, LinkedList *dataList,
                        LinkedList *symbolList, LinkedList *externList, LinkedList *externListToPrint);

RESULT handleOneOperands(char *sourceAndTargetOperandsTranslation, int currentAddress, char *translateTargetOperand, COMMAND command, int numOperands, char **operand, LinkedList *commandList, LinkedList *dataList,
                         LinkedList *symbolList, LinkedList *externList, char *firstOperand_A_R_E, LinkedList *externListToPrint);

RESULT handleTwoOperands(char *sourceAndTargetOperandsTranslation, int currentAddress, char *translateSourceOperand, char *translateTargetOperand,
                         COMMAND command, int numOperands, char **operand, LinkedList *commandList, LinkedList *dataList,
                         LinkedList *symbolList, LinkedList *externList,  char *firstOperand_A_R_E,  char *secondOperand_A_R_E, LinkedList *externListToPrint);

#endif

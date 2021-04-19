

#ifndef MMN_14_PRINTTOFILE_H
#define MMN_14_PRINTTOFILE_H

#include "ParseCommand.h"
#include "TranslateOperands.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>
#include "Parser.h"

RESULT print_command_to_obj_file (FILE *objFile, char *totalCommandTranslation, char *translateSourceOperand,
                                  char *translateTargetOperand, int numOperands, char *firstOperand_A_R_E,
                                  char *secondOperand_A_R_E, int currentAddress, LinkedList *externListToPrint, int *externalOperandsCounter);
RESULT print_data_to_obj_file (FILE *objFile, char *hexTranslation, int address);
RESULT print_entry_to_entry_file(FILE *entFile, LinkedList *entryList);
RESULT print_extern_to_extern_file(FILE *extFile, LinkedList *externList);
#endif


#ifndef MMN_14_PARSEDATA_H
#define MMN_14_PARSEDATA_H
#include "TranslateOperands.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>
#include "Parser.h"
RESULT parse_data (FILE *objFile, LinkedList *dataList, LinkedList *symbolList, LinkedList *externList, LinkedList *entryList, int ICF);
RESULT handle_data_declaration (FILE *objFile, LinkedList *dataList, int *dataArray , int dataArrayLength, int currentAddress);
RESULT handle_string_declaration (FILE *objFile, LinkedList *dataList, char *stringCharArray  , int currentAddress);
#endif

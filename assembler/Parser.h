
#ifndef MMN_14_PARSER_H
#define MMN_14_PARSER_H

#include <stdio.h>
#include "errors.h"
#include "LinkedList.h"
#include "Symbol.h"
typedef enum LabelFlag_f {
    ON,
    OFF
} LabelFlag;
typedef RESULT (*f)(FILE*);
typedef enum Declares_t {
    DATA_DECLARE,
    STRING_DECLARE
} Declare;
typedef struct DataProperties_t {
    Declare declare;

    int *dataArray;
    int dataArrayLength;

    char *charArray;

    int beginDC;
    int endDC;
} DataProperties;
typedef struct CommandProperties_t {
    char *command;

    char **operands;
    int numOperands;

    int beginIC;
    int endIC;

} CommandProperties;

void line_properties_free(void*);

typedef enum e_typeOfDataDeclaration {
    DATA,
    STRING
}typeOfDataDeclaration;

RESULT parse(FILE* fp, char* fileName);
void fill_extern_list_address(LinkedList *externListToPrint, int address, const int *index);

#endif



#ifndef MMN_14_TRANSLATE_COMMAND_H
#define MMN_14_TRANSLATE_COMMAND_H
#include "Utils.h"
#include "LinkedList.h"
typedef enum e_labels
{
    data,
    string,
    entry
} LABEL;


RESULT translate_command(char *dest, char *commandStr) ;
COMMAND find_command (char *command);
void init( int * binaryNumArray);
void printArray (int * p, int size);
#endif

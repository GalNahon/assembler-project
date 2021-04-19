

#ifndef MMN_14_UTILS_H
#define MMN_14_UTILS_H
#include<string.h>
#include "LinkedList.h"
#include "errors.h"
#include <stdio.h>
#define BinaryLength 12

typedef enum e_commands
{
    mov,
    cmp,
    add,
    sub,
    lea,
    clr,
    not,
    inc,
    dec,
    jmp,
    bne,
    jsr,
    red,
    prn,
    rts,
    stop
} COMMAND;
const char* get_error (RESULT result);
int checkCommaBetweenOperands(char *str);
int firstSeparator(char* str);
void init_binary_number(char *binaryNumArray, int i);
RESULT decimal_to_binary_string(char *dest, int decimalNum, int length);
int num_of_delimiter(char* string, char delimiter);
int is_external_label(char *operandToAnalyze, LinkedList *externList);
int is_entry_label(char *operandToAnalyze, LinkedList *entryList);
int skip_white_spaces(char *str, int index);
RESULT check_space_before_char(char* str);
RESULT check_comma_in_operands(char* str);
int isDigit(char s);
void init_binary_number(char *binaryNumArray, int length);
int string_to_int (char *str);

RESULT is_numeric_string_legal(char *string);
RESULT is_string_declaration_legal(char * string);

void translate_binary_string_to_hex(char *dest, char *binaryNumberString);
void hex_translation (char *translatedBinaryStringToHexChar, char *translateToHex);
#endif



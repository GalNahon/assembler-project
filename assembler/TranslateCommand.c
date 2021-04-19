
#include "TranslateCommand.h"
#include "Utils.h"
#include <string.h>
#include "LinkedList.h"

#define OPCODE_LENGTH 4
#define FUNCT_LENGTH 4

/** commands: **/
#define NO_FUNCT 0

#define MOV_OPCODE 0

#define CMP_OPCODE 1

#define ADD_OPCODE 2
#define ADD_FUNCT 10

#define SUB_OPCODE 2
#define SUB_FUNCT 11

#define LEA_OPCODE 4

#define CLR_OPCODE 5
#define CLR_FUNCT 10

#define NOT_OPCODE 5
#define NOT_FUNCT 11

#define INC_OPCODE 5
#define INC_FUNCT 12

#define DEC_OPCODE 5
#define DEC_FUNCT 13

#define JMP_OPCODE 9
#define JMP_FUNCT 10

#define BNE_OPCODE 9
#define BNE_FUNCT 11

#define JSR_OPCODE 9
#define JSR_FUNCT 12

#define RED_OPCODE 12

#define PRN_OPCODE 13

#define RTS_OPCODE 14

#define STOP_OPCODE 15


RESULT translate_command(char *dest, char *commandStr) {

    char translatedOpcode[OPCODE_LENGTH + 1];
    char translatedFunct[FUNCT_LENGTH + 1];
    COMMAND command;

    translatedOpcode[0] = '\0';
    translatedFunct[0] = '\0';
    command = find_command(commandStr);

    if (command == mov) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, MOV_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NO_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == cmp) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, CMP_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NO_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == add) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, ADD_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, ADD_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == sub) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, SUB_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, SUB_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == lea) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, LEA_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NO_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == clr) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, CLR_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, CLR_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == not) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, NOT_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NOT_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == inc) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, INC_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, INC_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == dec) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, DEC_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, DEC_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == jmp) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, JMP_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, JMP_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == bne) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, BNE_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, BNE_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == jsr) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, JSR_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, JSR_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == red) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, RED_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NO_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == prn) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, PRN_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NO_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == rts) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, RTS_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NO_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    } else if (command == stop) {
        RESULT resOpcode;
        RESULT resFunct;
        resOpcode = decimal_to_binary_string(translatedOpcode, STOP_OPCODE, OPCODE_LENGTH);
        resFunct = decimal_to_binary_string(translatedFunct, NO_FUNCT, FUNCT_LENGTH);
        if (resFunct != SUCCESS || resOpcode != SUCCESS)
            return ERROR_IN_COMMAND_TRANSLATION;
        strcat(dest, translatedOpcode);
        strcat(dest, translatedFunct);
        return SUCCESS;
    }
    return SUCCESS;
}

COMMAND find_command(char *command) {
    if (strncmp(command, "mov", 3) == 0)
        return mov;
    if (strncmp(command, "cmp", 3) == 0)
        return cmp;
    if (strncmp(command, "add", 3) == 0)
        return add;
    if (strncmp(command, "sub", 3) == 0)
        return sub;
    if (strncmp(command, "lea", 3) == 0)
        return lea;
    if (strncmp(command, "clr", 3) == 0)
        return clr;
    if (strncmp(command, "not", 3) == 0)
        return not;
    if (strncmp(command, "inc", 3) == 0)
        return inc;
    if (strncmp(command, "dec", 3) == 0)
        return dec;
    if (strncmp(command, "jmp", 3) == 0)
        return jmp;
    if (strncmp(command, "bne", 3) == 0)
        return bne;
    if (strncmp(command, "jsr", 3) == 0)
        return jsr;
    if (strncmp(command, "red", 3) == 0)
        return red;
    if (strncmp(command, "prn", 3) == 0)
        return prn;
    if (strncmp(command, "rts", 3) == 0)
        return rts;
    if (strncmp(command, "stop", 4) == 0)
        return stop;
    return stop;
}



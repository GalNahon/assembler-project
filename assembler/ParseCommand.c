
#include "ParseCommand.h"
#include "TranslateOperands.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "PrintToFile.h"
#include "ParsAddressingMode.h"


#define SOURCE_OPERAND 0
#define TARGET_OPERAND 1

#define ADDRESSING_MODE_OPERAND_LENGTH 2
#define TOTAL_ADDRESSING_MODE_LENGTH 4
#define FINAL_WORD_TRANSLATION_LENGTH 12
#define NO_OPERAND 0
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


RESULT parse_command (FILE *objFile, LinkedList *commandList, LinkedList *dataList, LinkedList *symbolList, LinkedList *externList, int *IC, int *ICF, int *DC,  LinkedList *externListToPrint){
    Node *commandListCurrentNode;
    char totalCommandTranslation[13];
    int externalOperandsCounterPointer;
    commandListCurrentNode = commandList->head;
    externalOperandsCounterPointer = 0;

    while (commandListCurrentNode != NULL) {
        CommandProperties* commandListCurrentData;
        char *commandStr;
        int numOperands;
        char **operands;
        int currentAddress;
        COMMAND command;
        RESULT resTranslateCommand;
        char translatedOpcodeAndFunct[9];

        char translateSourceOperand [FINAL_WORD_TRANSLATION_LENGTH + 1];
        char translateTargetOperand [FINAL_WORD_TRANSLATION_LENGTH + 1];
        char sourceAndTargetOperandsTranslation [TOTAL_ADDRESSING_MODE_LENGTH + 1];

        char firstOperand_A_R_E [2];
        char secondOperand_A_R_E [2];

        commandListCurrentData = commandListCurrentNode->data;
        commandStr = commandListCurrentData->command;
        numOperands = commandListCurrentData->numOperands;
        operands = commandListCurrentData->operands;
        currentAddress = commandListCurrentData->beginIC;
        command = find_command(commandStr);
        translatedOpcodeAndFunct[0] = '\0';
        resTranslateCommand = translate_command(translatedOpcodeAndFunct, commandStr);
        if(resTranslateCommand != SUCCESS)
            return resTranslateCommand;

        translateSourceOperand[0] = '\0';
        translateTargetOperand[0] = '\0';
        sourceAndTargetOperandsTranslation[0] = '\0';

        firstOperand_A_R_E [1] = '\0';
        firstOperand_A_R_E [0] = 'A';
        secondOperand_A_R_E [1] = '\0';
        secondOperand_A_R_E [0] = 'A';

        if(numOperands == 0){
            RESULT handler;
            handler = handleNoOperands(sourceAndTargetOperandsTranslation, currentAddress, command, numOperands, operands, commandList, dataList, symbolList, externList, externListToPrint);
            IC++;
            if(handler != SUCCESS)
                return handler;
        }
        if(numOperands == 1){
            RESULT handler;
            handler = handleOneOperands(sourceAndTargetOperandsTranslation, currentAddress, translateTargetOperand, command, numOperands, operands, commandList, dataList, symbolList, externList, secondOperand_A_R_E, externListToPrint);
            IC = IC + 2;
            if(handler != SUCCESS)
                return handler;
        }
        if(numOperands == 2){
            RESULT handler;
            handler = handleTwoOperands(sourceAndTargetOperandsTranslation, currentAddress, translateSourceOperand, translateTargetOperand, command, numOperands, operands, commandList, dataList, symbolList, externList, firstOperand_A_R_E, secondOperand_A_R_E, externListToPrint);
            IC = IC + 3;
            if(handler != SUCCESS)
                return handler;
        }
        strcat(totalCommandTranslation, translatedOpcodeAndFunct);
        strcat(totalCommandTranslation, sourceAndTargetOperandsTranslation);
        print_command_to_obj_file(objFile, totalCommandTranslation, translateSourceOperand, translateTargetOperand,
                                  numOperands, firstOperand_A_R_E, secondOperand_A_R_E, currentAddress, externListToPrint, &externalOperandsCounterPointer);
        memset(sourceAndTargetOperandsTranslation, 0, sizeof sourceAndTargetOperandsTranslation);
        memset(totalCommandTranslation, 0, sizeof totalCommandTranslation);
        memset(translateSourceOperand, 0, sizeof translateSourceOperand);
        memset(translateTargetOperand, 0, sizeof translateTargetOperand);
        commandListCurrentNode = commandListCurrentNode->next;
    }
    return SUCCESS;
}
RESULT handleNoOperands(char *sourceAndTargetOperandsTranslation, int currentAddress, COMMAND command, int numOperands, char **operand, LinkedList *commandList, LinkedList *dataList,
                        LinkedList *symbolList, LinkedList *externList, LinkedList *externListToPrint)  {

    char *noSourceOperand;
    char *noTargetOperand;
    addressingMode firstAddressingMode;
    addressingMode secondAddressingMode;
    char translateSourceOperandAddressingMode [ADDRESSING_MODE_OPERAND_LENGTH + 1];
    char translateTargetOperandAddressingMode [ADDRESSING_MODE_OPERAND_LENGTH + 1];
    RESULT resParseFirstAddressingMode;
    RESULT resParseSecondAddressingMode;

    noSourceOperand = "NO_OPERAND";
    noTargetOperand = "NO_OPERAND";
    firstAddressingMode = NO_OPERAND_ADDRESS;
    secondAddressingMode = NO_OPERAND_ADDRESS;
    translateSourceOperandAddressingMode[0] = '\0';
    translateTargetOperandAddressingMode[0] = '\0';

    resParseFirstAddressingMode = parse_addressing_mode( &firstAddressingMode, translateSourceOperandAddressingMode, translateTargetOperandAddressingMode, noSourceOperand, SOURCE_OPERAND, command, commandList, dataList, symbolList, externList);
    if(resParseFirstAddressingMode != SUCCESS)
        return resParseFirstAddressingMode;

    resParseSecondAddressingMode = parse_addressing_mode(&secondAddressingMode, translateSourceOperandAddressingMode, translateTargetOperandAddressingMode, noTargetOperand, TARGET_OPERAND, command, commandList, dataList, symbolList, externList);
    if(resParseSecondAddressingMode != SUCCESS)
        return resParseSecondAddressingMode;
    strcat(sourceAndTargetOperandsTranslation, translateSourceOperandAddressingMode);
    strcat(sourceAndTargetOperandsTranslation, translateTargetOperandAddressingMode);
    return SUCCESS;
}

RESULT handleOneOperands(char *sourceAndTargetOperandsTranslation, int currentAddress, char *translateTargetOperand, COMMAND command, int numOperands, char **operand, LinkedList *commandList, LinkedList *dataList,
                         LinkedList *symbolList, LinkedList *externList, char *firstOperand_A_R_E, LinkedList *externListToPrint) {

    char *noSourceOperand;
    char *secondOperand;
    addressingMode firstAddressingMode;
    addressingMode secondAddressingMode;
    char translateSourceOperandAddressingMode [ADDRESSING_MODE_OPERAND_LENGTH + 1];
    char translateTargetOperandAddressingMode [ADDRESSING_MODE_OPERAND_LENGTH + 1];
    RESULT resParseFirstAddressingMode;
    RESULT resParseSecondAddressingMode;
    RESULT resTranslateSecondOperand;

    noSourceOperand = "NO_OPERAND";
    secondOperand = operand[0];
    firstAddressingMode = NO_OPERAND_ADDRESS;
    translateSourceOperandAddressingMode[0] = '\0';
    translateTargetOperandAddressingMode[0] = '\0';

    resParseFirstAddressingMode = parse_addressing_mode(&firstAddressingMode, translateSourceOperandAddressingMode, translateTargetOperandAddressingMode, noSourceOperand, SOURCE_OPERAND, command, commandList, dataList, symbolList, externList);
    if(resParseFirstAddressingMode != SUCCESS)
        return resParseFirstAddressingMode;

    resParseSecondAddressingMode = parse_addressing_mode(&secondAddressingMode, translateSourceOperandAddressingMode, translateTargetOperandAddressingMode, secondOperand, TARGET_OPERAND, command, commandList, dataList, symbolList, externList);
    if(resParseSecondAddressingMode != SUCCESS)
        return resParseSecondAddressingMode;

    resTranslateSecondOperand = translate_operand(SECOND_OPERAND, currentAddress, secondOperand, secondAddressingMode, translateTargetOperand, symbolList, externList, firstOperand_A_R_E, externListToPrint);
    if(resTranslateSecondOperand != SUCCESS)
        return resTranslateSecondOperand;
    strcat(sourceAndTargetOperandsTranslation, translateSourceOperandAddressingMode);
    strcat(sourceAndTargetOperandsTranslation, translateTargetOperandAddressingMode);
    return SUCCESS;
}

RESULT handleTwoOperands(char *sourceAndTargetOperandsTranslation, int currentAddress, char *translateSourceOperand, char *translateTargetOperand,
                         COMMAND command, int numOperands, char **operand, LinkedList *commandList, LinkedList *dataList,
                         LinkedList *symbolList, LinkedList *externList, char *firstOperand_A_R_E,  char *secondOperand_A_R_E, LinkedList *externListToPrint){
    char* firstOperand;
    char* secondOperand;
    addressingMode firstAddressingMode;
    addressingMode secondAddressingMode;
    char translateSourceOperandAddressingMode [ADDRESSING_MODE_OPERAND_LENGTH + 1];
    char translateTargetOperandAddressingMode [ADDRESSING_MODE_OPERAND_LENGTH + 1];
    RESULT resParseFirstAddressingMode;
    RESULT resParseSecondAddressingMode;
    RESULT resTranslateFirstOperand;
    RESULT resTranslateSecondOperand;

    firstOperand = operand[0];
    secondOperand = operand[1];
    translateSourceOperandAddressingMode[0] = '\0';
    translateTargetOperandAddressingMode[0] = '\0';


    resParseFirstAddressingMode = parse_addressing_mode(&firstAddressingMode, translateSourceOperandAddressingMode, translateTargetOperandAddressingMode, firstOperand, SOURCE_OPERAND, command, commandList, dataList, symbolList, externList);
    if(resParseFirstAddressingMode != SUCCESS)
        return resParseFirstAddressingMode;

    resParseSecondAddressingMode = parse_addressing_mode(&secondAddressingMode, translateSourceOperandAddressingMode, translateTargetOperandAddressingMode, secondOperand, TARGET_OPERAND, command, commandList, dataList, symbolList, externList);
    if(resParseSecondAddressingMode != SUCCESS)
        return resParseSecondAddressingMode;

    resTranslateFirstOperand = translate_operand(FIRST_OPERAND, currentAddress, firstOperand, firstAddressingMode, translateSourceOperand, symbolList, externList, firstOperand_A_R_E, externListToPrint);
    if(resTranslateFirstOperand != SUCCESS)
        return resTranslateFirstOperand;

    resTranslateSecondOperand = translate_operand(SECOND_OPERAND, currentAddress, secondOperand, secondAddressingMode, translateTargetOperand, symbolList, externList, secondOperand_A_R_E, externListToPrint);
    if(resTranslateSecondOperand != SUCCESS)
        return resTranslateSecondOperand;
    strcat(sourceAndTargetOperandsTranslation, translateSourceOperandAddressingMode);
    strcat(sourceAndTargetOperandsTranslation, translateTargetOperandAddressingMode);
    return SUCCESS;

}


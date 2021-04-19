
#include "ParseData.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>
#include "PrintToFile.h"

#define DATA_LENGTH 12
#define HEX_LENGTH 4


RESULT parse_data (FILE *objFile, LinkedList *dataList, LinkedList *symbolList, LinkedList *externList, LinkedList *entryList,int ICF){
    Node *dataListCurrentNode;
    dataListCurrentNode = dataList->head;
    while (dataListCurrentNode != NULL) {
        DataProperties *dataListCurrentData;
        Declare declaration;
        dataListCurrentData = dataListCurrentNode->data;
        declaration = dataListCurrentData->declare;
        if(declaration == DATA_DECLARE){
            int *dataArray;
            int currentAddress;
            int dataArrayLength;
            RESULT resDataHandler;
            dataArray = dataListCurrentData->dataArray;
            currentAddress = dataListCurrentData->beginDC + ICF;
            dataArrayLength= dataListCurrentData->dataArrayLength;
            resDataHandler = handle_data_declaration(objFile, dataList, dataArray, dataArrayLength, currentAddress);
            if(resDataHandler != SUCCESS)
                return resDataHandler;
        }
        if( declaration == STRING_DECLARE){
            char *stringCharArray;
            int currentAddress;
            RESULT resStringHandler;
            stringCharArray = dataListCurrentData->charArray;
            currentAddress = dataListCurrentData->beginDC + ICF;
            resStringHandler = handle_string_declaration(objFile, dataList, stringCharArray, currentAddress);
            if(resStringHandler != SUCCESS)
                return resStringHandler;
        }
        dataListCurrentNode = dataListCurrentNode->next;
    }
    fclose(objFile);
        return SUCCESS;

    }

RESULT handle_data_declaration (FILE *objFile, LinkedList *dataList, int *dataArray , int dataArrayLength, int dataAddress){
    int index;
    char dataInBinaryString[DATA_LENGTH];
    char hexDataTranslation[HEX_LENGTH];

    dataInBinaryString[0] ='\0';
    hexDataTranslation[0] ='\0';

    for(index = 0; index < dataArrayLength; index++){
        RESULT resDecimalToBinary;
        resDecimalToBinary = decimal_to_binary_string(dataInBinaryString, dataArray[index], DATA_LENGTH);
        if(resDecimalToBinary != SUCCESS)
            return resDecimalToBinary;
        translate_binary_string_to_hex(hexDataTranslation, dataInBinaryString);
        print_data_to_obj_file(objFile, hexDataTranslation, dataAddress);
        memset(hexDataTranslation, 0, sizeof hexDataTranslation);
        memset(dataInBinaryString, 0, sizeof dataInBinaryString);
        dataAddress ++;
    }
    return SUCCESS;
}


RESULT handle_string_declaration (FILE *objFile, LinkedList *dataList, char *stringCharArray  , int stringAddress){
    int index;
    char stringInBinaryString[DATA_LENGTH];
    char hexStringTranslation[HEX_LENGTH];
    index = 1;
    stringInBinaryString[0] ='\0';
    hexStringTranslation[0] = '\0';
    stringCharArray[strlen(stringCharArray) -1] = '\0';
    while (index <= strlen(stringCharArray)){
        int charToAscii;
        RESULT resDecimalToBinary;
        charToAscii = (int)stringCharArray[index];
        resDecimalToBinary = decimal_to_binary_string(stringInBinaryString, charToAscii, DATA_LENGTH);
        if(resDecimalToBinary != SUCCESS)
            return resDecimalToBinary;
        translate_binary_string_to_hex(hexStringTranslation, stringInBinaryString);
        print_data_to_obj_file(objFile, hexStringTranslation, stringAddress);
        memset(hexStringTranslation, 0, sizeof hexStringTranslation);
        memset(stringInBinaryString, 0, sizeof stringInBinaryString);
        stringAddress ++;
        index ++;
    }
    return SUCCESS;
}
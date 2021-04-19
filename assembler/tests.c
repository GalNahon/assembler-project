
#include <stdio.h>
#include "TranslateCommand.h"
#include "Parser.h"
#include "errors.h"
#include "tests.h"
#include "Parser.h"
#include "LinkedList.h"
#include "Parser.h"


void runOpcodeAndFunctTests(){

   testParse();
/**   testMov();
      test();
   tstCheckSeparatorInData();
   testCmp();
   testAdd();
   testSub();
   testLea();
   testClr();
   testNot();
   testInc();
   testDec();
   testJmp();
   testBne();
   testJsr();
   testRed();
   testPrn();
   testRts();
   testStop();
   **/
}

void testParse() {

    FILE *fp = fopen("testFile.txt", "rw");
/**    parse(fp);**/
    fclose(fp);
}
/**
void test() {
    char command[100] = "STR: .string \"abcd\" ";
    printf("test\n");
    processCommand(command, DC, IC, Label_node* labels_node_head);
    RESULT res = checkCommaInData(command);
    if (res == SUCCESS)
        printf("SUCCESS");
}
void tstCheckSeparatorInData() {
    char command[100] = "+12,   -1  , +11";
    printf("test CheckSeparatorInData\n");
    RESULT res = checkCommaInData(command);
    if (res == SUCCESS)
        printf("SUCCESS");
}



void testStop() {
    char command[4] = "stop";
    printf("binary translation of stop is:\n");
    translate_command(command);
    printf("\n");
}

void testRts() {
    char command[4] = "rts";
    printf("binary translation of rts is:\n");
    translate_command(command);
    printf("\n");
}

void testPrn() {
    char command[4] = "prn";
    printf("binary translation of prn is:\n");
    translate_command(command);
    printf("\n");
}

void testRed() {
    char command[4] = "red";
    printf("binary translation of red is:\n");
    translate_command(command);
    printf("\n");
}

void testJsr() {
    char command[4] = "jsr";
    printf("binary translation of jsr is:\n");
    translate_command(command);
    printf("\n");
}

void testBne() {
    char command[4] = "bne";
    printf("binary translation of bne is:\n");
    translate_command(command);
    printf("\n");
}

void testJmp() {
    char command[20] = "jmp r1";
    printf("binary translation of jmp is:\n");
    translate_command(command);
    printf("\n");
}

void testDec() {
    char command[4] = "dec";
    printf("binary translation of dec is:\n");
    translate_command(command);
    printf("\n");
}

void testInc() {
    char command[4] = "inc";
    printf("binary translation of inc is:\n");
    translate_command(command);
    printf("\n");
}

void testNot() {
    char command[4] = "not";
    printf("binary translation of not is:\n");
    translate_command(command);
    printf("\n");
}

void testClr() {
    char command[4] = "clr";
    printf("binary translation of clr is:\n");
    translate_command(command);
    printf("\n");
}

void testLea() {
    char command[4] = "lea";
    printf("binary translation of lea is:\n");
    translate_command(command);
    printf("\n");
}

void testSub() {
    char command[20] = "sub   r1,r4";
    printf("binary translation of sub is:\n");
    translate_command(command);
    printf("\n");
}

void testAdd() {
    char command[4] = "add";
    printf("binary translation of add is:\n");
    translate_command(command);
    printf("\n");
}

void testMov() {
    LinkedList *commandsList = create_linked_list();
    LinkedList *dataList = create_linked_list();
    LinkedList *symbolList = create_linked_list();
    LinkedList *externList = create_linked_list();
    LinkedList *entryList = create_linked_list();
    char command[20] = "mov r1  , r2";
    printf("binary translation of mov is:\n");
    parseCommand(command, IC, DC, commandsList, dataList);
    printf("\n");

}
void testCmp() {
    char command[4] = "cmp";
    printf("binary translation of cmp is:\n");
    translate_command(command);
    printf("\n");
}
**/


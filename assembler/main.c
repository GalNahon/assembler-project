#include <stdio.h>
#include "Parser.h"

int main(int argc, char** argv)
{
    int i;
    for (i = 1; i < argc; i++) {
        parse(fopen(argv[i],"r"), argv[i]);
    }

    /**runOpcodeAndFunctTests();**/
    return 0;
}
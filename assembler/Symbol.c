
#include "Symbol.h"
#include <string.h>
#include <stdlib.h>
int symbol_predicate(void *symbol, char *symbolName) {
    Symbol* temp;
    temp = (Symbol*) symbol;
    if (strcmp(temp->name, symbolName) == 0) {
        return 1;
    }
    return 0;
}

void symbol_free(void *symbol) {
    Symbol* temp;
    temp = (Symbol*) symbol;
    free(temp->name);
}

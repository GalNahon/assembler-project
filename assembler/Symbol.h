

#ifndef MMN_14_SYMBOL_H
#define MMN_14_SYMBOL_H
typedef enum SymbolType_t {
  CODE_SYMBOL_TYPE,
  DATA_SYMBOL_TYPE,
  EXTERNAL_SYMBOL_TYPE,
  ENTRY_SYMBOL_TYPE
} SymbolType;
typedef struct Symbol_t {
    char* name;
    int address;
    SymbolType type;
} Symbol;

int symbol_predicate(void* symbol, char* symbolName);
void symbol_free(void* symbol);
#endif

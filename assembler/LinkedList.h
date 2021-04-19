
#ifndef MMN_14_LINKEDLIST_H
#define MMN_14_LINKEDLIST_H
#define MAX_LEN 31
typedef struct NodeS Node;
typedef int (*predicate)(void*, char*);
typedef void (*freeData)(void*);
struct NodeS {
    void* data;
    Node* next;
};

typedef struct LinkedListS {
    Node* head;
} LinkedList;

LinkedList* create_linked_list();
void destroy_linked_list(LinkedList *list, freeData freeDataFunction);
void add_item(LinkedList* list, void* data);
void* get_item(LinkedList* list, char* itemId, predicate p);
void* get_item_by_index(LinkedList* list, unsigned int index);
void* get_last_item(LinkedList* list);



#endif

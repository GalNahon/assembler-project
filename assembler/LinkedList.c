
#include "LinkedList.h"
#include <stdlib.h>
LinkedList* create_linked_list() {
    LinkedList* list;
    list= malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void destroy_linked_list(LinkedList* list, freeData freeDataFunction) {
    Node* head;
    Node* temp;
    head = list->head;
    while(head != NULL) {
        temp = head->next;
        freeDataFunction(head->data);
        free(head->data);
        free(head);
        head = temp;
    }
    free(list);
}

void add_item(LinkedList* list, void *data) {
    Node* newNode;
    Node** curr;
    newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;

    curr = &list->head;
    if (*curr == NULL) {
        *curr = newNode;
        return;
    }
    while(*curr != NULL) {
        if ((*curr)->next == NULL) {
            (*curr)->next = newNode;
            break;
        }
        curr = &((*curr)->next);
    }
}

void* get_item(LinkedList* list, char* itemId, predicate p) {
    Node* curr;
    curr = list->head;
    while(curr != NULL && !p(curr->data, itemId)) {
        curr = curr->next;
    }
    if (curr == NULL) {
        return NULL;
    }
    return curr->data;
}

void* get_item_by_index(LinkedList* list, unsigned int index) {
    Node* curr;
    curr = list->head;
    while(index > 0) {
        if (curr == NULL) {
            return NULL;
        }
        curr = curr->next;
        index--;
    }
    if (curr == NULL) {
        return NULL;
    }
    return curr->data;
}

void *get_last_item(LinkedList *list) {
    Node* curr;
    curr = list->head;
    while(curr != NULL) {
        if (curr->next == NULL) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

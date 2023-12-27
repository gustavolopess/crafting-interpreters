/*
Do the same thing for C. To get some practice with pointers, define a doubly linked list of heap-allocated strings. Write functions to insert, find, and delete items from it. Test them.
*/

// TODO: tests
// TODO: keep track of tail

#include <stdio.h>
#include <stdlib.h>

typedef struct list_node list_node;

struct list_node {
    list_node *prev;
    list_node *next;
    int val;
};

list_node* new_list_node(list_node *prev, list_node *next, int val) {
    list_node *node = (list_node*)malloc(sizeof(list_node));
    node->prev = prev;
    node->next = next;
    node->val = val;
    return node;
}

typedef struct doubly_list doubly_list;

struct doubly_list {
    list_node* head;
};

doubly_list* new_doubly_linked_list(list_node* head) {
    doubly_list* list = (doubly_list*)malloc(sizeof(doubly_list));
    list->head = head;
    return list;
}

void pprint(doubly_list* list) {
    list_node* curr = list->head->next;
    if (curr == NULL) {
        printf("Empty\n");
        return;
    }
    while (curr != NULL) {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

void push_to_end(doubly_list* list, int val) {
    list_node* curr = list->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    list_node* node = new_list_node(curr, NULL, val);
    curr->next = node;
}

void append_to_begin(doubly_list* list, int val) {
    list_node* head = list->head;
    list_node* curr_head_next = head->next;
    
    if (curr_head_next == NULL) {
        list_node* node = new_list_node(head, NULL, val);
        head->next = node;
        return;
    }
    
    list_node* node = new_list_node(head, curr_head_next, val);
    curr_head_next->prev = node;
    head->next = node;
}

list_node* search_first_occurrence(doubly_list* list, int val) {
    list_node* curr = list->head;
    while (curr != NULL && curr->val != val) {
        curr = curr->next;
    }
    if (curr == NULL) {
        return NULL;
    }
    return curr;
}

void remove_node(doubly_list* list, list_node* node) {
    if (node == NULL) return;
    
    list_node* node_prev = node->prev;
    list_node* node_next = node->next;
    
    if (node_prev != NULL) {
        node_prev->next = node_next;
    }
    
    if (node_next != NULL) {
        node_next->prev = node_prev;
    }
}

void add_after_node(doubly_list* list, list_node* node, int val) {
    if (node == NULL) return;
    
    list_node* new_node = new_list_node(node, node->next, val);
    node->next = new_node;
}

void add_before_node(doubly_list* list, list_node* node, int val) {
    if (node == NULL) return;
    
    list_node* new_node = new_list_node(node->prev, node, val);
    list_node* node_prev = node->prev;
    node->prev = new_node;
    node_prev->next = new_node;
}

list_node* pop_from_begin(doubly_list* list) {
    if (list == NULL) return NULL;
    
    list_node* head = list->head;
    if (head == NULL || head->next == NULL) return NULL;
    
    list_node* popped = head->next;
    head->next = head->next->next;
    return popped;
}

int main() {
    list_node* head = new_list_node(NULL, NULL, -1); // head is only for representation
    doubly_list* list = new_doubly_linked_list(head);
    
    push_to_end(list, 1);
    push_to_end(list, 2);
    append_to_begin(list, 3);
    append_to_begin(list, 5);
    pprint(list);
    list_node* found = search_first_occurrence(list, 3);
    printf("Found: %d\n", found->val);
    add_after_node(list, found, 199);
    add_before_node(list, found, 293);
    pprint(list);
    
    found = search_first_occurrence(list, 5);
    add_before_node(list, found, -40);
    pprint(list);
    
    append_to_begin(list, -390);
    pprint(list);
    
    printf("head->next: %d\n", head->next->val);
    
    printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
     printf("popped: %d\n", pop_from_begin(list)->val);
    pprint(list);
    
    return 0;
}

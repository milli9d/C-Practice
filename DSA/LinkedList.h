#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef LinkedList
#define LinkedList

typedef struct ListNode
{
    struct ListNode *next;
    int32_t val;
} ListNode;

void append(int32_t val, ListNode **list);
void printList(ListNode *list);
void generateRandomList(uint32_t size, uint32_t mod, ListNode **list);
void delete_node_by_idx(int32_t idx, ListNode **list);
void delete_node_by_val(int32_t val, ListNode **list);
void deallocateList(ListNode **list);
void reverseListIterative(ListNode **list);
ListNode *reverseListHelper(ListNode *curr, ListNode **head);
void reverseList(ListNode **head);

#endif
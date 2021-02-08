#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Queue.h"
/*
    Queue is FIFO data structure 
    PUSH from front 
    POP from Back

*/

// Push from front , always replace head
void enqueue(int val, Queue **queuePtr)
{
    // If no queue exists , then allocate new queue
    if (*queuePtr == NULL)
    {
        Queue *temp = (Queue *)malloc(sizeof(Queue));
        temp->mData = NULL;
        temp->size = 0;
        *queuePtr = temp;
    }

    // Extract pointer to head
    ListNode **head = &((*queuePtr)->mData);
    ListNode *insertPtr = *head;
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    temp->val = val;
    temp->next = NULL;
    // If list already exists , then attach to node
    if (insertPtr != NULL)
    {
        temp->next = insertPtr;
    }
    // Attach new node
    *head = temp;
    (*queuePtr)->size++;
    return;
}

// Remove last node / pop from back
void dequeue(Queue *queuePtr)
{
    // Sanity check
    if (queuePtr == NULL || queuePtr->mData == NULL)
    {
        printf("Queue is empty!\n");
        return;
    }
    ListNode *searchPtr = queuePtr->mData;
    // Traverse to the second last element
    while (searchPtr->next != NULL && searchPtr->next->next != NULL)
    {
        searchPtr = searchPtr->next;
    }
    // Here searchPtr is at second last element
    ListNode *delPtr = searchPtr->next;
    searchPtr->next = NULL;
    free(delPtr);
    queuePtr->size--;
    return;
}

// Return the first-in (back) element value
int peekQueue(Queue *queuePtr)
{
    if (queuePtr == NULL || queuePtr->mData == NULL)
    {
        printf("Queue is Empty!\n");
        return -9999;
    }

    // Traverse to end
    ListNode *searchPtr = queuePtr->mData;
    while (searchPtr->next != NULL)
    {
        searchPtr = searchPtr->next;
    }
    return searchPtr->val;
}

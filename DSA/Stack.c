#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Stack.h"
#include <time.h>

// Append to front
void push_on_stack(int val, struct Stack **stackPtr)
{
    // If stack does not exist, allocate a new stack
    if (*stackPtr == NULL)
    {
        Stack *temp = (Stack *)malloc(sizeof(Stack));
        // Initialize stack
        temp->mData = NULL;
        temp->size = 0;
        // Make this the new stack , continue from here
        *stackPtr = temp;
    }

    //Make new Node for pushing
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    temp->val = val;
    temp->next = NULL;

    // Make pointer to head for easy access
    ListNode **head = &((*stackPtr)->mData);
    // Make a Ptr to head node for easy access
    ListNode *insertPtr = *head;

    // This means that list is not empty,  then attach the old list to new node
    if (insertPtr != NULL)
    {
        ListNode *originalHead = *head;
        temp->next = originalHead;
    }
    // Here we have already dealt with rest of the list, Attach new node
    *head = temp;
    // Increment size
    (*stackPtr)->size += 1;
    return;
}

// Delete from front , always delete head
void pop_from_stack(Stack *stackPtr)
{
    // Check that a stack exists , if not , then return
    if (stackPtr == NULL)
    {
        printf("Stack does not exist!\n");
        return;
    }
    // Bring head out from stack
    ListNode **head = &(stackPtr->mData);
    // Check if head exists , if not , then return
    if (*head == NULL)
    {
        printf("Stack is empty!\n");
        return;
    }
    // Make a Ptr for easy access
    ListNode *delPtr = *head;
    // If there is more than one element
    if (delPtr->next != NULL)
    {
        ListNode *next = delPtr->next;
        *head = next;
    }
    // De-Allocate memory
    free(delPtr);
    // Decrement Size
    (stackPtr->size)--;
    // Manage dangling pointer
    delPtr = NULL;
}

// Peek value from stack's Top
int peek_stack(Stack *stackPtr)
{
    if (stackPtr != NULL && stackPtr->mData != NULL)
    {
        // The TOP is the head node , so return head node
        return stackPtr->mData->val;
    }
}

// Generate Random Values
void generateStack(int count, int mod, Stack **stackPtr)
{
    srand(time(0));
    for (int i = 0; i < count; i++)
    {
        push_on_stack(rand() % mod, stackPtr);
    }
}
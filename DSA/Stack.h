#include "LinkedList.h"

#ifndef STACK
#define STACK

typedef struct Stack
{
    ListNode *mData;
    int size;
} Stack;

void push_on_stack(int val, Stack **stackPtr);
void generateStack(int count, int mod, Stack **stackPtr);
void pop_from_stack(Stack *stackPtr);
int peek_stack(Stack *stackPtr);
#endif
#include "LinkedList.h"

#ifndef QUEUE
#define QUEUE

typedef struct Queue
{
    ListNode *mData;
    int size;
} Queue;

void enqueue(int val, Queue **queuePtr);
void dequeue(Queue *queuePtr);
int peekQueue(Queue *queuePtr);
#endif
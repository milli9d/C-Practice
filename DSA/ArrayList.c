#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

typedef struct ArrayList
{
    ListNode *mData;
    int size;
    int capacity;
} ArrayList;


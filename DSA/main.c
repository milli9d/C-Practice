#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"

int main(int argc, char const *argv[])
{
	{
		ListNode *list1 = NULL;
		generateRandomList(20, 10, &list1);
		printf("Print Original List\n");
		printList(list1);

		const int idx = 5;
		printf("Delete node by index %d\n", idx);
		delete_node_by_idx(idx, &list1);
		printList(list1);

		const int val1 = 2;
		const int val2 = 0;
		printf("Delete by value %d\n", val1);
		delete_node_by_val(val1, &list1);
		printList(list1);
		printf("Delete by value %d\n", val2);
		delete_node_by_val(val2, &list1);
		printList(list1);

		printf("Reverse List\n");
		reverseList(&list1);
		printList(list1);

		printf("Reverse List\n");
		reverseListIterative(&list1);
		printList(list1);
		deallocateList(&list1);
	}

	{
		printf("Stack test!\n");
		Stack *test = NULL;
		generateStack(15, 10, &test);
		printList(test->mData);
	}

	{
		printf("Queue test!\n");
		Queue *test = NULL;
		enqueue(10, &test);
		enqueue(20, &test);
		enqueue(30, &test);
		enqueue(40, &test);
		enqueue(50, &test);
		dequeue(test);
		dequeue(test);
		dequeue(test);
		int a = peekQueue(test);
		printList(test->mData);
	}

	/* code */
	return 0;
}
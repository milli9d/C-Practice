#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "LinkedList.h"

// Append to end of list
void append(int32_t val, ListNode **list)
{
    // Make a new node
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    temp->val = val;
    temp->next = NULL;

    // This is to search to the end of the list
    ListNode *searchPtr = *list;
    // Head is Null , new list
    if (searchPtr == NULL)
    {
        *list = temp;
        return;
    }
    // Normal Case
    else
    {
        // Traverse to last node , not end of list
        while (searchPtr->next != NULL)
        {
            searchPtr = searchPtr->next;
        }
        // Here we have searchPtr at end of list , attach node
        searchPtr->next = temp;
    }
    return;
}

// Reverse List Iteratively
void reverseListIterative(ListNode **list)
{
    ListNode *searchPtr = *list;
    // Sanity Checks
    if (searchPtr == NULL || searchPtr->next == NULL)
    {
        return;
    }

    ListNode *prevPtr = NULL;
    // Traverse till last node and flip pointers as you go
    while (searchPtr->next != NULL)
    {
        // Copy for treaversing
        ListNode *next = searchPtr->next;
        // Pointer swap
        searchPtr->next = prevPtr;
        // Traverse forward
        prevPtr = searchPtr;
        searchPtr = next;
    }
    // Here prevPtr should be at last node
    if (searchPtr != NULL)
    {
        searchPtr->next = prevPtr;
        *list = searchPtr;
    }
    else
    {
        printf("REVERSE FAILED!\n");
    }
}

ListNode *reverseListHelper(ListNode *curr, ListNode **head)
{
    // Terminating Case
    if (curr == NULL)
    {
        return NULL;
    }
    // Set head to curr
    if (curr->next == NULL)
    {
        *head = curr;
        return curr;
    }

    // Pointer Exchange
    ListNode *first = curr;
    // Attach rest of sorted list
    ListNode *second = reverseListHelper(curr->next, head);
    second->next = first;
    first->next = NULL;

    // Return rest of sorted list
    return first;
}

void reverseList(ListNode **head)
{
    // Call Helper Function
    reverseListHelper(*head, head);
}

// Print out a Linked List
void printList(ListNode *list)
{
    ListNode *searchPtr = list;
    if (searchPtr == NULL)
    {
        printf("LIST IS EMPTY!\n");
        return;
    }
    while (searchPtr != NULL)
    {
        printf("%3d-->", searchPtr->val);
        searchPtr = searchPtr->next;
    }
    printf("\n");
}

void generateRandomList(uint32_t size, uint32_t mod, ListNode **list)
{
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        append((rand() % mod), list);
    }
}

// Delete node where val matches list element
void delete_node_by_val(int32_t val, ListNode **list)
{
    // Sanity Check
    if (*list == NULL)
    {
        printf("Delete:List Empty!\n");
        return;
    }

    // Copy pointer to search through list
    ListNode *searchPtr = *list;
    // Case of head being a match , keep deleting till head no longer matches
    while (searchPtr != NULL && searchPtr->val == val)
    {
        ListNode *delPtr = searchPtr;
        *list = searchPtr->next;
        searchPtr = searchPtr->next;
        free(delPtr);
        delPtr = NULL;
    }
    // Move ahead of head
    while (searchPtr != NULL && searchPtr->next != NULL)
    {
        if (searchPtr->next->val == val)
        {
            // At this point I have element before the element I want to delete
            ListNode *next = searchPtr->next->next;
            ListNode *delPtr = searchPtr->next;
            if (next != NULL)
            {
                searchPtr->next = next;
            }
            else
            {
                searchPtr->next = NULL;
            }
            free(delPtr);
            delPtr = NULL;
            continue;
        }
        searchPtr = searchPtr->next;
    }
}

// Delete a node at a particular index
void delete_node_by_idx(int32_t idx, ListNode **list)
{
    // Sanity Check
    if (*list == NULL)
    {
        printf("Delete:List Empty!\n");
        return;
    }
    // Case of head
    if (idx == 0 && *list != NULL)
    {
        ListNode *delPtr = *list;
        *list = (*list)->next;
        free(delPtr);
        delPtr = NULL;
        return;
    }
    // Case of rest of the list
    ListNode *searchPtr = *list;
    idx--;
    while ((idx--) > 0 && searchPtr->next != NULL)
    {
        searchPtr = searchPtr->next;
    }
    // At this point searchPtr should be before the node to be deleted
    if (idx > 0 || searchPtr->next == NULL) //  Quick Safety check
    {
        printf("Index Does not Exist!\n");
        return;
    }
    ListNode *delPtr = searchPtr->next;
    // If not at end of list then append remaining list
    if (delPtr->next != NULL)
    {
        searchPtr->next = delPtr->next;
    }
    else
    {
        searchPtr->next = NULL;
    }
    // de-allocate node
    free(delPtr);
    delPtr = NULL;
}

// Destructor
void deallocateList(ListNode **list)
{
    ListNode *delPtr = *list;
    // traverse till end of list , last element
    while (delPtr->next != NULL)
    {
        ListNode *next = delPtr->next;
        // De-allocate memory
        free(delPtr);
        // Increment
        delPtr = next;
    }
    *list = NULL;
    printf("List Deallocated!\n");
}
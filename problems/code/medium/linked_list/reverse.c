#include <stdio.h>
#include <stdlib.h>

// Definition of a node
struct Node
{
    int data;
    struct Node* next;
};

/*
    Traverse the list once, and for each node we reverse its next 
    pointer so it points to the previous node instead of the next one
    
    A singly linked list only points forward, so we must rebuild the 
    direction step by step.

    We must store next before reversing the pointer, otherwise we 
    lose access to the rest of the list.
    
    Trick is to not think of the list as a whole, separate it into
    two by keep track of the prev, and return prev. Since, we know
    the end of a list always points to NULL, you don't need scan the
    list to the end.

    List at start of each loop:
        curr = 1->2->3->4->NULL  prev = NULL   
        2->3->4->NULL            prev = 1->NULL
        3->4->NULL               prev = 2->1->NULL
        4->NULL                  prev = 3->2->1->NULL
        NULL                     prev = 4->3->2->1->NULL
*/
struct Node* reverseList(struct Node* head)
{
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL)
    {
        next = current->next;   // store next node
        current->next = prev;   // reverse current node's pointer
        prev = current;         // move prev forward
        current = next;         // move current forward
    }

    return prev; // new head
}

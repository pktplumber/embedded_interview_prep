
#include <stddef.h>

struct Node {
    int data;
    struct Node* next;
};

/*
    Swapping any two nodes is easy, but the trick is handling
    the edge cases:
        - What if X or Y is the head?
        - How do you handle storing and setting the X and Y's
          previous nodes?


*/
void swapNodes(struct Node** head_ref, int x, int y) {
    // If x and y are same, nothing to do
    if (x == y)
    {
        return;
    }

    struct Node *prevX = NULL;
    struct Node *currX = *head_ref;
    struct Node *prevY = NULL;
    struct Node *currY = *head_ref;

    // Search for x
    while (currX && x > 0)
    {
        prevX = currX;
        currX = currX->next;
        x--;
    }

    // Search for y
    while (currY && y > 0)
    {
        prevY = currY;
        currY = currY->next;
        y--;
    }

    // If either x or y is not present, do nothing
    if (!currX || !currY)
    {
        return;
    }

    // If x is not head of list
    if (prevX != NULL)
    {
        // X is saved in currX, so we can overwrite prevX->next
        prevX->next = currY;
    }
    else // x is head
    {
        *head_ref = currY;
    }

    // If y is not head of list
    if (prevY != NULL)
    {
        // Y is saved in currY, so we can overwrite prevY->next
        prevY->next = currX;
    }
    else // y is head
    {
        *head_ref = currX;
    }

    // Swap next pointers
    struct Node* temp = currX->next;
    currX->next = currY->next;
    currY->next = temp;
}


void swapNthNode(struct Node** head, int n)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    int count = 0;
    struct Node* curs = *head;
    while (curs != NULL)
    {
        count++;
        curs = curs->next;
    }

    if (n <= count)
    {
        swapNodes(head, n-1, count - n);
    }
}

/*
    Need to keep track of node pointers so that the next pairs are
    always pointed to correctly.

    Need:
        current - points to first node in current pair
        prev - points to last in pair after swap (which is current
            at end of each loop)
        nextPair - stores first node in next pair after swap (gets
            written to current)
        nextNode - temp stores current->next node after the swap 
*/
struct Node* swapAdjacentNodes(struct Node* head)
{
    // If list is empty or has only one node, no swap needed
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct Node* prev = NULL;
    struct Node* current = head;
    head = head->next;  // After first swap, new head will be the second node

    while (current != NULL && current->next != NULL)
    {
        struct Node* nextNode = current->next;
        struct Node* nextPair = nextNode->next;

        // Swap current and nextNode
        nextNode->next = current;
        current->next = nextPair;

        // Connect previous pair to the current swapped pair
        if (prev != NULL)
        {
            prev->next = nextNode;
        }

        // Move prev and current pointers forward
        prev = current;
        current = nextPair;
    }

    return head;
}

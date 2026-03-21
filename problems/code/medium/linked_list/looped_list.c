
#include <stdint.h>
#include <stddef.h>

struct Node
{
    struct Node* next;
    int val;
};

/*
    Idea is to have a "fast" and "slow" pointer
    a->b->c->1->2->3--|
             ^--5<-4<-|
    Iters:
        0: fast = a, slow = a
        1: fast = c, slow = b
        2: fast = 2, slow = c
        3: fast = 4, slow = 1
        4: fast = 1, slow = 2
        5: fast = 3, slow = 3
    Then break, and get count by iterating until cursor = slow
*/
int find_loop_len(struct Node* head)
{
    if (head == NULL)
    {
        return -1;
    }

    int loop_len = 0;
    struct Node* fast = head; // Increments by 2 each loop
    struct Node* slow = head; // Increments by 1 each time

    // If either is NULL, then there is no loop
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        // 
        if (fast == slow)
        {
            // Loop found
            loop_len = 1;
            struct Node* tmp = slow->next;
            while (tmp != NULL)
            {
                loop_len++;
                tmp = tmp->next;
            }
            break;
        }
    }
    return loop_len;
}

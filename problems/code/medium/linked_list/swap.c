#include <stddef.h>


struct Node
{
    int value;
    struct Node* next;
};

void swap_nodes_impl1(
    struct Node** head,
    struct Node* a,
    struct Node* a_prev,
    struct Node* b,
    struct Node* b_prev
)
{
    // Invalid inputs include:
    // - Head being NULL
    // - A or B being NULL (nothing to swap)
    // - A and B being the same (also implies nothing to swap)
    // - a_prev and b_prev being NULL (implies both a and b are the head)
    if (*head == NULL ||
        head == NULL ||
        a == NULL ||
        b == NULL ||
        a == b ||
        (a_prev == NULL && b_prev == NULL)
    )
    {
        return;
    }

    // Handle adjacent nodes
    if (a->next == b)
    {
        // Is a the head?
        if (a_prev != NULL)
        {
            // No, a_prev next is simple b
            a_prev->next = b;
        }
        else
        {
            // Yes, new head is a
            *head = b;
        }

        a->next = b->next;
        b->next = a;
    }
    else if (b->next == a)
    {
        // Is b the head?
        if (b_prev != NULL)
        {
            // No, b_prev next is simply a
            b_prev->next = a;
        }
        else
        {
            // Yes, new head is a
            *head = a;
        }

        b->next = a->next;
        a->next = b;
    }
    else
    {
        if (a_prev != NULL)
        {
            a_prev->next = b;
        }
        else
        {
            *head = b;
        }

        if (b_prev != NULL)
        {
            b_prev->next = a;
        }
        else
        {
            *head = a;
        }

        struct Node* tmp = b->next;
        b->next = a->next;
        a->next = tmp;
    }
}

void swap_nodes(struct Node** head, int i, int j)
{
    if (i == j)
    {
        return;
    }

    struct Node** a = head;
    struct Node** b = head;

    for (int k = 0; k < i; k++)
    {
        if (*a == NULL)
        {
            return;
        }
        a = &(*a)->next;
    }

    for (int k = 0; k < j; k++)
    {
        if (*b == NULL)
        {
            return;
        }
        b = &(*b)->next;
    }

    struct Node* nodeA = *a;
    struct Node* nodeB = *b;

    if (nodeA == NULL || nodeB == NULL)
    {
        return;
    }

    struct Node* tmp = nodeB->next;
    nodeB->next = nodeA->next;
    nodeA->next = tmp;

    *a = nodeB;
    *b = nodeA;
}

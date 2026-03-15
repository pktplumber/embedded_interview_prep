
#include <stdint.h>
#include <memory.h>
#include <stdbool.h>

struct ListNode_t
{
    struct ListNode_t *next;
    uint32_t Value;
};

typedef struct
{
    struct ListNode_t* Head;
    struct ListNode_t* Tail;
}List_t;

void append_node(List_t *list, struct ListNode_t *node)
{
    if (list->Head)
    {
        list->Tail->next = node;
        list->Tail = node;
    }
    else
    {
        // initial append
        list->Head = node;
        list->Tail = node;
    }
}

uint32_t get_count(List_t* list)
{
    struct ListNode_t* node = list->Head;
    uint32_t count = 0;
    if (node)
    {
        while (node != list->Tail)
        {
            count++;
            node = node->next;
        }
    }
    return count;
}

struct ListNode_t* pop_front(List_t* list)
{
    struct ListNode_t* ret = NULL;
    if (list && list->Head)
    {
        ret = list->Head;
        list->Head = list->Head->next;
    }
    return ret;
}

struct ListNode_t* get_node(List_t* list, uint32_t n)
{
    struct ListNode_t* cursor = list->Head;
    while (n)
    {
        if (cursor == NULL)
        {
            return NULL;
        }
        cursor = cursor->next;
        n--;
    }
    return cursor;
}

bool insert_node(List_t* list, struct ListNode_t* node, size_t idx)
{
    bool result = false;
    if (list && node && list->Head)
    {
        if (idx == 0)
        {
            struct ListNode_t* tmp = list->Head;
            list->Head = node;
            list->Head->next = tmp;
            result = true;
        }
        else
        {
            struct ListNode_t* tmp = get_node(list, idx-1);
            if (tmp != NULL)
            {
                struct ListNode_t* sect = tmp->next;
                tmp->next = node;
                node->next = sect;
                result = true;
            }
        }
    }
    return result;
}

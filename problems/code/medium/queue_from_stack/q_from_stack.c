
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define STACK_SZ    128

uint8_t data[STACK_SZ];

typedef struct
{
    size_t elems;
    uint8_t data[STACK_SZ]
}stack_t;

typedef struct
{
    stack_t in;
    stack_t out;
}queue_t;


void init_stack(stack_t* stack)
{
    stack->elems = 0;
}

bool stack_push(stack_t* stack, uint8_t item)
{
    bool ret = false;
    if (stack != NULL)
    {
        if (stack->elems < STACK_SZ)
        {
            stack->data[stack->elems] = item;
            stack->elems++;
            ret = true;
        }
    }
    return ret;
}

bool stack_pop(stack_t* stack, uint8_t* item)
{
    if (stack != NULL && item != NULL)
    {
        if (stack->elems > 0)
        {
            *item = stack->data[stack->elems];
            stack->elems--;
        }
    }
}

bool stack_is_empty(stack_t* stack)
{
    if (stack != NULL)
    {
        return stack->elems == 0;
    }
    return false;
}

bool stack_is_full(stack_t* stack)
{
    if (stack != NULL)
    {
        return stack->elems == STACK_SZ;
    }
    return false;
}

void queue_init(queue_t* queue)
{
    init_stack(&queue->in);
    init_stack(&queue->out);
}

bool queue_enqueue(queue_t* queue, const uint8_t item)
{
    stack_push(&queue->in, item);
}

static bool queue_transfer(stack_t* from, stack_t* to)
{
    uint8_t tmp;
    while (!stack_is_empty(from))
    {
        if (!stack_pop(from, &tmp))
        {
            return false;
        }
        if (!stack_push(to, tmp))
        {
            return false;
        }
    }

    return true;
}

static bool queue_dequeue(queue_t* queue, uint8_t* out)
{
    if (stack_is_empty(&queue->out))
    {
        if (stack_is_empty(&queue->in))
        {
            return false;
        }

        bool stat = queue_transfer(&queue->in, &queue->out);
        if (!stat)
        {
            return stat;
        }
    }
    return stack_pop(&queue->out, out);
}

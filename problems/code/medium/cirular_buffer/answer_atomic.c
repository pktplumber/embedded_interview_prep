
#include <stdint.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct
{
    uint8_t* buffer;
    size_t capacity;
    atomic_size_t head;
    atomic_size_t tail;
}circ_buf_t;


bool circ_buf_init(circ_buf_t* handle, uint8_t* buffer, const size_t size);
bool circ_buf_push(circ_buf_t* handle, const uint8_t value);
bool circ_buf_pop(circ_buf_t* handle, uint8_t* value);
bool circ_buf_is_empty(const circ_buf_t* handle);
bool circ_buf_is_full(const circ_buf_t* handle);
size_t circ_buf_size(const circ_buf_t* handle);
void circ_buf_clear(circ_buf_t* handle);

bool circ_buf_init(circ_buf_t* handle, uint8_t* buffer, const size_t size)
{
    if (handle == NULL || buffer == NULL || size < 2)
    {
        return false;
    }

    handle->buffer = buffer;
    handle->capacity = size;
    atomic_store(&handle->head, 0);
    atomic_store(&handle->tail, 0);

    return true;
}

bool circ_buf_push(circ_buf_t* handle, const uint8_t value)
{
    if (handle == NULL)
    {
        return false;
    }

    size_t head = atomic_load(&handle->head);
    size_t tail = atomic_load(&handle->tail);
}

bool circ_buf_pop(circ_buf_t* handle, uint8_t* value)
{
    if (handle == NULL)
    {
        return false;
    }

}

bool circ_buf_is_empty(const circ_buf_t* handle)
{
    if (handle == NULL)
    {
        return false;
    }

    return 
}

bool circ_buf_is_full(const circ_buf_t* handle)
{
    if (handle == NULL)
    {
        return false;
    }

}

size_t circ_buf_size(const circ_buf_t* handle)
{
    if (handle == NULL)
    {
        return false;
    }

}

void circ_buf_clear(circ_buf_t* handle)
{
    if (handle == NULL)
    {
        return false;
    }

}

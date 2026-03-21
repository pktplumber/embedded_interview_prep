
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    uint8_t* buffer;
    size_t capacity;
    size_t head;
    size_t tail;
}circ_buf_t;


bool circ_buf_init(circ_buf_t* handle, uint8_t* buffer, const size_t size);
bool circ_buf_push(circ_buf_t* handle, const uint8_t value);
bool circ_buf_pop(circ_buf_t* handle, uint8_t* value);
bool circ_buf_is_empty(const circ_buf_t* handle);
bool circ_buf_is_full(const circ_buf_t* handle);


bool circ_buf_init(circ_buf_t* handle, uint8_t* buffer, const size_t size)
{
    bool result = false;
    if (handle != NULL && buffer != NULL && size > 0)
    {
        handle->buffer = buffer;
        handle->capacity = size;
        handle->head = 0;
        handle->tail = 0;
        result = true;
    }
    return result;
}

bool circ_buf_is_empty(const circ_buf_t* handle)
{
    bool result = true;
    if (handle != NULL)
    {
        result = handle->head == handle->tail;
    }
    return result;
}

bool circ_buf_is_full(const circ_buf_t* handle)
{
    bool result = false;
    if (handle != NULL)
    {
        result = handle->head == (handle->tail + 1) % handle->capacity;
    }
    return result;
}

bool circ_buf_push(circ_buf_t* handle, const uint8_t value)
{
    bool result = false;
    if (handle != NULL && !is_full(handle))
    {
        handle->buffer[handle->tail] = value;
        handle->tail = (handle->tail + 1) % handle->capacity;
    }
    return result;
}

bool circ_buf_pop(circ_buf_t* handle, uint8_t* value)
{
    bool result = false;
    if (handle != NULL && value != NULL && !is_empty(handle))
    {
        *value = handle->buffer[handle->head];
        handle->head = (handle->head + 1) % handle->capacity;
    }
    return result;
}

size_t circ_buf_size(const circ_buf_t* handle)
{
    size_t result = 0;
    if (handle != NULL)
    {
        if (handle->tail >= handle->head)
        {
            result = handle->tail - handle->head;
        }
        else
        {
            result = handle->capacity - (handle->head - handle->tail);
        }
    }
    return result;
}

void circ_buf_clear(circ_buf_t* handle)
{
    if (handle != NULL)
    {
        handle->head = 0;
        handle->tail = 0;
    }
}


// Performance tip - If capacity is power of two, you can replace modulo with:
//   (index + 1) & (capacity - 1);

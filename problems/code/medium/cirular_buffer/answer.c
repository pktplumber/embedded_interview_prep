
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    uint8_t* buffer;
    size_t capacity;
    uint8_t head;
    uint8_t tail;
}circ_buf_t;


bool init(circ_buf_t* handle, uint8_t* buffer, const size_t size);
bool push(circ_buf_t* handle, const uint8_t value);
bool pop(circ_buf_t* handle, uint8_t* value);
bool is_empty(circ_buf_t* handle);
bool is_full(circ_buf_t* handle);


bool init(circ_buf_t* handle, uint8_t* buffer, const size_t size)
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

bool push(circ_buf_t* handle, const uint8_t value)
{
    bool result = false;
    if (handle != NULL)
    {
        if (!is_full(handle))
        {
            handle->buffer[handle->tail] = value;
            handle->tail += 1;
            handle->tail %= handle->capacity;
            result = true;
        }
    }
    return result;
}

bool pop(circ_buf_t* handle, uint8_t* value)
{
    bool result = false;
    if (handle != NULL && value != NULL)
    {
        if (!is_empty(handle))
        {
            result = true;
        }
    }
    return result;
}

bool is_empty(circ_buf_t* handle)
{
    bool result = true;
    if (handle != NULL)
    {
        if (handle->head != handle->tail)
        {
            result = false;
        }
    }
    return result;
}

bool is_full(circ_buf_t* handle)
{
    bool result = false;
    if (handle != NULL)
    {
        if (handle->head > 0)
        {
            
        }
    }
}


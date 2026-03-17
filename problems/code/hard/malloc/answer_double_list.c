
#include <stdint.h>
#include <memory.h>

#define CUSTOM_MALLOC_MEM_SZ    ((1 << 17) - 1)


struct block_header_t
{
    struct block_header_t *prev;
    struct block_header_t *next;
    size_t block_sz;  // Bytes allocated for this block
    int free;
}block_header_t;

static block_header_t *free_list;
static block_header_t *in_use_head;

static uint8_t heap[CUSTOM_MALLOC_MEM_SZ];


void init(void)
{
    free_list = (block_header_t*)heap;
    free_list->prev = NULL;
    free_list->next = NULL;
    free_list->block_sz = sizeof(heap) - sizeof(block_header_t);
}

static block_header_t* find_free_block(size_t sz)
{
    block_header_t* curs = free_list;

    while (curs != NULL)
    {
        if (curs->block_sz >= sz && curs->free)
        {
            return curs;
        }
        curs = curs->next;
    }
    return NULL;
}

static void split_block(block_header_t* block, size_t size)
{
    if (block->size <= size + sizeof(block_header_t))
    {
        return;
    }

    block_header_t* new_block = (block_header_t*)
        ((uint8_t*)block + sizeof(block_header_t) + size);

    new_block->size = block->size - size - sizeof(block_header_t);
    new_block->free = 1;

    new_block->next = block->next;
    new_block->prev = block;

    if (new_block->next)
    {
        new_block->next->prev = new_block;
    }

    block->size = size;
    block->next = new_block;
}


void* my_malloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    block_header_t* block = find_free_block(size);
    if (!block)
    {
        return NULL;
    }

    split_block(block, size);

    block->free = 0;

    // Remove from free list if needed
    if (block == free_list)
    {
        free_list = block->next;
    }

    if (block->prev)
    {
        block->prev->next = block->next;
    }

    if (block->next)
    {
        block->next->prev = block->prev;
    }

    block->next = block->prev = NULL;

    return (void*)(block + 1);
}

static void coalesce(block_header_t* block)
{
    // Merge with next
    if (block->next && block->next->free)
    {
        block->size += sizeof(block_header_t) + block->next->size;
        block->next = block->next->next;

        if (block->next)
        {
            block->next->prev = block;
        }
    }

    // Merge with prev
    if (block->prev && block->prev->free)
    {
        block->prev->size += sizeof(block_header_t) + block->size;
        block->prev->next = block->next;

        if (block->next)
        {
            block->next->prev = block->prev;
        }

        block = block->prev;
    }
}

void my_free(void* ptr)
{
    if (!ptr)
    {
        return;
    }

    block_header_t* block = (block_header_t*)ptr - 1;

    block->free = 1;

    // Insert at front of free list
    block->next = free_list;
    block->prev = NULL;

    if (free_list)
    {
        free_list->prev = block;
    }

    free_list = block;

    coalesce(block);
}

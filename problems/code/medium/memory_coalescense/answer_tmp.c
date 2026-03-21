#include <stdint.h>

#define MAX_FREE_BLOCKS 32

typedef struct FreeBlock
{
    uint32_t address;   // start address of free block
    uint32_t size;      // size in bytes
    struct FreeBlock* next;
} FreeBlock;

FreeBlock block_pool[MAX_FREE_BLOCKS];

FreeBlock* allocate_node(void);

void free_block(FreeBlock** head, uint32_t addr, uint32_t size)
{
    FreeBlock* prev = NULL;
    FreeBlock* curs = *head;

    while (curs != NULL && curs->addr < addr)
    {
        prev = curs;
        curs = curs->next;
    }

    
}
#include <stdint.h>
#include <stddef.h>

#define MAX_FREE_BLOCKS 32

typedef struct FreeBlock
{
    uint32_t address;   // start address of free block
    uint32_t size;      // size in bytes
    struct FreeBlock* next;
} FreeBlock;

FreeBlock* allocate_node(void);

void free_block(FreeBlock** head, uint32_t addr, uint32_t size)
{
    if (head == NULL || size == 0)
        return;

    FreeBlock* new_block = allocate_node();
    if (new_block == NULL)
        return; // no free nodes available

    new_block->address = addr;
    new_block->size = size;
    new_block->next = NULL;

    // Special case: insert at the head or empty list
    if (*head == NULL || addr < (*head)->address)
    {
        new_block->next = *head;
        *head = new_block;
    }
    else
    {
        // Find insertion point
        FreeBlock* prev = *head;
        FreeBlock* curr = (*head)->next;
        while (curr != NULL && curr->address < addr)
        {
            prev = curr;
            curr = curr->next;
        }
        new_block->next = curr;
        prev->next = new_block;
    }

    // Coalesce contiguous blocks
    FreeBlock* curr = *head;
    while (curr != NULL && curr->next != NULL)
    {
        if (curr->address + curr->size == curr->next->address)
        {
            // Merge curr and curr->next
            FreeBlock* tmp = curr->next;
            curr->size += tmp->size;
            curr->next = tmp->next;

            // Optionally return tmp to pool here if needed
            // tmp->next = NULL; 
        }
        else
        {
            curr = curr->next;
        }
    }
}

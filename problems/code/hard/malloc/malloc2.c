#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define MEMORY_SIZE (128 * 1024)  // 128 KB

typedef struct Block {
    size_t size;         // Size of the block excluding the header
    int free;            // 1 if free, 0 if allocated
    struct Block *next;  // Next block in the memory list
} Block;

static uint8_t memory[MEMORY_SIZE];
static Block *freeList = NULL;

// Align to 8 bytes for simplicity
#define ALIGN8(x) (((x) + 7) & ~7)
#define BLOCK_SIZE sizeof(Block)

// Initialize the memory pool
void memory_init() {
    freeList = (Block *)memory;
    freeList->size = MEMORY_SIZE - BLOCK_SIZE;
    freeList->free = 1;
    freeList->next = NULL;
}

// Split a block if it’s too large
void split_block(Block *block, size_t size) {
    if (block->size >= size + BLOCK_SIZE + 8) { // Enough space for a new block
        Block *newBlock = (Block *)((uint8_t *)block + BLOCK_SIZE + size);
        newBlock->size = block->size - size - BLOCK_SIZE;
        newBlock->free = 1;
        newBlock->next = block->next;
        block->size = size;
        block->next = newBlock;
    }
}

// Simple malloc
void *my_malloc(size_t size) {
    size = ALIGN8(size);
    Block *current = freeList;
    
    while (current) {
        if (current->free && current->size >= size) {
            split_block(current, size);
            current->free = 0;
            return (void *)((uint8_t *)current + BLOCK_SIZE);
        }
        current = current->next;
    }
    return NULL; // Out of memory
}

// Coalesce adjacent free blocks
void coalesce()
{
    Block *current = freeList;
    while (current && current->next)
    {
        if (current->free && current->next->free)
        {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        }
        else
        {
            current = current->next;
        }
    }
}

// Free memory
void my_free(void *ptr) {
    if (!ptr) return;
    Block *block = (Block *)((uint8_t *)ptr - BLOCK_SIZE);
    block->free = 1;
    coalesce();
}

// Debug helper
void print_memory() {
    Block *current = freeList;
    printf("Memory Blocks:\n");
    while (current) {
        printf("Block at %p, size: %zu, free: %d, next: %p\n",
               current, current->size, current->free, current->next);
        current = current->next;
    }
}

int main() {
    memory_init();

    void *a = my_malloc(1024);
    void *b = my_malloc(2048);
    void *c = my_malloc(512);

    print_memory();

    my_free(b);
    my_free(a);

    print_memory();

    void *d = my_malloc(3000); // Should reuse freed space
    print_memory();

    return 0;
}
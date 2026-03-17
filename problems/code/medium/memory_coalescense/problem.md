# Free Block Coalescing in a Memory Pool

You are implementing a simple fixed memory allocator for an embedded system that does not have malloc(). Free memory blocks are stored in a singly linked list sorted by address and each node represents a free memory block.

You are given the following code:
```
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
```

## Task
Implement a function: `void free_block(FreeBlock** head, uint32_t addr, uint32_t size);` that will:
1. Insert the freed block into the linked list in sorted order by address.
2. Merge adjacent blocks if they are contiguous in memory.

Two blocks are contiguous if `block1.address + block1.size == block2.address`.

### Constraints:
1. No dynamic memory allocation allowed
2. Function must run in O(n)
3. The list may be empty
4. Blocks may need to merge with:
  - previous
  - next
  - both
5. The function may be called from interrupt context

### Example

Initial free list:

```
0x1000 size=128 -> 0x1200 size=256
```

Freeing:

```
addr = 0x1080
size = 128
```

After insertion:
```
0x1000 size=128
0x1080 size=128
0x1200 size=256
```

Then coalescing occurs:

```
0x1000 size=256
0x1200 size=256
```

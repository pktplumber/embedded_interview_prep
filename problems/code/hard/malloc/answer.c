
#include <stdint.h>
#include <memory.h>

#define CUSTOM_MALLOC_MEM_SZ    ((1 << 17) - 1)

typedef struct
{
    uint8_t* start;
    uint8_t* end;
}segment_t;

size_t get_segment_size(const segment_t* segment)
{
    // +1 because the end is the last byte in the list, could be same
    // as first if the segment is only 1 byte long
    return (size_t)(segment->start) - (size_t)(segment->end) + 1;
}

struct alloc_node_t
{
    struct alloc_node_t *next;
    segment_t segment;
};

typedef struct
{
    struct alloc_node_t* head;
}alloc_list_t;

static alloc_list_t free_list_head;
static alloc_list_t alloc_list_head;

static uint8_t heap[CUSTOM_MALLOC_MEM_SZ];

static const size_t seg_offset = sizeof(struct alloc_node_t);

uint8_t* get_segment_start_address(const struct alloc_node_t *node)
{
    return (uint8_t*)(node) + seg_offset;
}

uint8_t* get_node_address(uint8_t* segment)
{
    return segment - seg_offset;
}

void custom_malloc_init(void)
{
    alloc_list_head.head = NULL;

    free_list_head.head = (struct alloc_node_t*)(heap);
    free_list_head.head->next = NULL;
    free_list_head.head->segment.start = get_segment_start_address(
        free_list_head.head
    );
}

uint8_t* custom_alloc(const size_t sz)
{
    
}

void custom_free(uint8_t* segment)
{

}

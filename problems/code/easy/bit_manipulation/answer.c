// Implement functions to toggle, set, and clear a bit.

#include <stdint.h>
#include <stdbool.h>

uint32_t toggle_bit(uint32_t num, uint8_t position)
{
    return num ^ (1 << position);
}

uint32_t set_bit(uint32_t num, uint8_t position)
{
    return num | (1 << position);
}

uint32_t clear_bit(uint32_t num, uint8_t position)
{
    return num & ~(1 << position);
}

bool is_bit_set(uint32_t num, uint8_t position)
{
    return (num >> position) & 1 == 1;
}

uint32_t set_multiple_bits(uint32_t num, uint32_t mask)
{
    return num |= mask;
}

uint32_t clear_multiple_bits(uint32_t num, uint32_t mask)
{
    return num & ~mask;
}

uint32_t toggle_multiple_bits(uint32_t num, uint32_t mask)
{
    return num ^ mask;
}

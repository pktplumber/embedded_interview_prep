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

#define REG_ADDR   (*(volatile uint32_t*)0x40000000)

#define MODE_MASK  (0xFFu << 8)
#define MODE_SHIFT 8

void set_mode(uint8_t mode)
{
    uint32_t reg = REG_ADDR;                // Read
    reg &= ~MODE_MASK;                      // Clear MODE bits
    reg |= ((uint32_t)mode << MODE_SHIFT);  // Set new MODE
    REG_ADDR = reg;                         // Write back
}


uint32_t reverse_bits(uint32_t num)
{
    uint32_t ret = ((num >> 16) & 0xFFFF) | ((num << 16) & 0xFFFF000);
    ret = ((ret & 0xFF00FF00) >> 8) | ((ret & 0x00FF00FF) << 8);
    ret = ((ret & 0xF0F0F0F0) >> 4) | ((ret & 0x0F0F0F0F) << 4);
    ret = ((ret & 0xCCCCCCCC) >> 2) | ((ret & 0x33333333) << 2);
    return ((ret & 0xAAAAAAAA) >> 2) | ((ret & 0x55555555) << 1);
}

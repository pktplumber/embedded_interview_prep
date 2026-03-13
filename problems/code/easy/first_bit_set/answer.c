
#include <stdint.h>

int first_set_bit(uint32_t x)
{
    if (!x)
    {
        return -1;
    }

    int idx = 0;
    while (!((x = x >> 1) & 1))
    {
        idx++;
    }
    return idx;
}

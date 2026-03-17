
#include <stddef.h>
#include <stdint.h>

void reverse1(uint32_t* arr, size_t sz)
{
    int i = 0;
    while (i < sz/2)
    {
        uint32_t tmp = arr[i];
        arr[i] = arr[sz-1-i];
        arr[sz-1] = tmp;
        i++;
    }
}

uint32_t reverse_bits_u32(uint32_t num)
{
    num = (num >> 16) | (num << 16);
    num = ((num & 0xFF00FF00) >> 8) | ((num & 0x00FF00FF) << 8);
    num = ((num & 0xF0F0F0F0) >> 4) | ((num & 0x0F0F0F0F) << 4);
    num = ((num & 0xCCCCCCCC) >> 2) | ((num & 0x33333333) << 2);
    num = ((num & 0xAAAAAAAA) >> 1) | ((num & 0x55555555) << 1);
    return num;
}

void reverse2(uint32_t* arr, size_t sz)
{
    size_t i = 0;
    while (i < sz/2)
    {
        uint32_t tmp = reverse_bits_u32(arr[i]);
        arr[i] = reverse_bits_u32(arr[sz-1-i]);
        arr[sz-1-i] = tmp;
        i++;
    }

    // Handle middle if odd length
    if ((sz & 1) == 1)
    {
        arr[i] = reverse_bits_u32(arr[i]);
    }
}

uint32_t find_duplicate(uint32_t* arr, size_t sz)
{
    uint32_t xor_all = 1;
    for (uint32_t i = 2; i <= sz; i++)
    {
        xor_all ^= i;
    }

    uint32_t xor_arr = arr[0];
    for (int i = 1; i < sz; i++)
    {
        xor_arr ^= arr[i];
    }

    return xor_all ^ xor_arr;
}

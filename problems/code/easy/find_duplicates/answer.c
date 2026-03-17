#include <stdbool.h>


// The function should not loop through the string twice (O(N^2))
// complexity. Since the maximum character value is 256, we can create
// an array that tracks the number of times a char appears in the string.
// Then return true if any of the counts is greater than 1. (O(N)) time
// complexity
bool has_duplicates_str(const char* s)
{
    int freq[256] = {0};

    char* c = s;
    while (*c)
    {
        freq[(int)(*c)] += 1;
        c++;
    }

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 1)
        {
            return true;
        }
    }

    return false;
}

// Any even better implementation is store the occurrance of the char as a 
// bit in a single int variable, but this only works for inputs of limited
// range (lower case strings), This involves using the integer as a bit
// vector and setting the bit location if a character occurs
bool has_dups_lower_case_str(const char* s)
{
    int bit_vect = 0;
    char *c = s;
    while (*c)
    {
        int val = (*c) - 'a';
        if (bit_vect & (1 << val) > 0)
        {
            return false;
        }
        bit_vect |= (1 << val);
    }
} 

// If the input is an array of uint16_ts or uint32_ts, using a frequency
// table would not be memory efficient. If you can modify the array,
// one solution would be to sort the array then check if sequential
// elements are equal (O(n*log(n)))

#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int find_dups_array(int *arr, const size_t arr_sz)
{
    qsort(arr, arr_sz, sizeof(int), cmp);

    for (int i = 1; i < arr_sz; i++)
    {
        if (arr[i] == arr[i-1])
        {
            return true;
        }
    }

    return false;
}


// If you cannot sort/modify the array in place, you would need to
// implement a hash table. O(n) time and space complexity

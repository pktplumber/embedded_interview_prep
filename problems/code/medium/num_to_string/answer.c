
#include <stdio.h>

void print_float(float num)
{
    char flt_s[32] = {'\0'};
    int s_idx = 0;
    int whole_num = (int)num;
    int dec = (int)((num - whole_num) * 100);
    printf("whole_num = %d, dec = %d\n", whole_num, dec);
    whole_num = (num >=0) ? (int)num : (int)num*-1;
    dec = (dec >= -1) ? dec : dec * -1;
    printf("whole_num = %d, dec = %d\n", whole_num, dec);
    
    while (dec)
    {
        flt_s[s_idx++] = (char)((dec%10) + '0');
        dec /= 10;
    }
    
    flt_s[s_idx++] = '.';
    
    while (whole_num)
    {
        flt_s[s_idx++] = (char)((whole_num%10) + '0');
        whole_num /= 10;
    }
    
    if (num < 0)
    {
        flt_s[s_idx++] = '-';
    }
    
    // reverse
    for (int i = 0; i < s_idx/2; i++)
    {
        char tmp = flt_s[i];
        flt_s[i] = flt_s[s_idx-i-1];
        flt_s[s_idx-i-1] = tmp;
    }
    
    printf("%s\n", flt_s);
}

int main()
{
    printf("%d\n", ((int)(0.21*100) + '0') % 10);
    print_float(1234.23);

    return 0;
}
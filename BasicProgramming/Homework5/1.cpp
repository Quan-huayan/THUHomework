#include <stdio.h>
#include <string.h>

int inline todigit(char c)
{
    return (c >> 6) * 9 + c & 0x0F;
}

int main()
{
    char c[10],*p=c;
    int d=0;
    scanf("%s", c);
    while(*p) d=d*15+todigit(*(p++));
    printf("%c%c%c%c",d/343 + '0', d/49 % 7 + '0', d/7 % 7 +'0', d % 7 + '0');
    return 0;
}
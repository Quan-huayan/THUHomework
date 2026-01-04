#include <stdio.h>

void outputInverse(int num)
{
    while(num>0) putchar('0'+num%10),num/=10;
}

int main()
{
    int d;
    scanf("%d", &d);
    outputInverse(d);
    return 0;
}
#include <stdio.h>

int calArray(int n)
{
    if(n==0) return 1;
    if(n==1) return 3;
    if(n>1) return 4*calArray(n-1)-calArray(n-2);
    return 0;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%d",calArray(n));
    return 0;
}
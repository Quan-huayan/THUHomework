#include <stdio.h>

int step_methods(int n)
{
    if(n<=1) return 1;
    if(n==2) return 2;
    if(n==3) return 4;
    return step_methods(n-1)+step_methods(n-2)+step_methods(n-3);
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%d",step_methods(n));
    return 0;
}
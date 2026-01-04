#include <stdio.h>

int Jesphus(int m,int n)
{
    if(n<=1) return 1;
    return (Jesphus(m,n-1)+m-1)%n+1;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    printf("%d",Jesphus(m,n));
    return 0;
}
#include <stdio.h>

//快速幂
long long powmod(long long a, long long d, long long mod)
{
    long long ret = 1;
    while (d>0)
    {
        if (d & 1) ret = (ret*a)%mod;
        a = (a*a)%mod;
        d >>= 1;
    }
    return ret; 
}

int main()
{
    int x,n;
    scanf("%d %d",&x,&n);
    printf("%d",powmod(x,n,10007));
    return 0;
}
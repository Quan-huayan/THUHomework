#include <stdio.h>

int main()
{
    long long min, max, sum=0;
    scanf("%lld %lld", &min, &max);
    for(long long i=min;i<=max;i++) sum += i*i;
    printf("%lld", sum);
    return 0;
}
#include <stdio.h>

int primes[30]={2,3,5,7,11,
13,17,19,23,29,
31,37,41,43,47,
53,59,61,67,71,
73,79,81,83,89,
97,101,103,107,109};

bool isPrime(int num)
{
    for(int i=0;i<30;i++)
    {
        if(primes[i] * primes[i] > num) break;
        if(num % primes[i] == 0) return false;
    }
    return true;
}

int primeNum(int* array, int num)
{
    int ret = 0;
    for(int i=0;i<num;i++)
        if(isPrime(array[i])) ret++;
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *p = new int [n];
    for(int i=0;i<n;i++) scanf("%d",p+i);
    printf("%d",primeNum(p, n));
    return 0;
}
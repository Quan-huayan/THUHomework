#include <stdio.h>

unsigned int calAlphaMul(unsigned int n)
{
    if(n<10) return n;
    unsigned int prefixNow = n, mul = 1, digitNow;
    do {
        if(digitNow = prefixNow % 10) mul*=digitNow;
    }while(prefixNow /= 10);
    return calAlphaMul(mul);
}

int main()
{
    unsigned int uInput;
    scanf("%u",&uInput);
    printf("%u",calAlphaMul(uInput));
    return 0;
}
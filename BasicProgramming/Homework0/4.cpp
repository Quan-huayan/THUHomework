#include <stdio.h>

int main()
{
    int c_tempature;
    scanf("%d",&c_tempature);
    printf("%.2f", 1.8f * (float)c_tempature + 32.0);
    return 0;
}
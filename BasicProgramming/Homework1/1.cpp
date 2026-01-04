#include <stdio.h>

int main()
{
    double dSale, dRate;
    scanf("%lf %lf",&dSale,&dRate);
    double dTax = dSale * dRate;
    printf("%.2lf",dTax);
    return 0;
}
#include <stdio.h>

int inline sgn(int x)
{
    return x % 2 ? 1 : -1;
}//计算第x项的符号

int main()
{
    int n, i;
    double x,xn,xNow;
    scanf("%lf %d",&x,&n);
    xn=sgn(n)*x/(double)n;
    xNow = xn, i = n;
    while(--i>0) xNow = x * (xNow + sgn(i) / (double)i);
    printf("%.6lf", xNow);
    return 0;
}
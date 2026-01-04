#include <stdio.h>
#include <math.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

#define MIN(a,b) (((a)<(b))?(a):(b))


int main(){
    double a, b, c;
    scanf("%lf %lf %lf",&a,&b,&c);

    double p = (a + b + c) / 2.0;
    double S2 = p * (p - a) * (p - b) * (p - c);
    double max = MAX(MAX(a,b),c);
    if(S2 > 0) printf("%.6lf",2*sqrt(S2)/max);
    else printf("NO");

    return 0;
}
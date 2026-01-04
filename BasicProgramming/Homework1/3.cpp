#include <stdio.h>

int main()
{
    int a[3], dMax;
    scanf("%d %d %d",a,a+1,a+2);
    dMax = a[0];
    for(int i=1;i<3;i++) if(a[i]>dMax) dMax=a[i];
    printf("%d",dMax);
    return 0;
}
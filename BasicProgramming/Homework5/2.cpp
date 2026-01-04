#include <stdio.h>

int main()
{
    long n, nInput = 0, nNow, numNow=0, nMode=0, numMode=0;
    scanf("%ld",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%ld",&nInput);
        if(i==0) nNow = nInput;
        if(nInput>nNow)//nNow结算
        {
            if(numNow>numMode) nMode = nNow, numMode=numNow;//个数更多，成为新的众数
            nNow = nInput, numNow = 1;//否则不管；但无论如何nNow,numNow更新
        }
        else if(i==n-1)//结束结算
        {
            numNow++;
            if(numNow>numMode) nMode = nNow, numMode=numNow;//个数更多，成为新的众数
        }
        else numNow++;//统计nNow的个数
    }
    printf("%d",nMode);
    return 0;
}
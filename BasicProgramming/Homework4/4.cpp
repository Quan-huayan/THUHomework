#include <stdio.h>

#define N 101


int main()
{
    int n,count[N];
    for(int i=0;i<N;i++) count[i]=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int nowInput;
        scanf("%d",&nowInput);
        count[nowInput]++;
    }
    //sort
    for(int i=0;i<N-1;i++)
        for(int j=N-1;j>i;j--)
            if(count[j]<count[j-1])
            {
                int temp = count[j];
                count[j] = count[j-1];
                count[j-1] = temp;
            }
    int maxNum = count[N-1],numMaxFrequence = 0;
    for(int j=N-1;j>=0;j--)
    {
        if(count[j]<maxNum) break;
        numMaxFrequence+=maxNum;
    }
    printf("%d",numMaxFrequence);
    return 0;
}
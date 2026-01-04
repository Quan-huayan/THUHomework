#include <stdio.h>

int main()
{
    int n,num[1000];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&num[i]);
    for(int i=0;i<n-1;i++)
        for(int j=n-1;j>i;j--)
            if(num[j]<num[j-1])
            {
                int temp=num[j];
                num[j]=num[j-1];
                num[j-1]=temp;
            }
    for(int i=0;i<n;i++) printf("%d ",num[i]);
    return 0;
}
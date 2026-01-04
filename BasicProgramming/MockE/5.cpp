#include <stdio.h>

int getMaxSum(int* array, int num, int* buf)
{
    int *dp = buf, ret;

    // dp[i] 表示以i结尾的递增子序列的最大和。
    for(int i=0;i<num;i++)
        if(i==0) dp[0] = array[0];
        else //不是，则从元素比array[i]小的元素中选取
        {
            int max = 0;//初值为0是可以的，因为可以只选取这一个元素
            for(int j=0;j<i;j++)
                if(array[j]<array[i] && dp[j] > max)
                    max = dp[j];
            dp[i] = array[i] + max;
        }
    
    ret = dp[0];
    for(int i=1;i<num;i++)
        if(dp[i]>ret) ret = dp[i];

    return ret;
}

int main()
{
    int inputLength, inputs[3000] = { 0 }, buffer[3000] = { 0 };
    scanf("%d",&inputLength);
    for(int i=0;i<inputLength;i++) scanf("%d", inputs+i);
    int output = getMaxSum(inputs, inputLength, buffer);
    printf("%d", output);
    return 0;
}
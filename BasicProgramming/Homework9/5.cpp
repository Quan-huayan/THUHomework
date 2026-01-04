#include <stdio.h>

//动态规划：返回从sequence开始的最长递增子序列长度
int getLengthOfMaxMonotoneIncreasingSequence(int* sequence,int num)
{
    int *dp = new int[num];

    for(int i=0;i<num;i++) dp[i] = 1;
    for(int i=1;i<num;i++)//计算dp[i]:以第i个元素结尾的最大递增子序列长度
        for(int j=0;j<i;j++)
            if(sequence[j]<sequence[i])
                dp[i] = dp[i] < dp[j] + 1 ? dp[j] + 1 : dp[i];

    int ret = dp[0];
    for(int i=0;i<num;i++) ret = ret < dp[i] ? dp[i] : ret;
    delete[] dp;
    return ret;
}

int main()
{
    int sequence[101],i;
    for(i=0;i<101;i++)
        if(EOF==scanf("%d",&sequence[i]) or sequence[i]==-1) break;
    printf("%d",getLengthOfMaxMonotoneIncreasingSequence(sequence, i));
    return 0;
}
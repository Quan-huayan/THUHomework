struct matrix
{
    long long nums[2][2];//先列后行
    //重载运算符
    matrix operator * (matrix A)
    {
        matrix ret;
        ret.nums[0][0] = nums[0][0]*A.nums[0][0] + nums[0][1]*A.nums[1][0];
        ret.nums[0][1] = nums[0][0]*A.nums[0][1] + nums[0][1]*A.nums[1][1];
        ret.nums[1][0] = nums[1][0]*A.nums[0][0] + nums[1][1]*A.nums[1][0];
        ret.nums[1][1] = nums[1][0]*A.nums[0][1] + nums[1][1]*A.nums[1][1];
        return ret;
    }
    matrix operator % (long long n)
    {
        matrix ret = *this;
        ret.nums[0][0] %= n;
        ret.nums[0][1] %= n;
        ret.nums[1][0] %= n;
        ret.nums[1][1] %= n;
        return ret;
    }
};

#include <stdio.h>

//快速幂
matrix powmod(matrix a, long long d, long long mod)
{
    matrix ret = {{{1,0},{0,1}}};
    while (d>0)
    {
        if (d & 1) ret = (ret*a)%mod;
        a = (a*a)%mod;
        d >>= 1;
    }
    return ret; 
}

int main()
{
    matrix f0 = {{{1,1},{1,0}}};
    int n;
    scanf("%d %d",&n);
    printf("%lld",powmod(f0,n,10007).nums[0][1]);
    return 0;
}
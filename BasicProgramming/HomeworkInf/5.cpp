//组合问题：简单递推可以得到
//对于任何n:b_n:1打头的非法字符串,c_n:0打头的非法字符串,a_n=b_n+c_n
//b_n = c_{n-1} + 2^(n-2)
//c_n = b_{n-1} + c_{n-1} = a_{n-1}
//即 a_n = a_{n-1} + a_{n-2} + 2^(n-1)
//n=0,1时自然都是0
//n=2:a_2=a_1+a_0+1=1:11:1
//n=3:a_3=a_2+a_1+2=3:011,110,111:3
//n=4:a_4=a_3+a_2+4=8:0011,0110,0111,1100,1101,1110,1111,1011:8
//令 a_n = d_n + 2^n, 则 d_n = d_{n-1} + d_{n-2}
//实际上可以计算出 d_n = -F_(n+2)

//快速幂
long long powmod(long long a, long long d, long long mod)
{
    long long ret = 1;
    while (d>0)
    {
        if (d & 1) ret = (ret*a)%mod;
        a = (a*a)%mod;
        d >>= 1;
    }
    return ret; 
}

struct matrix
{
    long long nums[2][2];//先列后行
    //重载运算符
    matrix MulMod(matrix A,long long n)
    {
        matrix ret;
        ret.nums[0][0] = ((nums[0][0]*A.nums[0][0])%n + (nums[0][1]*A.nums[1][0])%n)%n;
        ret.nums[0][1] = ((nums[0][0]*A.nums[0][1])%n + (nums[0][1]*A.nums[1][1])%n)%n;
        ret.nums[1][0] = ((nums[1][0]*A.nums[0][0])%n + (nums[1][1]*A.nums[1][0])%n)%n;
        ret.nums[1][1] = ((nums[1][0]*A.nums[0][1])%n + (nums[1][1]*A.nums[1][1])%n)%n;
        return ret;
    }
};

#include <stdio.h>

//矩阵快速幂
matrix powmod(matrix a, long long d, long long mod)
{
    matrix ret = {{{1,0},{0,1}}};
    while (d>0)
    {
        if (d & 1) ret = ret.MulMod(a,mod);
        a = a.MulMod(a,mod);
        d >>= 1;
    }
    return ret; 
}

#define MOD 1000000007

int main()
{
    matrix f0 = {{{1,1},{1,0}}};
    int n;
    scanf("%d",&n);
    printf("%lld ",(powmod(2,n,MOD)+MOD-powmod(f0,n+2,MOD).nums[0][1])%MOD);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long long inline pow10ll(long long d)
{
    long long ret[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000};
    return d<0?1:ret[d];
}

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

bool isPrime(long long num)
{
    if(num<2) return false;
    //if(num==2 or num==3 or num==5 or num==7 or num==11 or num==61) return true;
    if(num<=1000000)//对于本题 1e6以下返回true
        return true;
    else //>10^6时用Miller-Rabin测试，2^32以下是确定性的
    {
        if(num%2==0 || num%3==0 || num%7==0 || num%11==0) return false;
        long long d = num-1;
        long long s=0;
        while(!(d&1)) d>>=1,s++;
        const int p_tests[]={2,7,11,61};

        for(int k=0;k<4;k++)
        {
            int p = p_tests[k];
            long long x = powmod(p,d,num);
            if(x!=1 and x!=num-1)
            {
                for(int i=0;i<s-1;i++)
                {
                    x = (x * x) % num;
                    if(x==num-1) { x=1;break;}
                }
                if(x!=1) return false;
            }
        }
    }
    return true;
}

int palindromes_1e6[113] = {2,3,5,7,11,101,131,151,181,191,313,353,373,383,727,757,787,797,919,929,
    10301,10501,10601,11311,11411,12421,12721,12821,13331,13831,13931,14341,14741,15451,15551,16061,
    16361,16561,16661,17471,17971,18181,18481,19391,19891,19991,30103,30203,30403,30703,30803,31013,
    31513,32323,32423,33533,34543,34843,35053,35153,35353,35753,36263,36563,37273,37573,38083,38183,
    38783,39293,70207,70507,70607,71317,71917,72227,72727,73037,73237,73637,74047,74747,75557,76367,
    76667,77377,77477,77977,78487,78787,78887,79397,79697,79997,90709,91019,93139,93239,93739,94049,
    94349,94649,94849,94949,95959,96269,96469,96769,97379,97579,97879,98389,98689};

int inline getDigitNumber(long long n)
{
    return (int)log10(n)+1;
}

int generate_Palindromes(unsigned int min, unsigned int max, long long *lp)
{
    int ret=0;
    if(min<=1000000)
    {
        for(int i = 0;i<113 && palindromes_1e6[i]<=max;i++)
            if(palindromes_1e6[i]>=min)
                lp[ret++]=palindromes_1e6[i];
        if(max<=1000000) return ret;
        min = 1000001;//只生成首位为10
    }

    //初始化
    int nMinDigitsNumber = getDigitNumber(min);
    int halfMinDigitsNumber = nMinDigitsNumber / 2;
    int nowHighHalf,nowHighHalf_s, nowHalfDigits;
    int iFirst;
    nowHalfDigits = halfMinDigitsNumber+1;
    if(nMinDigitsNumber % 2 == 0) iFirst = 0, nowHighHalf_s = 0;
    else
    {
        nowHighHalf = min / pow10ll(halfMinDigitsNumber);
        int nFirst = nowHighHalf / pow10ll(nowHalfDigits-1);
        //首位调整
        switch(nFirst)
        {
        case 1:
            iFirst=0, nowHighHalf_s=nowHighHalf - 1*pow10ll(nowHalfDigits-1);
            break;
        case 2:
            iFirst=1, nowHighHalf_s= 0;
            break;
        case 3:
            iFirst=1, nowHighHalf_s=nowHighHalf - 3*pow10ll(nowHalfDigits-1);
            break;
        case 4:case 5:case 6:
            iFirst=2, nowHighHalf_s=0;
            break;
        case 7:
            iFirst=2, nowHighHalf_s=nowHighHalf - 7*pow10ll(nowHalfDigits-1);
            break;
        case 8:
            iFirst=3, nowHighHalf_s=0;
            break;
        case 9:
            iFirst=3, nowHighHalf_s=nowHighHalf - 9*pow10ll(nowHalfDigits-1);
            break;
        }
    }

    int nMaxDigitsNumber = getDigitNumber(max);
    int halfMaxDigitsNumber = nMaxDigitsNumber / 2;
    int maxHighHalf,maxHalfDigits,maxHighHalf_s,max_nFirst;
    if(nMaxDigitsNumber % 2 == 0) max_nFirst = 9, maxHighHalf_s = pow10ll(halfMaxDigitsNumber - 1) - 1, maxHalfDigits=halfMaxDigitsNumber;
    else maxHighHalf = max / pow10ll(halfMaxDigitsNumber), 
    maxHalfDigits=halfMaxDigitsNumber+1, max_nFirst = maxHighHalf / pow10ll(maxHalfDigits-1),
    maxHighHalf_s = maxHighHalf % pow10ll(maxHalfDigits-1);

    //先对半位数循环，nowHalfDigits
    for(;nowHalfDigits<=maxHalfDigits;nowHalfDigits++)
    {
        int nFirsts[4]={1,3,7,9};
        //然后对首位循环，i=0,1,2,3分别对应首位为1,3,7,9
        for(;iFirst<4;iFirst++)
        {
            //然后对nowHighHalf_s循环
            if(nowHalfDigits<maxHalfDigits || nFirsts[iFirst]<max_nFirst)
            {
                for(;nowHighHalf_s<pow10ll(nowHalfDigits-1);nowHighHalf_s++)
                {
                    //生成一个回文数

                    //先计算尾部
                    long long n = nFirsts[iFirst]*pow10ll(nowHalfDigits-1) + nowHighHalf_s, nNow = 0;
                    n /= 10;
                    while(n) nNow = nNow * 10 + n%10, n/=10;

                    //然后加和得到完整值
                    lp[ret++] = (nFirsts[iFirst]*pow10ll(nowHalfDigits-1) + nowHighHalf_s) * pow10ll(nowHalfDigits-1) + nNow;
                }
                //回到初始值
                nowHighHalf_s = 0;
            }
            else
            {
                if(nFirsts[iFirst] == max_nFirst)
                {
                    for(;nowHighHalf_s<=maxHighHalf_s;nowHighHalf_s++)
                    {
                        //生成一个回文数

                        //先计算尾部    
                        long long n = nFirsts[iFirst]*pow10ll(nowHalfDigits-1) + nowHighHalf_s, nNow = 0;
                        n /= 10;
                        while(n) nNow = nNow * 10 + n%10, n/=10;

                        //然后加和得到完整值
                        long long next = (nFirsts[iFirst]*pow10ll(nowHalfDigits-1) + nowHighHalf_s) * pow10ll(nowHalfDigits-1) + nNow;
                        if(next > max) return ret;
                        lp[ret++] = next;
                    }
                }
                //返回
                return ret;
            }
        }
        iFirst=0;//首次执行不改变iFirst,但往后iFirst需置初值
    }
    return -1;
}

//2^32-1以下一共有5953个回文质数
int main()
{
    unsigned int min, max;
    scanf("%u %u",&min,&max);
    unsigned int m;
    long long i,*llPalindromes=new long long[100000];//我们最多会生成44113个回文数
    int nPalindromes = generate_Palindromes(min,max,llPalindromes);
    long long nums=0;
    for(int i=0;i<nPalindromes;i++)
        if(isPrime(llPalindromes[i]))
            printf("%lld ", llPalindromes[i]);
    delete[] llPalindromes;
    return 0;
}
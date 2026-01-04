#include <stdio.h>

const int prime_split[18][8]={
    {2,4,6,10,12,16,18,-1},//1
    {1,3,5,9,11,15,17,-1},//2
    {2,4,8,10,14,16,-1},//3
    {1,3,7,9,13,15,-1},//4
    {2,6,8,12,14,18,-1},//5
    {1,5,7,11,13,17,-1},//6
    {4,6,10,12,16,-1},//7
    {3,5,9,11,15,-1},//8
    {2,4,8,10,14,-1},//9
    {1,3,7,9,13,-1},//10
    {2,6,8,12,18,-1},//11
    {1,5,7,11,17,-1},//12
    {4,6,10,16,18,-1},//13
    {3,5,9,15,17,-1},//14
    {2,4,8,14,16,-1},//15
    {1,3,7,13,15,-1},//16
    {2,6,12,14,-1},//17
    {1,5,11,13,-1}//18
    };

int main()
{
    int n;
    scanf("%d",&n);
    if(n % 2 != 0) printf("No Answer");
    int* result = new int[n];
    bool* tagUses = new bool[n];//0代表1，依此类推
    int *p=result,*pEnd=result + n - 1;
    for(int i=0;i<n;tagUses[i++]=false);
    *p = 1;tagUses[0]=true;
    int nFail = -1;
    bool tagFirst = true;
    do
    {
        do
        {
            if(!tagFirst)
            {
                const int *r = prime_split[*(p-1)-1];
                while(*r!=-1 && *r<=n)
                {
                    if(*r<=nFail) 
                    {
                        r++;
                        continue;
                    }
                    if(tagUses[(*r)-1]==false)
                        break;
                    r++;
                }
                if(*r==-1 || *r>n) break;
                *p = *r;
                tagUses[(*p)-1]=true;
            }
            else tagFirst = false;
            for(p++;p<=pEnd;p++)
            {
                const int *r = prime_split[*(p-1)-1];
                while(*r!=-1 && *r<=n)
                {
                    if(tagUses[(*r)-1]==false)
                        break;
                    r++;
                }
                if(*r==-1 || *r>n) break;
                *p = *r;
                tagUses[(*p)-1]=true;
            }
            if(p>pEnd)
            {
                if(prime_split[*pEnd-1][0] != 1) break;
                for(int i=0;i<n;i++) printf("%d ",result[i]);
                putchar('\n');
            }
        } while(0);//所有的break都代表p处开始出现问题(p-1推不出合理的p的值)
        //记录下出问题的数字
        nFail = *(p-1);
        //p回退1格
        p--;tagUses[(*p)-1]=false;
        if(p <= result) break;
    } while(1);
    delete[] result;
}
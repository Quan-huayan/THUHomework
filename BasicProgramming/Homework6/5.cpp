#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 2001

#define MAX_INT_LENGTH 224

#define MAX_INT 999999999

#define RADIX (MAX_INT+1)


char* getTail(char* str)
{
    char* p = str;
    while (*(p++));
    return --p;
}

void reverse(char* str)
{
    char* tail = getTail(str), * head = str;
    tail--;
    while (head < tail)
    {
        char temp = *head;
        *head = *tail;
        *tail = temp;
        head++, tail--;
    }
}

//int最大值2,147,483,648，可存储0-999,999,999

//乘法结果放在num1
//num1,num2应遵循低位小号的排序
void multiply(int* num1, int* num2)
{
    long long u = 0, step = 0,step2 = 0;//最多可能出现两次进位
    int numResult[MAX_INT_LENGTH] = {0};//结果临时存储
    int *p1 = num1, *p2 = num2, *p = numResult;
    while(*p2 != -1)
    {
        int shift = p2 - num2;
        p1 = num1;
        p = numResult + shift;
        u = 0, step = 0, step2 = 0;
        while(*p1 != -1)
        {
            u = (long long)(*p1) * (long long)(*(p2)) + step + *p;
            *p = u % RADIX;
            u /= RADIX;
            u += step2;
            step = u % RADIX;
            step2 = u / RADIX;
            p1++,p++;
        }
        while(step || step2)
        {
            u = *p + step;
            *p = u % RADIX;
            u /= RADIX;
            u += step2;
            step = u % RADIX;
            step2 = u / RADIX;
        }
        p2++;
    }
    //-1标志
    int i;
    for(i = MAX_INT_LENGTH-1;i>0;i--)
        if(numResult[i-1]!=0)
        {
            numResult[i]=-1;
            break;
        }
    memcpy(num1, numResult, (i+1)*sizeof(int));
}

//请先行reverse
//9位一次拆分
//最后部分置-1
void split(char* s, int* num)
{
    int len = strlen(s);
    char c[10];
    int nNowPos  = 0;
    int i = 0;
    for(i=0;i<len;i+=9)
    {
        strncpy(c, s, 9);
        reverse(c);
        *num = atoi(c);
        s += 9,num++;
    }
    *num = -1;
}

//请保证s为空，用后请自行reverse
//9位一次合并
//注意最高位要设为-1
void merge(char* s, int* num)
{
    char c[12];
    while(1)
    {
        if(*num == -1) break;
        sprintf(c, "%.9i", *(num++));
        reverse(c);
        strcat(s,c);
    }
    //删去尾部0
    char* t = getTail(s);
    t--;
    while(*t=='0') *(t--) = '\0';
}

int main()
{
    char c1[MAX_LENGTH],c2[MAX_LENGTH];
    int num1[MAX_INT_LENGTH],num2[MAX_INT_LENGTH];
    gets(c1), gets(c2);
    reverse(c1), reverse(c2);
    split(c1,num1), split(c2,num2);
    multiply(num1,num2);
    memset(c2, 0, MAX_LENGTH);
    merge(c2,num1);
    reverse(c2);
    if(!(*c2)) putchar('0'); 
    else puts(c2);
    return 0;
}
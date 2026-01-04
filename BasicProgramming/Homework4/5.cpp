#include <stdio.h>
#include <string.h>

#define BUF_SIZE 0x1000


char* getTail(char* str)
{
    char* p=str;
    while(*(p++));
    return --p;
}

void reverse(char * str)
{
    char * tail = getTail(str),* head=str;
    tail--;
    while((unsigned long)head<(unsigned long)tail)
    {
        char temp=*head;
        *head=*tail;
        *tail=temp;
        head++,tail--;
    }
}

//输入的是个位在前的字符串
void add(char* num1, char* num2, char *sum)
{
    int nJinwei=0;
    char *p1 = num1, *p2 = num2, *p = sum;
    while(*p1 && *p2)
    {
        int sumNow = (*p1-'0')+(*p2-'0')+nJinwei;
        *p = sumNow % 10 + '0';
        nJinwei = sumNow / 10;
        p1++,p2++,p++;
    }
    if(*p1)//如果p1所指非空
    {
        while(*p1)
        {
            int sumNow = (*p1-'0')+nJinwei;
            *p = sumNow % 10 + '0';
            nJinwei = sumNow / 10;
            p1++,p++;
        }
    }
    else if(*p2) //如果p2所指非空
    {
        while(*p2)
        {
            int sumNow = (*p2-'0')+nJinwei;
            *p = sumNow % 10 + '0';
            nJinwei = sumNow / 10;
            p2++,p++;
        }
    }
    //全部加和完毕
    if(nJinwei==0) *p='\0';//置终止符
    else *p='1',*(++p)='\0';
}

int main()
{
    char num1[BUF_SIZE]="\0",num2[BUF_SIZE]="\0",sum[BUF_SIZE]="\0";
    gets(num1);
    gets(num2);
    reverse(num1);
    reverse(num2);
    add(num1,num2,sum);
    reverse(sum);
    puts(sum);
    return 0;
}
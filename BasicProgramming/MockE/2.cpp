#include <stdio.h>
#include <string.h>

void reverse(char* str)
{
    char* p = str, * q=str;
    while(*(q++));
    q--,q--;//
    while(p<q)
    {
        char c = *p;
        *p = *q;
        *q = c;
        p++, q--;
    };
}

inline char itc(int i)
{
    return i<10 ? i+'0' : i-10+'A';
}

inline int cti(char s)
{
    return (s >= '0') && (s <= '9') ? s - '0' : s - 'A' + 10;
}

int myAtoi(char* str, int len, int index)
{
    char* p=str, *pEnd = str + len;
    int ret = 0;
    while(*p && p<pEnd)
    {
        ret = ret * index + cti(*p++);
    }
    return ret;
}

void myItoa(int num, char* str, int len, int index)
{
    char* p = str, *pEnd = str+len;
    while(num && p<pEnd)
    {
        *(p++) = itc(num % index);
        num /= index;
    }
    *p = '\0';
    reverse(str);
}

int main()
{
    char s1[40], s2[40];
    int index1,index2;
    gets(s1);
    scanf("%d",&index1);
    scanf("%d",&index2);
    
    if(strlen(s1) == 1 && s1[0] == '0')
    {
        putchar('0');
        return 0;
    }
    myItoa(myAtoi(s1,40,index1),s2,40,index2);
    puts(s2);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char words[16][20] = {"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen"};

char words_square_rev[16][3] = {"00","10","40","90","61",
"52","63","94","46","18","00",
"12","44","96","69","52"};

int words_num[20] = {-1};

inline int value(int s) { return (s*s)%100;}

int main()
{
    int n;
    char temp[20], all[200] = {'\0'};
    scanf("%d",&n);
    int m = 0;
    for(int i=0;i<n;i++)
    {
        scanf("%s",temp);
        //变小写
        char *p=temp;
        while(*p) *p = tolower(*p),p++;
        int j=0;
        for(;j<16;j++) 
            if(0==strcmp(temp,words[j])) 
                break;
        if(j==16) continue;
        words_num[m++] = j;
    }
    //排序
    for(int i=0;i<m;i++)
        for(int j=m-1;j>i;j--)
            if(value(words_num[j-1])<value(words_num[j]))
            {
                int temp = words_num[j];
                words_num[j] = words_num[j-1];
                words_num[j-1] = temp;
            }
    //拼接
    for(int i=0;i<m;i++)
        strcat(all, words_square_rev[words_num[i]]);
    //去掉末尾0
    //先获得末尾
    char *p=all;
    while(*(p++));
    p--;//p指向NULL
    while(*(--p)=='0' && p>=all);
    if(p<all)
    {
        putchar('0');
        return 0;        
    }
    p++;
    *p='\0';
    //reverse
    p--;
    char *q=all;
    while(q<p)
    {
        char temp=*p;
        *p=*q;
        *q=temp;
        p--,q++;
    }
    puts(all);
    return 0;
}
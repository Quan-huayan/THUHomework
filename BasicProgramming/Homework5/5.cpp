#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 2000


int inline sgn(int n)
{
    if (!n) return 0;
    return n > 0 ? 1 : (-1);
}

int LCD(int n, int m)
{
    if (n == 0) return m;
    else if (m == 0) return n;
    if (n < m) { int temp = n; n = m; m = temp; }//使m<n
    return LCD(n % m, m);
}

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
    while ((unsigned long)head < (unsigned long)tail)
    {
        char temp = *head;
        *head = *tail;
        *tail = temp;
        head++, tail--;
    }
}

void long_division(char* buf, int up, int low)
{
    //先全部转换成正数；
    int sign = sgn(up) * sgn(low);
    up *= sgn(up), low *= sgn(low);
    if (sign == 0)//由于分母不为0，故输出为0
    {
        buf[0] = '0', buf[1] = 0;
        return;
    }

    //下面进行长除法：
    int nIntegerPart = up / low;//先获取小数部分
    up %= low;
    if (up)//整除的情况不需要长除
    {
        //优化，约掉LCD
        int nLCD = LCD(up, low);
        up /= nLCD;
        low /= nLCD;

        int nRest = up, nDiv = 0;//nRest存储当前余数，nDiv存储商
        int* arRest = (int*)calloc(low + 8, sizeof(int));//用来存储余数的数组
        int* arDiv = (int*)calloc(low + 8, sizeof(int));//用来存储商的数组
        bool tagCycleDecimal = false;//为false说明无循环
        int posCycleStart = 0;
        int posRest = 0, posBuf = 0;
        while (!tagCycleDecimal)
        {
            //计算当前的商
            nRest *= 10;
            nDiv = nRest / low;
            nRest = nRest % low;
            arDiv[posRest] = nDiv;
            arRest[posRest++] = nRest;

            //buf写入当前的商
            buf[posBuf++] = nDiv + '0';
            
            if (nRest == 0) break;//为0时退出

            //进行是否循环判断
            for (int i = 0; i < posRest - 1; i++) //posRest此时指向当前余数所在位置的下一个位置
                if (nRest == arRest[i] && nDiv == arDiv[i])
                {
                    tagCycleDecimal = true;//说明存在循环
                    posCycleStart = i;//posBuf恰是循环节开头所在位置
                    buf[posBuf] = '\0';//将现在的商所在位置的下一个位置0
                    posBuf--; //buf位置回退
                    buf[posBuf] = ')';//将现在的商所在位置放上后括号
                    break;//退出循环
                }
        }

        if (tagCycleDecimal)//若存在循环
        {
            char* pStart = &buf[posCycleStart], * pEnd = getTail(pStart);
            *(pEnd + 1) = '\0';
            do { *pEnd = *(pEnd - 1); } while (--pEnd != pStart);
            *pStart = '(';
        }

        free(arDiv);
        free(arRest);
    }

    //将整数部分转化成字符串
    char* sDecimal = (char*)calloc(MAX_STRING_LENGTH, sizeof(char));

    //先处理正负号
    if (sign == -1) sDecimal[0] = '-', sDecimal++;

    char* p = sDecimal;
    while (nIntegerPart)
    {
        *p++ = nIntegerPart % 10 + '0';
        nIntegerPart = nIntegerPart / 10;
    }

    if (sDecimal[0]) reverse(sDecimal);
    else sDecimal[0] = '0', p++;
    if (buf[0]) *(p++) = '.', * p = '\0';

    if (sign == -1) sDecimal--;//再处理正负号

    strcat(sDecimal, buf);
    strcpy(buf, sDecimal);
    free(sDecimal);
}

int main()
{
    int numerator, denominator;
    char buf[MAX_STRING_LENGTH] = { 0 };
    scanf("%d %d", &numerator, &denominator);
    long_division(buf, numerator, denominator);
    printf("%s", buf);
    return 0;
}
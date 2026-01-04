#include <stdio.h>
#include <stdlib.h>

int intersection_set(int* a, int* b, int m, int n, int* result)
{
    int* p1 = a, * p2 = b, * pResult = result;
    int* pEnd1 = p1 + m - 1, * pEnd2 = p2 + n - 1;
    bool tag1 = false, tag2 = false;
    do
    {
        //谁小谁进
        if(*p1 < *p2)
        {
            if(tag1) break;
            else while(*p1 < *p2)
            {
                p1++;
                if(p1>pEnd1)
                {
                    tag1 = true;//同时跳出外层循环
                    break;
                }
            }
        }
        else if(*p2 < *p1)
        {
            if(tag2) break;
            else while(*p2 < *p1)
            {
                p2++;
                if(p2>pEnd2)
                {
                    tag2 = true;
                    break;
                }
            }
        }
        else //*p1=*p2
        {
            *(pResult++) = *p1;
            if(p1<pEnd1) p1++;
            else break;
            if(p2<pEnd2) p2++;
            else break;
        }
    }while(!tag1 && !tag2);
    return pResult - result;
}

int union_set(int* a, int* b, int m, int n, int* result)
{
    int* p1 = a, * p2 = b, * pResult = result;
    int* pEnd1 = p1 + m - 1, * pEnd2 = p2 + n - 1;
    bool tag1 = false, tag2 = false;
    do
    {
        //谁小谁进
        if(*p1 < *p2)
        {
            if(tag1)//tag1进不了了,p2进
            {
                while(p2<=pEnd2) *(pResult++) = *(p2++);
                tag2 = true;//结束循环
            }
            else while(*p1 < *p2)
            {
                if(p1>=pEnd1)
                {
                    *(pResult++) = *p1;
                    tag1 = true;
                    break;
                }
                *(pResult++) = *(p1++);
            }
        }
        else if(*p2 < *p1)
        {
            if(tag2)//p2进不了了,p1进
            {
                while(p1<=pEnd1) *(pResult++) = *(p1++);
                tag1 = true;//结束循环
            }
            else while(*p2 < *p1)
            {
                if(p2>=pEnd2)
                {
                    *(pResult++) = *p2;
                    tag2 = true;
                    break;
                }
                *(pResult++) = *(p2++);
            }
        }
        else //*p1=*p2
        {
            *(pResult++) = *p1;
            if(p1<pEnd1) p1++;
            else tag1=true;
            if(p2<pEnd2) p2++;
            else tag2=true;
        }
    }while(!tag1 || !tag2);
    return pResult - result;
}

int difference_set(int* a, int* b, int m, int n, int* result)
{
    int* p1 = a, * p2 = b, * pResult = result;
    int* pEnd1 = p1 + m - 1, * pEnd2 = p2 + n - 1;
    bool tag1 = false, tag2 = false;
    do
    {
        //谁小谁进
        if(*p1 < *p2)
        {//不可能有tag1=true
            while(*p1 < *p2)
            {
                *(pResult++) = *p1;
                if(p1>=pEnd1)
                {
                    tag1 = true;
                    break;
                }
                p1++;
            }
        }
        else if(*p2 < *p1)
        {
            if(tag2)//p2进不了了,p1进
            {
                while(p1<=pEnd1) *(pResult++) = *(p1++);
                break;
            }
            else while(*p2 < *p1)
            {
                if(p2>=pEnd2)
                {
                    tag2 = true;
                    break;
                }
                p2++;
            }
        }
        else //*p1=*p2
        {
            if(p1<pEnd1) p1++;
            else break;
            if(p2<pEnd2) p2++;
        }
    }while(!tag1);
    return pResult - result;
}

int main()
{
    int* num1, * num2, *result, nNum1, nNum2, nResult;

    scanf("%d", &nNum1);
    num1 = new int[nNum1];
    for (int i = 0; i < nNum1; i++) scanf("%d", &num1[i]);
    scanf("%d", &nNum2);
    num2 = new int[nNum2];
    for (int i = 0; i < nNum2; i++) scanf("%d", &num2[i]);

    result = new int[nNum1 + nNum2];

    nResult = intersection_set(num1, num2, nNum1, nNum2, result);
    for (int i = 0; i < nResult; i++) printf("%d ", result[i]);
    
    putchar('\n');

    nResult = union_set(num1, num2, nNum1, nNum2, result);
    for (int i = 0; i < nResult; i++) printf("%d ", result[i]);
    
    putchar('\n');

    nResult = difference_set(num1, num2, nNum1, nNum2, result);
    for (int i = 0; i < nResult; i++) printf("%d ", result[i]);

    delete[] num1;
    delete[] num2;
    delete[] result;

    return 0;
}
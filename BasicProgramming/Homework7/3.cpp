#include <stdio.h>
#include <stdlib.h>

void merge(int* a, int* b, int m, int n, int* result)
{
    int* p1 = a, * p2 = b, * pResult = result;
    int* pEnd1 = p1 + m - 1, * pEnd2 = p2 + n - 1;
    while (p1 <= pEnd1 || p2 <= pEnd2)
    {
        int iNow1, iNow2;
        bool tag1 = true, tag2 = true;
        if (p1 <= pEnd1) iNow1 = *(p1++);
        else tag1 = false;
        if (p2 <= pEnd2) iNow2 = *(p2++);
        else tag2 = false;
        if (tag1 && tag2) *pResult = iNow1 > iNow2 ? (p1--, iNow2) : (p2--, iNow1);
        else *pResult = tag1 ? iNow1 : iNow2;
        pResult++;
    }
}

int main()
{
    int* num1, * num2, *result, nNum1, nNum2;

    scanf("%d", &nNum1);
    num1 = new int[nNum1];
    for (int i = 0; i < nNum1; i++) scanf("%d", &num1[i]);
    scanf("%d", &nNum2);
    num2 = new int[nNum2];
    for (int i = 0; i < nNum2; i++) scanf("%d", &num2[i]);

    result = new int[nNum1 + nNum2];

    merge(num1, num2, nNum1, nNum2, result);

    for (int i = 0; i < nNum1 + nNum2; i++) printf("%d ", result[i]);

    delete[] num1;
    delete[] num2;
    delete[] result;

    return 0;
}
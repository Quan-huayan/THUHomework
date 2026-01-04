#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned int u32;

void swap(u32&a, u32&b)
{
    u32 t = a;
    a = b;
    b = t;
}

void sort(u32* array, int n)
{
    if(n<=1) return;
    
    if(n<=16)
        for(int i=n-1;i>0;i--)
            for(int j=0;j<i;j++)
                if (array[j]>array[j+1]) swap(array[j],array[j+1]);
    
    int nLeftHalf = n/2,nRightHalf = n - nLeftHalf;
    sort(array, nLeftHalf);
    sort(array + nLeftHalf, nRightHalf);
    
    u32 *array_backup = new u32[n];
    memcpy(array_backup, array, n * sizeof(u32));
    u32 *p=array;
    u32 *pL=array_backup, *pR=array_backup+nLeftHalf;
    u32 *pL_end = pR-1, *pR_end = array_backup+n-1;
    
    while(pL<=pL_end && pR<=pR_end)
        if(*pL<=*pR) *p++ = *pL++;
        else *p++ = *pR++;
    
    while(pL<=pL_end) *p++=*pL++;
    while(pR<=pR_end) *p++=*pR++;
    
    delete[] array_backup;
}

int main()
{
    int n;
    scanf("%d",&n);
    u32 *array = new u32[n];
    for(int i=0;i<n;i++) scanf("%u",&array[i]);
    sort(array, n);
    for(int i=0;i<n;i++) printf("%u ",array[i]);
    return 0;
}
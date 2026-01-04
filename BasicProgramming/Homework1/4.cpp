#include <stdio.h>

bool isRunnian(int nYear)
{
    return (!(nYear % 4) && (nYear % 100)) || !(nYear % 400);
}

int main()
{
    int nYear;
    scanf("%d", &nYear);
    printf("%s",isRunnian(nYear) ? "TRUE" : "FALSE");
    return 0;
}
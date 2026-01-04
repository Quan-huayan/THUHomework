#include <stdio.h>

int main()
{
    int a, b, result;
    char c;
    scanf("%d %c %d",&a,&c,&b);
    switch(c)
    {
    case '+':
        result = a + b;break;
    case '-':
        result = a - b;break;
    case '*':
        result = a * b;break;
    default:
        return -1;
    }
    printf("%d",result);
    return 0;
}
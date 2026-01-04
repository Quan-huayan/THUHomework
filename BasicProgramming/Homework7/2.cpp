#include <stdio.h>
#include <string.h>

int main()
{
    char s1[1000],s2[1000];
    gets(s1);
    gets(s2);
    printf("%d", strcmp(s1,s2));

    return 0;
}
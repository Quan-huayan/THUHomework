#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 200


int main()
{
    char c1[MAX_LENGTH],c2[MAX_LENGTH],*p1=c1,*p2=c2;
    char cFirst = getchar(), c;
    while(EOF != (c=getchar()))
    {
        if(c > cFirst) *(p1++) = c;
        else *(p2++) = c;
    }
    *(p1++) = cFirst;
    *p1 = *p2 = '\0';
    int lC2 = strlen(c2);
    for(int i=0;i<lC2-1;i++)
        for(int j=lC2-1;j>=i;j--)
            if(c2[j-1]>c2[j])
            {
                char temp = c2[j-1];
                c2[j-1] = c2[j];
                c2[j] = temp;
            }
    strcat(c1,c2);
    printf("%s", c1);
    return 0;
}
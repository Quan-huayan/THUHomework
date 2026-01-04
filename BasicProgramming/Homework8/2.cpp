#include <stdio.h>
#include <ctype.h>

void strcompress(char *in, char *out)
{
    int count[26] = {0};
    char *p=in, *q=out;
    for(;*p;p++)
    {
        if(islower(*p))
        {
            auto index = *p - 'a';
            count[index]++;
            if(count[index] != 1 and count[index] !=3 and count[index]!=6) continue;
        }
        *(q++)=*p;
    }
    *q='\0';
}

int main()
{
    char input[1001]={0}, output[1001]={0};
    gets(input);
    strcompress(input,output);
    puts(output);
    return 0;
}
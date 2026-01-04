#include <stdio.h>
#include <ctype.h>

int inline AlphabetToIndex(char c)
{
    if(isupper(c)) return c - 'A';
    else if (islower(c)) return c - 'a' + 26;
    return 0;
}

char inline IndexToAlphabet(int index)
{
    if(index<26) return index + 'A';
    else if(index<52) return index - 26 + 'a';
    return 0;
}

int main()
{
    char c;
    bool b[52] = {false};
    while(EOF != (c=getchar()) && c!='\n')
    {
        int i;
        if(i=AlphabetToIndex(c)) b[i]=!b[i];
    }
    for(int i=0;i<52;i++)
        if(b[i]) printf("%c", IndexToAlphabet(i));
    return 0;
}
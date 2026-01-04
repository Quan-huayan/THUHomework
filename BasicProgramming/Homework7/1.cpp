#include <stdio.h>
#include <string.h>

char* getTail(char* str)
{
    char* p = str;
    while (*(p++));
    return --p;
}

int main()
{
    char word[30], suffix[5];
    scanf("%s",word);
    
    char *tail = getTail(word);
    tail--;

    switch(*tail)
    {
    case 's':
    case 'x':
    case 'z':
        strcpy(suffix,"es");
        break;
    case 'h':
        tail--;
        switch(*tail)
        {
        case 'c':
        case 's':
            strcpy(suffix, "es");
            break;
        default:
            strcpy(suffix, "s");
        }
        break;
    case 'y':
        tail--;
        switch(*tail)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            strcpy(suffix, "s");
            break;
        default:
            tail++;
            *tail = 'i';
            strcpy(suffix, "es");
        }
        break;
    default:
        strcpy(suffix, "s");
    }

    strcat(word,suffix);
    printf("%s", word);

    return 0;
}
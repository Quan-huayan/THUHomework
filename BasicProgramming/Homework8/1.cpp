#include <stdio.h>
#include <string.h>

int expression(char* s)
{
    char *p = s, lastOperation = '/0';
    int ret=0,nowNum = 0;
    bool tagEqual = false;
    while(*p)
    {
        switch(*p)
        {
        case '=':
            tagEqual = true;
        case '+':
        case '-':
            switch (lastOperation)
            {
            case '+':
                ret += nowNum;
                break;
            case '-':
                ret -= nowNum;
                break;
            default:
                ret = nowNum;
                break;
            }
            nowNum = 0, lastOperation = *p;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            nowNum = nowNum*10 + (*p - '0');
            break;
        }
        if(tagEqual) break;
        p++;
    }
    return ret;
}

int main()
{
    char string[200];
    gets(string);
    printf("%d", expression(string));
    return 0;
}
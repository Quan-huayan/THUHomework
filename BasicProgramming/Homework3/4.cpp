#include <stdio.h>

int main()
{
    int summary[3] = {0};
    int c;
    while((c=getchar())!='#')
    {
        switch(c)
        {
        case ' ':
            summary[0]++;
            break;
        case '\n':
            summary[1]++;
            break;
        default:
            summary[2]++;
            break;
        }
    }
    printf("%d %d %d", summary[0],summary[1],summary[2]);
    return 0;
}
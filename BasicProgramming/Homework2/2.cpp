#include <stdio.h>

enum scoreRate
{
    F=0,
    D=6,
    C,
    B,
    A
};

int main()
{
    int score;
    scanf("%d",&score);
    switch(int rate = score/10)
    {
    case 10:
        rate--;
    case A:
    case B:
    case C:
    case D:
        printf("%c",'A'+9-rate);break;
    case F:
    default:
        printf("F");
    }
    return 0;
}
#include <stdio.h>
#include <math.h>

int main()
{
    const long xuehao = 2025030000L;

    float sq = sqrtf(xuehao);
    printf("%d\n%.2f\n%d %d", xuehao, sq, xuehao / 19260817L, xuehao % 19260817L);

    return 0;
}
#include <stdio.h>

struct vector
{
    int x, y;
    int static inline isParallel(vector a, vector b)
    { return !(a.x*b.y-a.y*b.x)?1:0;}
    int static inline isPendicular(vector a, vector b)
    { return !(a.x*b.x+a.y*b.y)?1:0;}
};

int main()
{
    vector vA, vB;
    scanf("%d %d %d %d",&vA.x,&vA.y,&vB.x,&vB.y);
    int tag = vector::isParallel(vA,vB) + vector::isPendicular(vA,vB) * 2;
    if(tag==3) tag = 1;
    printf("%d", tag);
    return 0;
}
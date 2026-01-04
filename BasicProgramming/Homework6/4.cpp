#include "stdio.h"
#include "string.h"

int main()
{
    char c[8];
    gets(c);

    int len = strlen(c);
    int nums[8];
    bool tag[10]={false};
    for(int i=0;i<len;i++)
    {
        nums[i] = c[i] - '0';
        if(nums[i]<=0 || nums[i]>9 || tag[nums[i]]) 
        {
            printf("no");
            return 0;
        }
        tag[nums[i]] = true;
    }

    int i = 0;
    do
    {
        i = (nums[i] + i) % len;
        if(!tag[nums[i]])
        {
            printf("no");
            return 0;
        }
        tag[nums[i]]=false;
    }while(i);//结束条件应该是i回到0

    tag[nums[0]] = false;

    for(int i=1;i<10;i++)
        if(tag[i])
        {
            printf("no");
            return 0;
        }
    printf("yes");
    return 0;
}
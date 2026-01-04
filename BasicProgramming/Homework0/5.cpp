#include <stdio.h>

typedef struct timex
{
    int hour;
    int minute;
    int second;
} time;

int inline standard_time(time t)
{
    return t.hour * 3600 + t.minute * 60 + t.second;
}

//输出单位为second
int differ_time(time start, time end)
{
    //将时间转换为标准秒时间
    int time_start = standard_time(start), time_end = standard_time(end);

    return (time_end + 86400 - time_start) % 86400;
}

int main()
{
    time start, end;
    scanf("%d:%d:%d %d:%d:%d", &start.hour, &start.minute, &start.second,
        &end.hour, &end.minute, &end.second);
    printf("%d", differ_time(start, end));
    return 0;
}
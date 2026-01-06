#include <stdio.h>
#include <stdbool.h>

// 月份天数数组
int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// 判断是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取某年某月的天数
int getMonthDays(int year, int month) {
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return monthDays[month - 1];
}

// 计算日期是星期几（0=周日, 1=周一, ..., 6=周六）
int getWeekday(int year, int month, int day) {
    // Zeller公式
    if (month < 3) {
        month += 12;
        year--;
    }
    
    int century = year / 100;
    int y = year % 100;
    
    int weekday = (day + 13 * (month + 1) / 5 + y + y / 4 + century / 4 + 5 * century) % 7;
    
    // 转换为0=周日, 1=周一, ..., 6=周六
    return (weekday + 6) % 7;
}

// 计算两个日期之间的天数差
int daysBetween(int y1, int m1, int d1, int y2, int m2, int d2) {
    // 将日期转换为从公元1年1月1日开始的天数
    long days1 = 0, days2 = 0;
    
    // 计算第一个日期的天数
    for (int year = 1; year < y1; year++) {
        days1 += isLeapYear(year) ? 366 : 365;
    }
    for (int month = 1; month < m1; month++) {
        days1 += getMonthDays(y1, month);
    }
    days1 += d1;
    
    // 计算第二个日期的天数
    for (int year = 1; year < y2; year++) {
        days2 += isLeapYear(year) ? 366 : 365;
    }
    for (int month = 1; month < m2; month++) {
        days2 += getMonthDays(y2, month);
    }
    days2 += d2;
    
    return (int)(days2 - days1);
}

// 日期增加指定天数
void addDays(int *year, int *month, int *day, int days) {
    *day += days;
    
    while (*day > getMonthDays(*year, *month)) {
        *day -= getMonthDays(*year, *month);
        (*month)++;
        
        if (*month > 12) {
            *month = 1;
            (*year)++;
        }
    }
}

// 测试
int main() {
    printf("=== 日期计算测试 ===\n");
    
    int year = 2026, month = 1, day = 6;
    printf("当前日期: %d年%d月%d日\n", year, month, day);
    
    // 判断闰年
    printf("%d年是%s年\n", year, isLeapYear(year) ? "闰" : "平");
    
    // 获取星期几
    char *weekdays[] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};
    int weekday = getWeekday(year, month, day);
    printf("%d年%d月%d日是%s\n", year, month, day, weekdays[weekday]);
    
    // 计算天数差
    int y1 = 2024, m1 = 3, d1 = 15;
    int y2 = 2024, m2 = 12, d2 = 25;
    int diff = daysBetween(y1, m1, d1, y2, m2, d2);
    printf("%d年%d月%d日 到 %d年%d月%d日 相差 %d 天\n", 
           y1, m1, d1, y2, m2, d2, diff);
    
    // 日期增加
    printf("\n%d年%d月%d日 增加30天后: ", year, month, day);
    addDays(&year, &month, &day, 30);
    printf("%d年%d月%d日\n", year, month, day);
    
    return 0;
}
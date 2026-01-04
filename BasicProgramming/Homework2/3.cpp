#include <stdio.h>

enum
{
    SOLO = 1,
    HOMEOWNER,
    MARRIED,
    DIVORCED
};
const int TaxChangedLine[]={17850,23900,29750,14875};
const double TaxBasicRate = 0.15;
const double TaxRestRate = 0.28;

#define ReLU(a) (((a)>0)?(a):0)


int main()
{
    int individualType;
    double income;
    scanf("%d %lf",&individualType,&income);

    //标准化:从零开始，故减1
    printf("%.6lf",income * TaxBasicRate + ReLU(income - TaxChangedLine[individualType-1]) * (TaxRestRate-TaxBasicRate));
    return 0;
}
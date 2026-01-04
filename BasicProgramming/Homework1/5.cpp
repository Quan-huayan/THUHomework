//牛顿迭代

#include <stdio.h>
#include <math.h>

int IsHasSolution(double a, double b, double c)
{
    //a,c异号直接返回
    if (a > 0 && c < 0) return 2;
    if (a < 0 && c > 0) return 2;
    if (a == 0 || c == 0) return fabs(b) > 0 ? 2 : 1;
    //c 过大的情况
    if (a > 1.0 && c > 1.0e6 && b < 2.0e3) return 0;
    //b 过大的情况
    if (b > 1000)
        if (a * c < 250000) return 2;
        else
        {
            if (a < 0 && c < 0) a = -a, c = -c;
            double delta = fabs(b) - 2 * sqrt(a) * sqrt(c);
            if (fabs(delta) < 1.0e-10) return 1;
            if (delta > 0) return 2;
            if (delta < 0) return 0;
        }
    //a 过小的情况
    if (fabs(a) < 0.0001)
        if (b > 1 && c < 2500)
            return 2;
        else a *= 100, b *= 100, c *= 100;

    double delta = c - (b / a) * (b / 4.0);

    if (fabs(delta) < 1.0e-10) return 1;

    if (a < 0) delta = -delta;

    return delta < 0 ? 2 : 0;
}

//本方法默认二重根
double GetSolution(double x0, double a, double b, double c)
{
    //ax^2+bx+c的导数为2ax+b.
    double x1, delta;
    x1 = x0;
    //a 过小的情况
    if (fabs(a) < 0.0001 && fabs(b)<0.01) a *= 100, b *= 100, c *= 100;
    do
    {
        delta = (a * x1 * x1 + b * x1 + c) / (2 * a * x1 + b);
        x1 -= delta;
    } while (fabs(delta) >= 1.0e-12);
    return x1;
}

double inline getSym(double a, double b)
{
    //a,b均过小时放大处理
    if (a < 1e-4 && b < 1e-2) a *= 1000, b *= 1000;
    return -b / a * 0.5;
}

int main()
{
    double a, b, c, s1, s2, dSym;
    int tag;
    scanf("%lf %lf %lf", &a, &b, &c);
    dSym = getSym(a, b);
    if(fabs(dSym) <= 1e-14) dSym = 0;
    if (!(tag = IsHasSolution(a, b, c))) printf("Error");
    else if (tag == 1) printf("%.6lf", dSym);
    else {
        s1 = GetSolution(dSym + fabs(dSym) * 0.1, a, b, c);
        s2 = GetSolution(dSym - fabs(dSym) * 0.1, a, b, c);
        if (s2 > s1) printf("%.6lf\n%.6lf", s2, s1);
        else printf("%.6lf\n%.6lf", s1, s2);
    }

    return 0;
}
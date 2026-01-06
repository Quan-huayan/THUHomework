#include <stdio.h>
#include <complex>
#include <math.h>
#include <string.h>

#define MAX_STRING_LENGTH 500001 //大数长度
#define MAX_INT_LENGTH 131072 //数组长度 55556
#define RADIX_DIGITS 7
#define INT_MAX_1 9999999
#define INT_DIGIT_FORMAT "%.7i"
#define RADIX (INT_MAX_1 + 1)

#define PI 3.14159265358979323846264338
using comp = std::complex<long double>;

char c1[MAX_STRING_LENGTH] = {0},c2[MAX_STRING_LENGTH] = {0};
comp num1[MAX_INT_LENGTH*2] = {0},num2[MAX_INT_LENGTH*2] = {0},num3[MAX_INT_LENGTH*2] = {0};
int num_buf[MAX_INT_LENGTH*2];

void reverse(char* str)
{
    char *tail = str, *head = str;
    while(*(tail++));
    tail--,tail--;
    while (head < tail)
    {
        char temp = *head;
        *head = *tail;
        *tail = temp;
        head++, tail--;
    }
}

void fft(comp* array,comp* buff, int n)
{
    if(n == 1) return;
    comp* array2 = array + (n / 2);

    //奇偶分离
    for(int i=1,j=0;i<n;i+=2,j++) buff[j] = array[i];//奇
    for(int i=0,j=0;i<n;i+=2,j++) array[j] = array[i];//偶
    for(int i=0;i<n/2;i++) array2[i] = buff[i];

    fft(array, buff, n/2);
    fft(array2, buff, n/2);

    //合并
    for(int i=0;i<n/2;i++)
    {
        comp a,b;
        comp factor = exp(-2 * PI * i / (long double)n * comp(0,1));
        a = array[i] + array2[i] * factor;
        b = array[i] - array2[i] * factor;
        array[i] = a;
        array2[i] = b;
    }
}

void ifft(comp* array, comp* buff, int n)
{
    for(int i=0;i<n;i++) array[i] = conj(array[i]);
    fft(array, buff, n);
    for(int i=0;i<n;i++) array[i] = conj(array[i]) / (long double)n;
}

void multiple()
{
    fft(num1, num3, MAX_INT_LENGTH*2);
    fft(num2, num3, MAX_INT_LENGTH*2);
    for(int i=0;i<MAX_INT_LENGTH*2;i++) num3[i] = num1[i] * num2[i];
    ifft(num3, num1, MAX_INT_LENGTH*2);
}

void get_num(char* s, comp* num)
{
    int len = strlen(s);
    char c[RADIX_DIGITS+1] = {0};
    int nNowPos  = 0;
    int i = 0;
    for(i=0;i<len;i+=RADIX_DIGITS)
    {
        strncpy(c, s, RADIX_DIGITS);
        reverse(c);
        *num = atoi(c);
        s += RADIX_DIGITS,num++;
    }
}

void out_num(char* buf, comp* num, int* int_buf)
{
    //处理进位
    long double next = 0;
    comp *p = num;
    int *q = int_buf;
    while(1)
    {
        long long numNow = llround(p->real() + next);
        next = numNow / RADIX;
        *q = numNow % RADIX;
        if(*q == 0 && lround(next) == 0)
        {
            *q = -1;
            break;
        }
        p++,q++;
    }
    char c[12];
    while(1)
    {
        if(*int_buf == -1) break;
        sprintf(c, INT_DIGIT_FORMAT, *(int_buf++));
        reverse(c);
        strcat(buf,c);
    }
    //删去尾部0
    char* t = buf;
    while(*(t++));
    t--,t--;
    while(*t=='0') *(t--) = '\0';
}

int main()
{
    char c,*p = c1;
    while((c=getchar())!=EOF && c!='\n') *(p++) = c;
    *p = '\0', p = c2;
    while((c=getchar())!=EOF && c!='\n') *(p++) = c;
    *p = '\0';
    reverse(c1),reverse(c2);
    get_num(c1, num1);
    get_num(c2, num2);
    multiple();
    memset(c2, 0, MAX_STRING_LENGTH);
    out_num(c2, num3, num_buf);
    reverse(c2);
    puts(c2);
    return 0;
}
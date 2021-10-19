#include <cs50.h>
#include <stdio.h>

long get_num(void);
void check_sum(long n);

int main(void)
{
    long num = get_num();
    check_sum(num);
}

long get_num(void)
{
    long num = get_long("Number: ");
    return num;
}

void check_type(digit,n)
{
    if (digit==15 && (n==34 || n==37))
    {
        printf("AMEX\n");
    }
    else if ((digit==16) && (n==51 || n==55))
    {
        printf("MASTERCARD\n");
    }
    else if ((digit==16 || digit == 13) && (n>=40 && n<50) )
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}


void check_sum(long n)
{
    long sum=0;
    long digit=0;
    long start_digit=0;
    for (long i=n; i>0; i=i/10)
    {

        long a=i % 10;
        if (i<100 && i>=10)
        {
            start_digit=i;
        }
        digit++;
        i=i/10;
        if (i<100 && i>=10)
        {
            start_digit=i;
        }
        if (i>0)
        {
            digit++;
        }
        long b = 2*(i%10);
        if (b>=10)
        {
            long m=b%10;
            long k=b/10%10;
            b=m+k;
        }
        sum=sum+a+b;
    }

    if (sum%10!=0)
    {
        printf("INVALID\n");
    }
    else
    {
        check_type(digit, start_digit);
    }
}

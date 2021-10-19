#include <cs50.h>
#include <stdio.h>

int get_height(void);
void make_bricks(int n);

int main(void)
{
    int i = get_height();
    make_bricks(i);
}

int get_height(void)
{
    int n;
    do
    {
        n=get_int("Height: ");
    }
    while (n>8 || n<1);
    return n;
}

void make_bricks(int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n-i-1; j++)
        {
            printf(" ");
        }
        for (int k=0; k<i+1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l=0; l<=i;l++)
        {
            printf("#");
        }

        printf("\n");
    }
}

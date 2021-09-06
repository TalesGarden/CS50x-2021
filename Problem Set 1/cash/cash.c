#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int coins = 0;
    float dollars = get_float("Change owed: ");

    while (dollars  < 0)
    {
        dollars = get_float("Change owed: ");
    }

    int cents = round(dollars * 100);

    int remaning = cents;

    do
    {
        if (remaning - 25 >= 0)
        {
            remaning -= 25;
            coins ++;
        }
        else if (remaning - 10 >= 0)
        {
            remaning -= 10;
            coins ++;
        }
        else if (remaning - 5 >= 0)
        {
            remaning -= 5;
            coins ++;
        }
        else if (remaning - 1 >= 0)
        {
            remaning -= 1;
            coins++;
        }
    }
    while (remaning > 0);

    printf("%i\n", coins);
}
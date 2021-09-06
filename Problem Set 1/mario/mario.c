#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    height = get_int("Height:");

    while (height < 1 || height > 8)
    {
        height = get_int("Height:");
    }

    for (int i = 0; i < height; ++i)
    {
        for (int space = height - (i + 1) ; space > 0; space --)
        {
            printf(" ");
        }

        for (int brick = 0 ; brick <= i; ++brick)
        {
            printf("#");
        }
        printf("\n");

    }
}
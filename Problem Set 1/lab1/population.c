#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startSize = 0;
    int endSize = 0;
    do
    {
        startSize = get_int("Start size: ");
    }
    while (startSize < 9);

    do
    {
        endSize = get_int("End size:");
    }
    while (endSize < startSize);


    int years = 0;
    int bornLlamas = 0;
    int deadLlamas = 0;
    while (startSize < endSize)
    {
        bornLlamas = startSize / 3;
        deadLlamas = startSize / 4;
        startSize = startSize + bornLlamas - deadLlamas;
        years++;
    }

    printf("Years: %d", years);
}
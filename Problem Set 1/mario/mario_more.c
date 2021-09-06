#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int count_lines = 0;
   int dimension_matrix;

    //input a positive integer between 1 and 8
   do{
       dimension_matrix = get_int("Height:");
   }
   while(dimension_matrix <=0 || dimension_matrix >8);

//Using a loop to print a part of the matrix
    for(int i = 1; i<=dimension_matrix; i++)
    {
        printf("\n");
        for(int j = 1; j<=dimension_matrix; j++)
        {
            if( (i+j)>=(dimension_matrix+1) )           //above the secondary matrix
            {
                printf("#");
                if(j == dimension_matrix)           //mirroring the first pyramid
                {
                    printf("  ");
                    count_lines++;
                    for(int k = 0; k<count_lines; k++)
                    {
                       printf("#");
                    }
                }
            }
            else
            {
                printf(" ");
            }
        }

    }
     printf("\n\n");

     return 0;
}

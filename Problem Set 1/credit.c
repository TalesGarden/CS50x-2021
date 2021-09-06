#include <stdio.h>
#include <cs50.h>

int sumValidation(int );
bool testLegit(int a,int b ,int c );

int main(void)
{
     int total_sum = 0;
     long int number = get_long("\n Number : ");
     long int aux = number;        //To save the original number
     int count_digits = 1 ;      //count the number of digits

     long int last_digit,remaining;

     //separate the long int  into peaces
     while(true)
     {
         last_digit =  aux%10;     //rest of division
         remaining =  aux/10;     //entire division by 10
         aux = remaining;        // rest of the initial integer;

         //  starting with the number’s second-to-last digit:
         if(count_digits % 2 == 0 )
         {
            last_digit *=2;
            total_sum = sumValidation(last_digit);
         }
         else if(count_digits%2 == 1)       //sum of the digits that weren’t multiplied by 2
         {
             total_sum = sumValidation(last_digit);
         }

         count_digits++;
         if( aux/10 == 0 )    //when there is one final digit
         {
            last_digit = remaining;
            if(count_digits % 2 == 0)
            {
                total_sum = sumValidation(last_digit*2);
            }
            break;
         }
     }

     testLegit(total_sum,count_digits,last_digit);
}
//  make sum of Luhn’s Algorithm
int sumValidation(int num1){

    static int total = 0;

    if ( num1 / 10 != 0 )   // add those products’ digits,not the products themselves) together
    {
        total += num1 % 10;
        total += num1 / 10;
        return total;
    }
    total += num1;
    return total;
}
//show if its a valid number card and what company card
bool testLegit(int num, int total_digits, int first_digit)
{
    if ( num%10 == 0)  // if number card is valid find the company
     {
        if( total_digits == 15 && first_digit % 3 ==0 )
         {
             printf("\tAMEX\n");
             return true;
         }

        if ( (total_digits ==13 || total_digits == 16) && first_digit == 4 )
        {
         printf("\tVISA\n");;
         return true;
        }
         if( total_digits == 16 && first_digit % 5 ==0)
         {
             printf("\tMASTERCARD\n");
             return true;
         }
     }
     printf("\tINVALID\n");
     return false;
}

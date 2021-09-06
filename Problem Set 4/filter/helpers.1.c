#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    int red, green, blue;
    //scanning the matriz, and averagin rgb
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j<width;++j)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;


            average = round((blue + green + red)/3.00);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue = 0;
    int sepiaRed, sepiaBlue, sepiaGreen;

    //scanning the matriz
    for(int i = 0; i<height; ++i)
    {
        for(int j = 0; j<width; ++j)
        {
            //saving the values
            red = image[i][j].rgbtRed;
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            //doing the calculations of sepia Filter
            sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            if(sepiaRed > 255)sepiaRed = 255;
            if(sepiaGreen > 255)sepiaGreen = 255;
            if(sepiaBlue > 255)sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // k contain the last indice of the array, and it decreases
    int k = 0;
    //use to save the values to make the change
    int auxRed, auxGreen, auxBlue;
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < (width/2); j++)
        {
            k = (width -j- 1);


            auxRed = image[i][j].rgbtRed;
            auxGreen = image[i][j].rgbtGreen;
            auxBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;

            image[i][k].rgbtRed = auxRed;
            image[i][k].rgbtGreen = auxGreen;
            image[i][k].rgbtBlue = auxBlue;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int average_red = 0, average_green = 0, average_blue = 0;
    int count_number = 0;

    int box = 1; // set 1 to have a 3x3 box

    //scanning the matriz
    for (int i = 0; i<height; ++i)
    {
        for(int j = 0; j<width;++j)
        {
            average_red = 0;
            average_blue = 0;
            average_red = 0;
            count_number = 0;

            //forming a 3x3 box
            for (int li = i-box; li<=i+box; ++li )
            {
                if( li < 0 )
                {
                    li = 0;
                }
                if( li == height)
                {
                    break;
                }

                for(int col = j-box; col<= j+box; col++)
                {

                    if (col == width ) break;
                    if (col < 0)
                    {
                        col = 0;
                    }

                    count_number++;

                    average_red += image[li][col].rgbtRed;
                    average_green += image[li][col].rgbtGreen;
                    average_blue += image[li][col].rgbtBlue;

                }

            }
                //set the new average to the pixel
            image[i][j].rgbtRed = average_red/count_number ;
            image[i][j].rgbtGreen = average_green/count_number;
            image[i][j].rgbtBlue = average_blue/count_number ;

            //cleaning the averages and the count number


        }

    }

    return;
}


  /*

*/
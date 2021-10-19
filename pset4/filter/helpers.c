#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // round括号搞错了！
            int shade = round((image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = shade;
            image[i][j].rgbtGreen = shade;
            image[i][j].rgbtRed = shade;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            // 忘记-1了！！
            image[i][j] = image[i][width-1-j];
            image[i][width-1-j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // you can't assign new value to image, because the pixel of each value is from the original image
    RGBTRIPLE newi[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue_sum = 0;
            int red_sum = 0;
            int green_sum = 0;
            float count = 0.0;
            for (int n = -1; n < 2; n++)
            {
                for ( int m = -1; m < 2; m++)
                {
                    //开始这里一直搞不定，边界可能弄错了，导致sum一直为0
                    // check的时候边界又错了！
                    if ((i + n) >= 0 && (i + n) <= height-1 && (j + m) >= 0 && (j + m) <= width-1)
                    {
                        blue_sum += image[i+n][j+m].rgbtBlue;
                    // printf("the image[%i][%i]'s blue sum is %i\n",i+n,j+m,image[i+n][j+m].rgbtBlue);
                        red_sum += image[i+n][j+m].rgbtRed;
                        green_sum += image[i+n][j+m].rgbtGreen;
                        count++;
                    }

                }

            }

            newi[i][j].rgbtBlue = round(blue_sum/count);
            // printf("the image[%i][%i]'s blue is %i\n",i,j,newi[i][j].rgbtBlue);
            newi[i][j].rgbtRed = round(red_sum/count);
            newi[i][j].rgbtGreen = round(green_sum/count);

        }
    }

 for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtBlue = newi[m][n].rgbtBlue;
            image[m][n].rgbtRed = newi[m][n].rgbtRed;
            image[m][n].rgbtGreen = newi[m][n].rgbtGreen;
        }
    }
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_blue=0;
            float Gy_blue=0;
            float Gx_red=0;
            float Gy_red=0;
            float Gx_green = 0;
            float Gy_green = 0;
            for (int m = 0; m < 3; m++)
            {
                for (int n = 0; n < 3; n++)
                {
                    if (i + m-1 < 0 || i + m-1 > height - 1)
                    {
                        continue;
                    }
                    if (j + n - 1 < 0 || j + n - 1> width - 1)
                    {
                        continue;
                    }


                    Gx_blue += image[i + m - 1][j + n - 1].rgbtBlue * Gx[m][n];
                    Gx_red += image[i + m - 1][j + n - 1].rgbtRed * Gx[m][n];
                    Gx_green += image[i + m - 1][j + n - 1].rgbtGreen * Gx[m][n];

                    Gy_blue += image[i + m - 1][j + n - 1].rgbtBlue * Gy[m][n];
                    Gy_red += image[i + m - 1][j + n - 1].rgbtRed * Gy[m][n];
                    Gy_green += image[i + m - 1][j + n - 1].rgbtGreen * Gy[m][n];
                }
            }

            int blue = round(sqrt(pow(Gx_blue,2) + pow(Gy_blue,2)));
            int red = round(sqrt(pow(Gx_red,2) + pow(Gy_red,2)));
            int green = round(sqrt(pow(Gx_green,2) + pow(Gy_green,2)));



            if (blue > 255)
            {
                blue = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }

            //一定要注意数据本身的限制(rgtblue-0到255)；所以先判断大小；
            //花了好长时间！！！

            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;


        }

    }

     for (int m = 0; m < height; m++)
        {
            for (int n = 0; n < width; n++)
            {

                image[m][n].rgbtBlue = temp[m][n].rgbtBlue;



                image[m][n].rgbtRed = temp[m][n].rgbtRed;



                image[m][n].rgbtGreen = temp[m][n].rgbtGreen;

            }
        }
}




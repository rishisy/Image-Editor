#include <math.h>

#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            float average = (image[x][y].rgbtRed + image[x][y].rgbtGreunzip reen +
                             image[x][y].rgbtBlue) /
                            3.0;
            image[x][y].rgbtRed = round(average);
            image[x][y].rgbtGreen = round(average);
            image[x][y].rgbtBlue = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            float sepiaRed = (.393 * image[x][y].rgbtRed) +
                             (.769 * image[x][y].rgbtGreen) +
                             (.189 * image[x][y].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            float sepiaGreen = (.349 * image[x][y].rgbtRed) +
                               (.686 * image[x][y].rgbtGreen) +
                               (.168 * image[x][y].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            float sepiaBlue = (.272 * image[x][y].rgbtRed) +
                              (.534 * image[x][y].rgbtGreen) +
                              (.131 * image[x][y].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[x][y].rgbtRed = round(sepiaRed);
            image[x][y].rgbtGreen = round(sepiaGreen);
            image[x][y].rgbtBlue = round(sepiaBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width / 2.0; y++)
        {
            BYTE temp1 = image[x][y].rgbtRed;
            BYTE temp2 = image[x][y].rgbtGreen;
            BYTE temp3 = image[x][y].rgbtBlue;
            image[x][y].rgbtRed = image[x][width - y - 1].rgbtRed;
            image[x][y].rgbtGreen = image[x][width - y - 1].rgbtGreen;
            image[x][y].rgbtBlue = image[x][width - y - 1].rgbtBlue;
            image[x][width - y - 1].rgbtRed = temp1;
            image[x][width - y - 1].rgbtGreen = temp2;
            image[x][width - y - 1].rgbtBlue = temp3;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    float avgred;
    float avggreen;
    float avgblue;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            if (x == 0 && y == 0)  // top left corner
            {
                avgred =
                    (image[x][y].rgbtRed + image[x][y + 1].rgbtRed +
                     image[x + 1][y].rgbtRed + image[x + 1][y + 1].rgbtRed) /
                    4.0;
                avggreen = (image[x][y].rgbtGreen + image[x][y + 1].rgbtGreen +
                            image[x + 1][y].rgbtGreen +
                            image[x + 1][y + 1].rgbtGreen) /
                           4.0;
                avgblue =
                    (image[x][y].rgbtBlue + image[x][y + 1].rgbtBlue +
                     image[x + 1][y].rgbtBlue + image[x + 1][y + 1].rgbtBlue) /
                    4.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);

            }
            else if (x == 0 && y == width - 1)  // top right corner
            {
                avgred =
                    (image[x][y].rgbtRed + image[x][y - 1].rgbtRed +
                     image[x + 1][y].rgbtRed + image[x + 1][y - 1].rgbtRed) /
                    4.0;
                avggreen = (image[x][y].rgbtGreen + image[x][y - 1].rgbtGreen +
                            image[x + 1][y].rgbtGreen +
                            image[x + 1][y - 1].rgbtGreen) /
                           4.0;
                avgblue =
                    (image[x][y].rgbtBlue + image[x][y - 1].rgbtBlue +
                     image[x + 1][y].rgbtBlue + image[x + 1][y - 1].rgbtBlue) /
                    4.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);

            }
            else if (x == height - 1 && y == 0)  // bottom left corner
            {
                avgred =
                    (image[x][y].rgbtRed + image[x][y + 1].rgbtRed +
                     image[x - 1][y].rgbtRed + image[x - 1][y + 1].rgbtRed) /
                    4.0;
                avggreen = (image[x][y].rgbtGreen + image[x][y + 1].rgbtGreen +
                            image[x - 1][y].rgbtGreen +
                            image[x - 1][y + 1].rgbtGreen) /
                           4.0;
                avgblue =
                    (image[x][y].rgbtBlue + image[x][y + 1].rgbtBlue +
                     image[x - 1][y].rgbtBlue + image[x - 1][y + 1].rgbtBlue) /
                    4.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);
            }
            else if (x == height - 1 &&
                     y == width - 1)  // bottom right corner
            {
                avgred =
                    (image[x][y].rgbtRed + image[x][y - 1].rgbtRed +
                     image[x - 1][y].rgbtRed + image[x - 1][y - 1].rgbtRed) /
                    4.0;
                avggreen = (image[x][y].rgbtGreen + image[x][y - 1].rgbtGreen +
                            image[x - 1][y].rgbtGreen +
                            image[x - 1][y - 1].rgbtGreen) /
                           4.0;
                avgblue =
                    (image[x][y].rgbtBlue + image[x][y - 1].rgbtBlue +
                     image[x - 1][y].rgbtBlue + image[x - 1][y - 1].rgbtBlue) /
                    4.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);
            }
            else if (x == 0 && (y != 0 && y != width - 1))  // top row
            {
                avgred =
                    (image[x][y].rgbtRed + image[x][y - 1].rgbtRed +
                     image[x][y + 1].rgbtRed + image[x + 1][y - 1].rgbtRed +
                     image[x + 1][y].rgbtRed + image[x + 1][y + 1].rgbtRed) /
                    6.0;
                avggreen =
                    (image[x][y].rgbtGreen + image[x][y - 1].rgbtGreen +
                     image[x][y + 1].rgbtGreen + image[x + 1][y - 1].rgbtGreen +
                     image[x + 1][y].rgbtGreen +
                     image[x + 1][y + 1].rgbtGreen) /
                    6.0;
                avgblue =
                    (image[x][y].rgbtBlue + image[x][y - 1].rgbtBlue +
                     image[x][y + 1].rgbtBlue + image[x + 1][y - 1].rgbtBlue +
                     image[x + 1][y].rgbtBlue + image[x + 1][y + 1].rgbtBlue) /
                    6.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);

            }
            else if ((x != 0 && x != height - 1) && y == 0)  // left col
            {
                avgred = (image[x][y].rgbtRed + image[x - 1][y].rgbtRed +
                          image[x + 1][y].rgbtRed + image[x][y + 1].rgbtRed +
                          image[x - 1][y + 1].rgbtRed +
                          image[x + 1][y + 1].rgbtRed) /
                         6.0;
                avggreen =
                    (image[x][y].rgbtGreen + image[x - 1][y].rgbtGreen +
                     image[x + 1][y].rgbtGreen + image[x][y + 1].rgbtGreen +
                     image[x - 1][y + 1].rgbtGreen +
                     image[x + 1][y + 1].rgbtGreen) /
                    6.0;
                avgblue = (image[x][y].rgbtBlue + image[x - 1][y].rgbtBlue +
                           image[x + 1][y].rgbtBlue + image[x][y + 1].rgbtBlue +
                           image[x - 1][y + 1].rgbtBlue +
                           image[x + 1][y + 1].rgbtBlue) /
                          6.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);
            }
            else if ((x != 0 && x != height - 1) && y == width - 1) // right col
            {
                avgred = (image[x][y].rgbtRed + image[x - 1][y].rgbtRed +
                          image[x + 1][y].rgbtRed + image[x][y - 1].rgbtRed +
                          image[x + 1][y - 1].rgbtRed +
                          image[x - 1][y - 1].rgbtRed) /
                         6.0;
                avggreen =
                    (image[x][y].rgbtGreen + image[x - 1][y].rgbtGreen +
                     image[x + 1][y].rgbtGreen + image[x][y - 1].rgbtGreen +
                     image[x + 1][y - 1].rgbtGreen +
                     image[x - 1][y - 1].rgbtGreen) /
                    6.0;
                avgblue = (image[x][y].rgbtBlue + image[x - 1][y].rgbtBlue +
                           image[x + 1][y].rgbtBlue + image[x][y - 1].rgbtBlue +
                           image[x + 1][y - 1].rgbtBlue +
                           image[x - 1][y - 1].rgbtBlue) /
                          6.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);
            }
            else if (x == height - 1 && (y != width - 1 && y != 0))  // bottom row
            {
                avgred = (image[x][y].rgbtRed + image[x][y - 1].rgbtRed +
                          image[x][y + 1].rgbtRed + image[x - 1][y].rgbtRed +
                          image[x - 1][y - 1].rgbtRed +
                          image[x - 1][y + 1].rgbtRed) /
                         6.0;
                avggreen =
                    (image[x][y].rgbtGreen + image[x][y - 1].rgbtGreen +
                     image[x][y + 1].rgbtGreen + image[x - 1][y].rgbtGreen +
                     image[x - 1][y - 1].rgbtGreen +
                     image[x - 1][y + 1].rgbtGreen) /
                    6.0;
                avgblue = (image[x][y].rgbtBlue + image[x][y - 1].rgbtBlue +
                           image[x][y + 1].rgbtBlue + image[x - 1][y].rgbtBlue +
                           image[x - 1][y - 1].rgbtBlue +
                           image[x - 1][y + 1].rgbtBlue) /
                          6.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);
            }
            else
            {
                avgred =
                    (image[x][y].rgbtRed + image[x][y - 1].rgbtRed +
                     image[x][y + 1].rgbtRed + image[x - 1][y].rgbtRed +
                     image[x - 1][y - 1].rgbtRed + image[x - 1][y + 1].rgbtRed +
                     image[x + 1][y - 1].rgbtRed + image[x + 1][y].rgbtRed +
                     image[x + 1][y + 1].rgbtRed) /
                    9.0;
                avggreen =
                    (image[x][y].rgbtGreen + image[x][y - 1].rgbtGreen +
                     image[x][y + 1].rgbtGreen + image[x - 1][y].rgbtGreen +
                     image[x - 1][y - 1].rgbtGreen +
                     image[x - 1][y + 1].rgbtGreen +
                     image[x + 1][y - 1].rgbtGreen + image[x + 1][y].rgbtGreen +
                     image[x + 1][y + 1].rgbtGreen) /
                    9.0;
                avgblue =
                    (image[x][y].rgbtBlue + image[x][y - 1].rgbtBlue +
                     image[x][y + 1].rgbtBlue + image[x - 1][y].rgbtBlue +
                     image[x - 1][y - 1].rgbtBlue +
                     image[x - 1][y + 1].rgbtBlue +
                     image[x + 1][y - 1].rgbtBlue + image[x + 1][y].rgbtBlue +
                     image[x + 1][y + 1].rgbtBlue) /
                    9.0;

                copy[x][y].rgbtRed = round(avgred);
                copy[x][y].rgbtGreen = round(avggreen);
                copy[x][y].rgbtBlue = round(avgblue);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}

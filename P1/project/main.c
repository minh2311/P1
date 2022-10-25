#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *c_image(unsigned char *i1, unsigned char *i2, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);

    for (int i = 0; i < width * height * channel; i += 3)
    {//                 red                                green                               blue
        if ((i1[i] >= 0 && i1[i] <= 150) && (i1[i+1] >= 150 && i1[i+1] <= 255) && (i1[i+2] >= 0 && i1[i+2] <= 150))
        {
            //if green, put weather
            temp_array[i] = i2[i];
            temp_array[i+1] = i2[i+1];
            temp_array[i+2] = i2[i+2];
        }
        else
        {
            //if not green, put girl
            temp_array[i] = i1[i];
            temp_array[i+1] = i1[i+1];
            temp_array[i+2] = i1[i+2];
        }
    }
    return temp_array;
}

int main()
{
    int width, height, channel;
    char woman[] = "./images/foreground.png";
    char weather[] = "./images/weather_forecast-resized.jpg";
    char save[] = "./images/background.png";
    
    unsigned char *i1 = stbi_load(woman, &width, &height, &channel, 3);
    unsigned char *i2 = stbi_load(weather, &width, &height, &channel, 0);

    unsigned char *combine_image = c_image(i1, i2, width, height, channel);
    stbi_write_jpg(save, width, height, channel, combine_image, width * channel);
}
#include "Image.h"
#include "Color.h"

#include <iostream>

Image::Image(int inWidth, int inHeight)
	: width(inWidth), height(inHeight)
{
}

void Image::Render()
{
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j < height; ++j) 
    {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) 
        {
            Color pixelColor = Color(
                float(i) / (width - 1),
                float(j) / (height - 1),
                0.0f
            );

            pixelColor.Write(std::cout);
        }
    }

    std::clog << "\rDone.                 \n";
}
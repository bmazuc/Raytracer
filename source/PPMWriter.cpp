#include "PPMWriter.h"
#include "Color.h"
#include "Maths/Interval.h"
#include "FrameBuffer.h"

#include <iostream>

PPMWriter::PPMWriter(std::ostream& inOutput)
	: output(inOutput)
{
}

void PPMWriter::Write(const FrameBuffer& frameBuffer) const
{
    int width = frameBuffer.GetWidth();
    int height = frameBuffer.GetHeight();

    const int pixelCount = width * height;

    WriteHeader(width, height);

    int lastProgress = -1;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            WritePixel(frameBuffer.GetPixel(x, y));
            const int pixel = y * width + x + 1;
            const int progress = (pixel * 100) / pixelCount;
            if (progress != lastProgress)
            {
                lastProgress = progress;
                std::clog << "\rWriting .ppm: " << progress << '%' << std::flush;
            }
        }
    }

    output.flush();
}

void PPMWriter::WriteHeader(int width, int height) const
{
    output << "P3\n" << width << ' ' << height << "\n255\n";
}

void PPMWriter::WritePixel(const Color& color) const
{
    Color gammaColor = Color::LinearToGamma(color);

    // Translate the [0,1] component values to the byte range [0,255].
    const Interval intensity(0.000f, 0.999f);
    int rbyte = int(255.999f * intensity.Clamp(gammaColor.r));
    int gbyte = int(255.999f * intensity.Clamp(gammaColor.g));
    int bbyte = int(255.999f * intensity.Clamp(gammaColor.b));

    // Write out the pixel color components.
    output << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
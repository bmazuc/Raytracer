#include "PPMWriter.h"
#include "Color.h"
#include "Maths/Interval.h"
#include "FrameBuffer.h"

PPMWriter::PPMWriter(std::ostream& inOutput)
	: output(inOutput)
{
}

void PPMWriter::Write(const FrameBuffer& frameBuffer) const
{
    int width = frameBuffer.GetWidth();
    int height = frameBuffer.GetHeight();

    WriteHeader(width, height);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            WritePixel(frameBuffer.GetPixel(x, y));
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
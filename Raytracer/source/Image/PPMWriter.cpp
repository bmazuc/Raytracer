#include "Image/PPMWriter.h"
#include "Color.h"
#include "Maths/Interval.h"
#include "Image/ImageBuffer.h"
#include "Utils/NumericUtils.h"

#include <fstream>

bool PPMWriter::Write(const std::string& filename, const ImageBuffer& frameBuffer) const
{
    if (!frameBuffer.IsValid())
    {
        return false;
    }

    std::ofstream output(filename);

    if (!output.is_open())
    {
        return false;
    }

    const int width = NumericUtils::ToInt(frameBuffer.GetWidth());
    const int height = NumericUtils::ToInt(frameBuffer.GetHeight());

    WriteHeader(output, width, height);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            WritePixel(output, frameBuffer.GetPixel(x, y));
        }
    }

    output.flush();
    if (!output.good())
    {
        return false;
    }

    output.close();

    return !output.fail();
}

void PPMWriter::WriteHeader(std::ofstream& output, int width, int height) const
{
    output << "P3\n" << width << ' ' << height << "\n255\n";
}

void PPMWriter::WritePixel(std::ofstream& output, const Color& color) const
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
#include "Image/ImageWriterFactory.h"
#include "Image/PPMWriter.h"
#include "Image/PngWriter.h"
#include "Image/JpgWriter.h"

#include <algorithm>

std::unique_ptr<ImageWriter> ImageWriterFactory::CreateImageWriter(const std::string& extension)
{
    std::string ext = extension;

    std::transform(
        ext.begin(),
        ext.end(),
        ext.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        }
    );

    if (extension == ".ppm")
    {
        return std::make_unique<PPMWriter>();
    }

    if (extension == ".png")
    {
        return std::make_unique<PngWriter>();
    }

    if (extension == ".jpg")
    {
        return std::make_unique<JpgWriter>();
    }

    return nullptr;
}
#include "Utils/ImageConverter.h"

#include <limits>

QImage ImageConverter::ToQImage(const ImageBuffer& buffer)
{
    if (!buffer.IsValid())
    {
        return {};
    }

    const size_t width = buffer.GetWidth();
    const size_t height = buffer.GetHeight();

    if (width > static_cast<size_t>(std::numeric_limits<int>::max() / 3) ||
        height > static_cast<size_t>(std::numeric_limits<int>::max()))
    {
        return {};
    }

    const std::vector<unsigned char> data = buffer.GetImageData();

    QImage image(
        data.data(),
        static_cast<int>(width),
        static_cast<int>(height),
        static_cast<int>(width * 3),
        QImage::Format_RGB888
    );

    return image.copy();
}

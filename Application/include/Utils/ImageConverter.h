#ifndef RAYTRACER_APPLICATION_IMAGE_CONVERTER_H
#define RAYTRACER_APPLICATION_IMAGE_CONVERTER_H

#include <QImage>
#include "Image/ImageBuffer.h"

namespace ImageConverter
{
    QImage ToQImage(const ImageBuffer& buffer);
}

#endif // RAYTRACER_APPLICATION_IMAGE_CONVERTER_H
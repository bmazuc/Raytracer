#ifndef RAYTRACER_APPLICATION_IMAGE_CONVERTER_H
#define RAYTRACER_APPLICATION_IMAGE_CONVERTER_H

#include <QImage>
#include "Image/ImageBuffer.h"

namespace ImageConverter
{
    /**
     * Convers the internal RGB pixel representation into a QImage
     * suitable for display in the graphical interface.
     *
     * @param buffer Source image buffer.
     * @return Converted Qt image.
     */
    QImage ToQImage(const ImageBuffer& buffer);
}

#endif // RAYTRACER_APPLICATION_IMAGE_CONVERTER_H
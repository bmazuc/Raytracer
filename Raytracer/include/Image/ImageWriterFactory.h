#ifndef RAYTRACER_IMAGE_WRITER_FACTORY_H
#define RAYTRACER_IMAGE_WRITER_FACTORY_H

#include <memory>
#include <string>

class ImageWriter;

namespace ImageWriterFactory
{
	std::unique_ptr<ImageWriter> CreateImageWriter(const std::string& extension);
}

#endif // RAYTRACER_IMAGE_WRITER_FACTORY_H
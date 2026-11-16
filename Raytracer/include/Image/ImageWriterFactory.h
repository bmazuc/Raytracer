#ifndef RAYTRACER_IMAGE_WRITER_FACTORY_H
#define RAYTRACER_IMAGE_WRITER_FACTORY_H

#include <memory>
#include <string>

class ImageWriter;

namespace ImageWriterFactory
{
	/**
	* Selects the appropriate writer according to the provided
	 * file extension.
	 *
	 * @param extension File extension identifying the image format.
	 * @return An instance of the corresponding image writer,
	 * or nullptr if the format is unsupported.
	*/
	std::unique_ptr<ImageWriter> CreateImageWriter(const std::string& extension);
}

#endif // RAYTRACER_IMAGE_WRITER_FACTORY_H
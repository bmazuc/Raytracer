#ifndef SKY_MATERIAL_SERIALIZER_H
#define SKY_MATERIAL_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <memory>

class Sky;
class GradientSky;

/**
 * Handles serialization and deserialization of sky models.
 *
 * Converts supported background models and their properties
 * to and from JSON representations.
 */
class SkySerializer
{
public:
	/**
	 * Delegates the conversion to the serializer corresponding
	 * to the concrete sky type.
	 *
	 * @param sky Sky to serialize.
	 * @return JSON representation of the sky.
	 */
	static nlohmann::json SkyToJson(const Sky* sky);
	/**
	 * Identifies the serialized sky type and creates
	 * the corresponding sky instance.
	 *
	 * @param json JSON object describing the sky.
	 * @return Reconstructed sky object.
	 */
	static std::unique_ptr<Sky> SkyFromJson(const nlohmann::json& json);

private:
	/**
	 * Serializes a gradient sky and its properties into JSON.
	 *
	 * @param gradient Gradient sky to serialize.
	 * @return JSON representation of the sky.
	 */
	static nlohmann::json GradientSkyToJson(const GradientSky* gradientSky);
	/**
	 * Reconstructs a gradient sky from its JSON representation.
	 *
	 * @param json JSON object containing gradient sky properties.
	 * @return Reconstructed gradient sky.
	 */
	static std::unique_ptr<GradientSky> GradientSkyFromJson(const nlohmann::json& json);
};

#endif // OBJECT_MATERIAL_SERIALIZER_H
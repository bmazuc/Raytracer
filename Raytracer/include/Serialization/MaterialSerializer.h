#ifndef RAYTRACER_MATERIAL_SERIALIZER_H
#define RAYTRACER_MATERIAL_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <memory>

class Material;
class Lambertian;
class Metal;
class Dielectric;

/**
 * Handles serialization and deserialization of materials.
 *
 * Converts supported material types and their properties
 * to and from JSON representations.
 */
class MaterialSerializer
{
public:
	/**
	 * Delegates the conversion to the serializer corresponding
	 * to the concrete material type.
	 * 
	 * @param material Material to serialize.
	 * @return JSON representation of the material.
	 */
	static nlohmann::json MaterialToJson(const std::shared_ptr<Material>& material);
	/**
	 * Identifies the serialized object type and creates
	 * the corresponding material instance.
	 * 
	 * @param json JSON object describing the material.
	 * @return Reconstructed material.
	 */
	static std::shared_ptr<Material> MaterialFromJson(const nlohmann::json& json);

private:
	/**
	 * Serializes a lambertian material and its properties into JSON.
	 *
	 * @param lambertian Lambertian material to serialize.
	 * @return JSON representation of the material.
	 */
	static nlohmann::json LambertianToJson(const std::shared_ptr<Lambertian>& lambertian);
	/**
	 * Reconstructs a lambertian material from its JSON representation.
	 *
	 * @param json JSON object containing lambertian material properties.
	 * @return Reconstructed lambertian material.
	 */
	static std::shared_ptr<Lambertian> LambertianFromJson(const nlohmann::json& json);

	/**
	 * Serializes a metal material and its properties into JSON.
	 *
	 * @param metal Metal material to serialize.
	 * @return JSON representation of the material.
	 */
	static nlohmann::json MetalToJson(const std::shared_ptr<Metal>& metal);
	/**
	 * Reconstructs a metal material from its JSON representation.
	 *
	 * @param json JSON object containing metal material properties.
	 * @return Reconstructed metal material.
	 */
	static std::shared_ptr<Metal> MetalFromJson(const nlohmann::json& json);

	/**
	 * Serializes a dielectric material and its properties into JSON.
	 *
	 * @param dielectric Dielectric material to serialize.
	 * @return JSON representation of the material.
	 */
	static nlohmann::json DielectricToJson(const std::shared_ptr<Dielectric>& dielectric);
	/**
	 * Reconstructs a dielectric material from its JSON representation.
	 *
	 * @param json JSON object containing dielectric material properties.
	 * @return Reconstructed dielectric material.
	 */
	static std::shared_ptr<Dielectric> DielectricFromJson(const nlohmann::json& json);
};

#endif // RAYTRACER_MATERIAL_SERIALIZER_H
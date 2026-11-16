#ifndef OBJECT_MATERIAL_SERIALIZER_H
#define OBJECT_MATERIAL_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <memory>

class Hittable;
class Sphere;

/**
 * Handles serialization and deserialization of scene objects.
 *
 * Converts supported geometric objects to and from JSON representations.
 */
class ObjectSerializer
{
public:
	/**
	 * Delegates the conversion to the serializer corresponding
	 * to the concrete object type.
	 *
	 * @param object Scene object to serialize.
	 * @return JSON representation of the object.
	 */
	static nlohmann::json ObjectToJson(const std::shared_ptr<Hittable>& object);
	/**
	 * Identifies the serialized object type and creates
	 * the corresponding geometric instance.
	 *
	 * @param json JSON object describing the geometry.
	 * @return Reconstructed scene object.
	 */
	static std::shared_ptr<Hittable> ObjectFromJson(const nlohmann::json& json);

private:
	/**
	 * Serializes a sphere and its properties into JSON.
	 *
	 * @param sphere Sphere to serialize.
	 * @return JSON representation of the sphere.
	 */
	static nlohmann::json SphereToJson(const std::shared_ptr<Sphere>& sphere);
	/**
	 * Reconstructs a sphere from its JSON representation.
	 *
	 * @param json JSON object containing sphere properties.
	 * @return Reconstructed sphere.
	 */
	static std::shared_ptr<Sphere> SphereFromJson(const nlohmann::json& json);
};

#endif // OBJECT_MATERIAL_SERIALIZER_H
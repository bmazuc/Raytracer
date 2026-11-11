#include "Serialization/ObjectSerializer.h"
#include "Serialization/MaterialSerializer.h"
#include "Serialization/JsonTypes.h"
#include "Scene/Sphere.h"

nlohmann::json ObjectSerializer::ObjectToJson(const std::shared_ptr<Hittable>& object)
{
	if (std::shared_ptr<Sphere> sphere = std::dynamic_pointer_cast<Sphere>(object))
	{
		return SphereToJson(sphere);
	}

	throw std::runtime_error("Unknown object type");
}

nlohmann::json ObjectSerializer::SphereToJson(const std::shared_ptr<Sphere>& sphere)
{
	return {
		{"type", "sphere"},
		{"position", sphere->GetCenter()},
		{"radius", sphere->GetRadius()},
		{"material", MaterialSerializer::MaterialToJson(sphere->GetMaterial())}
	};
}

std::shared_ptr<Hittable> ObjectSerializer::ObjectFromJson(const nlohmann::json& json)
{
	const std::string type = json.at("type").get<std::string>();

	if (type == "sphere")
	{
		return SphereFromJson(json);
	}

	throw std::runtime_error("Unknown object type: " + type);
}

std::shared_ptr<Sphere> ObjectSerializer::SphereFromJson(const nlohmann::json& json)
{
	return std::make_shared<Sphere>(
		json.at("position").get<Vec3>(),
		json.at("radius").get<float>(),
		MaterialSerializer::MaterialFromJson(json.at("material"))
	);
}
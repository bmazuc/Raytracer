#ifndef OBJECT_MATERIAL_SERIALIZER_H
#define OBJECT_MATERIAL_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <memory>

class Hittable;
class Sphere;

class ObjectSerializer
{
public:
	static nlohmann::json ObjectToJson(const std::shared_ptr<Hittable>& object);
	static std::shared_ptr<Hittable> ObjectFromJson(const nlohmann::json& json);

private:
	static nlohmann::json SphereToJson(const std::shared_ptr<Sphere>& sphere);
	static std::shared_ptr<Sphere> SphereFromJson(const nlohmann::json& json);
};

#endif // OBJECT_MATERIAL_SERIALIZER_H
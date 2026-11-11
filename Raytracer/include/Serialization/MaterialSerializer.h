#ifndef RAYTRACER_MATERIAL_SERIALIZER_H
#define RAYTRACER_MATERIAL_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <memory>

class Material;
class Lambertian;
class Metal;
class Dielectric;

class MaterialSerializer
{
public:
	static nlohmann::json MaterialToJson(const std::shared_ptr<Material>& material);
	static std::shared_ptr<Material> MaterialFromJson(const nlohmann::json& json);

private:
	static nlohmann::json LambertianToJson(const std::shared_ptr<Lambertian>& lambertian);
	static std::shared_ptr<Lambertian> LambertianFromJson(const nlohmann::json& json);

	static nlohmann::json MetalToJson(const std::shared_ptr<Metal>& metal);
	static std::shared_ptr<Metal> MetalFromJson(const nlohmann::json& json);

	static nlohmann::json DielectricToJson(const std::shared_ptr<Dielectric>& dielectric);
	static std::shared_ptr<Dielectric> DielectricFromJson(const nlohmann::json& json);
};

#endif // RAYTRACER_MATERIAL_SERIALIZER_H
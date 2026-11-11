#ifndef SKY_MATERIAL_SERIALIZER_H
#define SKY_MATERIAL_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <memory>

class Sky;
class GradientSky;

class SkySerializer
{
public:
	static nlohmann::json SkyToJson(const Sky* sky);
	static std::unique_ptr<Sky> SkyFromJson(const nlohmann::json& json);

private:
	static nlohmann::json GradientSkyToJson(const GradientSky* gradientSky);
	static std::unique_ptr<GradientSky> GradientSkyFromJson(const nlohmann::json& json);
};

#endif // OBJECT_MATERIAL_SERIALIZER_H
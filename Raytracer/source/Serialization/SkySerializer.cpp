#include "Serialization/SkySerializer.h"
#include "Serialization/JsonTypes.h"
#include "Scene/Sky/Sky.h"
#include "Scene/Sky/GradientSky.h"

nlohmann::json SkySerializer::SkyToJson(const Sky* sky)
{
	if (const GradientSky* gradient = dynamic_cast<const GradientSky*>(sky))
	{
		return GradientSkyToJson(gradient);
	}

	throw std::runtime_error("Unknown sky type");
}

std::unique_ptr<Sky> SkySerializer::SkyFromJson(const nlohmann::json& json)
{
	const std::string type = json.at("type").get<std::string>();

	if (type == "gradient")
	{
		return GradientSkyFromJson(json);
	}

	throw std::runtime_error("Unknown sky type: " + type);
}

nlohmann::json SkySerializer::GradientSkyToJson(const GradientSky* gradientSky)
{
	return {
			{"type", "gradient"},
			{"horizonColor", gradientSky->GetHorizonColor()},
			{"zenithColor", gradientSky->GetZenithColor()}
	};
}

std::unique_ptr<GradientSky> SkySerializer::GradientSkyFromJson(const nlohmann::json& json)
{
	return std::make_unique<GradientSky>(
		json.at("horizonColor").get<Color>(),
		json.at("zenithColor").get<Color>()
	);
}
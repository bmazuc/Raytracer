#include "Serialization/MaterialSerializer.h"
#include "Serialization/JsonTypes.h"

#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

nlohmann::json MaterialSerializer::MaterialToJson(const std::shared_ptr<Material>& material)
{
    if (std::shared_ptr<Lambertian> lambertian = std::dynamic_pointer_cast<Lambertian>(material))
    {
        return LambertianToJson(lambertian);
    }

    if (std::shared_ptr<Metal> metal = std::dynamic_pointer_cast<Metal>(material))
    {
        return MetalToJson(metal);
    }

    if (std::shared_ptr<Dielectric> dielectric = std::dynamic_pointer_cast<Dielectric>(material))
    {
        return DielectricToJson(dielectric);
    }

    throw std::runtime_error("Unknown material type");
}

std::shared_ptr<Material> MaterialSerializer::MaterialFromJson(const nlohmann::json& json)
{
    const std::string type = json.at("type").get<std::string>();

    if (type == "lambertian")
    {
        return LambertianFromJson(json);
    }

    if (type == "metal")
    {
        return MetalFromJson(json);
    }

    if (type == "dielectric")
    {
        return DielectricFromJson(json);
    }

    throw std::runtime_error("Unknown material type: " + type);
}

nlohmann::json MaterialSerializer::LambertianToJson(const std::shared_ptr<Lambertian>& lambertian)
{
    return {
            {"type", "lambertian"},
            {"albedo", lambertian->GetAlbedo()}
    };
}

std::shared_ptr<Lambertian> MaterialSerializer::LambertianFromJson(const nlohmann::json& json)
{
    return std::make_shared<Lambertian>(
        json.at("albedo").get<Color>()
    );
}

nlohmann::json MaterialSerializer::MetalToJson(const std::shared_ptr<Metal>& metal)
{
    return {
    {"type", "metal"},
    {"albedo", metal->GetAlbedo()},
    {"roughness", metal->GetRoughness()}
    };
}
std::shared_ptr<Metal> MaterialSerializer::MetalFromJson(const nlohmann::json& json)
{
    return std::make_shared<Metal>(
        json.at("albedo").get<Color>(),
        json.at("roughness").get<float>()
    );
}

nlohmann::json MaterialSerializer::DielectricToJson(const std::shared_ptr<Dielectric>& dielectric)
{
    return {
           {"type", "dielectric"},
           {"refractionIndex", dielectric->GetRefractionIndex()}
    };
}

std::shared_ptr<Dielectric> MaterialSerializer::DielectricFromJson(const nlohmann::json& json)
{
    return std::make_shared<Dielectric>(
        json.at("refractionIndex").get<float>()
    );
}
#ifndef RAYTRACER_JSON_TYPE_H
#define RAYTRACER_JSON_TYPE_H

#include <nlohmann/json.hpp>

#include "Maths/Vec3.h"
#include "Color.h"

/**
 * Provides JSON conversion functions for fundamental
 * mathematical and rendering types.
 */

/**
 * Define serialization support for Vec3
 */
inline void to_json(nlohmann::json& json, const Vec3& vec)
{
	json = nlohmann::json{ vec.x, vec.y, vec.z };
}

/**
 * Define deserialization support for Vec3
 */
inline void from_json(const nlohmann::json& json, Vec3& vec)
{
	if (json.size() != 3)
	{
		throw std::runtime_error("Invalid Vec3 JSON");
	}

	vec = Vec3(
		json.at(0).get<float>(),
		json.at(1).get<float>(),
		json.at(2).get<float>()
	);
}

/**
 * Define serialization support for Color
 */
inline void to_json(nlohmann::json& json, const Color& color)
{
	json = nlohmann::json{ color.r, color.g, color.b };
}

/**
 * Define deserialization support for Color
 */
inline void from_json(const nlohmann::json& json, Color& color)
{
	if (json.size() != 3)
	{
		throw std::runtime_error("Invalid Color JSON");
	}

	color = Color(
		json.at(0).get<float>(),
		json.at(1).get<float>(),
		json.at(2).get<float>()
	);
}

#endif // RAYTRACER_JSON_TYPE_H
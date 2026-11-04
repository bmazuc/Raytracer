#include "Scene/Hittable.h"
#include "Ray.h"

void Hittable::SetFaceNormal(const Ray& ray, const Vec3& outwardNormal, HitInfo& hitInfo) const
{
	hitInfo.frontFace = Vec3::Dot(ray.direction, outwardNormal) < 0;
	hitInfo.normal = hitInfo.frontFace ? outwardNormal : -outwardNormal;
}
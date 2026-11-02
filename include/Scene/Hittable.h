#ifndef __HITTABLE_H_INCLUDED__
#define __HITTABLE_H_INCLUDED__

#include "Maths/Vec3.h"
#include "Maths/Interval.h"

struct Ray;
class Material;


struct HitInfo
{
public:
	Vec3 point;
	Vec3 normal;
	std::shared_ptr<Material> material;
	float t;
	bool frontFace;
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const = 0;

protected:
	void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal, HitInfo& hitInfo) const;
};

#endif // __HITTABLE_H_INCLUDED__
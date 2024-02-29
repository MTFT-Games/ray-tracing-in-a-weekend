#pragma once

#include "Ray.h"
#include "utility.h"

class Material;

class HitRecord {
public:
	Point3 position;
	Vec3 normal;
	shared_ptr<Material> material;
	double t;
	bool frontFace;
	
	// Sets normal and front face, assumes normalized normal
	void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
		frontFace = Dot(ray.Direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const Ray& ray, Interval validT, HitRecord& record) const = 0;
};
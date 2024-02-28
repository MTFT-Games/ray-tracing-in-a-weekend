#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Point3& origin, const Vec3& direction) : 
		origin(origin), direction(direction) {}

	Point3 Origin() const { return origin; }
	Vec3 Direction() const { return direction; }

	Point3 At(double t) const {
		return origin + t * direction;
	}

private:
	Point3 origin;
	Vec3 direction;
};
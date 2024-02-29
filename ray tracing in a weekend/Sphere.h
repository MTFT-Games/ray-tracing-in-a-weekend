#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable {
public:
	Sphere(Point3 center, double radius, shared_ptr<Material> material) : center(center), radius(radius), material(material) {}

	bool Hit(const Ray& ray, Interval validT, HitRecord& record) const override {
        Vec3 centerToRay = ray.Origin() - center;

        // Quadratic math
        double a = ray.Direction().LengthSquared();
        double halfB = Dot(centerToRay, ray.Direction());
        double c = centerToRay.LengthSquared() - radius * radius;
        double discriminant = halfB * halfB - a * c;

        if (discriminant < 0) {
            return false;
        }
        double sqrtDisc = sqrt(discriminant);

        // Find nearest root that is in range
        double root = (-halfB - sqrtDisc) / a;
        if (!validT.Surrounds(root)) {
            root = (-halfB + sqrtDisc) / a;
            if (!validT.Surrounds(root)) {
                return false;
            }
        }
        
        record.t = root;
        record.position = ray.At(root);
        Vec3 outwardNormal = (record.position - center) / radius;
        record.SetFaceNormal(ray, outwardNormal);
        record.material = material;

        return true;
	}

private:
    Point3 center;
    double radius;
    shared_ptr<Material> material;
};
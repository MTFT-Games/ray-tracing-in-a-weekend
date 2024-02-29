#pragma once

#include "utility.h"

class HitRecord;

class Material {
public:
	virtual ~Material() = default;

	virtual bool Scatter(
		const Ray& incomingRay, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
	Lambertian(const Color& albedo) : albedo(albedo) {}

	bool Scatter(const Ray& incoming, const HitRecord& record, Color& attenuation, Ray& scattered)
		const override {
		Vec3 scatterDirection = record.normal + RandomUnitVector();
		scattered = Ray(record.position, scatterDirection);
	}
};
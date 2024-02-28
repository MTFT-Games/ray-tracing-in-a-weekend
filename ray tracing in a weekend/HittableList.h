#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
	std::vector<shared_ptr<Hittable>> objects;

	HittableList() {};
	HittableList(shared_ptr<Hittable> object) { Add(object); }

	void Clear() { objects.clear(); }

	void Add(shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	bool Hit(const Ray& ray, Interval validT, HitRecord& record) const override {
		HitRecord tempRecord;
		bool hitAnything = false;
		double closestSoFar = validT.max;

		for (const shared_ptr<Hittable>& object : objects) {
			if (object->Hit(ray, Interval(validT.min, closestSoFar), tempRecord)) {
				hitAnything = true;
				closestSoFar = tempRecord.t;
				record = tempRecord;
			}
		}

		return hitAnything;
	}
};
#pragma once
#include "ray.h"

class material;

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material* mat_ptr;
};

class hittable {
public:
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) = 0;
};


#pragma once
#include "ray.h"

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
};

class hittable {
public:
	virtual bool hit(const ray& r,float tmin,float tmax, hit_record& rec) const;
};


#pragma once
#include "ray.h"
#include "vec3.h"


vec3 reflect(const vec3& v, const vec3& n) {
	//reflected ray is v + 2B
	//B=dot(v,n)
	//since v is in opposite dir, use -ve 
	return v - 2 * dot(v, n) * n;
};

class material {
public:
	virtual bool scatter(const ray& r_in ,const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
	lambertian(const vec3& a): albedo(a) {};
	bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		//TODO: Add Scatter for Lamberetain SHading Model
		// I = cos(theta) = unit(globalizednormal)*unit(lightdirection);
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target-rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};

class metal : public material {
public:
	metal(const vec3 a) : albedo(a) {};

	bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
		vec3 reflected = reflect(unit_vector(r_in.direction()) , rec.normal);
		scattered = ray(rec.p,reflected);
		attenuation = albedo;
		return (dot( scattered.direction() ,rec.normal)>0);
	}
	vec3 albedo;
};
#pragma once
#include "ray.h"
#include "vec3.h"


vec3 reflect(const vec3& v, const vec3& n) {
	//reflected ray is v + 2B
	//B=dot(v,n)
	//since v is in opposite dir, use -ve 
	return v - 2 * dot(v, n) * n;
};

//TODO: add refraction
bool refract(const vec3& v,const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv,n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if (discriminant > 0) {
		//update refracted 
		refracted = ni_over_nt*(uv-n*dt) - n*sqrt(discriminant);
		return true;
	}
	else {
		return false;
	}
}

//polynomial approximation by Christophe Schlick
float schlick(float cosine, float	red_idx) {
	float r0 = (1-red_idx)/(1+red_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

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
	metal(const vec3 a,float f) : albedo(a) {
		if (f < 1) fuzz = f; else fuzz = 1;
	};

	bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
		vec3 reflected = reflect(unit_vector(r_in.direction()) , rec.normal);
		scattered = ray(rec.p,reflected);
		attenuation = albedo;
		return (dot( scattered.direction() ,rec.normal)>0);
	}
	vec3 albedo;
	float fuzz;
};

class dielectric : public material {
public:
	dielectric(float x) : ref_idx(x) {};
	bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(),rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0,1.0,1.0);
		vec3 refracted;

		float reflect_prob;
		float cosine;

		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx*dot(r_in.direction(),rec.normal)/r_in.direction().length();


		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0/ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}

		if (refract(r_in.direction(),outward_normal,ni_over_nt,refracted)) {
			reflect_prob = schlick(cosine,ref_idx);
		}
		else {
			reflect_prob = 1.0;
		}

		if (random_double() < reflect_prob) {
			scattered = ray(rec.p, reflected);
		}
		else {
			scattered = ray(rec.p, refracted);
		}
		return true;
	}

	float ref_idx;//refractive index
};
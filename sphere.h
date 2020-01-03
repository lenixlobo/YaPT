#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(vec3 cen, float r) : center(cen),radius(r)  {};
	virtual bool hit(const ray& r,float tmin, float tmax, hit_record& rec) ;
	vec3 center;
	float radius;
};

bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec)  {
	//Equation : (p(t) - C)*(p(t) - C) = R*R
	// point on a sphere with center C; (X-Cx)*(X-Cx) + (Y-Cy)*(Y-Cy) + (Z-Cz)*(Z-Cz) = R*R
	// t2dot(B,B)+2tdot(B,A−C)+dot(A−C,A−C)−R2=0
	//objective: find t(the point at which the intersection happens)
	vec3 oc = r.origin() - center;
	float  a = dot(r.direction(), r.direction());
	float  b = dot(oc,r.direction());
	float  c = dot(oc,oc) - radius*radius;
	float discriminant = b*b - a*c;

	if (discriminant > 0) {
		float temp = ( -b-sqrt(discriminant))/(a);
		if (temp<tmax && temp>tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center)/radius;
			return true;
		}

		temp = ( -b+sqrt(discriminant) )/(a);
		if (temp<tmax && temp>tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}
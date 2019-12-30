#pragma once
#include "hittable.h"

class hittablelist : public hittable {

public:
	hittablelist() {};
	hittablelist(hittable** hitl, int n)  { hitlist = hitl;  list_size = n; };

	bool hit(const ray& r, float tmin, float tmax, hit_record& rec) ;
	hittable** hitlist;
	int list_size;
};

bool hittablelist::hit(const ray& r, float tmin, float tmax, hit_record& rec)  {

	hit_record temp_record;
	
	bool hit_anything = false;
	double closest_so_far = tmax;
	for (int i = 0; i < list_size; i++) {
		if (hitlist[i]->hit(r, tmin, closest_so_far, temp_record)) {
			hit_anything = true;
			closest_so_far = temp_record.t;
			rec = temp_record;
		}
	}

	return hit_anything;
}
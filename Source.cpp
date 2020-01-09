
#include <iostream>
#include <fstream>
#include<math.h>
#include<cfloat>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "hittablelist.h"
#include "sphere.h"
#include "camera.h"
#include "randomize.h"
#include "material.h"

/*
float hit_sphere(const vec3& center,float radius, const ray& r) {
	//Equation : (p(t) - C)*(p(t) - C) = R*R
	// point on a sphere with center C; (X-Cx)*(X-Cx) + (Y-Cy)*(Y-Cy) + (Z-Cz)*(Z-Cz) = R*R
	// t2dot(B,B)+2tdot(B,A−C)+dot(A−C,A−C)−R2=0
	//objective: find t(the point at which the intersection happens)
	
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(),r.direction());
	float b = 2 * dot(oc,r.direction());
	float c = dot(oc,oc) - radius*radius;
	float discriminant = b * b - 4*a*c;;
	if (discriminant < 0) { return -1.0; }
	else {
		return float( -b - sqrt( discriminant )) / (2.0 * a); //use - instead of +,to find the smaller root 
	}


}
*/

vec3 color3(const ray& r,hittable* world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation*color3(scattered, world, depth+1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());//unit_vector : respresents the direction of a ray
		float t = 0.5 * (unit_direction.y() + 1.0); // t : 
		// lerp : linear interpolation between white and blue;
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.4, 1.0);
	}
}

/*
vec3 color2(const ray& r,hittable* world) {
	
	hit_record rec;

	if (world->hit(r, 0.0, FLT_MAX , rec)) {
		//hit object render
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color2(ray(rec.p, target - rec.p), world);
		//return 0.5*vec3(rec.normal.x() + 1 , rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		//handles bg
		vec3 unit_direction = unit_vector(r.direction());//unit_vector : respresents the direction of a ray
		float t = 0.5 * (unit_direction.y() + 1.0); // t : 
		// lerp : linear interpolation between white and blue;
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.4, 1.0);
	}

}
*/
/*
vec3 color(const ray& r) {
	

	float t = hit_sphere(vec3(0,0,-1),0.5,r);
	if (t > 0.0) {
		vec3 N = unit_vector( r.point_at_parameter(t)-vec3(0,0,-1));
		return 0.5*vec3(N.x()+1,N.y()+1,N.z()+1 );
	}

	vec3 unit_direction = unit_vector( r.direction() );//unit_vector : respresents the direction of a ray
	t = 0.5*(unit_direction.y() + 1.0); // t : 
	// lerp : linear interpolation between white and blue;
	return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5,1.0,1.0);
}
*/
void write_jpg() {
	//std::cout << "Hello World" << std::endl;
	int nx = 500;
	int ny = 250;
	int ns = 100;

	//define coordinate system
	/*vec3 lower_left_corner(-2.0 ,-1.0 ,-1.0);
	vec3 horizontal(4.0 ,0.0 ,0.0);
	vec3 vertical(0.0 ,2.0 ,0.0);
	vec3 origin(0.0 ,0.0 ,0.0);
	*/

	std::cout << " Creating objects"<<std::endl;
	
	//create list of objects
	hittable *list[4];
	//list[0] = new sphere (vec3(0, 0, -1) ,0.5);
	//list[1] = new sphere (vec3(0, -100.5, -1) ,100);
	list[0] = new sphere( vec3(0, 0, -1) , 0.5 ,new lambertian(vec3( 0.8, 0.3, 0.3) ) );
	list[1] = new sphere( vec3(0, -100.5, -1) , 100 ,new lambertian(vec3( 0.8, 0.8, 0.0) ) );
	list[2] = new sphere( vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2) ) );
	list[3] = new sphere( vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8) ) );
	hittable* world = new hittablelist(list	,4);

	camera cam;

	uint8_t* pixels = new uint8_t[nx*ny*3];

	//std::cout << "P3\n" <<nx<<" "<<ny<<"\n255\n";
	int index = 0;
	for (int col = ny-1; col >=0; col--) {
		for (int row = 0; row < nx; row++) {
			
			vec3 colors(0, 0, 0);
			std::cout << "Row: " << row << "\t Col: " << col << std::endl;
			for (int s=0 ; s < ns; s++) {
				
				float u = float(row + random_double()) / float(nx);
				float v = float(col + random_double()) / float(ny);
				
				ray r = cam.get_ray(u,v);
				colors += color3(r, world,0);
			}

			colors /= float(ns);

				float ir = int(255 * colors[0]);
				float ig = int(255 * colors[1]);
				float ib = int(255 * colors[2]);
					
				pixels[index++] = ir;
				pixels[index++] = ig;
				pixels[index++] = ib;

		}
	}

	stbi_write_jpg("test.jpg", nx, ny, 3, pixels, 100);
	//int stbi_write_png(char const *filename, int w, int h, int comp (Y,YA,RGB,RGBA), const void *data, int stride_in_bytes);	
}


int main() {
	
	std::cout << "Rendering Image "<<std::endl;
	write_jpg();
	std::cout << "Rendered Image test.png";

	return 0;
}
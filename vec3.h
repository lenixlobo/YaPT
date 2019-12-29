#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>

class vec3 {
public:

	vec3() { }
	vec3(float x0, float x1, float x2) { xx[0] = x0, xx[1] = x1, xx[2] = x2;  }
	inline float x() { return xx[0]; }
	inline float y() { return xx[1]; }
	inline float z() { return xx[2]; }
	
	inline float r() { return xx[0]; }
	inline float g() { return xx[1]; }
	inline float b() { return xx[2]; }

	inline float length() const { return sqrt( xx[0] * xx[0] + xx[1] * xx[1] + xx[2] * xx[2] ); }
	inline float squaredlength() const { return xx[0] * xx[0] + xx[1] * xx[1] + xx[2] * xx[2]; }

	inline const vec3& operator+() const { return *this; }
	inline const vec3& operator-() const { return vec3( -xx[0], -xx[1], -xx[2]); }
	
	inline float operator[](int i) const { return xx[i]; }
	inline float& operator[](int i) { return xx[i]; }

	inline vec3& operator +=(const vec3 v2);
	inline vec3& operator -=(const vec3 v2);
	inline vec3& operator *=(const vec3 v2);
	inline vec3& operator /=(const vec3 v2);

	inline vec3& operator *=(float t);
	inline vec3& operator /=(float t);

	inline void make_unit_vector();
	float xx[3];
};


inline std::istream& operator>> (std::istream& is, vec3& v)
{
	is >> v.xx[0] >> v.xx[1] >> v.xx[2];
	return is;
}

inline std::ostream& operator<< (std::ostream& os, vec3& v)
{
	os << v.xx[0] << " " << v.xx[1] << " " << v.xx[2];
	return os;
}

inline void vec3::make_unit_vector()
{
	float k = 1 / sqrt(xx[0] * xx[0] + xx[1] * xx[1] + xx[2] * xx[2]);
	xx[0] *= k;	xx[1] *= k;	xx[2] *= k;
}



inline vec3 operator +(vec3 v1, vec3 v2) {
	return vec3(v1.xx[0] + v2.xx[0], v1.xx[1] + v2.xx[1], v1.xx[2] + v2.xx[2]);
}

inline vec3 operator -(vec3 v1, vec3 v2) {
	return vec3(v1.xx[0] - v2.xx[0], v1.xx[1] - v2.xx[1], v1.xx[2] - v2.xx[2]);
}

inline vec3 operator *(vec3 v, float t) {
	return vec3(v.xx[0] * t, v.xx[1] * t, v.xx[2] * t);
}

inline vec3 operator* (vec3 v1, vec3 v2) {
	return vec3(v1.xx[0] * v2.xx[0], v1.xx[1] * v2.xx[1], v1.xx[2] * v2.xx[2]);
}

inline vec3 operator *(float t, vec3 v)
{
	return vec3(v.xx[0] * t, v.xx[1] * t, v.xx[2] * t);
}

inline vec3 operator /(vec3 v1, vec3 v2) {
	return vec3(v1.xx[0] / v2.xx[0], v1.xx[1] / v2.xx[1], v1.xx[2] / v2.xx[2]);
}


inline vec3 operator /(vec3 v, float t) {
	return vec3(v.xx[0] / t, v.xx[1] / t, v.xx[2] / t);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}


inline float dot(const vec3 v1, const vec3 v2) {
	return v1.xx[0] * v2.xx[0] + v1.xx[1] * v2.xx[1] + v1.xx[2] * v2.xx[2];
}

inline vec3 cross(const vec3 v1, const  vec3 v2) {
	return vec3(v2.xx[2] * v1.xx[1] - v2.xx[1] * v1.xx[2], v2.xx[0] * v1.xx[2] - v2.xx[2] * v1.xx[0], v1.xx[0] * v2.xx[1] - v2.xx[0] * v1[1]);
}

inline vec3& vec3::operator +=(const vec3 v2)
{
	xx[0] += v2.xx[0];
	xx[1] += v2.xx[1];
	xx[2] += v2.xx[2];

	return *this;
}

inline vec3& vec3::operator -=(const vec3 v2)
{
	xx[0] -= v2.xx[0];
	xx[1] -= v2.xx[1];
	xx[2] -= v2.xx[2];

	return *this;
}

inline vec3& vec3::operator *=(const vec3 v2)
{
	xx[0] *= v2.xx[0];
	xx[1] *= v2.xx[1];
	xx[2] *= v2.xx[2];

	return *this;
}

inline vec3& vec3::operator /=(const vec3 v2) {
	xx[0] /= v2.xx[0];
	xx[1] /= v2.xx[1];
	xx[2] /= v2.xx[2];
	return *this;
}

inline vec3& vec3::operator *=(float t) {
	xx[0] *= t;
	xx[1] *= t;
	xx[2] *= t;
	return *this;
}

inline vec3& vec3::operator /=(float t) {
	float k = 1.0f / t;
	xx[0] *= k;
	xx[1] *= k;
	xx[2] *= k;
	return *this;
}


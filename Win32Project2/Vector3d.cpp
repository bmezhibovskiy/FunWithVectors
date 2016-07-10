#include "Vector3d.h"
#include <math.h>

Vector3d::Vector3d() : Vector3d(0, 0, 0) {}

Vector3d::Vector3d(double x, double y, double z) : x(x), y(y), z(z), w(1) {}

Vector3d Vector3d::operator+(const Vector3d& other) {
	return Vector3d(x + other.x, y + other.y, z + other.z);
}

Vector3d Vector3d::operator-(const Vector3d& other) {
	return Vector3d(x - other.x, y - other.y, z - other.z);
}

Vector3d Vector3d::operator*(double s) {
	return Vector3d(x * s, y * s, z * s);
}

double Vector3d::lengthSquared() {
	return x*x + y*y + z*z;
}

double Vector3d::length() {
	return sqrt(lengthSquared());
}

Vector3d Vector3d::normalized() {
	return Vector3d(x, y, z) * (1.0 / length());
}

double Vector3d::dot(const Vector3d& other) {
	return x*other.x + y*other.y + z*other.z;
}

Vector3d Vector3d::cross(const Vector3d& other) {
	double x = y*other.z - z*other.y;
	double y = z*other.x - x*other.z;
	double z = x*other.y - y*other.x;
	return Vector3d(x, y, z);
}


Vector3d operator*(double s, const Vector3d& v) {
	return Vector3d(v.x * s, v.y * s, v.z * s);
}

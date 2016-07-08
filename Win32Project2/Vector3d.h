#pragma once

class Vector3d {
public:
	double x, y, z;

	Vector3d::Vector3d();
	Vector3d::Vector3d(double x, double y, double z);

	Vector3d Vector3d::operator+(const Vector3d& other);
	Vector3d Vector3d::operator-(const Vector3d& other);
	Vector3d Vector3d::operator*(double s);
	double Vector3d::lengthSquared();
	double Vector3d::length();
	Vector3d Vector3d::normalized();
	double Vector3d::dot(const Vector3d& other);
	Vector3d Vector3d::cross(const Vector3d& other);
};

Vector3d operator*(double s, const Vector3d& v);

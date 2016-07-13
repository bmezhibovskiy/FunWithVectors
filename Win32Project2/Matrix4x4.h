#pragma once
#include <vector>
#include "Vector3d.h"

class Matrix4x4 {
	std::vector<std::vector<double> > matrix;
public:
	static Matrix4x4 identity();
	static Matrix4x4 rotationZ(double angle); //angle is in radians
	static Matrix4x4 scale(const Vector3d& scaleBy);
	static Matrix4x4 translate(const Vector3d& translateBy);

	Matrix4x4(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44);

	Vector3d operator*(const Vector3d& v);
	Matrix4x4 operator*(const Matrix4x4& m2);
	Matrix4x4 operator*(double s);

	Matrix4x4 transpose();
	double determinant();
	bool isInvertible();
	Matrix4x4 cofactor();
	Matrix4x4 adjoint();
	Matrix4x4 inverse();

	friend Matrix4x4 operator*(double s, const Matrix4x4& m);

};
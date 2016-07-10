#include <vector>
using namespace std;
#include "Matrix4x4.h"
#include "Vector3d.h"

Matrix4x4 Matrix4x4::identity() {
	return Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::rotationZ(double angle) {
	return Matrix4x4(cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::scale(Vector3d scaleBy) {
	return Matrix4x4(scaleBy.x, 0, 0, 0, 0, scaleBy.y, 0, 0, 0, 0, scaleBy.z, 0, 0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::translate(Vector3d translateBy) {
	return Matrix4x4(1, 0, 0, translateBy.x, 0, 1, 0, translateBy.y, 0, 0, 1, translateBy.z, 0, 0, 0, 1);
}

Matrix4x4::Matrix4x4(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44) {
	vector<double> row1;
	row1.push_back(m11);
	row1.push_back(m12);
	row1.push_back(m13);
	row1.push_back(m14);
	vector<double> row2;
	row2.push_back(m21);
	row2.push_back(m22);
	row2.push_back(m23);
	row2.push_back(m24);
	vector<double> row3;
	row3.push_back(m31);
	row3.push_back(m32);
	row3.push_back(m33);
	row3.push_back(m34);
	vector<double> row4;
	row4.push_back(m41);
	row4.push_back(m42);
	row4.push_back(m43);
	row4.push_back(m44);
	matrix.push_back(row1);
	matrix.push_back(row2);
	matrix.push_back(row3);
	matrix.push_back(row4);
}

Vector3d Matrix4x4::operator*(Vector3d v) {
	double x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3] * v.w;
	double y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3] * v.w;
	double z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3] * v.w;
	double w = matrix[3][0] * v.x + matrix[3][1] * v.y + matrix[3][2] * v.z + matrix[3][3] * v.w;
	Vector3d result(x, y, z);
	result.w = w;
	return result;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 m2) {
	return Matrix4x4(
		matrix[0][0] * m2.matrix[0][0] + matrix[0][1] * m2.matrix[1][0] + matrix[0][2] * m2.matrix[2][0] + matrix[0][3] * m2.matrix[3][0],
		matrix[0][0] * m2.matrix[0][1] + matrix[0][1] * m2.matrix[1][1] + matrix[0][2] * m2.matrix[2][1] + matrix[0][3] * m2.matrix[3][1],
		matrix[0][0] * m2.matrix[0][2] + matrix[0][1] * m2.matrix[1][2] + matrix[0][2] * m2.matrix[2][2] + matrix[0][3] * m2.matrix[3][2],
		matrix[0][0] * m2.matrix[0][3] + matrix[0][1] * m2.matrix[1][3] + matrix[0][2] * m2.matrix[2][3] + matrix[0][3] * m2.matrix[3][3],

		matrix[1][0] * m2.matrix[0][0] + matrix[1][1] * m2.matrix[1][0] + matrix[1][2] * m2.matrix[2][0] + matrix[1][3] * m2.matrix[3][0],
		matrix[1][0] * m2.matrix[0][1] + matrix[1][1] * m2.matrix[1][1] + matrix[1][2] * m2.matrix[2][1] + matrix[1][3] * m2.matrix[3][1],
		matrix[1][0] * m2.matrix[0][2] + matrix[1][1] * m2.matrix[1][2] + matrix[1][2] * m2.matrix[2][2] + matrix[1][3] * m2.matrix[3][2],
		matrix[1][0] * m2.matrix[0][3] + matrix[1][1] * m2.matrix[1][3] + matrix[1][2] * m2.matrix[2][3] + matrix[1][3] * m2.matrix[3][3],

		matrix[2][0] * m2.matrix[0][0] + matrix[2][1] * m2.matrix[1][0] + matrix[2][2] * m2.matrix[2][0] + matrix[2][3] * m2.matrix[3][0],
		matrix[2][0] * m2.matrix[0][1] + matrix[2][1] * m2.matrix[1][1] + matrix[2][2] * m2.matrix[2][1] + matrix[2][3] * m2.matrix[3][1],
		matrix[2][0] * m2.matrix[0][2] + matrix[2][1] * m2.matrix[1][2] + matrix[2][2] * m2.matrix[2][2] + matrix[2][3] * m2.matrix[3][2],
		matrix[2][0] * m2.matrix[0][3] + matrix[2][1] * m2.matrix[1][3] + matrix[2][2] * m2.matrix[2][3] + matrix[2][3] * m2.matrix[3][3],

		matrix[3][0] * m2.matrix[0][0] + matrix[3][1] * m2.matrix[1][0] + matrix[3][2] * m2.matrix[2][0] + matrix[3][3] * m2.matrix[3][0],
		matrix[3][0] * m2.matrix[0][1] + matrix[3][1] * m2.matrix[1][1] + matrix[3][2] * m2.matrix[2][1] + matrix[3][3] * m2.matrix[3][1],
		matrix[3][0] * m2.matrix[0][2] + matrix[3][1] * m2.matrix[1][2] + matrix[3][2] * m2.matrix[2][2] + matrix[3][3] * m2.matrix[3][2],
		matrix[3][0] * m2.matrix[0][3] + matrix[3][1] * m2.matrix[1][3] + matrix[3][2] * m2.matrix[2][3] + matrix[3][3] * m2.matrix[3][3]
		);
}
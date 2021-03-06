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

Matrix4x4 Matrix4x4::scale(const Vector3d& scaleBy) {
	return Matrix4x4(scaleBy.x, 0, 0, 0, 0, scaleBy.y, 0, 0, 0, 0, scaleBy.z, 0, 0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::translate(const Vector3d& translateBy) {
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

Vector3d Matrix4x4::operator*(const Vector3d& v) {
	double x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3] * v.w;
	double y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3] * v.w;
	double z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3] * v.w;
	double w = matrix[3][0] * v.x + matrix[3][1] * v.y + matrix[3][2] * v.z + matrix[3][3] * v.w;
	Vector3d result(x, y, z);
	result.w = w;
	return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m2) {
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

Matrix4x4 Matrix4x4::operator*(double s) {
	return Matrix4x4(matrix[0][0] * s, matrix[0][1] * s, matrix[0][2] * s, matrix[0][3] * s,
		matrix[1][0] * s, matrix[1][1] * s, matrix[1][2] * s, matrix[1][3] * s,
		matrix[2][0] * s, matrix[2][1] * s, matrix[2][2] * s, matrix[2][3] * s,
		matrix[3][0] * s, matrix[3][1] * s, matrix[3][2] * s, matrix[3][3] * s);
}

Matrix4x4 operator*(double s, const Matrix4x4& m) {
	return Matrix4x4(m.matrix[0][0] * s, m.matrix[0][1] * s, m.matrix[0][2] * s, m.matrix[0][3] * s,
		m.matrix[1][0] * s, m.matrix[1][1] * s, m.matrix[1][2] * s, m.matrix[1][3] * s,
		m.matrix[2][0] * s, m.matrix[2][1] * s, m.matrix[2][2] * s, m.matrix[2][3] * s,
		m.matrix[3][0] * s, m.matrix[3][1] * s, m.matrix[3][2] * s, m.matrix[3][3] * s);
}

Matrix4x4 Matrix4x4::transpose() {
	return Matrix4x4(matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
		matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1], 
		matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2], 
		matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
}

bool Matrix4x4::isInvertible() {
	return determinant() != 0;
}

Matrix4x4 Matrix4x4::inverse() {
	if ( !isInvertible() ) {
		throw "Can't invert a matrix that is not invertible!";
	}
	
	
	return (1.0 / determinant()) * adjoint();
}

double Matrix4x4::determinant() {
	return matrix[0][0] * matrix[1][1] * matrix[2][2] * matrix[3][3] +
		matrix[0][0] * matrix[1][2] * matrix[2][3] * matrix[3][1] +
		matrix[0][0] * matrix[1][3] * matrix[2][1] * matrix[3][2] +

		matrix[0][1] * matrix[1][0] * matrix[2][3] * matrix[3][2] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] * matrix[3][3] +
		matrix[0][1] * matrix[1][3] * matrix[2][2] * matrix[3][0] +

		matrix[0][2] * matrix[1][0] * matrix[2][1] * matrix[3][3] +
		matrix[0][2] * matrix[1][1] * matrix[2][3] * matrix[3][0] +
		matrix[0][2] * matrix[1][3] * matrix[2][0] * matrix[3][1] +

		matrix[0][3] * matrix[1][0] * matrix[2][2] * matrix[3][1] +
		matrix[0][3] * matrix[1][1] * matrix[2][0] * matrix[3][2] +
		matrix[0][3] * matrix[1][2] * matrix[2][1] * matrix[3][0] -

		matrix[0][0] * matrix[1][1] * matrix[2][3] * matrix[3][2] -
		matrix[0][0] * matrix[1][2] * matrix[2][1] * matrix[3][3] -
		matrix[0][0] * matrix[1][3] * matrix[2][2] * matrix[3][1] -

		matrix[0][1] * matrix[1][0] * matrix[2][2] * matrix[3][3] -
		matrix[0][1] * matrix[1][2] * matrix[2][3] * matrix[3][0] -
		matrix[0][1] * matrix[1][3] * matrix[2][0] * matrix[3][2] -

		matrix[0][2] * matrix[1][0] * matrix[2][3] * matrix[3][1] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] * matrix[3][3] -
		matrix[0][2] * matrix[1][3] * matrix[2][1] * matrix[3][0] -

		matrix[0][3] * matrix[1][0] * matrix[2][1] * matrix[3][2] -
		matrix[0][3] * matrix[1][1] * matrix[2][2] * matrix[3][0] -
		matrix[0][3] * matrix[1][2] * matrix[2][0] * matrix[3][1];
}

Matrix4x4 Matrix4x4::cofactor() {
	Matrix4x4 result = Matrix4x4::identity();
	size_t dim = matrix.size();
	for (size_t row = 0; row < dim; ++row) {
		for (size_t col = 0; col < dim; ++col) {

			//Creating the smaller 3x3 matrix from the rows and cols that are not [row] and [col]
			Matrix4x4 smallerMatrix = Matrix4x4::identity();
			smallerMatrix.matrix.clear();
			for (size_t i = 0; i < dim; ++i) {
				vector<double> smallerMatrixRow;
				if (i != row) {
					for (size_t j = 0; j < dim; ++j) {
						if (j != col) {
							smallerMatrixRow.push_back(matrix[i][j]);
						}
					}
					smallerMatrixRow.push_back(0);
					smallerMatrix.matrix.push_back(smallerMatrixRow);
				}
			}
			//the Dummy row pads our matrix so that the determinant is the same on the inner 3x3 that we care about.
			vector<double> dummyRow;
			dummyRow.push_back(0);
			dummyRow.push_back(0);
			dummyRow.push_back(0);
			dummyRow.push_back(1);
			smallerMatrix.matrix.push_back(dummyRow);
			//

			double sign = 1.0;
			if (row % 2 == 0 && col % 2 == 1 || row % 2 == 1 && col % 2 == 0) {
				sign = -1.0;
			}

			result.matrix[row][col] = sign * smallerMatrix.determinant();

		}
	}
	return result;
}

Matrix4x4 Matrix4x4::adjoint() {
	return cofactor().transpose();
}

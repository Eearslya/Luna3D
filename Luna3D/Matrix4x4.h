#pragma once

#include <array>

#include "Vector3.h"

class Matrix4x4 {
public:
	Matrix4x4() {}
	//Matrix4x4(const std::array<std::array<float, 4>, 4> &_mat) : mat(_mat) {}

	static Matrix4x4 MakeIdentity();
	static Matrix4x4 MakeRotationX(float);
	static Matrix4x4 MakeRotationY(float);
	static Matrix4x4 MakeRotationZ(float);
	static Matrix4x4 MakeTranslation(float, float, float);
	static Matrix4x4 MakeProjection(float, float, float, float);

	static Matrix4x4 PointAt(Vector3 &, Vector3 &, Vector3 &);
	Matrix4x4 QuickInverse() const;

	Matrix4x4 operator*(const Matrix4x4 &i) const;
	Vector3 operator*(const Vector3 &) const;

	//float mat[4][4] = { 0.0f };
	std::array<std::array<float, 4>, 4> mat = { 0 };
};


#include <cmath>

#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::MakeIdentity() {
	Matrix4x4 m;
	m.mat[0][0] = 1.0f;
	m.mat[1][1] = 1.0f;
	m.mat[2][2] = 1.0f;
	m.mat[3][3] = 1.0f;
	return m;
}

Matrix4x4 Matrix4x4::MakeRotationX(float fAngleRad) {
	Matrix4x4 m;
	m.mat[0][0] = 1.0f;
	m.mat[1][1] = cosf(fAngleRad);
	m.mat[1][2] = sinf(fAngleRad);
	m.mat[2][1] = -sinf(fAngleRad);
	m.mat[2][2] = cosf(fAngleRad);
	m.mat[3][3] = 1.0f;
	return m;
}

Matrix4x4 Matrix4x4::MakeRotationY(float fAngleRad) {
	Matrix4x4 m;
	m.mat[0][0] = cosf(fAngleRad);
	m.mat[0][2] = sinf(fAngleRad);
	m.mat[1][1] = 1.0f;
	m.mat[2][0] = -sinf(fAngleRad);
	m.mat[2][2] = cosf(fAngleRad);
	m.mat[3][3] = 1.0f;
	return m;
}

Matrix4x4 Matrix4x4::MakeRotationZ(float fAngleRad) {
	Matrix4x4 m;
	m.mat[0][0] = cosf(fAngleRad);
	m.mat[0][1] = sinf(fAngleRad);
	m.mat[1][0] = -sinf(fAngleRad);
	m.mat[1][1] = cosf(fAngleRad);
	m.mat[2][2] = 1.0f;
	m.mat[3][3] = 1.0f;
	return m;
}

Matrix4x4 Matrix4x4::MakeTranslation(float x, float y, float z) {
	Matrix4x4 m;
	m.mat[0][0] = 1.0f;
	m.mat[1][1] = 1.0f;
	m.mat[2][2] = 1.0f;
	m.mat[3][3] = 1.0f;
	m.mat[3][0] = x;
	m.mat[3][1] = y;
	m.mat[3][2] = z;
	return m;
}

Matrix4x4 Matrix4x4::MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar) {
	float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
	Matrix4x4 matrix;
	matrix.mat[0][0] = fAspectRatio * fFovRad;
	matrix.mat[1][1] = fFovRad;
	matrix.mat[2][2] = fFar / (fFar - fNear);
	matrix.mat[3][2] = (-fFar * fNear) / (fFar - fNear);
	matrix.mat[2][3] = 1.0f;
	matrix.mat[3][3] = 0.0f;
	return matrix;
}

Matrix4x4 Matrix4x4::PointAt(Vector3 &pos, Vector3 &target, Vector3 &up) {
	Matrix4x4 m;

	Vector3 newForward = (target - pos).Normal();
	Vector3 newUp = (up - (newForward * up.Dot(newForward))).Normal();
	Vector3 newRight = newUp.Cross(newForward);

	m.mat[0][0] = newRight.x;   m.mat[0][1] = newRight.y;   m.mat[0][2] = newRight.z;   m.mat[0][3] = 0.0f;
	m.mat[1][0] = newUp.x;      m.mat[1][1] = newUp.y;      m.mat[1][2] = newUp.z;      m.mat[1][3] = 0.0f;
	m.mat[2][0] = newForward.x; m.mat[2][1] = newForward.y; m.mat[2][2] = newForward.z; m.mat[2][3] = 0.0f;
	m.mat[3][0] = pos.x;        m.mat[3][1] = pos.y;        m.mat[3][2] = pos.z;        m.mat[3][3] = 1.0f;

	return m;
}

Matrix4x4 Matrix4x4::QuickInverse() const {
	Matrix4x4 m;
	m.mat[0][0] = mat[0][0]; m.mat[0][1] = mat[1][0]; m.mat[0][2] = mat[2][0]; m.mat[0][3] = 0.0f;
	m.mat[1][0] = mat[0][1]; m.mat[1][1] = mat[1][1]; m.mat[1][2] = mat[2][1]; m.mat[1][3] = 0.0f;
	m.mat[2][0] = mat[0][2]; m.mat[2][1] = mat[1][2]; m.mat[2][2] = mat[2][2]; m.mat[2][3] = 0.0f;
	m.mat[3][0] = -(mat[3][0] * m.mat[0][0] + mat[3][1] * m.mat[1][0] + mat[3][2] * m.mat[2][0]);
	m.mat[3][1] = -(mat[3][0] * m.mat[0][1] + mat[3][1] * m.mat[1][1] + mat[3][2] * m.mat[2][1]);
	m.mat[3][2] = -(mat[3][0] * m.mat[0][2] + mat[3][1] * m.mat[1][2] + mat[3][2] * m.mat[2][2]);
	return m;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &i) const {
	Matrix4x4 m;

	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			m.mat[row][col] =
				mat[row][0] * i.mat[0][col] +
				mat[row][1] * i.mat[1][col] +
				mat[row][2] * i.mat[2][col] +
				mat[row][3] * i.mat[3][col];
		}
	}

	return m;
}

Vector3 Matrix4x4::operator*(const Vector3 &i) const {
	return Vector3(
		i.x * mat[0][0] + i.y * mat[1][0] + i.z * mat[2][0] + i.w * mat[3][0],
		i.x * mat[0][1] + i.y * mat[1][1] + i.z * mat[2][1] + i.w * mat[3][1],
		i.x * mat[0][2] + i.y * mat[1][2] + i.z * mat[2][2] + i.w * mat[3][2],
		i.x * mat[0][3] + i.y * mat[1][3] + i.z * mat[2][3] + i.w * mat[3][3]
	);
}

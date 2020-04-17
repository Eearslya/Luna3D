#pragma once

class Vector3 {
public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f) {}
	Vector3(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	static Vector3 Zero();

	Vector3 Normal();

	Vector3 Cross(const Vector3 &) const;
	float Dot(const Vector3 &) const;
	float Magnitude() const;

	Vector3 operator+(const Vector3 &) const;
	Vector3 operator-(const Vector3 &) const;
	Vector3 operator*(const Vector3 &) const;
	Vector3 operator*(const float &) const;
	Vector3 operator/(const Vector3 &) const;
	Vector3 operator/(const float &) const;

	Vector3 &operator+=(const Vector3 &);
	Vector3 &operator-=(const Vector3 &);
	Vector3 &operator*=(const Vector3 &);
	Vector3 &operator*=(const float &);
	Vector3 &operator/=(const Vector3 &);
	Vector3 &operator/=(const float &);

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
};


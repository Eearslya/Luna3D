#include <cmath>

#include "Vector3.h"

Vector3 Vector3::Zero() {
	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Normal() {
	float mag = Magnitude();
	return Vector3(x / mag, y / mag, z / mag);
}

Vector3 Vector3::Cross(const Vector3 &other) const {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

float Vector3::Dot(const Vector3 &other) const {
	return x * other.x + y * other.y + z * other.z;
}

float Vector3::Magnitude() const {
	return sqrtf(this->Dot(*this));
}

Vector3 Vector3::operator+(const Vector3 &other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const Vector3 &other) const {
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const float &value) const {
	return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator/(const Vector3 &other) const {
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator/(const float &value) const {
	return Vector3(x / value, y / value, z / value);
}

Vector3 &Vector3::operator+=(const Vector3 &other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &other) {
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vector3 &Vector3::operator*=(const float &value) {
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

Vector3 &Vector3::operator/=(const Vector3 &other) {
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vector3 &Vector3::operator/=(const float &value) {
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}

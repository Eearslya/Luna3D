#include "Triangle.h"

Vector3 Triangle::Normal() const {
	Vector3 lineA, lineB, normal;
	lineA = b - a;
	lineB = c - a;
	normal = lineA.Cross(lineB).Normal();
	return normal;
}

Triangle Triangle::operator+(const Vector3 &translate) const {
	return Triangle(a + translate, b + translate, c + translate);
}

Triangle Triangle::operator*(const Vector3 &scale) const {
	return Triangle(a * scale, b * scale, c * scale);
}

Triangle Triangle::operator*(const float &scale) const {
	return Triangle(a * scale, b * scale, c * scale);
}

Triangle Triangle::operator*(const Matrix4x4 &mat) const {
	return Triangle(mat * a, mat * b, mat * c);
}

Vector3 &Triangle::operator[](unsigned short i) {
	switch (i) {
	case 0: return a; break;
	case 1: return b; break;
	case 2: return c; break;
	default: throw "Attempted to index invalid triangle vertex!";
	}
}

Triangle &Triangle::operator+=(const Vector3 &translate) {
	this->a += translate;
	this->b += translate;
	this->c += translate;
	return *this;
}

Triangle &Triangle::operator*=(const Vector3 &scale) {
	this->a *= scale;
	this->b *= scale;
	this->c *= scale;
	return *this;
}

Triangle &Triangle::operator*=(const float &scale) {
	this->a *= scale;
	this->b *= scale;
	this->c *= scale;
	return *this;
}

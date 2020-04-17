#pragma once

#include "Matrix4x4.h"
#include "olcPixelGameEngine.h"
#include "Vector3.h"

class Triangle {
public:
	Triangle() : a(Vector3::Zero()), b(Vector3::Zero()), c(Vector3::Zero()), color(olc::WHITE) {}
	Triangle(Vector3 _a, Vector3 _b, Vector3 _c) : a(_a), b(_b), c(_c), color(olc::WHITE) {}
	Triangle(const Triangle &t) : a(t.a), b(t.b), c(t.c), color(t.color) {}

	Vector3 Normal() const;

	Triangle operator+(const Vector3 &) const;
	Triangle operator*(const Vector3 &) const;
	Triangle operator*(const float &) const;
	Triangle operator*(const Matrix4x4 &) const;
	Vector3 &operator[](unsigned short);

	Triangle &operator+=(const Vector3 &);
	Triangle &operator*=(const Vector3 &);
	Triangle &operator*=(const float &);

	Vector3 a;
	Vector3 b;
	Vector3 c;

	olc::Pixel color = olc::WHITE;
};


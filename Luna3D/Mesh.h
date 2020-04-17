#pragma once

#include <string>
#include <vector>

#include "Triangle.h"

class Mesh {
public:
	Mesh() : tris({}) {}
	Mesh(const std::vector<Triangle> _tris) : tris(_tris) {}
	Mesh(std::string sFilename);

	std::vector<Triangle> tris;
};


#include <fstream>
#include <strstream>

#include "Mesh.h"

Mesh::Mesh(std::string sFilename) {
	std::ifstream file(sFilename);
	if (!file.is_open()) {
		return;
	}

	std::vector<Vector3> vertices;

	while (!file.eof()) {
		char line[128];
		file.getline(line, 128);

		std::strstream str;
		str << line;

		char lineType;

		if (line[0] == 'v') {
			Vector3 vec;
			str >> lineType >> vec.x >> vec.y >> vec.z;
			vertices.push_back(vec);
		}
		else if (line[0] == 'f') {
			int vertIds[3];
			str >> lineType >> vertIds[0] >> vertIds[1] >> vertIds[2];
			tris.push_back(Triangle(vertices[vertIds[0] - 1], vertices[vertIds[1] - 1], vertices[vertIds[2] - 1]));
		}
	}

	file.close();
}
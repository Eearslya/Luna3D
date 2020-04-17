#pragma once

#include "Mesh.h"
#include "olcPixelGameEngine.h"

class Luna3D : public olc::PixelGameEngine {
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float) override;

	void DrawMesh(Mesh);

private:
	unsigned short nRenderMode = 0;
	bool bRenderSurfaces = true;
	bool bRenderWireframes = false;

	Mesh meshCube;
	Mesh meshShip;

	Vector3 vecCamera;
	Vector3 vecLight;

	float fTheta = 0.0f;
};


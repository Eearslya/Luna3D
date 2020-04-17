#include <algorithm>

#include "Luna3D.h"
#include "Matrix4x4.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Vector3.h"

bool Luna3D::OnUserCreate() {
	meshCube = std::vector<Triangle>{
		{ { 0, 0, 0 }, { 0, 1, 0 }, {1, 1, 0} }, { { 0, 0, 0 }, { 1, 1, 0 }, {1, 0, 0} }, // South
		{ { 1, 0, 0 }, { 1, 1, 0 }, {1, 1, 1} }, { { 1, 0, 0 }, { 1, 1, 1 }, {1, 0, 1} }, // East
		{ { 1, 0, 1 }, { 1, 1, 1 }, {0, 1, 1} }, { { 1, 0, 1 }, { 0, 1, 1 }, {0, 0, 1} }, // North
		{ { 0, 0, 1 }, { 0, 1, 1 }, {0, 1, 0} }, { { 0, 0, 1 }, { 0, 1, 0 }, {0, 0, 0} }, // West
		{ { 0, 1, 0 }, { 0, 1, 1 }, {1, 1, 1} }, { { 0, 1, 0 }, { 1, 1, 1 }, {1, 1, 0} }, // Top
		{ { 1, 0, 1 }, { 0, 0, 1 }, {0, 0, 0} }, { { 1, 0, 1 }, { 0, 0, 0 }, {1, 0, 0} }  // Bottom
	};

	meshShip = Mesh("axis.obj");

	return true;
}

bool Luna3D::OnUserUpdate(float fElapsedTime) {
	Clear(olc::BLACK);

	//fTheta += 1.0f * fElapsedTime;

	vecCamera = { 0, 0, 0 };
	vecLight = { 0, 0.5f, -1 };
	vecLight = vecLight.Normal();

	if (GetKey(olc::Key::M).bReleased) {
		nRenderMode = (nRenderMode + 1) % 3;
		if (nRenderMode == 0) bRenderSurfaces = true, bRenderWireframes = false;
		else if (nRenderMode == 1) bRenderSurfaces = true, bRenderWireframes = true;
		else bRenderSurfaces = false, bRenderWireframes = true;
	}

	//DrawMesh(meshCube);
	DrawMesh(meshShip);

	return true;
}

void Luna3D::DrawMesh(Mesh mesh) {
	Matrix4x4 matRotZ = Matrix4x4::MakeRotationZ(fTheta * 0.5f);
	Matrix4x4 matRotX = Matrix4x4::MakeRotationX(fTheta);

	Matrix4x4 matTranslate = Matrix4x4::MakeTranslation(0.0f, 0.0f, 5.0f);

	Matrix4x4 matProjection = Matrix4x4::MakeProjection(90.0f, (float)ScreenHeight() / (float)ScreenWidth(), 0.1f, 1000.0f);

	Matrix4x4 matWorld = Matrix4x4::MakeIdentity();
	matWorld = matRotZ * matRotX;
	matWorld = matWorld * matTranslate;

	std::vector<Triangle> vecTrianglesToRaster;

	for (auto tri : mesh.tris) {
		Triangle triTransformed = tri * matWorld;

		Vector3 triNormal = triTransformed.Normal();
		float dot = triNormal.Dot(triTransformed.a - vecCamera);

		if (dot < 0) {
			olc::Pixel triColor = triTransformed.color;

			float fLightIntensity = triNormal.Dot(vecLight);

			Triangle triProjected = triTransformed * matProjection;
			triProjected[0] = triProjected[0] / triProjected[0].w;
			triProjected[1] = triProjected[1] / triProjected[1].w;
			triProjected[2] = triProjected[2] / triProjected[2].w;
			triProjected += Vector3(1, 1, 0);
			triProjected *= Vector3(0.5f * (float)ScreenWidth(), 0.5f * (float)ScreenHeight(), 1.0f);
			
			triProjected.color.r = (int)((float)triProjected.color.r * fLightIntensity);
			triProjected.color.g = (int)((float)triProjected.color.g * fLightIntensity);
			triProjected.color.b = (int)((float)triProjected.color.b * fLightIntensity);

			vecTrianglesToRaster.push_back(triProjected);
		}
	}

	std::sort(
		vecTrianglesToRaster.begin(),
		vecTrianglesToRaster.end(),
		[](Triangle &t1, Triangle &t2) {
			float z1 = (t1.a.z + t1.b.z + t1.c.z) / 3.0f;
			float z2 = (t2.a.z + t2.b.z + t2.c.z) / 3.0f;
			return z1 > z2;
		}
	);

	for (auto tri : vecTrianglesToRaster) {
		if (bRenderSurfaces) {
			FillTriangle(
				{ (int)tri.a.x, (int)tri.a.y },
				{ (int)tri.b.x, (int)tri.b.y },
				{ (int)tri.c.x, (int)tri.c.y },
				tri.color
			);
		}

		if (bRenderWireframes) {
			DrawTriangle(
				{ (int)tri.a.x, (int)tri.a.y },
				{ (int)tri.b.x, (int)tri.b.y },
				{ (int)tri.c.x, (int)tri.c.y },
				bRenderSurfaces ? olc::BLACK : olc::WHITE
			);
		}
	}
}

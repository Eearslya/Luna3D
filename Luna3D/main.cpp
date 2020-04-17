#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Luna3D.h"

int main(void) {
	Luna3D engine = Luna3D();
	short scale = 1;
	int w = 1280 / scale;
	int h = 960 / scale;
	int x = 1 << (scale - 1);
	//if (engine.Construct(w, h, x, x)) {
	if (engine.Construct(256, 240, 2, 2)) {
		engine.Start();
	}
}
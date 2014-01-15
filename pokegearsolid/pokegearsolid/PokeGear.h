#pragma once

#include "DirectXFrame.h"
#include "dxinput.h"
#include "Map.h"

#define max3d 100
#define max2d 100
#define maxtext 100
#define maxtexture 20
#define maxModels 20

class PokeGear
{
private:
	dxinputframe input;
	DirectXFrame display;
	char keyboard [256];
	DIMOUSESTATE2 mouse;
	cam camera;
	D3Object D3Objs[max3d];
	D3Object Models[maxModels];
	renderInfo Sprites[max2d];
	TextStruct Text[maxtext];
	TextureStruc textures[maxtexture];
	D3DMATERIAL9 materials[10];
public:
	PokeGear();
	void init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed);
	void update();
	void shutdown();
	~PokeGear();
};
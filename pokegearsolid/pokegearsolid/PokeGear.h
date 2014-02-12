#pragma once

#include "DirectXFrame.h"
#include "dxinput.h"
#include "Map.h"
#include "Stealth.h"
#include "PlayerState.h"
#include "Menu.h"
#include "SoundFrame.h"

#define max3d 100
#define max2d 100
#define maxtext 100
#define maxtexture 20
#define maxModels 20

enum gameState
{
	MainMenu,
	stealth,
	story,
	battle,
	GameOver
};
class PokeGear
{
private:
	gameState curState;
	dxinputframe input;
	DirectXFrame display;
	char keyboard [256];
	DIMOUSESTATE2 mouse;
	cam camera;
	D3Object D3Objs[max3d];
	D3Object Models[maxModels];
	renderInfo Sprites[max2d];
	renderInfo curSpri;
	TextStruct Text[maxtext];
	TextureStruc textures[maxtexture];
	D3DMATERIAL9 materials[10];
	PlayerState curPlay;
	Stealth sneak;
	Menu menuSys;
	SoundFrame soundSys;
	bool bCanInput;
	bool menuPushed;
public:
	PokeGear();
	void init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed);
	void update();
	void shutdown();
	~PokeGear();
};
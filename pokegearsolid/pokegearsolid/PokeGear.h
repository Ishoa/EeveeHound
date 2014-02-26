#pragma once

#include "DirectXFrame.h"
#include "dxinput.h"
#include "Map.h"
#include "Stealth.h"
#include "PlayerState.h"
#include "Menu.h"
#include "SoundFrame.h"
#include "Battle.h"
#include "Dio.h"

#define max3d 100
#define max2d 100
#define maxtext 100
#define maxtexture 20
#define maxModels 20
#define maxMat 10


enum gameState
{
	MainMenu,
	stealth,
	story,
	battle,
	GameOver
};

enum battleState {
	BATTLESTART,
	MAIN,
	MOVES,
	WAIT,
	RESOLVEMOVES,
	OVER
};

class PokeGear
{
private:
	gameState curState;
	battleState curBattleState;
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
	D3DMATERIAL9 materials[maxMat];
	PlayerState curPlay;
	Stealth sneak;
	Menu menuSys;
	SoundFrame soundSys;
	bool bCanInput;
	bool bCanInput2;
	bool menuPushed;
	char scenenumber;
	bool newscene;
	Battle battler;
	bool donePlayerAttack;
	bool doneEnemyAttack;
	bool battleover;
	bool playerlost;
	Dio talks;
public:
	PokeGear();
	void init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed);
	void update();
	void shutdown();
	~PokeGear();
};
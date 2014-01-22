#pragma once
#include "Defines.h"

class PlayerState
{
private:
	Pos curPos,rendPos;
	LPCWSTR curMapName;
public:
	PlayerState();
	Pos getPos();
	Pos getRen();
	void setPos(int locx,int locy,int renx,int reny);
	LPCWSTR getMap();
};
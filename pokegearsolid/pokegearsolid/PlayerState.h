#pragma once
#include "Defines.h"
#include <vector>

class PlayerState
{
private:
	Pos curPos,rendPos;
	LPCWSTR curMapName;
	std::vector<bool> watchedDialogs;
	int curHP,maxHP,PP1,PP2,PP3,PP4;
public:
	PlayerState();
	Pos getPos();
	Pos getRen();
	void setHP(int);
	void setMaxHP(int);
	void getPPs(int& move1,int& move2,int& move3,int& move4);
	int getHP();
	int getMaxHP();
	void setPos(int locx,int locy,int renx,int reny);
	bool setSceen(bool[],int arraySize);
	LPCWSTR getMap();
};
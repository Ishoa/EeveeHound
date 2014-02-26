#pragma once
#include "Defines.h"
#include "Pokemon.h"

#include <vector>

class PlayerState
{
private:
	Pos curPos,rendPos;
	LPCWSTR curMapName;
	std::vector<bool> watchedDialogs;
	Pokemon pikachu;
	Pokemon enemy;
	int playermove,enemymove;
public:
	PlayerState();
	Pos getPos();
	Pos getRen();
	void setPikachu(Pokemon);
	void setEnemy(Pokemon);
	Pokemon getPikachu();
	Pokemon getEnemy();
	void decrementPikaPP(int);
	void decrementEnemyPP(int);
	void randomizeEnemy();
	void initPikachu();
	void resolveMoveInOrder(bool);
	void setPlayerMove(int);
	int getPlayerMove();
	void setEnemyMove(int);
	int getEnemyMove();
	void setPos(int locx,int locy,int renx,int reny);
	bool setSceen(bool[],int arraySize);
	LPCWSTR getMap();
};
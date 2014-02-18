#pragma once
#include "EntBase.h"
#define zOffset -0.5f
#include "Map.h"

enum AIDirection
{
	Up,
	Down,
	Left,
	Right,
	WaitUp,
	WaitDown,
	WaitLeft,
	WaitRight
};

struct AINode
{
	AIDirection direction;
	int NumMoves;
	AINode* nextNode;
};

class EntAI : public Entity
{
private:
	D3Object rend;
	int moveLeft, stun;
	AIDirection curDirect;
	AINode* NextNode;
public:
	EntAI();
	EntAI(Pos&,AINode&,void* map);
	bool getRend(D3Object&);
	bool setRend(D3Object&);
	bool isStuned();
	AIDirection curDirection();
	void setStuned(int time);
	Pos getPos();
	bool update(void*);
};
#pragma once
#include "EntBase.h"
#define zOffset -0
#include "Map.h"

enum AIDirection
{
	Up,
	Down,
	Left,
	Right
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
	EntAI(Pos&,AINode&);
	bool getRend(D3Object&);
	bool setRend(D3Object&);
	bool update(void*);
};
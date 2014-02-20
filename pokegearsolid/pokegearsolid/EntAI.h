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
	int nextNodeNum;
	int nodeNum;
};

class EntAI : public Entity
{
private:
	D3Object rend;
	int moveLeft, stun, startNode, nodeNum;
	Pos startPos;
	AIDirection curDirect;
	AINode* NextNode;
public:
	EntAI();
	EntAI(Pos&,AINode&,void* map,int nodeNum);
	void setAI(Pos&,AINode&,void* map,int nodeNum);
	bool getRend(D3Object&);
	bool setRend(D3Object&);
	bool isStuned();
	AIDirection curDirection();
	void setStuned(int time);
	Pos getPos();
	Pos getStartPos();
	int getStartNode();
	bool update(void*);
};
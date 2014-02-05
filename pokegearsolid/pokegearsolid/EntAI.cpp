#include "EntAI.h"

EntAI::EntAI():Entity(AI)
{
	NextNode = 0;
}

EntAI::EntAI(Pos& pos,AINode& node):Entity(AI,pos)
{
	curDirect = node.direction;
	moveLeft = node.NumMoves;
	NextNode = node.nextNode;
}

bool EntAI::update(void* in)
{
	int x,y;
	Map* curmap = (Map*)in;
	Pos po;
	D3DXMATRIX Rot,Trans;
	x = loc.X;
	y = loc.Y;
	D3DXMatrixIdentity(&Rot);
	D3DXMatrixIdentity(&Trans);
	switch(curDirect)
	{
	case Up:
		++y;
		break;
	case Down:
		--y;
		break;
	case Left:
		--x;
		break;
	case Right:
		++x;
		break;
	}
	if(curmap->valid(x,y))
	{
		loc.X = x;
		loc.Y = y;
		--moveLeft;
		curmap->GetWorldPos(x,y,po);
		D3DXMatrixTranslation(&Trans,po.X,po.Y,zOffset);
		rend.matrix = Trans;
		if(moveLeft<=0)
		{
			if(NextNode != 0)
			{
				curDirect = NextNode->direction;
				moveLeft = NextNode->NumMoves;
				NextNode = NextNode->nextNode;
			}
		}
	}
	return true;
}

bool EntAI::getRend(D3Object& out)
{
	out = rend;
	return true;
}

bool EntAI::setRend(D3Object& in)
{
	rend = in;
	return true;
}
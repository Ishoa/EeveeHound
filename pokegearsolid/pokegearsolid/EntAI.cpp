#include "EntAI.h"

EntAI::EntAI():Entity(AI)
{
	NextNode = 0;
}

EntAI::EntAI(Pos& pos,AINode& node,void*in):Entity(AI,pos)
{
	D3DXMATRIX Rot,Trans;
	D3DXMatrixIdentity(&Rot);
	D3DXMatrixIdentity(&Trans);
	Pos po;

	curDirect = node.direction;
	moveLeft = node.NumMoves;
	NextNode = node.nextNode;
	
	Map* curmap = (Map*)in;
	curmap->setNotEmpty(pos.X,pos.Y);

	curmap->GetWorldPos(pos.X,pos.Y,po);
	D3DXMatrixTranslation(&Trans,po.X,po.Y,zOffset);
	rend.matrix = Trans;
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
	curmap->setEmpty(loc.X,loc.Y);
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
	if(curmap->valid(x,y)&&curmap->empt(x,y))
	{
		loc.X = x;
		loc.Y = y;
		--moveLeft;
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
	curmap->GetWorldPos(loc.X,loc.Y,po);
	D3DXMatrixTranslation(&Trans,po.X,po.Y,zOffset);
	rend.matrix = Trans;
	curmap->setNotEmpty(loc.X,loc.Y);
	return true;
}

Pos EntAI::getPos()
{
	return loc;
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
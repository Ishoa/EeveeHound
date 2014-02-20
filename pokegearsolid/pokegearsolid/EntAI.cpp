#include "EntAI.h"

EntAI::EntAI():Entity(AI)
{
	NextNode = 0;
}

EntAI::EntAI(Pos& pos,AINode& node,void*in,int nodeNum):Entity(AI,pos)
{
	D3DXMATRIX Rot,Trans;
	D3DXMatrixIdentity(&Rot);
	D3DXMatrixIdentity(&Trans);
	Pos po;

	startPos = pos;
	startNode = nodeNum;

	curDirect = node.direction;
	moveLeft = node.NumMoves;
	NextNode = node.nextNode;
	
	Map* curmap = (Map*)in;
	curmap->setNotEmpty(pos.X,pos.Y);

	curmap->GetWorldPos(pos.X,pos.Y,po);
	D3DXMatrixTranslation(&Trans,po.X,po.Y,zOffset);
	rend.matrix = Trans;
}

void EntAI::setAI(Pos& pos,AINode& node,void*in,int nodeNum)
{
	D3DXMATRIX Rot,Trans;
	D3DXMatrixIdentity(&Rot);
	D3DXMatrixIdentity(&Trans);
	Pos po;

	loc = pos;

	startPos = pos;
	startNode = nodeNum;

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
	if(stun<=0)
	{
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
		curmap->setNotEmpty(loc.X,loc.Y);
	}
	else
	{
		--stun;
	}

	curmap->GetWorldPos(loc.X,loc.Y,po);
	D3DXMatrixTranslation(&Trans,po.X,po.Y,zOffset);
	switch(curDirect)
	{
	case Down:
		D3DXMatrixRotationZ(&Rot,3.14);
		break;
	case Left:
		D3DXMatrixRotationZ(&Rot,1.57079633);
		break;
	case Right:
		D3DXMatrixRotationZ(&Rot,4.71238898);
		break;
	case WaitDown:
		D3DXMatrixRotationZ(&Rot,3.14);
		break;
	case WaitLeft:
		D3DXMatrixRotationZ(&Rot,1.57079633);
		break;
	case WaitRight:
		D3DXMatrixRotationZ(&Rot,4.71238898);
		break;
	}
	rend.matrix = Rot*Trans;
	return true;
}

void EntAI::setStuned(int time)
{
	stun = time;
}

bool EntAI::isStuned()
{
	if(stun>0)
	{
		return true;
	}
	return false;
}

Pos EntAI::getPos()
{
	return loc;
}

Pos EntAI::getStartPos()
{
	return startPos;
}

int EntAI::getStartNode()
{
	return startNode;
}

AIDirection EntAI::curDirection()
{
	return curDirect;
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
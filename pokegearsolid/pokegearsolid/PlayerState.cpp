#include "PlayerState.h"

PlayerState::PlayerState()
{
	curPos.X = 0;
	curPos.Y = 0;
	curPos.Z = 0;
	rendPos.X = 1;
	rendPos.Y = 1;
	rendPos.Z = 0;
}

Pos PlayerState::getPos()
{
	return curPos;
}

Pos PlayerState::getRen()
{
	return rendPos;
}

void PlayerState::setPos(int locx,int locy,int renx,int reny)
{
	curPos.X = locx;
	curPos.Y = locy;
	curPos.Z = 0;

	rendPos.X = renx;
	rendPos.Y = reny;
	rendPos.Z = 0;
}
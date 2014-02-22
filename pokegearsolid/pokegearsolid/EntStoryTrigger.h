#pragma once
#include "Defines.h"
#include "PlayerState.h"

class EntStoryTrigger
{
private:
	int storyNum;
	Pos loc;
public:
	EntStoryTrigger();
	void setStoryNum(int);
	void setLoc(Pos);
	int update(PlayerState*);
};
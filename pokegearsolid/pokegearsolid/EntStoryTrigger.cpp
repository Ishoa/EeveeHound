#include "EntStoryTrigger.h"
EntStoryTrigger::EntStoryTrigger()
{
	storyNum = 0;
	loc.X = 0;
	loc.Y = 0;
	loc.Z = 0;
}
void EntStoryTrigger::setStoryNum(int num)
{
	storyNum = num;
}

void EntStoryTrigger::setLoc(Pos po)
{
	loc.X = po.X;
	loc.Y = po.Y;
}

bool EntStoryTrigger::update(PlayerState* play)
{
	if(play->sceenNew(storyNum))
	{
		play->setWatched(storyNum);
		return true;
	}
	return false;
}

int EntStoryTrigger::getStoryNum()
{
	return storyNum;
}

Pos EntStoryTrigger::getLoc()
{
	return loc;
}
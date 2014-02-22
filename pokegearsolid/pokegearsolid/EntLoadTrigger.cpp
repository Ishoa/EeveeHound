#include "EntLoadTrigger.h"
#include "Stealth.h"

EntLoadTrigger::EntLoadTrigger()
{
	Pos tempPos;
	mapName = "map.txt";
	tempPos.Z = 0;
	tempPos.X = 0;
	tempPos.Y = 0;
	playLoc = tempPos;
	tempPos.X = 1;
	loc = tempPos;
}
void EntLoadTrigger::setMap(const char* map)
{
	mapName = map;
}
void EntLoadTrigger::setMap(std::string map)
{
	mapName = map;
}
void EntLoadTrigger::setLoc(Pos pos)
{
	 loc = pos;
}
void EntLoadTrigger::setPlayLoc(Pos pos)
{
	playLoc = pos;
}

bool EntLoadTrigger::update(std::string& map,Pos& playerPos)
{
	if(playerPos.X==loc.X&&playerPos.Y==loc.Y)
	{
		map = mapName;
		playerPos = playLoc;
		return true;
	}
	return false;
}

std::string EntLoadTrigger::getMapName()
{
	return mapName;
}
Pos EntLoadTrigger::getPlay()
{
	return playLoc;
}
Pos EntLoadTrigger::getLoc()
{
	return loc;
}
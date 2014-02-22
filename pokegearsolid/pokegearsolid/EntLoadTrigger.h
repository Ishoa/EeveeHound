#pragma once
#include "Defines.h"
#include <string>

class EntLoadTrigger
{
private:
	Pos loc, playLoc;
	std::string mapName;
public:
	EntLoadTrigger();
	void setMap(const char*);
	void setMap(std::string);
	void setLoc(Pos);
	void setPlayLoc(Pos);
	std::string getMapName();
	Pos getPlay();
	Pos getLoc();
	bool update(std::string&,Pos&);
};
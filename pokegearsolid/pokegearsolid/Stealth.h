#include "Map.h"
#include "PlayerState.h"
#include "EntAI.h"
#include <fstream>
#include <vector>

class Stealth
{
private:
	Map CurMap;
	Pos PlayerPos;
	std::vector<EntAI> AIList;
	std::vector<AINode> NodeList;
public:
	Stealth();
	void init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text);
	void Update(char[],bool&,DIMOUSESTATE2&,PlayerState& player);
	bool setPlayPos(PlayerState&,int x,int y);
	void getRend(D3Object[],int& NumObjs,renderInfo[],int& NumSprit,TextStruct[],int& NumText);
	void shutdown();
	~Stealth();
};
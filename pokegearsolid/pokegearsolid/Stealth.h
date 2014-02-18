#include "Map.h"
#include "PlayerState.h"
#include "EntAI.h"
#include <fstream>
#include <vector>
#include "SoundFrame.h"

class Stealth
{
private:
	Map CurMap;
	Pos PlayerPos;
	std::vector<EntAI> AIList;
	std::vector<AINode> NodeList;
public:
	Stealth();
	void init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture gentext, Texture enemyTex, D3Object& enemyModel, D3DMATERIAL9* enemyMat);
	void Update(char[],bool&,DIMOUSESTATE2&,PlayerState& player,SoundFrame*);
	bool setPlayPos(PlayerState&,int x,int y);
	void getRend(D3Object[],int& NumObjs,renderInfo[],int& NumSprit,TextStruct[],int& NumText);
	void shutdown();
	~Stealth();
};
#include "Map.h"
#include "PlayerState.h"
#include "EntAI.h"
#include <fstream>
#include <vector>
#include "SoundFrame.h"
#include "EntLoadTrigger.h"
#include <string>

//const char* map="map.txt";
class Stealth
{
private:
	Map CurMap;
	Pos PlayerPos;
	D3Object baseEnemy;
	std::vector<EntAI> AIList;
	std::vector<AINode> NodeList;
	std::vector<EntLoadTrigger> LoadList;
public:
	Stealth();
	Pos getPlayPos();
	void init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture gentext, Texture enemyTex, D3Object& enemyModel, D3DMATERIAL9* enemyMat);
	int Update(char[],bool&,DIMOUSESTATE2&,PlayerState& player,SoundFrame*);
	bool setPlayPos(PlayerState&,int x,int y);
	void getRend(D3Object[],int& NumObjs,renderInfo[],int& NumSprit,TextStruct[],int& NumText);
	void saveMap(const char* fileName);
	void loadMap(std::string fileName);
	void loadMap(std::string fileName,Texture enemyTex, D3Object& enemyModel, D3DMATERIAL9* enemyMat);
	void shutdown();
	void clearVectors();
	~Stealth();
};
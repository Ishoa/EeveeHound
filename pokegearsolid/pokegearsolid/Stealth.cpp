#include "Stealth.h"
#define stunTime 10
#define viewLength 3

Stealth::Stealth()
{
}

void linkNodes(AINode* node1,AINode* node2)
{
	node1->nextNode = node2;
	node1->nextNodeNum = node2->nodeNum;
}

void Stealth::init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text, Texture enemyTex, D3Object& enemyModel, D3DMATERIAL9* enemyMat)
{
	//Pos temp1,temp2;
	CurMap.CreMap(20,20,floorbase,floormat,wallmat,text);
	//CurMap=Map(20,20,floorbase,floormat,wallmat,text);

	loadMap("map.txt",enemyTex,enemyModel,enemyMat);
	
	//temp1.X=1;
	//temp1.Y=1;
	//temp2.X=1;
	//temp2.Y=5;
	//CurMap.addWall(temp1,temp2);

	//temp1.X=3;
	//temp1.Y=1;
	//temp2.X=3;
	//temp2.Y=5;
	//CurMap.addWall(temp1,temp2);

	//temp1.X = 6;
	//temp1.Y = 5;
	//temp2.X = 4;
	//temp2.Y = 8;
	//CurMap.addWall(temp1,temp2);
	/*
	temp1.X = 7;
	temp1.Y = 5;
	AINode testNode;
	int numNodes = 0;
	testNode.direction = Right;
	testNode.NumMoves = 3;
	testNode.nodeNum = NodeList.size();
	NodeList.push_back(testNode);

	testNode.direction = Left;
	testNode.nodeNum = NodeList.size();
	NodeList.push_back(testNode);

	linkNodes(&NodeList[NodeList.size()-2],&NodeList[NodeList.size()-1]);
	
	linkNodes(&NodeList[NodeList.size()-1],&NodeList[NodeList.size()-2]);

	EntAI testAI(temp1,NodeList[NodeList.size()-2],&CurMap,NodeList.size()-2);

	enemyModel.objMat = enemyMat;
	enemyModel.objTex = enemyTex;
	testAI.setRend(enemyModel);
	AIList.push_back(testAI);*/
	
	/*
	EntLoadTrigger tempLoad;
	Pos tempPos;
	tempPos.X = 1;
	tempPos.Y = 0;
	tempPos.Z = 0;
	tempLoad.setLoc(tempPos);
	tempPos.X = 0;
	tempLoad.setPlayLoc(tempPos);
	tempLoad.setMap("map.txt");
	LoadList.push_back(tempLoad);
	*/

	//saveMap("savetest.txt");
}

int Stealth::Update(char keyboard[],bool& takeinput,DIMOUSESTATE2& mouse,PlayerState& player,SoundFrame* soundSys)
{
	Pos playloc, playren,sightCheck;
	int listLength;
	bool hasMoved = false;
	std::string tempString;
	playloc = player.getPos();
	if(keyboard[DIK_UP]&0x80)
	{
		if(CurMap.valid(playloc.X,playloc.Y + 1)&&takeinput)
		{
			playloc.Y += 1;
			CurMap.GetWorldPos(playloc.X,playloc.Y,playren);
			player.setPos(playloc.X,playloc.Y,playren.X,playren.Y);
			hasMoved = true;
		}
		takeinput = false;
	}
	else if(keyboard[DIK_DOWN]&0x80)
	{
		if(CurMap.valid(playloc.X,playloc.Y - 1)&&takeinput)
		{
			playloc.Y -= 1;
			CurMap.GetWorldPos(playloc.X,playloc.Y,playren);
			player.setPos(playloc.X,playloc.Y,playren.X,playren.Y);
			hasMoved = true;
		}
		takeinput = false;
	}
	else if(keyboard[DIK_LEFT]&0x80)
	{
		if(CurMap.valid(playloc.X-1,playloc.Y)&&takeinput)
		{
			playloc.X -= 1;
			CurMap.GetWorldPos(playloc.X,playloc.Y,playren);
			player.setPos(playloc.X,playloc.Y,playren.X,playren.Y);
			hasMoved = true;
		}
		takeinput = false;
	}
	else if(keyboard[DIK_RIGHT]&0x80)
	{
		if(CurMap.valid(playloc.X+1,playloc.Y)&&takeinput)
		{
			playloc.X += 1;
			CurMap.GetWorldPos(playloc.X,playloc.Y,playren);
			player.setPos(playloc.X,playloc.Y,playren.X,playren.Y);
			hasMoved = true;
		}
		takeinput = false;
	}
	else if(keyboard[DIK_SPACE]&0x80)
	{
		if(takeinput)
		{
			hasMoved = true;
		}
		takeinput = false;
	}
	else if(!takeinput)
	{
		takeinput = true;
	}
	
	if(hasMoved)
	{
		listLength = LoadList.size();
		PlayerPos = player.getPos();
		for(int i = 0;i<listLength;++i)
		{
			if(LoadList[i].update(tempString,PlayerPos))
			{
				loadMap(tempString);
				setPlayPos(player,PlayerPos.X,PlayerPos.Y);
				return 0;
			}
		}
		listLength = AIList.size();
		for(int i = 0; i<listLength;++i)
		{
			if(player.getPos().X == AIList[i].getPos().X&&player.getPos().Y == AIList[i].getPos().Y)
			{
				AIList[i].setStuned(stunTime);
			}
			else
			{
				if(!AIList[i].isStuned())
				{
					sightCheck = AIList[i].getPos();
					for(int v = 0;v<viewLength;++v)
					{
						switch(AIList[i].curDirection())
						{
						case Up:
						case WaitUp:
							sightCheck.Y+=1;
							break;
						case Down:
						case WaitDown:
							sightCheck.Y-=1;
							break;
						case Left:
						case WaitLeft:
							sightCheck.X-=1;
							break;
						case Right:
						case WaitRight:
							sightCheck.X+=1;
							break;
						}
						if(CurMap.valid(sightCheck.X,sightCheck.Y))
						{
							if(sightCheck.X==playloc.X&&sightCheck.Y==playloc.Y)
							{
								AIList[i].setStuned(stunTime);
								//start battle
								soundSys->Play(0);
								return 1;
							}
						}
						else
						{
							v = viewLength;
						}
					}
				}
				AIList[i].update(&CurMap);
			}
		}
		for(int i = 0;i<StoryList.size();++i)
		{
			if(StoryList[i].update(&player))
			{
				return 2;
			}
		}
		
	}
	return 0;
}

bool Stealth::setPlayPos(PlayerState& player,int x,int y)
{
	Pos loc,rend;
	loc.X = x;
	loc.Y = y;
	loc.Z = 0;
	if(CurMap.valid(x,y))
	{
		CurMap.GetWorldPos(x,y,rend);
		player.setPos(loc.X,loc.Y,rend.X,rend.Y);
		return true;
	}
	return false;
}

void Stealth::getRend(D3Object objs[],int& NumObjs,renderInfo sprites[],int& NumSprit,TextStruct text[],int& NumText)
{
	CurMap.display(objs,NumObjs);
	int size = AIList.size();
	for(int i = 0;i<size;++i)
	{
		if(AIList[i].getRend(objs[NumObjs]))
		{
			++NumObjs;
		}
	}
}

void Stealth::shutdown()
{
	CurMap.cleanup();
}

void Stealth::saveMap(const char* fileName)
{
	int x,y;
	Pos temp;
	std::ofstream file;
	std::string tempString;
	file.open(fileName);
	//call map save to get size and walls
	CurMap.saveMap(file);
	//number of nodes
	file<<NodeList.size()<<"\n";
	//save nodes
	for(int i = 0;i<NodeList.size();++i)
	{
		file<<NodeList[i].direction<<" "<<NodeList[i].NumMoves<<" "<<NodeList[i].nextNodeNum<<"\n";
	}
	//number of AIs
	file<<AIList.size()<<"\n";
	//save AI
	for(int i = 0;i<AIList.size();++i)
	{
		temp = AIList[i].getStartPos();
		file<<temp.X<<" "<<temp.Y<<" "<<AIList[i].getStartNode()<<"\n";
	}
	//number of loads
	file<<LoadList.size()<<"\n";
	for(int i = 0;i<LoadList.size();++i)
	{
		temp = LoadList[i].getLoc();
		x = temp.X;
		y = temp.Y;
		temp = LoadList[i].getPlay();
		file<<LoadList[i].getMapName()<<" "<<x<<" "<<y<<" "<<temp.X<<" "<<temp.Y<<"\n";
	}
	//number of story points
	file<<StoryList.size()<<"\n";
	for(int i = 0;i<StoryList.size();++i)
	{
		temp = StoryList[i].getLoc();
		x = StoryList[i].getStoryNum();
		file<<temp.X<<" "<<temp.Y<<" "<<x<<"\n";
	}
}

void Stealth::clearVectors()
{
	AIList.clear();
	NodeList.clear();
	LoadList.clear();
}

Pos Stealth::getPlayPos()
{
	return PlayerPos;
}

void Stealth::loadMap(std::string fileName)
{
	loadMap(fileName,baseEnemy.objTex,baseEnemy,baseEnemy.objMat);
}

void Stealth::loadMap(std::string fileName, Texture enemyTex, D3Object& enemyModel, D3DMATERIAL9* enemyMat)
{
	clearVectors();
	Pos temp1,temp2;
	std::string tempString;
	int tempInt;
	int numWalls,xSize,ySize,numAI,numAINode,numLoads,numStory;
	AINode tempNode;
	EntAI tempAI;
	EntLoadTrigger tempLoad;
	EntStoryTrigger tempTrigger;
	std::ifstream file;
	file.open(fileName);
	if(file.is_open())
	{
		//get map size
		file>>xSize;
		file.ignore();
		file>>ySize;
		file.ignore();
		//clear map and set its size
		CurMap.resizeMap(xSize,ySize);
		//get number of walls
		file>>numWalls;
		file.ignore();
		//add walls
		for (int i=0;i<numWalls;i++)
		{
			file>>temp1.X;
			file>>temp1.Y;
			file>>temp2.X;
			file>>temp2.Y;
			file.ignore();
			CurMap.addWall(temp1,temp2);
		}
		//get number of nodes
		file>>numAINode;
		file.ignore();
		//add nodes
		for(int i = 0;i<numAINode;++i)
		{
			file>>tempInt;
			switch(tempInt)
			{
			case 0:
				tempNode.direction = Up;
				break;
			case 1:
				tempNode.direction = Down;
				break;
			case 2:
				tempNode.direction = Left;
				break;
			case 3:
				tempNode.direction = Right;
				break;
			case 4:
				tempNode.direction = WaitUp;
				break;
			case 5:
				tempNode.direction = WaitDown;
				break;
			case 6:
				tempNode.direction = WaitLeft;
				break;
			case 7:
				tempNode.direction = WaitRight;
				break;
			}
			file>>tempNode.NumMoves;
			file>>tempNode.nextNodeNum;
			file.ignore();
			tempNode.nodeNum = i;
			NodeList.push_back(tempNode);
		}
		//link nodes
		for(int i = 0;i<numAINode;++i)
		{
			linkNodes(&NodeList[i],&NodeList[NodeList[i].nextNodeNum]);
		}
		//get number of AIs
		file>>numAI;
		file.ignore();
		//add AIs
		enemyModel.objTex = enemyTex;
		enemyModel.objMat = enemyMat;
		tempAI.setRend(enemyModel);
		baseEnemy = enemyModel;
		for(int i = 0;i<numAI;++i)
		{
			file>>temp1.X;
			file>>temp1.Y;
			file>>tempInt;
			file.ignore();
			tempAI.setAI(temp1,NodeList[tempInt],&CurMap,tempInt);
			AIList.push_back(tempAI);
		}
		//get number of load points
		file>>numLoads;
		file.ignore();
		//add load points
		for(int i = 0;i<numLoads;++i)
		{
			std::getline(file,tempString,' ');
			file>>temp1.X;
			file>>temp1.Y;
			file>>temp2.X;
			file>>temp2.Y;
			file.ignore();
			tempLoad.setLoc(temp1);
			tempLoad.setPlayLoc(temp2);
			tempLoad.setMap(tempString);
			LoadList.push_back(tempLoad);
		}
		//get number of story triggers
		file>>numStory;
		file.ignore();
		//add story triggers
		for(int i = 0;i<numStory;++i)
		{
			file>>temp1.X;
			file>>temp1.Y;
			file>>tempInt;
			file.ignore();
			tempTrigger.setLoc(temp1);
			tempTrigger.setStoryNum(tempInt);
			StoryList.push_back(tempTrigger);
		}
	}
	
	file.close();
}

Stealth::~Stealth()
{
	shutdown();
}
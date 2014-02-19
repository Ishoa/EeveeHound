#include "Stealth.h"
#define stunTime 10
#define viewLength 3

Stealth::Stealth()
{
}

void Stealth::init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text, Texture enemyTex, D3Object& enemyModel, D3DMATERIAL9* enemyMat)
{
	Pos temp1,temp2;
	CurMap.CreMap(20,20,floorbase,floormat,wallmat,text);
	//CurMap=Map(20,20,floorbase,floormat,wallmat,text);
	temp1.X=1;
	temp1.Y=1;
	temp2.X=1;
	temp2.Y=5;
	CurMap.addWall(temp1,temp2);

	temp1.X=3;
	temp1.Y=1;
	temp2.X=3;
	temp2.Y=5;
	CurMap.addWall(temp1,temp2);

	temp1.X = 6;
	temp1.Y = 5;
	temp2.X = 4;
	temp2.Y = 8;
	CurMap.addWall(temp1,temp2);

	temp1.X = 7;
	temp1.Y = 5;
	AINode testNode;

	testNode.direction = Right;
	testNode.NumMoves = 3;
	NodeList.push_back(testNode);

	testNode.direction = Left;
	NodeList.push_back(testNode);

	NodeList[0].nextNode = &NodeList[1];
	NodeList[1].nextNode = &NodeList[0];

	EntAI testAI(temp1,NodeList[0],&CurMap);
	enemyModel.objMat = enemyMat;
	enemyModel.objTex = enemyTex;
	testAI.setRend(enemyModel);
	AIList.push_back(testAI);
}

void Stealth::Update(char keyboard[],bool& takeinput,DIMOUSESTATE2& mouse,PlayerState& player,SoundFrame* soundSys)
{
	Pos playloc, playren,sightCheck;
	bool hasMoved = false;
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
	int listLength = AIList.size();
	if(hasMoved)
	{
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
						if(sightCheck.X==playloc.X&&sightCheck.Y==playloc.Y)
						{
							AIList[i].setStuned(stunTime);
							//start battle
							soundSys->Play(0);
						}
					}
				}
				AIList[i].update(&CurMap);
			}
		}
		
	}

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

Stealth::~Stealth()
{
	shutdown();
}
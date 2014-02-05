#include "Stealth.h"

Stealth::Stealth()
{
}

void Stealth::init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text)
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

	testNode.direction = Up;
	testNode.NumMoves = 3;
	NodeList.push_back(testNode);

	testNode.direction = Down;
	NodeList.push_back(testNode);

	NodeList[0].nextNode = &NodeList[1];
	NodeList[1].nextNode = &NodeList[0];

	EntAI testAI(temp1,NodeList[0]);
	floorbase.objMat = floormat;
	floorbase.objTex = text;
	testAI.setRend(floorbase);
	AIList.push_back(testAI);
}

void Stealth::Update(char keyboard[],bool& takeinput,DIMOUSESTATE2& mouse,PlayerState& player)
{
	Pos playloc, playren;
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
			AIList[i].update(&CurMap);
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
#include "Stealth.h"

Stealth::Stealth()
{
}

void Stealth::init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text)
{
	Pos temp1,temp2;
	//CurMap.CreMap(20,20,floorbase,floormat,wallmat,text);
	CurMap=Map(20,20,floorbase,floormat,wallmat,text);
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
}

void Stealth::Update(char keyboard[],bool& takeinput,DIMOUSESTATE2& mouse,PlayerState& player)
{
	Pos playloc, playren;
	playloc = player.getPos();
	if(keyboard[DIK_UP]&0x80)
	{
		if(CurMap.valid(playloc.X,playloc.Y + 1)&&takeinput)
		{
			playloc.Y += 1;
			CurMap.GetWorldPos(playloc.X,playloc.Y,playren);
			player.setPos(playloc.X,playloc.Y,playren.X,playren.Y);
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
		}
		takeinput = false;
	}
	else if(!takeinput)
	{
		takeinput = true;
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
}

void Stealth::shutdown()
{
	CurMap.cleanup();
}

Stealth::~Stealth()
{
	shutdown();
}
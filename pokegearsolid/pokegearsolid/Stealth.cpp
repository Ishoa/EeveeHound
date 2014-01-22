#include "Stealth.h"

Stealth::Stealth()
{
}

void Stealth::init(D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text)
{
	CurMap = Map(20,20,floorbase,floormat,wallmat,text);
}

void Stealth::Update(char keyboard[],DIMOUSESTATE2& mouse,PlayerState& player)
{
	if(keyboard[DIK_UP]&0x80)
	{

	}
	else if(keyboard[DIK_DOWN]&0x80)
	{

	}
	else if(keyboard[DIK_LEFT]&0x80)
	{

	}
	else if(keyboard[DIK_RIGHT]&0x80)
	{

	}
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
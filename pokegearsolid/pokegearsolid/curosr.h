#pragma once
#include "Defines.h"

class curosr
{
private:
	float x,y;
	Texture Sprite;
	TexInfo SpriteInf;
public:
	curosr();
	void getPos(float &X,float &Y);
	void setPos(float x,float y);
	void move(float xChange,float yChange);
	//was going to manage sprite in this, but changed it to into programe
	void setSprite(renderInfo);
	renderInfo getRend();
};
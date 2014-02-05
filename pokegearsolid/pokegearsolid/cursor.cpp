//mouse managment for menu
//by Tyler van Gastel

#include "curosr.h"

curosr::curosr()
{
	x = 0;
	y = 0;
	Sprite = 0;
}

void curosr::getPos(float &X, float &Y)
{
	X = x;
	Y = y;
}

void curosr::setPos(float X, float Y)
{
	x = X;
	y = Y;
}

void curosr::setSprite(renderInfo sprite)
{
	Sprite = sprite.tex;
	SpriteInf = sprite.texinfo;
}

void curosr::move(float cX,float cY)
{
	x += cX;
	y += cY;
}

renderInfo curosr::getRend()
{
	renderInfo rendinf;
	D3DXMATRIX loc;
	D3DXMatrixIdentity(&loc);
	D3DXMatrixTranslation(&loc,x,y,0);
	rendinf.tex = Sprite;
	rendinf.texinfo = SpriteInf;
	rendinf.matrix = loc;
	return rendinf;
}
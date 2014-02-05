//button for menu system
//by Tyler van Gastel

#include "Button.h"

Button::Button()
{
	drawInfo.text = L"NONE";
	highlight = false;
	active = true;
	visable = true;
	drawInfo.rec.left = 0;
	drawInfo.rec.right = 10;
	drawInfo.rec.top = 0;
	drawInfo.rec.bottom = 10;
	defColor = D3DCOLOR_XRGB(255,255,255);
	higColor = D3DCOLOR_XRGB(255,0,255);
}

void Button::setLoc(float tE,float bE,float lE,float rE)
{
	drawInfo.rec.top = tE;
	drawInfo.rec.bottom = bE;
	drawInfo.rec.left = lE;
	drawInfo.rec.right = rE;
}
void Button::getLoc(float &tE,float &bE,float &lE,float &rE)
{
	tE = drawInfo.rec.top;
	bE = drawInfo.rec.bottom;
	lE = drawInfo.rec.left;
	rE = drawInfo.rec.right;
}

void Button::setColors(DWORD defCol,DWORD higCol)
{
	defColor = defCol;
	higColor = higCol;
}

TextStruct Button::getTextInf()
{
	if(visable)
	{
		if(active)
		{
			if(highlight)
			{
				drawInfo.textColor = higColor;
			}
			else
			{
				drawInfo.textColor = defColor;
			}
		}
		else
		{
			drawInfo.textColor = D3DCOLOR_XRGB(150,150,150);
		}
	}
	else
	{
		drawInfo.textColor = D3DCOLOR_ARGB(0,100,100,100);
	}
	return drawInfo;
}

void Button::setlable(wchar_t* text)
{
	drawInfo.text = text;
}

void Button::Update(float x, float y)
{
	if(x<drawInfo.rec.right&&x>drawInfo.rec.left)
	{
		if(y<drawInfo.rec.bottom&&y>drawInfo.rec.top)
		{
			highlight = true;
		}
		else
		{
			highlight = false;
		}
	}
	else
	{
		highlight = false;
	}
}

void Button::setActive(bool in)
{
	active = in;
}

bool Button::getActive()
{
	return active;
}

bool Button::clicked()
{
	if(highlight&&active)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::setVisable(bool vis)
{
	visable = vis;
}

bool Button::getVisable()
{
	return visable;
}

void Button::setVisAct(bool in)
{
	visable = in;
	active = in;
}
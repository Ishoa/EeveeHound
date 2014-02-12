//Button class for menu
//Tyler van Gastel
//created 9/24/13
//last modified 9/24/13
#pragma once
#include "Defines.h"

class Button
{
private:
	bool highlight,active,visable;
	TextStruct drawInfo;
	int height,width;
	DWORD defColor,higColor;
public:
	Button();
	void setLoc(float tE,float bE,float lE,float rE);
	void getLoc(float &tE,float &bE,float &lE,float &rE);
	void setColors(DWORD defCol,DWORD higCol);
	TextStruct getTextInf();
	void setlable(wchar_t*);
	void Update(float mouseX,float mouseY);
	bool clicked();
	void setActive(bool);
	bool getActive();
	void setVisable(bool);
	bool getVisable();
	void setVisAct(bool);
	void setRes(int W,int H);
};
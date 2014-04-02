//menu thing
//by Tyler van Gastel

#pragma once
#include "Defines.h"
#include "curosr.h"
#include "Button.h"
#include "Pokemon.h"
#define numBut 11

class Menu
{
private:
	curosr cur;
	int state,lastBut,height,width;
	Button buttons[numBut];
public:
	Menu();
	int getState();
	void setState(int);
	bool setButton(Button newButton,int index);
	bool buttonIsPushed(int button);
	bool getPushed(int &buttonPushed,bool&);
	void Update(char keyboard[],DIMOUSESTATE2& mouse,bool &pushed);
	void OptionsReset();
	void CreditsReset();
	void setMouseSprite(renderInfo sprite);
	void GetRender(renderInfo&,int& numSprite,TextStruct[],int& numText);
	void getMousePos(int &X,int &Y);
	void reset();
	void battleReset();
	void battleResetWithMoves(Pokemon a_pikachu);
	void setRes(int w,int h);
	void MoveMouseToBut(int button);
	void setQuitMenu();
	Button getBut(int button);
};
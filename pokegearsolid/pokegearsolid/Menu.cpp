//menu thing
//by Tyler van Gastel

#include "Menu.h"

Menu::Menu()
{
	lastBut = 0;
	for(int i = 0;i<numBut;i++)
	{
		buttons[i].setActive(true);
		buttons[i].setLoc(100+60*i,150+60*i,300,500);
	}
	buttons[0].setlable(L"Play");
	buttons[1].setlable(L"Help");
	buttons[2].setlable(L"Options");
	buttons[3].setlable(L"Credits");
	buttons[4].setlable(L"Quit");
	for(int i = 5;i<numBut;++i)
	{
		buttons[i].setlable(L"Blank");
		buttons[i].setVisAct(false);
	}
	width = 800;
	height = 600;
}

void Menu::reset()
{
	int w,h;
	//store curent res
	h = height;
	w = width;
	//change res for ez placment
	height = 600;
	width = 800;
	setRes(width,height);
	for(int i = 0;i<numBut;i++)
	{
		buttons[i].setActive(true);
		buttons[i].setLoc(100+60*i,150+60*i,300,500);
	}
	buttons[0].setlable(L"Play");
	buttons[0].setVisAct(true);
	buttons[1].setlable(L"Intro");
	buttons[1].setVisAct(false);
	buttons[2].setlable(L"Options");
	buttons[2].setVisAct(true);
	buttons[3].setlable(L"Credits");
	buttons[3].setVisAct(true);
	buttons[4].setlable(L"Quit");
	buttons[4].setVisAct(true);
	for(int i = 5;i<numBut;++i)
	{
		buttons[i].setlable(L"Blank");
		buttons[i].setVisAct(false);
	}
	//reset res
	setRes(800,600);
}



void Menu::setMouseSprite(renderInfo sprite)
{
	cur.setSprite(sprite);
}

int Menu::getState()
{
	return state;
}

void Menu::setState(int in)
{
	state = in;
}

bool Menu::setButton(Button newButton,int index)
{
	if(index>=0&&index<numBut)
	{
		buttons[index] = newButton;
		return true;
	}
	else
	{
		return false;
	}
}

bool Menu::buttonIsPushed(int button)
{
	if(button>=0&&button<numBut)
	{
		return buttons[button].clicked();
	}
	else
	{
		return false;
	}
}

bool Menu::getPushed(int &buttonPushed,bool &pushed)
{
	for(int i = 0;i < numBut;++i)
	{
		if(buttons[i].clicked())
		{
			if(!pushed)
			{
				buttonPushed = i;
				pushed = true;
				return true;
			}
		}
	}
	return false;
}

void Menu::Update(char keyboard[],DIMOUSESTATE2& mouse,bool &pushed)
{
	float x,y;
	cur.move(mouse.lX,mouse.lY);
	cur.getPos(x,y);
	if(x<0)
	{
		x = 0;
	}
	else if(x>width)
	{
		x=width;
	}
	if(y<0)
	{
		y = 0;
	}
	else if(y>height)
	{
		y = height;
	}
	cur.setPos(x,y);
	if((keyboard[DIK_UP]&0x80))
	{
		bool loop = true;
		if(!pushed)
		{
			--lastBut;
			while(loop)
			{
				if(lastBut<0)
				{
					lastBut = numBut-1;
				}
				if(buttons[lastBut].getActive())
				{
					loop = false;
				}
				else
				{
					--lastBut;
				}
			}
			MoveMouseToBut(lastBut);
			pushed = true;
		}
	}
	else if(keyboard[DIK_DOWN]&0x80)
	{
		bool loop = true;
		if(!pushed)
		{
			++lastBut;
			while(loop)
			{
				if(lastBut>=numBut)
				{
					lastBut = 0;
				}
				if(buttons[lastBut].getActive())
				{
					loop = false;
				}
				else
				{
					++lastBut;
				}
			}
			MoveMouseToBut(lastBut);
			pushed = true;
		}
	}
	else if(keyboard[DIK_RETURN]&0x80||mouse.rgbButtons[0]&0x80)
	{
		pushed = true;
	}
	else if(pushed)
	{
		pushed = false;
	}
	for(int i = 0;i<numBut;++i)
	{
		buttons[i].Update(x,y);
	}
}

void Menu::GetRender(renderInfo& mou,int& sprites,TextStruct tex[],int& text)
{
	mou = cur.getRend();
	++sprites;
	for(int i = 0;i<numBut;++i)
	{
		if(buttons[i].getVisable())
		{
			tex[text] = buttons[i].getTextInf();
			++text;
		}
	}
}

void Menu::getMousePos(int &X,int &Y)
{
	float x,y;
	cur.getPos(x,y);
	X = x;
	Y = y;
}

void Menu::setRes(int w,int h)
{
	width = w;
	height = h;
	//update all the button locations
	for(int i = 0;i<numBut;++i)
	{
		buttons[i].setRes(w,h);
	}
}

void Menu::MoveMouseToBut(int but)
{
	float t,b,l,r;
	if(but<numBut)
	{
		buttons[but].getLoc(t,b,l,r);
		b -= t;
		r -= l;
		b = b/2;
		r = r/2;
		l += r;
		t += b;
		cur.setPos(l,t);
	}
}

Button Menu::getBut(int but)
{
	if(but<numBut&&but>=0)
	{
		return buttons[but];
	}
	else
		return buttons[0];
}
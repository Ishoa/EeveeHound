// Battle system by josh

#pragma once
#include "Battle.h"


Battle::Battle() {
	curtextincrement = 0;
}


Battle::~Battle() {

}


Battle::Battle(Menu a_battlemenu, int a_numsprites, renderInfo* a_sprites) {
	setBattleMenu(a_battlemenu);
	for(int i = 0; i < a_numsprites; ++i) {
		sprites[i] = a_sprites[i];
	}

}


void Battle::Init(TextureStruc a_sprites[]) {
	srand(time(NULL));
	curnumsprites = 0;
	D3DXMATRIX matrixlovetwo;
	D3DXMATRIX matrixlovetwo2;
	D3DXMATRIX matrixlovetwo3;
	D3DXMatrixIdentity(&matrixlovetwo);
	D3DXMatrixIdentity(&matrixlovetwo2);
	D3DXMatrixIdentity(&matrixlovetwo3);
	for(int i = 3; i < 9; ++i) {
		D3DXMatrixIdentity(&matrixlovetwo);
		D3DXMatrixIdentity(&matrixlovetwo2);
		D3DXMatrixIdentity(&matrixlovetwo3);
		if(i == 3) {
			D3DXMatrixTranslation(&matrixlovetwo,0,0,0);
			D3DXMatrixScaling(&matrixlovetwo2,3.3f,3.3f,3.3f);
		}
		else if (i == 4) {
			D3DXMatrixTranslation(&matrixlovetwo,75,300,0);
			D3DXMatrixScaling(&matrixlovetwo2,2.0f,2.0f,2.0f);
		}
		else {
			D3DXMatrixTranslation(&matrixlovetwo,475,50,0);
			D3DXMatrixScaling(&matrixlovetwo2,2.0f,2.0f,2.0f);
		}
		
		D3DXMatrixMultiply(&matrixlovetwo3, &matrixlovetwo2, &matrixlovetwo);
		sprites[i-3].tex = a_sprites[i].objTex;
		sprites[i-3].texinfo = a_sprites[i].texInfo;
		sprites[i-3].matrix = matrixlovetwo3;
		++curnumsprites;
	}
}


LPCWSTR terribleJankyIntToLPCWSTR(int a);


void Battle::battleStart(Pokemon a_pikachu, Pokemon a_enemy) {
	
}


void Battle::menuReset(Pokemon a_pikachu, Pokemon a_enemy) {
	battlemenu.battleReset();
	//wchar_t tempwchar_t[256];
	D3DXCOLOR tempcolor = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	curtextincrement = 0;
	battletext[curtextincrement].text = a_pikachu.getName();// Pikachu's name
	battletext[curtextincrement].rec.top = 450;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 600;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = L"hp:"; // hp's hp:
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 540;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getCurHP()); // Pikachu's curhp
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 600;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // hp's slash
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 640;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMaxHP()); // pikach's max hp
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 680;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	//  enemy start
	battletext[curtextincrement].text = a_enemy.getName();// Enemy's name
	battletext[curtextincrement].rec.top = 75;
	battletext[curtextincrement].rec.bottom = 0;
	battletext[curtextincrement].rec.left = 0;
	battletext[curtextincrement].rec.right = 200;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = L"hp:"; // hp's hp:
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 0;
	battletext[curtextincrement].rec.right = 100;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_enemy.getCurHP()); // enemy's curhp
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 160;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // hp's slash
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 210;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_enemy.getMaxHP()); // enemy's max hp
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 60;
	battletext[curtextincrement].rec.right = 210;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
}


void Battle::menuResetWithMoves(Pokemon a_pikachu, Pokemon a_enemy) {
	battlemenu.battleResetWithMoves(a_pikachu);
	D3DXCOLOR tempcolor = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	curtextincrement = 0;
	battletext[curtextincrement].text = a_pikachu.getName();// Pikachu's name
	battletext[curtextincrement].rec.top = 450;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 600;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = L"hp:"; // hp's hp:
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 540;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getCurHP()); // Pikachu's curhp
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 600;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // hp's slash
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 640;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMaxHP()); // pikachu's max hp
	battletext[curtextincrement].rec.top = 525;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 680;
	battletext[curtextincrement].rec.right = 800;
	++curtextincrement;
	//  enemy start
	battletext[curtextincrement].text = a_enemy.getName();// Enemy's name
	battletext[curtextincrement].rec.top = 75;
	battletext[curtextincrement].rec.bottom = 0;
	battletext[curtextincrement].rec.left = 0;
	battletext[curtextincrement].rec.right = 200;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = L"hp:"; // hp's hp:
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 0;
	battletext[curtextincrement].rec.right = 100;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_enemy.getCurHP()); // enemy's curhp
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 160;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // hp's slash
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 210;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_enemy.getMaxHP()); // enemy's max hp
	battletext[curtextincrement].rec.top = 150;
	battletext[curtextincrement].rec.bottom = 75;
	battletext[curtextincrement].rec.left = 60;
	battletext[curtextincrement].rec.right = 210;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	// Start move pp's
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(0).getCurPP()); // pikachu's 1st move's curpp
	battletext[curtextincrement].rec.top = 480;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 160;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // pikachu's 1st move's slash
	battletext[curtextincrement].rec.top = 480;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 210;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(0).getMaxPP()); // pikachu's 1st move's maxpp
	battletext[curtextincrement].rec.top = 480;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 60;
	battletext[curtextincrement].rec.right = 210;
	++curtextincrement;
	// second move
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(1).getCurPP()); // pikachu's 2nd move's curpp
	battletext[curtextincrement].rec.top = 480;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 210;
	battletext[curtextincrement].rec.right = 360;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // pikachu's 2nd move's slash
	battletext[curtextincrement].rec.top = 480;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 210;
	battletext[curtextincrement].rec.right = 410;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(1).getMaxPP()); // pikachu's 2nd move's maxpp
	battletext[curtextincrement].rec.top = 480;
	battletext[curtextincrement].rec.bottom = 525;
	battletext[curtextincrement].rec.left = 260;
	battletext[curtextincrement].rec.right = 410;
	++curtextincrement;
	// third move pp
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(2).getCurPP()); // pikachu's 3rd move's curpp
	battletext[curtextincrement].rec.top = 565;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 160;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // pikachu's 3rd move's slash
	battletext[curtextincrement].rec.top = 565;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 10;
	battletext[curtextincrement].rec.right = 210;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(2).getMaxPP()); // pikachu's 3rd move's maxpp
	battletext[curtextincrement].rec.top = 565;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 60;
	battletext[curtextincrement].rec.right = 210;
	++curtextincrement;
	// fourth move
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(3).getCurPP()); // pikachu's 4th move's curpp
	battletext[curtextincrement].rec.top = 565;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 210;
	battletext[curtextincrement].rec.right = 360;
	++curtextincrement;
	battletext[curtextincrement].text = L"/"; // pikachu's fortuh move's slash
	battletext[curtextincrement].rec.top = 565;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 210;
	battletext[curtextincrement].rec.right = 410;
	++curtextincrement;
	battletext[curtextincrement].text = terribleJankyIntToLPCWSTR(a_pikachu.getMove(3).getMaxPP()); // pikachu's 4th move's maxpp
	battletext[curtextincrement].rec.top = 565;
	battletext[curtextincrement].rec.bottom = 600;
	battletext[curtextincrement].rec.left = 260;
	battletext[curtextincrement].rec.right = 410;
	++curtextincrement;

}


void Battle::addText(Pokemon a_user, Move a_move) {
	D3DXCOLOR tempcolor = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	battletext[curtextincrement].text = a_user.getName();// User's name
	battletext[curtextincrement].rec.top = 375;
	battletext[curtextincrement].rec.bottom = 450;
	battletext[curtextincrement].rec.left = 300;
	battletext[curtextincrement].rec.right = 500;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = L"used";// Used
	battletext[curtextincrement].rec.top = 375;
	battletext[curtextincrement].rec.bottom = 450;
	battletext[curtextincrement].rec.left = 425;
	battletext[curtextincrement].rec.right = 625;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
	battletext[curtextincrement].text = a_move.getName();// User's move's name
	battletext[curtextincrement].rec.top = 375;
	battletext[curtextincrement].rec.bottom = 450;
	battletext[curtextincrement].rec.left = 575;
	battletext[curtextincrement].rec.right = 775;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
}


void Battle::addYouWin() {
	D3DXCOLOR tempcolor = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	battletext[curtextincrement].text = L"You win!";// User's name
	battletext[curtextincrement].rec.top = 300;
	battletext[curtextincrement].rec.bottom = 375;
	battletext[curtextincrement].rec.left = 300;
	battletext[curtextincrement].rec.right = 500;
	battletext[curtextincrement].textColor = tempcolor;
	++curtextincrement;
}


void Battle::GetBattleRender(renderInfo a_sprites[],int& a_numsprites,TextStruct tex[],int& text, Species a_enemy) {
	
	for(int i = 0;i<curtextincrement;++i) {
		tex[text] = battletext[i];
		++text;
	}
	for(int i = 0; i < 2; ++i) {
		a_sprites[a_numsprites] = sprites[i];
		++a_numsprites;
	}

	if(a_enemy == RATATA) {
		a_sprites[a_numsprites] = sprites[2];
		++a_numsprites;
	}
	else if(a_enemy == ZUBAT) {
		a_sprites[a_numsprites] = sprites[3];
		++a_numsprites;
	}
	else if(a_enemy == KOFFING) {
		a_sprites[a_numsprites] = sprites[4];
		++a_numsprites;
	}
	else if(a_enemy == EKANS) {
		a_sprites[a_numsprites] = sprites[5];
		++a_numsprites;
	}
	battlemenu.GetRender(a_sprites[a_numsprites], a_numsprites, tex, text);

}


void Battle::setBattleMenu(Menu a_battlemenu) {
	battlemenu = a_battlemenu;
}


Menu Battle::getBattleMenu() {
	return battlemenu;
}


void Battle::addSprite(renderInfo a_newsprite) {
	if(curnumsprites < 20) {
		sprites[curnumsprites] = a_newsprite;
		incrementCurNumSprites();
	}
}


renderInfo Battle::getSprite(int a_index) {
	return sprites[a_index];
}


int Battle::getCurNumSprites() {
	return curnumsprites;
}


void Battle::incrementCurNumSprites() {
	++curnumsprites;
}


void Battle::Update(char keyboard[],DIMOUSESTATE2& mouse,bool &pushed) {
	battlemenu.Update(keyboard,mouse,pushed);

}




// This function is really janky and really terrible.
// You pass in an int, and it returns an LPCWSTR of that int
// Only works for -15 through 180.

LPCWSTR terribleJankyIntToLPCWSTR(int a) {
	if(a>=0 && a<=30) {
		if(a<=15) {
			if(a==0)
				return L"0";
			if(a==1)
				return L"1";
			if(a==2)
				return L"2";
			if(a==3)
				return L"3";
			if(a==4)
				return L"4";
			if(a==5)
				return L"5";
			if(a==6)
				return L"6";
			if(a==7)
				return L"7";
			if(a==8)
				return L"8";
			if(a==9)
				return L"9";
			if(a==10)
				return L"10";
			if(a==11)
				return L"11";
			if(a==12)
				return L"12";
			if(a==13)
				return L"13";
			if(a==14)
				return L"14";
			if(a==15)
				return L"15";
		}
		else {
			if(a==16)
				return L"16";
			if(a==17)
				return L"17";
			if(a==18)
				return L"18";
			if(a==19)
				return L"19";
			if(a==20)
				return L"20";
			if(a==21)
				return L"21";
			if(a==22)
				return L"22";
			if(a==23)
				return L"23";
			if(a==24)
				return L"24";
			if(a==25)
				return L"25";
			if(a==26)
				return L"26";
			if(a==27)
				return L"27";
			if(a==28)
				return L"28";
			if(a==29)
				return L"29";
			if(a==30)
				return L"30";
			
		}
	}
	else if(a>30 && a<=60) {
		if(a<=45) {
			if(a==31)
				return L"31";
			if(a==32)
				return L"32";
			if(a==33)
				return L"33";
			if(a==34)
				return L"34";
			if(a==35)
				return L"35";
			if(a==36)
				return L"36";
			if(a==37)
				return L"37";
			if(a==38)
				return L"38";
			if(a==39)
				return L"39";
			if(a==40)
				return L"40";
			if(a==41)
				return L"41";
			if(a==42)
				return L"42";
			if(a==43)
				return L"43";
			if(a==44)
				return L"44";
			if(a==45)
				return L"45";
		}
		else {
			if(a==46)
				return L"46";
			if(a==47)
				return L"47";
			if(a==48)
				return L"48";
			if(a==49)
				return L"49";
			if(a==50)
				return L"50";
			if(a==51)
				return L"51";
			if(a==52)
				return L"52";
			if(a==53)
				return L"53";
			if(a==54)
				return L"54";
			if(a==55)
				return L"55";
			if(a==56)
				return L"56";
			if(a==57)
				return L"57";
			if(a==58)
				return L"58";
			if(a==59)
				return L"59";
			if(a==60)
				return L"60";
			
		}
	}
	else if(a>60 && a<=90) {
		if(a<=75) {
			if(a==61)
				return L"61";
			if(a==62)
				return L"62";
			if(a==63)
				return L"63";
			if(a==64)
				return L"64";
			if(a==65)
				return L"65";
			if(a==66)
				return L"66";
			if(a==67)
				return L"67";
			if(a==68)
				return L"68";
			if(a==69)
				return L"69";
			if(a==70)
				return L"70";
			if(a==71)
				return L"71";
			if(a==72)
				return L"72";
			if(a==73)
				return L"73";
			if(a==74)
				return L"74";
			if(a==75)
				return L"75";
			
		}
		else {
			if(a==76)
				return L"76";
			if(a==77)
				return L"77";
			if(a==78)
				return L"78";
			if(a==79)
				return L"79";
			if(a==80)
				return L"80";
			if(a==81)
				return L"81";
			if(a==82)
				return L"82";
			if(a==83)
				return L"83";
			if(a==84)
				return L"84";
			if(a==85)
				return L"85";
			if(a==86)
				return L"86";
			if(a==87)
				return L"87";
			if(a==88)
				return L"88";
			if(a==89)
				return L"89";
			if(a==90)
				return L"90";
			
		}
	}
	else if(a>90 && a<=120) {
		if(a<=105) {
			if(a==91)
				return L"91";
			if(a==92)
				return L"92";
			if(a==93)
				return L"93";
			if(a==94)
				return L"94";
			if(a==95)
				return L"95";
			if(a==96)
				return L"96";
			if(a==97)
				return L"97";
			if(a==98)
				return L"98";
			if(a==99)
				return L"99";
			if(a==100)
				return L"100";
			if(a==101)
				return L"101";
			if(a==102)
				return L"102";
			if(a==103)
				return L"103";
			if(a==104)
				return L"104";
			if(a==105)
				return L"105";
			
		}
		else {
			if(a==106)
				return L"106";
			if(a==107)
				return L"107";
			if(a==108)
				return L"108";
			if(a==109)
				return L"109";
			if(a==110)
				return L"110";
			if(a==111)
				return L"111";
			if(a==112)
				return L"112";
			if(a==113)
				return L"113";
			if(a==114)
				return L"114";
			if(a==115)
				return L"115";
			if(a==116)
				return L"116";
			if(a==117)
				return L"117";
			if(a==118)
				return L"118";
			if(a==119)
				return L"119";
			if(a==120)
				return L"120";
			
		}
	}
	else if(a>120 && a<=150) {
		if(a<=135) {
			if(a==121)
				return L"121";
			if(a==122)
				return L"122";
			if(a==123)
				return L"123";
			if(a==124)
				return L"124";
			if(a==125)
				return L"125";
			if(a==126)
				return L"126";
			if(a==127)
				return L"127";
			if(a==128)
				return L"128";
			if(a==129)
				return L"129";
			if(a==130)
				return L"130";
			if(a==131)
				return L"131";
			if(a==132)
				return L"132";
			if(a==133)
				return L"133";
			if(a==134)
				return L"134";
			if(a==135)
				return L"135";
			
		}
		else {
			if(a==136)
				return L"136";
			if(a==137)
				return L"137";
			if(a==138)
				return L"138";
			if(a==139)
				return L"139";
			if(a==140)
				return L"140";
			if(a==141)
				return L"141";
			if(a==142)
				return L"142";
			if(a==143)
				return L"143";
			if(a==144)
				return L"144";
			if(a==145)
				return L"145";
			if(a==146)
				return L"146";
			if(a==147)
				return L"147";
			if(a==148)
				return L"148";
			if(a==149)
				return L"149";
			if(a==150)
				return L"150";
			
		}
	}
	else if(a>150 && a<=180) {
		if(a<=165) {
			if(a==151)
				return L"151";
			if(a==152)
				return L"152";
			if(a==153)
				return L"153";
			if(a==154)
				return L"154";
			if(a==155)
				return L"155";
			if(a==156)
				return L"156";
			if(a==157)
				return L"157";
			if(a==158)
				return L"158";
			if(a==159)
				return L"159";
			if(a==160)
				return L"160";
			if(a==161)
				return L"161";
			if(a==162)
				return L"162";
			if(a==163)
				return L"163";
			if(a==164)
				return L"164";
			if(a==165)
				return L"165";
			
		}
		else {
			if(a==166)
				return L"166";
			if(a==167)
				return L"167";
			if(a==168)
				return L"168";
			if(a==169)
				return L"169";
			if(a==170)
				return L"170";
			if(a==171)
				return L"171";
			if(a==172)
				return L"172";
			if(a==173)
				return L"173";
			if(a==174)
				return L"174";
			if(a==175)
				return L"175";
			if(a==176)
				return L"176";
			if(a==177)
				return L"177";
			if(a==178)
				return L"178";
			if(a==179)
				return L"179";
			if(a==180)
				return L"180";
			
		}
	}
	else if(a>-30 && a<=0) {
		if(a>=-15) {
			if(a==-1)
				return L"-1";
			if(a==-2)
				return L"-2";
			if(a==-3)
				return L"-3";
			if(a==-4)
				return L"-4";
			if(a==-5)
				return L"-5";
			if(a==-6)
				return L"-6";
			if(a==-7)
				return L"-7";
			if(a==-8)
				return L"-8";
			if(a==-9)
				return L"-9";
			if(a==-10)
				return L"-10";
			if(a==-11)
				return L"-11";
			if(a==-12)
				return L"-12";
			if(a==-13)
				return L"-13";
			if(a==-14)
				return L"-14";
			if(a==-15)
				return L"-15";
		}
		else {

		}
	}
	else if(a>-60 && a<=-30) {
		if(a<=-45) {

		}
		else {

		}
	}
	else if(a>-90 && a<=-60) {
		if(a<=-75) {

		}
		else {

		}
	}
	else if(a>-120 && a<=-90) {
		if(a<=-105) {

		}
		else {

		}
	}
	else if(a>-150 && a<=-120) {
		if(a<=-135) {

		}
		else {

		}
	}
	else if(a>-180 && a<=-150) {
		if(a<=-165) {

		}
		else {

		}
	}
}
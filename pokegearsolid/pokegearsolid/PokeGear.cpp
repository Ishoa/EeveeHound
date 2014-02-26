#include "PokeGear.h"

PokeGear::PokeGear()
{
	//cam setup
	camera.cam_up_vec = D3DXVECTOR3(0,1,0);
	camera.cam_pos = D3DXVECTOR3(0,1,-5);
	camera.cam_look_pos = D3DXVECTOR3(0,0,-4);
	bCanInput = true;
	menuPushed = false;
	donePlayerAttack = false;
	doneEnemyAttack = false;
	battleover = false;
	playerlost = false;
	curState = MainMenu;
	curBattleState = MAIN;
	bCanInput2 = true;
	newscene=true;
	musicMute = false;
}

void PokeGear::init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
	int tex = 0;
	input.init(hWnd,hInst);
	display.Init(hWnd,hInst,bWindowed);
	soundSys.Init();
	for(int i = 0;i<maxModels;++i)
	{
		Models[i].obj = 0;
	}
	for(int i = 0;i<maxtexture;++i)
	{
		textures[i].objTex = 0;
	}
	//start art loading
	//Player Mat
	materials[0].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Ambient color reflected
	materials[0].Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);		// Diffuse color reflected
	materials[0].Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// Emissive color reflected
	materials[0].Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// Specular
	materials[0].Power = 0.0f;										// Specular highlight intensity
	//player Model
	display.CreateUVCube(Models[0],1,1,1);
	Models[0].objMat = &materials[0];
	ZeroMemory(&Models[0].matrix,sizeof(Models[0].matrix));
	D3DXMatrixTranslation(&Models[0].matrix,0,0,1);
	//default textue
	display.LoadTex(L"playtex.bmp",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//player texture
	display.LoadTex(L"pikachu.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	Models[0].objTex = textures[tex].objTex;
	++tex;
	//enemy texture
	display.LoadTex(L"enemy.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	// BATTLE TEXTURES START
	//battle background texture
	display.LoadTex(L"battlebackground.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(0,0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//battle pikachu texture
	display.LoadTex(L"battlepikachu.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(0,0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//battle ratata texture
	display.LoadTex(L"battlerattata.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(0,0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//battle zubat texture
	display.LoadTex(L"battlezubat.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(0,0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//battle koffing texture
	display.LoadTex(L"battlekoffing.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(0,0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//battle ekans texture
	display.LoadTex(L"battleekans.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(0,0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;

	//character sprites
	//snake
	display.LoadTex(L"snake.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//joy
	display.LoadTex(L"joy.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//pikachu
	display.LoadTex(L"solidchu.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	//evilchu
	display.LoadTex(L"evilchu.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;

	//load more stuff
	display.LoadTex(L"Pokegearsolid.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	display.LoadTex(L"deathbyekans.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;
	display.LoadTex(L"win.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[tex].texInfo,0,&textures[tex].objTex);
	++tex;

	//world Model base
	display.CreateUncenteredCube(Models[1],1,1,1);
	//create enemy model
	display.CreateUVCube(Models[2],2,2,1);
	//floor mat
	materials[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	materials[1].Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Diffuse color reflected
	materials[1].Emissive = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Emissive color reflected
	materials[1].Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Specular
	materials[1].Power = 0.0f;										// Specular highlight intensity
	//wall mat
	materials[2].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	materials[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Diffuse color reflected
	materials[2].Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Emissive color reflected
	materials[2].Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Specular
	materials[2].Power = 0.0f;										// Specular highlight intensity
	//enemy mat
	materials[3].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Ambient color reflected
	materials[3].Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);		// Diffuse color reflected
	materials[3].Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// Emissive color reflected
	materials[3].Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// Specular
	materials[3].Power = 0.0f;										// Specular highlight intensity
	//test set texture for world
	Models[1].objTex = textures[0].objTex;
	//end art load
	sneak.init(Models[1],&materials[1],&materials[2],textures[0].objTex,textures[2].objTex,Models[2],&materials[3]);
	sneak.setPlayPos(curPlay,0,0);
	menuSys.reset();
	//set sprite tex
	curSpri.tex = textures[0].objTex;
	curSpri.texinfo = textures[0].texInfo;
	menuSys.setMouseSprite(curSpri);

	talks.init(textures);

	Menu tempmenu;
	tempmenu.battleReset();
	tempmenu.setMouseSprite(curSpri);
	battler.setBattleMenu(tempmenu);
	battler.Init(textures);

	//load music
	soundSys.loadStream("MGSMain.mp3",0);
	soundSys.loadStream("MGSSneak.mp3",1);
	soundSys.loadStream("battle.mp3",2);
	//load sounds
	soundSys.load("MGSAleartSound.wav",0);
	//start menu music
	soundSys.PlayStream(0,musicMute);
}

//soundSys.load("FileName",&sound); to load a sound
//soundSys.loadStream("FileName",&sound); to load a sound to steam
//soundSys.Play(sound); to play a sound
//soundSys.PlayStream(sound,bMuted); to play or mute stream

void PokeGear::update()
{
	Pos temp;
	int numobjs = 0,numSprits = 0,numText = 0;
	int tempInt;
	input.Update(keyboard,mouse);
	renderInfo tempRend;
	switch(curState)
	{
	case MainMenu:
		menuSys.GetRender(Sprites[numSprits],numSprits,Text,numText);
		tempRend.tex = textures[13].objTex;
		D3DXMatrixIdentity(&tempRend.matrix);
		Sprites[numSprits] = tempRend;
		++numSprits;
		if((mouse.rgbButtons[0]&0x80)||(keyboard[DIK_RETURN]&0x80))
		{
			if(menuSys.getPushed(tempInt,menuPushed))
			{
				switch(tempInt)
				{
				case 0:
					curState = story;
					soundSys.PlayStream(0,true);
					soundSys.PlayStream(1,musicMute);
					break;
				case 4:
					PostQuitMessage(0);
					break;
				}
			}
		}
		menuSys.Update(keyboard,mouse,menuPushed);
		break;
	case stealth:
		//update and get render for map and ents
		tempInt = sneak.Update(keyboard,bCanInput,mouse,curPlay,&soundSys);
		sneak.getRend(D3Objs,numobjs,Sprites,numSprits,Text,numText);
		switch(tempInt)
		{
		case 0:
			temp = curPlay.getRen();
			//move cam
			camera.cam_pos.x = temp.X;
			camera.cam_pos.y = temp.Y;
			camera.cam_look_pos.x = temp.X;
			camera.cam_look_pos.y = temp.Y;
			//add player to draw list
			D3DXMatrixTranslation(&Models[0].matrix,temp.X,temp.Y,temp.Z);
			D3Objs[numobjs] = Models[0];
			D3DXMatrixTranslation(&D3Objs[numobjs].matrix,temp.X,temp.Y,temp.Z);
			++numobjs;
			break;
		case 1:
			curState = battle;
			curBattleState = BATTLESTART;
			soundSys.PlayStream(1,true);
			soundSys.PlayStream(2,musicMute);
			break;
		case 2:
			newscene = true;
			curState = story;
			break;
		case 3:
			curState = victory;
			menuSys.setQuitMenu();
			break;
		}
		//end stealth
		break;
	case story:
		talks.update(keyboard,bCanInput2,newscene);
		talks.getRend(Sprites,numSprits,Text,numText);
		if(talks.getname() == "endscene")
		{
			curState = stealth;
		}
		break;
	case battle:
		battler.GetBattleRender(Sprites,numSprits,Text,numText,curPlay.getEnemy().getSpecies());
		switch(curBattleState) {
		case BATTLESTART:
			curPlay.randomizeEnemy();
			battler.menuReset(curPlay.getPikachu(),curPlay.getEnemy());
			curBattleState = MAIN;
			break;
		case MAIN:
			if((mouse.rgbButtons[0]&0x80)||(keyboard[DIK_RETURN]&0x80)) {
				if(battler.getBattleMenu().getPushed(tempInt,menuPushed)) {
					switch(tempInt) {
					case 0: // Fight
						curBattleState = MOVES;
						battler.menuResetWithMoves(curPlay.getPikachu(),curPlay.getEnemy());
						break;
					case 1: // Bag

						break;
					case 2: // Pokemon

						break;
					case 3: // Run

						break;
					}
				}
			}
			break;
		case MOVES:
			if((mouse.rgbButtons[0]&0x80)||(keyboard[DIK_RETURN]&0x80)) {
				if(battler.getBattleMenu().getPushed(tempInt,menuPushed)) {
					switch(tempInt) {
					case 0:
						if(curPlay.getPikachu().getMove(0).getCurPP() > 0) {
							curPlay.setPlayerMove(0);
							curPlay.decrementPikaPP(0);
							battler.menuResetWithMoves(curPlay.getPikachu(),curPlay.getEnemy());
							//display.zeroWaitTime();
							curBattleState = WAIT;
						}
						else {

						}
						break;
					case 1:
						if(curPlay.getPikachu().getMove(1).getCurPP() > 0) {
							curPlay.setPlayerMove(1);
							curPlay.decrementPikaPP(1);
							battler.menuResetWithMoves(curPlay.getPikachu(),curPlay.getEnemy());
							//display.zeroWaitTime();
							curBattleState = WAIT;
						}
						else {

						}
						break;
					case 2:
						if(curPlay.getPikachu().getMove(2).getCurPP() > 0) {
							curPlay.setPlayerMove(2);
							curPlay.decrementPikaPP(2);
							battler.menuResetWithMoves(curPlay.getPikachu(),curPlay.getEnemy());
							//display.zeroWaitTime();
							curBattleState = WAIT;
						}
						else {

						}
						break;
					case 3:
						if(curPlay.getPikachu().getMove(3).getCurPP() > 0) {
							curPlay.setPlayerMove(3);
							curPlay.decrementPikaPP(3);
							battler.menuResetWithMoves(curPlay.getPikachu(),curPlay.getEnemy());
							//display.zeroWaitTime();
							curBattleState = WAIT;
						}
						else {

						}
						break;
					}
				}
			}
			break;
		case WAIT:
			if(display.getWaitTime() >= 4 && !battleover) {
				if(donePlayerAttack && doneEnemyAttack) {
					display.zeroWaitTime();
					battler.menuReset(curPlay.getPikachu(), curPlay.getEnemy());
					curBattleState = MAIN;
					donePlayerAttack = false;
					doneEnemyAttack = false;
				}
				else {
					display.zeroWaitTime();
					curBattleState = RESOLVEMOVES;
				}
			}
			else if(display.getWaitTime() >= 4 && battleover) {
				curBattleState = BATTLESTART;
				curState = stealth;
				soundSys.PlayStream(2,true);
				soundSys.PlayStream(1,musicMute);
				donePlayerAttack = false;
				doneEnemyAttack = false;
				battleover = false;
			}

			break;
		case RESOLVEMOVES:
			if(curPlay.getPikachu().getCurHP() <=0) {
				playerlost = true;
				curBattleState = BATTLESTART;
				curState = GameOver;
				soundSys.PlayStream(2,true);
				soundSys.PlayStream(1,musicMute);
				menuSys.setQuitMenu();
				curPlay.initPikachu();
				donePlayerAttack = false;
				doneEnemyAttack = false;
				battleover = false;
			}
			else if(curPlay.getPikachu().getSpeed() >= curPlay.getEnemy().getSpeed() && !donePlayerAttack || doneEnemyAttack) {
				curPlay.resolveMoveInOrder(true);
				donePlayerAttack = true;
				battler.menuResetWithMoves(curPlay.getPikachu(), curPlay.getEnemy());
				battler.addText(curPlay.getPikachu(),curPlay.getPikachu().getMove(curPlay.getPlayerMove()));
			}
			else if(curPlay.getEnemy().getCurHP() > 0){
				int randomenemymove = rand()%4;
				curPlay.setEnemyMove(randomenemymove);
				curPlay.decrementEnemyPP(randomenemymove);
				curPlay.resolveMoveInOrder(false);
				doneEnemyAttack = true;
				battler.menuResetWithMoves(curPlay.getPikachu(), curPlay.getEnemy());
				battler.addText(curPlay.getEnemy(),curPlay.getEnemy().getMove(curPlay.getEnemyMove()));
			}
			else {
				doneEnemyAttack = false;
				donePlayerAttack = false;
				battleover = true;
			}
			if(battleover)
				curBattleState = OVER;
			else
				curBattleState = WAIT;
			break;
		case OVER:
			display.zeroWaitTime();
			battler.addYouWin();
			curBattleState = WAIT;
			break;
		}
		battler.Update(keyboard,mouse,menuPushed);
		break;
	case GameOver:
		menuSys.GetRender(Sprites[numSprits],numSprits,Text,numText);
		tempRend.tex = textures[14].objTex;
		D3DXMatrixIdentity(&tempRend.matrix);
		Sprites[numSprits] = tempRend;
		++numSprits;
		if((mouse.rgbButtons[0]&0x80)||(keyboard[DIK_RETURN]&0x80))
		{
			if(menuSys.getPushed(tempInt,menuPushed))
			{
				switch(tempInt)
				{
				case 0:
					PostQuitMessage(0);
					break;
				}
			}
		}
		menuSys.Update(keyboard,mouse,menuPushed);
		break;
	case victory:
		menuSys.GetRender(Sprites[numSprits],numSprits,Text,numText);
		tempRend.tex = textures[15].objTex;
		D3DXMatrixIdentity(&tempRend.matrix);
		Sprites[numSprits] = tempRend;
		++numSprits;
		if((mouse.rgbButtons[0]&0x80)||(keyboard[DIK_RETURN]&0x80))
		{
			if(menuSys.getPushed(tempInt,menuPushed))
			{
				switch(tempInt)
				{
				case 0:
					PostQuitMessage(0);
					break;
				}
			}
		}
		menuSys.Update(keyboard,mouse,menuPushed);
		break;
		break;
	}
	display.Render(camera,D3Objs,numobjs,Sprites,numSprits,Text,numText);
	soundSys.update();
}

void PokeGear::shutdown()
{
	for(int i = 0;i<maxModels;++i)
	{
		if(Models[i].obj != 0)
		{
			Models[i].objDec->Release();
			Models[i].objDec = 0;
			Models[i].objInd->Release();
			Models[i].objInd = 0;
			Models[i].obj->Release();
			Models[i].obj = 0;
		}
	}
	for(int i = 0;i<maxtexture;++i)
	{
		if(textures[i].objTex!=0)
		{
			textures[i].objTex->Release();
			textures[i].objTex = 0;
		}
	}
	sneak.shutdown();
	input.ShutDown();
	display.Shutdown();
}

PokeGear::~PokeGear()
{
	shutdown();
}
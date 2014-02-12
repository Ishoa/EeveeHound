#include "PokeGear.h"

PokeGear::PokeGear()
{
	//cam setup
	camera.cam_up_vec = D3DXVECTOR3(0,1,0);
	camera.cam_pos = D3DXVECTOR3(0,-1,-10);
	camera.cam_look_pos = D3DXVECTOR3(0,0,0);
	bCanInput = true;
	menuPushed = false;
	curState = MainMenu;
}

void PokeGear::init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
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
	materials[0].Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);		// Ambient color reflected
	materials[0].Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);		// Diffuse color reflected
	materials[0].Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Emissive color reflected
	materials[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// Specular
	materials[0].Power = 0.0f;										// Specular highlight intensity
	//player Model
	display.CreateCube(Models[0],2,1,1);
	Models[0].objMat = &materials[0];
	ZeroMemory(&Models[0].matrix,sizeof(Models[0].matrix));
	D3DXMatrixTranslation(&Models[0].matrix,0,0,1);
	//player texture
	display.LoadTex(L"playtex.bmp",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[0].texInfo,0,&textures[0].objTex);
	Models[0].objTex = textures[0].objTex;
	//world Model base
	display.CreateUncenteredCube(Models[1],1,1,1);
	//floor mat
	materials[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	materials[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Diffuse color reflected
	materials[1].Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Emissive color reflected
	materials[1].Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Specular
	materials[1].Power = 0.0f;										// Specular highlight intensity
	//wall mat
	materials[2].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	materials[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Diffuse color reflected
	materials[2].Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Emissive color reflected
	materials[2].Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Specular
	materials[2].Power = 0.0f;										// Specular highlight intensity
	//test set texture for world
	Models[1].objTex = textures[0].objTex;
	//end art load
	sneak.init(Models[1],&materials[1],&materials[2],textures[0].objTex);
	sneak.setPlayPos(curPlay,0,0);
	menuSys.reset();
	//set sprite tex
	curSpri.tex = textures[0].objTex;
	curSpri.texinfo = textures[0].texInfo;
	menuSys.setMouseSprite(curSpri);
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
	switch(curState)
	{
	case MainMenu:
		menuSys.GetRender(Sprites[numSprits],numSprits,Text,numText);
		if((mouse.rgbButtons[0]&0x80)||(keyboard[DIK_RETURN]&0x80))
		{
			if(menuSys.getPushed(tempInt,menuPushed))
			{
				switch(tempInt)
				{
				case 0:
					curState = stealth;
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
		sneak.Update(keyboard,bCanInput,mouse,curPlay,&soundSys);
		sneak.getRend(D3Objs,numobjs,Sprites,numSprits,Text,numText);
		temp = curPlay.getRen();
		//move cam
		camera.cam_pos.x = temp.X;
		camera.cam_pos.y = temp.Y;
		camera.cam_look_pos.x =temp.X;
		camera.cam_look_pos.y = temp.Y;
		//add player to draw list
		D3DXMatrixTranslation(&Models[0].matrix,temp.X,temp.Y,temp.Z);
		D3Objs[numobjs] = Models[0];
		D3DXMatrixTranslation(&D3Objs[numobjs].matrix,temp.X,temp.Y,temp.Z);
		++numobjs;
		//end stealth
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
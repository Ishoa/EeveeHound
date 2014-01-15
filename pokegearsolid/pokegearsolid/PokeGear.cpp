#include "PokeGear.h"

PokeGear::PokeGear()
{
	//cam setup
	camera.cam_up_vec = D3DXVECTOR3(0,0,1);
	camera.cam_pos = D3DXVECTOR3(0,10,0);
	camera.cam_look_pos = D3DXVECTOR3(0,0,0);
}

void PokeGear::init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
	input.init(hWnd,hInst);
	display.Init(hWnd,hInst,bWindowed);
	for(int i = 0;i<maxModels;++i)
	{
		Models[i].obj = 0;
	}
	for(int i = 0;i<maxtexture;++i)
	{
		textures[i].objTex = 0;
	}
	//movement demo
	materials[0].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// Ambient color reflected
	materials[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// Diffuse color reflected
	materials[0].Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Emissive color reflected
	materials[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// Specular
	materials[0].Power = 30.0f;										// Specular highlight intensity
	display.CreateCube(Models[0],2,1,1);
	Models[0].objMat = &materials[0];
	ZeroMemory(&Models[0].matrix,sizeof(Models[0].matrix));
	D3DXMatrixTranslation(&Models[0].matrix,0,0,0);
	display.LoadTex(L"playtex.bmp",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&textures[0].texInfo,0,&textures[0].objTex);
	Models[0].objTex = textures[0].objTex;
	//end movment demo
}

void PokeGear::update()
{
	int numobjs = 0;
	input.Update(keyboard,mouse);
	//movement demo
	D3Objs[numobjs] = Models[0];
	++numobjs;
	//end movement demo
	display.Render(camera,D3Objs,numobjs,Sprites,0,Text,0);
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
	input.ShutDown();
	display.Shutdown();
}

PokeGear::~PokeGear()
{
	shutdown();
}
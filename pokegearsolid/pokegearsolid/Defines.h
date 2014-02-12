#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define Texture IDirect3DTexture9*
#define TexInfo D3DXIMAGE_INFO

#include <fmod.hpp>
#pragma comment(lib,"Fmodex_vc.lib")
//sound for sound system
#define Sound FMOD::Sound*

struct D3Object
{
	IDirect3DVertexBuffer9* obj;
	IDirect3DIndexBuffer9* objInd;
	IDirect3DVertexDeclaration9* objDec;
	D3DMATERIAL9* objMat;
	Texture objTex;
	D3DXMATRIX matrix;
	int numVerts;
	int numPrim;
};

struct TextureStruc
{
	LPCWSTR name;
	Texture objTex;
	TexInfo texInfo;
};

struct renderInfo
{
	Texture tex;
	TexInfo texinfo;
	D3DXMATRIX matrix;
};

struct sprit
{
	Texture tex;
	TexInfo texinfo;
};

struct TextStruct
{
	RECT rec;
	LPCWSTR text;
	D3DCOLOR textColor;
};

struct Pos
{
	float X;
	float Y;
	float Z;
};

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 uv;
};

struct cam
{
	D3DXVECTOR3 cam_pos;
	D3DXVECTOR3 cam_look_pos;
	D3DXVECTOR3 cam_up_vec;
	float fov_deg;
	float drawDist;
};
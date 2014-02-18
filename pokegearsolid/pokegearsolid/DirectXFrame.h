#pragma once

#pragma comment(lib, "winmm.lib")
//////////////////////////////////////////////////////////////////////////
// Direct3D 9 headers and libraries required
//////////////////////////////////////////////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "Defines.h"
//////////////////////////////////////////////////////////////////////////
// DirectInput headers and libraries
//////////////////////////////////////////////////////////////////////////

class DirectXFrame
{
	HWND m_hWnd;
	HINSTANCE m_hInts;
	bool m_bVsync;
	int width;
	int height;
	int FPS;
	float dt,frams,ltime,curTime;

	IDirect3D9* m_pD3DObject;
	IDirect3DDevice9* m_pD3DDevice;
	D3DCAPS9 m_D3DCaps;
	D3DLIGHT9 m_Light;

	ID3DXFont* m_pD3DFont;

	ID3DXSprite* m_pD3DSprite;
public:
	DirectXFrame(void);
	~DirectXFrame(void);
	void Update();
	void Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed);
	void Render(cam &caminf,D3Object[],int NumObjs,renderInfo[],int NumSprit,TextStruct[],int NumText);
	void LoadTex(LPCWSTR FileName,UINT Width,UINT Height,UINT MipLevels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,DWORD Filter,DWORD MipFilter,D3DCOLOR ColorKey,D3DXIMAGE_INFO *SrcInfo,PALETTEENTRY *pPalette,LPDIRECT3DTEXTURE9 *Tex);
	void CreateCube(D3Object&,float height,float width,float depth);
	void CreateUVCube(D3Object&,float height,float width,float depth);
	void CreateUncenteredCube(D3Object&,float height,float width,float depth);
	void Shutdown();
};
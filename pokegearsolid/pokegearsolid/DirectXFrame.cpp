#include "DirectXFrame.h"
#include <stdio.h>
#include <ctime>
#pragma comment(lib, "winmm.lib")


DirectXFrame::DirectXFrame()
{
	m_bVsync		= false;
	m_pD3DObject	= 0;
	m_pD3DDevice	= 0;
	width = 0;
	height = 0;
	//fps counter stuffs
	frams = 0;
	FPS = 100;
	ltime = GetTickCount();
	curTime = ltime;
	dt = 0;
}

DirectXFrame::~DirectXFrame()
{
	Shutdown();
}

void DirectXFrame::Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
	m_hWnd = hWnd;
	//////////////////////////////////////////////////////////////////////////
	// Direct3D Foundations - D3D Object, Present Parameters, and D3D Device
	//////////////////////////////////////////////////////////////////////////

	// Create the D3D Object
	m_pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);

	// Find the width and height of window using hWnd and GetWindowRect()
	RECT rect;
	GetWindowRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	// Set D3D Device presentation parameters before creating the device
	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));  // NULL the structure's memory

	D3Dpp.hDeviceWindow					= hWnd;										// Handle to the focus window
	D3Dpp.Windowed						= bWindowed;								// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;								// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;										// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;										// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;							// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= height;									// Make sure resolution is supported, use adapter modes
	D3Dpp.BackBufferWidth				= width;									// (Same as above)
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;					// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= m_bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE; // Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= bWindowed ? 0 : D3DPRESENT_RATE_DEFAULT;	// Full-screen refresh rate, use adapter modes or default
	D3Dpp.MultiSampleQuality			= 0;										// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;						// MSAA currently off, check documentation for support.

	// Check device capabilities
	DWORD deviceBehaviorFlags = 0;
	m_pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	// Determine vertex processing mode
	if(m_D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		// Hardware vertex processing supported? (Video Card)
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	}
	else
	{
		// If not, use software (CPU)
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}

	// If hardware vertex processing is on, check pure device support
	if(m_D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;	
	}

	// Create the D3D Device with the present parameters and device flags above
	m_pD3DObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
		D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
		hWnd,					// handle to the focus window
		deviceBehaviorFlags,	// behavior flags
		&D3Dpp,					// presentation parameters
		&m_pD3DDevice);			// returned device pointer

	//*************************************************************************

	//////////////////////////////////////////////////////////////////////////
	// Create a Font Object
	//////////////////////////////////////////////////////////////////////////
	D3DXCreateFont(m_pD3DDevice,30,0,FW_BOLD,0,false,DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman"),&m_pD3DFont);

	//////////////////////////////////////////////////////////////////////////
	// Create Sprite Object and Textures
	//////////////////////////////////////////////////////////////////////////
	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);

	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(60, 60, 60));
	m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	ZeroMemory(&m_Light, sizeof(m_Light));

	// Ambient light color emitted from this light
	m_Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// Diffuse light color emitted from this light
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// Specular light color emitted from this light
	m_Light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// Light Type (Point) Requires: Position, Range, Attenuation
	m_Light.Type = D3DLIGHT_POINT;	// Point, alternatively D3DLIGHT_DIRECTIONAL or D3DLIGHT_SPOT
	// Light Position
	m_Light.Position = D3DXVECTOR3(30.0f, 10.0f, -10.0f); 
	// Range of Light
	m_Light.Range = 100.0f;
	// Light Attenuation
	m_Light.Attenuation0 = 0.0f;	// Constant
	m_Light.Attenuation1 = 0.05f;	// Linear
	m_Light.Attenuation2 = 0.0f;	// Quadratic

	// Set Light
	m_pD3DDevice->SetLight(0, &m_Light);	// 0 is the index for this light
	// Enable Light
	m_pD3DDevice->LightEnable(0, true);
}

void DirectXFrame::Update()
{

}

void DirectXFrame::Render(cam &caminf,D3Object D3Objs[],int NumObjs,renderInfo Renders[],int NumSprit,TextStruct Texts[],int NumText)
{
	// If the device was not created successfully, return
	if(!m_pD3DDevice)
		return;
	//*************************************************************************
	RECT rect;
	GetWindowRect(m_hWnd, &rect);

	D3DRECT winRect;
	winRect.x1 = rect.left;
	winRect.x2 = rect.right;
	winRect.y1 = rect.top;
	winRect.y2 = rect.bottom;
	
	rect.right -= rect.left;
	rect.left = 0;
	rect.bottom -= rect.top;
	rect.top = 0;


	if(SUCCEEDED(m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(m_pD3DDevice->BeginScene()))
		{
			D3DXMATRIX TransMat;
			//set cam
			D3DXMatrixLookAtLH(&TransMat,&caminf.cam_pos,&caminf.cam_look_pos,&caminf.cam_up_vec);
			m_pD3DDevice->SetTransform(D3DTS_VIEW,&TransMat);
			D3DXMatrixPerspectiveFovLH(&TransMat,D3DXToRadian(caminf.fov_deg),width/height,1.0f,caminf.drawDist);
			m_pD3DDevice->SetTransform(D3DTS_PROJECTION,&TransMat);
			//start 3d stuff
			for(int i = 0;i<NumObjs;++i)
			{
				//obj info
				m_pD3DDevice->SetTransform(D3DTS_WORLD,&D3Objs[i].matrix);
				m_pD3DDevice->SetStreamSource(0,D3Objs[i].obj, 0, sizeof(Vertex));
				m_pD3DDevice->SetIndices(D3Objs[i].objInd);
				m_pD3DDevice->SetVertexDeclaration(D3Objs[i].objDec);
				//set texture
				m_pD3DDevice->SetTexture(0,D3Objs[i].objTex);
				m_pD3DDevice->SetMaterial(D3Objs[i].objMat);
				//set trans
				m_pD3DDevice->SetTransform(D3DTS_WORLD, &D3Objs[i].matrix);
				//
				m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,D3Objs[i].numVerts,0,D3Objs[i].numPrim);
			}
			//end 3d stuff
			//start sprites
			if(SUCCEEDED(m_pD3DSprite->Begin(NULL)))
			{
				IDirect3DTexture9* Tex;
				D3DXIMAGE_INFO TexInf;
				for(int i = 0;i<NumSprit;++i)
				{
					TransMat = Renders[i].matrix;
					Tex = Renders[i].tex;
					TexInf = Renders[i].texinfo;
					//set sprite trans
					m_pD3DSprite->SetTransform(&TransMat);
					//Draw sprite
					m_pD3DSprite->Draw(Tex,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
				}
				m_pD3DSprite->End();
			}
			//end sprites
			//start text
			for(int i = 0;i<NumText;++i)
			{
				m_pD3DFont->DrawText(0,Texts[i].text,-1,&Texts[i].rec,DT_TOP|DT_CENTER|DT_NOCLIP,Texts[i].textColor);
			}
			//end text
			//fps start
			wchar_t buffer[190];
			swprintf_s(buffer, 190, L"FPS: %d", FPS);
			m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
			//fps end
			m_pD3DDevice->EndScene();	
		}
		m_pD3DDevice->Present(NULL,NULL,NULL,NULL);
	}
	//update fps counter
	curTime = GetTickCount();
	if(curTime-ltime >= 1000.0f)
	{
		FPS = frams;
		frams = 0;
		ltime = curTime;
	}
	else
	{
		++frams;
	}
}

void DirectXFrame::Shutdown()
{
	//Sprite
	if(m_pD3DSprite != NULL)
	{
		m_pD3DSprite->Release();
		m_pD3DSprite = NULL;
	}
	// Font
	if(m_pD3DFont != NULL)
	{
		m_pD3DFont->Release();
		m_pD3DFont = NULL;
	}
	// 3DDevice	
	if(m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	// 3DObject
	if(m_pD3DObject != NULL)
	{
		m_pD3DObject->Release();
		m_pD3DObject = NULL;
	}
}

void DirectXFrame::LoadTex(LPCWSTR FileName,UINT Width,UINT Height,UINT MipLevels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,DWORD Filter,DWORD MipFilter,D3DCOLOR ColorKey,D3DXIMAGE_INFO *SrcInfo,PALETTEENTRY *pPalette,LPDIRECT3DTEXTURE9 *Tex)
{
	D3DXCreateTextureFromFileEx(m_pD3DDevice,FileName,Width,Height,MipLevels,Usage,Format,Pool,Filter,MipFilter,ColorKey,SrcInfo,pPalette,Tex);
}

void DirectXFrame::CreateCube(D3Object& obj,float height,float width,float depth)
{
	float h = height/2;
	float w = width/2;
	float d = depth/2;
	Vertex m_cubeVerts[24];
	WORD m_cubeIndices[36];
	// Load vertex info, listed per cube face quads
	// Front 
	m_cubeVerts[0].position = D3DXVECTOR3(-w, -h, -d); 
	m_cubeVerts[1].position = D3DXVECTOR3(-w, h, -d); 
	m_cubeVerts[2].position = D3DXVECTOR3(w, h, -d); 
	m_cubeVerts[3].position = D3DXVECTOR3(w, -h, -d); 
	D3DXVec3Normalize(&m_cubeVerts[0].normal, &D3DXVECTOR3(0.0f, 0.0f, -1.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[1].normal, &D3DXVECTOR3(0.0f, 0.0f, -1.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[2].normal, &D3DXVECTOR3(0.0f, 0.0f, -1.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[3].normal, &D3DXVECTOR3(0.0f, 0.0f, -1.0f)); 
	m_cubeVerts[0].uv = D3DXVECTOR2(0.0f, 1.0f); 
	m_cubeVerts[1].uv = D3DXVECTOR2(0.0f, 0.0f); 
	m_cubeVerts[2].uv = D3DXVECTOR2(1.0f, 0.0f); 
	m_cubeVerts[3].uv = D3DXVECTOR2(1.0f, 1.0f);

	// Back 
	m_cubeVerts[4].position = D3DXVECTOR3(-w, -h, d); 
	m_cubeVerts[5].position = D3DXVECTOR3(w, -h, d); 
	m_cubeVerts[6].position = D3DXVECTOR3(w, h, d); 
	m_cubeVerts[7].position = D3DXVECTOR3(-w, h, d); 
	D3DXVec3Normalize(&m_cubeVerts[4].normal, &D3DXVECTOR3(0.0f, 0.0f, 1.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[5].normal, &D3DXVECTOR3(0.0f, 0.0f, 1.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[6].normal, &D3DXVECTOR3(0.0f, 0.0f, 1.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[7].normal, &D3DXVECTOR3(0.0f, 0.0f, 1.0f)); 
	m_cubeVerts[4].uv = D3DXVECTOR2(1.0f, 1.0f); 
	m_cubeVerts[5].uv = D3DXVECTOR2(0.0f, 1.0f); 
	m_cubeVerts[6].uv = D3DXVECTOR2(0.0f, 0.0f); 
	m_cubeVerts[7].uv = D3DXVECTOR2(1.0f, 0.0f);

	// Top 
	m_cubeVerts[8].position = D3DXVECTOR3(-w, h, -d); 
	m_cubeVerts[9].position = D3DXVECTOR3(-w, h, d); 
	m_cubeVerts[10].position = D3DXVECTOR3(w, h, d); 
	m_cubeVerts[11].position = D3DXVECTOR3(w, h, -d); 
	D3DXVec3Normalize(&m_cubeVerts[8].normal, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[9].normal, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[10].normal, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[11].normal, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)); 
	m_cubeVerts[8].uv = D3DXVECTOR2(0.0f, 1.0f); 
	m_cubeVerts[9].uv = D3DXVECTOR2(0.0f, 0.0f); 
	m_cubeVerts[10].uv = D3DXVECTOR2(1.0f, 0.0f); 
	m_cubeVerts[11].uv = D3DXVECTOR2(1.0f, 1.0f);

	// Bottom 
	m_cubeVerts[12].position = D3DXVECTOR3(-w, -h, -d); 
	m_cubeVerts[13].position = D3DXVECTOR3(w, -h, -d); 
	m_cubeVerts[14].position = D3DXVECTOR3(w, -h, d); 
	m_cubeVerts[15].position = D3DXVECTOR3(-w, -h, d); 
	D3DXVec3Normalize(&m_cubeVerts[12].normal, &D3DXVECTOR3(0.0f, -1.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[13].normal, &D3DXVECTOR3(0.0f, -1.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[14].normal, &D3DXVECTOR3(0.0f, -1.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[15].normal, &D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	m_cubeVerts[12].uv = D3DXVECTOR2(1.0f, 1.0f); 
	m_cubeVerts[13].uv = D3DXVECTOR2(0.0f, 1.0f); 
	m_cubeVerts[14].uv = D3DXVECTOR2(0.0f, 0.0f); 
	m_cubeVerts[15].uv = D3DXVECTOR2(1.0f, 0.0f);

	// Left 
	m_cubeVerts[16].position = D3DXVECTOR3(-w, -h, d); 
	m_cubeVerts[17].position = D3DXVECTOR3(-w, h, d); 
	m_cubeVerts[18].position = D3DXVECTOR3(-w, h, -d); 
	m_cubeVerts[19].position = D3DXVECTOR3(-w, -h, -d); 
	D3DXVec3Normalize(&m_cubeVerts[16].normal, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[17].normal, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[18].normal, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[19].normal, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f)); 
	m_cubeVerts[16].uv = D3DXVECTOR2(0.0f, 1.0f); 
	m_cubeVerts[17].uv = D3DXVECTOR2(0.0f, 0.0f); 
	m_cubeVerts[18].uv = D3DXVECTOR2(1.0f, 0.0f); 
	m_cubeVerts[19].uv = D3DXVECTOR2(1.0f, 1.0f);

	// Right 
	m_cubeVerts[20].position = D3DXVECTOR3(w, -h, -d); 
	m_cubeVerts[21].position = D3DXVECTOR3(w, h, -d); 
	m_cubeVerts[22].position = D3DXVECTOR3(w, h, d); 
	m_cubeVerts[23].position = D3DXVECTOR3(w, -h, d); 
	D3DXVec3Normalize(&m_cubeVerts[20].normal, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[21].normal, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[22].normal, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)); 
	D3DXVec3Normalize(&m_cubeVerts[23].normal, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)); 
	m_cubeVerts[20].uv = D3DXVECTOR2(0.0f, 1.0f); 
	m_cubeVerts[21].uv = D3DXVECTOR2(0.0f, 0.0f); 
	m_cubeVerts[22].uv = D3DXVECTOR2(1.0f, 0.0f); 
	m_cubeVerts[23].uv = D3DXVECTOR2(1.0f, 1.0f);

	// Load index info, refers into index into verts array to compose triangles 
	// Note: A clockwise winding order of verts will show the front face.

	// Front 
	m_cubeIndices[0] = 0; m_cubeIndices[1] = 1; m_cubeIndices[2] = 2; // Triangle 0 
	m_cubeIndices[3] = 0; m_cubeIndices[4] = 2; m_cubeIndices[5] = 3; // Triangle 1

	// Back 
	m_cubeIndices[6] = 4; m_cubeIndices[7] = 5; m_cubeIndices[8] = 6; // Triangle 2 
	m_cubeIndices[9] = 4; m_cubeIndices[10] = 6; m_cubeIndices[11] = 7; // Triangle 3

	// Top 
	m_cubeIndices[12] = 8; m_cubeIndices[13] = 9; m_cubeIndices[14] = 10; // Triangle 4 
	m_cubeIndices[15] = 8; m_cubeIndices[16] = 10; m_cubeIndices[17] = 11; // Triangle 5

	// Bottom 
	m_cubeIndices[18] = 12; m_cubeIndices[19] = 13; m_cubeIndices[20] = 14; // Triangle 6 
	m_cubeIndices[21] = 12; m_cubeIndices[22] = 14; m_cubeIndices[23] = 15; // Triangle 7

	// Left 
	m_cubeIndices[24] = 16; m_cubeIndices[25] = 17; m_cubeIndices[26] = 18; // Triangle 8 
	m_cubeIndices[27] = 16; m_cubeIndices[28] = 18; m_cubeIndices[29] = 19; // Triangle 9

	// Right 
	m_cubeIndices[30] = 20; m_cubeIndices[31] = 21; m_cubeIndices[32] = 22; // Triangle 10 
	m_cubeIndices[33] = 20; m_cubeIndices[34] = 22; m_cubeIndices[35] = 23; // Triangle 11
	//create decloration
	D3DVERTEXELEMENT9 decl[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	m_pD3DDevice->CreateVertexDeclaration(decl, &obj.objDec);
	//create memory
	m_pD3DDevice->CreateVertexBuffer(24*sizeof(Vertex),D3DUSAGE_WRITEONLY,0,D3DPOOL_MANAGED,&obj.obj,0);
	m_pD3DDevice->CreateIndexBuffer(36*sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&obj.objInd,0);
	//copy info to memory
	VOID* pVertices; VOID* pInd;
	obj.obj->Lock(0,0,&pVertices,0);
	memcpy(pVertices,m_cubeVerts,24*sizeof(Vertex));
	obj.obj->Unlock();

	obj.objInd->Lock(0,0,&pInd,0);
	memcpy(pInd,m_cubeIndices,36*sizeof(WORD));
	obj.objInd->Unlock();

	obj.numVerts = 24;
	obj.numPrim = 12;
}
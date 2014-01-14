#include "dxinput.h"

dxinputframe::dxinputframe()
{
	m_pDIObj = NULL;
	m_pDIKeyboard = NULL;
	m_pDIMouse = NULL;
}

void dxinputframe::init(HWND& hWnd,HINSTANCE& hInst)
{
	DirectInput8Create(hInst,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pDIObj,NULL);
	m_pDIObj->CreateDevice(GUID_SysKeyboard,&m_pDIKeyboard,NULL);
	m_pDIObj->CreateDevice(GUID_SysMouse,&m_pDIMouse,NULL);
	m_pDIKeyboard->SetDataFormat(&c_dfDIKeyboard); 
	m_pDIMouse->SetDataFormat(&c_dfDIMouse2);
	m_pDIKeyboard->SetCooperativeLevel(hWnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pDIMouse->SetCooperativeLevel(hWnd,DISCL_FOREGROUND | DISCL_EXCLUSIVE);
}

void dxinputframe::ShutDown()
{
	if(m_pDIKeyboard != NULL)
	{
		m_pDIKeyboard->Release();
		m_pDIKeyboard = NULL;
	}
	if(m_pDIMouse != NULL)
	{
		m_pDIMouse->Release();
		m_pDIMouse = NULL;
	}
	if(m_pDIObj != NULL)
	{
		m_pDIObj->Release();
		m_pDIObj = NULL;
	}
}

dxinputframe::~dxinputframe()
{
	ShutDown();
}

void dxinputframe::Update(char keyboard[],DIMOUSESTATE2 &mouse)
{
	char buffer[256];
	DIMOUSESTATE2 mouseState;
	ZeroMemory(buffer,sizeof(buffer));
	ZeroMemory(&mouseState,sizeof(mouseState));
	if(m_pDIKeyboard->Acquire() != DIERR_INPUTLOST)
		m_pDIKeyboard->GetDeviceState(sizeof(buffer),(LPVOID)&buffer);
	if(m_pDIMouse->Acquire()!= DIERR_INPUTLOST)
		m_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE2),&mouseState);
	mouse = mouseState;
	//keyboard = buffer;
	for(int i = 0;i<sizeof(buffer)-1;i++)
	{
		keyboard[i] = buffer[i];
	}
}
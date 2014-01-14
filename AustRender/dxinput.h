#pragma once

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class dxinputframe
{
private:
	IDirectInput8* m_pDIObj;
	IDirectInputDevice8* m_pDIKeyboard;
	IDirectInputDevice8* m_pDIMouse;
public:
	dxinputframe();
	void init(HWND& hWnd,HINSTANCE& hInst);
	void ShutDown();
	~dxinputframe();
	void Update(char[],DIMOUSESTATE2&);
};
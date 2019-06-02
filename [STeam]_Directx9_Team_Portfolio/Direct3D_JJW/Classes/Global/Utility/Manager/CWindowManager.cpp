#include "CWindowManager.h"
#include "../Interface/IWindowMessageHandler.h"

//! 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND a_hWindow,
	UINT a_nMessage,
	WPARAM a_wParam,
	LPARAM a_lParam)
{
	static IWindowMessageHandler *pHandler = nullptr;

	switch (a_nMessage) {
		case WM_CREATE: {

			auto pstCreateStruct = (CREATESTRUCT *)a_lParam;
			pHandler = (IWindowMessageHandler *)pstCreateStruct->lpCreateParams;
			break;
		}
		case WM_SETCURSOR:
			return TRUE;

	}
	if (pHandler != nullptr) {
		return pHandler->handleWindowMessage(a_hWindow,
			a_nMessage,
			a_wParam,
			a_lParam);
	}

	return DefWindowProc(a_hWindow,
		a_nMessage,
		a_wParam,
		a_lParam);
}

void CWindowManager::init(HINSTANCE a_hInstance, const int a_nOptions, const SIZE a_stWindowSize, IWindowMessageHandler * a_pHandler)
{
	m_nOptions = a_nOptions;
	m_stWindowSize = a_stWindowSize;
	m_hInstance = a_hInstance;
	m_pHandler = a_pHandler;

	m_hWindow = this->createWindow();
}

SIZE CWindowManager::getWindowSize(void)
{
	return m_stWindowSize;
}

HWND CWindowManager::getWindowHandle(void)
{
	return m_hWindow;
}

HINSTANCE CWindowManager::getInstanceHandle(void)
{
	return m_hInstance;
}

HWND CWindowManager::createWindow(void)
{
	WNDCLASS stWindowClass = {
		CS_VREDRAW | CS_HREDRAW,
		WndProc,
		0,
		0,
		m_hInstance,
		LoadIconA(m_hInstance, MAKEINTRESOURCEA("IDI_ICON1")),
		LoadCursorFromFileA("Resources/Cursor/Arrow.cur"),
		(HBRUSH)GetStockObject(COLOR_WINDOW + 1),
		nullptr,
		_T("[STeam] Tera Online")
	};

	// 클래스를 등록한다
	RegisterClass(&stWindowClass);

	RECT stWindowRect = {
		0, 0, m_stWindowSize.cx, m_stWindowSize.cy
	};

	// 윈도우의 크기를 계산한다
	AdjustWindowRect(&stWindowRect, WS_EX_TOPMOST | WS_POPUP, false);

	// 윈도우를 생성한다
	return CreateWindow(
		stWindowClass.lpszClassName,
		stWindowClass.lpszClassName,
		WS_EX_TOPMOST | WS_POPUP ,//| WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		stWindowRect.right - stWindowRect.left,
		stWindowRect.bottom - stWindowRect.top,
		GetDesktopWindow(),
		nullptr,
		m_hInstance,
		m_pHandler);
}

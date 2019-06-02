#include "CWindowApplication.h"
#include "../Manager/CWindowManager.h"

//전역 변수
static CWindowApplication *g_pInstance = nullptr;

CWindowApplication::CWindowApplication(HINSTANCE a_hInstance, const int a_nOptions, const SIZE a_stWindowSize)
:
m_nOptions(a_nOptions),
m_hInstance(a_hInstance),
m_stWindowSize(a_stWindowSize)
{
	g_pInstance = this;

	if (AllocConsole()) {
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
}

CWindowApplication::~CWindowApplication(void)
{
	FreeConsole();
}

LRESULT CWindowApplication::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	switch (a_nMessage) {
		case WM_DESTROY: {
			this->handleDestroyMessage(a_wParam, a_lParam);
			break;
		}
	}

	return DefWindowProc(a_hWindow,
		a_nMessage,
		a_wParam,
		a_lParam);
}

CWindowApplication * CWindowApplication::getInstance(void)
{
	return g_pInstance;
}

int CWindowApplication::runApplication(void)
{
	this->initApplication();

	// 윈도우를 출력한다
	ShowWindow(GET_WINDOW_HANDLE(),
		m_nOptions);

	UpdateWindow(GET_WINDOW_HANDLE());
	return this->runMessageLoop();
}

void CWindowApplication::initApplication(void)
{
	// 윈도우 관리자를 초기화한다
	GET_WINDOW_MANAGER()->init(m_hInstance,
		m_nOptions,
		m_stWindowSize,
		this);
}

int CWindowApplication::runMessageLoop(void)
{
	MSG stMessage = { 0 };

	while (GetMessage(&stMessage, nullptr, 0, 0)) {
		TranslateMessage(&stMessage);
		DispatchMessage(&stMessage);
	}

	return (int)stMessage.wParam;
}

void CWindowApplication::handleDestroyMessage(WPARAM a_wParam, LPARAM a_lParam)
{
	PostQuitMessage(0);
}

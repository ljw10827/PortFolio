#pragma once

#include "../../Define/KGlobalDefine.h"

class IWindowMessageHandler;

//! 윈도우 관리자
class CWindowManager
{
public:			// getter

	//! 윈도우 크기를 반환한다
	SIZE getWindowSize(void);

	//! 윈도우 핸들을 반환한다
	HWND getWindowHandle(void);

	//! 인스턴스 핸들을 반환한다
	HINSTANCE getInstanceHandle(void);

public:			// public 함수

	//! 싱글턴
	DECLARE_SINGLETON(CWindowManager);

	//! 초기화
	virtual void init(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize,
		IWindowMessageHandler *a_pHandler);

private:			// private 함수

	//! 윈도우를 생성한다
	HWND createWindow(void);

private:			// private 변수

	int m_nOptions = 0;
	SIZE m_stWindowSize;
	
	HWND m_hWindow = nullptr;
	HINSTANCE m_hInstance = nullptr;
	IWindowMessageHandler * m_pHandler = nullptr;
};

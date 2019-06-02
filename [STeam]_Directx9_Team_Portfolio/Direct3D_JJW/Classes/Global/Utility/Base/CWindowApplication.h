#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IWindowMessageHandler.h"

//! 윈도우 어플리케이션
class CWindowApplication : public IWindowMessageHandler
{
public:			// 인터페이스 구현

	//! 윈도우 메세지를 처리한다
	virtual LRESULT handleWindowMessage(HWND a_hWindow,
		UINT a_nMessage,
		WPARAM a_wParam,
		LPARAM a_lParam) override;

public:			// getter

	//! 인스턴스를 반환한다
	static CWindowApplication * getInstance(void);

public:			// public 함수

	//! 어플리케이션을 실행한다
	virtual int runApplication(void);

public:			// 생성자

	//! 생성자
	explicit CWindowApplication(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize);

	//! 소멸자
	virtual ~CWindowApplication(void);

protected:			// protected 함수

	//! 어플리케이션을 초기화한다
	virtual void initApplication(void);

	//! 메세지 루프를 실행한다
	virtual int runMessageLoop(void);

	//! 윈도우 파괴 메세지를 처리한다
	virtual void handleDestroyMessage(WPARAM a_wParam, LPARAM a_lParam);

protected:			// private 변수

	int m_nOptions = 0;
	SIZE m_stWindowSize;
	HINSTANCE m_hInstance = nullptr;
};

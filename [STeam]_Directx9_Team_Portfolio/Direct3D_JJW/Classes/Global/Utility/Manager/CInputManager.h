#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! 시간 관리자
class CInputManager : public IUpdateable
{
public:			// 인터페이스 구현

				//! 상태를 갱신한다
	virtual void update(void) override;

public:			// getter

	//! 마우스 휠을 반환한다
	int getMouseWheel(void);

	//! 마우스 위치를 반환한다
	POINT getMousePosition(void);

	POINT getNowMousePosition(void) {
		return NowMousePosition;
	}
	void setNowMousePosition(POINT _MousePosition) {
		NowMousePosition = _MousePosition;
	}
	POINT getPrevMousePosition(void) {
		return prevMousePosition;
	}
	void setPrevMousePosition(POINT _prevMousePosition) {
		prevMousePosition = _prevMousePosition;
	}


public:			// public 함수

				//! 싱글턴
	DECLARE_SINGLETON(CInputManager);

	//! 초기화
	void init(void);

	//! 키보드 눌림 여부를 검사
	bool isKeyDown(const int a_nKeyCode);

	//! 키보드를 눌렀을 겨우
	bool isKeyPressed(const int a_nKeyCode);

	//! 키보드를 땠을 경우
	bool isKeyReleased(const int a_nKeyCode);

	//! 마우스 눌림 여부를 검사
	bool isMouseDown(const int a_nButtonIndex);

	//! 마우스를 눌렀을 경우
	bool isMousePressed(const int a_nButtonIndex);

	//! 마우스를 땠을 경우
	bool isMouseRelease(const int a_nButtonIndex);


private:		// private 함수

	//! 다이렉트 인풋을 생성
	LPDIRECTINPUT8 createDirectInput(void);

	//! 키보드 디바이스를 생성
	LPDIRECTINPUTDEVICE8 createKeyboardDevice(void);
	
	//! 마우스 디바이스를 생성
	LPDIRECTINPUTDEVICE8 createMouseDevice(void);

private:			// 소멸자

	//! 소멸자
	virtual ~CInputManager(void);

private:		// private 변수

	BYTE m_anKeyboardState[UCHAR_MAX + 1];
	BYTE m_anPrevKeyboardState[UCHAR_MAX + 1];

	DIMOUSESTATE m_stMouseState;
	DIMOUSESTATE m_stPrevMouseState;

	
	LPDIRECTINPUT8 m_pDirectInput = nullptr;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice = nullptr;
	LPDIRECTINPUTDEVICE8 m_pMouseDevcie = nullptr;

	// 이전 마우스 좌표 저장
	POINT prevMousePosition;

	// 현재 마우스 좌표 저장
	POINT NowMousePosition;

};
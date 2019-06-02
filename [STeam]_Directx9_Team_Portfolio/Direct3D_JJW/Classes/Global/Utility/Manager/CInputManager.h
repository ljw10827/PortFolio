#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! �ð� ������
class CInputManager : public IUpdateable
{
public:			// �������̽� ����

				//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter

	//! ���콺 ���� ��ȯ�Ѵ�
	int getMouseWheel(void);

	//! ���콺 ��ġ�� ��ȯ�Ѵ�
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


public:			// public �Լ�

				//! �̱���
	DECLARE_SINGLETON(CInputManager);

	//! �ʱ�ȭ
	void init(void);

	//! Ű���� ���� ���θ� �˻�
	bool isKeyDown(const int a_nKeyCode);

	//! Ű���带 ������ �ܿ�
	bool isKeyPressed(const int a_nKeyCode);

	//! Ű���带 ���� ���
	bool isKeyReleased(const int a_nKeyCode);

	//! ���콺 ���� ���θ� �˻�
	bool isMouseDown(const int a_nButtonIndex);

	//! ���콺�� ������ ���
	bool isMousePressed(const int a_nButtonIndex);

	//! ���콺�� ���� ���
	bool isMouseRelease(const int a_nButtonIndex);


private:		// private �Լ�

	//! ���̷�Ʈ ��ǲ�� ����
	LPDIRECTINPUT8 createDirectInput(void);

	//! Ű���� ����̽��� ����
	LPDIRECTINPUTDEVICE8 createKeyboardDevice(void);
	
	//! ���콺 ����̽��� ����
	LPDIRECTINPUTDEVICE8 createMouseDevice(void);

private:			// �Ҹ���

	//! �Ҹ���
	virtual ~CInputManager(void);

private:		// private ����

	BYTE m_anKeyboardState[UCHAR_MAX + 1];
	BYTE m_anPrevKeyboardState[UCHAR_MAX + 1];

	DIMOUSESTATE m_stMouseState;
	DIMOUSESTATE m_stPrevMouseState;

	
	LPDIRECTINPUT8 m_pDirectInput = nullptr;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice = nullptr;
	LPDIRECTINPUTDEVICE8 m_pMouseDevcie = nullptr;

	// ���� ���콺 ��ǥ ����
	POINT prevMousePosition;

	// ���� ���콺 ��ǥ ����
	POINT NowMousePosition;

};
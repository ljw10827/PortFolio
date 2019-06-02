#pragma once

#include "../../Define/KGlobalDefine.h"

class IWindowMessageHandler;

//! ������ ������
class CWindowManager
{
public:			// getter

	//! ������ ũ�⸦ ��ȯ�Ѵ�
	SIZE getWindowSize(void);

	//! ������ �ڵ��� ��ȯ�Ѵ�
	HWND getWindowHandle(void);

	//! �ν��Ͻ� �ڵ��� ��ȯ�Ѵ�
	HINSTANCE getInstanceHandle(void);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CWindowManager);

	//! �ʱ�ȭ
	virtual void init(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize,
		IWindowMessageHandler *a_pHandler);

private:			// private �Լ�

	//! �����츦 �����Ѵ�
	HWND createWindow(void);

private:			// private ����

	int m_nOptions = 0;
	SIZE m_stWindowSize;
	
	HWND m_hWindow = nullptr;
	HINSTANCE m_hInstance = nullptr;
	IWindowMessageHandler * m_pHandler = nullptr;
};

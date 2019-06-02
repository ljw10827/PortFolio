#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IWindowMessageHandler.h"

//! ������ ���ø����̼�
class CWindowApplication : public IWindowMessageHandler
{
public:			// �������̽� ����

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow,
		UINT a_nMessage,
		WPARAM a_wParam,
		LPARAM a_lParam) override;

public:			// getter

	//! �ν��Ͻ��� ��ȯ�Ѵ�
	static CWindowApplication * getInstance(void);

public:			// public �Լ�

	//! ���ø����̼��� �����Ѵ�
	virtual int runApplication(void);

public:			// ������

	//! ������
	explicit CWindowApplication(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize);

	//! �Ҹ���
	virtual ~CWindowApplication(void);

protected:			// protected �Լ�

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void);

	//! �޼��� ������ �����Ѵ�
	virtual int runMessageLoop(void);

	//! ������ �ı� �޼����� ó���Ѵ�
	virtual void handleDestroyMessage(WPARAM a_wParam, LPARAM a_lParam);

protected:			// private ����

	int m_nOptions = 0;
	SIZE m_stWindowSize;
	HINSTANCE m_hInstance = nullptr;
};

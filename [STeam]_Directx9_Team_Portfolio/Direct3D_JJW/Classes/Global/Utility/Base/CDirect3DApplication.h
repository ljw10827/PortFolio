#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CWindowApplication.h"
#include "../Interface/IUpdateable.h"
#include "../Interface/IRenderable.h"


class CCamera;
class CGrid;
class CLight;
class CGizmo;
class CLabel;
class CSkybox;
class CSceneObject;

//! ���̷�Ʈ 3D ���ø����̼�
class CDirect3DApplication : public CWindowApplication,
							 public IUpdateable,
							 public IRenderable
{
public:		

	//! Ÿ�� ������
	typedef std::function<void(void)> TCallback;

public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ȭ���� �׸���
	virtual void draw(void) override;

	//! UI�� �׸���
	virtual void drawUI(void) override;
	
public:			// getter

	//! ������ ��ȯ�Ѵ�
	CLight * getLight(void);

	//! ī�޶� ��ȯ�Ѵ�
	CCamera * getCamera(void);

	//! ��������Ʈ�� ��ȯ�Ѵ�
	LPD3DXSPRITE getSprite(void);

	bool getPressedLCtrl(void) { return _pressedLCtr; }


	void setPressedLCtrl(bool isPressed) { _pressedLCtr = isPressed; }

public:			// public �Լ�

	// �ݹ��� �߰��Ѵ�
	void AddCallback(const TCallback &callback);
	
				//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

	//! �޼��� ������ �����Ѵ�
	virtual int runMessageLoop(void) final override;


	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow,
		UINT a_nMessage,
		WPARAM a_wParam,
		LPARAM a_lParam) override;


public:			// ������

	//! ������
	explicit CDirect3DApplication(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize);

	//! �Ҹ���
	virtual ~CDirect3DApplication(void);

protected:			// protected �Լ�

	//! ��ī�� �ڽ��� �����Ѵ�
	virtual CSkybox * CreateSkybox(void);

	//! ��������Ʈ�� �����Ѵ�
	virtual LPD3DXSPRITE CreateSprite(void);

protected:			// protected ����

	int _FPS = 0;
	int _drawCount = 0;
	float _skipTime = 0.0f;

	bool _pressedLCtr = false;

	POINT m_stPrevMousePosition;

	CCamera * m_pCamera = nullptr;
	CGrid * m_pGrid = nullptr;
	CLight * m_pLight = nullptr;
	CGizmo * m_pGizmo = nullptr;
	CLabel * _timeLabel = nullptr;
	CSkybox * _skybox = nullptr;

	LPD3DXSPRITE _sprite = nullptr;

	CSceneObject * _scene = nullptr;

	std::vector< TCallback> _rateCallbackList;

	
};
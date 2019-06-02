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

//! 다이렉트 3D 어플리케이션
class CDirect3DApplication : public CWindowApplication,
							 public IUpdateable,
							 public IRenderable
{
public:		

	//! 타입 재정의
	typedef std::function<void(void)> TCallback;

public:			// 인터페이스 구현

	//! 상태를 갱신한다
	virtual void update(void) override;

	//! 화면을 그린다
	virtual void draw(void) override;

	//! UI를 그린다
	virtual void drawUI(void) override;
	
public:			// getter

	//! 광원을 반환한다
	CLight * getLight(void);

	//! 카메라를 반환한다
	CCamera * getCamera(void);

	//! 스프라이트를 반환한다
	LPD3DXSPRITE getSprite(void);

	bool getPressedLCtrl(void) { return _pressedLCtr; }


	void setPressedLCtrl(bool isPressed) { _pressedLCtr = isPressed; }

public:			// public 함수

	// 콜백을 추가한다
	void AddCallback(const TCallback &callback);
	
				//! 어플리케이션을 초기화한다
	virtual void initApplication(void) override;

	//! 메세지 루프를 실행한다
	virtual int runMessageLoop(void) final override;


	//! 윈도우 메세지를 처리한다
	virtual LRESULT handleWindowMessage(HWND a_hWindow,
		UINT a_nMessage,
		WPARAM a_wParam,
		LPARAM a_lParam) override;


public:			// 생성자

	//! 생성자
	explicit CDirect3DApplication(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize);

	//! 소멸자
	virtual ~CDirect3DApplication(void);

protected:			// protected 함수

	//! 스카이 박스를 생성한다
	virtual CSkybox * CreateSkybox(void);

	//! 스프라이트를 생성한다
	virtual LPD3DXSPRITE CreateSprite(void);

protected:			// protected 변수

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
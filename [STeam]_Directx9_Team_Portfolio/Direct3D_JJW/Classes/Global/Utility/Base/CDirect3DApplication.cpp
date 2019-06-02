#include "CDirect3DApplication.h"
#include "../Manager/CWindowManager.h"
#include "../Manager/CInputManager.h"
#include "../Manager/CTimeManager.h"
#include "../Manager/CSchedulerManager.h"
#include "../../../Tera/Monster/CMonsterFactory.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CSoundManager.h"
#include "../Manager/CSceneManager.h"
#include "../Base/CSceneObject.h"
#include "../Object/CCamera.h"
#include "../Object/CLight.h"
#include "../Object/CSkybox.h"
#include "../Debug/CGrid.h"
#include "../Debug/CGizmo.h"
#include "../UI/CLabel.h"


CDirect3DApplication::CDirect3DApplication(HINSTANCE a_hInstance, const int a_nOptions, const SIZE a_stWindowSize)
	:
	CWindowApplication(a_hInstance, a_nOptions, a_stWindowSize)
{
}

CDirect3DApplication::~CDirect3DApplication(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pLight);
	SAFE_DELETE(m_pGizmo);
	SAFE_RELEASE(_sprite);
	SAFE_DELETE(_timeLabel);
	SAFE_DELETE(_skybox);
}

CSkybox * CDirect3DApplication::CreateSkybox(void)
{
	return nullptr;
}

LPD3DXSPRITE CDirect3DApplication::CreateSprite(void)
{
	LPD3DXSPRITE sprite = nullptr;
	D3DXCreateSprite(GET_DEVICE(), &sprite);

	return sprite;

}

void CDirect3DApplication::AddCallback(const TCallback & callback)
{
	_rateCallbackList.push_back(callback);
}

void CDirect3DApplication::initApplication(void)
{
	CWindowApplication::initApplication();

	GET_DEVICE_MANAGER()->init(GET_WINDOW_HANDLE(), m_stWindowSize);

	_skybox = this->CreateSkybox();
	_sprite = this->CreateSprite();

	m_pGrid = new CGrid(50);
	m_pGrid->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pGizmo = new CGizmo(25);
	m_pGizmo->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pCamera = new CCamera(m_stWindowSize.cx / (float)m_stWindowSize.cy, 50.0f);
	m_pCamera->setPosition(D3DXVECTOR3(0.0f, 2.0f, -10.0f));

	m_pLight = new CLight(0);
	m_pLight->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pLight->setRotation(D3DXVECTOR3(45.0f, 0.0f, 0.0f));

	_timeLabel = new CLabel("", 20);
	_timeLabel->setPosition(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	m_stPrevMousePosition = GET_MOUSE_POSITION();

	_pressedLCtr = true;

}

void CDirect3DApplication::update(void)
{
	if (_skybox != nullptr) {
		_skybox->update();
	}
	m_pGrid->update();
	m_pGizmo->update();
	m_pCamera->update();
	m_pLight->update();

	// FPS 상태를 갱신한다
	// {
	_drawCount += 1;
	
	_skipTime += GET_DELTA_TIME();
	if (_skipTime >= 1.0f) {
		_FPS = _drawCount;

		_drawCount = 0;
		_skipTime = 0.0f;
	}
	// }

	//! 씬을 업데이트한다
	if (_scene == nullptr) {
		_scene = GET_SCENE_MANAGER()->getSceneObject();
	}
	else if (_scene != nullptr) {
		GET_SCENE_MANAGER()->getSceneObject()->update();
	}

	auto stMousePosition = GET_MOUSE_POSITION();
	
	// 왼쪽 컨트롤 누르면 마우스 보인다.
	if (IS_KEY_PRESSED(DIK_LCONTROL)) {
		if (!_pressedLCtr) {
			_pressedLCtr = true;
			stMousePosition.x = 0;
			stMousePosition.y = 0;
			m_stPrevMousePosition.x = 0;
			m_stPrevMousePosition.y = 0;

			GET_INPUT_MANAGER()->setPrevMousePosition(m_stPrevMousePosition);
			GET_INPUT_MANAGER()->setNowMousePosition(stMousePosition);

			GET_CAMERA()->setFollowObjectEnable(false);
			SetCursor(LoadCursorFromFileA("Resources/Cursor/Arrow.cur"));
		}
		else {
			_pressedLCtr = false;
			m_stPrevMousePosition = stMousePosition;
			GET_CAMERA()->setFollowObjectEnable(true);
			SetCursor(LoadCursorFromFileA("Resources/Cursor/Empty.cur"));
		}
	}

	if (!_pressedLCtr) {

		// 마우스 휠 조정
		int nMouseWheel = GET_MOUSE_WHEEL();
		m_pCamera->moveByZAxis(nMouseWheel / 30.f);

		// 마우스 범위 벗어 났을 경우

		POINT stMoustPosition;
		GetCursorPos(&stMoustPosition);

		if (100.0f >= stMousePosition.x)
		{
			m_stPrevMousePosition.x = GET_WINDOW_SIZE().cx / 2;
			SetCursorPos(stMoustPosition.x + GET_WINDOW_SIZE().cx / 2 - 100, stMoustPosition.y);
			stMousePosition.x = GET_WINDOW_SIZE().cx / 2;
		};
		if (GET_WINDOW_SIZE().cx - 100.0f <= stMousePosition.x)
		{
			m_stPrevMousePosition.x = GET_WINDOW_SIZE().cx / 2;
			SetCursorPos(stMoustPosition.x - GET_WINDOW_SIZE().cx / 2 + 100, stMoustPosition.y);
			stMousePosition.x = GET_WINDOW_SIZE().cx / 2;
		}

		GET_INPUT_MANAGER()->setPrevMousePosition(m_stPrevMousePosition);
		GET_INPUT_MANAGER()->setNowMousePosition(stMousePosition);

		m_pCamera->rotateByXAxis((stMousePosition.y - m_stPrevMousePosition.y) * 0.1f);
		m_pCamera->rotateByYAxis((stMousePosition.x - m_stPrevMousePosition.x) * 0.1f, false);

		m_stPrevMousePosition = stMousePosition;
	}

	if (IS_MOUSE_DOWN((int)EMouseInput::RIGHT_BUTTON)) {
		if (IS_KEY_DOWN(DIK_W)) {
			m_pCamera->moveByZAxis(30.0f * GET_DELTA_TIME());
		}
		else if (IS_KEY_DOWN(DIK_S)) {
			m_pCamera->moveByZAxis(-30.0f * GET_DELTA_TIME());
		}

		if (IS_KEY_DOWN(DIK_A)) {
			m_pCamera->moveByXAxis(-30.0f * GET_DELTA_TIME());
		}
		else if (IS_KEY_DOWN(DIK_D)) {
			m_pCamera->moveByXAxis(30.0f * GET_DELTA_TIME());
		}

		if (IS_KEY_DOWN(DIK_Q)) {
			m_pCamera->rotateByYAxis(-90.0f * GET_DELTA_TIME(), false);
		}
		else if (IS_KEY_DOWN(DIK_E)) {
			m_pCamera->rotateByYAxis(90.0f * GET_DELTA_TIME(), false);
		}
	}
}

void CDirect3DApplication::draw(void)
{
	if (_skybox != nullptr) {
		_skybox->draw();
	}
	//m_pGrid->draw();
	//m_pGizmo->draw();
	
	//! 씬을 그린다
	if (_scene != nullptr) {
		GET_SCENE_MANAGER()->getSceneObject()->draw();
	}
}

void CDirect3DApplication::drawUI(void)
{
	////! 타임 갱신
	//char string[MAX_PATH] = "";
	//sprintf(string, "FSP : %d\nRunningTime : %0.2f sec\nDelta_Time : %0.5f sec", _FPS, GET_RUNNING_TIME(), GET_DELTA_TIME());
	//_timeLabel->setString(string);
	//_timeLabel->drawUI();

	//! 씬을 그린다
	if (_scene != nullptr) {
		GET_SCENE_MANAGER()->getSceneObject()->drawUI();
	}
}


CLight * CDirect3DApplication::getLight(void)
{
	return m_pLight;
}

CCamera * CDirect3DApplication::getCamera(void)
{
	return m_pCamera;
}

LPD3DXSPRITE CDirect3DApplication::getSprite(void)
{
	return _sprite;
}

int CDirect3DApplication::runMessageLoop(void)
{
	// 관리자 초기화한다
	GET_TIME_MANAGER()->init();
	GET_INPUT_MANAGER()->init();
	GET_SOUND_MANAGER()->init();
	GET_SCHEDULER_MANAGER()->init();
	GET_MONSTER()->init();

	MSG stMessage = { 0 };

	while (stMessage.message != WM_QUIT) {
		if (PeekMessage(&stMessage, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&stMessage);
			DispatchMessage(&stMessage);
		}

		// 관리자를 갱신한다
		GET_TIME_MANAGER()->update();
		GET_SCHEDULER_MANAGER()->update();
		GET_INPUT_MANAGER()->update();
		GET_MONSTER()->update();
		/*
		Clear 함수는 버퍼를 지우는 영할을 한다.
		이때 지우는 버퍼를 명시하는 것이 가능하다.
		D3DCLEAR_TARGET : 렌더링의 타겟 버퍼
		D3DCLEAR_ZBUFFER : 깊이버퍼
		D3DCLEAR_STENCIL : 스텐실 버퍼

		깊이 버퍼는 보통 1.0f로 초기화 한다.
		(즉, 투영을 거치고 나면 Z의 값은 0~1의 범위로 변경되는데
		이 값의 최대값을 입력하겠다는 의미)

		스텐실버퍼는 0으로 초기화하는 것이 일반적이다.
		*/
		// 1. 버퍼를 지운다.
		GET_DEVICE()->Clear(0,
			nullptr,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			D3DCOLOR_XRGB(0,0,0),
			1.0f,
			0);

		if (SUCCEEDED(GET_DEVICE()->BeginScene())) {
			this->update();
			this->draw();
			
			this->drawUI();
			// 콜백을 호출한다
			// {
			for (int i = 0; i < _rateCallbackList.size(); ++i) {
				if (_rateCallbackList[i] != nullptr) {
					_rateCallbackList[i]();
				}
			}

			_rateCallbackList.clear();
			// }
			
			/*_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
			{
			
			}
			_sprite->End();*/

			GET_DEVICE()->EndScene();
		}
		
		

		/*
		백 버퍼의 장면을 프레임 버퍼로 이동한다.
		(즉, 해당 함수가 완료되고 나면 화면 상에 장면이 그려진다.)
		*/
		GET_DEVICE()->Present(nullptr, nullptr, nullptr, nullptr);
		
	}

	return (int)stMessage.wParam;
}

LRESULT CDirect3DApplication::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{

	return CWindowApplication::handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
}

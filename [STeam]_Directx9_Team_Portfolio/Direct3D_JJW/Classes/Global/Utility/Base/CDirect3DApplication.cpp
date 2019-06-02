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

	// FPS ���¸� �����Ѵ�
	// {
	_drawCount += 1;
	
	_skipTime += GET_DELTA_TIME();
	if (_skipTime >= 1.0f) {
		_FPS = _drawCount;

		_drawCount = 0;
		_skipTime = 0.0f;
	}
	// }

	//! ���� ������Ʈ�Ѵ�
	if (_scene == nullptr) {
		_scene = GET_SCENE_MANAGER()->getSceneObject();
	}
	else if (_scene != nullptr) {
		GET_SCENE_MANAGER()->getSceneObject()->update();
	}

	auto stMousePosition = GET_MOUSE_POSITION();
	
	// ���� ��Ʈ�� ������ ���콺 ���δ�.
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

		// ���콺 �� ����
		int nMouseWheel = GET_MOUSE_WHEEL();
		m_pCamera->moveByZAxis(nMouseWheel / 30.f);

		// ���콺 ���� ���� ���� ���

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
	
	//! ���� �׸���
	if (_scene != nullptr) {
		GET_SCENE_MANAGER()->getSceneObject()->draw();
	}
}

void CDirect3DApplication::drawUI(void)
{
	////! Ÿ�� ����
	//char string[MAX_PATH] = "";
	//sprintf(string, "FSP : %d\nRunningTime : %0.2f sec\nDelta_Time : %0.5f sec", _FPS, GET_RUNNING_TIME(), GET_DELTA_TIME());
	//_timeLabel->setString(string);
	//_timeLabel->drawUI();

	//! ���� �׸���
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
	// ������ �ʱ�ȭ�Ѵ�
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

		// �����ڸ� �����Ѵ�
		GET_TIME_MANAGER()->update();
		GET_SCHEDULER_MANAGER()->update();
		GET_INPUT_MANAGER()->update();
		GET_MONSTER()->update();
		/*
		Clear �Լ��� ���۸� ����� ������ �Ѵ�.
		�̶� ����� ���۸� ����ϴ� ���� �����ϴ�.
		D3DCLEAR_TARGET : �������� Ÿ�� ����
		D3DCLEAR_ZBUFFER : ���̹���
		D3DCLEAR_STENCIL : ���ٽ� ����

		���� ���۴� ���� 1.0f�� �ʱ�ȭ �Ѵ�.
		(��, ������ ��ġ�� ���� Z�� ���� 0~1�� ������ ����Ǵµ�
		�� ���� �ִ밪�� �Է��ϰڴٴ� �ǹ�)

		���ٽǹ��۴� 0���� �ʱ�ȭ�ϴ� ���� �Ϲ����̴�.
		*/
		// 1. ���۸� �����.
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
			// �ݹ��� ȣ���Ѵ�
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
		�� ������ ����� ������ ���۷� �̵��Ѵ�.
		(��, �ش� �Լ��� �Ϸ�ǰ� ���� ȭ�� �� ����� �׷�����.)
		*/
		GET_DEVICE()->Present(nullptr, nullptr, nullptr, nullptr);
		
	}

	return (int)stMessage.wParam;
}

LRESULT CDirect3DApplication::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{

	return CWindowApplication::handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
}

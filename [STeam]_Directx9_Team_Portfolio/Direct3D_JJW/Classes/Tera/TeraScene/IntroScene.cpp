#include "IntroScene.h"
#include "MainScene.h"
#include "LoadingScene.h"
#include "../TeraUI/CTeraUI.h"
#include "../../Global/Utility/Manager/CResourceManager.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../../Global/Utility/Manager/CSceneManager.h"
#include "../../Global/Utility/Manager/CSchedulerManager.h"

#include "../../Global/Utility/UI/CSprite.h"

void IntroScene::init(void)
{
	CSceneObject::init();
	
	_teraUI = new CTeraUI(CTeraUI::EMapKind::none);
	_teraUI->init();

	this->addChildObject(_teraUI);

	GET_DIRECT3D_APPLICATION()->AddCallback([=](void) -> void {

		SetCursor(LoadCursorFromFileA("Resources/Cursor/Arrow.cur"));


		//////// ---------------------------  비디오재생
		HRESULT hr;
		IGraphBuilder *m_pGraph;
		IMediaControl *m_pMediaControl;
		IVideoWindow *m_pVidWin;
		IMediaEvent *m_pEvent;

		m_pGraph = NULL;
		m_pMediaControl = NULL;
		m_pVidWin = NULL;

		CoInitialize(NULL);

		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void**)&m_pGraph);
		if (FAILED(hr)) {
			std::cout << "인스턴스생성오류" << std::endl;
		}

		hr = m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);
		if (FAILED(hr)) {
			std::cout << "미디어컨트롤" << std::endl;
		}

		hr = m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&m_pVidWin);
		if (FAILED(hr)) {
			std::cout << "비디오윈도우" << std::endl;
		}

		hr = m_pGraph->QueryInterface(IID_IMediaEvent, (void **)&m_pEvent);
		if (FAILED(hr)) {
			std::cout << "미디어이벤트" << std::endl;
		}

		hr = m_pGraph->RenderFile(L"D:\\IntroVideo.avi", NULL);
		if (FAILED(hr)) {
			std::cout << "로드 오류" << std::endl;
		}

		m_pVidWin->put_Owner((OAHWND)GET_WINDOW_HANDLE());
		m_pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);

		RECT grc;
		GetClientRect(GET_WINDOW_HANDLE(), &grc);

		m_pVidWin->SetWindowPosition(0, 0, grc.right, grc.bottom);

		if (SUCCEEDED(m_pMediaControl->Run())) {
			long ev;
			m_pEvent->WaitForCompletion(INFINITE, &ev);
		}

		m_pVidWin->put_Visible(OAFALSE);
		m_pVidWin->put_Owner(NULL);

		m_pEvent->Release();
		m_pMediaControl->Release();
		m_pVidWin->Release();
		m_pGraph->Release();

		CoUninitialize();

		////// ---------------------------  비디오재생

		// 인트로 음악재생
		SET_SCHEDULE(32.1f, [=](void) ->void {
			_teraUI->loadingScreenStart(true);

			SET_SCHEDULE(1.0f, [=](void) ->void {
				PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Intro/IntroThema.wav");
				GET_DIRECT3D_APPLICATION()->setPressedLCtrl(true);
			});
		});
	});
}

void IntroScene::update(void)
{
	CSceneObject::update();

	_isUpdateEnd = false;

	if (_teraUI->getStartButtonOver()) {

		if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON)) {
			GET_SOUND_MANAGER()->setEffectsVolume(0.5f);
			PLAY_EFFECT_SOUND("Resources/Sounds/ETC/IntroMenuClick.wav");
			_isChangeScene = true;
			auto sprite = _teraUI->getLoadingBackGround();
			sprite->setTexture("Resources/Textures/TeraUI/newLoading2.tga");
		}
	}

	if (_isChangeScene) {
		GET_SOUND_MANAGER()->setEffectsVolume(1.0f);

		_isChangeScene = false;
		LoadingScene * loadingScene = new LoadingScene("Main");
		loadingScene->init();
		GET_SCENE_MANAGER()->replaceSceneObject(loadingScene);
	}

	_isUpdateEnd = true;

}

#include "LoadingScene.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../../Global/Utility/Manager/CSceneManager.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/Manager/CSchedulerManager.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../../Global/Utility/UI/CSprite.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "MainScene.h"
#include "BossScene.h"

LoadingScene::LoadingScene(const std::string & nextSceneName)
	:
	_nextSceneName(nextSceneName)
{
	// Do Nothing
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::init(void)
{
	CSceneObject::init();

	_teraUI = new CTeraUI(CTeraUI::EMapKind::loading);
	_teraUI->init();
	this->addChildObject(_teraUI);

	// 쓰레드를 통해 다음씬의 초기화를 비동기식으로 진행한다.
	_loadingCompletePercent = 0.0f;

	// 커서변경
	SetCursor(LoadCursorFromFileA("Resources/Cursor/Loading.ani"));

	char spriteName[256] = "";
	sprintf(spriteName, "LoadingBackGround_%02d.tga", CreateIntRandomValue(1, 3));

	std::string backSpritePath = "Resources/Textures/TeraUI/" + (std::string)spriteName;

	auto backGround = new CSprite(backSpritePath);
	backGround->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	backGround->setSpriteScaleTemp(
		1.0f/2048.0f * GET_WINDOW_SIZE().cx,
		1.0f/1024.0f * GET_WINDOW_SIZE().cy);

	this->addChildObject(backGround);

	_loadingProgressBarBack = new CSprite("Resources/Textures/TeraUI/LoadingProgressBack.tga");
	auto backTextureSize = _loadingProgressBarBack->getTextureSize();
	_loadingProgressBarBack->setPosition(
		D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f - backTextureSize.cx / 2.0f,
			GET_WINDOW_SIZE().cy / 10.0f * 8.0f,
			0.0f));
	this->addChildObject(_loadingProgressBarBack);

	_loadingProgressBar = new CSprite("Resources/Textures/TeraUI/LoadingProgress.tga");
	auto barTextureSize = _loadingProgressBar->getTextureSize();
	_loadingProgressBar->setPosition(
		D3DXVECTOR3(((GET_WINDOW_SIZE().cx / 2.0f) - (barTextureSize.cx / 2.0f) + 8.0f),
			GET_WINDOW_SIZE().cy / 10.0f * 8.0f + 15.5f,
			0.0f));
	_loadingProgressBar->setTextureSize(0, 0);
	_loadingProgressBarBack->addChildObject(_loadingProgressBar);

	_perLoadingLabel = new CLabel(_text, 14);
	_perLoadingLabel->setColor(D3DXCOLOR(1.f, 1.0f, 1.0f, 0.8f));
	_perLoadingLabel->setPosition(
		D3DXVECTOR3(GET_WINDOW_SIZE().cx / 10.0f * 4.7f,
			GET_WINDOW_SIZE().cy / 10.0f * 8.0f + 20.5f,
			0.0f));

	_loadingProgressBarBack->addChildObject(_perLoadingLabel);


	if (_nextSceneName == "Main") {
		_nextScene = new MainScene();
		_nextScene->init();
	}
	else if (_nextSceneName == "Boss") {
		_nextScene = new BossScene();
		_nextScene->init();
	}

	GET_DIRECT3D_APPLICATION()->AddCallback([=](void)->void {
		_teraUI->loadingScreenStart(false);
	});
}

void LoadingScene::update(void)
{
	CSceneObject::update();
	_isUpdateEnd = false;
	
	_nextScene->update();

	if (_nextSceneName == "Main") {

		_loadingCompletePercent = MainScene::getCompleteInitCount() / 80.0f * 100.0f;

		float sizeX = _loadingCompletePercent / 100.f * _loadingProgressBar->getOriginSize().cx;
		float SizeY = _loadingProgressBar->getOriginSize().cy;
		_loadingProgressBar->setTextureSize(sizeX, SizeY);

		
	}
	else if (_nextSceneName == "Boss") {

		int a = BossScene::getCompleteInitCount();
		_loadingCompletePercent = BossScene::getCompleteInitCount() / 87.0f * 100;

		float sizeX = _loadingCompletePercent / 100.f * _loadingProgressBar->getOriginSize().cx;
		float SizeY = _loadingProgressBar->getOriginSize().cy;
		_loadingProgressBar->setTextureSize(sizeX, SizeY);
	}


	sprintf(_text, "Loading..... %0.1f%%", _loadingCompletePercent);
	_perLoadingLabel->setString(_text);

	_isUpdateEnd = true;

	if (_loadingCompletePercent >= 100.0f && _isUpdateEnd) {

		// 커서세팅
		SetCursor(LoadCursorFromFileA("Resources/Cursor/Empty.cur"));
		SetCursorPos(GET_WINDOW_SIZE().cx / 2.0f, GET_WINDOW_SIZE().cy / 2.0f);
		GET_DIRECT3D_APPLICATION()->setPressedLCtrl(false);
		GET_CAMERA()->setFollowObjectEnable(true);

		// 배경음  변경
		PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Main/Beginner_Village.wav");
		GET_SCENE_MANAGER()->replaceSceneObject(_nextScene);

	}

	////테스트
	//
	//if (_loadingCompletePercent >= 99.f) {
	//	babo = true;
	//}

	//if (babo) {
	//	_loadingCompletePercent = 0.0f;
	//	babo = false;
	//	MainScene * mainScene = new MainScene();
	//	mainScene->init();
	//	SetCursor(LoadCursorFromFileA("Resources/Cursor/Arrow.cur"));
	//	GET_SCENE_MANAGER()->replaceSceneObject(mainScene);
	//}
}

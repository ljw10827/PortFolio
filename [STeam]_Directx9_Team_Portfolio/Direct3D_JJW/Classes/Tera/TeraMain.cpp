#include "TeraMain.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Base/CObject.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Base/CSceneObject.h"
#include "../Global/Utility/Manager/CSceneManager.h"
#include "TeraScene/IntroScene.h"
#include "TeraScene/MainScene.h"
#include "TeraScene/BossScene.h"
#include "TeraScene/LoadingScene.h"

#pragma comment(lib, "strmiids")

TeraMain::TeraMain(HINSTANCE a_hInstance, const int a_nOptions, const SIZE a_stWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_stWindowSize)
{
	// Do Nothing
}

TeraMain::~TeraMain(void)
{
}

void TeraMain::initApplication(void)
{
	CDirect3DApplication::initApplication();
	
	IntroScene * introScene = new IntroScene();
	introScene->init();

	GET_SCENE_MANAGER()->replaceSceneObject(introScene);
}

void TeraMain::update(void)
{
	CDirect3DApplication::update();

}

void TeraMain::draw(void)
{
	CDirect3DApplication::draw();

}

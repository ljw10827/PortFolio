#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CSceneObject.h"

class CSprite;
class CLabel;
class CSceneObject;

//class LoadingScene
//{
//	std::thread thread1()
//};

class LoadingScene : public CSceneObject
{
public:				// public ÇÔ¼ö

	explicit LoadingScene(const std::string & nextSceneName);

	virtual ~LoadingScene();

	virtual void init(void) override;
	virtual void update(void) override;

private:

	float _loadingCompletePercent = 0.0f;

	char _text[256] = "";
	std::string _nextSceneName = "";

	CLabel * _perLoadingLabel = nullptr;
	CSprite *  _loadingProgressBar = nullptr;
	CSprite *  _loadingProgressBarBack = nullptr;

	CSceneObject * _nextScene = nullptr;
};
#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CSceneObject.h"

class CLabel;
class CSprite;

class IntroScene : public CSceneObject
{
public:		// 인터페이스 구현

	virtual void init(void) override;

	//virtual void draw(void) override;

	virtual void update(void) override;

private: // private 변수


	CTeraUI * _teraUI = nullptr;

	float _sceneChangeTime = 0.0f;
	bool _isChangeScene = false;

	bool _isSceneStart = false;
};
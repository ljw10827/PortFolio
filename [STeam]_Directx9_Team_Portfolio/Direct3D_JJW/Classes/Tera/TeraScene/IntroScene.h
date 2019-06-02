#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CSceneObject.h"

class CLabel;
class CSprite;

class IntroScene : public CSceneObject
{
public:		// �������̽� ����

	virtual void init(void) override;

	//virtual void draw(void) override;

	virtual void update(void) override;

private: // private ����


	CTeraUI * _teraUI = nullptr;

	float _sceneChangeTime = 0.0f;
	bool _isChangeScene = false;

	bool _isSceneStart = false;
};
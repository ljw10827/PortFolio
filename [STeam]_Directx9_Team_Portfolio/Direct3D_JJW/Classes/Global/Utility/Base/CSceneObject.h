#pragma once

#include "CObject.h"
#include "../Interface/IRenderable.h"
#include "../../../Tera/Etc/CTeraGlobalHeader.h"


//! 씬 객체
class CSceneObject : public CObject,
					public IRenderable
{
public:

	virtual ~CSceneObject(void);
public:

	enum class EInitStep
	{
		STEP01 = 1, STEP02, STEP03, STEP04, STEP05, STEP06, STEP07, STEP08, STEP09, STEP10,
		STEP11, STEP12, STEP13, STEP14, STEP15, STEP16, STEP17, STEP18, STEP19, STEP20, STEP21,
		STEP22, STEP23, STEP24, STEP25, STEP26, STEP27, STEP28, STEP29, STEP30
	};

public:		// 인터페이스 구현

	virtual void init(void);

	virtual void update(void) override;

	virtual void draw(void)  override;
	virtual void drawUI(void) final override;

	static float getCompleteInitCount(void) { return _completeInitCount; }

	static void setCompleteInitCount(float count) { _completeInitCount += count; }

	std::string getSceneName(void) { return _sceneName; }

	CTeraUI* getTeraUI(void) { return _teraUI; }

protected:		// protected변수

	float _cameraFar = -70.0f;

	bool _isSceneChange = false;
	bool _isDrawEnd = false;
	bool _isDrawUIEnd = false;
	bool _isUpdateEnd = false;

	CPlayer * _player = nullptr;
	CTeraUI * _teraUI = nullptr;

	CTeraMap * _map = nullptr;

	bool _isSceneStart = false;

	static float _completeInitCount;

	bool _isInitScene = false;

	EInitStep _initStep;

	std::string _sceneName = "";

};
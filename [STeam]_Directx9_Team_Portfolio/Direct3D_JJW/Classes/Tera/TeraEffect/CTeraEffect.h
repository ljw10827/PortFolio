#pragma once
#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"


class CTeraEffect : public CRenderObject
{
	
public:
	virtual void update() override;
	
	virtual void doDrawObject(void) override;

	virtual void AddLocation(const D3DXVECTOR3 &addVector);
public:

	void effeckUpdate(float deltaTime);

public:
	void setDeltaTime(float deltaTime);
public:
	void playEffeckseer(const D3DXVECTOR3 &position, const int startFrame = 0);

	void stopEffekseer();

	void setRotationEffekseer(const float angleX = 0.0f, const float angleY = 0.0f, const float angleZ = 0.0f);

	void setScaleEffekseer(const float scaleX = 1.0f, const float scaleY = 1.0f, const float scaleZ = 1.0f);

	bool EffekExist();

	void fireBallExplosion(const D3DXVECTOR3 &position);

	D3DXVECTOR3 getEffectPosition();

public:

	explicit CTeraEffect(const std::wstring &filepath, EffectType effectType = EffectType::NONE);

	virtual ~CTeraEffect();

private:
	STEffekseer _effekseer;
	EffectType _effectType;

	std::wstring _filepath;

	float _deltaTime = 1.0f;
	float _count = 0.0f;

	D3DXVECTOR3 _position;
};

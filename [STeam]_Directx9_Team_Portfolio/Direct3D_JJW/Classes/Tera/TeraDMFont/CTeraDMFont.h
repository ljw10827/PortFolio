#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CUIObject.h"

#define MAX_NUM_DIGIT 5

class CSprite;

class CTeraDMFont : public CUIObject
{
public:
	struct STDamageFont
	{
		CSprite *_damageSprite;
		int OriginNumber;
	};

	struct STDamageList
	{
		D3DXVECTOR3 _positionList[MAX_NUM_DIGIT];
		CSprite * _damageSpriteList[MAX_NUM_DIGIT];
		CSprite * _bloodSprite;
		D3DXVECTOR3 _bloodPosition;
		int _digit;
		float _deleteCount = 0;
	};

public:

	virtual void doDrawUI(void) override;

	virtual void update(void) override;

public:
	void drawFont(void);

public:
	explicit CTeraDMFont(void);

	virtual ~CTeraDMFont();

public:
	void damageCalculate(int damage, D3DXVECTOR3 position);

	void addDamage(int damage);

public:
	STDamageFont _damageFont[10];

	int _digit = 0;
	int _damageArray[MAX_NUM_DIGIT];

	std::vector<STDamageList> _damageList;

	float _deleteCount = 0;

};
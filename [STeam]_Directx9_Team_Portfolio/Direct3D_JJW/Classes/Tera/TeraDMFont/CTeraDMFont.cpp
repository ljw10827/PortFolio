#include "CTeraDMFont.h"
#include "../../Global/Utility/UI/CSprite.h"
#include "../../Global/Utility/Manager/CTimeManager.h"

CTeraDMFont::CTeraDMFont(void)
{
	ZeroMemory(&_damageFont, sizeof(_damageFont));
	ZeroMemory(&_damageArray, sizeof(_damageArray));

	for (int i = 0; i < 10; ++i)
	{
		_damageFont[i]._damageSprite = new CSprite("Resources/Textures/TeraUI/comboFont2.tga");
	}
	
	_damageFont[0]._damageSprite->setRectSize(234 / 2.0f, 282 / 2.0f, 0, 58 / 2.0f);
	_damageFont[0].OriginNumber = 5;

	_damageFont[1]._damageSprite->setRectSize(422 / 2.0f, 470 / 2.0f, 0, 58 / 2.0f);
	_damageFont[1].OriginNumber = 9;

	_damageFont[2]._damageSprite->setRectSize(282 / 2.0f, 328 / 2.0f, 0, 58 / 2.0f);
	_damageFont[2].OriginNumber = 6;

	_damageFont[3]._damageSprite->setRectSize(330 / 2.0f , 376 / 2.0f, 0, 58 / 2.0f);
	_damageFont[3].OriginNumber = 7;

	_damageFont[4]._damageSprite->setRectSize(376 / 2.0f, 422 / 2.0f, 0, 58 / 2.0f);
	_damageFont[4].OriginNumber = 8;

	_damageFont[5]._damageSprite->setRectSize(46 / 2.0f, 94 / 2.0f,   0, 58 / 2.0f);
	_damageFont[5].OriginNumber = 1;


	_damageFont[6]._damageSprite->setRectSize(94 / 2.0f, 140 / 2.0f, 0, 58 / 2.0f);
	_damageFont[6].OriginNumber = 2;

	_damageFont[7]._damageSprite->setRectSize(0, 46 / 2.0f,   0, 58 / 2.0f);
	_damageFont[7].OriginNumber = 0;

	_damageFont[8]._damageSprite->setRectSize(188 / 2.0f, 234 / 2.0f, 0, 58 / 2.0f);
	_damageFont[8].OriginNumber = 4;

	_damageFont[9]._damageSprite->setRectSize(140 / 2.0f , 188 / 2.0f, 0, 58 / 2.0f);
	_damageFont[9].OriginNumber = 3;

	for (int i = 0; i < 10; ++i)
	{
		_damageFont[i]._damageSprite->setPosition(D3DXVECTOR3(100 + ((46 / 2.0f) * _damageFont[i].OriginNumber) + ((46 / 2.0f) * i), 100.0f, 0.0f));
	}

	


}

CTeraDMFont::~CTeraDMFont()
{

}


void CTeraDMFont::update(void)
{
	CUIObject::update();

	if (_damageList.size() != 0)
	{
		for (int i = 0; i < _damageList.size(); ++i)
		{
			_damageList[i]._deleteCount += GET_DELTA_TIME();

			if (_damageList[i]._deleteCount >= 3)
			{
				_damageList.erase(_damageList.begin());
			}
		}
	}
}

void CTeraDMFont::drawFont(void)
{
	
	for (int i = 0; i < _damageList.size(); ++i)
	{
		for (int j = 0; j < _damageList[i]._digit; ++j)
		{
			_damageList[i]._damageSpriteList[j]->setPosition(_damageList[i]._positionList[j]);
			_damageList[i]._damageSpriteList[j]->drawUI();
		}
		_damageList[i]._bloodSprite->setPosition(_damageList[i]._bloodPosition);
		_damageList[i]._bloodSprite->drawUI();
	}

}



void CTeraDMFont::doDrawUI(void)
{
	CUIObject::doDrawUI();
	
	this->drawFont();
}


void CTeraDMFont::damageCalculate(int damage, D3DXVECTOR3 position)
{
	int OriginDamage = damage;
	int digitNumber = 1;
	int i = 0;
	
	STDamageList damageList;
	ZeroMemory(&damageList, sizeof(damageList));

	while (true)
	{
		damage = damage / 10;
		_digit++;

		if (damage == 0)
		{
			break;
		}
	}

	for(int i = 0; i < _digit - 1; ++i)
	{
		digitNumber *= 10;
	}

	while (true)
	{
		_damageArray[i] = OriginDamage / digitNumber;
		OriginDamage = OriginDamage % digitNumber;
		
		digitNumber /= 10;
		i++;
		
		if (OriginDamage == 0)
		{
			break;
		}
	}

	for (int i = 0; i < _digit; ++i)
	{
		damageList._damageSpriteList[i] = _damageFont[_damageArray[i]]._damageSprite;

		damageList._positionList[i] = D3DXVECTOR3((position.x + (47 / 2.0f) * _damageFont[_damageArray[i]].OriginNumber) +
			((47 / 2.0f) * i) - ((_digit * (47 / 2.0f)) / 2),
			position.y, position.z);
	}
	
	damageList._bloodSprite = new CSprite("Resources/Textures/TeraUI/HitEffect.tga");
	damageList._bloodPosition = D3DXVECTOR3(position.x - (damageList._bloodSprite->getOriginSize().cx / 2.0f), position.y - (damageList._bloodSprite->getOriginSize().cy / 2.0f), 0.0f);

	damageList._digit = _digit;
	damageList._deleteCount = 0;

	_damageList.push_back(damageList);

	_digit = 0;
}

void CTeraDMFont::addDamage(int damage)
{
	STDamageFont damageFont[10];
	ZeroMemory(&damageFont, sizeof(damageFont));

	
	for (int i = 0; i < _digit; ++i)
	{
		damageFont[i]._damageSprite = _damageFont[_damageArray[i]]._damageSprite;
	}

}


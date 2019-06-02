#include "MCraftySpider.h"
#include "../../Global/Function/GlobalFunction.h"
// TODO
MCraftySpider::MCraftySpider(const std::string & monsterName)
	:
	CMonster(monsterName)
{

}

MCraftySpider::~MCraftySpider(void)
{
	CMonster::~CMonster();
}

void MCraftySpider::init(void)
{
	CMonster::init();
	this->setScale(D3DXVECTOR3(0.6f, 0.6f, 0.6f));
	_moveSpeed = CreateFloatRandomValue(7.0f, 9.0f);

	_status.hp = CreateIntRandomValue(2500, 3000);
	_status.maxAtk = CreateIntRandomValue(140, 160);
	_status.minAtk = CreateIntRandomValue(120, 140);
	_status.perAtkAcc = 0;
	_status.perAtkCri = 0;
	_status.perAtkDmg = 0;
	_status.PerDef = CreateIntRandomValue(5, 12);

	// ÃÊ±âÈ­
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 30, 0.01f, 30);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMesh->setShadowMatrix(worldMatrix);

}

void MCraftySpider::update(void)
{
	CMonster::update();

	auto stPos = this->getPosition();
	if (this->getPosition().x < 254.0f)
	{
		stPos.x = 254.0f;
		this->setPosition(stPos);
	}
	if (this->getPosition().x > 450.0f)
	{
		stPos.x = 450.0f;
		this->setPosition(stPos);
	}
	if (this->getPosition().z < 277.0f)
	{
		stPos.z = 277.0f;
		this->setPosition(stPos);
	}
	if (this->getPosition().z > 442.0f)
	{
		stPos.z = 442.0f;
		this->setPosition(stPos);
	}
}

void MCraftySpider::doDrawObject(void)
{
	CMonster::doDrawObject();
}

void MCraftySpider::NormalAtk()
{
	_state = EState::ISATTACKING;
	if (CreateIntRandomValue(0, 100) > 60) {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/M_CraftySpider/Atk01.wav");
	}
	else {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/M_CraftySpider/Atk02.wav");
	}
	
	_skinnedMesh->PlayAnimation("Atk01", false, false, [=](const std::string &animName)->void {
		_state = EState::ATK;
	});
}


void MCraftySpider::BeAttacked(CPlayer * target, int damage)
{
	if (_state != EState::REMOVE && _state != EState::BEATTACKED) {
		CMonster::BeAttacked(target, damage);

		_skinnedMesh->PlayAnimation("AggroChange", false, false, [=](const std::string &animName)->void {
			_state = EState::BEATTACKED;
		});
	}
}
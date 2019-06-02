#include "MPollutedWolf.h"
#include "../../Global/Function/GlobalFunction.h"
// TODO
MPollutedWolf::MPollutedWolf(const std::string & monsterName)
	:
	CMonster(monsterName)
{

}

MPollutedWolf::~MPollutedWolf(void)
{
	CMonster::~CMonster();
}

void MPollutedWolf::init(void)
{
	CMonster::init();
	this->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	_moveSpeed = CreateFloatRandomValue(10.0f, 12.0f);

	_status.hp = CreateIntRandomValue(3500, 4000);
	_status.maxAtk = CreateIntRandomValue(220, 240);
	_status.minAtk = CreateIntRandomValue(180, 200);
	_status.perAtkAcc = 0;
	_status.perAtkCri = 0;
	_status.perAtkDmg = 0;
	_status.PerDef = CreateIntRandomValue(0, 10);

	// ÃÊ±âÈ­
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 60.f, 0.01f, 60.f);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMesh->setShadowMatrix(worldMatrix);
}

void MPollutedWolf::update(void)
{
	CMonster::update();

	auto stPos = this->getPosition();
	if (this->getPosition().x < -110)
	{
		stPos.x = -110;
		this->setPosition(stPos);
	}
	if (this->getPosition().x > 187)
	{
		stPos.x = 187;
		this->setPosition(stPos);
	}
	if (this->getPosition().z < -48)
	{
		stPos.z = -48;
		this->setPosition(stPos);
	}
	if (this->getPosition().z > 148)
	{
		stPos.z = 148;
		this->setPosition(stPos);
	}
}

void MPollutedWolf::doDrawObject(void)
{
	CMonster::doDrawObject();
}

void MPollutedWolf::NormalAtk()
{
	_state = EState::ISATTACKING;

	PLAY_EFFECT_SOUND("Resources/Sounds/Monster/M_PollutedWolf/PollutedWolf_Atk02.wav");

	_skinnedMesh->PlayAnimation("Atk02", false, false, [=](const std::string &animName)->void {
		_state = EState::ATK;
	});
}

void MPollutedWolf::BeAttacked(CPlayer * target, int damage)
{
	if (_state != EState::REMOVE && _state != EState::BEATTACKED) {
		CMonster::BeAttacked(target, damage);

		auto animList = _skinnedMesh->getAnimationNameList();
		std::string animName = "";

		for (auto iterator : animList) {
			if (iterator == "AggroChange" || iterator == "Stun") {
				animName = iterator;
			}
			else {
				animName = "none";
			}
		}

		if (animName != "none") {
			_skinnedMesh->PlayAnimation(animName, false, false, [=](const std::string &animName)->void {
				_state = EState::BEATTACKED;
			});
		}
		else {
			_state = EState::BEATTACKED;
		}
	}
}
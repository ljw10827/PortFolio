#include "MPlantMini.h"
#include "../../Global/Function/GlobalFunction.h"
#include "CMonsterFactory.h"

// TODO
MPlantMini::MPlantMini(const std::string & monsterName)
	:
	CMonster(monsterName)
{

}

MPlantMini::~MPlantMini(void)
{
	CMonster::~CMonster();
}

void MPlantMini::init(void)
{
	CMonster::init();
	this->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	_moveSpeed = CreateFloatRandomValue(7.0f, 9.0f);

	_status.hp = CreateIntRandomValue(1500, 2000);
	_status.maxAtk = CreateIntRandomValue(60, 70);
	_status.minAtk = CreateIntRandomValue(40, 50);
	_status.perAtkAcc = 0;
	_status.perAtkCri = 0;
	_status.perAtkDmg = 0;
	_status.PerDef = CreateIntRandomValue(2, 6);

	// ÃÊ±âÈ­
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 40, 0.01f, 40);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMesh->setShadowMatrix(worldMatrix);
}

void MPlantMini::update(void)
{
	CMonster::update();
	
	auto stPos = this->getPosition();
	if (this->getPosition().x > -447.0f &&this->getPosition().x < 222.0f &&
		this->getPosition().z > 337.0f && this->getPosition().z < 453.0f)
	{
		if (this->getPosition().x < -447.0f)
		{
			stPos.x = -447.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().x > 222.0f)
		{
			stPos.x = 222.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z < 337.0f)
		{
			stPos.z = 337.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z > 453.0f)
		{
			stPos.z = 453.0f;
			this->setPosition(stPos);
		}
	}

	if (this->getPosition().x > 254.0f && this->getPosition().x < 450.0f &&
		this->getPosition().z > 227.0f && this->getPosition().z < 442.0f)
	{
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
		if (this->getPosition().z < 227.0f)
		{
			stPos.z = 227.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z > 442.0f)
		{
			stPos.z = 442.0f;
			this->setPosition(stPos);
		}
	}
}

void MPlantMini::doDrawObject(void)
{
	CMonster::doDrawObject();
}

void MPlantMini::NormalAtk()
{
	_state = EState::ISATTACKING;

	
	char temp[256] = "";
	sprintf(temp, "Resources/Sounds/Monster/M_Plant_mini/Atk%02d.wav", CreateIntRandomValue(1, 5));
	PLAY_EFFECT_SOUND(temp);

	_skinnedMesh->PlayAnimation("Atk02", false, false, [=](const std::string &animName)->void {
		_state = EState::ATK;
	});
}

void MPlantMini::BeAttacked(CPlayer * target, int damage)
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
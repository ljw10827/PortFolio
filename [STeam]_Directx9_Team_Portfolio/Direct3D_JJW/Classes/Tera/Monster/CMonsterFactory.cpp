#include "CMonsterFactory.h"
#include "../TeraScene/MainScene.h"
#include "../TeraScene/BossScene.h"	

void CMonsterFactory::init(void)
{
}

CMonsterFactory::~CMonsterFactory(void)
{
	
}

void CMonsterFactory::update(void)
{
	/*auto iterator = _monsterList.begin();

	for (iterator; iterator != _monsterList.end();) {
		if ((*iterator)->getState() == CMonster::EState::DEATH) {
			(*iterator)->setState(CMonster::EState::REMOVE);

			if (_removeObject->getMonsterName() == "M_Argass")		(MArgass*)(*iterator)
			if (_removeObject->getMonsterName() == "M_Basilisk")
			if (_removeObject->getMonsterName() == "M_CraftySpider")
			if (_removeObject->getMonsterName() == "M_DooBean")
			if (_removeObject->getMonsterName() == "M_GhillieDhu")
			if (_removeObject->getMonsterName() == "M_Plant_mini")
			if (_removeObject->getMonsterName() == "M_PollutedWolf")
			_monsterList.erase(iterator);
		}
		else {
			++iterator;
		}
	}*/
}

void CMonsterFactory::CreateBasilisk(int count)
{
	for (int i = 0; i < count; ++i) {
		MBasilisk* monster = new MBasilisk("M_Basilisk");
		monster->init();
		
		monster->setPosition(D3DXVECTOR3(27, 0.0f, 65));

		_monsterList.push_back(monster);
	}
}

void CMonsterFactory::CreateGhillieDhu(int count)
{
	for (int i = 0; i < count; ++i) {
		MGhillieDhu* monster = new MGhillieDhu("M_GhillieDhu");
		monster->init();

		if (CreateIntRandomValue(0, 100) <= 50) {
			x = CreateFloatRandomValue(-129.0f, 87.0f);
			z = CreateFloatRandomValue(278.0f, 400.0f);
		}
		else
		{
			x = CreateFloatRandomValue(-172.0f, -30.0f);
			z = CreateFloatRandomValue(-295.0f, -176.0f);
		}
		monster->setPosition(D3DXVECTOR3(x, 0.0f, z));

		_monsterList.push_back(monster);
	}
}

void CMonsterFactory::CreateArgass(int count)
{
	for (int i = 0; i < count; ++i) {
		MArgass* monster = new MArgass("M_Argass");
		monster->init();
		
		if (CreateIntRandomValue(0, 100) <= 50) {
			x = CreateFloatRandomValue(-129.0f, 87.0f);
			z = CreateFloatRandomValue(278.0f, 400.0f);
		}
		else {
			x = CreateFloatRandomValue(-172.0f, -30.0f);
			z = CreateFloatRandomValue(-295.0f, -176.0f);
		}
		monster->setPosition(D3DXVECTOR3(x, 0.0f, z));

		_monsterList.push_back(monster);
	}
}
void CMonsterFactory::CreateCraftySpider(int count)
{
	for (int i = 0; i < count; ++i) {
		MCraftySpider* monster = new MCraftySpider("M_CraftySpider");
		monster->init();

		x = CreateFloatRandomValue(200.0f, 400.0f);
		z = CreateFloatRandomValue(220.0f, 400.0f);

		monster->setPosition(D3DXVECTOR3(x, 0.0f, z));

		_monsterList.push_back(monster);
	}

}
void CMonsterFactory::CreateDooBean(int count)
{
	for (int i = 0; i < count; ++i) {
		MDooBean* monster = new MDooBean("M_DooBean");
		monster->init();

		if (CreateIntRandomValue(0, 100) <= 50) {
			x = CreateFloatRandomValue(-447.0f, -222.0f);
			z = CreateFloatRandomValue(270.0f, 400.0f);
		}
		else {
			x = CreateFloatRandomValue(-113.0f, 190.0f);
			z = CreateFloatRandomValue(-50.0f, 150.0f);
		}

		monster->setPosition(D3DXVECTOR3(x, 0.0f, z));

		_monsterList.push_back(monster);
	}

}
void CMonsterFactory::CreatePlantMini(int count)
{
	for (int i = 0; i < count; ++i) {
		MPlantMini* monster = new MPlantMini("M_Plant_mini");
		monster->init();

		if (CreateIntRandomValue(0, 100) <= 50) {
			x = CreateFloatRandomValue(-400.0f, 222.0f);
			z = CreateFloatRandomValue(270.0f, 400.0f);
		}
		else {
			x = CreateFloatRandomValue(254.0f, 400.0f);
			z = CreateFloatRandomValue(227.0f, 400.0f);
		}

		monster->setPosition(D3DXVECTOR3(x, 0.0f, z));

		_monsterList.push_back(monster);
	}

}
void CMonsterFactory::CreatePollutedWolf(int count)
{
	for (int i = 0; i < count; ++i) {
		MPollutedWolf* monster = new MPollutedWolf("M_PollutedWolf");
		monster->init();

		x = CreateFloatRandomValue(-113.0f, 190.0f);
		z = CreateFloatRandomValue(-50.0f, 150.0f);

		monster->setPosition(D3DXVECTOR3(x, 0.0f, z));

		_monsterList.push_back(monster);
	}
}
void CMonsterFactory::CreateVergos()
{
	////////////////º¸½º
	MVergos* monster = new MVergos("M_Vergos");
	monster->init();

	_monsterList.push_back(monster);

	BossScene::setCompleteInitCount(10.0f);
}

void CMonsterFactory::removeMonster(void)
{
}

void CMonsterFactory::RemoveAllMonster(void)
{
}

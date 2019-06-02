#include "CMonsterFactory.h"

CMonsterFactory::~CMonsterFactory(void)
{
	/*for (auto &valueType : _monsterList) {
		SAFE_DELETE(valueType.second);
	}*/
}

void CMonsterFactory::CreateMonster(std::unordered_map<std::string, int> monsterCountList)
{
	auto iterator = monsterCountList.find("M_Basilisk");

	if (iterator != monsterCountList.end()) {
		monsterCount = 0;
		monsterTotalCount = 0.0f;
		for (int i = 0; i < iterator->second; ++i)
		{
			monsterTotalCount += 1;
		}
		for (int i = 0; i < iterator->second; ++i)
		{
			MBasilisk* monster = new MBasilisk("M_Basilisk");
			monster->init();

			_basiliskList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}


	iterator = monsterCountList.find("M_GhillieDhu");

	if (iterator != monsterCountList.end()) {
		monsterCount = 0;
		monsterTotalCount = 0.0f;
		for (int i = 0; i < iterator->second; ++i)
		{
			monsterTotalCount += 1;
		}
		for (int i = 0; i < iterator->second; ++i) 
		{
			MGhillieDhu* monster = new MGhillieDhu("M_GhillieDhu");
			monster->init();

			_gillieDhuList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}

	iterator = monsterCountList.find("M_Argass");

	if (iterator != monsterCountList.end()) 
	{
		monsterCount = 0;
		monsterTotalCount = 0.0f;
		for (int i = 0; i < iterator->second; ++i) {
			monsterTotalCount += 1;
		}
		for (int i = 0; i < iterator->second; ++i) 
		{
			MArgass* monster = new MArgass("M_Argass");
			monster->init();

			_argassList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}

	iterator = monsterCountList.find("M_CraftySpider");

	if (iterator != monsterCountList.end()) 
	{
		monsterCount = 0;
		monsterTotalCount = 0.0f;
		for (int i = 0; i < iterator->second; ++i) 
		{
			monsterTotalCount += 1;
		}
		for (int i = 0; i < iterator->second; ++i) 
		{
			MCraftySpider* monster = new MCraftySpider("M_CraftySpider");
			monster->init();

			_craftySpiderList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}

	iterator = monsterCountList.find("M_DooBean");

	if (iterator != monsterCountList.end()) 
	{
		monsterCount = 0;
		monsterTotalCount = 0.0f;
		for (int i = 0; i < iterator->second; ++i) {
			monsterTotalCount += 1;
		}
		for (int i = 0; i < iterator->second; ++i) 
		{
			MDooBean* monster = new MDooBean("M_DooBean");
			monster->init();

			_dooBeanList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}

	iterator = monsterCountList.find("M_Plant_mini");

	if (iterator != monsterCountList.end()) 
	{
		monsterCount = 0;
		monsterTotalCount = 0.0f;
		for (int i = 0; i < iterator->second; ++i) 
		{
			monsterTotalCount += 1;
		}
		for (int i = 0; i < iterator->second; ++i) 
		{
			MPlantMini* monster = new MPlantMini("M_Plant_mini");
			monster->init();

			_plantMiniList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}

	iterator = monsterCountList.find("M_PollutedWolf");

	if (iterator != monsterCountList.end()) 
	{
		monsterCount = 0;
		monsterTotalCount = 0.0f;
		for (int i = 0; i < iterator->second; ++i) 
		{
			monsterTotalCount += 1;
		}
		for (int i = 0; i < iterator->second; ++i) 
		{
			MPollutedWolf* monster = new MPollutedWolf("M_PollutedWolf");
			monster->init();

			_pollutedWolfList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}

	////////////////º¸½º
	iterator = monsterCountList.find("M_Vergos");

	if (iterator != monsterCountList.end()) {

		for (int i = 0; i < iterator->second; ++i) {
			MVergos* monster = new MVergos("M_Vergos");
			monster->init();

			_vergosList.push_back(monster);
			_monsterList.push_back(monster);
		}
	}
}

#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"
#include "../../Global/Utility/Object/CSkinnedMesh.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../../Global/Utility/Manager/CSchedulerManager.h"
#include "../TeraDMFont/CTeraDMFont.h"
#include "../Player/CPlayer.h"

class CLabel;
class CSkinnedMeshBoss;

//! 몬스터 클래스
class CMonster : public CRenderObject
{
public:

	struct STBattleObject
	{
		CPlayer * target = nullptr;
		STBoundingSphere tSphere;
		STBoundingSphere mWeaponSphere;
		STBoundingSphere mSubWeaponSphere;
		D3DXVECTOR3 tPos;
		D3DXVECTOR3 mPos;
		D3DXVECTOR3 vecDir;
		D3DXVECTOR3 direction;
		float distance;
	};

	enum class EState
	{
		NONE = 0,
		MOVE,
		NORMAL,
		ATK,
		ISATTACKING,
		BEATTACKED,
		WALK,
		DEATH,
		REMOVE
	};

	struct STStatus
	{
		int hp;
		int minAtk;
		int maxAtk;
		int PerDef;
		int perAtkCri;
		int perAtkDmg;
		int perAtkAcc;
		int realAtk;
		float atkDelayTime;
	};

public:				// public 함수

	// 생성자 & 소멸자
	explicit CMonster(const std::string & monsterName);
	virtual ~CMonster(void);

	// 인터페이스
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

	// 애니메이션
	virtual void Wait(void);
	virtual void Walk(void);
	virtual void Move(void);
	virtual void NormalAtk(void);
	virtual void BeAttacked(CPlayer * target, int tDamage);
	virtual void Death(void);

	virtual void Skill01(void){}
	virtual void Skill02(void){}
	virtual void Skill03(void){}
	virtual void Skill04(void){}
	virtual void Skill05(void){}
	

public:				// getter setter

	//! 몬스터 상태를 반환한다
	EState getState(void) { return _state; }

	void setState(EState state) { _state = state; }

	//! 몬스터 능력치를 반환한다
	STStatus getStatus(void) { return _status; }

	CSkinnedMesh * getSkinnedMesh(void) { return _skinnedMesh; }
	CSkinnedMeshBoss * getSkinnedMeshBoss(void) { return _skinnedMeshBoss; }

	std::string getMonsterName(void) { return _monsterName; }

	CLabel* getMissLabel(void) { return _missLabel; }


private:			// private 함수

	// 스킨드 메시를 생성한다
	CSkinnedMesh * CreateSkinnedMesh();

	CSkinnedMeshBoss * CreateSkinnedMeshBoss();

protected:			// private 변수

	std::string _monsterName = "";
	CSkinnedMesh * _skinnedMesh = nullptr;
	CSkinnedMeshBoss * _skinnedMeshBoss = nullptr;
	EState _state;
	STStatus _status;

	D3DXVECTOR3 _direction;
	float _changeDirTime = 0.0f;
	float _changeDirTimer = 0.0f;
	float _moveSpeed = 0.0f;
	float _moveTime = 0.0f;
	float _moveTimer = 0.0f;

	CLabel * _criLabel = nullptr;
	CLabel * _missLabel = nullptr;

	CObject * _target = nullptr;

	STBattleObject _battleObj;

	CTeraDMFont* _damageSkin = nullptr;

	bool _isHitAtk = false;

	float _soundTimer = 0.0f;

	
};
#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

class CSkinnedMesh;
class CLabel;
class CMonster;
class CTeraDMFont;
class CTeraEffect;
class CParticleSystem;

//! 플레이어 클래스
class CPlayer : public CRenderObject
{
public:

	enum class ESubState
	{
		NONE = 0,
		RUN,
		WAIT
	};

	enum class EMainState
	{
		NONE = 0,
		NORMAL,
		ATK,
		ISATK,
		JUMP,
		GAIACRUSH,
		CUTTINGSLASH,
		STINGERBLADE,
		WALK,
		BEATTACK,
		TENACITY
	};

	struct STStateMachine
	{
		EMainState main;
		ESubState sub;
	};

	struct STStatus
	{
		int hp;
		int MaxAtk;
		int MinAtk;
		int perDef;
		int perAtkCri;
		int perAtkCriDmg;
		int realAtk;
		int perAtkAcc;
		int lastAtkDelayTime;
	};

public:			// 생성자

	//! 생성자
	explicit CPlayer(void);

	//! 소멸자
	virtual ~CPlayer(void);

public:			// getter & setter

	//! 스킨드메시를 가져온다
	CSkinnedMesh * getSkinnedMesh(void) { return _skinnedMesh; }

	//! 플레이어 드로우 여부를 설정한다.
	void setVisible(bool isVisible);

	EMainState getPlayerState(void) { return _state.main; }

	STStatus getPlayerStatus(void) { return _status; }


public:			// 인터페이스

	//! 초기화 한다
	void init(void);

	//! 업데이트 
	virtual void update(void) final override;

public:			// public 함수

	void NormalAtk(void);
	void AtkRun(void);
	void Death(void);
	void InWeapon(void);
	void NormalRun(void);
	void NormalWalk(void);
	void OutWeapon(void);
	void BeAttacked(CMonster * target, int damage);
	void NormalWait(void);
	void AttackWait(void);

	void doHitMonster(void);

private:

	//! 스킨드 메시를 생성한다
	CSkinnedMesh * CreateSkinnedMesh(void);

	CParticleSystem * CreateParticleSystem(void);

private:			// private 변수

	bool _isVisible = false;

	STStatus _status;
	STStateMachine _state;
	CSkinnedMesh * _skinnedMesh = nullptr;

	int _comboStack = 0;
	bool _isPlayingCombo = false;

	char _textComboStack[256] = "";
	CLabel * _label = nullptr;

	
	D3DXVECTOR3 _offsetPos;

	float testTime = 0.0f;
	bool testBool = false;

	D3DXVECTOR3 _direction;

	bool _isJumpLoop = false;
	float _jumpSpeed = 30.0f;
	float _jumpValocity = 0.5f;

	float _mapHeight = 0.0f;

	float _footTimer = 0.0f;

	float _prevAngle = 0.0f;


	float _atkWaitCount = 0;

	bool _isInWeapon = true;
	bool _isdoHit = false;
	bool _isdoSkill = false;

	float _count = 0;

	CMonster * _target = nullptr;
	CTeraDMFont * _damageSkin = nullptr;
	CTeraEffect * _buffEffect = nullptr;

	bool _isPlayWeapon = false;

	// 파티클

	CParticleSystem * _particleSystem = nullptr;
};
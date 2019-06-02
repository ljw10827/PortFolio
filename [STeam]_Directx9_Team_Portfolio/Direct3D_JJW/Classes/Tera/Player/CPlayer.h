#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

class CSkinnedMesh;
class CLabel;
class CMonster;
class CTeraDMFont;
class CTeraEffect;
class CParticleSystem;

//! �÷��̾� Ŭ����
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

public:			// ������

	//! ������
	explicit CPlayer(void);

	//! �Ҹ���
	virtual ~CPlayer(void);

public:			// getter & setter

	//! ��Ų��޽ø� �����´�
	CSkinnedMesh * getSkinnedMesh(void) { return _skinnedMesh; }

	//! �÷��̾� ��ο� ���θ� �����Ѵ�.
	void setVisible(bool isVisible);

	EMainState getPlayerState(void) { return _state.main; }

	STStatus getPlayerStatus(void) { return _status; }


public:			// �������̽�

	//! �ʱ�ȭ �Ѵ�
	void init(void);

	//! ������Ʈ 
	virtual void update(void) final override;

public:			// public �Լ�

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

	//! ��Ų�� �޽ø� �����Ѵ�
	CSkinnedMesh * CreateSkinnedMesh(void);

	CParticleSystem * CreateParticleSystem(void);

private:			// private ����

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

	// ��ƼŬ

	CParticleSystem * _particleSystem = nullptr;
};
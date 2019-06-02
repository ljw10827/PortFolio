#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../TeraEffect/CTeraEffect.h"
#include "CMonster.h"

class MVergos : public CMonster
{
public:

	struct effectStruct
	{
		CTeraEffect * bossFireBall = nullptr;
		D3DXVECTOR3 moveCoord;
		bool alive = false;
	};

public:				// public 함수

	// 생성자 & 소멸자
	explicit MVergos(const std::string & monsterName);
	virtual ~MVergos(void);

	// 인터페이스
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

	enum BossPosition
	{
		sky,
		ground
	};

	enum BossPhase
	{
		Phase1,
		Phase2,
		Phase3
	};

	int getUserDamage(void) { return userDamage; }


	void BeAttacked(CPlayer* player, int tDamage);

private:
	BossPosition bossPosition;
	BossPhase bossPhase = BossPhase::Phase1;

	bool bisPlayerPositionIsAnglePlus120 = false;
	bool bisPlayerPositionIsAngleMinus120 = false;

	bool flyStart = false;
	bool flyEnd = false;
	bool Akting = false;
	bool highFlying = false;
	bool lowFlying = false;
	bool RoundAtking = false;
	bool bisAlive = true;
	bool IsWaiting = true;
	bool battleStart = false;

	int firstY = 0;
	int totalHeight = 0;

	int pattern = 0;

	void bossBreathFlankRight(void);
	void bossBreathFlankLeft(void);
	void bossRoundAtkR(void);
	void bossRoundAtkL(void);

	// 페이즈 1
	void Phase1BreathFront(void);
	void Phase1BlowRight(void);
	void Phase1BlowLeft(void);

	// 페이즈 2
	void Phase2flyStart(void);
	void Phase2flyEnd(void);
	void Phase2flyBreath(void);
	void Phase2flyFireBall(void);

	// 페이즈 3
	void Phase3BlowHead(void);
	void Phase3BlowBatter(void);
	void Phase3BlowBatterShot(void);
	void Phase3BlowRight2(void);
	void Phase3BlowLeft2(void);

	void bossGroggy(void);
	void bossFlinch(void);
	void bossRoar(void);
	void bossDeath(void);

	void fireBallEffect(void);

	int hp = 10000;
	int BossDamage = 0;
	int userDamage = 0;

	std::vector<effectStruct> effectStructMove;

	CTeraEffect * bossFireBall[5];
	D3DXVECTOR3 FireBallDirection;
	CTeraEffect * bossBreath;
	bool fireExplosion = false;
	D3DXVECTOR3 fireExplosionPosition;
	bool FireBallAtk = false;
	bool BreathAtk = false;
	bool laserAtk[5] = { false };
	D3DXVECTOR3 laserPosition[5];

	CTeraEffect * ShockWave;
	bool ShockWaveAKt = false;
	bool ShockWaveAKtRed = false;
	CTeraEffect * ExplosionPosition;
	CTeraEffect * ShockWaveRed;

	CPlayer* _target = nullptr;

	CLabel* _label = nullptr;
};
#include "MVergos.h"
#include "../../Global/Function/GlobalFunction.h"

#include "../../Global/Utility/Manager/CSchedulerManager.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../Monster/CMonsterFactory.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../TeraScene/BossScene.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "../../Global/Utility/Object/CSkinnedMeshBoss.h"


// TODO
MVergos::MVergos(const std::string & monsterName)
	:
	CMonster(monsterName)
{

}

MVergos::~MVergos(void)
{
	CMonster::~CMonster();
}

void MVergos::init(void)
{
	CMonster::init();

	// TODO
	// 여러마리 뽑아볼려고 테스트 예시
	// 랜덤생성
	/*float x = CreateFloatRandomValue(-400.0f, 400.0f);
	float z = CreateFloatRandomValue(-400.0f, 400.0f);*/

	hp = 20000;

	firstY = 20.0f;
	this->rotateByYAxis(90);
	
	this->setPosition(D3DXVECTOR3(0, 200, 0));
	this->setScale(D3DXVECTOR3(0.5, 0.5f, 0.5f));

	bossPosition = ground;
	//PLAY_EFFECT_SOUND("Resources/Sounds/Player/Foot/Ostrich_Foot_Grass_01.wav");
	//PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FireBreath_Casting_Stereo_2.wav");

	for (int i = 0; i < 5; i++)
	{
		bossFireBall[i] = new CTeraEffect(L"Resources/Effekseers/FireBallTest2.efk");
		//bossFireBall[i]->setDeltaTime(0.2f);
	}
	bossBreath = new CTeraEffect(L"Resources/Effekseers/FireBreath.efk");
	ShockWave = new CTeraEffect(L"Resources/Effekseers/ShockWave.efk");
	ShockWaveRed = new CTeraEffect(L"Resources/Effekseers/ShockWaveRed.efk");
	ExplosionPosition = new CTeraEffect(L"Resources/Effekseers/FinalSlash.efk");
	StartBuff = new CTeraEffect(L"Resources/Effekseers/StartBuff.efk");
	StartBuff->setDeltaTime(0.70f);
	StartCircle = new CTeraEffect(L"Resources/Effekseers/StartCircle.efk");
	// ToDO
	StartCircle->setDeltaTime(0.8f);

	
	// 초기화
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 200, 0.01f, 200);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMeshBoss->setShadowMatrix(worldMatrix);


	_label = new CLabel("", 20);
	_label->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f - 40, 70.0f, 0.0f));
	_label->setColor(D3DXCOLOR(255, 0, 0,255));

	GET_DIRECT3D_APPLICATION()->AddCallback([=](void)->void {
		// 처음 연출
		SET_SCHEDULE(5.0f, [=](void) -> void {
			PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Pattern_01.wav");
			_skinnedMeshBoss->PlayAnimation("BreathJumpLoop", true);
			StartBuff->playEffeckseer(D3DXVECTOR3(0, 10, 0));
			StartBuff->setScaleEffekseer(140.0f, 140.0f, 140.0f);
		});
	});
	
}

void MVergos::update(void)
{
	CMonster::update();

	StartBuff->update();
	StartCircle->update();


	// 처음이면은
	if (!_startBuffEnd) {
		_skinnedMeshBoss->PlayAnimation("BreathJumpLoop", false);
		_startTimer += GET_DELTA_TIME();
		if (_startTimer <= 6.5f) {
			this->moveByYAxis(-30.f * GET_DELTA_TIME());
		}
		else {
			this->bossRoar();
			_startBuffEnd = true;
			StartCircle->playEffeckseer(D3DXVECTOR3(0,10,0));
			StartCircle->setScaleEffekseer(140.0f, 140.0f, 140.0f);
			this->setPosition(D3DXVECTOR3(0, 20.0f, 0));
		}
	}

	_target = ((BossScene*)(this->m_pParentObject))->getPlayer();

	hp -= BossDamage;

	char hpStr[256] = "";
	sprintf(hpStr,"보스 HP : %d\n", hp);

	_label->setString(hpStr);

	if (BossDamage > 1500.0f)
	{
		Akting = true;
		this->bossGroggy();
	}
	if (BossDamage <= 1500.0f && BossDamage >1000.0f)
	{
		
		Akting = true;
		this->bossFlinch();
	}

	BossDamage = 0;

	if (IS_KEY_PRESSED(DIK_Y))
	{
		BossDamage = 1500;
	}
	if (IS_KEY_PRESSED(DIK_U))
	{
		BossDamage = 1001;
	}

	if(IS_KEY_PRESSED(DIK_Z))
	{
		hp -= 1000.0f;
		((BossScene*)(this->m_pParentObject))->getTeraUI()->setBossHpPercent(1000);

		//printf("Hp : %d \n", hp);
	}
	if (hp < 0 && bisAlive)
	{
		bisAlive = false;
	}

	if (battleStart)
	{
		if (bisAlive)
		{
			if (bossPhase == BossPhase::Phase1 && hp < 14000)
			{
				SET_SCHEDULE(1, [=](void)->void {
					bossPhase = BossPhase::Phase2;
					bossPosition = sky;
					this->Phase2flyStart();
					highFlying = true;
				});
				Akting = true;
			}

			if (highFlying)
			{
				//PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_5.wav");
				this->moveByYAxis(2);
				totalHeight += 2;
				if (this->getPosition().y > 150)
				{
					auto bossPos = this->getPosition();
					bossPos.y = 150;
					this->setPosition(bossPos);
					highFlying = false;
				}
			}

			if (bossPhase == BossPhase::Phase2 && hp <= 7000)
			{
				//PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/NewBattle_02.wav");
				SET_SCHEDULE(1, [=](void)->void {
					highFlying = false;
					bossPhase = BossPhase::Phase3;
					bossPosition = ground;
					this->Phase2flyEnd();
					lowFlying = true;
				});
				Akting = true;
			}

			if (lowFlying)
			{
				this->moveByYAxis(-7);
				totalHeight -= 7;
				if (this->getPosition().y < firstY)
				{
					auto bossPos = this->getPosition();
					bossPos.y = firstY;
					this->setPosition(bossPos);
					//PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Pattern_01.wav");
				}
				Akting = true;
			}

			if (bossPosition == sky)
			{
				auto MonsterToPlayerVector = this->getPosition() - _target->getPosition();
				D3DXVec3Normalize(&MonsterToPlayerVector, &MonsterToPlayerVector);
				MonsterToPlayerVector.y = 0.0f;

				this->rotateByDirection(MonsterToPlayerVector);
			}
			if (bossPosition == ground)
			{
				auto MonsterToPlayerVector = this->getPosition() - _target->getPosition();
				D3DXVec3Normalize(&MonsterToPlayerVector, &MonsterToPlayerVector);
				MonsterToPlayerVector.y = 0.0f;

				auto dotAngleFirst = D3DXVec3Dot(&this->getForwardDirection(), &MonsterToPlayerVector);
				auto dotAngleSecond = D3DXVec3Dot(&this->getRightDirection(), &MonsterToPlayerVector);

				if (!bisPlayerPositionIsAnglePlus120)
				{
					if (dotAngleFirst < 0 && dotAngleSecond > 0)
					{
						bisPlayerPositionIsAnglePlus120 = true;
					}
				}
				if (!bisPlayerPositionIsAngleMinus120)
				{
					if (dotAngleFirst < 0 && dotAngleSecond < 0)
					{
						bisPlayerPositionIsAngleMinus120 = true;
					}
				}
			}
			if (bisPlayerPositionIsAnglePlus120 && !RoundAtking)
			{
				RoundAtking = true;
				this->bossRoundAtkR();
			}
			if (bisPlayerPositionIsAngleMinus120 && !RoundAtking)
			{
				RoundAtking = true;
				this->bossRoundAtkL();
			}

			if (!Akting && !bisPlayerPositionIsAnglePlus120 && !bisPlayerPositionIsAngleMinus120)
			{
				if (bossPhase == BossPhase::Phase1)
				{
					SET_SCHEDULE(2, [=](void)->void {
						if (!bisPlayerPositionIsAnglePlus120 && !bisPlayerPositionIsAngleMinus120 && bossPhase == BossPhase::Phase1)
						{
							auto MonsterToPlayerVector = this->getPosition() - _target->getPosition();
							{
								if (_skinnedMeshBoss->PlayingAnimationTrue())
								{
									pattern = CreateIntRandomValue(1, 2);
									if (pattern == 1)
									{
										this->Phase1BlowRight();
									}
									else if (pattern == 2)
									{
										this->Phase1BlowLeft();
									}
								}
							}
						}
					});
					Akting = true;
				}
				if (bossPhase == BossPhase::Phase2)
				{
					SET_SCHEDULE(0.5, [=](void)->void {
						pattern = CreateIntRandomValue(0, 100);
						if (pattern <= 35)
						{
							this->Phase2flyBreath();
						}
						else if (pattern > 35)
						{
							this->Phase2flyFireBall();
						}

					});
					Akting = true;
				}
				if (bossPhase == BossPhase::Phase3)
				{
					if (_skinnedMeshBoss->PlayingAnimationTrue())
					{
						if (fireExplosion == false)
						{
							SET_SCHEDULE(2, [=](void)->void {
								fireExplosionPosition = D3DXVECTOR3(CreateIntRandomValue(-150, 150), 20, CreateIntRandomValue(-150, 150));

								ExplosionPosition->playEffeckseer(fireExplosionPosition);
								ExplosionPosition->setScaleEffekseer(50, 50, 50);
								SET_SCHEDULE(2, [=](void)->void {
									bossFireBall[0]->fireBallExplosion(fireExplosionPosition);
									bossFireBall[0]->setScaleEffekseer(15, 15, 15);
									fireExplosion = true; });
							});
						}
						if (bossPhase == BossPhase::Phase1)
						{
							pattern = CreateIntRandomValue(1, 5);
							if (pattern == 1)
							{
								this->Phase3BlowHead();
							}
							else if (pattern == 2)
							{
								this->Phase3BlowBatter();
							}
							else if (pattern == 3)
							{
								this->Phase3BlowBatterShot();
							}
							else if (pattern == 4)
							{
								this->Phase3BlowRight2();
							}
							else if (pattern == 5)
							{
								this->Phase3BlowLeft2();
							}
						}
						Akting = true;
					}
				}
			}
		}
		else
		{
			if (hp < 0 && !bisAlive)
			{
				this->bossDeath();
				hp = 0;
			}

			if (hp == 0 && !bisAlive)
			{
				this->moveByYAxis(-0.05);
				if (this->getPosition().y < 0)
				{
					auto bossPos = this->getPosition();
					bossPos.y = 0;
					this->setPosition(bossPos);
				}
			}
		}
	}

	if (IS_KEY_PRESSED(DIK_0)) {

		pattern = CreateIntRandomValue(1, 5);
		if (pattern == 1)
		{
			this->Phase3BlowHead();
		}
		else if (pattern == 2)
		{
			this->Phase3BlowBatter();
		}
		else if (pattern == 3)
		{
			this->Phase3BlowBatterShot();
		}
		else if (pattern == 4)
		{
			this->Phase3BlowRight2();
		}
		else if (pattern == 5)
		{
			this->Phase3BlowLeft2();
		}
		Akting = true;
	}

	ExplosionPosition->update();
	ExplosionPosition->AddLocation(FireBallDirection);

	bossFireBall[0]->update();
	bossFireBall[0]->AddLocation(FireBallDirection);

	auto FireBallPos = bossFireBall[0]->getEffectPosition();

	if (FireBallPos.y < -100)
	{
		if (D3DXVec3Length(&(FireBallPos - _target->getPosition())) < 100 && FireBallAtk)
		{
			printf("파이어볼 피격!\n");

			auto hitCount = CreateIntRandomValue(0, 100);

			if (hitCount >= 30) {
				auto ran = CreateIntRandomValue(300, 400);
				_target->BeAttacked(this, ran);
			}

			FireBallAtk = false;
		}
		//FireBallAtk = false;
	}

	if (fireExplosion)
	{
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FireExplosion3Combo_Stereo.wav");
		if (D3DXVec3Length(&(fireExplosionPosition - _target->getPosition())) < 150)
		{
			printf("익스프로젼 피격!\n");
			auto hitCount = CreateIntRandomValue(0, 100);

			if (hitCount >= 20) {
				auto ran = CreateIntRandomValue(300, 400);
				_target->BeAttacked(this, ran);
			}
			fireExplosion = false;
		}
		fireExplosion = false;
	}

	if (IS_KEY_PRESSED(DIK_X))
	{
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_SoundWave_Stereo_1.wav");
	}

	bossBreath->update();
	bossBreath->AddLocation(FireBallDirection);

	auto BreathPos = bossBreath->getEffectPosition();
	BreathPos.y = 0;
	if (D3DXVec3Length(&(BreathPos - _target->getPosition())) < 70 && BreathAtk)
	{
		printf("브레스 피격!\n");
		auto hitCount = CreateIntRandomValue(0, 100);

		if (hitCount <= 80) {
			auto ran = CreateIntRandomValue(200, 400);
			_target->BeAttacked(this, ran);
		}

		BreathAtk = false;
	}

	if (D3DXVec3Length(&(D3DXVECTOR3(0.0f, 0.0f, 0.0f) - _target->getPosition())) < 150 && ShockWaveAKt)
	{
		printf("쇼크웨이브 피격!\n");

		auto hitCount = CreateIntRandomValue(0, 100);

		if (hitCount <= 80) {
			auto ran = CreateIntRandomValue(200, 300);
			_target->BeAttacked(this, ran);
		}

		ShockWaveAKt = false;
	}

	if (D3DXVec3Length(&(D3DXVECTOR3(0.0f, 0.0f, 0.0f) - _target->getPosition())) < 160 && ShockWaveAKtRed)
	{
		printf("쇼크웨이브 레드 피격!\n");

		auto hitCount = CreateIntRandomValue(0, 100);

		if (hitCount <= 90) {
			auto ran = CreateIntRandomValue(800, 1000);
			_target->BeAttacked(this, ran);
		}

		ShockWaveAKtRed = false;
	}

	ShockWave->update();
	ShockWaveRed->update();
	//ShockWaveRed->AddLocation(laserPosition[i]);
	//ShockWave->AddLocation(D3DXVECTOR3());

	//printf("%f, \n", D3DXVec3Length(&(D3DXVECTOR3(0.0f, 0.0f, 0.0f) - _target->getPosition())));
}

void MVergos::doDrawObject(void)
{
	CMonster::doDrawObject();
	for (int i = 0; i < 5; i++)
	{
		bossFireBall[i]->draw();
	}
	bossBreath->draw();
	ShockWave->draw();
	ShockWaveRed->draw();
	ExplosionPosition->draw();
	StartBuff->draw();
	StartCircle->draw();
}

void MVergos::BeAttacked(CPlayer * player, int tDamage)
{
	auto tPerAtkCri = player->getPlayerStatus().perAtkCri;
	auto tPerAtkCriDmg = player->getPlayerStatus().perAtkCriDmg;
	float baseDamage = tDamage;
	bool isCri = false;

	if (tPerAtkCri >= CreateIntRandomValue(0, 100)) {
		baseDamage = (float)(tDamage * (float)tPerAtkCriDmg / 100.0f);
		isCri = true;
	}

	if (isCri) {
		D3DXVECTOR3 pos = {
			GET_WINDOW_SIZE().cx / 2.0f + CreateFloatRandomValue(-200,200),
			GET_WINDOW_SIZE().cy / 2.0f + CreateFloatRandomValue(-200,100),
			0.0f
		};
		_criLabel->setPosition(pos);
		_criLabel->setVisible(true);

		SET_SCHEDULE(2.0f, [=](void)->void {
			_criLabel->setVisible(false);
		});
	}

	// 대미지계산 후 적용
	auto realDamage = baseDamage * (100.0f - _status.PerDef) / 100.0f;

	auto ranX = GET_WINDOW_SIZE().cx / 2.0f + CreateFloatRandomValue(-300, 300);
	auto ranY = 300 + CreateFloatRandomValue(-100, 100);

	_damageSkin->damageCalculate(realDamage, D3DXVECTOR3(ranX, ranY, 0.0f));
	((BossScene*)(this->m_pParentObject))->getTeraUI()->setBossHpPercent(realDamage);

	char soundPath[256];
	sprintf(soundPath, "Resources/Sounds/Player/NormalAtk/Damage00_%02d.wav", CreateIntRandomValue(0, 5));
	PLAY_EFFECT_SOUND(soundPath);

	BossDamage = realDamage;

}

void MVergos::fireBallEffect(void)
{
	auto MonsterToPlayerVector = _target->getPosition() - this->getFinalThirdWeaponBoundingSphereW().centerPosition;
	D3DXVECTOR3 fireBallMove = MonsterToPlayerVector / 100.0f;

	effectStruct effectstruct = { nullptr };
	effectstruct.bossFireBall = new CTeraEffect(L"Resources/Effekseers/FireBallTest2.efk");
	effectstruct.bossFireBall->playEffeckseer(this->getFinalThirdWeaponBoundingSphereW().centerPosition);
	effectstruct.bossFireBall->setScale(D3DXVECTOR3(15.0f, 15.0f, 15.0f));
	effectstruct.alive = true;
	effectstruct.moveCoord = fireBallMove;
	effectStructMove.push_back(effectstruct);
}

void MVergos::Phase1BreathFront(void)
{
	auto MonsterToPlayerVector = _target->getPosition() - _skinnedMeshBoss->getFinalThirdWeaponBoundingSphereW().centerPosition;
	FireBallDirection = MonsterToPlayerVector / 200;
	D3DXVec3Normalize(&MonsterToPlayerVector, &MonsterToPlayerVector);

	MonsterToPlayerVector.y = 0;

	SET_SCHEDULE(2.0f, [=](void)->void {
		bossBreath->playEffeckseer(_skinnedMeshBoss->getFinalThirdWeaponBoundingSphereW().centerPosition + D3DXVECTOR3(0, -200, 0)
			- MonsterToPlayerVector * 10.0f);
		bossBreath->setRotationEffekseer(0, 0, 0);
		bossBreath->setScaleEffekseer(5, 5, 5);
	});

	_skinnedMeshBoss->PlayAnimation("BreathFront", false, false, [=](const std::string &animName)->void {
		Akting = false;
		_skinnedMeshBoss->PlayAnimation("Wait", true);
	});
}


void MVergos::Phase1BlowRight(void)
{
	_skinnedMeshBoss->PlayAnimation("BlowRightStart", false, false, [=](const std::string &animName)->void {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FirePlace_Stereo_1.wav");
		SET_SCHEDULE(0.5f, [=](void)->void {
			auto monsterDirection = this->getForwardDirection();
			D3DXVec3Normalize(&monsterDirection, &monsterDirection);
			auto AtkDirection = monsterDirection * cos(60);
			D3DXVec3Normalize(&AtkDirection, &AtkDirection);
			ShockWave->playEffeckseer(AtkDirection * 20);
			ShockWave->setRotationEffekseer(0, 0, 0);
			ShockWave->setScaleEffekseer(100, 100, 100);

			ShockWaveAKt = true;
		});
		_skinnedMeshBoss->PlayAnimation("BlowRightShot", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BlowRightEnd", false, false, [=](const std::string &animName)->void {
				Akting = false;
				bisPlayerPositionIsAngleMinus120 = false;
				bisPlayerPositionIsAnglePlus120 = false;
				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::Phase1BlowLeft(void)
{
	_skinnedMeshBoss->PlayAnimation("BlowLeftStart", false, false, [=](const std::string &animName)->void {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FirePlace_Stereo_1.wav");
		SET_SCHEDULE(0.5f, [=](void)->void {
			auto monsterDirection = this->getForwardDirection();
			D3DXVec3Normalize(&monsterDirection, &monsterDirection);
			auto AtkDirection = monsterDirection * cos(-60);
			D3DXVec3Normalize(&AtkDirection, &AtkDirection);
			ShockWave->playEffeckseer(AtkDirection * 20);
			ShockWave->setRotationEffekseer(0, 0, 0);
			ShockWave->setScaleEffekseer(100, 100, 100);

			ShockWaveAKt = true;
		});
		_skinnedMeshBoss->PlayAnimation("BlowLeftShot", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BlowLeftEnd", false, false, [=](const std::string &animName)->void {
				Akting = false;
				bisPlayerPositionIsAngleMinus120 = false;
				bisPlayerPositionIsAnglePlus120 = false;
				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::Phase3BlowHead(void)
{
	SET_SCHEDULE(3.0, [=](void)->void {
		auto monsterDirection = this->getForwardDirection();
		auto AtkDirection = monsterDirection / cos(-30);
		D3DXVec3Normalize(&AtkDirection, &AtkDirection);

		ShockWaveRed->playEffeckseer(D3DXVECTOR3(0,0,0));
		ShockWaveRed->setRotationEffekseer(0, 0, 0);
		ShockWaveRed->setScaleEffekseer(400, 400, 250);

		ShockWaveAKtRed = true;
	});

	_skinnedMeshBoss->PlayAnimation("BlowHeadStart", false, false, [=](const std::string &animName)->void {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FireBreath_Stereo_01.wav");
		_skinnedMeshBoss->PlayAnimation("BlowHeadShot", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BlowHeadR", false, false, [=](const std::string &animName)->void {
				Akting = false;

				bisPlayerPositionIsAngleMinus120 = false;
				bisPlayerPositionIsAnglePlus120 = false;

				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::Phase3BlowBatter(void)
{
	_skinnedMeshBoss->PlayAnimation("BlowBatterStart", false, false, [=](const std::string &animName)->void {
		_skinnedMeshBoss->PlayAnimation("BlowBatterShot01", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BlowBatterR", false, false, [=](const std::string &animName)->void {
				Akting = false;
				bisPlayerPositionIsAngleMinus120 = false;
				bisPlayerPositionIsAnglePlus120 = false;
				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::Phase3BlowBatterShot(void)
{
	_skinnedMeshBoss->PlayAnimation("BlowBatterShot02Start", false, false, [=](const std::string &animName)->void {
		_skinnedMeshBoss->PlayAnimation("BlowBatterShot02End", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BlowBatterR", false, false, [=](const std::string &animName)->void {
				Akting = false;
				bisPlayerPositionIsAngleMinus120 = false;
				bisPlayerPositionIsAnglePlus120 = false;
				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::Phase3BlowRight2(void)
{
	_skinnedMeshBoss->PlayAnimation("Phase4_BlowLeft", false, false, [=](const std::string &animName)->void {
		Akting = false;
		bisPlayerPositionIsAngleMinus120 = false;
		bisPlayerPositionIsAnglePlus120 = false;
		_skinnedMeshBoss->PlayAnimation("Wait", true);
	});
}

void MVergos::Phase3BlowLeft2(void)
{
	_skinnedMeshBoss->PlayAnimation("Phase4_BlowRight", false, false, [=](const std::string &animName)->void {
		Akting = false;
		bisPlayerPositionIsAngleMinus120 = false;
		bisPlayerPositionIsAnglePlus120 = false;
		_skinnedMeshBoss->PlayAnimation("Wait", true);
	});
}

void MVergos::bossRoundAtkR(void)
{
	_skinnedMeshBoss->PlayAnimation("RoundAtk01R", false, false, [=](const std::string &animName)->void {
		_skinnedMeshBoss->PlayAnimation("RoundAtk01Start", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("RoundAtk01End", false, false, [=](const std::string &animName)->void {
				this->rotateByYAxis(140);

				Akting = false;
				RoundAtking = false;
				bisPlayerPositionIsAnglePlus120 = false;
				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::bossRoundAtkL(void)
{
	_skinnedMeshBoss->PlayAnimation("RoundAtk02R", false, false, [=](const std::string &animName)->void {
		_skinnedMeshBoss->PlayAnimation("RoundAtk02Start", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("RoundAtk02End", false, false, [=](const std::string &animName)->void {
				this->rotateByYAxis(-140);

				Akting = false;
				RoundAtking = false;
				bisPlayerPositionIsAngleMinus120 = false;
				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::Phase2flyStart(void)
{
	//_skinnedMeshBoss->StopAnimation();
	_skinnedMeshBoss->PlayAnimation("BreathJumpStart", false, false, [=](const std::string &animName)->void {
		Akting = false;
		highFlying = false;
		printf("%d\n", totalHeight);
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Phase2_01.wav");
		//PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FireBreath_Casting_Stereo_2.wav");
		bisPlayerPositionIsAngleMinus120 = false;
		bisPlayerPositionIsAnglePlus120 = false;
		_skinnedMeshBoss->PlayAnimation("BreathJumpLoop", true);
	});
}

void MVergos::Phase2flyEnd(void)
{
	_skinnedMeshBoss->StopAnimation();
	//PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Phase2_02.wav");
	_skinnedMeshBoss->PlayAnimation("BreathJumpEnd", false, false, [=](const std::string &animName)->void {
		Akting = false;
		lowFlying = false;
		printf("%d\n", totalHeight);
		bisPlayerPositionIsAngleMinus120 = false;
		bisPlayerPositionIsAnglePlus120 = false;
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Pattern_04.wav");
		_skinnedMeshBoss->PlayAnimation("Wait", true);
	});
}

void MVergos::Phase2flyBreath(void)
{
	BreathAtk = true;

	auto MonsterToPlayerVector = _target->getPosition() - _skinnedMeshBoss->getFinalThirdWeaponBoundingSphereW().centerPosition;
	FireBallDirection = MonsterToPlayerVector / 70;
	D3DXVec3Normalize(&MonsterToPlayerVector, &MonsterToPlayerVector);

	auto MonsterToPlayerVectorXZ = D3DXVECTOR3(MonsterToPlayerVector.x, 0.0, MonsterToPlayerVector.z);


	auto stAngle = D3DXVec3Dot(&MonsterToPlayerVector, &MonsterToPlayerVectorXZ);

	MonsterToPlayerVector.y = 0;

	auto tempAngle = D3DXToDegree(stAngle);

	SET_SCHEDULE(1.0f, [=](void)->void {
		bossBreath->playEffeckseer(_skinnedMeshBoss->getFinalThirdWeaponBoundingSphereW().centerPosition + D3DXVECTOR3(0, -200, 0)
			- MonsterToPlayerVector * 50.0f);
		bossBreath->setRotationEffekseer(0, 0, 0);
		bossBreath->setScaleEffekseer(5, 5, 5);
	});

	_skinnedMeshBoss->PlayAnimation("BreathJumpShot", false, false, [=](const std::string &animName)->void {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Attack_VOX_Wet_05.wav");
		auto dam = CreateIntRandomValue(300, 600);
		hp -= dam;
		((BossScene*)(this->m_pParentObject))->getTeraUI()->setBossHpPercent(dam);
		_skinnedMeshBoss->PlayAnimation("BreathJumpShotLoop", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BreathJumpShotEnd", false, false, [=](const std::string &animName)->void {
				Akting = false;
				_skinnedMeshBoss->PlayAnimation("BreathJumpLoop", true);
			});
		});
	});
}

void MVergos::Phase2flyFireBall(void)
{
	FireBallAtk = true;

	auto MonsterToPlayerVector = _target->getPosition() - _skinnedMeshBoss->getFinalMainWeaponBoundingSphereW().centerPosition;

	FireBallDirection = MonsterToPlayerVector / 150;
	D3DXVec3Normalize(&MonsterToPlayerVector, &MonsterToPlayerVector);

	MonsterToPlayerVector.y = 0;

	SET_SCHEDULE(0.8f, [=](void)->void {
		bossFireBall[0]->playEffeckseer(_skinnedMeshBoss->getFinalThirdWeaponBoundingSphereW().centerPosition + D3DXVECTOR3(0, -100, 0)
		- MonsterToPlayerVector * 50.0f);
		bossFireBall[0]->setScaleEffekseer(15, 15, 15);
	});

	_skinnedMeshBoss->PlayAnimation("BreathJumpShot", false, false, [=](const std::string &animName)->void {
		auto dam = CreateIntRandomValue(500, 1000);
		hp -= dam;
		((BossScene*)(this->m_pParentObject))->getTeraUI()->setBossHpPercent(dam);
		_skinnedMeshBoss->PlayAnimation("BreathJumpShotEnd", false, false, [=](const std::string &animName)->void {
			SET_SCHEDULE(1, [=](void)->void{PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FirePlace_Stereo_1.wav"); 
			});
			Akting = false;
			_skinnedMeshBoss->PlayAnimation("BreathJumpLoop", false);
		});
	});
}

void MVergos::bossGroggy(void)
{
	PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Idle_VOX_Dry_04.wav");

	_skinnedMeshBoss->PlayAnimation("Groggy", false, false, [=](const std::string &animName)->void {
		Akting = false;
		_skinnedMeshBoss->PlayAnimation("Wait", true);
	});
}

void MVergos::bossFlinch(void)
{
	PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Damage_VOX_Dry_03.wav");
	_skinnedMeshBoss->PlayAnimation("Flinch", false, false, [=](const std::string &animName)->void {
		Akting = false;
		_skinnedMeshBoss->PlayAnimation("Wait", true);
	});
}

void MVergos::bossRoar(void)
{
	    //PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FireBreath_Casting_Stereo_1.wav");
	_skinnedMeshBoss->PlayAnimation("Phase4_RoarStart", false, false, [=](const std::string &animName)->void {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FireBreath_Casting_Stereo_2.wav");
		_skinnedMeshBoss->PlayAnimation("Phase4_RoarLoop", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("Phase4_RoarEnd", false, false, [=](const std::string &animName)->void {
				Akting = false;
				battleStart = true;
				//PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_3.wav");
				_skinnedMeshBoss->PlayAnimation("Wait", true);
			});
		});
	});
}

void MVergos::bossDeath(void)
{
	PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Phase4_05.wav");
	//PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_Die_VOX_Wet_01.wav");
	_skinnedMeshBoss->PlayAnimation("Death", false, false, [=](const std::string &animName)->void {
		_skinnedMeshBoss->PlayAnimation("DeathWait", true);
	});
}

void MVergos::bossBreathFlankRight(void)
{
	PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FirePlace_Stereo_2.wav");
	RoundAtking = true;
	_skinnedMeshBoss->PlayAnimation("BreathFlankRightStart", false, false, [=](const std::string &animName)->void {
		_skinnedMeshBoss->PlayAnimation("BreathFlankRightLoop", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BreathFlankRightEnd", false, false, [=](const std::string &animName)->void {
				bisPlayerPositionIsAnglePlus120 = false;
				this->bossRoundAtkR();
			});
		});
	});
}

void MVergos::bossBreathFlankLeft(void)
{
	PLAY_EFFECT_SOUND("Resources/Sounds/Monster/Vergos/Vergos_FirePlace_Stereo_2.wav");

	RoundAtking = true;
	_skinnedMeshBoss->PlayAnimation("BreathFlankLeftStart", false, false, [=](const std::string &animName)->void {
		_skinnedMeshBoss->PlayAnimation("BreathFlankLeftLoop", false, false, [=](const std::string &animName)->void {
			_skinnedMeshBoss->PlayAnimation("BreathFlankLeftEnd", false, false, [=](const std::string &animName)->void {
				this->bossRoundAtkL();
			});
		});
	});
}
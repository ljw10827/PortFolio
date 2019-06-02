#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! 파티클 생성기
class CParticleEmitter : public IUpdateable
{
public:	
	
	//! 파티클 
	struct STParticle
	{
		bool isActive;
		float activeTime;
		float lifeTime;

		float scale;
		float startScale;
		float endScale;

		float angle;
		float angleVelocity;

		D3DXCOLOR color;
		D3DXCOLOR startColor;
		D3DXCOLOR endColor;

		D3DXVECTOR3 position;
		D3DXVECTOR3 velocity;
	};

	//! 매개변수
	struct STParameters
	{
		int maxNumParticles;
		int numParticlesPerSecond;
	};

public:			// 생성자

	//! 생성자
	explicit CParticleEmitter(const STParameters &parameters);

public:			// 인터페이스

	//! 상태를 갱신한다
	virtual void update(void) override;

public:			// public 함수

	//! 파티클 생성을 시작한다
	void StartParticleEmit();

	//! 파티클 생성을 중지한다.
	void StopParticleEmit(void);

public:			// getter

	//! 파티클 리스트를 반환한다
	std::vector<STParticle> getParticleList(void);

private:		// private 함수

	//! 파티클을 생성한다
	void CreateParticles(void);

	//! 파티클을 갱싱한다
	void UpdateParticles(void);

	//! 파티클을 제거한다
	void RemoveParticles(void);

private:			// private 변수
	
	float _skipTime = 0.0f;
	bool _isEmitEnable = false;

	STParameters _parameters;
	std::vector<STParticle> _particleList;
};
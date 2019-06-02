#include "CParticleEmitter.h"
#include "../Manager/CTimeManager.h"
#include "../../Function/GlobalFunction.h"

CParticleEmitter::CParticleEmitter(const STParameters & parameters)
	:
	_parameters(parameters),
	_skipTime(1.0f / parameters.numParticlesPerSecond)
{
}

void CParticleEmitter::update(void)
{
	if (_isEmitEnable) {
		this->CreateParticles();
	}

	this->UpdateParticles();
	this->RemoveParticles();
}

void CParticleEmitter::StartParticleEmit(void)
{
	_isEmitEnable = true;
}

void CParticleEmitter::StopParticleEmit(void)
{
	_isEmitEnable = false;
}

std::vector<CParticleEmitter::STParticle> CParticleEmitter::getParticleList(void)
{
	return _particleList;
}

void CParticleEmitter::CreateParticles(void)
{
	_skipTime += GET_DELTA_TIME() * 15;

	// 누적 된 시간만큼 생성 가능한 파티클을 만든다.
	while (_skipTime >= 1.0f / _parameters.numParticlesPerSecond) {
		_skipTime -= 1.0f / _parameters.numParticlesPerSecond;


		// 파티클 생성이 가능 한 경우
		if (_particleList.size() < _parameters.maxNumParticles) {
			STParticle particle;
			ZeroMemory(&particle, sizeof(particle));

			particle.isActive = true;
			particle.activeTime = CreateFloatRandomValue(0.5f, 1.2f);
			particle.lifeTime = particle.activeTime;

			particle.startColor = D3DXCOLOR(CreateFloatRandomValue(0.0f, 0.0f),
				CreateFloatRandomValue(0.0f, 0.0f),
				CreateFloatRandomValue(0.0f, 0.0f),
				1.0f);

			particle.endColor = D3DXCOLOR(CreateFloatRandomValue(0.5f, 0.5f),
				CreateFloatRandomValue(0.5f, 0.5f),
				CreateFloatRandomValue(0.5f, 0.5f),
				0.3f);

			particle.startScale = CreateFloatRandomValue(1.3f, 1.5f);
			particle.endScale = CreateFloatRandomValue(1.3f, 1.5f);

			particle.angleVelocity = 0;// CreateFloatRandomValue(30.0f, 30.0f);

			particle.velocity = D3DXVECTOR3(CreateFloatRandomValue(-1, 1),
				CreateFloatRandomValue(-20,10),
				CreateFloatRandomValue(-1, 1));
			_particleList.push_back(particle);
		}
	}
}

void CParticleEmitter::UpdateParticles(void)
{
	for (auto &particle : _particleList) {
		particle.lifeTime -= GET_DELTA_TIME();

		if (particle.lifeTime <= 0.0f) {
			particle.isActive = false;
		}
		else {
			particle.position += particle.velocity * GET_DELTA_TIME();
			particle.angle += particle.angleVelocity * GET_DELTA_TIME();

			/*
			//! 보간 공식
			- T의 범위는 0 ~ 1
			- P0 + (P1 - P0) * T
			- (P0 * (1 - T)) + (P1 * T)
			*/
			float time = particle.lifeTime / particle.activeTime;
			particle.color =
				particle.startColor +
				(particle.endColor - particle.startColor) * (1.0f - time);

			particle.scale =
				particle.startScale +
				(particle.endScale - particle.startScale) * (1.0f - time);

		}
	}
}

void CParticleEmitter::RemoveParticles(void)
{
	auto iterator = _particleList.begin();

	while (iterator != _particleList.end()) {
		if (iterator->isActive) {
			++iterator;
		}
		else {
			iterator = _particleList.erase(iterator);
		}
	}
}

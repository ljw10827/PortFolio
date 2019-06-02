#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! ��ƼŬ ������
class CParticleEmitter : public IUpdateable
{
public:	
	
	//! ��ƼŬ 
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

	//! �Ű�����
	struct STParameters
	{
		int maxNumParticles;
		int numParticlesPerSecond;
	};

public:			// ������

	//! ������
	explicit CParticleEmitter(const STParameters &parameters);

public:			// �������̽�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// public �Լ�

	//! ��ƼŬ ������ �����Ѵ�
	void StartParticleEmit();

	//! ��ƼŬ ������ �����Ѵ�.
	void StopParticleEmit(void);

public:			// getter

	//! ��ƼŬ ����Ʈ�� ��ȯ�Ѵ�
	std::vector<STParticle> getParticleList(void);

private:		// private �Լ�

	//! ��ƼŬ�� �����Ѵ�
	void CreateParticles(void);

	//! ��ƼŬ�� �����Ѵ�
	void UpdateParticles(void);

	//! ��ƼŬ�� �����Ѵ�
	void RemoveParticles(void);

private:			// private ����
	
	float _skipTime = 0.0f;
	bool _isEmitEnable = false;

	STParameters _parameters;
	std::vector<STParticle> _particleList;
};
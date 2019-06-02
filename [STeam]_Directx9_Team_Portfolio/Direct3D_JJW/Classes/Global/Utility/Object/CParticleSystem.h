#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"
#include "../Particle/CParticleEmitter.h"

//! ��ƼŬ �ý���
class CParticleSystem : public CRenderObject
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1
		};

		D3DXVECTOR3 position;
		D3DCOLOR color;
		D3DXVECTOR2 UV;
	};

	// �Ű�����
	struct STParameters
	{
		std::string textureFilepath;
		CParticleEmitter::STParameters emitterParameters;
	};

public:		// ������

	//! ������
	explicit CParticleSystem(const STParameters &parameters);

	//! �Ҹ���
	virtual ~CParticleSystem(void);

public:		// �������̽�

	//! ���¸� �����Ѵ�
	virtual void update(void);

	//! ��ü�� �׸� ���
	virtual void preDrawObject(void);

	//! ��ü�� �׸���
	virtual void doDrawObject(void);

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void);

public:		// public �Լ�
	
	//! ��ƼŬ �ִϸ��̼��� �����Ѵ�
	void StartParticleAnimation(float activeTime);

	//! ��ƼŬ �ִϸ��̼��� �����Ѵ�
	void StopParticleAnimation(void);

private:	// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer(void);

private:		// private ����

	STParameters _parameters;
	bool _isEmitEnable = false;
	float _lifeActiveTime = 0.0f;

	CParticleEmitter * _particleEmitter = nullptr;

	LPDIRECT3DTEXTURE9 _texture = nullptr;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = nullptr;
};
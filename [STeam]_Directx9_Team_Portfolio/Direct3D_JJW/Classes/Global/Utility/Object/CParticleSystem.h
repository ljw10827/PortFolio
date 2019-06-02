#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"
#include "../Particle/CParticleEmitter.h"

//! 파티클 시스템
class CParticleSystem : public CRenderObject
{
public:

	//! 정점
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

	// 매개변수
	struct STParameters
	{
		std::string textureFilepath;
		CParticleEmitter::STParameters emitterParameters;
	};

public:		// 생성자

	//! 생성자
	explicit CParticleSystem(const STParameters &parameters);

	//! 소멸자
	virtual ~CParticleSystem(void);

public:		// 인터페이스

	//! 상태를 갱신한다
	virtual void update(void);

	//! 객체를 그릴 경우
	virtual void preDrawObject(void);

	//! 객체를 그린다
	virtual void doDrawObject(void);

	//! 객체를 그렸을 경우
	virtual void postDrawObject(void);

public:		// public 함수
	
	//! 파티클 애니메이션을 시작한다
	void StartParticleAnimation(float activeTime);

	//! 파티클 애니메이션을 중지한다
	void StopParticleAnimation(void);

private:	// private 함수

	//! 정점 버퍼를 생성한다
	LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer(void);

private:		// private 변수

	STParameters _parameters;
	bool _isEmitEnable = false;
	float _lifeActiveTime = 0.0f;

	CParticleEmitter * _particleEmitter = nullptr;

	LPDIRECT3DTEXTURE9 _texture = nullptr;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = nullptr;
};
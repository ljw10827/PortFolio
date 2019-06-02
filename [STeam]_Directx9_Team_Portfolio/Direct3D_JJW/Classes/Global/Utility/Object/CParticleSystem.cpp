#include "CParticleSystem.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"
#include "../Manager/CTimeManager.h"

CParticleSystem::CParticleSystem(const STParameters & parameters)
	:
	_parameters(parameters)
{
	_texture = GET_TEXTURE(parameters.textureFilepath);
	_vertexBuffer = this->CreateVertexBuffer();

	_particleEmitter = new CParticleEmitter(parameters.emitterParameters);
}

CParticleSystem::~CParticleSystem(void)
{
	SAFE_DELETE(_particleEmitter);
}

void CParticleSystem::update(void)
{
	CRenderObject::update();
	_particleEmitter->update();

	if (_isEmitEnable) {
		_lifeActiveTime -= GET_DELTA_TIME();

		if (_lifeActiveTime <= 0.0f) {
			this->StopParticleAnimation();
		}
	}
}

void CParticleSystem::preDrawObject(void)
{
	CRenderObject::preDrawObject();

	GET_DEVICE()->SetRenderState(D3DRS_ZWRITEENABLE, false);
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);
	GET_DEVICE()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GET_DEVICE()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//// 텍스처의 알파값을 color정보랑 같이 연산하라
	//GET_DEVICE()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//GET_DEVICE()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	//GET_DEVICE()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	//// 텍스처의 컬러를 color 정보랑 같이 연산하라.
	//GET_DEVICE()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//GET_DEVICE()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	//GET_DEVICE()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
}

void CParticleSystem::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	// 행렬을 설정한다
	// {
	auto worldMatrix = this->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);
	// }

	// 정점 데이터를 설정한다
	// {
	STVertex *vertices = nullptr;
	auto particleList = _particleEmitter->getParticleList();

	if (SUCCEEDED(_vertexBuffer->Lock(0, 0, (void **)&vertices, 0))) {
		for (int i = 0; i < particleList.size(); ++i) {
			
			D3DXVECTOR3 positions[] = {
				D3DXVECTOR3(-0.5f, -0.5f, 0.0f),
				D3DXVECTOR3(-0.5f, 0.5f, 0.0f),
				D3DXVECTOR3(0.5f, 0.5f, 0.0f),
				D3DXVECTOR3(-0.5f, -0.5f, 0.0f),
				D3DXVECTOR3(0.5f, 0.5f, 0.0f),
				D3DXVECTOR3(0.5f, -0.5f, 0.0f)
			};

			int index = i * 6;
			auto particle = particleList[i];

			// 척도 행렬을 계산한다
			// {
			D3DXMATRIXA16 scaleMatrix;
			D3DXMatrixScaling(&scaleMatrix,
				particle.scale,
				particle.scale,
				particle.scale);
			// }

			// 회전 행렬을 계산한다
			// {
			D3DXMATRIXA16 rotateMatrix;
			D3DXMatrixRotationYawPitchRoll(&rotateMatrix,
				D3DXToRadian(particle.angle),
				D3DXToRadian(particle.angle),
				D3DXToRadian(particle.angle));
			// }

			// 이동 행렬을 계싼한다.
			//{
			D3DXMATRIXA16 translationMatrix;
			D3DXMatrixTranslation(&translationMatrix,
				particle.position.x,
				particle.position.y,
				particle.position.z);
			//}

			// 최종 행렬을 적용한다
			// {
			D3DXMATRIXA16 worldMatrix = scaleMatrix * rotateMatrix * translationMatrix;

			D3DXVec3TransformCoordArray(positions,
				sizeof(D3DXVECTOR3),
				positions,
				sizeof(D3DXVECTOR3),
				&worldMatrix,
				sizeof(positions) / sizeof(positions[0]));
			// }

			for (int j = 0; j < 6; ++j) {
				vertices[index + j].position = positions[j];
				vertices[index + j].color = particle.color;
			}

			vertices[index + 0].UV = D3DXVECTOR2(0.0f, 1.0f);
			vertices[index + 1].UV = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index + 2].UV = D3DXVECTOR2(1.0f, 0.0f);
			vertices[index + 3].UV = D3DXVECTOR2(0.0f, 1.0f);
			vertices[index + 4].UV = D3DXVECTOR2(1.0f, 0.0f);
			vertices[index + 5].UV = D3DXVECTOR2(1.0f, 1.0f);
		}

		_vertexBuffer->Unlock();
	}
	// }
	GET_DEVICE()->SetStreamSource(0, _vertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetTexture(0, _texture);
	GET_DEVICE()->SetFVF(STVertex::FVF);

	GET_DEVICE()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, particleList.size() *2);

}

void CParticleSystem::postDrawObject(void)
{
	CRenderObject::postDrawObject();

	GET_DEVICE()->SetTexture(0, nullptr);
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
	GET_DEVICE()->SetRenderState(D3DRS_ZWRITEENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	GET_DEVICE()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CParticleSystem::StartParticleAnimation(float activeTime)
{
	_isEmitEnable = true;
	_lifeActiveTime = activeTime;

	_particleEmitter->StartParticleEmit();
}

void CParticleSystem::StopParticleAnimation(void)
{
	_isEmitEnable = false;
	_lifeActiveTime = 0.0f;

	_particleEmitter->StopParticleEmit();
}

LPDIRECT3DVERTEXBUFFER9 CParticleSystem::CreateVertexBuffer(void)
{
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = nullptr;

	/*
	정점 버퍼에 데이터를 수시로 채워 넣을 경우 이는 많은 부하를 일으키는 원인이 된다.
	그렇기 때문에 이러한 작업을 좀 더 빠르게 하기 위해서는 버퍼를 동적으로 생성해야되며,
	해당 작업은 D3DUSAGE_DYNAMIC 옵션에 의해서 활성가능하다.

	또한, 동적 버퍼는 그래픽에 생성하는 것이 불가능하기 때문에
	D3DPOOL_MANAGED 옵션을 사용할 수 없다.
	(즉, 시스템 메모리에 정점 버퍼를 생성해야한다)
	*/
	// 정점 버퍼를 생성한다
	GET_DEVICE()->CreateVertexBuffer(sizeof(STVertex) * _parameters.emitterParameters.maxNumParticles * 6,
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_SYSTEMMEM,
		&vertexBuffer,
		nullptr);

	return vertexBuffer;
}

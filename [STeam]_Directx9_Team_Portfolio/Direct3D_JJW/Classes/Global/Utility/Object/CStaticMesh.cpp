#include "CStaticMesh.h"
#include "../Base/CDirect3DApplication.h"
#include "../Manager/CResourceManager.h"
#include "../Manager/CDeviceManager.h"
#include "CCamera.h"
#include "CLight.h"
#include "../../Function/GlobalFunction.h"

#define STATIC_MESH_TYPE_DEVICE		1
#define STATIC_MESH_TYPE_EFFECT		2

#define STATIC_MESH_TYPE		STATIC_MESH_TYPE_EFFECT

CStaticMesh::CStaticMesh(const STParameters & parameters)
{
#if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE
	_staticMesh = GET_STATIC_MESH(parameters.meshFilePath);

#else
	_effect = GET_EFFECT(parameters.effectFilePath);

	_staticMesh = GET_STATIC_MESH(parameters.meshFilePath);

	// 바운딩 정보를 설정한다
	// {
	auto boundingBox = CreateBoundingBox(_staticMesh.mesh);
	auto boundingSphere = CreateBoundingSphere(_staticMesh.mesh);

	this->setBoundingBox(boundingBox);
	this->setBoundingSphere(boundingSphere);
	// }

#endif		// #if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE
}

void CStaticMesh::preDrawObject(void)
{
	CRenderObject::preDrawObject();
	// 알파 블렌딩을 활성화한다
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GET_DEVICE()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CStaticMesh::doDrawObject(void)
{
	CRenderObject::doDrawObject();

#if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE

	// 행렬을 설정한다
	auto worldMatrix = this->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	for (int i = 0; i < _staticMesh.numMaterials; ++i) {
		GET_DEVICE()->SetMaterial(&_staticMesh.materialList[i]);
		GET_DEVICE()->SetTexture(0, _staticMesh.textureList[i]);

		_staticMesh.mesh->DrawSubset(i);

		GET_DEVICE()->SetTexture(0, nullptr);
	}

#else

	// 행렬을 설정한다
	// {
	auto worldMatrix = this->getFinalWorldMatrix();
	
	D3DXMATRIXA16 viewMatrix = GET_CAMERA()->getViewMatrix();
	D3DXMATRIXA16 projectionMatrix = GET_CAMERA()->getProjectionMatrix();

	_effect->SetMatrix("_worldMatrix", &worldMatrix);
	_effect->SetMatrix("_viewMatrix", &viewMatrix);
	_effect->SetMatrix("_projectionMatrix", &projectionMatrix);

	// 조명 설정
	D3DXVECTOR4 lightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);
	D3DXVECTOR4 viewPosition(GET_CAMERA()->getPosition(), 1.0f);

	_effect->SetVector("_lightDirection", &lightDirection);
	_effect->SetVector("_cameraPosition", &viewPosition);

	_effect->SetTechnique("MyTechnique");
	
	UINT numPasses = 0;
	_effect->Begin(&numPasses, 0);

	for (int i = 0; i < numPasses; ++i) {
		_effect->BeginPass(i);

		//! 렌더링 시작
		for (int j = 0; j < _staticMesh.numMaterials; ++j) {
			_effect->SetTexture("_texture", _staticMesh.textureList[j]);
			_effect->CommitChanges();

			_staticMesh.mesh->DrawSubset(j);
		}
		_effect->EndPass();
	}

	_effect->End();

#endif		// #if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE
}

void CStaticMesh::postDrawObject(void)
{
	CRenderObject::postDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

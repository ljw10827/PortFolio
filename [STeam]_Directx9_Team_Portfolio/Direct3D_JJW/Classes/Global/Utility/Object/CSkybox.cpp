#include "CSkybox.h"
#include "CCamera.h"
#include "../Base/CDirect3DApplication.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CSkybox::CSkybox(const STParameters & parameters)
{
	_mesh = this->CreateMesh(parameters.radius);
	_effect = GET_EFFECT(parameters.effectFilePath);
	_cubeTexture = GET_CUBE_TEXTURE(parameters.cubeTextureFilePath);
}

void CSkybox::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	D3DXMATRIXA16 worldMatrix = this->getFinalWorldMatrix();

	D3DXMATRIXA16 viewMatrix = GET_CAMERA()->getViewMatrix();
	D3DXMATRIXA16 projectionMatrix = GET_CAMERA()->getProjectionMatrix();

	_effect->SetMatrix("_worldMatrix", &worldMatrix);
	_effect->SetMatrix("_viewMatrix", &viewMatrix);
	_effect->SetMatrix("_projectionMatrix", &projectionMatrix);

	_effect->SetTexture("_cubeTexture", _cubeTexture);

	_effect->SetTechnique("MyTechnique");

	UINT numPasses = 0;
	_effect->Begin(&numPasses, 0);

	for (int i = 0; i < numPasses; ++i) {
		_effect->BeginPass(i);

		_mesh->DrawSubset(0);

		_effect->EndPass();
	}

	_effect->End();
}

LPD3DXMESH CSkybox::CreateMesh(const float radius)
{
	LPD3DXMESH mesh = nullptr;
	LPD3DXBUFFER adjacency = nullptr;

	D3DXCreateSphere(GET_DEVICE(),
		radius,
		50,
		50,
		&mesh,
		&adjacency);

	// 법선 정보를 계산한다
	D3DXComputeNormals(mesh, (DWORD*)(adjacency->GetBufferPointer()));

	return mesh;
}

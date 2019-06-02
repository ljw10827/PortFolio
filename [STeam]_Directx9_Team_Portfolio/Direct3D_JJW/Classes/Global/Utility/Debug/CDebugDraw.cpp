#include "CDebugDraw.h"
#include "../Manager/CDeviceManager.h"
#include "../../Function/GlobalFunction.h"

CDebugDraw::CDebugDraw(CRenderObject * targetObejct, EDebugType debugType)
	:
	_debugType(debugType),
	_targetObject(targetObejct)
{
	if (debugType == EDebugType::BOX) {
		auto boundingBox = _targetObject->getBoundingBox();
		_boxMesh = this->CreateBoxMesh(boundingBox);
	}
	else if(debugType == EDebugType::SPHERE){
		auto boundingSphere = _targetObject->getBoundingSphere();
		_sphereMesh = this->CreateSphereMesh(boundingSphere);

		auto weaponSphere = _targetObject->getWeaponSphere();
		_weaponMesh = this->CreateSphereMesh(weaponSphere);

		auto subWeaponSphere = _targetObject->getSubWeaponSphere();
		_subWeaponMesh = this->CreateSphereMesh(subWeaponSphere);

		auto thirdWeaponSphere = _targetObject->getThirdWeaponSphere();
		_thirdWeaponMesh = this->CreateSphereMesh(thirdWeaponSphere);
	}
}

CDebugDraw::~CDebugDraw(void)
{
	SAFE_RELEASE(_boxMesh);
	SAFE_RELEASE(_sphereMesh);
	SAFE_RELEASE(_weaponMesh);
}

void CDebugDraw::preDrawObject(void)
{
	CRenderObject::preDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);
	GET_DEVICE()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GET_DEVICE()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void CDebugDraw::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	if (_debugType == EDebugType::BOX) {
		this->DrawBoxMesh();
	}
	else {
		this->DrawSphereMesh();
		if (_targetObject->getMainWeaponName() != "none") {
			this->DrawWeaponMesh();
		}
		if (_targetObject->getSubWeaponName() != "none") {
			this->DrawSubWeaponMesh();
		}
		if (_targetObject->getThirdWeaponName() != "none") {
			this->DrawThirdWeaponMesh();
		}
	}

	this->DrawGuideLine();
}

void CDebugDraw::postDrawObject(void)
{
	CRenderObject::postDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
	GET_DEVICE()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	GET_DEVICE()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void CDebugDraw::DrawBoxMesh(void)
{
	auto boundingBox = _targetObject->getBoundingBox();

	D3DXMATRIXA16 translation;

	D3DXMatrixTranslation(&translation,
		(boundingBox.maxPosition.x + boundingBox.minPosition.x) / 2.0f,
		(boundingBox.maxPosition.y + boundingBox.minPosition.y) / 2.0f,
		(boundingBox.maxPosition.z + boundingBox.minPosition.z) / 2.0f);

	auto worldMatrix = translation * _targetObject->getBoundingWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	_boxMesh->DrawSubset(0);
}

void CDebugDraw::DrawSphereMesh(void)
{
	auto boundingSphere = _targetObject->getBoundingSphere();

	D3DXMATRIXA16 translation;

	D3DXMatrixTranslation(&translation,
		boundingSphere.centerPosition.x,
		boundingSphere.centerPosition.y,
		boundingSphere.centerPosition.z);

	auto worldMatrix = translation * _targetObject->getBoundingWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	_sphereMesh->DrawSubset(0);
}

void CDebugDraw::DrawWeaponMesh(void)
{
	auto boundingSphere = _targetObject->getWeaponSphere();

	D3DXMATRIXA16 translation;

	D3DXMatrixTranslation(&translation,
		boundingSphere.centerPosition.x,
		boundingSphere.centerPosition.y,
		boundingSphere.centerPosition.z);

	auto worldMatrix = translation * _targetObject->getMainWeaponBoundingWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	_weaponMesh->DrawSubset(0);

}

void CDebugDraw::DrawSubWeaponMesh(void)
{
	auto boundingSphere = _targetObject->getSubWeaponSphere();

	D3DXMATRIXA16 translation;

	D3DXMatrixTranslation(&translation,
		boundingSphere.centerPosition.x,
		boundingSphere.centerPosition.y,
		boundingSphere.centerPosition.z);

	auto worldMatrix = translation * _targetObject->getSubWeaponBoundingWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	_subWeaponMesh->DrawSubset(0);

}

void CDebugDraw::DrawThirdWeaponMesh(void)
{
	auto boundingSphere = _targetObject->getThirdWeaponSphere();

	D3DXMATRIXA16 translation;

	D3DXMatrixTranslation(&translation,
		boundingSphere.centerPosition.x,
		boundingSphere.centerPosition.y,
		boundingSphere.centerPosition.z);

	auto worldMatrix = translation * _targetObject->getThirdWeaponBoundingWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	_thirdWeaponMesh->DrawSubset(0);
}

void CDebugDraw::DrawGuideLine(void)
{

	// 월드 행렬을 설정한다
	// {
	D3DXMATRIXA16 worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	// }
	

	STVertex vertices[2];
	ZeroMemory(&vertices, sizeof(vertices));

	vertices[0].color = D3DCOLOR_XRGB(255, 255, 0);
	vertices[1].color = D3DCOLOR_XRGB(255, 255, 0);

	if (_debugType == EDebugType::SPHERE) {
		auto boundingSphere = _targetObject->getFinalBoundingSphere();
		vertices[0].position = boundingSphere.centerPosition;

		auto direction = WORLD_UP_DIRECTION + WORLD_RIGHT_DIRECTION;
		D3DXVec3Normalize(&direction, &direction);

		vertices[0].position = boundingSphere.centerPosition;
		vertices[1].position = boundingSphere.centerPosition + (direction * boundingSphere.radius);

		////////////////////// 웨펀
		//if (_targetObject->getIsPlayer()) {
		//	STVertex Wvertices[2];
		//	ZeroMemory(&Wvertices, sizeof(Wvertices));
		//	Wvertices[0].color = D3DCOLOR_XRGB(255, 255, 0);
		//	Wvertices[1].color = D3DCOLOR_XRGB(255, 255, 0);

		//	auto weaponSphere = _targetObject->getFinalBoundingSphereW();
		//	Wvertices[0].position = weaponSphere.centerPosition;

		//	auto Wdirection = WORLD_UP_DIRECTION + WORLD_RIGHT_DIRECTION;
		//	D3DXVec3Normalize(&Wdirection, &Wdirection);

		//	Wvertices[0].position = weaponSphere.centerPosition;
		//	Wvertices[1].position = weaponSphere.centerPosition + (Wdirection * weaponSphere.radius * 100.0f);

		//	GET_DEVICE()->SetFVF(STVertex::FVF);
		//	GET_DEVICE()->DrawPrimitiveUP(D3DPT_LINELIST, 1, Wvertices, sizeof(STVertex));
		//}
	}
	else {
		auto boundingBox = _targetObject->getFinalBoundingBox();

		vertices[0].position = boundingBox.minPosition;
		vertices[1].position = boundingBox.maxPosition;

		this->DrawBoundingBoxGuideLine();
	}

	GET_DEVICE()->SetFVF(STVertex::FVF);
	GET_DEVICE()->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(STVertex));
	GET_DEVICE()->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(STVertex));
}

void CDebugDraw::DrawBoundingBoxGuideLine(void)
{
	auto objectBox = _targetObject->getObjectBox();
	auto boundingBox = ConvertObjectBoxToBox(objectBox);
	STVertex vertices[24];
	int size = sizeof(vertices) / sizeof(vertices[0]);

	// 정점 정보를 세팅한다
	// {
	for (int i = 0; i < size; ++i) {
		vertices[i].color = D3DCOLOR_XRGB(0, 255, 0);
	}

	float deltaX = boundingBox.maxPosition.x - boundingBox.minPosition.x;
	float deltaY = boundingBox.maxPosition.y - boundingBox.minPosition.y;
	float deltaZ = boundingBox.maxPosition.z - boundingBox.minPosition.z;
	
	// 밑면 
	vertices[0].position = boundingBox.minPosition;
	vertices[1].position = boundingBox.minPosition + D3DXVECTOR3(0.0f, 0.0f, deltaZ);

	vertices[2].position = boundingBox.minPosition + D3DXVECTOR3(0.0f, 0.0f, deltaZ);
	vertices[3].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, 0.0f, deltaZ);

	vertices[4].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, 0.0f, deltaZ);
	vertices[5].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, 0.0f, 0.0f);

	vertices[6].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, 0.0f, 0.0f);
	vertices[7].position = boundingBox.minPosition;

	// 윗면 
	vertices[8].position = boundingBox.minPosition + D3DXVECTOR3(0.0f, deltaY, 0.0f);
	vertices[9].position = boundingBox.minPosition + D3DXVECTOR3(0.0f, deltaY, deltaZ);

	vertices[10].position = boundingBox.minPosition + D3DXVECTOR3(0.0f, deltaY, deltaZ);
	vertices[11].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, deltaY, deltaZ);

	vertices[12].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, deltaY, deltaZ);
	vertices[13].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, deltaY, 0.0f);

	vertices[14].position = boundingBox.minPosition + D3DXVECTOR3(deltaX, deltaY, 0.0f);
	vertices[15].position = boundingBox.minPosition + D3DXVECTOR3(0.0f, deltaY, 0.0f);

	// 기둥
	vertices[16].position = vertices[0].position;
	vertices[17].position = vertices[8].position;

	vertices[18].position = vertices[2].position;
	vertices[19].position = vertices[10].position;

	vertices[20].position = vertices[4].position;
	vertices[21].position = vertices[12].position;

	vertices[22].position = vertices[6].position;
	vertices[23].position = vertices[14].position;
	// }

	GET_DEVICE()->SetFVF(STVertex::FVF);
	GET_DEVICE()->DrawPrimitiveUP(D3DPT_LINELIST, 12, vertices, sizeof(STVertex));

}

LPD3DXMESH CDebugDraw::CreateBoxMesh(const STBoundingBox & boundingBox)
{
	LPD3DXMESH mesh = nullptr;

	//! 메시를 생성한다
	D3DXCreateBox(GET_DEVICE(),
		(boundingBox.maxPosition.x - boundingBox.minPosition.x),
		(boundingBox.maxPosition.y - boundingBox.minPosition.y), 
		(boundingBox.maxPosition.z - boundingBox.minPosition.z), 
		&mesh,
		nullptr);

	return mesh;
}

LPD3DXMESH CDebugDraw::CreateSphereMesh(const STBoundingSphere & boundingShpere)
{
	LPD3DXMESH mesh = nullptr;

	//! 메시를 생성한다
	D3DXCreateSphere(GET_DEVICE(),
		boundingShpere.radius,
		20,
		20,
		&mesh,
		nullptr);

	return mesh;
}

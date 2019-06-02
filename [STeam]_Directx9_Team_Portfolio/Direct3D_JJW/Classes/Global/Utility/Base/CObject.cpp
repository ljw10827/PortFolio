#include "CObject.h"
#include "../../Function/GlobalFunction.h"

CObject::CObject(void)
	:
	m_stPosition(0.0f, 0.0f, 0.0f),
	m_stScale(1.0f, 1.0f, 1.0f),
	m_stRotation(0.0f, 0.0f, 0.0f),

	m_stRightDirection(WORLD_RIGHT_DIRECTION),
	m_stUpDirection(WORLD_UP_DIRECTION),
	m_stForwardDirection(WORLD_FORWARD_DIRECTION)
{
	ZeroMemory(&_boundingBox, sizeof(STBoundingBox));
	ZeroMemory(&_boundingSphere, sizeof(STBoundingSphere));
	D3DXMatrixIdentity(&m_stWorldMatrix);
	D3DXMatrixIdentity(&m_stOffsetMatrix);
}

CObject::~CObject(void)
{
	for (auto pChildObject : m_oChildObjectList) {
		SAFE_DELETE(pChildObject);
	}
}


void CObject::update(void)
{
	// 이동 행렬을 계산한다
	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, m_stPosition.x, m_stPosition.y, m_stPosition.z);

	// 척도 행렬을 계산한다
	D3DXMATRIXA16 stScale;
	D3DXMatrixScaling(&stScale, m_stScale.x, m_stScale.y, m_stScale.z);

	// 회전 행렬을 계산한다
	D3DXMATRIXA16 stRotation;
	D3DXMatrixIdentity(&stRotation);

	CopyMemory(&stRotation._11, &m_stRightDirection, sizeof(m_stRightDirection));
	CopyMemory(&stRotation._21, &m_stUpDirection, sizeof(m_stUpDirection));
	CopyMemory(&stRotation._31, &m_stForwardDirection, sizeof(m_stForwardDirection));

	// 월드 행렬을 계산한다
	m_stWorldMatrix = stScale * stRotation * stTranslation;

	// 자식 객체 상태 갱신
	for (auto pChildObject : m_oChildObjectList) {
		pChildObject->update();
	}

}

D3DXVECTOR3 CObject::getPosition(void)
{
	return m_stPosition;
}

D3DXVECTOR3 CObject::getScale(void)
{
	return m_stScale;
}

D3DXVECTOR3 CObject::getFollowPosition(void)
{

	return this->getPosition();
}

D3DXVECTOR3 CObject::getRotation(void)
{
	return m_stRotation;
}

D3DXVECTOR3 CObject::getRightDirection(void)
{
	return m_stRightDirection;
}

D3DXVECTOR3 CObject::getUpDirection(void)
{
	return m_stUpDirection;
}

D3DXVECTOR3 CObject::getForwardDirection(void)
{
	return m_stForwardDirection;
}

D3DXMATRIXA16 CObject::getWorldMatrix(void)
{
	return m_stWorldMatrix;
}

D3DXMATRIXA16 CObject::getBoundingWorldMatrix(void)
{
	return this->getFinalWorldMatrix();
}

D3DXMATRIXA16 CObject::getWeaponBoundingWorldMatrix(void)
{
	return this->getFinalWorldMatrix();
}

D3DXMATRIXA16 CObject::getMainWeaponBoundingWorldMatrix(void)
{
	return this->getFinalWorldMatrix();
}

D3DXMATRIXA16 CObject::getSubWeaponBoundingWorldMatrix(void)
{
	return this->getFinalWorldMatrix();
}

D3DXMATRIXA16 CObject::getThirdWeaponBoundingWorldMatrix(void)
{
	return this->getFinalWorldMatrix();
}

D3DXMATRIXA16 CObject::getFinalWorldMatrix(void)
{
	if (m_pParentObject == nullptr) {
		return m_stOffsetMatrix * m_stWorldMatrix;
	}

	auto stParenWorldMatrix = m_pParentObject->getFinalWorldMatrix();
	return m_stOffsetMatrix * m_stWorldMatrix * stParenWorldMatrix;
}

STBoundingBox CObject::getAxisAlignBox(void)
{
	auto objectBox = this->getObjectBox();
	return ConvertObjectBoxToBox(objectBox);
}

STObjectBox CObject::getObjectBox(void)
{
	STObjectBox objectBox;
	ZeroMemory(&objectBox, sizeof(objectBox));

	auto boundingBox = this->getFinalBoundingBox();
	auto worldMatrix = this->getBoundingWorldMatrix();


	// 축 정보를 설정한다
	D3DXVECTOR3 rightDirection;
	D3DXVECTOR3 upDirection;
	D3DXVECTOR3 forwardDirection;

	CopyMemory(&rightDirection, &worldMatrix(0, 0), sizeof(D3DXVECTOR3));
	CopyMemory(&upDirection, &worldMatrix(1, 0), sizeof(D3DXVECTOR3));
	CopyMemory(&forwardDirection, &worldMatrix(2, 0), sizeof(D3DXVECTOR3));

	D3DXVec3Normalize(&objectBox.axis[X_DIRECTION], &rightDirection);
	D3DXVec3Normalize(&objectBox.axis[Y_DIRECTION], &upDirection);
	D3DXVec3Normalize(&objectBox.axis[Z_DIRECTION], &forwardDirection);

	/*objectBox.axis[X_DIRECTION] = this->getRightDirection();
	objectBox.axis[Y_DIRECTION] = this->getUpDirection();
	objectBox.axis[Z_DIRECTION] = this->getForwardDirection();*/

	// 중심 정보를 설정한다
	objectBox.centerPosition = (boundingBox.minPosition + boundingBox.maxPosition) / 2.0f;

	// 길이 정보를 설정한다
	// {
	auto direction = boundingBox.maxPosition - boundingBox.minPosition;

	for (int i = 0; i < MAX_NUM_DIRECTIONS; ++i) {
		auto axis = objectBox.axis[i];
		float dotValue = D3DXVec3Dot(&direction, &axis);

		objectBox.halfLengths[i] = dotValue / 2.0f;
	}
	// }

	return objectBox;
}

STBoundingBox CObject::getBoundingBox(void)
{
	return _boundingBox;
}

STBoundingSphere CObject::getBoundingSphere(void)
{
	return _boundingSphere;
}

STBoundingSphere CObject::getWeaponSphere(void)
{
	return _weaponSphere;
}

void CObject::setPosition(const D3DXVECTOR3 & a_rstPosition)
{
	m_stPosition = a_rstPosition;
}

void CObject::setScale(const D3DXVECTOR3 & a_rstScale)
{
	m_stScale = a_rstScale;
}

void CObject::setRotation(const D3DXVECTOR3 & a_rstRotation)
{
	m_stRotation = a_rstRotation;

	D3DXQUATERNION stQuaternion;
	D3DXQuaternionRotationYawPitchRoll(&stQuaternion, 
		D3DXToRadian(a_rstRotation.y), 
		D3DXToRadian(a_rstRotation.x), 
		D3DXToRadian(a_rstRotation.z));

	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationQuaternion(&stRotation, &stQuaternion);

	CopyMemory(&m_stRightDirection, &stRotation._11, sizeof(m_stRightDirection));
	CopyMemory(&m_stUpDirection, &stRotation._21, sizeof(m_stUpDirection));
	CopyMemory(&m_stForwardDirection, &stRotation._31, sizeof(m_stForwardDirection));

}

void CObject::setParentObject(CObject * a_pParentObject)
{
	assert(m_pParentObject == nullptr);
	m_pParentObject = a_pParentObject;
}

void CObject::setOffsetMatrix(const D3DXMATRIXA16 & a_rstOffsetMatrix)
{
	m_stOffsetMatrix = a_rstOffsetMatrix;
}

void CObject::setBoundingBox(const STBoundingBox & boundingBox)
{
	_boundingBox = boundingBox;
}

void CObject::setBoundingSphere(const STBoundingSphere & boundingSphere)
{
	_boundingSphere = boundingSphere;
}

void CObject::setBoundingSphereWeapon(const STBoundingSphere & boundingSphere)
{
	_weaponSphere = boundingSphere;
}

void CObject::setBoundingSphereSubWeapon(const STBoundingSphere & boundingSphere)
{
	_subWeaponSphere = boundingSphere;
}

void CObject::setBoundingSphereThirdWeapon(const STBoundingSphere & boundingSphere)
{
	_thirdWeaponSphere = boundingSphere;
}

//void CObject::setBoundingSphereW(const STBoundingSphere & boundingSphere)
//{
//	_weaponSphere = boundingSphere;
//}


STBoundingBox CObject::getFinalBoundingBox(void)
{
	auto worldMatrix = this->getBoundingWorldMatrix();
	auto boundingBox = this->getBoundingBox();

	D3DXVec3TransformCoord(&boundingBox.minPosition, &boundingBox.minPosition, &worldMatrix);
	D3DXVec3TransformCoord(&boundingBox.maxPosition, &boundingBox.maxPosition, &worldMatrix);

	return boundingBox;
}

STBoundingSphere CObject::getFinalBoundingSphere(void)
{
	auto worldMatrix = this->getBoundingWorldMatrix();
	auto boundingSphere = this->getBoundingSphere();

	D3DXVec3TransformCoord(&boundingSphere.centerPosition,
		&boundingSphere.centerPosition,
		&worldMatrix);

	boundingSphere.radius *= max(max(worldMatrix(0,0), worldMatrix(1,1)), max(worldMatrix(1, 1), worldMatrix(2, 2)));

	return boundingSphere;
}

STBoundingSphere CObject::getFinalMainWeaponBoundingSphereW(void)
{
	auto worldMatrix = this->getMainWeaponBoundingWorldMatrix();
	auto boundingSphere = this->getWeaponSphere();

	D3DXVec3TransformCoord(&boundingSphere.centerPosition,
		&boundingSphere.centerPosition,
		&worldMatrix);

	boundingSphere.radius *= max(max(m_stScale.x, m_stScale.y), max(m_stScale.y, m_stScale.z));

	return boundingSphere;
}

STBoundingSphere CObject::getFinalSubWeaponBoundingSphereW(void)
{
	auto worldMatrix = this->getSubWeaponBoundingWorldMatrix();
	auto boundingSphere = this->getWeaponSphere();

	D3DXVec3TransformCoord(&boundingSphere.centerPosition,
		&boundingSphere.centerPosition,
		&worldMatrix);

	boundingSphere.radius *= max(max(m_stScale.x, m_stScale.y), max(m_stScale.y, m_stScale.z));

	return boundingSphere;
}

STBoundingSphere CObject::getFinalThirdWeaponBoundingSphereW(void)
{
	auto worldMatrix = this->getThirdWeaponBoundingWorldMatrix();
	auto boundingSphere = this->getWeaponSphere();

	D3DXVec3TransformCoord(&boundingSphere.centerPosition,
		&boundingSphere.centerPosition,
		&worldMatrix);

	boundingSphere.radius *= max(max(m_stScale.x, m_stScale.y), max(m_stScale.y, m_stScale.z));

	return boundingSphere;
}

//STBoundingSphere CObject::getFinalBoundingSphereW(void)
//{
//	auto worldMatrix = this->getWeaponBoundingWorldMatrix();
//	auto boundingSphere = this->getWeaponSphere();
//
//	D3DXVec3TransformCoord(&boundingSphere.centerPosition,
//		&boundingSphere.centerPosition,
//		&worldMatrix);
//
//	boundingSphere.radius *= max(max(m_stScale.x, m_stScale.y), max(m_stScale.y, m_stScale.z));
//
//	return boundingSphere;
//}

void CObject::addChildObject(CObject * a_pChildObject)
{
	auto oIterator = std::find(m_oChildObjectList.begin(),
		m_oChildObjectList.end(),
		a_pChildObject);

	// 추가할 자식이 자식리스트에 없으면 추가하라
	if (oIterator == m_oChildObjectList.end()) {
		a_pChildObject->setParentObject(this);
		m_oChildObjectList.push_back(a_pChildObject);
	}
}

void CObject::removeChildObejct(CObject * a_pChildObject)
{
	auto oIterator = std::find(m_oChildObjectList.begin(),
		m_oChildObjectList.end(),
		a_pChildObject);

	// 지울 자식이 자식리스트에 있으면 지워라
	if (oIterator != m_oChildObjectList.end()) {
		SAFE_DELETE(*oIterator);
		m_oChildObjectList.erase(oIterator);
		// TODO:
		// 자식 객체 메모리 제거로직 필요
	}
}

void CObject::moveByXAxis(const float a_fOffset, const bool a_bIsLocal)
{
	if (a_bIsLocal) {
		m_stPosition += m_stRightDirection * a_fOffset;
	}
	else {
		m_stPosition += WORLD_RIGHT_DIRECTION * a_fOffset;
	}
}

void CObject::moveByYAxis(const float a_fOffset, const bool a_bIsLocal)
{

	if (a_bIsLocal) {
		m_stPosition += m_stUpDirection * a_fOffset;
	}
	else {
		m_stPosition += WORLD_UP_DIRECTION * a_fOffset;
	}
}

void CObject::moveByZAxis(const float a_fOffset, const bool a_bIsLocal)
{

	if (a_bIsLocal) {
		m_stPosition += m_stForwardDirection * a_fOffset;
	}
	else {
		m_stPosition += WORLD_FORWARD_DIRECTION * a_fOffset;
	}
}

void CObject::rotateByXAxis(const float a_fAngle, const bool a_bIsLocal)
{
	D3DXMATRIXA16 stRotation;
	/*
	D3DXMatrixRotationAxis 함수는 특정 축을 가지고 회전을 할 수 있는 행렬을 계산한다
	*/
	if (a_bIsLocal) {
		D3DXMatrixRotationAxis(&stRotation, &m_stRightDirection, D3DXToRadian(a_fAngle));
	}
	else {
		D3DXMatrixRotationAxis(&stRotation, &WORLD_RIGHT_DIRECTION, D3DXToRadian(a_fAngle));
	}

	/*
	D3DXVec3TransformCoord 함수는 벡터를 Point로 인식한다
	D3DXVec3TransformNormal 함수는 벡터를 Direction으로 인식한다
	(즉, D3DXVec3TransformNormal 함수는 이동연산이 의미가 없다.)
	*/
	this->rotateByMatrix(stRotation);
	/*
	기저 벡터는 항상 크기가 1이여야 하기 때문에
	회전 변환 후 크기를 다시 정규화 시켜준다.
	*/
	this->normalizeUnitAxis();
}

void CObject::rotateByYAxis(const float a_fAngle, const bool a_bIsLocal)
{
	D3DXMATRIXA16 stRotation;

	if (a_bIsLocal) {
		D3DXMatrixRotationAxis(&stRotation, &m_stUpDirection, D3DXToRadian(a_fAngle));
	}
	else {
		D3DXMatrixRotationAxis(&stRotation, &WORLD_UP_DIRECTION, D3DXToRadian(a_fAngle));
	}

	this->rotateByMatrix(stRotation);
	this->normalizeUnitAxis();
}

void CObject::rotateByZAxis(const float a_fAngle, const bool a_bIsLocal)
{
	D3DXMATRIXA16 stRotation;

	if (a_bIsLocal) {
		D3DXMatrixRotationAxis(&stRotation, &m_stForwardDirection, D3DXToRadian(a_fAngle));
	}
	else {
		D3DXMatrixRotationAxis(&stRotation, &WORLD_FORWARD_DIRECTION, D3DXToRadian(a_fAngle));
	}

	this->rotateByMatrix(stRotation);
	this->normalizeUnitAxis();
}

void CObject::rotateByPosition(const D3DXVECTOR3 & a_rstPosition, bool isBillboardY)
{
	auto stDirection = a_rstPosition - m_stPosition;
	D3DXVec3Normalize(&stDirection, &stDirection);

	this->rotateByDirection(stDirection, isBillboardY);
}

void CObject::rotateByDirection(const D3DXVECTOR3 & a_rstDirection, bool isBillboardY)
{
	m_stForwardDirection = a_rstDirection;
	m_stUpDirection = WORLD_UP_DIRECTION;

	if (isBillboardY) {
		m_stRightDirection.y = 0.0f;
		m_stForwardDirection.y = 0.0f;
		D3DXVec3Normalize(&m_stRightDirection, &m_stRightDirection);
		D3DXVec3Normalize(&m_stForwardDirection, &m_stForwardDirection);
	}

	this->resetUnitAxis();
}

void CObject::rotateByMatrix(const D3DXMATRIXA16 & a_rstMatrix)
{
	D3DXVec3TransformNormal(&m_stRightDirection, &m_stRightDirection, &a_rstMatrix);
	D3DXVec3TransformNormal(&m_stUpDirection, &m_stUpDirection, &a_rstMatrix);
	D3DXVec3TransformNormal(&m_stForwardDirection, &m_stForwardDirection, &a_rstMatrix);
}

void CObject::resetUnitAxis(void)
{
	D3DXVec3Cross(&m_stRightDirection, &m_stUpDirection, &m_stForwardDirection);
	D3DXVec3Cross(&m_stUpDirection, &m_stForwardDirection, &m_stRightDirection);

	this->normalizeUnitAxis();
}

void CObject::normalizeUnitAxis(void)
{
	D3DXVec3Normalize(&m_stRightDirection, &m_stRightDirection);
	D3DXVec3Normalize(&m_stUpDirection, &m_stUpDirection);
	D3DXVec3Normalize(&m_stForwardDirection, &m_stForwardDirection);
}

#include "CCamera.h"
#include "../Manager/CDeviceManager.h"

CCamera::CCamera(const float a_fAspect, const float a_fFieldOfView)
:
m_fAspect(a_fAspect)
{
	D3DXMatrixIdentity(&m_stViewMatrix);
	this->setFieldOfView(a_fFieldOfView);
}

D3DXMATRIXA16 CCamera::getViewMatrix(void)
{
	return m_stViewMatrix;
}

D3DXMATRIXA16 CCamera::getProjectionMatrix(void)
{
	return m_stProjectionMatrix;
}

void CCamera::setFieldOfView(const float a_fFieldOfView)
{
	m_fFieldOfView = a_fFieldOfView;

	D3DXMatrixPerspectiveFovLH(&m_stProjectionMatrix,
		D3DXToRadian(a_fFieldOfView),
		m_fAspect,
		0.1f,
		2000.0f);

	GET_DEVICE()->SetTransform(D3DTS_PROJECTION, &m_stProjectionMatrix);
}

void CCamera::setFollowObject(CObject * a_pFollowObject, 
	const D3DXVECTOR3 & a_rstFollowOffset,
	const EFollowType a_eFollowType)
{
	m_eFollowType = a_eFollowType;
	m_pFollowObject = a_pFollowObject;
	m_stFollowOffset = a_rstFollowOffset;
}

void CCamera::setFollowObjectEnable(bool isEnable)
{
	_isFollowEnable = isEnable;
}

void CCamera::update(void)
{
	CObject::update();

	if (m_pFollowObject != nullptr && _isFollowEnable) {
		auto stPosition = m_pFollowObject->getFollowPosition();
		stPosition.y = stPosition.y + 5.0f;

		if (m_eFollowType == EFollowType::FIXED) {
			this->setPosition(stPosition + m_stFollowOffset);
		}
		else {
			D3DXMATRIXA16 stRotation;
			D3DXMatrixIdentity(&stRotation);

			if (m_eFollowType == EFollowType::FREE) {
				auto stRightDirection = this->getRightDirection();
				auto stUpDirection = this->getUpDirection();
				auto stForwardDirection = this->getForwardDirection();

				CopyMemory(&stRotation(0, 0), &stRightDirection, sizeof(stRightDirection));
				CopyMemory(&stRotation(1, 0), &stUpDirection, sizeof(stUpDirection));
				CopyMemory(&stRotation(2, 0), &stForwardDirection, sizeof(stForwardDirection));
			}
			else {
				auto stRightDirection = m_pFollowObject->getRightDirection();
				auto stUpDirection = m_pFollowObject->getUpDirection();
				auto stForwardDirection = m_pFollowObject->getForwardDirection();
			
				CopyMemory(&stRotation(0, 0), &stRightDirection, sizeof(stRightDirection));
				CopyMemory(&stRotation(1, 0), &stUpDirection, sizeof(stUpDirection));
				CopyMemory(&stRotation(2, 0), &stForwardDirection, sizeof(stForwardDirection));
			}

			D3DXVECTOR3 stFollowOffset;
			D3DXVec3TransformCoord(&stFollowOffset, &m_stFollowOffset, &stRotation);

			this->setPosition(stPosition + stFollowOffset);
		}

		if (isBHeightPositionY)
		{
			this->setPosition(D3DXVECTOR3(this->getPosition().x, mapHeightPositionY, this->getPosition().z));
		}

		this->rotateByPosition(stPosition);
	}

	/*
	회전 행렬의 역행렬은 회전 행렬의 전치 행렬과 동일하다
	(단, 회전 행렬의 각 축이 단위 벡터 일 경우에만 해당한다)

	이동 행렬의 역행렬:			회전 행렬의 역행렬:
	  1,   0,   0, 0			Rx, Ux,	Fx, 0
	  0,   1,   0, 0			Ry,	Uy,	Fy, 0
	  0,   0,   1, 0			Rz,	Uz,	Fz, 0
	-px, -py, -pz, 1			 0,  0,  0, 1
	*/

	/*
	회전 행렬의 요소
	
			 Right.x,		   Up.x,		  Forward.x, 0,
			 Right.y,		   Up.y,		  Forward.y, 0,
			 Right.z,		   Up.z,		  Forward.z, 0,
	-(Pos dot Right), -(Pos dot Up), -(Pos dot Forward), 1
	*/
	D3DXMATRIXA16 stViewMatrix;
	D3DXMatrixIdentity(&stViewMatrix);

	stViewMatrix(0, 0) = m_stRightDirection.x;
	stViewMatrix(1, 0) = m_stRightDirection.y;
	stViewMatrix(2, 0) = m_stRightDirection.z;
	stViewMatrix(3, 0) = -D3DXVec3Dot(&m_stPosition, &m_stRightDirection);

	stViewMatrix(0, 1) = m_stUpDirection.x;
	stViewMatrix(1, 1) = m_stUpDirection.y;
	stViewMatrix(2, 1) = m_stUpDirection.z;
	stViewMatrix(3, 1) = -D3DXVec3Dot(&m_stPosition, &m_stUpDirection);

	stViewMatrix(0, 2) = m_stForwardDirection.x;
	stViewMatrix(1, 2) = m_stForwardDirection.y;
	stViewMatrix(2, 2) = m_stForwardDirection.z;
	stViewMatrix(3, 2) = -D3DXVec3Dot(&m_stPosition, &m_stForwardDirection);

	m_stViewMatrix = stViewMatrix;
	GET_DEVICE()->SetTransform(D3DTS_VIEW, &m_stViewMatrix);
}

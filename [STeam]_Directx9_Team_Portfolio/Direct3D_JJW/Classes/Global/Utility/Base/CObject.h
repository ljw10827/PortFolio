#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! 객체
class CObject : public IUpdateable
{
public:				// 인터페이스 구현

	//! 상태를 갱신한다
	virtual void update(void) override;

public:				// getter, setter
	
	//! 위치를 반환한다
	virtual D3DXVECTOR3 getPosition(void);

	//! 척도를 반환한다
	virtual D3DXVECTOR3 getScale(void);

	// 추적 위치를 반환한다
	virtual D3DXVECTOR3 getFollowPosition(void);

	//! 회전을 반환한다
	virtual D3DXVECTOR3 getRotation(void);


	//! X 축을 반환한다
	virtual D3DXVECTOR3 getRightDirection(void);


	//! Y 축을 반환한다
	virtual D3DXVECTOR3 getUpDirection(void);


	//! Z 축을 반환한다
	virtual D3DXVECTOR3 getForwardDirection(void);


	//! 월드 행렬을 반환한다
	virtual D3DXMATRIXA16 getWorldMatrix(void);

	//! 바운딩 월드 행렬을 반환한다
	virtual D3DXMATRIXA16 getBoundingWorldMatrix(void);

	//! 바운딩 월드 행렬을 반환한다
	virtual D3DXMATRIXA16 getWeaponBoundingWorldMatrix(void);

	//! 바운딩 월드 행렬을 반환한다
	// 몬스터터나 무기에 부착될 추가된 디버그(스피어, 박스)의 위치를 위한 용도
	virtual D3DXMATRIXA16 getMainWeaponBoundingWorldMatrix(void);
	virtual D3DXMATRIXA16 getSubWeaponBoundingWorldMatrix(void);
	virtual D3DXMATRIXA16 getThirdWeaponBoundingWorldMatrix(void);


	//! 최종 월드 행렬을 반환한다
	virtual D3DXMATRIXA16 getFinalWorldMatrix(void);

	//! 축 정렬 박스를 반환한다
	virtual STBoundingBox getAxisAlignBox(void);

	//! 객체 박스를 반환한다
	virtual STObjectBox getObjectBox(void);

	//! 바운딩 박스를 반환한다
	virtual STBoundingBox getBoundingBox(void);

	//! 바운딩 스피어를 반환한다
	virtual STBoundingSphere getBoundingSphere(void);

	STBoundingSphere getWeaponSphere(void);

	STBoundingSphere getSubWeaponSphere(void) { return _subWeaponSphere; }
	STBoundingSphere getThirdWeaponSphere(void) { return _thirdWeaponSphere; }
	SkinnedType getSkinnedType() { return _skinnedType; }

	// ---- setter

	//! 위치를 변경한다
	virtual void setPosition(const D3DXVECTOR3 &a_rstPosition);

	//! 척도를 변경한다
	virtual void setScale(const D3DXVECTOR3 &a_rstScale);

	//! 회전을 변경한다
	virtual void setRotation(const D3DXVECTOR3 &a_rstRotation);

	//! 부모 객체를 변경한다
	virtual void setParentObject(CObject *a_pParentObject);

	//! 오프셋 행렬을 변경한다
	virtual void setOffsetMatrix(const D3DXMATRIXA16 &a_rstOffsetMatrix);

	//! 바운딩 박스를 변경한다
	virtual void setBoundingBox(const STBoundingBox & boundingBox);

	//! 바운딩 스피어를 변경한다.
	virtual void setBoundingSphere(const STBoundingSphere & boundingSphere);

	//virtual void setBoundingSphereW(const STBoundingSphere & boundingSphere);

	virtual void setBoundingSphereWeapon(const STBoundingSphere & boundingSphere);
	virtual void setBoundingSphereSubWeapon(const STBoundingSphere & boundingSphere);
	virtual void setBoundingSphereThirdWeapon(const STBoundingSphere & boundingSphere);

	//! 최종 바운딩 박스를 반환한다
	virtual STBoundingBox getFinalBoundingBox(void);

	//! 최종 바인딩 박스를 반환한다
	virtual STBoundingSphere getFinalBoundingSphere(void);

	//virtual STBoundingSphere getFinalBoundingSphereW(void);

	virtual STBoundingSphere getFinalMainWeaponBoundingSphereW(void);
	virtual STBoundingSphere getFinalSubWeaponBoundingSphereW(void);
	virtual STBoundingSphere getFinalThirdWeaponBoundingSphereW(void);


public:				// public 함수
	
	//! 자식 객체를 추가한다
	void addChildObject(CObject *a_pChildObject);

	//! 자식 객체를 제거한다
	void removeChildObejct(CObject *a_pChildObject);

	//! X 축으로 위치를 변경한다
	void moveByXAxis(const float a_fOffset, const bool a_bIsLocal = true);

	//! Y 축으로 위치를 변경한다
	void moveByYAxis(const float a_fOffset, const bool a_bIsLocal = true);

	//! Z 축으로 위치를 변경한다
	void moveByZAxis(const float a_fOffset, const bool a_bIsLocal = true);

	//! X 축을 기준으로 회전한다
	void rotateByXAxis(const float a_fAngle, const bool a_bIsLocal = true);
	
	//! Y 축을 기준으로 회전한다
	void rotateByYAxis(const float a_fAngle, const bool a_bIsLocal = true);

	//! Z 축을 기준으로 회전한다
	void rotateByZAxis(const float a_fAngle, const bool a_bIsLocal = true);

	//! 해당 위치로 회전한다
	void rotateByPosition(const D3DXVECTOR3 &a_rstPosition, bool isBillboardY = false);

	//! 해당 방향으로 회전한다
	void rotateByDirection(const D3DXVECTOR3 &a_rstDirection, bool isBillboardY = false);

	//! 회전 행렬을 기준으로 회전한다
	void rotateByMatrix(const D3DXMATRIXA16 &a_rstMatrix);

	//! 축을 다시 정렬한다
	void resetUnitAxis(void);

	//! 기저 벡터를 정규화한다.
	void normalizeUnitAxis(void);


public:				// 생성자 & 소멸자

	//! 생성자
	explicit CObject(void);

	//! 소멸자
	virtual ~CObject(void);

public:
	std::string	getMainWeaponName() { return _MainWeapon; }
	std::string	getSubWeaponName() { return _SubWeapon; }
	std::string	getThirdWeaponName() { return _ThirdWeapon; }

protected:			// private 변수

	D3DXVECTOR3 m_stPosition;
	D3DXVECTOR3 m_stScale;
	D3DXVECTOR3 m_stRotation;

	D3DXVECTOR3 m_stRightDirection;
	D3DXVECTOR3 m_stUpDirection;
	D3DXVECTOR3 m_stForwardDirection;

	D3DXMATRIXA16 m_stWorldMatrix;
	D3DXMATRIXA16 m_stOffsetMatrix;

	CObject *m_pParentObject = nullptr;
	std::vector<CObject *> m_oChildObjectList;

	STBoundingBox _boundingBox;
	STBoundingSphere _boundingSphere;

	STBoundingSphere _weaponSphere;

	STBoundingSphere _subWeaponSphere;
	STBoundingSphere _thirdWeaponSphere;

	SkinnedType _skinnedType;

	std::string _MainWeapon = " ";
	std::string _SubWeapon = " ";
	std::string _ThirdWeapon = " ";
};
#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! ��ü
class CObject : public IUpdateable
{
public:				// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:				// getter, setter
	
	//! ��ġ�� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getPosition(void);

	//! ô���� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getScale(void);

	// ���� ��ġ�� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getFollowPosition(void);

	//! ȸ���� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getRotation(void);


	//! X ���� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getRightDirection(void);


	//! Y ���� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getUpDirection(void);


	//! Z ���� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getForwardDirection(void);


	//! ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getWorldMatrix(void);

	//! �ٿ�� ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getBoundingWorldMatrix(void);

	//! �ٿ�� ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getWeaponBoundingWorldMatrix(void);

	//! �ٿ�� ���� ����� ��ȯ�Ѵ�
	// �����ͳ� ���⿡ ������ �߰��� �����(���Ǿ�, �ڽ�)�� ��ġ�� ���� �뵵
	virtual D3DXMATRIXA16 getMainWeaponBoundingWorldMatrix(void);
	virtual D3DXMATRIXA16 getSubWeaponBoundingWorldMatrix(void);
	virtual D3DXMATRIXA16 getThirdWeaponBoundingWorldMatrix(void);


	//! ���� ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getFinalWorldMatrix(void);

	//! �� ���� �ڽ��� ��ȯ�Ѵ�
	virtual STBoundingBox getAxisAlignBox(void);

	//! ��ü �ڽ��� ��ȯ�Ѵ�
	virtual STObjectBox getObjectBox(void);

	//! �ٿ�� �ڽ��� ��ȯ�Ѵ�
	virtual STBoundingBox getBoundingBox(void);

	//! �ٿ�� ���Ǿ ��ȯ�Ѵ�
	virtual STBoundingSphere getBoundingSphere(void);

	STBoundingSphere getWeaponSphere(void);

	STBoundingSphere getSubWeaponSphere(void) { return _subWeaponSphere; }
	STBoundingSphere getThirdWeaponSphere(void) { return _thirdWeaponSphere; }
	SkinnedType getSkinnedType() { return _skinnedType; }

	// ---- setter

	//! ��ġ�� �����Ѵ�
	virtual void setPosition(const D3DXVECTOR3 &a_rstPosition);

	//! ô���� �����Ѵ�
	virtual void setScale(const D3DXVECTOR3 &a_rstScale);

	//! ȸ���� �����Ѵ�
	virtual void setRotation(const D3DXVECTOR3 &a_rstRotation);

	//! �θ� ��ü�� �����Ѵ�
	virtual void setParentObject(CObject *a_pParentObject);

	//! ������ ����� �����Ѵ�
	virtual void setOffsetMatrix(const D3DXMATRIXA16 &a_rstOffsetMatrix);

	//! �ٿ�� �ڽ��� �����Ѵ�
	virtual void setBoundingBox(const STBoundingBox & boundingBox);

	//! �ٿ�� ���Ǿ �����Ѵ�.
	virtual void setBoundingSphere(const STBoundingSphere & boundingSphere);

	//virtual void setBoundingSphereW(const STBoundingSphere & boundingSphere);

	virtual void setBoundingSphereWeapon(const STBoundingSphere & boundingSphere);
	virtual void setBoundingSphereSubWeapon(const STBoundingSphere & boundingSphere);
	virtual void setBoundingSphereThirdWeapon(const STBoundingSphere & boundingSphere);

	//! ���� �ٿ�� �ڽ��� ��ȯ�Ѵ�
	virtual STBoundingBox getFinalBoundingBox(void);

	//! ���� ���ε� �ڽ��� ��ȯ�Ѵ�
	virtual STBoundingSphere getFinalBoundingSphere(void);

	//virtual STBoundingSphere getFinalBoundingSphereW(void);

	virtual STBoundingSphere getFinalMainWeaponBoundingSphereW(void);
	virtual STBoundingSphere getFinalSubWeaponBoundingSphereW(void);
	virtual STBoundingSphere getFinalThirdWeaponBoundingSphereW(void);


public:				// public �Լ�
	
	//! �ڽ� ��ü�� �߰��Ѵ�
	void addChildObject(CObject *a_pChildObject);

	//! �ڽ� ��ü�� �����Ѵ�
	void removeChildObejct(CObject *a_pChildObject);

	//! X ������ ��ġ�� �����Ѵ�
	void moveByXAxis(const float a_fOffset, const bool a_bIsLocal = true);

	//! Y ������ ��ġ�� �����Ѵ�
	void moveByYAxis(const float a_fOffset, const bool a_bIsLocal = true);

	//! Z ������ ��ġ�� �����Ѵ�
	void moveByZAxis(const float a_fOffset, const bool a_bIsLocal = true);

	//! X ���� �������� ȸ���Ѵ�
	void rotateByXAxis(const float a_fAngle, const bool a_bIsLocal = true);
	
	//! Y ���� �������� ȸ���Ѵ�
	void rotateByYAxis(const float a_fAngle, const bool a_bIsLocal = true);

	//! Z ���� �������� ȸ���Ѵ�
	void rotateByZAxis(const float a_fAngle, const bool a_bIsLocal = true);

	//! �ش� ��ġ�� ȸ���Ѵ�
	void rotateByPosition(const D3DXVECTOR3 &a_rstPosition, bool isBillboardY = false);

	//! �ش� �������� ȸ���Ѵ�
	void rotateByDirection(const D3DXVECTOR3 &a_rstDirection, bool isBillboardY = false);

	//! ȸ�� ����� �������� ȸ���Ѵ�
	void rotateByMatrix(const D3DXMATRIXA16 &a_rstMatrix);

	//! ���� �ٽ� �����Ѵ�
	void resetUnitAxis(void);

	//! ���� ���͸� ����ȭ�Ѵ�.
	void normalizeUnitAxis(void);


public:				// ������ & �Ҹ���

	//! ������
	explicit CObject(void);

	//! �Ҹ���
	virtual ~CObject(void);

public:
	std::string	getMainWeaponName() { return _MainWeapon; }
	std::string	getSubWeaponName() { return _SubWeapon; }
	std::string	getThirdWeaponName() { return _ThirdWeapon; }

protected:			// private ����

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
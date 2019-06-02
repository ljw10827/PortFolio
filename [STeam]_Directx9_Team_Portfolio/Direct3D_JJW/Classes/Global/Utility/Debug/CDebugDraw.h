#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

class CDebugDraw : public CRenderObject
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};

		D3DXVECTOR3 position;
		D3DCOLOR color;
	};
public:		// ������, �Ҹ���

	//! ������
	explicit CDebugDraw(CRenderObject * targetObejct, EDebugType debugType);

	//! �Ҹ���
	virtual ~CDebugDraw(void);

public:		// public �Լ�

	//! ��ü�� �׸� ���
	virtual void preDrawObject(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void) override;

private:	// private �Լ�

	//! �ڽ� �޽ø� �׸���
	void DrawBoxMesh(void);

	//! ���Ǿ� �޽ø� �׸���
	void DrawSphereMesh(void);
	// ���⸦ �׸���
	void DrawWeaponMesh(void);
	void DrawSubWeaponMesh(void);
	void DrawThirdWeaponMesh(void);


	//! ���̵� ������ �׸���.
	void DrawGuideLine(void);

	//! �ٿ�� �ڽ� ���̵� ������ �׸���
	void DrawBoundingBoxGuideLine(void);

	//! �ڽ� �޽ø� �����Ѵ�
	LPD3DXMESH CreateBoxMesh(const STBoundingBox & boundingBox);

	//! ���Ǿ� �޽ø� �����Ѵ�
	LPD3DXMESH CreateSphereMesh(const STBoundingSphere & boundingShpere);

private:	// private ����

	LPD3DXMESH _boxMesh = nullptr;
	LPD3DXMESH _sphereMesh = nullptr;

	LPD3DXMESH _weaponMesh = nullptr;
	LPD3DXMESH _subWeaponMesh = nullptr;
	LPD3DXMESH _thirdWeaponMesh = nullptr;

	EDebugType _debugType = EDebugType::NONE;
	CRenderObject * _targetObject = nullptr;
};
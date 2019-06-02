#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

class CDebugDraw : public CRenderObject
{
public:

	//! 정점
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};

		D3DXVECTOR3 position;
		D3DCOLOR color;
	};
public:		// 생성자, 소멸자

	//! 생성자
	explicit CDebugDraw(CRenderObject * targetObejct, EDebugType debugType);

	//! 소멸자
	virtual ~CDebugDraw(void);

public:		// public 함수

	//! 객체를 그릴 경우
	virtual void preDrawObject(void) override;

	//! 객체를 그린다
	virtual void doDrawObject(void) override;

	//! 객체를 그렸을 경우
	virtual void postDrawObject(void) override;

private:	// private 함수

	//! 박스 메시를 그린다
	void DrawBoxMesh(void);

	//! 스피어 메시를 그린다
	void DrawSphereMesh(void);
	// 무기를 그린다
	void DrawWeaponMesh(void);
	void DrawSubWeaponMesh(void);
	void DrawThirdWeaponMesh(void);


	//! 가이드 라인을 그린다.
	void DrawGuideLine(void);

	//! 바운딩 박스 가이드 라인을 그린다
	void DrawBoundingBoxGuideLine(void);

	//! 박스 메시를 생성한다
	LPD3DXMESH CreateBoxMesh(const STBoundingBox & boundingBox);

	//! 스피어 메시를 생성한다
	LPD3DXMESH CreateSphereMesh(const STBoundingSphere & boundingShpere);

private:	// private 변수

	LPD3DXMESH _boxMesh = nullptr;
	LPD3DXMESH _sphereMesh = nullptr;

	LPD3DXMESH _weaponMesh = nullptr;
	LPD3DXMESH _subWeaponMesh = nullptr;
	LPD3DXMESH _thirdWeaponMesh = nullptr;

	EDebugType _debugType = EDebugType::NONE;
	CRenderObject * _targetObject = nullptr;
};
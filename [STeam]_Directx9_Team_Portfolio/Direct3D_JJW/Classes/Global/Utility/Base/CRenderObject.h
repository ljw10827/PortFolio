#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CObject.h"
#include "../Interface/IRenderable.h"


class CDebugDraw;

//! 렌더링 객체
class CRenderObject : public CObject,
					  public IRenderable
{

public:			// 인터페이스

	/*
	final 키워드는 자식 클래스에서 해당 함수를 오버라이드 할 수 없도록
	컴파일러에게 강제하는 기능이다.
	(즉, 해당 클래스를 상속하는 자식 클래스에서는 해당 함수 재정의가 불가능하다.)
	*/

	//! 화면에 그린다
	virtual void drawUI(void) override;

	//! 화면에 그린다
	virtual void draw(void) final override;

public:		// setter

	//! 디버그 여부를 변경한다
	void setDebugEnable(const bool isEnable, const EDebugType debugType = EDebugType::BOX);

	//! 디버그 여부를 반환한다
	bool getDebugEnable() { return _isDebugEnable; }

	//! 그림자 여부를 변경한다
	void setShadowEnable(const bool isShadowEnable);

	//! 그림자 재질을 변경한다
	void setShadowMaterial(const D3DMATERIAL9 &shadowMaterial);

	//! 그림자 행렬을 변경한다
	void setShadowMatrix(const D3DXMATRIXA16 &shadowMatrix);
	bool getVisible(void) { return m_bIsVisible; }
	void setVisible(bool isVisible) { m_bIsVisible = isVisible; }

protected:			// protected 함수

	//! 객체를 그릴 경우
	virtual void preDrawObject(void);

	//! 객체를 그린다
	virtual void doDrawObject(void);

	//! 객체를 그렸을 경우
	virtual void postDrawObject(void);

	//! 그림자를 그릴 경우
	virtual void preDrawShadow(void);

	//! 그림자를 그린다
	virtual void doDrawShadow(void);

	//! 그림자를 그렸을 경우
	virtual void postDrawShadow(void);

	//! 그림자 메시를 생성한다
	virtual LPD3DXMESH CreateShadowMesh(void);



public:			// 생성자

	//! 생성자
	explicit CRenderObject(void);

	//! 소멸자
	virtual ~CRenderObject(void);

protected:			// private 변수

	bool m_bIsVisible = false;
	bool _isDebugEnable = false;
	bool _isShadowEnable = false;

	CDebugDraw *_debugDraw = nullptr;
	LPD3DXMESH _shadowMesh = nullptr;

	D3DMATERIAL9 _shadowMaterial;
	D3DXMATRIXA16 _shadowMatrix;

	bool _isPlayer = false;
};
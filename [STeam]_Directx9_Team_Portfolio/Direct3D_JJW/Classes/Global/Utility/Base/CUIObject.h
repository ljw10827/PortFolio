#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CObject.h"
#include "../Interface/IRenderable.h"

//! UI 객체
class CUIObject : public CObject,
				  public IRenderable
{
public:			// 생성자

	//! 생성자
	explicit CUIObject(void);

public:			// 인터페이스 구현

	//! 화면에 그린다
	virtual void draw(void) final override;

	//! UI를 그린다
	virtual void drawUI(void) final override;

public:			// setter

	//! 색상을 변경한다
	void setColor(const D3DCOLOR color);

	//! 드로우 여부를 변경한다
	void setVisible(bool isVisible);

	bool getVisible();

protected:		// protected 함수

	//! UI를 그린다
	virtual void doDrawUI(void);

protected:			// private 변수

	bool _isVisible = false;
	D3DCOLOR _color;
};
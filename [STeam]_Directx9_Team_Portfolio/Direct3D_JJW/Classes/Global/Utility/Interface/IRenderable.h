#pragma once

#include "../../Define/KGlobalDefine.h"

//! 드로우 인터페이스
class IRenderable
{
public:			// 인터페이스

	//! 화면을 그린다
	virtual void draw(void) = 0;

	//! UI를 그린다
	virtual void drawUI(void) { }
};
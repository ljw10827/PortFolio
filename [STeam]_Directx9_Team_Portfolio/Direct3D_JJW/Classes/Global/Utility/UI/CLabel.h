#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CUIObject.h"

class CLabel : public CUIObject
{
public:			// getter & setter 

	//! 문자열을 변경한다
	void setString(const std::string &textString);

public:			// public 함수

	//! UI를 그린다
	virtual void doDrawUI(void) override;

public:			// 생성자, 소멸자

	//! 생성자
	explicit CLabel(const std::string &string, const int fontSize);

private:			// private 변수

	std::string _textString = "";
	int _fontSize = 0;

	LPD3DXFONT _font = nullptr;
	LPD3DXSPRITE _sprite = nullptr;

};
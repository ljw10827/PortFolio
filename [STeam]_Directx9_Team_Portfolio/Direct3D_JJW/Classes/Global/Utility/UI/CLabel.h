#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CUIObject.h"

class CLabel : public CUIObject
{
public:			// getter & setter 

	//! ���ڿ��� �����Ѵ�
	void setString(const std::string &textString);

public:			// public �Լ�

	//! UI�� �׸���
	virtual void doDrawUI(void) override;

public:			// ������, �Ҹ���

	//! ������
	explicit CLabel(const std::string &string, const int fontSize);

private:			// private ����

	std::string _textString = "";
	int _fontSize = 0;

	LPD3DXFONT _font = nullptr;
	LPD3DXSPRITE _sprite = nullptr;

};
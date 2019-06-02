#include "CLabel.h"
#include "../Manager/CDeviceManager.h"

CLabel::CLabel(const std::string & string, const int fontSize)
	:
	_textString(string),
	_fontSize(fontSize)
{
	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(fontDesc));

	fontDesc.Height = fontSize;
	fontDesc.Weight = 500;

	//��Ʈ�� �����Ѵ�
	/*D3DXCreateFontIndirect(GET_DEVICE(),
		&fontDesc,
		&_font);*/
	D3DXCreateFontA(GET_DEVICE(),
		_fontSize,
		0,
		FW_NORMAL,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		"THE��ǰ����",
		&_font);
}

void CLabel::setString(const std::string & textString)
{
	_textString = textString;
}

void CLabel::doDrawUI(void)
{
	RECT textRect = {
		(int)m_stPosition.x, (int)m_stPosition.y
	};
	
	// ���ڿ��� ũ�⸦ ����Ѵ�
	_font->DrawTextA(nullptr,
		_textString.c_str(),
		-1,
		&textRect,
		DT_TOP | DT_LEFT | DT_CALCRECT,
		_color);

	// ���ڿ��� �׸���
	_font->DrawTextA(nullptr,
		_textString.c_str(),
		-1,
		&textRect,
		DT_TOP | DT_LEFT,
		_color);
}

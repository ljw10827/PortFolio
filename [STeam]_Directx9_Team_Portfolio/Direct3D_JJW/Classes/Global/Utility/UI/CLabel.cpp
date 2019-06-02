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

	//폰트를 생성한다
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
		"THE명품굴림",
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
	
	// 문자열의 크기를 계산한다
	_font->DrawTextA(nullptr,
		_textString.c_str(),
		-1,
		&textRect,
		DT_TOP | DT_LEFT | DT_CALCRECT,
		_color);

	// 문자열을 그린다
	_font->DrawTextA(nullptr,
		_textString.c_str(),
		-1,
		&textRect,
		DT_TOP | DT_LEFT,
		_color);
}

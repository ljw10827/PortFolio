#include "CUIObject.h"

CUIObject::CUIObject(void)
	:
	_isVisible(true),
	_color(D3DCOLOR_XRGB(255, 255, 255))
{
	// Do Nothing
}

void CUIObject::draw(void)
{
	// Do Nothing
}

void CUIObject::drawUI(void)
{
	if (_isVisible) {
		this->doDrawUI();
	}

	// 자식 UI 객체를 그린다
	for (auto childObject : m_oChildObjectList) {
		auto uiObject = dynamic_cast<CUIObject *>(childObject);

		if (uiObject != nullptr) {
			uiObject->drawUI();
		}
	}
}

void CUIObject::setColor(const D3DCOLOR color)
{
	_color = color;
}

void CUIObject::setVisible(bool isVisible)
{
	_isVisible = isVisible;
}

bool CUIObject::getVisible()
{
	return _isVisible;
}

void CUIObject::doDrawUI(void)
{
	// Do Nothing
}

#pragma once

#include "../../Define/KGlobalDefine.h"

//! ��ο� �������̽�
class IRenderable
{
public:			// �������̽�

	//! ȭ���� �׸���
	virtual void draw(void) = 0;

	//! UI�� �׸���
	virtual void drawUI(void) { }
};
#pragma once

#include "../../Define/KGlobalDefine.h"

//! ������Ʈ �������̽�
class IUpdateable
{
public:			// �������̽�

	//! ���¸� �����Ѵ�
	virtual void update(void) = 0;
};
#pragma once

#include "../../Define/KGlobalDefine.h"

//! 업데이트 인터페이스
class IUpdateable
{
public:			// 인터페이스

	//! 상태를 갱신한다
	virtual void update(void) = 0;
};
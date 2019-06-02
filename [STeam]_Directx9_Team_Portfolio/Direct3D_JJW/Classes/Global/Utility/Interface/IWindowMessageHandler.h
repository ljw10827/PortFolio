#pragma once

#include "../../Define/KGlobalDefine.h"

//! 윈도우 메세지 처리자
class IWindowMessageHandler
{
public:			// 인터페이스

	//! 윈도우 메세지를 처리한다
	virtual LRESULT handleWindowMessage(HWND a_hWindow,
		UINT a_nMessage,
		WPARAM a_wParam,
		LPARAM a_lParam) = 0;
};

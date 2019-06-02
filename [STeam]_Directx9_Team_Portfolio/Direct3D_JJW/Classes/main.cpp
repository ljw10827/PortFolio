
//! 외부 라리브러리 추가
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "EffekseerRendererDX9.lib")
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "Quartz.lib")
#pragma comment(lib, "Strmbase.lib")

#include "Tera/TeraMain.h"

// 응용 프로그램 메인
int APIENTRY _tWinMain(HINSTANCE a_hInstance,
	HINSTANCE a_hPrevInstance,
	TCHAR *a_pszCommand,
	const int a_nOptions)
{

	SIZE stWindowSize = {
		1920, 1080
	};

	//Example_34 oApplication(a_hInstance, a_nOptions, stWindowSize);
	TeraMain oApplication(a_hInstance, a_nOptions, stWindowSize);
	return oApplication.runApplication();
}
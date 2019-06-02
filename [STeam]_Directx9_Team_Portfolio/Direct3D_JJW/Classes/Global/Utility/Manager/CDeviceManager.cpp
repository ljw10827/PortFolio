#include "CDeviceManager.h"
#include "CWindowManager.h"



CDeviceManager::~CDeviceManager(void)
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDirect3D);
}

void CDeviceManager::init(HWND a_hWindow, const SIZE a_stWindowSize)
{
	m_pDirect3D = this->createDirect3D();
	m_pDevice = this->createDevice(a_hWindow, a_stWindowSize);
}


LPDIRECT3D9 CDeviceManager::getDirect3D(void)
{
	return m_pDirect3D;
}

LPDIRECT3DDEVICE9 CDeviceManager::getDevice(void)
{
	return m_pDevice;
}


LPDIRECT3D9 CDeviceManager::createDirect3D(void)
{
	/*
	Direct3DCreate9의 함수 매개변수는 항상 D3D_SDK_VERSION로 고정이다.
	(즉, 변하지 않는다)
	*/
	return Direct3DCreate9(D3D_SDK_VERSION);
}

LPDIRECT3DDEVICE9 CDeviceManager::createDevice(HWND a_hWindow, const SIZE a_stWindowSize)
{
	/*
	D3DCAPS9 은 그래픽 카드의 정보를 나타낸다.
	(즉, 해당 구조체의 정보를 통해서 그래픽 카드의 가능한 연산의 유무를 확인할 수 있다)
	*/
	D3DCAPS9 stDeviceCaps;

	/*
	D3DADAPTER_DEFAULT 는 주 그래픽 카드를 의미함.
	
	그래픽 카드는 크게 2가지 방식으로 제어 가능하다.
	하나는 참조형식(Software방식),
	또 다른 하나는 hardware 방식으로 제어 가능.
	

	--- D3DDEVTYPE_REF ---

	참조 방식의 장점 :
	그래픽카드가 직접적으로 지원하지 않는 Direct3D9의 모든 기능을 사용가능하다.

	참조 방식의 단점 :
	모든 연산을 CPU가 처리하므로 퍼포먼스가 매우 많이 떨어진다.(즉, 교육용)


	--- D3DDEVTYPE_HAL ---

	하드웨어 방식의 장점 :
	그래픽 카드가 처리하므로 우수한 퍼포먼스를 자랑함.

	하드웨어 방식의 단점 :
	그래픽카드가 지원하지 않는 기능은 이용할 수 없다.
	(하지만 지금은 대부분의 기능을 지원하기 때문에 문제없다.
	오래된 그래픽카드가 아니라면 특별한 단점이 될 수 없다.)

	HAL(Hardware abstraction Layer) 하드웨어 추상 계층
	Direct3D에서 제공하는 기능을 모아둔 인터페이스의 개념이다.

	그리고 각 그래픽카드 제조사는 HAL 계층에 있는 인터페이스를 기반으로 내부적인 명령어를 구현한다.
	*/
	// 그래픽 카드의 정보를 가져온다
	m_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stDeviceCaps);

	// 연산들을 CPU에서 처리하겠다 == software
	int nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	
	/*
	버텍스 프로세싱은 정점 및 광원 연산을 CPU 또는 그래픽카드에서
	수행할 것인지를 나타낸다.

	software에서 처리하기 위한 플래그 : D3DCREATE_SOFTWARE_VERTEXPROCESSING
	hardware에서 처리하기 위한 플래그 : D3DCREATE_HARDWARE_VERTEXPROCESSING
	*/
	if (stDeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	/*
	BackBufferWidth : 백 버퍼의 너비
    BackBufferHeight : 백 버퍼의 높이
    BackBufferFormat : 색상의 포멧(픽셀의 포맷을 의미한다.)
    BackBufferCount : 백 버퍼의 갯수

    MultiSampleType : 샘플링을 하기 위한 횟수(다중으로 할 수 록 AA기술을 구현할 수 있다)
    MultiSampleQuality : 샘플링의 품질(높을수록 경계면이 부러워짐)

    SwapEffect : 백버퍼를 프레임버퍼로 출력하는 방식
    hDeviceWindow : 그림이 그려질 윈도우
    Windowed : 창모드 유무
    EnableAutoDepthStencil : 깊이버퍼와 스텐실버퍼를 자동으로 생성 할 것인가에 대한 유무
    AutoDepthStencilFormat : 깊이버퍼와 스텐실버퍼의 포멧
    Flags : 안쓰임

	FullScreen_RefreshRateInHz : 전체화면 일 때 화면의 갱신 비율
	PresentationInterval : 백버퍼의 교체 주기
	*/
	// 전체모드
	D3DPRESENT_PARAMETERS stParameters = {
		GET_WINDOW_SIZE().cx,
		GET_WINDOW_SIZE().cy,
		D3DFMT_A8R8G8B8,
		1,
		D3DMULTISAMPLE_NONE,
		0,
		D3DSWAPEFFECT_DISCARD,
		a_hWindow,
		true,
		true,
		D3DFMT_D24S8,
		0,
		D3DPRESENT_RATE_DEFAULT,
		D3DPRESENT_INTERVAL_IMMEDIATE
	};

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	// 디바이스를 생성한다
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		a_hWindow,
		nVertexProcessing,
		&stParameters,
		&pDevice);
	
	return pDevice;
}

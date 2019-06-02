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
	Direct3DCreate9�� �Լ� �Ű������� �׻� D3D_SDK_VERSION�� �����̴�.
	(��, ������ �ʴ´�)
	*/
	return Direct3DCreate9(D3D_SDK_VERSION);
}

LPDIRECT3DDEVICE9 CDeviceManager::createDevice(HWND a_hWindow, const SIZE a_stWindowSize)
{
	/*
	D3DCAPS9 �� �׷��� ī���� ������ ��Ÿ����.
	(��, �ش� ����ü�� ������ ���ؼ� �׷��� ī���� ������ ������ ������ Ȯ���� �� �ִ�)
	*/
	D3DCAPS9 stDeviceCaps;

	/*
	D3DADAPTER_DEFAULT �� �� �׷��� ī�带 �ǹ���.
	
	�׷��� ī��� ũ�� 2���� ������� ���� �����ϴ�.
	�ϳ��� ��������(Software���),
	�� �ٸ� �ϳ��� hardware ������� ���� ����.
	

	--- D3DDEVTYPE_REF ---

	���� ����� ���� :
	�׷���ī�尡 ���������� �������� �ʴ� Direct3D9�� ��� ����� ��밡���ϴ�.

	���� ����� ���� :
	��� ������ CPU�� ó���ϹǷ� �����ս��� �ſ� ���� ��������.(��, ������)


	--- D3DDEVTYPE_HAL ---

	�ϵ���� ����� ���� :
	�׷��� ī�尡 ó���ϹǷ� ����� �����ս��� �ڶ���.

	�ϵ���� ����� ���� :
	�׷���ī�尡 �������� �ʴ� ����� �̿��� �� ����.
	(������ ������ ��κ��� ����� �����ϱ� ������ ��������.
	������ �׷���ī�尡 �ƴ϶�� Ư���� ������ �� �� ����.)

	HAL(Hardware abstraction Layer) �ϵ���� �߻� ����
	Direct3D���� �����ϴ� ����� ��Ƶ� �������̽��� �����̴�.

	�׸��� �� �׷���ī�� ������� HAL ������ �ִ� �������̽��� ������� �������� ��ɾ �����Ѵ�.
	*/
	// �׷��� ī���� ������ �����´�
	m_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stDeviceCaps);

	// ������� CPU���� ó���ϰڴ� == software
	int nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	
	/*
	���ؽ� ���μ����� ���� �� ���� ������ CPU �Ǵ� �׷���ī�忡��
	������ �������� ��Ÿ����.

	software���� ó���ϱ� ���� �÷��� : D3DCREATE_SOFTWARE_VERTEXPROCESSING
	hardware���� ó���ϱ� ���� �÷��� : D3DCREATE_HARDWARE_VERTEXPROCESSING
	*/
	if (stDeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	/*
	BackBufferWidth : �� ������ �ʺ�
    BackBufferHeight : �� ������ ����
    BackBufferFormat : ������ ����(�ȼ��� ������ �ǹ��Ѵ�.)
    BackBufferCount : �� ������ ����

    MultiSampleType : ���ø��� �ϱ� ���� Ƚ��(�������� �� �� �� AA����� ������ �� �ִ�)
    MultiSampleQuality : ���ø��� ǰ��(�������� ������ �η�����)

    SwapEffect : ����۸� �����ӹ��۷� ����ϴ� ���
    hDeviceWindow : �׸��� �׷��� ������
    Windowed : â��� ����
    EnableAutoDepthStencil : ���̹��ۿ� ���ٽǹ��۸� �ڵ����� ���� �� ���ΰ��� ���� ����
    AutoDepthStencilFormat : ���̹��ۿ� ���ٽǹ����� ����
    Flags : �Ⱦ���

	FullScreen_RefreshRateInHz : ��üȭ�� �� �� ȭ���� ���� ����
	PresentationInterval : ������� ��ü �ֱ�
	*/
	// ��ü���
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

	// ����̽��� �����Ѵ�
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		a_hWindow,
		nVertexProcessing,
		&stParameters,
		&pDevice);
	
	return pDevice;
}

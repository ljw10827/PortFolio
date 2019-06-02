#include "CInputManager.h"
#include "CWindowManager.h"


void CInputManager::init(void)
{
	ZeroMemory(m_anKeyboardState, sizeof(m_anKeyboardState));
	ZeroMemory(m_anPrevKeyboardState, sizeof(m_anPrevKeyboardState));

	ZeroMemory(&m_stMouseState, sizeof(m_stMouseState));
	ZeroMemory(&m_stPrevMouseState, sizeof(m_stPrevMouseState));

	m_pDirectInput = this->createDirectInput();
	m_pKeyboardDevice = this->createKeyboardDevice();
	m_pMouseDevcie = this->createMouseDevice();
}

bool CInputManager::isKeyDown(const int a_nKeyCode)
{
	return m_anKeyboardState[a_nKeyCode] & 0x80;
}

bool CInputManager::isKeyPressed(const int a_nKeyCode)
{
	return !(m_anPrevKeyboardState[a_nKeyCode] & 0x80) &&
		(m_anKeyboardState[a_nKeyCode] & 0x80);
}

bool CInputManager::isKeyReleased(const int a_nKeyCode)
{
	return (m_anPrevKeyboardState[a_nKeyCode] & 0x80) &&
		!(m_anKeyboardState[a_nKeyCode] & 0x80);
}

/*
마우스 버튼 인덱스
왼쪽 클릭 : 0
오른쪽 클릭 : 1
중앙 클릭 : 2
*/
bool CInputManager::isMouseDown(const int a_nButtonIndex)
{
	return m_stMouseState.rgbButtons[a_nButtonIndex] & 0x80;
}

bool CInputManager::isMousePressed(const int a_nButtonIndex)
{
	return !(m_stPrevMouseState.rgbButtons[a_nButtonIndex] & 0x80) &&
		(m_stMouseState.rgbButtons[a_nButtonIndex] & 0x80);
}

bool CInputManager::isMouseRelease(const int a_nButtonIndex)
{
	return (m_stPrevMouseState.rgbButtons[a_nButtonIndex] & 0x80) &&
		!(m_stMouseState.rgbButtons[a_nButtonIndex] & 0x80);
}

void CInputManager::update(void)
{
	CopyMemory(m_anPrevKeyboardState, m_anKeyboardState, sizeof(m_anKeyboardState));
	CopyMemory(&m_stPrevMouseState, &m_stMouseState, sizeof(m_stMouseState));

	m_pKeyboardDevice->GetDeviceState(sizeof(m_anKeyboardState), m_anKeyboardState);
	m_pMouseDevcie->GetDeviceState(sizeof(m_stMouseState), &m_stMouseState);
}

int CInputManager::getMouseWheel(void)
{
	return m_stMouseState.lZ;
}

POINT CInputManager::getMousePosition(void)
{
	POINT stMousePosition;
	GetCursorPos(&stMousePosition);

	ScreenToClient(GET_WINDOW_HANDLE(), &stMousePosition);

	return stMousePosition;
}

LPDIRECTINPUT8 CInputManager::createDirectInput(void)
{
	LPDIRECTINPUT8 pDirectInput = nullptr;
	DirectInput8Create(GET_INSTANCE_HANDLE(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&pDirectInput, nullptr);

	return pDirectInput;
}

LPDIRECTINPUTDEVICE8 CInputManager::createKeyboardDevice(void)
{
	LPDIRECTINPUTDEVICE8 pKeyboardDevice = nullptr;
	m_pDirectInput->CreateDevice(GUID_SysKeyboard, &pKeyboardDevice, nullptr);

	pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	pKeyboardDevice->SetCooperativeLevel(GET_WINDOW_HANDLE(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	pKeyboardDevice->Acquire();

	return pKeyboardDevice;
}

LPDIRECTINPUTDEVICE8 CInputManager::createMouseDevice(void)
{
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	m_pDirectInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);

	pMouseDevice->SetDataFormat(&c_dfDIMouse);
	pMouseDevice->SetCooperativeLevel(GET_WINDOW_HANDLE(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	pMouseDevice->Acquire();

	return pMouseDevice;
}

CInputManager::~CInputManager(void)
{
	SAFE_UNACQUIRE(m_pMouseDevcie);
	SAFE_UNACQUIRE(m_pKeyboardDevice);

	SAFE_RELEASE(m_pDirectInput);
}

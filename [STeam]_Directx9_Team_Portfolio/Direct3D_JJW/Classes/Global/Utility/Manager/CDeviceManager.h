#pragma once

#include "../../Define/KGlobalDefine.h"

/*
다이렉트 3D는 메모리 관리 방식으로 참조 카운팅 방식을 채택하고 있다
참조 카운트를 증가시킬때는 AddRef 함수,
참조 카운트를 감소시킬때는 Release 함수를 이용하면 된다
(쯕, 직접적으로 delete를 호출시키는 것은 금지되어있다)

IUnknown 인터페이스를 상속하는 모든 클래스는 해당 방식의 메모리 관리 규칙을
따라야한다 (iUnknown 인터페이스를 상속하는 클래스는 접두어가 I로 시작한다)

AddRef 함수가 호출되는 순간은 IUnknown 인터페이스를 상속한 클래스를 Get함수로 가져올때이다
(즉, Get 함수를 통해 객체를 가져왓다면 필히 Release 함수를 호출해 주어야한다)
*/

//! 디바이스 관리자
class CDeviceManager
{
public:				// 게터

	//! 다이렉트 3D를 반환한다
	LPDIRECT3D9 getDirect3D(void);

	//! 디바이스를 반환한다
	LPDIRECT3DDEVICE9 getDevice(void);

public:				// public 함수

	//! 싱글턴
	DECLARE_SINGLETON(CDeviceManager);

	//! 초기화
	virtual void init(HWND a_hWindow,
		const SIZE a_stWindowSize);

private:			// private 함수

	/*
	Direct3D는 그래픽 카드의 물리적인 정보를 취득하는데 사용된다.
	(보통 Device를 생성하기 전까지만 이용이 되고, 이후에는 잘 사용되지 않는다)
	*/
	//! 다이렉트 3D를 생성한다
	LPDIRECT3D9 createDirect3D(void);


	/*
	Direct3D Device는 실제적인 그래픽 카드를 제어하는 클래스이다.
	(즉, Device를 통해서 3차원 물체 등의 렌더링을 나타낸다)
	*/
	//! 디바이스를 생성한다
	LPDIRECT3DDEVICE9 createDevice(HWND a_hWindow,
		const SIZE a_stWindowSize);

private:			// 소멸자

	//! 소멸자
	virtual ~CDeviceManager(void);

private:			// private 변수

	LPDIRECT3D9 m_pDirect3D = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
};
#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

//! Example 15
class IntroScene;

class TeraMain : public CDirect3DApplication
{
public:			// 생성자

				//! 생성자
	explicit TeraMain(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize);

	virtual ~TeraMain(void);

public:			// public 함수

				//! 어플리케이션을 초기화한다
	virtual void initApplication(void) override;

	//! 상태를 갱신한다
	virtual void update(void) override;

	//! 화면을 그린다
	virtual void draw(void) override;

private:

	IntroScene * _scene = nullptr;

};

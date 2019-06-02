#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

//! Example 15
class IntroScene;

class TeraMain : public CDirect3DApplication
{
public:			// ������

				//! ������
	explicit TeraMain(HINSTANCE a_hInstance,
		const int a_nOptions,
		const SIZE a_stWindowSize);

	virtual ~TeraMain(void);

public:			// public �Լ�

				//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ȭ���� �׸���
	virtual void draw(void) override;

private:

	IntroScene * _scene = nullptr;

};

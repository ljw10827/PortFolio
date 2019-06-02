#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CObject.h"
#include "../Interface/IRenderable.h"

//! UI ��ü
class CUIObject : public CObject,
				  public IRenderable
{
public:			// ������

	//! ������
	explicit CUIObject(void);

public:			// �������̽� ����

	//! ȭ�鿡 �׸���
	virtual void draw(void) final override;

	//! UI�� �׸���
	virtual void drawUI(void) final override;

public:			// setter

	//! ������ �����Ѵ�
	void setColor(const D3DCOLOR color);

	//! ��ο� ���θ� �����Ѵ�
	void setVisible(bool isVisible);

	bool getVisible();

protected:		// protected �Լ�

	//! UI�� �׸���
	virtual void doDrawUI(void);

protected:			// private ����

	bool _isVisible = false;
	D3DCOLOR _color;
};
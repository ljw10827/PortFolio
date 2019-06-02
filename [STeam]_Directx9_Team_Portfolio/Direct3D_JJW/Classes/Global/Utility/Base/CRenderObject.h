#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CObject.h"
#include "../Interface/IRenderable.h"


class CDebugDraw;

//! ������ ��ü
class CRenderObject : public CObject,
					  public IRenderable
{

public:			// �������̽�

	/*
	final Ű����� �ڽ� Ŭ�������� �ش� �Լ��� �������̵� �� �� ������
	�����Ϸ����� �����ϴ� ����̴�.
	(��, �ش� Ŭ������ ����ϴ� �ڽ� Ŭ���������� �ش� �Լ� �����ǰ� �Ұ����ϴ�.)
	*/

	//! ȭ�鿡 �׸���
	virtual void drawUI(void) override;

	//! ȭ�鿡 �׸���
	virtual void draw(void) final override;

public:		// setter

	//! ����� ���θ� �����Ѵ�
	void setDebugEnable(const bool isEnable, const EDebugType debugType = EDebugType::BOX);

	//! ����� ���θ� ��ȯ�Ѵ�
	bool getDebugEnable() { return _isDebugEnable; }

	//! �׸��� ���θ� �����Ѵ�
	void setShadowEnable(const bool isShadowEnable);

	//! �׸��� ������ �����Ѵ�
	void setShadowMaterial(const D3DMATERIAL9 &shadowMaterial);

	//! �׸��� ����� �����Ѵ�
	void setShadowMatrix(const D3DXMATRIXA16 &shadowMatrix);
	bool getVisible(void) { return m_bIsVisible; }
	void setVisible(bool isVisible) { m_bIsVisible = isVisible; }

protected:			// protected �Լ�

	//! ��ü�� �׸� ���
	virtual void preDrawObject(void);

	//! ��ü�� �׸���
	virtual void doDrawObject(void);

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void);

	//! �׸��ڸ� �׸� ���
	virtual void preDrawShadow(void);

	//! �׸��ڸ� �׸���
	virtual void doDrawShadow(void);

	//! �׸��ڸ� �׷��� ���
	virtual void postDrawShadow(void);

	//! �׸��� �޽ø� �����Ѵ�
	virtual LPD3DXMESH CreateShadowMesh(void);



public:			// ������

	//! ������
	explicit CRenderObject(void);

	//! �Ҹ���
	virtual ~CRenderObject(void);

protected:			// private ����

	bool m_bIsVisible = false;
	bool _isDebugEnable = false;
	bool _isShadowEnable = false;

	CDebugDraw *_debugDraw = nullptr;
	LPD3DXMESH _shadowMesh = nullptr;

	D3DMATERIAL9 _shadowMaterial;
	D3DXMATRIXA16 _shadowMatrix;

	bool _isPlayer = false;
};
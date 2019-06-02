#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

class CGrid : public CRenderObject
{

public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};

		D3DXVECTOR3 m_stPosition;
		D3DCOLOR m_nColor;
	};

public:			// public �Լ�

	//! ��ü�� �׸� ���
	virtual void preDrawObject(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void) override;

public:			// ������ & �Ҹ���

	//! ������
	explicit CGrid(const int a_nSize);

	//! �Ҹ���
	virtual ~CGrid(void);

private:		// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

private:		// private ����

	int m_nSize = 0;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
};
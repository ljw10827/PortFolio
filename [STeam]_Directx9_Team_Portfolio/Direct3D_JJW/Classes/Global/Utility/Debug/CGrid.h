#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

class CGrid : public CRenderObject
{

public:

	//! 정점
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};

		D3DXVECTOR3 m_stPosition;
		D3DCOLOR m_nColor;
	};

public:			// public 함수

	//! 객체를 그릴 경우
	virtual void preDrawObject(void) override;

	//! 객체를 그린다
	virtual void doDrawObject(void) override;

	//! 객체를 그렸을 경우
	virtual void postDrawObject(void) override;

public:			// 생성자 & 소멸자

	//! 생성자
	explicit CGrid(const int a_nSize);

	//! 소멸자
	virtual ~CGrid(void);

private:		// private 함수

	//! 정점 버퍼를 생성한다
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

private:		// private 변수

	int m_nSize = 0;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
};
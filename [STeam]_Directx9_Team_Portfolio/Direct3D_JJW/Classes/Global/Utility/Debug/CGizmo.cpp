#include "CGizmo.h"
#include "../Manager/CDeviceManager.h"

CGizmo::CGizmo(const int a_nSize)
	:
	m_nSize(a_nSize)
{
	m_pVertexBuffer = this->createVertexBuffer();
}

CGizmo::~CGizmo(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
}


void CGizmo::preDrawObject(void)
{
	CRenderObject::preDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);
}

void CGizmo::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	auto stWorldMatrix = this->getWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetFVF(STVertex::FVF);

	GET_DEVICE()->DrawPrimitive(D3DPT_LINELIST, 0, 9);
}

void CGizmo::postDrawObject(void)
{
	CRenderObject::postDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 CGizmo::createVertexBuffer(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = nullptr;

	// 정점 버퍼를 생성한다
	GET_DEVICE()->CreateVertexBuffer(sizeof(STVertex) * 18,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED,
		&pVertexBuffer,
		nullptr);

	// 정점 정보를 설정한다
	// {
	STVertex *pstVertices = nullptr;

	if (SUCCEEDED(pVertexBuffer->Lock(0, 0, (void **)&pstVertices, 0))) {
		// X 축
		pstVertices[0].m_stPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pstVertices[1].m_stPosition = D3DXVECTOR3(m_nSize, 0.0f, 0.0f);

		pstVertices[2].m_stPosition = D3DXVECTOR3(m_nSize - 1.0f, 0.0f, 1.0f);
		pstVertices[3].m_stPosition = D3DXVECTOR3(m_nSize, 0.0f, 0.0f);

		pstVertices[4].m_stPosition = D3DXVECTOR3(m_nSize - 1.0f, 0.0f, -1.0f);
		pstVertices[5].m_stPosition = D3DXVECTOR3(m_nSize, 0.0f, 0.0f);

		pstVertices[0].m_nColor = D3DCOLOR_XRGB(255, 0, 0);
		pstVertices[1].m_nColor = D3DCOLOR_XRGB(255, 0, 0);
		pstVertices[2].m_nColor = D3DCOLOR_XRGB(255, 0, 0);
		pstVertices[3].m_nColor = D3DCOLOR_XRGB(255, 0, 0);
		pstVertices[4].m_nColor = D3DCOLOR_XRGB(255, 0, 0);
		pstVertices[5].m_nColor = D3DCOLOR_XRGB(255, 0, 0);

		// Y 축
		pstVertices[6].m_stPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pstVertices[7].m_stPosition = D3DXVECTOR3(0.0f, m_nSize, 0.0f);

		pstVertices[8].m_stPosition = D3DXVECTOR3(-1.0f, m_nSize - 1, 0.0f);
		pstVertices[9].m_stPosition = D3DXVECTOR3(0.0f, m_nSize, 0.0f);

		pstVertices[10].m_stPosition = D3DXVECTOR3(1.0f, m_nSize - 1.0f, -0.0f);
		pstVertices[11].m_stPosition = D3DXVECTOR3(0.0f, m_nSize, 0.0f);

		pstVertices[6].m_nColor = D3DCOLOR_XRGB(0, 255, 0);
		pstVertices[7].m_nColor = D3DCOLOR_XRGB(0, 255, 0);
		pstVertices[8].m_nColor = D3DCOLOR_XRGB(0, 255, 0);
		pstVertices[9].m_nColor = D3DCOLOR_XRGB(0, 255, 0);
		pstVertices[10].m_nColor = D3DCOLOR_XRGB(0, 255, 0);
		pstVertices[11].m_nColor = D3DCOLOR_XRGB(0, 255, 0);


		// Z 축
		pstVertices[12].m_stPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pstVertices[13].m_stPosition = D3DXVECTOR3(0.0f, 0.0f, m_nSize);

		pstVertices[14].m_stPosition = D3DXVECTOR3(-1.0f, 0.0f, m_nSize - 1.0f);
		pstVertices[15].m_stPosition = D3DXVECTOR3(0.0f, 0.0f, m_nSize);

		pstVertices[16].m_stPosition = D3DXVECTOR3(1.0f, 0.0f, m_nSize -1.0f);
		pstVertices[17].m_stPosition = D3DXVECTOR3(0.0f, 0.0f, m_nSize);

		pstVertices[12].m_nColor = D3DCOLOR_XRGB(0, 0, 255);
		pstVertices[13].m_nColor = D3DCOLOR_XRGB(0, 0, 255);
		pstVertices[14].m_nColor = D3DCOLOR_XRGB(0, 0, 255);
		pstVertices[15].m_nColor = D3DCOLOR_XRGB(0, 0, 255);
		pstVertices[16].m_nColor = D3DCOLOR_XRGB(0, 0, 255);
		pstVertices[17].m_nColor = D3DCOLOR_XRGB(0, 0, 255);

		pVertexBuffer->Unlock();
	}
	// }


	return pVertexBuffer;
}

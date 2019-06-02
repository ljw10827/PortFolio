#include "CGrid.h"
#include "../Manager/CDeviceManager.h"

CGrid::CGrid(const int a_nSize)
	:
	m_nSize(a_nSize)
{
	m_pVertexBuffer = this->createVertexBuffer();
}

CGrid::~CGrid(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
}

void CGrid::preDrawObject(void)
{
	CRenderObject::preDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);
}

void CGrid::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	auto stWorldMatrix = this->getWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetFVF(STVertex::FVF);

	GET_DEVICE()->DrawPrimitive(D3DPT_LINELIST, 0, (m_nSize + 1) * 2);
}

void CGrid::postDrawObject(void)
{
	CRenderObject::postDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}


LPDIRECT3DVERTEXBUFFER9 CGrid::createVertexBuffer(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = nullptr;

	// 정점 버퍼를 생성한다
	GET_DEVICE()->CreateVertexBuffer(sizeof(STVertex) * (m_nSize + 1) * 4,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED,
		&pVertexBuffer,
		nullptr);

	// 정점 정보를 설정한다
	// {
	STVertex *pstVertices = nullptr;

	if (SUCCEEDED(pVertexBuffer->Lock(0, 0, (void **)&pstVertices, 0))) {

		D3DXVECTOR3 stBasePosition(m_nSize / -2.0f, 0.0f, m_nSize / 2.0f);

		for (int i = 0; i <= m_nSize; ++i) {
			int nIndex = i * 4;

			// 가로
			pstVertices[nIndex + 0].m_stPosition = stBasePosition + D3DXVECTOR3(0.0f, 0.0f, -i);
			pstVertices[nIndex + 1].m_stPosition = stBasePosition + D3DXVECTOR3(m_nSize, 0.0f, -i);

			// 세로
			pstVertices[nIndex + 2].m_stPosition = stBasePosition + D3DXVECTOR3(i, 0.0f, 0.0f);
			pstVertices[nIndex + 3].m_stPosition = stBasePosition + D3DXVECTOR3(i, 0.0f, -m_nSize);

			D3DCOLOR nColor = (i % 5 == 0) ? D3DCOLOR_XRGB(200, 200, 200) : nColor = D3DCOLOR_XRGB(80, 80, 80);

			pstVertices[nIndex + 0].m_nColor = nColor;
			pstVertices[nIndex + 1].m_nColor = nColor;
			pstVertices[nIndex + 2].m_nColor = nColor;
			pstVertices[nIndex + 3].m_nColor = nColor;
		}

		pVertexBuffer->Unlock();
	}
	// }


	return pVertexBuffer;
}

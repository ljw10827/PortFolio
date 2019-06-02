#include "CStaticMesh_AlphaControl.h"
#include "../../Global/Utility/Manager/CResourceManager.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Object/CCamera.h"
#include "../../Global/Utility/Object/CLight.h"


#define STATIC_MESH_TYPE_DEVICE 1
#define STATIC_MESH_TYPE_EFFECT 2

#define STATIC_MESH_TYPE        STATIC_MESH_TYPE_EFFECT

CStaticMesh_AlphaControl::CStaticMesh_AlphaControl(const STParameters & a_rParameters, float Alpha)
{
	// �޽õ� �ϳ� �����ϰ� �ٸ����� �� �� �ֱ⿡ ���ҽ� �Ŵ����� �����.

	m_stStaticMesh = GET_STATIC_MESH(a_rParameters.m_oMeshFileName);
	m_pEffect = GET_EFFECT(a_rParameters.m_oEffectFileName);

	m_fAlpha = Alpha;
}

void CStaticMesh_AlphaControl::doDrawObject(void)
{
	CRenderObject::doDrawObject();

#if(STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE )

	auto stWorldMatrix = this->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	for (int i = 0; i < m_stStaticMesh.m_nNumMaterials; ++i)
	{
		GET_DEVICE()->SetMaterial(&m_stStaticMesh.m_oMaterialist[i]);
		GET_DEVICE()->SetTexture(0, m_stStaticMesh.m_oTexturlist[i]);

		m_stStaticMesh.m_pMesh->DrawSubset(i);

		// �׻� �ؽ��� ����� ������ nullptr�� �ִ´�. �̰��� ����̽��� �����̴�.
		GET_DEVICE()->SetTexture(0, nullptr);
	}

#else

	D3DXMATRIXA16 stWorldMatrix = this->getFinalWorldMatrix(); // �̷��� �ϴ� �� �� ��������
	D3DXMATRIXA16 stViewMatrix = GET_CAMERA()->getViewMatrix();
	D3DXMATRIXA16 stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix); // ���� ��� ����
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix); // �� ��� ����
	m_pEffect->SetMatrix("g_stPrijectionMatrix", &stProjectionMatrix); // ���� ��� ����


	D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f); // ���� ���� ����
	m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

	D3DXVECTOR4 stViewPosition(GET_CAMERA()->getPosition(), 1.0f);
	m_pEffect->SetVector("g_stViewPosition", &stViewPosition);

	m_pEffect->SetFloat("g_fAlgha", m_fAlpha);

	// 2�ܰ� ��ũ�� ���
	m_pEffect->SetTechnique("Example_24_AlphaControl");

	// 3�ܰ� Begin�Լ�
	UINT nNumber = 0;
	m_pEffect->Begin(/*��ũ�� �ȿ� �ִ� ��ũ�е�*/ &nNumber, 0); // �̷��� �ϸ� �н��� ������ ����.

	for (int i = 0; i < nNumber; ++i)
	{
		m_pEffect->BeginPass(i);

		for (int j = 0; j < m_stStaticMesh.numMaterials; ++j)
		{
			m_pEffect->SetTexture("g_pTexture", m_stStaticMesh.textureList[j]);

			m_pEffect->CommitChanges();

			m_stStaticMesh.mesh->DrawSubset(j);

		}

		m_pEffect->EndPass();
	}
	m_pEffect->End();

#endif
}

void CStaticMesh_AlphaControl::preDrawObject(void)
{
	CRenderObject::preDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GET_DEVICE()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CStaticMesh_AlphaControl::postDrawObject(void)
{
	CRenderObject::postDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

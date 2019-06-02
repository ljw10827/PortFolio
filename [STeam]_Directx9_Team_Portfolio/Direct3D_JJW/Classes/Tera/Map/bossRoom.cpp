#include "bossRoom.h"

#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Utility/Manager/CResourceManager.h"
#include "../../Global/Utility/Object/CCamera.h"
			
#include "../../Global/Utility/Object/CSkinnedMesh.h"
#include "../StaticMesh/CStaticMesh_AlphaControl.h"

#include "../StaticMesh/CStaticMesh_Boss.h"


bossRoom::bossRoom(void)
{
}

bossRoom::~bossRoom(void)
{
}


void bossRoom::init(void)
{
	CTeraMap::init();
	m_pSphere = createSphere();
	m_pEffect = GET_EFFECT("Resources/Effects/BossRoom.fx");
	m_pCubeTexture = GET_CUBE_TEXTURE("Resources/MapResources/skyBox/temple/Texture1.dds");

	m_pStaticTemple[0] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/1/temple1.x");
	m_pStaticTemple[0]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticTemple[0]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStaticTemple[1] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/1/temple1.x");
	m_pStaticTemple[1]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticTemple[1]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStaticTemple[1]->rotateByYAxis(180);

	m_pStaticTemple[2] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/2/temple2.x");
	m_pStaticTemple[2]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticTemple[2]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStaticTemple[3] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/2/temple2.x");
	m_pStaticTemple[3]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticTemple[3]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStaticTemple[3]->rotateByYAxis(180);

	m_pStaticFloor = this->createStaticMeshMapAlpha("Resources/MapResources/bossRoom/floor/5/floor5.x");
	m_pStaticFloor->setPosition(D3DXVECTOR3(0.0f, -8.0f, 0.0f));
	m_pStaticFloor->setScale(D3DXVECTOR3(20.0f, 20.0f, 20.0f));

}

void bossRoom::update(void)
{
	CTeraMap::update();
	for (int i = 0; i < 4; ++i)
	{
		m_pStaticTemple[i]->update();
	}

	m_pStaticFloor->update();

	//m_pSinnedMeshFloor->update();
}

void bossRoom::doDrawObject(void)
{
	CTeraMap::doDrawObject();
	this->skyBoxDraw();

	for (int i = 0; i < 4; ++i)
	{
		m_pStaticTemple[i]->draw();
	}
	m_pStaticFloor->draw();

}

void bossRoom::skyBoxDraw(void)
{
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixIdentity(&stWorldMatrix);
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	D3DXMATRIXA16 stViewMatrix = GET_CAMERA()->getViewMatrix();
	D3DXMATRIXA16 stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);
	m_pEffect->SetTexture("g_CubeTexture", m_pCubeTexture);
	m_pEffect->SetTechnique("MyTechnique");

	UINT nNumger = 0;
	m_pEffect->Begin(&nNumger, 0);

	for (int i = 0; i < nNumger; ++i)
	{
		m_pEffect->BeginPass(i);

		m_pSphere->DrawSubset(0);

		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

LPD3DXMESH bossRoom::createSphere(void)
{
	LPD3DXMESH p_Mesh = nullptr;
	LPD3DXBUFFER pAdj = nullptr;

	D3DXCreateSphere(GET_DEVICE(), 700, 100, 100, &p_Mesh, &pAdj);

	// 법선 계산!
	D3DXComputeNormals(p_Mesh, (DWORD*)pAdj->GetBufferPointer());

	return p_Mesh;
}

CStaticMeshBoss * bossRoom::createStaticMeshMap(std::string Filepath)
{
	CStaticMeshBoss::STParameters stParameters = {
		Filepath,
		"Resources/Effects/bossRoomStaticMesh.fx"
	};

	return new CStaticMeshBoss(stParameters);
}

CStaticMesh_AlphaControl * bossRoom::createStaticMeshMapAlpha(std::string Filepath)
{
	CStaticMesh_AlphaControl::STParameters stParameters = {
	Filepath,
	"Resources/Effects/bossRoomStaticMesh_AlphaControl.fx"
	};

	return new CStaticMesh_AlphaControl(stParameters, 0.6);
}



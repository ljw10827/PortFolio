#include "filedMap.h"

#include "../../Global/Function/GlobalFunction.h"

#include "../../Global/Utility/Manager/CResourceManager.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Utility/Manager/CInputManager.h"

#include "../../Global/Utility/Base/CDirect3DApplication.h"

#include "../../Global/Utility/Object/CTerrain.h"
#include "../../Global/Utility/Object/CCamera.h"

#include "../StaticMesh/CStaticMesh_Map.h"

filedMap::filedMap()
{
}

filedMap::~filedMap(void)
{
}

float filedMap::getHeightMapY(const D3DXVECTOR3 & _vec)
{
	return m_pTerrain->getTerrainHeightAtPosition(_vec) + m_pTerrainPositionY;
}

void filedMap::init(void)
{
	m_pSphere = createSphere();
	m_pEffect = GET_EFFECT("Resources/MapResources/Example_27.fx");
	m_pCubeTexture = GET_CUBE_TEXTURE("Resources/MapResources/skyBOX/skyBOX2/Texture.dds");

	// -210가 없으면 너무 위에 가 있다.
	m_pTerrainPositionY = -210;

	m_pTerrain = this->createTerrain();
	m_pTerrain->setPosition(D3DXVECTOR3(0.0f, m_pTerrainPositionY, 0.0f));

	this->ObjectPosition();
	this->treePosition();
	this->templePosition();

}


void filedMap::update(void)
{
	CTeraMap::update();
	m_pTerrain->update();

	if (IS_KEY_PRESSED(DIK_1))
	{
		if (bIsDebugMode)
		{
			bIsDebugMode = false;
		}
		else
		{
			bIsDebugMode = true;
		}
	}

	
	m_pStaticMeshHouse1->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshHouse2->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshHouse3->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshHouse4->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshHouse5->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshStraw->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshStrawCar->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	for (int i = 0; i < NumberOfStrawPuppet; ++i){m_pStaticMeshStrawPuppet[i]->setDebugEnable(bIsDebugMode, EDebugType::BOX);}
	for (int i = 0; i < NumberOfFence1; ++i){m_pStaticMeshFence1[i]->setDebugEnable(bIsDebugMode, EDebugType::BOX);}
	for (int i = 0; i < NumberOfFence2; ++i){m_pStaticMeshFence2[i]->setDebugEnable(bIsDebugMode, EDebugType::BOX);}
	for (int i = 0; i < NumberOfFence3; ++i){m_pStaticMeshFence3[i]->setDebugEnable(bIsDebugMode, EDebugType::BOX);}
	m_pStaticMeshRuin[0]->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshRuin[1]->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshRuin[2]->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshRuin[3]->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	m_pStaticMeshRuin[4]->setDebugEnable(bIsDebugMode, EDebugType::BOX);
	for (int i = 0; i < NumberOfBuin; ++i)
	{
		auto stCoord = m_pStaticMeshRuin[i]->getPosition();
		stCoord.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshRuin[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshRuin[i]->setPosition(stCoord);
	}
	for (int i = 0; i < NumberOfTree1; ++i){m_pStaticMeshTree1[i]->setDebugEnable(bIsDebugMode, EDebugType::SPHERE);}
	for (int i = 0; i < NumberOfTree2; ++i){m_pStaticMeshTree2[i]->setDebugEnable(bIsDebugMode, EDebugType::SPHERE);}
	for (int i = 0; i < NumberOfTree3; ++i){m_pStaticMeshTree3[i]->setDebugEnable(bIsDebugMode, EDebugType::SPHERE);}
	for (int i = 0; i < NumberOfTreeBoss; ++i){m_pStaticMeshTreeBoss[i]->setDebugEnable(bIsDebugMode, EDebugType::SPHERE);}
	for (int i = 0; i < NumberOfTreeBossDestroy1; ++i){m_pStaticMeshTreeBossDestroy1[i]->setDebugEnable(bIsDebugMode, EDebugType::SPHERE);}
	for (int i = 0; i < NumberOfTreeBossDestroy2; ++i){m_pStaticMeshTreeBossDestroy2[i]->setDebugEnable(bIsDebugMode, EDebugType::SPHERE);}
	m_pStaticMeshHouse1->update();
	m_pStaticMeshHouse2->update();
	m_pStaticMeshHouse3->update();
	m_pStaticMeshHouse4->update();
	m_pStaticMeshHouse5->update();

	m_pStaticMeshStrawCar->update();
	m_pStaticMeshStraw->update();

	for (int i = 0; i < NumberOfStrawPuppet; i++){m_pStaticMeshStrawPuppet[i]->update();}
	for (int i = 0; i < NumberOfFence1; ++i){m_pStaticMeshFence1[i]->update();}
	for (int i = 0; i < NumberOfFence2; ++i){m_pStaticMeshFence2[i]->update();}
	for (int i = 0; i < NumberOfFence3; ++i){m_pStaticMeshFence3[i]->update();}
	for (int i = 0; i < NumberOfLeftWallBush; ++i){m_pStaticMeshLeftWallBush[i]->update();}
	for (int i = 0; i < NumberOfTopWallBush; ++i){m_pStaticMeshTopWallBush[i]->update();}
	for (int i = 0; i < NumberOfRIghtWallBush; ++i){m_pStaticMeshRIghtWallBush[i]->update();}
	for (int i = 0; i < NumberOfBottomWallBush; ++i){m_pStaticMeshBottomWallBush[i]->update();}
	for (int i = 0; i < NumberOfRIghtBottomEdgeBush; ++i){m_pStaticMeshRIghtBottomEdgeBush[i]->update();}
	for (int i = 0; i < NumberOfTree1; ++i){m_pStaticMeshTree1[i]->update();}
	for (int i = 0; i < NumberOfTree2; ++i){m_pStaticMeshTree2[i]->update();}
	for (int i = 0; i < NumberOfTree3; ++i){m_pStaticMeshTree3[i]->update();}
	for (int i = 0; i < NumberOfTreeBoss; ++i){m_pStaticMeshTreeBoss[i]->update();}
	for (int i = 0; i < NumberOfTreeBossDestroy1; ++i){m_pStaticMeshTreeBossDestroy1[i]->update();}
	for (int i = 0; i < NumberOfTreeBossDestroy2; ++i){m_pStaticMeshTreeBossDestroy2[i]->update();}
	for (int i = 0; i < NumberOfBuin; ++i){m_pStaticMeshRuin[i]->update();}

}

void filedMap::doDrawObject(void)
{
	CTeraMap::doDrawObject();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);
	GET_DEVICE()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	this->skyBoxDraw();

	m_pTerrain->draw();

	m_pStaticMeshHouse1->draw();
	m_pStaticMeshHouse2->draw();
	m_pStaticMeshHouse3->draw();
	m_pStaticMeshHouse4->draw();
	m_pStaticMeshHouse5->draw();
	m_pStaticMeshStrawCar->draw();
	m_pStaticMeshStraw->draw();

	for (int i = 0; i < NumberOfStrawPuppet; i++){m_pStaticMeshStrawPuppet[i]->draw();}
	for (int i = 0; i < NumberOfFence1; ++i){m_pStaticMeshFence1[i]->draw();}
	for (int i = 0; i < NumberOfFence2; ++i){m_pStaticMeshFence2[i]->draw();}
	for (int i = 0; i < NumberOfFence3; ++i){m_pStaticMeshFence3[i]->draw();}
	for (int i = 0; i < NumberOfLeftWallBush; ++i){m_pStaticMeshLeftWallBush[i]->draw();}
	for (int i = 0; i < NumberOfTopWallBush; ++i){m_pStaticMeshTopWallBush[i]->draw();}
	for (int i = 0; i < NumberOfRIghtWallBush; ++i){m_pStaticMeshRIghtWallBush[i]->draw();}
	for (int i = 0; i < NumberOfBottomWallBush; ++i){m_pStaticMeshBottomWallBush[i]->draw();}
	for (int i = 0; i < NumberOfRIghtBottomEdgeBush; ++i){m_pStaticMeshRIghtBottomEdgeBush[i]->draw();}
	for (int i = 0; i < NumberOfTree1; ++i){m_pStaticMeshTree1[i]->draw();}
	for (int i = 0; i < NumberOfTree2; ++i){m_pStaticMeshTree2[i]->draw();}
	for (int i = 0; i < NumberOfTree3; ++i){m_pStaticMeshTree3[i]->draw();}
	for (int i = 0; i < NumberOfTreeBoss; ++i){m_pStaticMeshTreeBoss[i]->draw();}
	for (int i = 0; i < NumberOfTreeBossDestroy1; ++i){m_pStaticMeshTreeBossDestroy1[i]->draw();}
	for (int i = 0; i < NumberOfTreeBossDestroy2; ++i){m_pStaticMeshTreeBossDestroy2[i]->draw();}
	for (int i = 0; i < NumberOfBuin; ++i){m_pStaticMeshRuin[i]->draw();}

	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

CTerrain * filedMap::createTerrain(void)
{
	CTerrain::STParameters stParameters
	{
		1,
		1.0f,
		"",
		"Resources/MapResources/wowTestMapEx/heightmap.bmp",
		"Resources/MapResources/mapTerrain.fx",
	};

	stParameters.tileSize.cx = 4;
	stParameters.tileSize.cy = 4;

	char szTextureFilepath[MAX_PATH] = "";
	sprintf(szTextureFilepath, "Resources/MapResources/wowTestMapEx/azeroth_35_33_bottom.png");

	stParameters.textureFilepathList.push_back(szTextureFilepath);

	return new CTerrain(stParameters);
}

CStaticMesh_Map * filedMap::createStaticMeshMap(std::string Filepath, const STSphereSRT _stSphere)
{
	CStaticMesh_Map::STParameters stParameters = {
		Filepath,
		"Resources/MapResources/Example_24.fx"
	};

	return new CStaticMesh_Map(stParameters, true, _stSphere);
}

void filedMap::skyBoxDraw(void)
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

LPD3DXMESH filedMap::createSphere(void)
{
	LPD3DXMESH p_Mesh = nullptr;
	LPD3DXBUFFER pAdj = nullptr;

	D3DXCreateSphere(GET_DEVICE(), 1050, 100, 50, &p_Mesh, &pAdj);

	// 법선 계산!
	D3DXComputeNormals(p_Mesh, (DWORD*)pAdj->GetBufferPointer());

	return p_Mesh;
}


void filedMap::ObjectPosition(void)
{
	m_pStaticMeshHouse1 = this->createStaticMeshMap("Resources/MapResources/집/1/house1.x");
	m_pStaticMeshHouse1->rotateByYAxis(0);
	m_pStaticMeshHouse1->setPosition(D3DXVECTOR3(-306.0f,
		4.2 - 32 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshHouse1->getPosition()), 157.0f));

	m_pStaticMeshHouse2 = this->createStaticMeshMap("Resources/MapResources/집/2/house2.x");
	m_pStaticMeshHouse2->rotateByYAxis(-45);
	m_pStaticMeshHouse2->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshHouse2->setPosition(D3DXVECTOR3(-389.0f,
		4.2 - 32 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshHouse2->getPosition()), 140.0f));

	m_pStaticMeshHouse3 = this->createStaticMeshMap("Resources/MapResources/집/3/house3.x");
	m_pStaticMeshHouse3->setPosition(D3DXVECTOR3(-235.0f,
		4.2 - 31 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshHouse3->getPosition()), 95.0f));

	m_pStaticMeshHouse4 = this->createStaticMeshMap("Resources/MapResources/집/4/house4.x");
	m_pStaticMeshHouse4->setPosition(D3DXVECTOR3(-315.0f,
		4.2 - 31 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshHouse4->getPosition()), -80.0f));

	m_pStaticMeshHouse5 = this->createStaticMeshMap("Resources/MapResources/집/5/house5.x");
	m_pStaticMeshHouse5->rotateByYAxis(135);
	m_pStaticMeshHouse5->setPosition(D3DXVECTOR3(-260.0f,
		4.2 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshHouse5->getPosition()), -39.0f));

	for (int i = 0; i < NumberOfStrawPuppet; i++)
	{
		m_pStaticMeshStrawPuppet[i] = this->createStaticMeshMap("Resources/MapResources/기타/허수아비/1.x");
		m_pStaticMeshStrawPuppet[i]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	}
	m_pStaticMeshStrawPuppet[0]->setPosition(D3DXVECTOR3(-350.0f,
		4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStrawPuppet[0]->getPosition()), 90.0f));
	m_pStaticMeshStrawPuppet[1]->setPosition(D3DXVECTOR3(-280.0f,
		4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStrawPuppet[1]->getPosition()), 90.0f));
	m_pStaticMeshStrawPuppet[2]->setPosition(D3DXVECTOR3(-350.0f,
		4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStrawPuppet[2]->getPosition()), 40.0f));
	m_pStaticMeshStrawPuppet[3]->setPosition(D3DXVECTOR3(-280.0f,
		4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStrawPuppet[3]->getPosition()), 40.0f));
	m_pStaticMeshStrawPuppet[4]->setPosition(D3DXVECTOR3(-350.0f,
		4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStrawPuppet[4]->getPosition()), -10.0f));
	m_pStaticMeshStrawPuppet[5]->setPosition(D3DXVECTOR3(-280.0f,
		4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStrawPuppet[5]->getPosition()), -10.0f));

	m_pStaticMeshStrawCar = this->createStaticMeshMap("Resources/MapResources/기타/짚차/1.x");
	m_pStaticMeshStrawCar->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshStrawCar->setPosition(D3DXVECTOR3(-365.0f,
		5 - 32 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStrawCar->getPosition()), 95.0f));

	m_pStaticMeshStraw = this->createStaticMeshMap("Resources/MapResources/기타/짚/1.x");
	m_pStaticMeshStraw->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshStraw->setPosition(D3DXVECTOR3(-375.0f,
		5 - 32 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshStraw->getPosition()), 95.0f));

	m_pStaticMeshFence1[0] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence1[0]->rotateByYAxis(90);
	m_pStaticMeshFence1[0]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[0]->setPosition(D3DXVECTOR3(-13.0f + m_pStaticMeshHouse3->getPosition().x, 5 - 30 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[0]->getPosition()), 16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[1] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence1[1]->rotateByYAxis(90);
	m_pStaticMeshFence1[1]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[1]->setPosition(D3DXVECTOR3(-5.0f + m_pStaticMeshHouse3->getPosition().x, 5 - 30 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[1]->getPosition()), 16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[2] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence1[2]->rotateByYAxis(90);
	m_pStaticMeshFence1[2]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[2]->setPosition(D3DXVECTOR3(3.0f + m_pStaticMeshHouse3->getPosition().x, 5 - 30 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[2]->getPosition()), 16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[3] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence1[3]->rotateByYAxis(90);
	m_pStaticMeshFence1[3]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[3]->setPosition(D3DXVECTOR3(11.0f + m_pStaticMeshHouse3->getPosition().x, 5 - 30 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[3]->getPosition()), 16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[4] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence1[4]->rotateByYAxis(180);
	m_pStaticMeshFence1[4]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[4]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse3->getPosition().x, 5 - 27 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[4]->getPosition()), 16.0f + m_pStaticMeshHouse3->getPosition().z));

	m_pStaticMeshFence1[5] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence1[5]->rotateByYAxis(180);
	m_pStaticMeshFence1[5]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[5]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse3->getPosition().x, 11 - 12 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[4]->getPosition()), 8.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[6] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence1[6]->rotateByYAxis(180);
	m_pStaticMeshFence1[6]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[6]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse3->getPosition().x, 11 - 12 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[5]->getPosition()), 0.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[7] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence1[7]->rotateByYAxis(180);
	m_pStaticMeshFence1[7]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[7]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse3->getPosition().x, 11 - 11 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[6]->getPosition()), -8.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[8] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence1[8]->rotateByYAxis(-90);
	m_pStaticMeshFence1[8]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[8]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse3->getPosition().x, 11 - 11 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[7]->getPosition()), -16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[9] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence1[9]->rotateByYAxis(-90);
	m_pStaticMeshFence1[9]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[9]->setPosition(D3DXVECTOR3(11.0f + m_pStaticMeshHouse3->getPosition().x, 11 - 10 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[8]->getPosition()), -16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[10] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence1[10]->rotateByYAxis(-90);
	m_pStaticMeshFence1[10]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[10]->setPosition(D3DXVECTOR3(3.0f + m_pStaticMeshHouse3->getPosition().x, 11 - 10 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[9]->getPosition()), -16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[11] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence1[11]->rotateByYAxis(-90);
	m_pStaticMeshFence1[11]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[11]->setPosition(D3DXVECTOR3(-5.0f + m_pStaticMeshHouse3->getPosition().x, 11 - 10 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[9]->getPosition()), -16.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence1[12] = this->createStaticMeshMap("Resources/MapResources/울타리/1/fence1.x");
	m_pStaticMeshFence1[12]->rotateByYAxis(0);
	m_pStaticMeshFence1[12]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence1[12]->setPosition(D3DXVECTOR3(-13.0f + m_pStaticMeshHouse3->getPosition().x, 11.5 - 10 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence1[9]->getPosition()), -16.0f + m_pStaticMeshHouse3->getPosition().z));


	m_pStaticMeshFence2[0] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[0]->rotateByYAxis(90);
	m_pStaticMeshFence2[0]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[0]->setPosition(D3DXVECTOR3(-13.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 30.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 80.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[1] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence2[1]->rotateByYAxis(90);
	m_pStaticMeshFence2[1]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[1]->setPosition(D3DXVECTOR3(-5.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 30.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[1]->getPosition()), 80.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[2] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[2]->rotateByYAxis(90);
	m_pStaticMeshFence2[2]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[2]->setPosition(D3DXVECTOR3(3.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 30.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[2]->getPosition()), 80.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[3] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence2[3]->rotateByYAxis(90);
	m_pStaticMeshFence2[3]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[3]->setPosition(D3DXVECTOR3(11.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 30.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[3]->getPosition()), 80.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[4] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[4]->rotateByYAxis(180);
	m_pStaticMeshFence2[4]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[4]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 30.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[4]->getPosition()), 80.0f + m_pStaticMeshHouse3->getPosition().z));

	m_pStaticMeshFence2[5] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[5]->rotateByYAxis(180);
	m_pStaticMeshFence2[5]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[5]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse1->getPosition().x, 19.5 - 19 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[4]->getPosition()), 72.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[6] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence2[6]->rotateByYAxis(180);
	m_pStaticMeshFence2[6]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[6]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse1->getPosition().x, 18 - 17.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[5]->getPosition()), 64.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[7] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[7]->rotateByYAxis(180);
	m_pStaticMeshFence2[7]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[7]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse1->getPosition().x, 18 - 17.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[6]->getPosition()), 56.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[8] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence2[8]->rotateByYAxis(180);
	m_pStaticMeshFence2[8]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[8]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse1->getPosition().x, 18.5 - 17.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[7]->getPosition()), 48.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[9] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[9]->rotateByYAxis(-90);
	m_pStaticMeshFence2[9]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[9]->setPosition(D3DXVECTOR3(19.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[9]->getPosition()), 40.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[10] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence2[10]->rotateByYAxis(-90);
	m_pStaticMeshFence2[10]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[10]->setPosition(D3DXVECTOR3(11.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[10]->getPosition()), 40.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[11] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[11]->rotateByYAxis(-90);
	m_pStaticMeshFence2[11]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[11]->setPosition(D3DXVECTOR3(3.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[11]->getPosition()), 40.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[12] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence2[12]->rotateByYAxis(-90);
	m_pStaticMeshFence2[12]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[12]->setPosition(D3DXVECTOR3(-5.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[12]->getPosition()), 40.0f + m_pStaticMeshHouse3->getPosition().z));

	m_pStaticMeshFence2[13] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[13]->rotateByYAxis(-90);
	m_pStaticMeshFence2[13]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[13]->setPosition(D3DXVECTOR3(-13.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[13]->getPosition()), 40.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[14] = this->createStaticMeshMap("Resources/MapResources/울타리/1/fence1.x");
	m_pStaticMeshFence2[14]->rotateByYAxis(0);
	m_pStaticMeshFence2[14]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[14]->setPosition(D3DXVECTOR3(-21.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 31.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[14]->getPosition()), 40.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[15] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence2[15]->rotateByYAxis(90);
	m_pStaticMeshFence2[15]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[15]->setPosition(D3DXVECTOR3(-21.0f + m_pStaticMeshHouse1->getPosition().x, 4 - 30.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[15]->getPosition()), 80.0f + m_pStaticMeshHouse3->getPosition().z));
	m_pStaticMeshFence2[16] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence2[16]->rotateByYAxis(0);
	m_pStaticMeshFence2[16]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence2[16]->setPosition(D3DXVECTOR3(-21.0f + m_pStaticMeshHouse1->getPosition().x, 3.5 - 30.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[16]->getPosition()), 72.0f + m_pStaticMeshHouse3->getPosition().z));

	// -411 19

	m_pStaticMeshFence3[0] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[0]->rotateByYAxis(0);
	m_pStaticMeshFence3[0]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[0]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 19));
	m_pStaticMeshFence3[1] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[1]->rotateByYAxis(0);
	m_pStaticMeshFence3[1]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[1]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 27));
	m_pStaticMeshFence3[2] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[2]->rotateByYAxis(0);
	m_pStaticMeshFence3[2]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[2]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 35));
	m_pStaticMeshFence3[3] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[3]->rotateByYAxis(0);
	m_pStaticMeshFence3[3]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[3]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 43));
	m_pStaticMeshFence3[4] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[4]->rotateByYAxis(0);
	m_pStaticMeshFence3[4]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[4]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 51));
	m_pStaticMeshFence3[5] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[5]->rotateByYAxis(0);
	m_pStaticMeshFence3[5]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[5]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 59));
	m_pStaticMeshFence3[6] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[6]->rotateByYAxis(0);
	m_pStaticMeshFence3[6]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[6]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 67));
	m_pStaticMeshFence3[7] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[7]->rotateByYAxis(0);
	m_pStaticMeshFence3[7]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[7]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 75));
	m_pStaticMeshFence3[8] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[8]->rotateByYAxis(0);
	m_pStaticMeshFence3[8]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[8]->setPosition(D3DXVECTOR3(-411.0f, -20 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 83));
	m_pStaticMeshFence3[9] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[9]->rotateByYAxis(0);
	m_pStaticMeshFence3[9]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[9]->setPosition(D3DXVECTOR3(-411.0f, -20 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 91));
	m_pStaticMeshFence3[10] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[10]->rotateByYAxis(0);
	m_pStaticMeshFence3[10]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[10]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 99));
	m_pStaticMeshFence3[11] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[11]->rotateByYAxis(0);
	m_pStaticMeshFence3[11]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[11]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 107));
	m_pStaticMeshFence3[12] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[12]->rotateByYAxis(0);
	m_pStaticMeshFence3[12]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[12]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 115));
	m_pStaticMeshFence3[13] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[13]->rotateByYAxis(0);
	m_pStaticMeshFence3[13]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[13]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 123));
	m_pStaticMeshFence3[14] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[14]->rotateByYAxis(0);
	m_pStaticMeshFence3[14]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[14]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 131));
	m_pStaticMeshFence3[15] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[15]->rotateByYAxis(0);
	m_pStaticMeshFence3[15]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[15]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 139));
	m_pStaticMeshFence3[16] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[16]->rotateByYAxis(0);
	m_pStaticMeshFence3[16]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[16]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 147));
	m_pStaticMeshFence3[17] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[17]->rotateByYAxis(0);
	m_pStaticMeshFence3[17]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[17]->setPosition(D3DXVECTOR3(-411.0f, -20.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 155));
	m_pStaticMeshFence3[18] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[18]->rotateByYAxis(0);
	m_pStaticMeshFence3[18]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[18]->setPosition(D3DXVECTOR3(-411.0f, -20.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 163));
	m_pStaticMeshFence3[19] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[19]->rotateByYAxis(0);
	m_pStaticMeshFence3[19]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[19]->setPosition(D3DXVECTOR3(-411.0f, -19.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 171));

	m_pStaticMeshFence3[20] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[20]->rotateByYAxis(0);
	m_pStaticMeshFence3[20]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[20]->setPosition(D3DXVECTOR3(-411.0f, -17 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 179));
	m_pStaticMeshFence3[21] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[21]->rotateByYAxis(0);
	m_pStaticMeshFence3[21]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[21]->setPosition(D3DXVECTOR3(-411.0f, -16 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 187));
	m_pStaticMeshFence3[22] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[22]->rotateByYAxis(0);
	m_pStaticMeshFence3[22]->rotateByXAxis(-20);
	m_pStaticMeshFence3[22]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[22]->setPosition(D3DXVECTOR3(-411.0f, -13 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 195));
	m_pStaticMeshFence3[23] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[23]->rotateByYAxis(0);
	m_pStaticMeshFence3[23]->rotateByXAxis(-20);
	m_pStaticMeshFence3[23]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[23]->setPosition(D3DXVECTOR3(-411.0f, -10 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 203));
	m_pStaticMeshFence3[24] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[24]->rotateByYAxis(0);
	m_pStaticMeshFence3[24]->rotateByXAxis(-20);
	m_pStaticMeshFence3[24]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[24]->setPosition(D3DXVECTOR3(-411.0f, -7 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 211));
	m_pStaticMeshFence3[25] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[25]->rotateByYAxis(90);
	m_pStaticMeshFence3[25]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[25]->setPosition(D3DXVECTOR3(-411.0f, -4.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[26] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[26]->rotateByYAxis(90);
	m_pStaticMeshFence3[26]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[26]->setPosition(D3DXVECTOR3(-403.0f, -4 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[27] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[27]->rotateByYAxis(90);
	m_pStaticMeshFence3[27]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[27]->setPosition(D3DXVECTOR3(-395.0f, -3.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[28] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[28]->rotateByYAxis(90);
	m_pStaticMeshFence3[28]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[28]->setPosition(D3DXVECTOR3(-387.0f, -3.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[29] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[29]->rotateByYAxis(90);
	m_pStaticMeshFence3[29]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[29]->setPosition(D3DXVECTOR3(-379.0f, -3.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));

	m_pStaticMeshFence3[30] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[30]->rotateByYAxis(90);
	m_pStaticMeshFence3[30]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[30]->setPosition(D3DXVECTOR3(-371.0f, -3.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[31] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[31]->rotateByYAxis(90);
	m_pStaticMeshFence3[31]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[31]->setPosition(D3DXVECTOR3(-363.0f, -3.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[32] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[32]->rotateByYAxis(90);
	m_pStaticMeshFence3[32]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[32]->setPosition(D3DXVECTOR3(-355.0f, -3.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[33] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[33]->rotateByYAxis(90);
	m_pStaticMeshFence3[33]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[33]->setPosition(D3DXVECTOR3(-347.0f, -2 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[34] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[34]->rotateByYAxis(90);
	m_pStaticMeshFence3[34]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[34]->setPosition(D3DXVECTOR3(-339.0f, -2 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[35] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[35]->rotateByYAxis(90);
	m_pStaticMeshFence3[35]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[35]->setPosition(D3DXVECTOR3(-331.0f, -3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[36] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[36]->rotateByYAxis(90);
	m_pStaticMeshFence3[36]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[36]->setPosition(D3DXVECTOR3(-323.0f, -5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[37] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[37]->rotateByYAxis(90);
	m_pStaticMeshFence3[37]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[37]->setPosition(D3DXVECTOR3(-315.0f, -7 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[38] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[38]->rotateByYAxis(90);
	m_pStaticMeshFence3[38]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[38]->setPosition(D3DXVECTOR3(-307.0f, -7 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[39] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[39]->rotateByYAxis(90);
	m_pStaticMeshFence3[39]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[39]->setPosition(D3DXVECTOR3(-299.0f, -7 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));

	m_pStaticMeshFence3[40] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[40]->rotateByYAxis(90);
	m_pStaticMeshFence3[40]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[40]->setPosition(D3DXVECTOR3(-291.0f, -6.7 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[41] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[41]->rotateByYAxis(90);
	m_pStaticMeshFence3[41]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[41]->setPosition(D3DXVECTOR3(-283.0f, -5.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[42] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[42]->rotateByYAxis(90);
	m_pStaticMeshFence3[42]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[42]->setPosition(D3DXVECTOR3(-275.0f, -3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[43] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[43]->rotateByYAxis(90);
	m_pStaticMeshFence3[43]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[43]->setPosition(D3DXVECTOR3(-267.0f, -2 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[44] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[44]->rotateByYAxis(90);
	m_pStaticMeshFence3[44]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[44]->setPosition(D3DXVECTOR3(-259.0f, -1 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[45] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[45]->rotateByYAxis(90);
	m_pStaticMeshFence3[45]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[45]->setPosition(D3DXVECTOR3(-251.0f, 0 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[46] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[46]->rotateByYAxis(90);
	m_pStaticMeshFence3[46]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[46]->setPosition(D3DXVECTOR3(-243.0f, 0 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[47] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[47]->rotateByYAxis(180);
	m_pStaticMeshFence3[47]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[47]->setPosition(D3DXVECTOR3(-235.0f, 0.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 217.5));
	m_pStaticMeshFence3[48] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[48]->rotateByYAxis(180);
	m_pStaticMeshFence3[48]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[48]->setPosition(D3DXVECTOR3(-235.0f, 0.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 209.5));
	m_pStaticMeshFence3[49] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[49]->rotateByYAxis(180);
	m_pStaticMeshFence3[49]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[49]->setPosition(D3DXVECTOR3(-235.0f, 0.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 209.5));

	m_pStaticMeshFence3[50] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[50]->rotateByYAxis(90);
	m_pStaticMeshFence3[50]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[50]->setPosition(D3DXVECTOR3(-235.0f, 0.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 201.5));
	m_pStaticMeshFence3[51] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[51]->rotateByYAxis(90);
	m_pStaticMeshFence3[51]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[51]->setPosition(D3DXVECTOR3(-227.0f, 0.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 201.5));
	m_pStaticMeshFence3[52] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[52]->rotateByYAxis(90);
	m_pStaticMeshFence3[52]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[52]->setPosition(D3DXVECTOR3(-219.0f, 0.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 201.5));
	m_pStaticMeshFence3[53] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[53]->rotateByYAxis(90);
	m_pStaticMeshFence3[53]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[53]->setPosition(D3DXVECTOR3(-211.0f, 2 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 201.5));
	m_pStaticMeshFence3[54] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[54]->rotateByYAxis(90);
	m_pStaticMeshFence3[54]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[54]->setPosition(D3DXVECTOR3(-203.0f, 3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 201.5));
	m_pStaticMeshFence3[55] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[55]->rotateByYAxis(180);
	m_pStaticMeshFence3[55]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[55]->setPosition(D3DXVECTOR3(-195.0f, 3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 201.5));
	m_pStaticMeshFence3[56] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[56]->rotateByYAxis(180);
	m_pStaticMeshFence3[56]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[56]->setPosition(D3DXVECTOR3(-195.0f, 3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 193.5));
	m_pStaticMeshFence3[57] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[57]->rotateByYAxis(180);
	m_pStaticMeshFence3[57]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[57]->setPosition(D3DXVECTOR3(-195.0f, 4 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 185.5));
	m_pStaticMeshFence3[58] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[58]->rotateByYAxis(180);
	m_pStaticMeshFence3[58]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[58]->setPosition(D3DXVECTOR3(-195.0f, 3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 177.5));
	m_pStaticMeshFence3[59] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[59]->rotateByYAxis(180);
	m_pStaticMeshFence3[59]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[59]->setPosition(D3DXVECTOR3(-195.0f, 3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 169.5));

	m_pStaticMeshFence3[60] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[60]->rotateByYAxis(180);
	m_pStaticMeshFence3[60]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[60]->setPosition(D3DXVECTOR3(-195.0f, 1 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 161.5));
	m_pStaticMeshFence3[61] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[61]->rotateByYAxis(180);
	m_pStaticMeshFence3[61]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[61]->setPosition(D3DXVECTOR3(-195.0f, 0 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 153.5));
	m_pStaticMeshFence3[62] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[62]->rotateByYAxis(180);
	m_pStaticMeshFence3[62]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[62]->setPosition(D3DXVECTOR3(-195.0f, -0 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 145.5));
	m_pStaticMeshFence3[63] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[63]->rotateByYAxis(180);
	m_pStaticMeshFence3[63]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[63]->setPosition(D3DXVECTOR3(-195.0f, -2 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 137.5));
	m_pStaticMeshFence3[64] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[64]->rotateByYAxis(180);
	m_pStaticMeshFence3[64]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[64]->setPosition(D3DXVECTOR3(-195.0f, -3 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 129.5));
	m_pStaticMeshFence3[65] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[65]->rotateByYAxis(180);
	m_pStaticMeshFence3[65]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[65]->setPosition(D3DXVECTOR3(-195.0f, -5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 121.5));
	m_pStaticMeshFence3[66] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[66]->rotateByYAxis(180);
	m_pStaticMeshFence3[66]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[66]->setPosition(D3DXVECTOR3(-195.0f, -7.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 113.5));
	m_pStaticMeshFence3[67] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[67]->rotateByYAxis(180);
	m_pStaticMeshFence3[67]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[67]->setPosition(D3DXVECTOR3(-195.0f, -8.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 105.5));
	m_pStaticMeshFence3[68] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[68]->rotateByYAxis(180);
	m_pStaticMeshFence3[68]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[68]->setPosition(D3DXVECTOR3(-195.0f, -9.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 97.5));
	m_pStaticMeshFence3[69] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[69]->rotateByXAxis(-20);
	m_pStaticMeshFence3[69]->rotateByYAxis(180);
	m_pStaticMeshFence3[69]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[69]->setPosition(D3DXVECTOR3(-195.0f, -11 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 90));

	m_pStaticMeshFence3[70] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[70]->rotateByXAxis(-30);
	m_pStaticMeshFence3[70]->rotateByYAxis(180);
	m_pStaticMeshFence3[70]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[70]->setPosition(D3DXVECTOR3(-195.0f, -13 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 82));
	m_pStaticMeshFence3[71] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[71]->rotateByYAxis(180);
	m_pStaticMeshFence3[71]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[71]->setPosition(D3DXVECTOR3(-195.0f, -17 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 74.5));
	m_pStaticMeshFence3[72] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[72]->rotateByYAxis(180);
	m_pStaticMeshFence3[72]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[72]->setPosition(D3DXVECTOR3(-195.0f, -19 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 66));
	m_pStaticMeshFence3[73] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[73]->rotateByYAxis(180);
	m_pStaticMeshFence3[73]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[73]->setPosition(D3DXVECTOR3(-195.0f, -20.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 58));
	m_pStaticMeshFence3[74] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[74]->rotateByYAxis(180);
	m_pStaticMeshFence3[74]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[74]->setPosition(D3DXVECTOR3(-195.0f, -21.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 50));
	m_pStaticMeshFence3[75] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[75]->rotateByYAxis(180);
	m_pStaticMeshFence3[75]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[75]->setPosition(D3DXVECTOR3(-195.0f, -21.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 42));
	m_pStaticMeshFence3[76] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[76]->rotateByYAxis(180);
	m_pStaticMeshFence3[76]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[76]->setPosition(D3DXVECTOR3(-195.0f, -21.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 34));
	m_pStaticMeshFence3[77] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[77]->rotateByYAxis(180);
	m_pStaticMeshFence3[77]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[77]->setPosition(D3DXVECTOR3(-195.0f, -21.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 26));
	m_pStaticMeshFence3[78] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[78]->rotateByYAxis(180);
	m_pStaticMeshFence3[78]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[78]->setPosition(D3DXVECTOR3(-195.0f, -21.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 18));
	m_pStaticMeshFence3[79] = this->createStaticMeshMap("Resources/MapResources/울타리/1/fence1.x");
	m_pStaticMeshFence3[79]->rotateByYAxis(135);
	m_pStaticMeshFence3[79]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[79]->setPosition(D3DXVECTOR3(-195.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), 10));

	m_pStaticMeshFence3[80] = this->createStaticMeshMap("Resources/MapResources/울타리/1/fence1.x");
	m_pStaticMeshFence3[80]->rotateByYAxis(45);
	m_pStaticMeshFence3[80]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[80]->setPosition(D3DXVECTOR3(-219.0f, -22.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[81] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[81]->rotateByYAxis(90);
	m_pStaticMeshFence3[81]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[81]->setPosition(D3DXVECTOR3(-227.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[82] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[82]->rotateByYAxis(90);
	m_pStaticMeshFence3[82]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[82]->setPosition(D3DXVECTOR3(-235.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[83] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[83]->rotateByYAxis(90);
	m_pStaticMeshFence3[83]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[83]->setPosition(D3DXVECTOR3(-243.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[84] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[84]->rotateByYAxis(90);
	m_pStaticMeshFence3[84]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[84]->setPosition(D3DXVECTOR3(-251.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[85] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[85]->rotateByYAxis(90);
	m_pStaticMeshFence3[85]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[85]->setPosition(D3DXVECTOR3(-259.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[86] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[86]->rotateByYAxis(90);
	m_pStaticMeshFence3[86]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[86]->setPosition(D3DXVECTOR3(-267.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[87] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[87]->rotateByYAxis(90);
	m_pStaticMeshFence3[87]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[87]->setPosition(D3DXVECTOR3(-275.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[88] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[88]->rotateByYAxis(90);
	m_pStaticMeshFence3[88]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[88]->setPosition(D3DXVECTOR3(-283.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[89] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[89]->rotateByYAxis(90);
	m_pStaticMeshFence3[89]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[89]->setPosition(D3DXVECTOR3(-291.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));

	m_pStaticMeshFence3[90] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[90]->rotateByYAxis(90);
	m_pStaticMeshFence3[90]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[90]->setPosition(D3DXVECTOR3(-299.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[91] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[91]->rotateByYAxis(90);
	m_pStaticMeshFence3[91]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[91]->setPosition(D3DXVECTOR3(-307.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[92] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[92]->rotateByYAxis(90);
	m_pStaticMeshFence3[92]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[92]->setPosition(D3DXVECTOR3(-315.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[93] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[93]->rotateByYAxis(90);
	m_pStaticMeshFence3[93]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[93]->setPosition(D3DXVECTOR3(-323.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[94] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[94]->rotateByYAxis(90);
	m_pStaticMeshFence3[94]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[94]->setPosition(D3DXVECTOR3(-331.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[95] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[95]->rotateByYAxis(90);
	m_pStaticMeshFence3[95]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[95]->setPosition(D3DXVECTOR3(-339.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[96] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[96]->rotateByYAxis(90);
	m_pStaticMeshFence3[96]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[96]->setPosition(D3DXVECTOR3(-347.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[97] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[97]->rotateByYAxis(90);
	m_pStaticMeshFence3[97]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[97]->setPosition(D3DXVECTOR3(-355.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[98] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[98]->rotateByYAxis(90);
	m_pStaticMeshFence3[98]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[98]->setPosition(D3DXVECTOR3(-363.0f, -19 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[99] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[99]->rotateByYAxis(90);
	m_pStaticMeshFence3[99]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[99]->setPosition(D3DXVECTOR3(-371.0f, -17 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));

	m_pStaticMeshFence3[100] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[100]->rotateByYAxis(90);
	m_pStaticMeshFence3[100]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[100]->setPosition(D3DXVECTOR3(-379.0f, -16 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[101] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[101]->rotateByYAxis(90);
	m_pStaticMeshFence3[101]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[101]->setPosition(D3DXVECTOR3(-387.0f, -16 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[102] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[102]->rotateByYAxis(90);
	m_pStaticMeshFence3[102]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[102]->setPosition(D3DXVECTOR3(-395.0f, -14 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[103] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[103]->rotateByYAxis(90);
	m_pStaticMeshFence3[103]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[103]->setPosition(D3DXVECTOR3(-403.0f, -14 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));
	m_pStaticMeshFence3[104] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[104]->rotateByYAxis(90);
	m_pStaticMeshFence3[104]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[104]->setPosition(D3DXVECTOR3(-411.0f, -13 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -110));

	m_pStaticMeshFence3[105] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[105]->rotateByYAxis(180);
	m_pStaticMeshFence3[105]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[105]->setPosition(D3DXVECTOR3(-411.0f, -14 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -102));
	m_pStaticMeshFence3[106] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[106]->rotateByYAxis(180);
	m_pStaticMeshFence3[106]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[106]->setPosition(D3DXVECTOR3(-411.0f, -15 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -94));
	m_pStaticMeshFence3[107] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[107]->rotateByYAxis(180);
	m_pStaticMeshFence3[107]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[107]->setPosition(D3DXVECTOR3(-411.0f, -16 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -86));
	m_pStaticMeshFence3[108] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[108]->rotateByYAxis(180);
	m_pStaticMeshFence3[108]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[108]->setPosition(D3DXVECTOR3(-411.0f, -18.5 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -78));
	m_pStaticMeshFence3[109] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[109]->rotateByYAxis(180);
	m_pStaticMeshFence3[109]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[109]->setPosition(D3DXVECTOR3(-411.0f, -20 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -70));

	m_pStaticMeshFence3[110] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[110]->rotateByYAxis(180);
	m_pStaticMeshFence3[110]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[110]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -62));
	m_pStaticMeshFence3[111] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[111]->rotateByYAxis(180);
	m_pStaticMeshFence3[111]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[111]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -54));
	m_pStaticMeshFence3[112] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[112]->rotateByYAxis(180);
	m_pStaticMeshFence3[112]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[112]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -46));
	m_pStaticMeshFence3[113] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[113]->rotateByYAxis(180);
	m_pStaticMeshFence3[113]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[113]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -38));
	m_pStaticMeshFence3[114] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[114]->rotateByYAxis(180);
	m_pStaticMeshFence3[114]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[114]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -30));
	m_pStaticMeshFence3[115] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[115]->rotateByYAxis(180);
	m_pStaticMeshFence3[115]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[115]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -22));
	m_pStaticMeshFence3[116] = this->createStaticMeshMap("Resources/MapResources/울타리/3/fence3.x");
	m_pStaticMeshFence3[116]->rotateByYAxis(180);
	m_pStaticMeshFence3[116]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[116]->setPosition(D3DXVECTOR3(-411.0f, -21 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -14));
	m_pStaticMeshFence3[117] = this->createStaticMeshMap("Resources/MapResources/울타리/2/fence2.x");
	m_pStaticMeshFence3[117]->rotateByYAxis(180);
	m_pStaticMeshFence3[117]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshFence3[117]->setPosition(D3DXVECTOR3(-411.0f, -22 + m_pTerrainPositionY + m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshFence2[0]->getPosition()), -6));

	for (int i = 0; i < NumberOfFence3; ++i)
	{
		m_pStaticMeshFence3[i]->setPosition(D3DXVECTOR3(m_pStaticMeshFence3[i]->getPosition().x,
			m_pStaticMeshFence3[i]->getPosition().y + 22, m_pStaticMeshFence3[i]->getPosition().z));
	}
}

void filedMap::treePosition(void)
{
	for (int i = 0; i < NumberOfLeftWallBush; ++i)
	{
		m_pStaticMeshLeftWallBush[i] = this->createStaticMeshMap("Resources/MapResources/나무/bush1/bush1.x");
		m_pStaticMeshLeftWallBush[i]->setScale(D3DXVECTOR3(7.0f, 7.0f, 7.0f));
		m_pStaticMeshLeftWallBush[i]->rotateByYAxis(90);
		m_pStaticMeshLeftWallBush[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		m_pStaticMeshLeftWallBush[i]->setPosition(D3DXVECTOR3(-492, 0.0f, -160 + i * 35));
		auto LeftBushCoord = m_pStaticMeshLeftWallBush[i]->getPosition();
		LeftBushCoord.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshLeftWallBush[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshLeftWallBush[i]->setPosition(LeftBushCoord);
	}

	for (int i = 0; i < NumberOfTopWallBush; ++i)
	{
		m_pStaticMeshTopWallBush[i] = this->createStaticMeshMap("Resources/MapResources/나무/bush1/bush1.x");
		m_pStaticMeshTopWallBush[i]->setScale(D3DXVECTOR3(7.0f, 7.0f, 7.0f));
		m_pStaticMeshTopWallBush[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		m_pStaticMeshTopWallBush[i]->setPosition(D3DXVECTOR3(-492 + i * 35, 0.0f, 500));
		auto TopBushCoord = m_pStaticMeshTopWallBush[i]->getPosition();
		TopBushCoord.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshTopWallBush[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshTopWallBush[i]->setPosition(TopBushCoord);
	}

	for (int i = 0; i < NumberOfRIghtWallBush; ++i)
	{
		m_pStaticMeshRIghtWallBush[i] = this->createStaticMeshMap("Resources/MapResources/나무/bush1/bush1.x");
		m_pStaticMeshRIghtWallBush[i]->setScale(D3DXVECTOR3(7.0f, 7.0f, 7.0f));
		m_pStaticMeshRIghtWallBush[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		m_pStaticMeshRIghtWallBush[i]->rotateByYAxis(-90);
		m_pStaticMeshRIghtWallBush[i]->setPosition(D3DXVECTOR3(492, 0.0f, 500 - i * 35));
		auto TopBushCoord = m_pStaticMeshRIghtWallBush[i]->getPosition();
		TopBushCoord.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshRIghtWallBush[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshRIghtWallBush[i]->setPosition(TopBushCoord);
	}

	for (int i = 0; i < NumberOfBottomWallBush; ++i)
	{
		if (i < 3)
		{
			m_pStaticMeshBottomWallBush[i] = this->createStaticMeshMap("Resources/MapResources/나무/bush4/bush4.x");
		}
		else
		{
			m_pStaticMeshBottomWallBush[i] = this->createStaticMeshMap("Resources/MapResources/나무/bush1/bush1.x");
		}
		m_pStaticMeshBottomWallBush[i]->setScale(D3DXVECTOR3(7.0f, 7.0f, 7.0f));
		m_pStaticMeshBottomWallBush[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		m_pStaticMeshBottomWallBush[i]->rotateByYAxis(0);
		m_pStaticMeshBottomWallBush[i]->setPosition(D3DXVECTOR3(112 - i * 25, 0.0f, -485));
		auto TopBushCoord = m_pStaticMeshBottomWallBush[i]->getPosition();
		TopBushCoord.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshBottomWallBush[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshBottomWallBush[i]->setPosition(TopBushCoord);
	}

	for (int i = 0; i < NumberOfRIghtBottomEdgeBush; ++i)
	{
		m_pStaticMeshRIghtBottomEdgeBush[i] = this->createStaticMeshMap("Resources/MapResources/나무/bush3/bush3.x");
		m_pStaticMeshRIghtBottomEdgeBush[i]->setScale(D3DXVECTOR3(17.0f, 17.0f, 17.0f));
		m_pStaticMeshRIghtBottomEdgeBush[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		m_pStaticMeshRIghtBottomEdgeBush[i]->rotateByYAxis(-90);
		m_pStaticMeshRIghtBottomEdgeBush[i]->setPosition(D3DXVECTOR3(492, 0.0f, 150 - i * 15));
		auto TopBushCoord = m_pStaticMeshRIghtBottomEdgeBush[i]->getPosition();
		TopBushCoord.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshRIghtBottomEdgeBush[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshRIghtBottomEdgeBush[i]->setPosition(TopBushCoord);
	}

	for (int i = 0; i < NumberOfTree1; ++i)
	{
		STSphereSRT _stSphere = { 0.22f, D3DXVECTOR3(-0.5, -19, -0.5) };

		m_pStaticMeshTree1[i] = this->createStaticMeshMap("Resources/MapResources/나무/tree1/tree1.x", _stSphere);
		m_pStaticMeshTree1[i]->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		m_pStaticMeshTree1[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		auto treeAngle = CreateFloatRandomValue(0, 360);
		m_pStaticMeshTree1[i]->rotateByYAxis(treeAngle);
	}
	m_pStaticMeshTree1[0]->setPosition(D3DXVECTOR3(-440, 0.0f, 280));
	m_pStaticMeshTree1[1]->setPosition(D3DXVECTOR3(-410, 0.0f, 290));
	m_pStaticMeshTree1[2]->setPosition(D3DXVECTOR3(-380, 0.0f, 290));
	m_pStaticMeshTree1[3]->setPosition(D3DXVECTOR3(-350, 0.0f, 240));
	m_pStaticMeshTree1[4]->setPosition(D3DXVECTOR3(-320, 0.0f, 240));
	m_pStaticMeshTree1[5]->setPosition(D3DXVECTOR3(-280, 0.0f, 310));
	m_pStaticMeshTree1[6]->setPosition(D3DXVECTOR3(-270, 0.0f, 400));
	m_pStaticMeshTree1[7]->setPosition(D3DXVECTOR3(-230, 0.0f, 310));
	m_pStaticMeshTree1[8]->setPosition(D3DXVECTOR3(-180, 0.0f, 200));
	m_pStaticMeshTree1[9]->setPosition(D3DXVECTOR3(-150, 0.0f, 150));

	m_pStaticMeshTree1[10]->setPosition(D3DXVECTOR3(-486, 0.0f, -212));
	m_pStaticMeshTree1[11]->setPosition(D3DXVECTOR3(-490, 0.0f, -240));
	m_pStaticMeshTree1[12]->setPosition(D3DXVECTOR3(-380, 0.0f, -230));
	m_pStaticMeshTree1[13]->setPosition(D3DXVECTOR3(-350, 0.0f, -220));
	m_pStaticMeshTree1[14]->setPosition(D3DXVECTOR3(-340, 0.0f, -180));
	m_pStaticMeshTree1[15]->setPosition(D3DXVECTOR3(-430, 0.0f, -140));
	m_pStaticMeshTree1[16]->setPosition(D3DXVECTOR3(-400, 0.0f, -280));
	m_pStaticMeshTree1[17]->setPosition(D3DXVECTOR3(-230, 0.0f, -160));
	m_pStaticMeshTree1[18]->setPosition(D3DXVECTOR3(-140, 0.0f, -110));
	m_pStaticMeshTree1[19]->setPosition(D3DXVECTOR3(-140, 0.0f, -30));

	m_pStaticMeshTree1[20]->setPosition(D3DXVECTOR3(486, 0.0f, 212));
	m_pStaticMeshTree1[21]->setPosition(D3DXVECTOR3(-490 + 50, 0.0f, -240));
	m_pStaticMeshTree1[22]->setPosition(D3DXVECTOR3(-380 + 50, 0.0f, -120));
	m_pStaticMeshTree1[23]->setPosition(D3DXVECTOR3(-350 + 50, 0.0f, -160));
	m_pStaticMeshTree1[24]->setPosition(D3DXVECTOR3(320, 0.0f, -70));
	m_pStaticMeshTree1[25]->setPosition(D3DXVECTOR3(-280 + 50, 0.0f, -220));
	m_pStaticMeshTree1[26]->setPosition(D3DXVECTOR3(190, 0.0f, -160));
	m_pStaticMeshTree1[27]->setPosition(D3DXVECTOR3(-180, 0.0f, -140));
	m_pStaticMeshTree1[28]->setPosition(D3DXVECTOR3(-150 + 50, 0.0f, -90));
	m_pStaticMeshTree1[29]->setPosition(D3DXVECTOR3(210, 0.0f, -30));

	m_pStaticMeshTree1[30]->setPosition(D3DXVECTOR3(180, 0.0f, 350));
	m_pStaticMeshTree1[31]->setPosition(D3DXVECTOR3(-160, 0.0f, -360));
	m_pStaticMeshTree1[32]->setPosition(D3DXVECTOR3(160, 0.0f, 380));
	m_pStaticMeshTree1[33]->setPosition(D3DXVECTOR3(-150, 0.0f, -410));
	m_pStaticMeshTree1[34]->setPosition(D3DXVECTOR3(130, 0.0f, 170));
	m_pStaticMeshTree1[35]->setPosition(D3DXVECTOR3(-115, 0.0f, -385));
	m_pStaticMeshTree1[36]->setPosition(D3DXVECTOR3(110, 0.0f, -70));
	m_pStaticMeshTree1[37]->setPosition(D3DXVECTOR3(-100, 0.0f, -340));
	m_pStaticMeshTree1[38]->setPosition(D3DXVECTOR3(-90, 0.0f, 380));
	m_pStaticMeshTree1[39]->setPosition(D3DXVECTOR3(-70, 0.0f, -430));

	m_pStaticMeshTree1[40]->setPosition(D3DXVECTOR3(-180, 0.0f, -260));
	m_pStaticMeshTree1[41]->setPosition(D3DXVECTOR3(-150, 0.0f, -290));
	m_pStaticMeshTree1[42]->setPosition(D3DXVECTOR3(-220, 0.0f, -300));
	m_pStaticMeshTree1[43]->setPosition(D3DXVECTOR3(-190, 0.0f, -330));



	for (int i = 0; i < NumberOfTree1; ++i)
	{
		auto stCoordTree = m_pStaticMeshTree1[i]->getPosition();
		stCoordTree.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshTree1[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshTree1[i]->setPosition(stCoordTree);
	}

	// 118 218
	for (int i = 0; i < NumberOfTree2; ++i)
	{
		STSphereSRT _stSphere = { 0.1f, D3DXVECTOR3(0.8, -28, -2.4) };
		m_pStaticMeshTree2[i] = this->createStaticMeshMap("Resources/MapResources/나무/tree2/tree2.x", _stSphere);
		m_pStaticMeshTree2[i]->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		m_pStaticMeshTree2[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		//auto treeAngle = 0;
		auto treeAngle = CreateFloatRandomValue(0, 180);
		m_pStaticMeshTree2[i]->rotateByYAxis(treeAngle);
	}
	m_pStaticMeshTree2[0]->setPosition(D3DXVECTOR3(-380, 0.0f, 400));
	m_pStaticMeshTree2[1]->setPosition(D3DXVECTOR3(-150, 0.0f, 305));
	m_pStaticMeshTree2[2]->setPosition(D3DXVECTOR3(-100, 0.0f, 100));
	m_pStaticMeshTree2[3]->setPosition(D3DXVECTOR3(-30, 0.0f, 190));
	m_pStaticMeshTree2[4]->setPosition(D3DXVECTOR3(50, 0.0f, 150));
	m_pStaticMeshTree2[5]->setPosition(D3DXVECTOR3(150, 0.0f, -30));
	m_pStaticMeshTree2[6]->setPosition(D3DXVECTOR3(250, 0.0f, 120));
	m_pStaticMeshTree2[7]->setPosition(D3DXVECTOR3(120, 0.0f, 50));
	m_pStaticMeshTree2[8]->setPosition(D3DXVECTOR3(280, 0.0f, 250));

	for (int i = 0; i < NumberOfTree2; ++i)
	{
		auto stCoordTree = m_pStaticMeshTree2[i]->getPosition();
		stCoordTree.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshTree2[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshTree2[i]->setPosition(stCoordTree);
	}

	for (int i = 0; i < NumberOfTree3; ++i)
	{
		STSphereSRT _stSphere = { 0.1f, D3DXVECTOR3(-01, -28, -1) };
		m_pStaticMeshTree3[i] = this->createStaticMeshMap("Resources/MapResources/나무/tree3/tree3.x", _stSphere);
		m_pStaticMeshTree3[i]->setScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
		m_pStaticMeshTree3[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		//auto treeAngle = CreateFloatRandomValue(0, 360);
		//auto treeAngle = 0;
		auto treeAngle = CreateFloatRandomValue(0, 360);
		m_pStaticMeshTree3[i]->rotateByYAxis(treeAngle);
		//m_pStaticMeshTree3[i]->setTreeSRT(treeAngle, 0.1f, D3DXVECTOR3(-01, -28, -1));
	}

	m_pStaticMeshTree3[0]->setPosition(D3DXVECTOR3(402, 0.0f, 408));

	for (int i = 0; i < NumberOfTree3; ++i)
	{
		auto stCoordTree = m_pStaticMeshTree3[i]->getPosition();
		stCoordTree.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshTree3[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshTree3[i]->setPosition(stCoordTree);
	}


	for (int i = 0; i < NumberOfTreeBoss; ++i)
	{
		STSphereSRT _stSphere = { 0.07f, D3DXVECTOR3(0, -30, 0) };
		m_pStaticMeshTreeBoss[i] = this->createStaticMeshMap("Resources/MapResources/나무/tree4/tree4.x", _stSphere);
		m_pStaticMeshTreeBoss[i]->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		m_pStaticMeshTreeBoss[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
		//auto treeAngle = 0;
		auto treeAngle = CreateFloatRandomValue(0, 360);
		m_pStaticMeshTreeBoss[i]->rotateByYAxis(treeAngle);
		//m_pStaticMeshTreeBoss[i]->setTreeSRT(treeAngle, 0.07f, D3DXVECTOR3(0, -30, 0));
	}

	m_pStaticMeshTreeBoss[0]->setPosition(D3DXVECTOR3(75, 0.0f, -212));
	m_pStaticMeshTreeBoss[1]->setPosition(D3DXVECTOR3(95, 0.0f, -232));
	m_pStaticMeshTreeBoss[2]->setPosition(D3DXVECTOR3(125, 0.0f, -222));
	m_pStaticMeshTreeBoss[3]->setPosition(D3DXVECTOR3(140, 0.0f, -242));
	m_pStaticMeshTreeBoss[4]->setPosition(D3DXVECTOR3(160, 0.0f, -235));
	m_pStaticMeshTreeBoss[5]->setPosition(D3DXVECTOR3(180, 0.0f, -235));
	m_pStaticMeshTreeBoss[6]->setPosition(D3DXVECTOR3(190, 0.0f, -245));
	m_pStaticMeshTreeBoss[7]->setPosition(D3DXVECTOR3(200, 0.0f, -265));
	m_pStaticMeshTreeBoss[8]->setPosition(D3DXVECTOR3(220, 0.0f, -275));
	m_pStaticMeshTreeBoss[9]->setPosition(D3DXVECTOR3(240, 0.0f, -295));

	m_pStaticMeshTreeBoss[10]->setPosition(D3DXVECTOR3(220, 0.0f, -285));
	m_pStaticMeshTreeBoss[10]->setPosition(D3DXVECTOR3(230, 0.0f, -270));
	m_pStaticMeshTreeBoss[11]->setPosition(D3DXVECTOR3(230, 0.0f, -230));
	m_pStaticMeshTreeBoss[12]->setPosition(D3DXVECTOR3(232, 0.0f, -220));
	m_pStaticMeshTreeBoss[13]->setPosition(D3DXVECTOR3(250, 0.0f, -200));
	m_pStaticMeshTreeBoss[14]->setPosition(D3DXVECTOR3(260, 0.0f, -180));
	m_pStaticMeshTreeBoss[15]->setPosition(D3DXVECTOR3(260, 0.0f, -190));
	m_pStaticMeshTreeBoss[16]->setPosition(D3DXVECTOR3(280, 0.0f, -185));
	m_pStaticMeshTreeBoss[17]->setPosition(D3DXVECTOR3(280, 0.0f, -170));
	m_pStaticMeshTreeBoss[18]->setPosition(D3DXVECTOR3(290, 0.0f, -165));
	m_pStaticMeshTreeBoss[19]->setPosition(D3DXVECTOR3(295, 0.0f, -160));
	m_pStaticMeshTreeBoss[20]->setPosition(D3DXVECTOR3(300, 0.0f, -162));

	m_pStaticMeshTreeBoss[20]->setPosition(D3DXVECTOR3(200 - 200, 0.0f, -235));
	m_pStaticMeshTreeBoss[20]->setPosition(D3DXVECTOR3(190 - 200, 0.0f, -220));
	m_pStaticMeshTreeBoss[21]->setPosition(D3DXVECTOR3(180 - 200, 0.0f, -260));
	m_pStaticMeshTreeBoss[22]->setPosition(D3DXVECTOR3(212 - 200, 0.0f, -270));
	m_pStaticMeshTreeBoss[23]->setPosition(D3DXVECTOR3(230 - 200, 0.0f, -290));
	m_pStaticMeshTreeBoss[24]->setPosition(D3DXVECTOR3(270 - 200, 0.0f, -120));
	m_pStaticMeshTreeBoss[25]->setPosition(D3DXVECTOR3(250 - 200, 0.0f, -190));
	m_pStaticMeshTreeBoss[26]->setPosition(D3DXVECTOR3(260 - 200, 0.0f, -165));
	m_pStaticMeshTreeBoss[27]->setPosition(D3DXVECTOR3(220 - 200, 0.0f, -160));
	m_pStaticMeshTreeBoss[28]->setPosition(D3DXVECTOR3(290 - 200, 0.0f, -135));
	m_pStaticMeshTreeBoss[29]->setPosition(D3DXVECTOR3(235 - 200, 0.0f, -170));

	m_pStaticMeshTreeBoss[30]->setPosition(D3DXVECTOR3(200, 0.0f, -235));
	m_pStaticMeshTreeBoss[30]->setPosition(D3DXVECTOR3(190, 0.0f, -220));
	m_pStaticMeshTreeBoss[31]->setPosition(D3DXVECTOR3(180, 0.0f, -260));
	m_pStaticMeshTreeBoss[32]->setPosition(D3DXVECTOR3(212, 0.0f, -270));
	m_pStaticMeshTreeBoss[33]->setPosition(D3DXVECTOR3(230, 0.0f, -290));
	m_pStaticMeshTreeBoss[34]->setPosition(D3DXVECTOR3(270, 0.0f, -120));
	m_pStaticMeshTreeBoss[35]->setPosition(D3DXVECTOR3(250, 0.0f, -190));
	m_pStaticMeshTreeBoss[36]->setPosition(D3DXVECTOR3(260, 0.0f, -165));
	m_pStaticMeshTreeBoss[37]->setPosition(D3DXVECTOR3(220, 0.0f, -160));
	m_pStaticMeshTreeBoss[38]->setPosition(D3DXVECTOR3(290, 0.0f, -135));
	m_pStaticMeshTreeBoss[39]->setPosition(D3DXVECTOR3(235, 0.0f, -170));

	m_pStaticMeshTreeBoss[40]->setPosition(D3DXVECTOR3(200 + 40, 0.0f, -180));
	m_pStaticMeshTreeBoss[40]->setPosition(D3DXVECTOR3(190 + 120, 0.0f, -10));
	m_pStaticMeshTreeBoss[41]->setPosition(D3DXVECTOR3(180 + 120, 0.0f, 0));
	m_pStaticMeshTreeBoss[42]->setPosition(D3DXVECTOR3(212 + 120, 0.0f, 10));
	m_pStaticMeshTreeBoss[43]->setPosition(D3DXVECTOR3(230 + 120, 0.0f, 20));
	m_pStaticMeshTreeBoss[44]->setPosition(D3DXVECTOR3(270 + 120, 0.0f, 15));
	m_pStaticMeshTreeBoss[45]->setPosition(D3DXVECTOR3(250 + 40, 0.0f, -110));
	m_pStaticMeshTreeBoss[46]->setPosition(D3DXVECTOR3(260 + 40, 0.0f, -95));
	m_pStaticMeshTreeBoss[47]->setPosition(D3DXVECTOR3(220 + 40, 0.0f, -86));
	m_pStaticMeshTreeBoss[48]->setPosition(D3DXVECTOR3(290 + 40, 0.0f, -125));
	m_pStaticMeshTreeBoss[49]->setPosition(D3DXVECTOR3(235 + 40, 0.0f, -90));

	m_pStaticMeshTreeBoss[50]->setPosition(D3DXVECTOR3(200 + 80, 0.0f, -120));
	m_pStaticMeshTreeBoss[50]->setPosition(D3DXVECTOR3(190 + 80, 0.0f, -110));
	m_pStaticMeshTreeBoss[51]->setPosition(D3DXVECTOR3(180 + 80, 0.0f, -70));
	m_pStaticMeshTreeBoss[52]->setPosition(D3DXVECTOR3(212 + 80, 0.0f, -30));
	m_pStaticMeshTreeBoss[53]->setPosition(D3DXVECTOR3(230 + 80, 0.0f, -20));
	m_pStaticMeshTreeBoss[54]->setPosition(D3DXVECTOR3(270 + 120, 0.0f, -50));
	m_pStaticMeshTreeBoss[55]->setPosition(D3DXVECTOR3(250 + 120, 0.0f, -70));
	m_pStaticMeshTreeBoss[56]->setPosition(D3DXVECTOR3(260 + 120, 0.0f, -35));
	m_pStaticMeshTreeBoss[57]->setPosition(D3DXVECTOR3(220 + 120, 0.0f, -36));
	m_pStaticMeshTreeBoss[58]->setPosition(D3DXVECTOR3(290 + 120, 0.0f, -25));
	m_pStaticMeshTreeBoss[59]->setPosition(D3DXVECTOR3(235 + 120, 0.0f, -10));

	m_pStaticMeshTreeBoss[60]->setPosition(D3DXVECTOR3(400, 0.0f, 30));
	m_pStaticMeshTreeBoss[61]->setPosition(D3DXVECTOR3(420, 0.0f, -20));
	m_pStaticMeshTreeBoss[62]->setPosition(D3DXVECTOR3(440, 0.0f, -35));
	m_pStaticMeshTreeBoss[63]->setPosition(D3DXVECTOR3(450, 0.0f, 10));
	m_pStaticMeshTreeBoss[64]->setPosition(D3DXVECTOR3(420, 0.0f, -25));

	m_pStaticMeshTreeBoss[65]->setPosition(D3DXVECTOR3(70, 0.0f, -307));
	m_pStaticMeshTreeBoss[66]->setPosition(D3DXVECTOR3(90, 0.0f, -290));
	m_pStaticMeshTreeBoss[67]->setPosition(D3DXVECTOR3(110, 0.0f, -310));
	m_pStaticMeshTreeBoss[68]->setPosition(D3DXVECTOR3(130, 0.0f, -300));
	m_pStaticMeshTreeBoss[69]->setPosition(D3DXVECTOR3(80, 0.0f, -280));

	m_pStaticMeshTreeBoss[70]->setPosition(D3DXVECTOR3(40 - 100, 0.0f, -350));
	m_pStaticMeshTreeBoss[71]->setPosition(D3DXVECTOR3(50 - 100, 0.0f, -220));
	m_pStaticMeshTreeBoss[72]->setPosition(D3DXVECTOR3(60 - 100, 0.0f, -350));
	m_pStaticMeshTreeBoss[73]->setPosition(D3DXVECTOR3(55 - 100, 0.0f, -320));
	m_pStaticMeshTreeBoss[74]->setPosition(D3DXVECTOR3(45 - 100, 0.0f, -400));
	m_pStaticMeshTreeBoss[75]->setPosition(D3DXVECTOR3(70 - 100, 0.0f, -307 - 100));
	m_pStaticMeshTreeBoss[76]->setPosition(D3DXVECTOR3(90 - 100, 0.0f, -290 - 150));
	m_pStaticMeshTreeBoss[77]->setPosition(D3DXVECTOR3(110 - 100, 0.0f, -310 - 120));
	m_pStaticMeshTreeBoss[78]->setPosition(D3DXVECTOR3(130 - 100, 0.0f, -300 - 80));
	m_pStaticMeshTreeBoss[79]->setPosition(D3DXVECTOR3(80 - 100, 0.0f, -280 - 120));

	m_pStaticMeshTreeBoss[80]->setPosition(D3DXVECTOR3(140, 0.0f, -307));
	m_pStaticMeshTreeBoss[81]->setPosition(D3DXVECTOR3(150, 0.0f, -290));
	m_pStaticMeshTreeBoss[82]->setPosition(D3DXVECTOR3(160, 0.0f, -310));
	m_pStaticMeshTreeBoss[83]->setPosition(D3DXVECTOR3(165, 0.0f, -300));
	m_pStaticMeshTreeBoss[84]->setPosition(D3DXVECTOR3(180, 0.0f, -280 - 50));
	m_pStaticMeshTreeBoss[85]->setPosition(D3DXVECTOR3(200, 0.0f, -307 - 50));
	m_pStaticMeshTreeBoss[86]->setPosition(D3DXVECTOR3(210, 0.0f, -290 - 50));
	m_pStaticMeshTreeBoss[87]->setPosition(D3DXVECTOR3(225, 0.0f, -310 - 50));
	m_pStaticMeshTreeBoss[88]->setPosition(D3DXVECTOR3(240, 0.0f, -300 - 50));
	m_pStaticMeshTreeBoss[89]->setPosition(D3DXVECTOR3(260, 0.0f, -280 - 50));

	m_pStaticMeshTreeBoss[90]->setPosition(D3DXVECTOR3(260, 0.0f, -307 - 50));
	m_pStaticMeshTreeBoss[91]->setPosition(D3DXVECTOR3(265, 0.0f, -290 - 60));
	m_pStaticMeshTreeBoss[92]->setPosition(D3DXVECTOR3(270, 0.0f, -310 - 70));
	m_pStaticMeshTreeBoss[93]->setPosition(D3DXVECTOR3(275, 0.0f, -300 - 80));
	m_pStaticMeshTreeBoss[94]->setPosition(D3DXVECTOR3(280, 0.0f, -280 - 90));
	m_pStaticMeshTreeBoss[95]->setPosition(D3DXVECTOR3(280, 0.0f, -307 - 100));
	m_pStaticMeshTreeBoss[96]->setPosition(D3DXVECTOR3(285, 0.0f, -290 - 110));
	m_pStaticMeshTreeBoss[97]->setPosition(D3DXVECTOR3(290, 0.0f, -310 - 120));
	m_pStaticMeshTreeBoss[98]->setPosition(D3DXVECTOR3(295, 0.0f, -300 - 130));
	m_pStaticMeshTreeBoss[99]->setPosition(D3DXVECTOR3(300, 0.0f, -280 - 140));

	for (int i = 0; i < NumberOfTreeBoss; ++i)
	{
		auto stCoordTree = m_pStaticMeshTreeBoss[i]->getPosition();
		stCoordTree.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshTreeBoss[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshTreeBoss[i]->setPosition(stCoordTree);
	}

	// 461 -156
	//for (int i = 0; i < NumberOfTreeBossDestroy1; ++i)
	//{
	//	m_pStaticMeshTreeBossDestroy1[i] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy1/tree.x");
	//	m_pStaticMeshTreeBossDestroy1[i]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	//	m_pStaticMeshTreeBossDestroy1[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
	//	//auto treeAngle = CreateFloatRandomValue(0, 360);
	//	//auto treeAngle = 0;
	//	//m_pStaticMeshTreeBossDestroy1[i]->rotateByYAxis(treeAngle);
	//	//m_pStaticMeshTreeBossDestroy1[i]->setTreeSRT(treeAngle, 0.11f, D3DXVECTOR3(-12, -3, 0));
	//}
	STSphereSRT _stSphere = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy1[0] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy1/tree.x", _stSphere);
	m_pStaticMeshTreeBossDestroy1[0]->setPosition(D3DXVECTOR3(290, 0.0f, -140));
	m_pStaticMeshTreeBossDestroy1[0]->rotateByYAxis(180);
	//m_pStaticMeshTreeBossDestroy1[0]->setTreeSRT(180, 0.11f, D3DXVECTOR3(-12, -3, 0));

	_stSphere = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy1[1] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy1/tree.x", _stSphere);
	m_pStaticMeshTreeBossDestroy1[1]->setPosition(D3DXVECTOR3(396, 0.0f, -105));
	m_pStaticMeshTreeBossDestroy1[1]->rotateByYAxis(-30);
	//m_pStaticMeshTreeBossDestroy1[1]->setTreeSRT(-30, 0.11f, D3DXVECTOR3(-12, -3, 0));

	_stSphere = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy1[2] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy1/tree.x", _stSphere);
	m_pStaticMeshTreeBossDestroy1[2]->setPosition(D3DXVECTOR3(400, 0.0f, -270));
	m_pStaticMeshTreeBossDestroy1[2]->rotateByYAxis(270);
	//m_pStaticMeshTreeBossDestroy1[2]->setTreeSRT(270, 0.11f, D3DXVECTOR3(-12, -3, 0));

	_stSphere = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy1[3] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy1/tree.x", _stSphere);
	m_pStaticMeshTreeBossDestroy1[3]->setPosition(D3DXVECTOR3(340, 0.0f, -350));
	m_pStaticMeshTreeBossDestroy1[3]->rotateByYAxis(135);
	//m_pStaticMeshTreeBossDestroy1[3]->setTreeSRT(135, 0.11f, D3DXVECTOR3(-12, -3, 0));

	_stSphere = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy1[4] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy1/tree.x", _stSphere);
	m_pStaticMeshTreeBossDestroy1[4]->setPosition(D3DXVECTOR3(377, 0.0f, -123));
	m_pStaticMeshTreeBossDestroy1[4]->rotateByYAxis(-235);
	//m_pStaticMeshTreeBossDestroy1[4]->setTreeSRT(-235, 0.11f, D3DXVECTOR3(-12, -3, 0));
	for (int i = 0; i < NumberOfTreeBossDestroy1; ++i)
	{
		m_pStaticMeshTreeBossDestroy1[i]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	}
	for (int i = 0; i < NumberOfTreeBossDestroy1; ++i)
	{
		auto stCoordTree = m_pStaticMeshTreeBossDestroy1[i]->getPosition();
		stCoordTree.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshTreeBossDestroy1[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshTreeBossDestroy1[i]->setPosition(stCoordTree);
	}

	/*for (int i = 0; i < NumberOfTreeBossDestroy2; ++i)
	{
		m_pStaticMeshTreeBossDestroy2[i] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy2/tree.x");
		m_pStaticMeshTreeBossDestroy2[i]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		m_pStaticMeshTreeBossDestroy2[i]->setPosition(D3DXVECTOR3(0, 0.0f, 0));
	}*/
	STSphereSRT _stSphere2 = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy2[0] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy2/tree.x", _stSphere2);
	m_pStaticMeshTreeBossDestroy2[0]->setPosition(D3DXVECTOR3(380, 0.0f, -260));
	m_pStaticMeshTreeBossDestroy2[0]->rotateByYAxis(30);
	//m_pStaticMeshTreeBossDestroy2[0]->setTreeSRT(30, 0.09f, D3DXVECTOR3(4.5, -15, 0));

	_stSphere2 = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy2[1] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy2/tree.x", _stSphere2);
	m_pStaticMeshTreeBossDestroy2[1]->setPosition(D3DXVECTOR3(416 + 20, 0.0f, -240));
	m_pStaticMeshTreeBossDestroy2[1]->rotateByYAxis(60);
	//m_pStaticMeshTreeBossDestroy2[1]->setTreeSRT(60, 0.09f, D3DXVECTOR3(4.5, -15, 0));

	_stSphere2 = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy2[2] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy2/tree.x", _stSphere2);
	m_pStaticMeshTreeBossDestroy2[2]->setPosition(D3DXVECTOR3(416 + 20, 0.0f, -160));
	m_pStaticMeshTreeBossDestroy2[2]->rotateByYAxis(180);
	//m_pStaticMeshTreeBossDestroy2[2]->setTreeSRT(180, 0.09f, D3DXVECTOR3(4.5, -15, 0));

	_stSphere2 = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy2[3] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy2/tree.x", _stSphere2);
	m_pStaticMeshTreeBossDestroy2[3]->setPosition(D3DXVECTOR3(380, 0.0f, -350));
	m_pStaticMeshTreeBossDestroy2[3]->rotateByYAxis(0);
	//m_pStaticMeshTreeBossDestroy2[3]->setTreeSRT(0, 0.09f, D3DXVECTOR3(4.5, -15, 0));

	_stSphere2 = { 0.11f, D3DXVECTOR3(-12, -3, 0) };
	m_pStaticMeshTreeBossDestroy2[4] = this->createStaticMeshMap("Resources/MapResources/나무/treeDestroy2/tree.x", _stSphere2);
	m_pStaticMeshTreeBossDestroy2[4]->setPosition(D3DXVECTOR3(416, 0.0f, -140));
	m_pStaticMeshTreeBossDestroy2[4]->rotateByYAxis(240);
	//m_pStaticMeshTreeBossDestroy2[4]->setTreeSRT(240, 0.09f, D3DXVECTOR3(4.5, -15, 0));

	for (int i = 0; i < NumberOfTreeBossDestroy2; ++i)
	{
		m_pStaticMeshTreeBossDestroy2[i]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	}
	for (int i = 0; i < NumberOfTreeBossDestroy2; ++i)
	{
		auto stCoordTree = m_pStaticMeshTreeBossDestroy2[i]->getPosition();
		stCoordTree.y = m_pTerrain->getTerrainHeightAtPosition(m_pStaticMeshTreeBossDestroy2[i]->getPosition()) + m_pTerrainPositionY;
		m_pStaticMeshTreeBossDestroy2[i]->setPosition(stCoordTree);
	}
}

void filedMap::templePosition(void)
{
	m_pStaticMeshRuin[0] = this->createStaticMeshMap("Resources/MapResources/bossRoom/ruin/2/2.x");
	m_pStaticMeshRuin[0]->setScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	m_pStaticMeshRuin[0]->setPosition(D3DXVECTOR3(319 + 35, 0.0f, -194.0f));
	m_pStaticMeshRuin[0]->rotateByZAxis(90);
	
	m_pStaticMeshRuin[1] = this->createStaticMeshMap("Resources/MapResources/bossRoom/ruin/1/1.x");
	m_pStaticMeshRuin[1]->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	m_pStaticMeshRuin[1]->setPosition(D3DXVECTOR3(319, 0.0f, -160.0f));
	m_pStaticMeshRuin[1]->rotateByYAxis(-90);

	m_pStaticMeshRuin[2] = this->createStaticMeshMap("Resources/MapResources/bossRoom/ruin/3/3.x");
	m_pStaticMeshRuin[2]->setScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	m_pStaticMeshRuin[2]->setPosition(D3DXVECTOR3(400, 0.0f, -250.0f));
	m_pStaticMeshRuin[2]->rotateByYAxis(45);
	
	m_pStaticMeshRuin[3] = this->createStaticMeshMap("Resources/MapResources/bossRoom/ruin/4/4.x");
	m_pStaticMeshRuin[3]->setScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	m_pStaticMeshRuin[3]->setPosition(D3DXVECTOR3(450, 0.0f, -350.0f));
	
	m_pStaticMeshRuin[4] = this->createStaticMeshMap("Resources/MapResources/bossRoom/ruin/5/5.x");
	m_pStaticMeshRuin[4]->setScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	m_pStaticMeshRuin[4]->setPosition(D3DXVECTOR3(320, 0.0f, -300.0f));
	m_pStaticMeshRuin[4]->rotateByYAxis(90);

}

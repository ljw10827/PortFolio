#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"
#include "CTeraMap.h"

#define NumberOfFence1 13
#define NumberOfFence2 17
#define NumberOfFence3 118
#define NumberOfStrawPuppet 6
#define NumberOfTree1 5
#define NumberOfLeftWallBush 19
#define NumberOfTopWallBush 28
#define NumberOfRIghtWallBush 10
#define NumberOfBottomWallBush 10

#define NumberOfRIghtBottomEdgeBush 43

#define NumberOfTree1 44
#define NumberOfTree2 9
#define NumberOfTree3 1

#define NumberOfTreeBoss 100

#define NumberOfTreeBossDestroy1 5
#define NumberOfTreeBossDestroy2 5
#define NumberOfTreeBossDestroy3 5

#define NumberOfBuin 5

class CStaticMesh_Map;
class CTerrain;
class CSprite;

/*

��ī�̹ڽ��� �ʹ� Ŀ�� ī�޶��� �ν� �Ÿ� ������ �þ�� ������
CCcamera Ŭ������ �Լ� setFieldofView���� ������� ����� �κп��� D3DXMatrixPerspectiveFovLH������ ������ 1000 -> 2000���� ����

*/

class filedMap : public CTeraMap
{
public:

	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_TEX1 //UV
		};

		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR2 m_stUV;
	};

public:
	// ���¸� �����Ѵ�.
	virtual void update(void) override;
	// ȭ���� �׸���.
	virtual void doDrawObject(void) override;

public:
	// ���ø��ɸ����� �ʱ�ȭ�Ѵ�.
	virtual void init(void);

public: // ������

	explicit filedMap();
	// �Ҹ���
	virtual ~filedMap(void);
public:
	// ����Ʈ ���� ��ȯ �Լ�
	float getHeightMapY(const D3DXVECTOR3 & _vec);

private:
	// ��ī�̹ڽ�
	void skyBoxDraw(void);
	LPD3DXMESH createSphere(void);
	LPDIRECT3DCUBETEXTURE9 m_pCubeTexture = nullptr;
	LPD3DXEFFECT m_pEffect = nullptr;
	LPD3DXMESH m_pSphere;

private:
	// ����Ʈ ��
	CTerrain * createTerrain(void);
	CTerrain * m_pTerrain;

private:
	// ������
	CStaticMesh_Map * createStaticMeshMap(std::string Filepath, const STSphereSRT _stSphere = { 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f) });

	CStaticMesh_Map * m_pStaticMeshHouse1 = nullptr;
	CStaticMesh_Map * m_pStaticMeshHouse2 = nullptr;
	CStaticMesh_Map * m_pStaticMeshHouse3 = nullptr;
	CStaticMesh_Map * m_pStaticMeshHouse4 = nullptr;
	CStaticMesh_Map * m_pStaticMeshHouse5 = nullptr;

	CStaticMesh_Map * m_pStaticMeshFence1[NumberOfFence1] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshFence2[NumberOfFence2] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshFence3[NumberOfFence3] = { nullptr };

	CStaticMesh_Map * m_pStaticMeshStraw = nullptr;
	CStaticMesh_Map * m_pStaticMeshStrawCar = nullptr;
	CStaticMesh_Map * m_pStaticMeshStrawPuppet[NumberOfStrawPuppet] = { nullptr };

	CStaticMesh_Map * m_pStaticMeshTree1[NumberOfTree1] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshTree2[NumberOfTree2] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshTree3[NumberOfTree3] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshTreeBoss[NumberOfTreeBoss] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshTreeBossDestroy1[NumberOfTreeBossDestroy1] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshTreeBossDestroy2[NumberOfTreeBossDestroy2] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshTreeBossDestroy3[NumberOfTreeBossDestroy3] = { nullptr };

	CStaticMesh_Map * m_pStaticMeshLeftWallBush[NumberOfLeftWallBush] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshTopWallBush[NumberOfTopWallBush] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshRIghtWallBush[NumberOfRIghtWallBush] = { nullptr };
	CStaticMesh_Map * m_pStaticMeshBottomWallBush[NumberOfBottomWallBush] = { nullptr };

	CStaticMesh_Map * m_pStaticMeshRIghtBottomEdgeBush[NumberOfRIghtBottomEdgeBush] = { nullptr };

	CStaticMesh_Map * m_pStaticMeshRuin[NumberOfBuin] = { nullptr };

private:

	float m_pTerrainPositionY = 0.0f;

	void ObjectPosition(void);
	void treePosition(void);
	void templePosition(void);

	bool bIsDebugMode = false;

};
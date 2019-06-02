#pragma once

#include "../Global/Define/KGlobalDefine.h"

class CStaticMesh;
class CTerrain;
class CSkinnedMesh;
class CStaticMesh_AlphaControl;
class CSprite_MapUI;

/*

��ī�̹ڽ��� �ʹ� Ŀ�� ī�޶��� �ν� �Ÿ� ������ �þ�� ������
CCcamera Ŭ������ �Լ� setFieldofView���� ������� ����� �κп��� D3DXMatrixPerspectiveFovLH������ ������ 1000 -> 2000���� ����

*/

class bossRoom
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

	//// ���¸� �����Ѵ�.
	//virtual void update(void) override;
	//// ȭ���� �׸���.
	//virtual void draw(void) override;
	// ���¸� �����Ѵ�.
	virtual void update(void);
	// ȭ���� �׸���.
	virtual void draw(void);
	// UI�� �׸���.
	void drawUI(void);
public:

	//// ���ø��ɸ����� �ʱ�ȭ�Ѵ�.
	//virtual void initApplication(void) override;
	// ���ø��ɸ����� �ʱ�ȭ�Ѵ�.
	virtual void init(void);


public: // ������

	explicit bossRoom(void);
	// �Ҹ���
	virtual ~bossRoom(void);

private:
	// ��ī�̹ڽ�

	void skyBoxDraw(void);

	LPD3DXMESH createSphere(void);

	LPDIRECT3DCUBETEXTURE9 m_pCubeTexture = nullptr;

	LPD3DXEFFECT m_pEffect = nullptr;

	LPD3DXMESH m_pSphere;

private:
	// ������
	CStaticMesh * createStaticMeshMap(std::string Filepath);
	CStaticMesh * m_pStaticTemple[4] = { nullptr };

	CStaticMesh_AlphaControl * createStaticMeshMapAlpha(std::string Filepath);
	CStaticMesh_AlphaControl * m_pStaticFloor = nullptr;

private:
	CSkinnedMesh * createSkinnedMesh(void);
	CSkinnedMesh * m_pBoss = nullptr;
	int tempNum;

private:
	void radarSetting(const D3DXVECTOR3 & a_rtPosition);

	CSprite_MapUI * m_pRadar = nullptr;
	CSprite_MapUI * m_pRadarBase = nullptr;
	CSprite_MapUI * m_pEnemy = nullptr;

	SIZE m_totalMapSize;

	SIZE m_RadarSize;
	SIZE m_RadarBaseSize;

	// ���콺�� ���� ��ġ
	POINT m_stPrevMousePosition;

	int m_pRadarAngle = 0;
	bool bIsEnemyDraw = false;
};
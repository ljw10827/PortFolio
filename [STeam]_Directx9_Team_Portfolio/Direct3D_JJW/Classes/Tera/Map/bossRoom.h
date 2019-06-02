#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CTeraMap.h"

class CStaticMeshBoss;
class CTerrain;
class CSkinnedMesh;
class CStaticMesh_AlphaControl;

/*

��ī�̹ڽ��� �ʹ� Ŀ�� ī�޶��� �ν� �Ÿ� ������ �þ�� ������
CCcamera Ŭ������ �Լ� setFieldofView���� ������� ����� �κп��� D3DXMatrixPerspectiveFovLH������ ������ 1000 -> 2000���� ����

*/

class bossRoom : public CTeraMap
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
	virtual void update(void) override;
	// ȭ���� �׸���.
	virtual void doDrawObject(void) override;

public:

	//// ���ø��ɸ����� �ʱ�ȭ�Ѵ�.
	//virtual void initApplication(void) override;
	// ���ø��ɸ����� �ʱ�ȭ�Ѵ�.
	virtual void init(void) override;


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
	CStaticMeshBoss * createStaticMeshMap(std::string Filepath);
	CStaticMeshBoss * m_pStaticTemple[4] = { nullptr };

	CStaticMesh_AlphaControl * createStaticMeshMapAlpha(std::string Filepath);
	float getHeightMapY(const D3DXVECTOR3 & pos) { return 0; }
	CStaticMesh_AlphaControl * m_pStaticFloor = nullptr;

	CStaticMeshBoss * testPosition = nullptr;

private:
	CSkinnedMesh * m_pSinnedMeshFloor = nullptr;

};
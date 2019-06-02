#pragma once

#include "../Global/Define/KGlobalDefine.h"

class CStaticMesh;
class CTerrain;
class CSkinnedMesh;
class CStaticMesh_AlphaControl;
class CSprite_MapUI;

/*

스카이박스가 너무 커서 카메라의 인식 거리 범위가 늘어났기 때문에
CCcamera 클래스의 함수 setFieldofView에서 투영행렬 만든는 부분에서 D3DXMatrixPerspectiveFovLH인자의 마지막 1000 -> 2000으로 수정

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

	//// 상태를 갱신한다.
	//virtual void update(void) override;
	//// 화면을 그린다.
	//virtual void draw(void) override;
	// 상태를 갱신한다.
	virtual void update(void);
	// 화면을 그린다.
	virtual void draw(void);
	// UI를 그린다.
	void drawUI(void);
public:

	//// 어플리케리션을 초기화한다.
	//virtual void initApplication(void) override;
	// 어플리케리션을 초기화한다.
	virtual void init(void);


public: // 생성자

	explicit bossRoom(void);
	// 소멸자
	virtual ~bossRoom(void);

private:
	// 스카이박스

	void skyBoxDraw(void);

	LPD3DXMESH createSphere(void);

	LPDIRECT3DCUBETEXTURE9 m_pCubeTexture = nullptr;

	LPD3DXEFFECT m_pEffect = nullptr;

	LPD3DXMESH m_pSphere;

private:
	// 구조물
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

	// 마우스의 이전 위치
	POINT m_stPrevMousePosition;

	int m_pRadarAngle = 0;
	bool bIsEnemyDraw = false;
};
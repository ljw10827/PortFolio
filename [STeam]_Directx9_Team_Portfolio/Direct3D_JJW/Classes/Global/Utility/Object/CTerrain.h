#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

class CTerrain : public CRenderObject
{
public:

	enum
	{
		MAX_NUM_TERRAIN_TEXTURES = 4
	};

	//! 정점
	struct STVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
		D3DXVECTOR2 UV;
	};

	//! 매개변수
	struct STParameters
	{
		int smoothLevel;
		float heightScale;

		std::string splatFilepath;
		std::string heightFilepath;
		std::string effectFilepath;

		SIZE tileSize;
		std::vector<std::string> textureFilepathList;

	};

public:				// 생성자 & 소멸자
	
	//! 생성자
	explicit CTerrain(const STParameters &parameters);

	//! 소멸자
	virtual ~CTerrain(void);

public:				// public 함수

	//! 갱신
	virtual void update(void) override;

	//! 객체를 그린다
	virtual void doDrawObject(void) override;

	float getTerrainHeightAtPosition(const D3DXVECTOR3 & position);

private:			// private 함수

	//! 지형 정보를 설정한다
	void SetupTerrainInfo(const STParameters &parameters);

	//! 높이 정보를 설정한다.
	void SetupTerrainHeight(const STParameters &parameters);

	//! 지형 높이를 부드럽게 한다.
	void SmoothTerrainHeight(const STParameters &parameters);

	//! 지형 메쉬를 생성한다
	LPD3DXMESH CreateTerrainMesh(const STParameters &parameters);

	//! 지형 텍스처를 생성한다
	std::vector<LPDIRECT3DTEXTURE9> CreateTerrainTextures(const STParameters &parameters, LPDIRECT3DTEXTURE9 *outSplatTexture);


private:			// private 변수

	SIZE _mapSize;
	SIZE _tileSize;
	SIZE _totalSize;

	LPD3DXMESH _mesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;
	LPDIRECT3DTEXTURE9 _splatTexture = nullptr;

	float _heightScale;
	std::vector<float> _heightList;
	std::vector<LPDIRECT3DTEXTURE9> _textureList;
};
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

	//! ����
	struct STVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
		D3DXVECTOR2 UV;
	};

	//! �Ű�����
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

public:				// ������ & �Ҹ���
	
	//! ������
	explicit CTerrain(const STParameters &parameters);

	//! �Ҹ���
	virtual ~CTerrain(void);

public:				// public �Լ�

	//! ����
	virtual void update(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	float getTerrainHeightAtPosition(const D3DXVECTOR3 & position);

private:			// private �Լ�

	//! ���� ������ �����Ѵ�
	void SetupTerrainInfo(const STParameters &parameters);

	//! ���� ������ �����Ѵ�.
	void SetupTerrainHeight(const STParameters &parameters);

	//! ���� ���̸� �ε巴�� �Ѵ�.
	void SmoothTerrainHeight(const STParameters &parameters);

	//! ���� �޽��� �����Ѵ�
	LPD3DXMESH CreateTerrainMesh(const STParameters &parameters);

	//! ���� �ؽ�ó�� �����Ѵ�
	std::vector<LPDIRECT3DTEXTURE9> CreateTerrainTextures(const STParameters &parameters, LPDIRECT3DTEXTURE9 *outSplatTexture);


private:			// private ����

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
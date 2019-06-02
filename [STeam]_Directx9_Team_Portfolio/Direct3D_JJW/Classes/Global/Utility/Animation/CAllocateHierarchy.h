#pragma once

#include "../../Define/KGlobalDefine.h"


//! 계층 구조 할당자
class CAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:

	//! 본
	struct STBone : public D3DXFRAME
	{
		D3DXMATRIXA16 combineMatrix;
		float firstHeight;
	};

	//! 메시 컨테이너
	struct STMeshContainer : public D3DXMESHCONTAINER
	{
		DWORD numBlends;
		LPD3DXMESH skinnedMesh;

		std::vector<STBone *> boneList;
		std::vector<D3DXMATRIXA16> boneMatrixList;
		std::vector<LPDIRECT3DTEXTURE9> textureList;
		std::vector<D3DXBONECOMBINATION> boneCombinationList;
	};

	//! 매개변수
	struct STParameters
	{
		std::string basePath;
		std::function<LPD3DXMESH(LPD3DXMESHCONTAINER, int) > skinnedMeshCreator;
	};

public:			// 생성자

	//! 생성자
	explicit CAllocateHierarchy(const STParameters & parameters);

public:			// 인터페이스 구현

	//! 프레임을 생성한다
	virtual HRESULT CALLBACK CreateFrame(const char *name, LPD3DXFRAME *newFrame) override;

	//! 메시 컨테이너를 생성한다
	virtual HRESULT CALLBACK CreateMeshContainer(const char* name,
		const D3DXMESHDATA *meshData,
		const D3DXMATERIAL *materials,
		const D3DXEFFECTINSTANCE *effectInstances,
		DWORD numMaterials,
		const DWORD *adjacency,
		LPD3DXSKININFO skinInfo,
		LPD3DXMESHCONTAINER *newMeshContainer) override;

	//! 프레임을 제거한다
	virtual HRESULT CALLBACK DestroyFrame(LPD3DXFRAME frameToFree) override;

	//! 메시 컨테이너를 제거한다
	virtual HRESULT CALLBACK DestroyMeshContainer(LPD3DXMESHCONTAINER meshContainerToFree) override;

private:			// private 변수

	int _numMeshContainers = 0;
	STParameters _parameters;
};
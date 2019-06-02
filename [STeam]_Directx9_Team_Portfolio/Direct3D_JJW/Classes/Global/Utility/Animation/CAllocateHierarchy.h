#pragma once

#include "../../Define/KGlobalDefine.h"


//! ���� ���� �Ҵ���
class CAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:

	//! ��
	struct STBone : public D3DXFRAME
	{
		D3DXMATRIXA16 combineMatrix;
		float firstHeight;
	};

	//! �޽� �����̳�
	struct STMeshContainer : public D3DXMESHCONTAINER
	{
		DWORD numBlends;
		LPD3DXMESH skinnedMesh;

		std::vector<STBone *> boneList;
		std::vector<D3DXMATRIXA16> boneMatrixList;
		std::vector<LPDIRECT3DTEXTURE9> textureList;
		std::vector<D3DXBONECOMBINATION> boneCombinationList;
	};

	//! �Ű�����
	struct STParameters
	{
		std::string basePath;
		std::function<LPD3DXMESH(LPD3DXMESHCONTAINER, int) > skinnedMeshCreator;
	};

public:			// ������

	//! ������
	explicit CAllocateHierarchy(const STParameters & parameters);

public:			// �������̽� ����

	//! �������� �����Ѵ�
	virtual HRESULT CALLBACK CreateFrame(const char *name, LPD3DXFRAME *newFrame) override;

	//! �޽� �����̳ʸ� �����Ѵ�
	virtual HRESULT CALLBACK CreateMeshContainer(const char* name,
		const D3DXMESHDATA *meshData,
		const D3DXMATERIAL *materials,
		const D3DXEFFECTINSTANCE *effectInstances,
		DWORD numMaterials,
		const DWORD *adjacency,
		LPD3DXSKININFO skinInfo,
		LPD3DXMESHCONTAINER *newMeshContainer) override;

	//! �������� �����Ѵ�
	virtual HRESULT CALLBACK DestroyFrame(LPD3DXFRAME frameToFree) override;

	//! �޽� �����̳ʸ� �����Ѵ�
	virtual HRESULT CALLBACK DestroyMeshContainer(LPD3DXMESHCONTAINER meshContainerToFree) override;

private:			// private ����

	int _numMeshContainers = 0;
	STParameters _parameters;
};
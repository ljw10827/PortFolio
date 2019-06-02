#include "CAllocateHierarchy.h"
#include "../Manager/CResourceManager.h"

CAllocateHierarchy::CAllocateHierarchy(const STParameters & parameters)
	:
	_parameters(parameters)
{
}

HRESULT CAllocateHierarchy::CreateFrame(const char * name, LPD3DXFRAME * newFrame)
{
	auto frame = new STBone();

	if (name != nullptr) {
		frame->Name = new char[strlen(name) + 1];
		strcpy(frame->Name, name);

		printf("Name: %s\n", name);
	}

	D3DXMatrixIdentity(&frame->combineMatrix);
	D3DXMatrixIdentity(&frame->TransformationMatrix);

	*newFrame = frame;

	return S_OK;
}

HRESULT CAllocateHierarchy::CreateMeshContainer(const char * name,
	const D3DXMESHDATA * meshData,
	const D3DXMATERIAL * materials,
	const D3DXEFFECTINSTANCE * effectInstances,
	DWORD numMaterials,
	const DWORD * adjacency,
	LPD3DXSKININFO skinInfo,
	LPD3DXMESHCONTAINER * newMeshContainer)
{
	// 일반 메시가 아닐 경우
	if (meshData->Type != D3DXMESHDATATYPE::D3DXMESHTYPE_MESH) {
		return E_FAIL;
	}

	auto meshContainer = new STMeshContainer();
	meshContainer->MeshData.Type = meshData->Type;
	meshContainer->MeshData.pMesh = meshData->pMesh;
	meshContainer->MeshData.pMesh->AddRef();

	if (name != nullptr) {
		meshContainer->Name = new char[strlen(name) + 1];
		strcpy(meshContainer->Name, name);
	}

	// 재질 정보를 설정한다.
	// {
	meshContainer->NumMaterials = numMaterials;
	meshContainer->pMaterials = new D3DXMATERIAL[numMaterials];
	
	CopyMemory(meshContainer->pMaterials,
		materials,
		sizeof(D3DXMATERIAL) * numMaterials);

	for (int i = 0; i < numMaterials; ++i) {
		D3DXMATERIAL material = materials[i];
		LPDIRECT3DTEXTURE9 texture = nullptr;

		if (material.pTextureFilename != nullptr) {
			char textureFilepath[MAX_PATH] = "";

			sprintf(textureFilepath, "%s/%s",
				_parameters.basePath.c_str(),
				material.pTextureFilename);

			texture = GET_SPRITE_TEXTURE(textureFilepath);
		}
		meshContainer->textureList.push_back(texture);

	}
	//}

	// 인접 정보를 설정한다
	// {
	meshContainer->pAdjacency = new DWORD[meshData->pMesh->GetNumFaces() * 3];

	CopyMemory(meshContainer->pAdjacency,
		adjacency,
		sizeof(DWORD) * (meshData->pMesh->GetNumFaces() * 3));
	// }

	if (skinInfo != nullptr) {
		DWORD numBones = skinInfo->GetNumBones();

		for (int i = 0; i < numBones; ++i) {
			auto boneOffsetMatrix = skinInfo->GetBoneOffsetMatrix(i);
			meshContainer->boneMatrixList.push_back(*boneOffsetMatrix);
		}

		meshContainer->pSkinInfo = skinInfo;
		meshContainer->pSkinInfo->AddRef();

		_numMeshContainers += 1;
		meshContainer->skinnedMesh = _parameters.skinnedMeshCreator(meshContainer, _numMeshContainers);
	}

	*newMeshContainer = meshContainer;

	return S_OK;
}

HRESULT CAllocateHierarchy::DestroyFrame(LPD3DXFRAME frameToFree)
{
	SAFE_DELETE_ARRAY(frameToFree->Name);
	SAFE_DELETE(frameToFree);

	return S_OK;
}

HRESULT CAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER meshContainerToFree)
{
	return S_OK;
}

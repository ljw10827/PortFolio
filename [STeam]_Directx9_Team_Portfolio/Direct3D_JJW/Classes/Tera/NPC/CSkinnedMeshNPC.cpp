#include "CSkinnedMeshNPC.h"
#include "CAnimationControllerNPC.h"
#include "../../Global/Utility/Animation/CAllocateHierarchy.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Utility/Object/CCamera.h"
#include "../../Global/Utility/Manager/CResourceManager.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/Object/CLight.h"

CSkinnedMeshNPC::CSkinnedMeshNPC(const STParameters & parameters)
{
	if (parameters.meshFilepath.rfind('/') != std::string::npos) {
		size_t index = parameters.meshFilepath.rfind('/');
		_basePath = parameters.meshFilepath.substr(0, index);
	}

	_effect = GET_EFFECT(parameters.effectFilepath);
	_mesh = this->CreateSkinnedMeshFromX(parameters);
}

CSkinnedMeshNPC::~CSkinnedMeshNPC(void)
{
	SAFE_DELETE(_animationController);
}

std::vector<std::string> CSkinnedMeshNPC::getAnimationNameList(void)
{
	return _animationController->getAnimationNameList();
}
// 애니메이션 프레임간격 비율 조절
void CSkinnedMeshNPC::setTimeScale(float timeScale)
{
	_animationController->setTimeScale(timeScale);
}

void CSkinnedMeshNPC::update(void)
{
	CRenderObject::update();
	_animationController->update();

	auto worldMatrix = this->getFinalWorldMatrix();
	this->UpdateBoneMatrices(_rootFrame, worldMatrix);
}

void CSkinnedMeshNPC::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	this->DrawBone(_rootFrame);
}

void CSkinnedMeshNPC::doDrawShadow(void)
{
	CRenderObject::doDrawShadow();

	auto worldMatrix = _shadowMatrix * this->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	GET_DEVICE()->SetMaterial(&_shadowMaterial);
	_shadowMesh->DrawSubset(0);
}

void CSkinnedMeshNPC::PlayAnimation()
{

	_animationController->playAnimation();
}

void CSkinnedMeshNPC::StopAnimation(void)
{
	_animationController->stopAnimation();
}

void CSkinnedMeshNPC::UpdateBoneMatrices(LPD3DXFRAME rootFrame, const D3DXMATRIXA16 & transformMatrix)
{
	//! combineMatrix : 자신 행렬 X 부모 행렬
	//! combineMatrix는 변환행렬이 계속 누적되어서 자식으로 내려간다.

	auto bone = (CAllocateHierarchy::STBone *)rootFrame;
	bone->combineMatrix = bone->TransformationMatrix * transformMatrix;

	// 형제 본이 존재할 경우
	if (bone->pFrameSibling != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameSibling, transformMatrix);
	}

	// 자식 본이 존재할 경우
	if (bone->pFrameFirstChild != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameFirstChild, bone->combineMatrix);
	}
}

void CSkinnedMeshNPC::DrawBone(LPD3DXFRAME rootFrame)
{
	auto meshContainer = rootFrame->pMeshContainer;

	while (meshContainer != nullptr) {
		
		// 행렬을 설정한다.
		// 실제 Draw 로직전에 view, projection을 세팅한다.
		// 얘내는 애니메이션과 상관없이 변함이 없기때문에
		//{
		auto viewMatrix = GET_CAMERA()->getViewMatrix();
		auto projectionMatrix = GET_CAMERA()->getProjectionMatrix();
		
		_effect->SetMatrix("_viewMatrix", &viewMatrix);
		_effect->SetMatrix("_projectionMatrix", &projectionMatrix);
		//}

		this->DrawMeshContainer(meshContainer);
		meshContainer = meshContainer->pNextMeshContainer;
	}

	// 형제 본이 존재할 경우
	if (rootFrame->pFrameSibling != nullptr) {
		this->DrawBone(rootFrame->pFrameSibling);
	}

	// 자식 본이 존재할 경우
	if (rootFrame->pFrameFirstChild != nullptr) {
		this->DrawBone(rootFrame->pFrameFirstChild);
	}
}
/////////////////////////////// 수정 스킨이 없을 경우에는 디바이스로 그린다
void CSkinnedMeshNPC::DrawMeshContainer(LPD3DXMESHCONTAINER meshContainer)
{
	auto meshContainerC = (CAllocateHierarchy::STMeshContainer *)meshContainer;

	if (meshContainerC->pSkinInfo == nullptr) {
		GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

		for (int i = 0; i < meshContainerC->NumMaterials; ++i) {
			auto bone = meshContainerC->boneList[i];
			auto worldMatrix = bone->combineMatrix;

			D3DXMATRIXA16 rotation;
			D3DXMatrixRotationY(&rotation, D3DXToRadian(90.0f));

			worldMatrix = rotation * worldMatrix;

			GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);
			GET_DEVICE()->SetTexture(0, meshContainerC->textureList[i]);

			meshContainerC->skinnedMesh->DrawSubset(i);
		}
		GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);

	}
	else {
		for (int i = 0; i < meshContainerC->boneCombinationList.size(); ++i) {
			int numBlends = 0;
			auto boneCombination = meshContainerC->boneCombinationList[i];

			// 뼈대가중치는 총 4개 인데 다 사용하진 않는다.
			// 사용 가능한 뼈대 가중치 갯수를 탐색한다
			for (int j = 0; j < meshContainerC->numBlends; ++j) {
				if (boneCombination.BoneId[j] != UINT_MAX) {
					numBlends += 1;
				}
			}

			D3DXMATRIXA16 matrices[4];
			ZeroMemory(matrices, sizeof(matrices));

			// 본 행렬을 연산한다
			for (int j = 0; j < numBlends; ++j) {
				DWORD boneId = boneCombination.BoneId[j];

				if (boneId == UINT_MAX) continue;
				auto bone = meshContainerC->boneList[boneId];
				auto boneMatrix = meshContainerC->boneMatrixList[boneId];

				matrices[j] = boneMatrix * bone->combineMatrix;
			}

			DWORD attributeId = boneCombination.AttribId;
			if (meshContainerC->textureList.size() <= attributeId) continue;
			auto texture = meshContainerC->textureList[attributeId];

			_effect->SetVector("_viewPosition", &D3DXVECTOR4(GET_CAMERA()->getPosition(), 0.0f));
			_effect->SetVector("_lightDirection", &D3DXVECTOR4(GET_LIGHT()->getForwardDirection(), 1.0f));
			_effect->SetInt("_numBlends", numBlends);
			_effect->SetMatrixArray("_boneMatrices", matrices, numBlends);
			_effect->SetTexture("_texture", texture);

			_effect->SetTechnique("MyTechnique");

			UINT numPasses = 0;
			_effect->Begin(&numPasses, 0);

			for (int j = 0; j < numPasses; ++j) {
				_effect->BeginPass(j);

				meshContainerC->skinnedMesh->DrawSubset(i);

				_effect->EndPass();
			}

			_effect->End();
		}
	}
}

void CSkinnedMeshNPC::SetupBone(LPD3DXFRAME rootFrame)
{
	// 현재 본에 메시 컨테이너 정보가 있을 경우
	if (rootFrame->pMeshContainer != nullptr) {
		this->SetupBoneOnMeshContainer(_rootFrame, rootFrame->pMeshContainer);
	}

	// 형제 본 정보가 있을 경우
	if (rootFrame->pFrameSibling != nullptr) {
		this->SetupBone(rootFrame->pFrameSibling);
	}

	// 자식 본 정보가 있을 경우
	if (rootFrame->pFrameFirstChild != nullptr) {
		this->SetupBone(rootFrame->pFrameFirstChild);
	}
}

void CSkinnedMeshNPC::SetupBoneOnMeshContainer(LPD3DXFRAME rootFrame, LPD3DXMESHCONTAINER meshContainer)
{
	auto meshContainerC = (CAllocateHierarchy::STMeshContainer *)meshContainer;

	for (int i = 0; i < meshContainerC->pSkinInfo->GetNumBones(); ++i) {
		std::string boneName = meshContainerC->pSkinInfo->GetBoneName(i);
		auto frame = D3DXFrameFind(rootFrame, boneName.c_str());

		meshContainerC->boneList.push_back((CAllocateHierarchy::STBone * )frame);
	}
}

LPD3DXMESH CSkinnedMeshNPC::CreateSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber)
{
	LPD3DXMESH mesh = nullptr;
	auto meshContainerC = (CAllocateHierarchy::STMeshContainer *)meshContainer;

	DWORD numBlends = 0;
	DWORD numBoneCombination = 0;
	LPD3DXBUFFER boneCombinationBuffer = nullptr;

	/*
	스킨드 애니메이션의 뼈대 가중치 연산은
	최대 4개의 행렬을 가지고 각 행렬의 비율(가중치)를
	합산해서 최종적인 변환 행렬을 만들어내는 것.
	*/

	//! 스킨드 메시를 생성한다( 뼈대가중치를 계산해서 일반 메시를 스킨드메시로 변환시킨다)
	meshContainerC->pSkinInfo->ConvertToBlendedMesh(meshContainerC->MeshData.pMesh,
		D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
		meshContainerC->pAdjacency,
		meshContainerC->pAdjacency,
		nullptr,
		nullptr,
		&numBlends,
		&numBoneCombination,
		&boneCombinationBuffer,
		&mesh);
	// bonCombination : 뼈대 가중치들의 정보
	// covertToBlendedMesh를 거치면 정점정보(FVF)에 뼈대가중치(BlendWeight)가 계산되어 추가된다.

	/*
	//! 뼈대 가중치 정보를 통한 정점의 연산
		- V world =
		(V local * Matrix world * weight1) +
		(V local * Matrix world * weight2) +
		(V local * Matrix world * weight3) +
		(V local * Matrix world * weight4);
	*/

	D3DVERTEXELEMENT9 elements[] = {
		0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
		0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0,
		0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0,
		0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0,
		0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,
		0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0,
		D3DDECL_END()
	};

	auto originMesh = mesh;

	//! 메시를 생성한다
	originMesh->CloneMesh(originMesh->GetOptions(),
		elements,
		GET_DEVICE(),
		&mesh);


	// 뼈대 조합 정보를 설정한다
	// {
	for (int i = 0; i < numBoneCombination; ++i) {
		auto boneCombinations = (LPD3DXBONECOMBINATION)(boneCombinationBuffer->GetBufferPointer());

		auto boneCombination = boneCombinations[i];
		boneCombination.BoneId = new DWORD[numBlends];

		// 본 정보를 복사한다.
		CopyMemory(boneCombination.BoneId,
			boneCombinations[i].BoneId,
			sizeof(DWORD) * numBlends);

		meshContainerC->boneCombinationList.push_back(boneCombination);
	}
	// }

	SAFE_RELEASE(originMesh);
	SAFE_RELEASE(boneCombinationBuffer);

	meshContainerC->numBlends = numBlends;
	_meshContainerList.push_back(meshContainerC);

	return mesh;
}

LPD3DXMESH CSkinnedMeshNPC::CreateSkinnedMeshFromX(const STParameters & parameters)
{
	CAllocateHierarchy::STParameters allocParameters = {
		_basePath,
		std::bind(&CSkinnedMeshNPC::CreateSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
	};
	CAllocateHierarchy allocateHierarchy(allocParameters);
	LPD3DXANIMATIONCONTROLLER animationContoller = nullptr;

	// 스킨드 메시를 생성한다
	D3DXLoadMeshHierarchyFromXA(parameters.meshFilepath.c_str(),
		D3DXMESH_MANAGED,
		GET_DEVICE(),
		&allocateHierarchy,
		nullptr,
		&_rootFrame,
		&animationContoller);

	// 본 정보를 설정한다
	this->SetupBone(_rootFrame);

	_animationController = new CAnimationControllerNPC(animationContoller);

	return _meshContainerList.front()->MeshData.pMesh;
}

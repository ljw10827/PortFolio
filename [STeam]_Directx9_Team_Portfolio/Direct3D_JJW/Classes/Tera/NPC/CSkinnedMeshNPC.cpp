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
// �ִϸ��̼� �����Ӱ��� ���� ����
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
	//! combineMatrix : �ڽ� ��� X �θ� ���
	//! combineMatrix�� ��ȯ����� ��� �����Ǿ �ڽ����� ��������.

	auto bone = (CAllocateHierarchy::STBone *)rootFrame;
	bone->combineMatrix = bone->TransformationMatrix * transformMatrix;

	// ���� ���� ������ ���
	if (bone->pFrameSibling != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameSibling, transformMatrix);
	}

	// �ڽ� ���� ������ ���
	if (bone->pFrameFirstChild != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameFirstChild, bone->combineMatrix);
	}
}

void CSkinnedMeshNPC::DrawBone(LPD3DXFRAME rootFrame)
{
	auto meshContainer = rootFrame->pMeshContainer;

	while (meshContainer != nullptr) {
		
		// ����� �����Ѵ�.
		// ���� Draw �������� view, projection�� �����Ѵ�.
		// �곻�� �ִϸ��̼ǰ� ������� ������ ���⶧����
		//{
		auto viewMatrix = GET_CAMERA()->getViewMatrix();
		auto projectionMatrix = GET_CAMERA()->getProjectionMatrix();
		
		_effect->SetMatrix("_viewMatrix", &viewMatrix);
		_effect->SetMatrix("_projectionMatrix", &projectionMatrix);
		//}

		this->DrawMeshContainer(meshContainer);
		meshContainer = meshContainer->pNextMeshContainer;
	}

	// ���� ���� ������ ���
	if (rootFrame->pFrameSibling != nullptr) {
		this->DrawBone(rootFrame->pFrameSibling);
	}

	// �ڽ� ���� ������ ���
	if (rootFrame->pFrameFirstChild != nullptr) {
		this->DrawBone(rootFrame->pFrameFirstChild);
	}
}
/////////////////////////////// ���� ��Ų�� ���� ��쿡�� ����̽��� �׸���
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

			// ���밡��ġ�� �� 4�� �ε� �� ������� �ʴ´�.
			// ��� ������ ���� ����ġ ������ Ž���Ѵ�
			for (int j = 0; j < meshContainerC->numBlends; ++j) {
				if (boneCombination.BoneId[j] != UINT_MAX) {
					numBlends += 1;
				}
			}

			D3DXMATRIXA16 matrices[4];
			ZeroMemory(matrices, sizeof(matrices));

			// �� ����� �����Ѵ�
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
	// ���� ���� �޽� �����̳� ������ ���� ���
	if (rootFrame->pMeshContainer != nullptr) {
		this->SetupBoneOnMeshContainer(_rootFrame, rootFrame->pMeshContainer);
	}

	// ���� �� ������ ���� ���
	if (rootFrame->pFrameSibling != nullptr) {
		this->SetupBone(rootFrame->pFrameSibling);
	}

	// �ڽ� �� ������ ���� ���
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
	��Ų�� �ִϸ��̼��� ���� ����ġ ������
	�ִ� 4���� ����� ������ �� ����� ����(����ġ)��
	�ջ��ؼ� �������� ��ȯ ����� ������ ��.
	*/

	//! ��Ų�� �޽ø� �����Ѵ�( ���밡��ġ�� ����ؼ� �Ϲ� �޽ø� ��Ų��޽÷� ��ȯ��Ų��)
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
	// bonCombination : ���� ����ġ���� ����
	// covertToBlendedMesh�� ��ġ�� ��������(FVF)�� ���밡��ġ(BlendWeight)�� ���Ǿ� �߰��ȴ�.

	/*
	//! ���� ����ġ ������ ���� ������ ����
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

	//! �޽ø� �����Ѵ�
	originMesh->CloneMesh(originMesh->GetOptions(),
		elements,
		GET_DEVICE(),
		&mesh);


	// ���� ���� ������ �����Ѵ�
	// {
	for (int i = 0; i < numBoneCombination; ++i) {
		auto boneCombinations = (LPD3DXBONECOMBINATION)(boneCombinationBuffer->GetBufferPointer());

		auto boneCombination = boneCombinations[i];
		boneCombination.BoneId = new DWORD[numBlends];

		// �� ������ �����Ѵ�.
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

	// ��Ų�� �޽ø� �����Ѵ�
	D3DXLoadMeshHierarchyFromXA(parameters.meshFilepath.c_str(),
		D3DXMESH_MANAGED,
		GET_DEVICE(),
		&allocateHierarchy,
		nullptr,
		&_rootFrame,
		&animationContoller);

	// �� ������ �����Ѵ�
	this->SetupBone(_rootFrame);

	_animationController = new CAnimationControllerNPC(animationContoller);

	return _meshContainerList.front()->MeshData.pMesh;
}

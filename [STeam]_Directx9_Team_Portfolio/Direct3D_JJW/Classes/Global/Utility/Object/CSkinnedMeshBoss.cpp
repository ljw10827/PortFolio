#include "CSkinnedMeshBoss.h"
#include "../Animation/CAllocateHierarchyBoss.h"
#include "../Animation/CAnimationController.h"
#include "../Base/CDirect3DApplication.h"
#include "../Manager/CDeviceManager.h"
#include "../Object/CCamera.h"
#include "../Manager/CResourceManager.h"
#include "../Manager/CTimeManager.h"
#include "../Object/CLight.h"
#include "../../Function/GlobalFunction.h"
#include "../../../Tera/Map/CTeraMapManager.h"

CSkinnedMeshBoss::CSkinnedMeshBoss(const STParameters & parameters, SkinnedType skinnedType)
	:
	_rootFrameName(parameters.rootFrameName),
	_weaponFrameName(parameters.MainWeaponFrameName)
{
	if (parameters.meshFilepath.rfind('/') != std::string::npos) {
		size_t index = parameters.meshFilepath.rfind('/');
		_basePath = parameters.meshFilepath.substr(0, index);
	}

	_effect = GET_EFFECT(parameters.effectFilepath);
	_mesh = this->CreateSkinnedMeshFromX(parameters);


	// �ٿ�� ������ �����Ѵ�
	// {
	auto boundingBox = CreateBoundingBox(_mesh);
	auto boundingSphere = CreateBoundingSphere(_mesh);

	_skinnedType = skinnedType;

	_MainWeapon = parameters.MainWeaponFrameName;
	_SubWeapon = parameters.SubWeaponFrameName;
	_ThirdWeapon = parameters.ThirdWeaponFrameName;

	switch (_skinnedType)
	{
		case SkinnedType::MDooBean:
		{
			boundingBox.minPosition.y -= 10.0f;
			boundingBox.maxPosition.y -= 10.0f;
			boundingSphere.centerPosition.y -= 10.0f;
			boundingSphere.radius = 10.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.radius = 10.0f;
			boundingSphere.centerPosition.x += 5.0f;
			boundingSphere.centerPosition.y -= 5.0f;
			this->setBoundingSphereWeapon(boundingSphere);
			this->setBoundingSphereSubWeapon(boundingSphere);

			break;
		}
		case SkinnedType::MPlantMini:
		{
			boundingBox.minPosition.y -= 10.0f;
			boundingBox.maxPosition.y -= 10.0f;
			boundingSphere.centerPosition.y -= 10.0f;
			boundingSphere.radius = 20.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.radius = 15.0f;
			//boundingSphere.centerPosition.x += 5.0f;
			boundingSphere.centerPosition.y -= 10.0f;
			this->setBoundingSphereWeapon(boundingSphere);
			this->setBoundingSphereSubWeapon(boundingSphere);

			break;
		}
		case SkinnedType::MPollutedWolf:
		{
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 0.0f;
			boundingSphere.radius = 15.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.radius = 15.0f;
			boundingSphere.centerPosition.y -= 14.0f;
			//boundingSphere.centerPosition.x += 10.0f;
			//boundingSphere.centerPosition.y -= 50.0f;
			//boundingSphere.centerPosition.x += 10.0f;
			this->setBoundingSphereWeapon(boundingSphere);
			this->setBoundingSphereSubWeapon(boundingSphere);

			break;
		}
		case SkinnedType::MGhillieDhu:
		{
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 0.0f;
			boundingSphere.radius = 30.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.radius = 15.0f;
			boundingSphere.centerPosition.y -= 45.0f;
			boundingSphere.centerPosition.x += 10.0f;
			this->setBoundingSphereWeapon(boundingSphere);
			this->setBoundingSphereSubWeapon(boundingSphere);

			break;
		}
		case SkinnedType::MCraftySpider:
		{
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 0.0f;
			boundingSphere.centerPosition.x -= 10.0f;
			boundingSphere.radius = 80.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.radius = 20.0f;
			//boundingSphere.centerPosition.y -= 45.0f;
			//boundingSphere.centerPosition.x += 10.0f;
			boundingSphere.centerPosition.y -= 50.0f;
			boundingSphere.centerPosition.x += 10.0f;
			this->setBoundingSphereWeapon(boundingSphere);
			this->setBoundingSphereSubWeapon(boundingSphere);

			break;
		}
		case SkinnedType::MBasilisk:
		{
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 0.0f;
			boundingSphere.centerPosition.x -= 10.0f;
			boundingSphere.radius = 80.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.centerPosition.y -= 53.0f;
			boundingSphere.centerPosition.x -= 30.0f;
			boundingSphere.centerPosition.z += 15.0f;
			boundingSphere.radius = 65.0f;
			this->setBoundingSphereWeapon(boundingSphere);

			break;
		}
		case SkinnedType::MArgass:
		{
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 0.0f;
			boundingSphere.centerPosition.z += 20.0f;
			boundingSphere.centerPosition.x -= 0.0f;
			boundingSphere.radius = 20;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.radius = 30.0f;
			boundingSphere.centerPosition.y -= 37.0f;
			boundingSphere.centerPosition.z += 10.0f;
			boundingSphere.centerPosition.x -= 10.0f;
			this->setBoundingSphereWeapon(boundingSphere);

			//boundingSphere.radius = 10.0f;
			//boundingSphere.centerPosition.y += 50.0f;
			//this->setBoundingSphereSubWeapon(boundingSphere);

			break;
		}
		case SkinnedType::MVergos:
		{
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 30.0f;
			boundingSphere.centerPosition.z += 10.0f;
			boundingSphere.centerPosition.x += 90.0f;
			boundingSphere.radius = 300.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			boundingSphere.radius = 110.0f;
			boundingSphere.centerPosition.y -= 240.0f;
			boundingSphere.centerPosition.x += 200.0f;
			//boundingSphere.centerPosition.z += 100.0f;
			this->setBoundingSphereWeapon(boundingSphere);
			this->setBoundingSphereSubWeapon(boundingSphere);

			boundingSphere.radius = 200.0f;
			boundingSphere.centerPosition.x -= 130.0f;
			this->setBoundingSphereThirdWeapon(boundingSphere);

			break;
		}
		case SkinnedType::NCastanic:
		{
			boundingBox.minPosition.y -= 10.0f;
			boundingBox.maxPosition.y -= 10.0f;
			boundingSphere.centerPosition.y -= 10.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			break;
		}
		case SkinnedType::Player:
		{
			// ��
			boundingSphere.radius = 15.0f;
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 30.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			// �ֹ���
			boundingSphere.radius = 6.0f;
			boundingSphere.centerPosition.y += 44.0f;
			boundingSphere.centerPosition.x += 1.5f;
			this->setBoundingSphereWeapon(boundingSphere);

			// ���깫��
			boundingSphere.radius = 6.0f;
			boundingSphere.centerPosition.y -= 22.0f;
			boundingSphere.centerPosition.x += -4.5f;
			this->setBoundingSphereSubWeapon(boundingSphere);

			break;
		}
		default:
		{
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);
			break;
		}
	}

	

	

}

CSkinnedMeshBoss::~CSkinnedMeshBoss(void)
{
	SAFE_DELETE(_animationController);
}

D3DXVECTOR3 CSkinnedMeshBoss::getFollowPosition(void)
{
	auto frame = D3DXFrameFind(_rootFrame, _rootFrameName.c_str());

	auto combineMatrix = static_cast<CAllocateHierarchyBoss::STBone *>(frame)->combineMatrix;

	return D3DXVECTOR3(combineMatrix(3, 0),
		combineMatrix(3, 1),
		combineMatrix(3, 2));
}

void CSkinnedMeshBoss::setRootBonePositionY(float yPosition) {
	auto frame = D3DXFrameFind(_rootFrame, _rootFrameName.c_str());
	static_cast<CAllocateHierarchyBoss::STBone *>(frame)->TransformationMatrix(3,1) = yPosition;
}

bool CSkinnedMeshBoss::PlayingAnimationTrue(void)
{
	return _animationController->getIsPlaying();
}

std::vector<std::string> CSkinnedMeshBoss::getAnimationNameList(void)
{
	return _animationController->getAnimationNameList();
}

D3DXMATRIXA16 CSkinnedMeshBoss::getBoundingWorldMatrix(void)
{
	auto frame = D3DXFrameFind(_rootFrame, _rootFrameName.c_str());
	return static_cast<CAllocateHierarchyBoss::STBone *>(frame)->combineMatrix;
}

D3DXMATRIXA16 CSkinnedMeshBoss::getMainWeaponBoundingWorldMatrix(void)
{
	auto frame = D3DXFrameFind(_rootFrame, _MainWeapon.c_str());
	return static_cast<CAllocateHierarchyBoss::STBone *>(frame)->combineMatrix;
}

D3DXMATRIXA16 CSkinnedMeshBoss::getSubWeaponBoundingWorldMatrix(void)
{
	auto frame = D3DXFrameFind(_rootFrame, _SubWeapon.c_str());
	return static_cast<CAllocateHierarchyBoss::STBone *>(frame)->combineMatrix;
}

D3DXMATRIXA16 CSkinnedMeshBoss::getThirdWeaponBoundingWorldMatrix(void)
{
	auto frame = D3DXFrameFind(_rootFrame, _ThirdWeapon.c_str());
	return static_cast<CAllocateHierarchyBoss::STBone *>(frame)->combineMatrix;
}

void CSkinnedMeshBoss::setTimeScale(float timeScale)
{
	_animationController->setTimeScale(timeScale);
}

float CSkinnedMeshBoss::getCurrentAnimPeriod(const std::string& animName)
{
	return _animationController->getCurrentAnimPeriod(animName);
}

bool CSkinnedMeshBoss::getIsCombo(void)
{
	return _animationController->getIsCombo();
}

void CSkinnedMeshBoss::update(void)
{
	CRenderObject::update();
	_animationController->update();

	auto worldMatrix = this->getFinalWorldMatrix();
	
	// TODO 
	/*auto frame = D3DXFrameFind(_rootFrame, _rootFrameName.c_str());
	auto bone = static_cast<CAllocateHierarchyBoss::STBone *>(frame);

	auto bonePosition = D3DXVECTOR3(
		bone->TransformationMatrix(3, 0),
		bone->TransformationMatrix(3, 1),
		bone->TransformationMatrix(3, 2));
	
	auto playerPos = this->m_pParentObject->getPosition();
	auto currentHeight = ((filedMap*)GET_MAP("FieldMap"))->getHeightMapY(playerPos + bonePosition);

	bone->TransformationMatrix(3, 1) = currentHeight;*/

	this->UpdateBoneMatrices(_rootFrame, worldMatrix);

}

void CSkinnedMeshBoss::setFinalPosition(const D3DXVECTOR3 &pos) 
{
	_CPlayerFinalPos = pos;
}

void CSkinnedMeshBoss::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	this->DrawBone(_rootFrame);
}

void CSkinnedMeshBoss::doDrawShadow(void)
{
	CRenderObject::doDrawShadow();

	auto worldMatrix = _shadowMatrix * this->getBoundingWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &worldMatrix);

	GET_DEVICE()->SetMaterial(&_shadowMaterial);
	_shadowMesh->DrawSubset(0);
}

void CSkinnedMeshBoss::PlayAnimation(const std::string & animationName, bool isLoop, bool isCombo, const TAnimCallback &callback)
{
	_animationController->playAnimation(animationName, isLoop, isCombo, callback);
}

void CSkinnedMeshBoss::setCallback(const TAnimCallback2 &callback)
{
	_animationController->setCallback(callback);
}

void CSkinnedMeshBoss::StopAnimation(void)
{
	_animationController->stopAnimation();
}

void CSkinnedMeshBoss::UpdateBoneMatrices(LPD3DXFRAME rootFrame, const D3DXMATRIXA16 & transformMatrix)
{
	//! combineMatrix : �ڽ� ��� X �θ� ���
	//! combineMatrix�� ��ȯ����� ��� �����Ǿ �ڽ����� ��������.
	
	auto bone = (CAllocateHierarchyBoss::STBone *)rootFrame;
	
	// 1. ���� ��Ʈ���� �߾��̹Ƿ� ��Ʈ���� ��ġ�� �Ʒ��� ������.
	// 2. ������ = ��Ʈ�� ��ġ -  ���̰� ��ġ(��Ʈ�� ��ġ - �÷��̾� ��ġ) 
	// 3. �� �������� ���� map���� getHeight�Լ��� ���� height���� ��������
	// �޹��θ�Ʈ������ �ϼ��Ǳ����� y������ �ٲ��ش�.

	// **** �� ���� x, z�� 0, 0�϶��� y������ ����� �� ���� �����ǿ� ���� height���� + ���ش�.

	// ���ʿ� ���������� 0,0,0�̹Ƿ� 0,0,0���� �ѹ� �θ��� ��Ʈ������ �԰� ������ y���� ����
	

	bone->combineMatrix = bone->TransformationMatrix * transformMatrix;

	/* 
	������ ���� final Y�� �𸣱⶧����.. 
	���ʿ� firstHeight = 0.0f
	��)
	< 1������ >
	boneY = 10, currentHeight = 3; bone->firstHeight = 0;
	����Y = 10 + 3 - 0 = 13;

	< 2������ > -> ���ڸ� (���� �̵��̾��»�Ȳ)
	boneY = 13, currentHeight = 3; bone->firstHeight = 3;
	����Y = 13 + 3 - 3 = 13;
	�̷ν� currentHeight 3�� ��� �������� firstHeight�� ���� 
	���ߵ��� �ʾƼ� ���� boneY�� ��ġ���� 10�� �����Ǵ� ��Ȳ.


	< 3������ >  -> �� �������� ��ȭ (�ִϸ��̼� �̵�)
	boneY = 13; currentHeight = 10; bone->firstHeight = 3;
	����Y = 13 + 10 - 3 = 20;
	�̷ν� currentHeight 10�� ���� ������ġ���� 10���� +10�� �Ǿ�
	���������� 20�� ��. �� ��Ģ�� ����.

	*/
	// ******* ������ ���� ���� �ִϸ��̼ǿ� �������� �߻���.(�̷л����� �´µ�..���� ������)
	//bone->combineMatrix(3, 1) +=  currentHeight - bone->firstHeight;
	//bone->firstHeight = currentHeight;
	

	// ���� �� ������ �����ϰԵǸ� ������ Y���� �Ҿ������ 
	// height�� ���������� �����鼭 ��Ų�� ��������������.
	// �׸��� skinnedMesh�� �����ϰ��ִ� _player�� ��ġ�� ������ �Ǿ������.
	// �Ѹ���� _player->setPosition()���� ���� Height���� �����ϰ��ִµ� + 50f�� �ص� 
	// ������ �ö�����ʴ´�.. 
	// ****** ������! �����ִϸ��̼�, �����ִϸ��̼ǿ���
	// ���� �ڿ������� height���� �����Ͽ� ���� �İ���������� �������� �������濡��
	// ������ų�鿡 ���� ó���� �Ϻ�������.
	//bone->combineMatrix(3, 1) = currentHeight;
	

	// ���� ���� ������ ���
	if (bone->pFrameSibling != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameSibling, transformMatrix);
	}

	// �ڽ� ���� ������ ���
	if (bone->pFrameFirstChild != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameFirstChild, bone->combineMatrix);
	}
}

void CSkinnedMeshBoss::DrawBone(LPD3DXFRAME rootFrame)
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

void CSkinnedMeshBoss::DrawMeshContainer(LPD3DXMESHCONTAINER meshContainer)
{
	auto meshContainerC = (CAllocateHierarchyBoss::STMeshContainer *)meshContainer;

	for (int i = 0; i < meshContainerC->boneCombinationList.size(); ++i){
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
			
			auto bone = meshContainerC->boneList[boneId];
			auto boneMatrix = meshContainerC->boneMatrixList[boneId];

			matrices[j] = boneMatrix * bone->combineMatrix;
		}

		DWORD attributeId = boneCombination.AttribId;
		auto texture = meshContainerC->textureList[attributeId];
		auto normalTexture = meshContainerC->normalTextureList[attributeId];

		_effect->SetVector("_viewPosition", &D3DXVECTOR4(GET_CAMERA()->getPosition(), 0.0f));
		_effect->SetVector("_lightDirection", &D3DXVECTOR4(GET_LIGHT()->getForwardDirection(), 1.0f));
		_effect->SetInt("_numBlends", numBlends);
		_effect->SetMatrixArray("_boneMatrices", matrices, numBlends);
		_effect->SetTexture("_texture", texture);
		_effect->SetTexture("_normalTexture", normalTexture);

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

void CSkinnedMeshBoss::SetupBone(LPD3DXFRAME rootFrame)
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

void CSkinnedMeshBoss::SetupBoneOnMeshContainer(LPD3DXFRAME rootFrame, LPD3DXMESHCONTAINER meshContainer)
{
	auto meshContainerC = (CAllocateHierarchyBoss::STMeshContainer *)meshContainer;

	for (int i = 0; i < meshContainerC->pSkinInfo->GetNumBones(); ++i) {
		std::string boneName = meshContainerC->pSkinInfo->GetBoneName(i);
		auto frame = D3DXFrameFind(rootFrame, boneName.c_str());

		meshContainerC->boneList.push_back((CAllocateHierarchyBoss::STBone * )frame);

	}
}

LPD3DXMESH CSkinnedMeshBoss::CreateSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber)
{
	LPD3DXMESH mesh = nullptr;
	auto meshContainerC = (CAllocateHierarchyBoss::STMeshContainer *)meshContainer;

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

LPD3DXMESH CSkinnedMeshBoss::CreateSkinnedMeshFromX(const STParameters & parameters)
{
	CAllocateHierarchyBoss::STParameters allocParameters = {
		_basePath,
		std::bind(&CSkinnedMeshBoss::CreateSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
	};
	CAllocateHierarchyBoss allocateHierarchy(allocParameters);
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

	_animationController = new CAnimationController(animationContoller);

	return _meshContainerList.front()->MeshData.pMesh;
}

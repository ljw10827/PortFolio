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


	// 바운딩 정보를 설정한다
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
			// 몸
			boundingSphere.radius = 15.0f;
			boundingBox.minPosition.y -= 30.0f;
			boundingBox.maxPosition.y -= 30.0f;
			boundingSphere.centerPosition.y -= 30.0f;
			this->setBoundingBox(boundingBox);
			this->setBoundingSphere(boundingSphere);

			// 주무기
			boundingSphere.radius = 6.0f;
			boundingSphere.centerPosition.y += 44.0f;
			boundingSphere.centerPosition.x += 1.5f;
			this->setBoundingSphereWeapon(boundingSphere);

			// 서브무기
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
	//! combineMatrix : 자신 행렬 X 부모 행렬
	//! combineMatrix는 변환행렬이 계속 누적되어서 자식으로 내려간다.
	
	auto bone = (CAllocateHierarchyBoss::STBone *)rootFrame;
	
	// 1. 현재 루트본이 중앙이므로 루트본의 위치를 아래로 떨군다.
	// 2. 포지션 = 루트본 위치 -  차이값 위치(루트본 위치 - 플레이어 위치) 
	// 3. 위 포지션을 토대로 map에서 getHeight함수를 통해 height값을 가져온후
	// 콤바인매트릭스가 완성되기전에 y성분을 바꿔준다.

	// **** 각 본의 x, z의 0, 0일때의 y성분을 계산한 후 현재 포지션에 대한 height값을 + 해준다.

	// 최초에 본포지션이 0,0,0이므로 0,0,0에서 한번 부모의 매트릭스가 먹고 난후의 y값을 저장
	

	bone->combineMatrix = bone->TransformationMatrix * transformMatrix;

	/* 
	본들의 기존 final Y를 모르기때문에.. 
	최초에 firstHeight = 0.0f
	예)
	< 1프레임 >
	boneY = 10, currentHeight = 3; bone->firstHeight = 0;
	최종Y = 10 + 3 - 0 = 13;

	< 2프레임 > -> 제자리 (본의 이동이없는상황)
	boneY = 13, currentHeight = 3; bone->firstHeight = 3;
	최종Y = 13 + 3 - 3 = 13;
	이로써 currentHeight 3이 계속 더해져도 firstHeight로 인해 
	가중되지 않아서 최초 boneY의 위치였던 10이 유지되는 상황.


	< 3프레임 >  -> 본 포지션의 변화 (애니메이션 이동)
	boneY = 13; currentHeight = 10; bone->firstHeight = 3;
	최종Y = 13 + 10 - 3 = 20;
	이로써 currentHeight 10이 본의 기존위치였던 10에서 +10이 되어
	최종적으로 20이 됨. 그 규칙을 따라감.

	*/
	// ******* 하지만 지금 뭔가 애니메이션에 버벅임이 발생함.(이론상으론 맞는데..뭔가 빠진듯)
	//bone->combineMatrix(3, 1) +=  currentHeight - bone->firstHeight;
	//bone->firstHeight = currentHeight;
	

	// 현재 이 구문을 적용하게되면 기존의 Y값을 잃어버리고 
	// height가 고정적으로 박히면서 스킨이 완전깨져버린다.
	// 그리고 skinnedMesh를 포함하고있는 _player의 위치와 별개가 되어버린다.
	// 한마디로 _player->setPosition()으로 지금 Height값을 적용하고있는데 + 50f를 해도 
	// 땅위로 올라오질않는다.. 
	// ****** 하지만! 돌진애니메이션, 전진애니메이션에서
	// 정말 자연스럽게 height값을 참고하여 땅에 파고들지않으며 오르막길 내리막길에서
	// 전진스킬들에 대한 처리가 완벽해진다.
	//bone->combineMatrix(3, 1) = currentHeight;
	

	// 형제 본이 존재할 경우
	if (bone->pFrameSibling != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameSibling, transformMatrix);
	}

	// 자식 본이 존재할 경우
	if (bone->pFrameFirstChild != nullptr) {
		this->UpdateBoneMatrices(bone->pFrameFirstChild, bone->combineMatrix);
	}
}

void CSkinnedMeshBoss::DrawBone(LPD3DXFRAME rootFrame)
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

void CSkinnedMeshBoss::DrawMeshContainer(LPD3DXMESHCONTAINER meshContainer)
{
	auto meshContainerC = (CAllocateHierarchyBoss::STMeshContainer *)meshContainer;

	for (int i = 0; i < meshContainerC->boneCombinationList.size(); ++i){
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

LPD3DXMESH CSkinnedMeshBoss::CreateSkinnedMeshFromX(const STParameters & parameters)
{
	CAllocateHierarchyBoss::STParameters allocParameters = {
		_basePath,
		std::bind(&CSkinnedMeshBoss::CreateSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
	};
	CAllocateHierarchyBoss allocateHierarchy(allocParameters);
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

	_animationController = new CAnimationController(animationContoller);

	return _meshContainerList.front()->MeshData.pMesh;
}

#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

class CAnimationControllerNPC;

//! 스킨드 메시
class CSkinnedMeshNPC : public CRenderObject
{
public:

	//! 매개변수
	struct STParameters
	{
		std::string meshFilepath;
		std::string effectFilepath;
	};

public:			// 생성자 & 소멸자

	//! 생성자
	explicit CSkinnedMeshNPC(const STParameters &parameters);

	//! 소멸자
	virtual ~CSkinnedMeshNPC(void);
	
public:			// getter

	//! 애니메이션 이름 리스트를 반환한다
	std::vector<std::string> getAnimationNameList(void);

	//! 시간값의 비율을 정한다
	void setTimeScale(float timeScale);

public:			// public 함수

	//! 상태를 갱신한다
	virtual void update(void) override;

	//! 객체를 그린다
	virtual void doDrawObject(void) override;

	//! 그림자를 그린다
	virtual void doDrawShadow(void) override;

	//! 애니메이션을 재생한다
	void PlayAnimation();

	// 애니메이션을 중지한다.
	void StopAnimation(void);

private:		// private 함수

	//! 본 행렬을 갱신한다
	void UpdateBoneMatrices(LPD3DXFRAME rootFrame, const D3DXMATRIXA16 &transformMatrix);

	//! 본을 그린다.
	void DrawBone(LPD3DXFRAME rootFrame);

	//! 메시 컨테이너를 그린다.
	void DrawMeshContainer(LPD3DXMESHCONTAINER meshContainer);
	
	//! 본을 설정한다
	void SetupBone(LPD3DXFRAME rootFrame);

	//! 본을 메시 컨테이너에 설정한다
	void SetupBoneOnMeshContainer(LPD3DXFRAME rootFrame, LPD3DXMESHCONTAINER meshContainer);

	//! 스킨드 메시를 생성한다
	LPD3DXMESH CreateSkinnedMesh(LPD3DXMESHCONTAINER meshContainer,
		int meshContainerNumber);

	//! 메시를 생성한다
	LPD3DXMESH CreateSkinnedMeshFromX(const STParameters &parameters);

private:		// private 변수

	std::string _basePath = "";

	LPD3DXEFFECT _effect = nullptr;
	LPD3DXMESH _mesh = nullptr;
	LPD3DXFRAME _rootFrame = nullptr;
	CAnimationControllerNPC * _animationController = nullptr;

	std::vector<LPD3DXMESHCONTAINER> _meshContainerList;

};
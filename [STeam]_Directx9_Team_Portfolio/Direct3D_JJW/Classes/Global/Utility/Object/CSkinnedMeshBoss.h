#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

class CAnimationController;

//! 스킨드 메시
class CSkinnedMeshBoss : public CRenderObject
{
public:

	//! 매개변수
	struct STParameters
	{
		std::string meshFilepath;
		std::string effectFilepath;
		std::string rootFrameName;
		std::string MainWeaponFrameName;
		std::string SubWeaponFrameName;
		std::string ThirdWeaponFrameName;
	};

	// 타입 재정의
	typedef std::function<void(const std::string &)> TAnimCallback;
	typedef std::function<void(const std::string &, float)> TAnimCallback2;

public:			// 생성자 & 소멸자

	//! 생성자
	explicit CSkinnedMeshBoss(const STParameters &parameters, SkinnedType skinnedType);

	//! 소멸자
	virtual ~CSkinnedMeshBoss(void);
	
public:			// getter

	// ! 추적 위치를 반환한다
	virtual D3DXVECTOR3 getFollowPosition(void) override;

	void setRootBonePositionY(float yPosition);

	bool PlayingAnimationTrue(void);


	//! 애니메이션 이름 리스트를 반환한다
	std::vector<std::string> getAnimationNameList(void);

	//! 바운딩 월드 행렬을 반환한다
	virtual D3DXMATRIXA16 getBoundingWorldMatrix(void) override;

	

	//virtual D3DXMATRIXA16 getWeaponBoundingWorldMatrix(void) override;

	// 몬스터 구체 추가
    virtual D3DXMATRIXA16 getMainWeaponBoundingWorldMatrix(void) override;
	virtual D3DXMATRIXA16 getSubWeaponBoundingWorldMatrix(void)override;
	virtual D3DXMATRIXA16 getThirdWeaponBoundingWorldMatrix(void)override;

	//! 애니메이션 시간값을 조절한다
	void setTimeScale(float timeScale);

	//! 현재 애니메이션의 period time을 반환한다
	float getCurrentAnimPeriod(const std::string &animName);

	//! 애니메이션 컨트롤러를 반환한다
	bool getIsCombo(void);

public:			// public 함수

	//! 상태를 갱신한다
	virtual void update(void) override;

	void setFinalPosition(const D3DXVECTOR3 & pos);

	//! 객체를 그린다
	virtual void doDrawObject(void) override;

	//! 그림자를 그린다
	virtual void doDrawShadow(void) override;

	//! 애니메이션을 재생한다
	void PlayAnimation(const std::string &animationName, bool isLoop = false, bool isCombo = false, const TAnimCallback &callback = nullptr);

	void setCallback(const TAnimCallback2 & callback);

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
	std::string _rootFrameName = "";
	std::string _weaponFrameName = "";

	LPD3DXEFFECT _effect = nullptr;
	LPD3DXMESH _mesh = nullptr;
	LPD3DXMESH _weaponMesh = nullptr;
	LPD3DXFRAME _rootFrame = nullptr;
	CAnimationController * _animationController = nullptr;

	std::vector<LPD3DXMESHCONTAINER> _meshContainerList;

	TAnimCallback _callback = nullptr;

	float _firstHeight = 0.0f;

	D3DXVECTOR3 _CPlayerFinalPos;
};
#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

class CAnimationController;

//! ��Ų�� �޽�
class CSkinnedMeshBoss : public CRenderObject
{
public:

	//! �Ű�����
	struct STParameters
	{
		std::string meshFilepath;
		std::string effectFilepath;
		std::string rootFrameName;
		std::string MainWeaponFrameName;
		std::string SubWeaponFrameName;
		std::string ThirdWeaponFrameName;
	};

	// Ÿ�� ������
	typedef std::function<void(const std::string &)> TAnimCallback;
	typedef std::function<void(const std::string &, float)> TAnimCallback2;

public:			// ������ & �Ҹ���

	//! ������
	explicit CSkinnedMeshBoss(const STParameters &parameters, SkinnedType skinnedType);

	//! �Ҹ���
	virtual ~CSkinnedMeshBoss(void);
	
public:			// getter

	// ! ���� ��ġ�� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getFollowPosition(void) override;

	void setRootBonePositionY(float yPosition);

	bool PlayingAnimationTrue(void);


	//! �ִϸ��̼� �̸� ����Ʈ�� ��ȯ�Ѵ�
	std::vector<std::string> getAnimationNameList(void);

	//! �ٿ�� ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getBoundingWorldMatrix(void) override;

	

	//virtual D3DXMATRIXA16 getWeaponBoundingWorldMatrix(void) override;

	// ���� ��ü �߰�
    virtual D3DXMATRIXA16 getMainWeaponBoundingWorldMatrix(void) override;
	virtual D3DXMATRIXA16 getSubWeaponBoundingWorldMatrix(void)override;
	virtual D3DXMATRIXA16 getThirdWeaponBoundingWorldMatrix(void)override;

	//! �ִϸ��̼� �ð����� �����Ѵ�
	void setTimeScale(float timeScale);

	//! ���� �ִϸ��̼��� period time�� ��ȯ�Ѵ�
	float getCurrentAnimPeriod(const std::string &animName);

	//! �ִϸ��̼� ��Ʈ�ѷ��� ��ȯ�Ѵ�
	bool getIsCombo(void);

public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	void setFinalPosition(const D3DXVECTOR3 & pos);

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	//! �׸��ڸ� �׸���
	virtual void doDrawShadow(void) override;

	//! �ִϸ��̼��� ����Ѵ�
	void PlayAnimation(const std::string &animationName, bool isLoop = false, bool isCombo = false, const TAnimCallback &callback = nullptr);

	void setCallback(const TAnimCallback2 & callback);

	// �ִϸ��̼��� �����Ѵ�.
	void StopAnimation(void);


private:		// private �Լ�

	//! �� ����� �����Ѵ�
	void UpdateBoneMatrices(LPD3DXFRAME rootFrame, const D3DXMATRIXA16 &transformMatrix);

	//! ���� �׸���.
	void DrawBone(LPD3DXFRAME rootFrame);

	//! �޽� �����̳ʸ� �׸���.
	void DrawMeshContainer(LPD3DXMESHCONTAINER meshContainer);
	
	//! ���� �����Ѵ�
	void SetupBone(LPD3DXFRAME rootFrame);

	//! ���� �޽� �����̳ʿ� �����Ѵ�
	void SetupBoneOnMeshContainer(LPD3DXFRAME rootFrame, LPD3DXMESHCONTAINER meshContainer);

	//! ��Ų�� �޽ø� �����Ѵ�
	LPD3DXMESH CreateSkinnedMesh(LPD3DXMESHCONTAINER meshContainer,
		int meshContainerNumber);

	//! �޽ø� �����Ѵ�
	LPD3DXMESH CreateSkinnedMeshFromX(const STParameters &parameters);

private:		// private ����

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
#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

class CAnimationControllerNPC;

//! ��Ų�� �޽�
class CSkinnedMeshNPC : public CRenderObject
{
public:

	//! �Ű�����
	struct STParameters
	{
		std::string meshFilepath;
		std::string effectFilepath;
	};

public:			// ������ & �Ҹ���

	//! ������
	explicit CSkinnedMeshNPC(const STParameters &parameters);

	//! �Ҹ���
	virtual ~CSkinnedMeshNPC(void);
	
public:			// getter

	//! �ִϸ��̼� �̸� ����Ʈ�� ��ȯ�Ѵ�
	std::vector<std::string> getAnimationNameList(void);

	//! �ð����� ������ ���Ѵ�
	void setTimeScale(float timeScale);

public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	//! �׸��ڸ� �׸���
	virtual void doDrawShadow(void) override;

	//! �ִϸ��̼��� ����Ѵ�
	void PlayAnimation();

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

	LPD3DXEFFECT _effect = nullptr;
	LPD3DXMESH _mesh = nullptr;
	LPD3DXFRAME _rootFrame = nullptr;
	CAnimationControllerNPC * _animationController = nullptr;

	std::vector<LPD3DXMESHCONTAINER> _meshContainerList;

};
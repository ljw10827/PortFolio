#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Interface/IUpdateable.h"

//! �ִϸ��̼� ��Ʈ�ѷ�
class CAnimationControllerNPC : public IUpdateable
{
public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter, setter

	//! �ִϸ��̼� �̸��� ��ȯ�Ѵ�
	std::vector<std::string> getAnimationNameList(void);

	//! �ð� ������ �����Ѵ�
	void setTimeScale(float a_fTimeScale);

public:			// public �Լ�

	//! �ִϸ��̼��� �����Ѵ�
	void playAnimation();

	//! �ִϸ��̼��� �����Ѵ�
	void stopAnimation(void);

public:			// ������

	//! ������
	CAnimationControllerNPC(LPD3DXANIMATIONCONTROLLER a_pAnimationController);

	//! �Ҹ���
	virtual ~CAnimationControllerNPC(void);

private:			// private �Լ�

	//! �ִϸ��̼��� �����Ѵ�
	void doPlayAnimation(LPD3DXANIMATIONSET a_pAnimationSet, bool a_bIsLoop);

private:			// private ����

	bool m_bIsLoop = false;
	bool m_bIsPlaying = false;

	float m_fTimeScale = 0.0f;
	float m_fMixedTime = 0.0f;
	float m_fLeftMixedTime = 0.0f;

	float _changeAnimSetTime = 0.0f;
	bool _isChangeAnimSet = false;

	LPD3DXANIMATIONSET m_pAnimationSet = nullptr;
	LPD3DXANIMATIONSET m_pNextAnimationSet = nullptr;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController = nullptr;

	std::vector<std::string> m_oAnimationNameList;
	std::unordered_map<std::string, LPD3DXANIMATIONSET> m_oAnimationSetList;
};

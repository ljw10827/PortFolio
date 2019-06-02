#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Interface/IUpdateable.h"

//! 애니메이션 컨트롤러
class CAnimationControllerNPC : public IUpdateable
{
public:			// 인터페이스 구현

	//! 상태를 갱신한다
	virtual void update(void) override;

public:			// getter, setter

	//! 애니메이션 이름을 반환한다
	std::vector<std::string> getAnimationNameList(void);

	//! 시간 비율을 변경한다
	void setTimeScale(float a_fTimeScale);

public:			// public 함수

	//! 애니메이션을 시작한다
	void playAnimation();

	//! 애니메이션을 중지한다
	void stopAnimation(void);

public:			// 생성자

	//! 생성자
	CAnimationControllerNPC(LPD3DXANIMATIONCONTROLLER a_pAnimationController);

	//! 소멸자
	virtual ~CAnimationControllerNPC(void);

private:			// private 함수

	//! 애니메이션을 시작한다
	void doPlayAnimation(LPD3DXANIMATIONSET a_pAnimationSet, bool a_bIsLoop);

private:			// private 변수

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

#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! 애니메이션 컨트롤러
class CAnimationController : public IUpdateable
{
public:			// 인터페이스 구현

	// 타입 재정의
	typedef std::function<void(const std::string &animationName)> TAnimCallback;
	typedef std::function<void(const std::string &, float)> TAnimCallback2;

	//! 상태를 갱신한다
	virtual void update(void) override;

public:			// getter, setter

	//! 애니메이션 이름을 반환한다
	std::vector<std::string> getAnimationNameList(void);

	//! 시간 비율을 변경한다
	void setTimeScale(float a_fTimeScale);

	//! 현재 애니메이션의 period time을 반환한다
	float getCurrentAnimPeriod(const std::string &animName);

	//! combo 상태를 반환한다
	bool getIsCombo(void);

	// 콜백
	void setCallback(const TAnimCallback2 &callback);

	bool getIsPlaying(void) { return m_bIsPlaying; }

public:			// public 함수

	//! 애니메이션을 시작한다
	void playAnimation(const std::string &a_rAnimationName, bool a_bIsLoop = false, bool isCombo = false, const TAnimCallback &callback = nullptr);

	//! 애니메이션을 중지한다
	void stopAnimation(void);

public:			// 생성자

	//! 생성자
	CAnimationController(LPD3DXANIMATIONCONTROLLER a_pAnimationController);

	//! 소멸자
	virtual ~CAnimationController(void);

private:			// private 함수

	//! 애니메이션을 시작한다
	void doPlayAnimation(LPD3DXANIMATIONSET a_pAnimationSet, bool a_bIsLoop, bool isCombo);

private:			// private 변수

	bool m_bIsLoop = false;
	bool m_bIsPlaying = false;
	
	bool _isCombo = false;
	float _comboDelayTime = 0.0f;

	float m_fTimeScale = 0.0f;
	float m_fMixedTime = 0.0f;
	float m_fLeftMixedTime = 0.0f;

	LPD3DXANIMATIONSET m_pAnimationSet = nullptr;
	LPD3DXANIMATIONSET m_pNextAnimationSet = nullptr;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController = nullptr;

	std::vector<std::string> m_oAnimationNameList;
	std::unordered_map<std::string, LPD3DXANIMATIONSET> m_oAnimationSetList;

	TAnimCallback _callback = nullptr;

	DOUBLE _currentAnimPeriod = 0.0f;

	TAnimCallback2 _callback2 = nullptr;
};

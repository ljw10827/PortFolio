#include "CAnimationControllerNPC.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Function/GlobalFunction.h"

CAnimationControllerNPC::CAnimationControllerNPC(LPD3DXANIMATIONCONTROLLER a_pAnimationController)
:
m_fTimeScale(1.0f),
m_pAnimationController(a_pAnimationController)
{
	int nNumAnimationSets = a_pAnimationController->GetNumAnimationSets();

	for(int i = 0; i < nNumAnimationSets; ++i) {
		LPD3DXANIMATIONSET pAnimationSet = nullptr;
		a_pAnimationController->GetAnimationSet(i, &pAnimationSet);

		std::string oAnimationName = pAnimationSet->GetName();

		m_oAnimationNameList.push_back(oAnimationName);
		m_oAnimationSetList.insert(decltype(m_oAnimationSetList)::value_type(oAnimationName, pAnimationSet));
	}
}

CAnimationControllerNPC::~CAnimationControllerNPC(void)
{
	for(auto &rValueType : m_oAnimationSetList) {
		SAFE_RELEASE(rValueType.second);
	}

	SAFE_RELEASE(m_pAnimationController);
}

void CAnimationControllerNPC::update(void)
{
	if(m_bIsPlaying) {
		float fDeltaTime = m_fTimeScale * GET_DELTA_TIME();

		// 다음 애니메이션이 있을 경우
		if(m_pNextAnimationSet != nullptr) {
			m_fLeftMixedTime -= fDeltaTime;

			// 애니메이션을 전환 중 일 경우
			if(m_fLeftMixedTime > 0.0f) {
				float fWeightA = m_fLeftMixedTime / m_fMixedTime;
				float fWeightB = 1.0f - fWeightA;

				m_pAnimationController->SetTrackWeight(0, fWeightA);
				m_pAnimationController->SetTrackWeight(1, fWeightB);
			} else {
				bool bIsLoop = m_bIsLoop;
				auto pAnimationSet = m_pNextAnimationSet;
			
				D3DXTRACK_DESC stTrackDesc;
				m_pAnimationController->GetTrackDesc(1, &stTrackDesc);

				this->stopAnimation();
				this->doPlayAnimation(pAnimationSet, bIsLoop);
				
				m_pAnimationController->SetTrackPosition(0, stTrackDesc.Position);
				m_pAnimationController->SetTrackAnimationSet(0, pAnimationSet);
			}
			// 애니메이션 속도조절
			m_pAnimationController->AdvanceTime(fDeltaTime, nullptr);
		} else {
			D3DXTRACK_DESC stTrackDesc;
			m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

			float fPercent = stTrackDesc.Position / m_pAnimationSet->GetPeriod();

			// 애니메이션이 진행 중 일 경우
			if(m_bIsLoop || fPercent <= 1.0f) {
				// 애니메이션 속도조절
				m_pAnimationController->AdvanceTime(fDeltaTime, nullptr);
			} else {
				this->stopAnimation();
				_changeAnimSetTime = 0.000000f;
			}
		}
	}
}

std::vector<std::string> CAnimationControllerNPC::getAnimationNameList(void)
{
	return m_oAnimationNameList;
}

void CAnimationControllerNPC::setTimeScale(float a_fTimeScale)
{
	m_fTimeScale = a_fTimeScale;
}
// NPC  playAnimation은 완전히 다름
// 가지고있는 애니메이션셋중에 랜덤으로 실행함
// 기본적으로는 wait라는 애니메이션을 실행하다가
// 랜덤시간에 따라 다른 모션으로 바뀜
void CAnimationControllerNPC::playAnimation()
{
	if (_changeAnimSetTime == 0.000000f) {
		this->doPlayAnimation(m_oAnimationSetList.find("wait")->second, true);
		_isChangeAnimSet = false;
	}
	else if ((_changeAnimSetTime >= CreateFloatRandomValue(10.0f, 20.0f)) && !_isChangeAnimSet) {
		auto animCount = m_oAnimationSetList.size()-1;
		int animNumber = CreateIntRandomValue(0, animCount);
		std::string randomAnimName = m_oAnimationNameList[animNumber];

		while (randomAnimName.c_str() == "wait" || randomAnimName.c_str() == "walk") {
			animNumber = CreateIntRandomValue(0, animCount);
			randomAnimName = m_oAnimationNameList[animNumber];
		}

		this->doPlayAnimation(m_oAnimationSetList.find(randomAnimName)->second, false);
		_isChangeAnimSet = true;
	}
	_changeAnimSetTime += GET_DELTA_TIME();

}

void CAnimationControllerNPC::stopAnimation(void)
{
	m_bIsLoop = false;
	m_bIsPlaying = false;
	m_pAnimationSet = nullptr;
	m_pNextAnimationSet = nullptr;

	m_pAnimationController->SetTrackPosition(0, 0.0f);
	m_pAnimationController->SetTrackAnimationSet(0, nullptr);

	m_pAnimationController->SetTrackEnable(1, false);
	m_pAnimationController->SetTrackPosition(1, 0.0f);
	m_pAnimationController->SetTrackAnimationSet(1, nullptr);
}

void CAnimationControllerNPC::doPlayAnimation(LPD3DXANIMATIONSET a_pAnimationSet, bool a_bIsLoop)
{
	if(!m_bIsPlaying) {
		m_pAnimationSet = a_pAnimationSet;
		m_pNextAnimationSet = nullptr;
		
		m_pAnimationController->SetTrackWeight(0, 1.0f);
		m_pAnimationController->SetTrackPosition(0, 0.0f);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
	} else if(m_pNextAnimationSet != a_pAnimationSet) {
		m_fMixedTime = 0.15f;
		m_pNextAnimationSet = a_pAnimationSet;

		// 현재 애니메이션과 다를 경우
		if(m_pAnimationSet != a_pAnimationSet) {
			m_fLeftMixedTime = m_fMixedTime;

			m_pAnimationController->SetTrackWeight(1, 0.0f);
			m_pAnimationController->SetTrackPosition(1, 0.0f);
		} else {
			// 애니메이션을 전환 중 일 경우
			if(m_fLeftMixedTime > 0.0f) {
				m_pAnimationController->SetTrackPosition(1, 0.0f);
			} else {
				D3DXTRACK_DESC stTrackDesc;
				m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

				m_pAnimationController->SetTrackPosition(1, stTrackDesc.Position);
			}

			m_fLeftMixedTime = 0.0f;
			m_pAnimationController->SetTrackWeight(1, 1.0f);
		}

		m_pAnimationController->SetTrackEnable(1, true);
		m_pAnimationController->SetTrackAnimationSet(1, m_pNextAnimationSet);
	}

	m_bIsLoop = a_bIsLoop;
	m_bIsPlaying = true;
}

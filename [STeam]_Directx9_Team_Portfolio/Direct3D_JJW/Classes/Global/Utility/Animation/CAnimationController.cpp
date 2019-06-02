#include "CAnimationController.h"
#include "../Manager/CTimeManager.h"

CAnimationController::CAnimationController(LPD3DXANIMATIONCONTROLLER a_pAnimationController)
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

CAnimationController::~CAnimationController(void)
{
	for(auto &rValueType : m_oAnimationSetList) {
		SAFE_RELEASE(rValueType.second);
	}

	SAFE_RELEASE(m_pAnimationController);
}

void CAnimationController::update(void)
{
	if(m_bIsPlaying) {
		float fDeltaTime = m_fTimeScale * GET_DELTA_TIME();

		// 다음 애니메이션이 생겼을 경우
		if (m_pNextAnimationSet != nullptr) {
			
			//-------------- 애니메이션을 자연스럽게 섞는 과정
			m_fLeftMixedTime -= fDeltaTime;

			// 애니메이션을 전환 중 일 경우
			if (m_fLeftMixedTime > 0.0f) {
				float fWeightA = m_fLeftMixedTime / m_fMixedTime;
				float fWeightB = 1.0f - fWeightA;

				m_pAnimationController->SetTrackWeight(0, fWeightA);
				m_pAnimationController->SetTrackWeight(1, fWeightB);
			}
			else {
				// 애니메이션을 전환 하는 과정
				bool bIsLoop = m_bIsLoop;
				auto pAnimationSet = m_pNextAnimationSet;

				D3DXTRACK_DESC stTrackDesc;
				m_pAnimationController->GetTrackDesc(1, &stTrackDesc);

				this->stopAnimation();
				this->doPlayAnimation(pAnimationSet, bIsLoop, _isCombo);

				m_pAnimationController->SetTrackPosition(0, stTrackDesc.Position);
				m_pAnimationController->SetTrackAnimationSet(0, pAnimationSet);
			}

			m_pAnimationController->AdvanceTime(fDeltaTime, nullptr);
		}
		// 다음 애니메이션이 없을경우
		else {

			// 0번 트랙에 있는 애니메이션을 플레이 시켜라
			std::string animationName = m_pAnimationSet->GetName();

			D3DXTRACK_DESC stTrackDesc;
			m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

			float fPercent = stTrackDesc.Position / m_pAnimationSet->GetPeriod();

			// 애니메이션이 진행 중 일 경우
			if (m_bIsLoop || fPercent <= 0.97f) {
				m_pAnimationController->AdvanceTime(fDeltaTime, nullptr);
				_currentAnimPeriod = m_pAnimationSet->GetPeriod();

				if (_callback2 != nullptr) {
					_callback2(animationName, fPercent);
				}
			}
			else {
				this->stopAnimation();
				if (_callback != nullptr) {
					_callback(animationName);
				}

			}
		}
	}
}

std::vector<std::string> CAnimationController::getAnimationNameList(void)
{
	return m_oAnimationNameList;
}

void CAnimationController::setTimeScale(float a_fTimeScale)
{
	m_fTimeScale = a_fTimeScale;
}

float CAnimationController::getCurrentAnimPeriod(const std::string & animName)
{
	auto oIterator = m_oAnimationSetList.find(animName);

	if (oIterator != m_oAnimationSetList.end()) {
		return (float)oIterator->second->GetPeriod();
	}
}

bool CAnimationController::getIsCombo(void)
{
	return _isCombo;
}

void CAnimationController::setCallback(const TAnimCallback2 & callback)
{
	_callback2 = callback;

}

void CAnimationController::playAnimation(const std::string & a_rAnimationName, bool a_bIsLoop, bool isCombo, const TAnimCallback &callback)
{
	_callback = callback;
	auto oIterator = m_oAnimationSetList.find(a_rAnimationName);

	if(oIterator != m_oAnimationSetList.end()) {
		this->doPlayAnimation(oIterator->second, a_bIsLoop, isCombo);
	}
}

void CAnimationController::stopAnimation(void)
{
	_callback2 = nullptr;
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

void CAnimationController::doPlayAnimation(LPD3DXANIMATIONSET a_pAnimationSet, bool a_bIsLoop, bool isCombo)
{

	// 애니메이션이 플레이중이 아니라면(멈춰있는 상태라면)
	if(!m_bIsPlaying) {
		m_pAnimationSet = a_pAnimationSet;
		m_pNextAnimationSet = nullptr;

		m_pAnimationController->SetTrackWeight(0, 1.0f);
		m_pAnimationController->SetTrackPosition(0, 0.0f);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
	} 
	// 애니메이션이 플레이중이고 다음 애니메이션과 플레이해야할 애니메이션이 다를경우
	else if(m_pNextAnimationSet != a_pAnimationSet) {
		m_fMixedTime = 0.15f;
		m_pNextAnimationSet = a_pAnimationSet;

		// 현재 애니메이션 != 플레이해야할 애니메이션
		if(m_pAnimationSet != a_pAnimationSet) {
			m_fLeftMixedTime = m_fMixedTime;

			m_pAnimationController->SetTrackWeight(1, 0.0f);
			m_pAnimationController->SetTrackPosition(1, 0.0f);
		} 
		// 현재 애니메이션 = 플레이해야할 애니메이션
		else {
			// 애니메이션을 전환 중 일 경우
			if(m_fLeftMixedTime > 0.0f) {
				m_pAnimationController->SetTrackPosition(1, 0.0f);
			} 
			else {
				D3DXTRACK_DESC stTrackDesc;
				m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

				m_pAnimationController->SetTrackPosition(1, stTrackDesc.Position);
			}

			m_fLeftMixedTime = 0.0f;
			m_pAnimationController->SetTrackWeight(1, 1.0f);
		}

		// 다음 애니메이션을 활성화 시킨다.
		m_pAnimationController->SetTrackEnable(1, true);
		m_pAnimationController->SetTrackAnimationSet(1, m_pNextAnimationSet);
	}

	// 애니메이션이 플레이중이고 다음 애니메이션과 플레이해야할 애니메이션이 같으면 
	// Do Nothing
	
	m_bIsLoop = a_bIsLoop;
	m_bIsPlaying = true;
}

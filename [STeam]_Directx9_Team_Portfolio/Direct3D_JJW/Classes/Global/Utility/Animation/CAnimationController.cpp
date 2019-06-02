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

		// ���� �ִϸ��̼��� ������ ���
		if (m_pNextAnimationSet != nullptr) {
			
			//-------------- �ִϸ��̼��� �ڿ������� ���� ����
			m_fLeftMixedTime -= fDeltaTime;

			// �ִϸ��̼��� ��ȯ �� �� ���
			if (m_fLeftMixedTime > 0.0f) {
				float fWeightA = m_fLeftMixedTime / m_fMixedTime;
				float fWeightB = 1.0f - fWeightA;

				m_pAnimationController->SetTrackWeight(0, fWeightA);
				m_pAnimationController->SetTrackWeight(1, fWeightB);
			}
			else {
				// �ִϸ��̼��� ��ȯ �ϴ� ����
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
		// ���� �ִϸ��̼��� �������
		else {

			// 0�� Ʈ���� �ִ� �ִϸ��̼��� �÷��� ���Ѷ�
			std::string animationName = m_pAnimationSet->GetName();

			D3DXTRACK_DESC stTrackDesc;
			m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

			float fPercent = stTrackDesc.Position / m_pAnimationSet->GetPeriod();

			// �ִϸ��̼��� ���� �� �� ���
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

	// �ִϸ��̼��� �÷������� �ƴ϶��(�����ִ� ���¶��)
	if(!m_bIsPlaying) {
		m_pAnimationSet = a_pAnimationSet;
		m_pNextAnimationSet = nullptr;

		m_pAnimationController->SetTrackWeight(0, 1.0f);
		m_pAnimationController->SetTrackPosition(0, 0.0f);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
	} 
	// �ִϸ��̼��� �÷������̰� ���� �ִϸ��̼ǰ� �÷����ؾ��� �ִϸ��̼��� �ٸ����
	else if(m_pNextAnimationSet != a_pAnimationSet) {
		m_fMixedTime = 0.15f;
		m_pNextAnimationSet = a_pAnimationSet;

		// ���� �ִϸ��̼� != �÷����ؾ��� �ִϸ��̼�
		if(m_pAnimationSet != a_pAnimationSet) {
			m_fLeftMixedTime = m_fMixedTime;

			m_pAnimationController->SetTrackWeight(1, 0.0f);
			m_pAnimationController->SetTrackPosition(1, 0.0f);
		} 
		// ���� �ִϸ��̼� = �÷����ؾ��� �ִϸ��̼�
		else {
			// �ִϸ��̼��� ��ȯ �� �� ���
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

		// ���� �ִϸ��̼��� Ȱ��ȭ ��Ų��.
		m_pAnimationController->SetTrackEnable(1, true);
		m_pAnimationController->SetTrackAnimationSet(1, m_pNextAnimationSet);
	}

	// �ִϸ��̼��� �÷������̰� ���� �ִϸ��̼ǰ� �÷����ؾ��� �ִϸ��̼��� ������ 
	// Do Nothing
	
	m_bIsLoop = a_bIsLoop;
	m_bIsPlaying = true;
}

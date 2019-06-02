#include "CTimeManager.h"

void CTimeManager::init(void)
{
	m_oPrevTimePoint = std::chrono::system_clock::now();
	m_oStartTimePoint = std::chrono::system_clock::now();
}
void CTimeManager::update(void)
{
	auto oCurrentTimePoint = std::chrono::system_clock::now();

	m_fDeltaTime = this->calculateDeltaTime(oCurrentTimePoint, m_oPrevTimePoint);
	m_fRunningTime = this->calculateDeltaTime(oCurrentTimePoint, m_oStartTimePoint);

	m_oPrevTimePoint = oCurrentTimePoint;
}

float CTimeManager::getDeltaTime(void)
{
	return m_fDeltaTime;
}

float CTimeManager::getRunningTime(void)
{
	return m_fRunningTime;
}


float CTimeManager::calculateDeltaTime(const TTimePoint & a_rCurrentTimePoint, const TTimePoint & a_rPrevTimePoint)
{
	
	return std::chrono::duration<float>(a_rCurrentTimePoint - a_rPrevTimePoint).count();
}

#include "CSchedulerManager.h"
#include "CTimeManager.h"

void CSchedulerManager::init(void)
{

}
void CSchedulerManager::update(void)
{
	for (auto &iterator : _scheduleList) {

		iterator.executeTime -= GET_DELTA_TIME();

		// 콜백 호출 시간이 다되었는가?  
		if(iterator.executeTime <= 0.0f && !iterator.isCompleteTime){
			iterator.isCompleteTime = true;
			iterator.callback();
		}
		else if (iterator.isCompleteTime && iterator.executeTime <= -5.0f) {
			this->RemoveScheule();
		}
	}
}

void CSchedulerManager::setScheduler(float executeTime, std::function<void(void)> callback)
{
	STScheduleData scheduleData = {
		executeTime,
		callback,
		false
	};

	_scheduleList.push_back(scheduleData);
}

void CSchedulerManager::RemoveScheule(void)
{
	auto iterator = _scheduleList.begin();

	while (iterator != _scheduleList.end()) {
		if (iterator->isCompleteTime) {
			iterator = _scheduleList.erase(iterator);
		}
		else {
			++iterator;
		}
	}
}


#ifndef _ALARM_PANEL_H_
#define _ALARM_PANEL_H_

#include <FApp.h>
#include <FUi.h>
#include <FBase.h>
#include <FSystem.h>

#include "Logic/Time.h"

class TizenAlarm
{
public:
	static TizenAlarm* Instance();
	virtual ~TizenAlarm(void);

	void OnAlarmExpired(int action);

	void SetSingleAlarm(int action, int hours, int minutes);
	Tizen::Base::DateTime getAlarmTime(int hours, int minutes);
	void CancelAlarm();

private:
	TizenAlarm(void);
	void ErrorMessage(void);
	void wakeUpAction();
	void goOutAlarm(int times);

private:
	int mAction;
	static TizenAlarm* mSharedInstance;
};



#endif /* _ALARM_PANEL_H_ */

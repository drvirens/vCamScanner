
#include <FLocales.h>
#include <FShell.h> //for lockmanager

#include "AppDelegate.h"
#include "TizenAlarm.h"
#include "cocos2d.h"
#include "Logic/DelayedActionsBase.h"
#include "Logic/IntentParams.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;
using namespace Tizen::System;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Locales;
using namespace Tizen::App;
using namespace Tizen::Base::Utility;
using namespace Tizen::Shell;

#ifdef _DEBUG

#ifndef _DEBUG_TEST
#define _DEBUG_TEST 1
#endif

#else

//make sure production never gets ttest code
//#ifndef _DEBUG_TEST
//#define _DEBUG_TEST 1
//#endif

#endif

static const int GO_OUT_BATCH = 1000;
TizenAlarm* TizenAlarm::mSharedInstance = 0;
TizenAlarm* TizenAlarm::Instance() {
	if (mSharedInstance) {
		return mSharedInstance;
	}
	mSharedInstance = new TizenAlarm();
	return mSharedInstance;
}

bool GetCurrentDateTime(DateTime& dt);

bool GetCurrentDateTime(DateTime& dt)
{
	DateTime dtNow;
	LocaleManager localManager;
	result r = E_FAILURE;
	TimeZone tz;

	r = SystemTime::GetCurrentTime(UTC_TIME, dtNow);
	if (IsFailed(r))
	{
		return false;
	}
	localManager.Construct();
	tz = localManager.GetSystemTimeZone();
	dt = tz.UtcTimeToWallTime(dtNow);
	return true;
}

TizenAlarm::TizenAlarm(void) : mAction(-99) {
}

TizenAlarm::~TizenAlarm(void) {
}

Tizen::Base::DateTime TizenAlarm::getAlarmTime(int hours, int minutes) {
#ifdef _DEBUG_TEST
	Tizen::Base::DateTime start;
	bool ret = GetCurrentDateTime(start);
	if (ret == false) {
		CCLOG("ERROR : GetCurrentDateTime");
	}
	start.AddMinutes(1);
	return start;
#else

	Tizen::Base::DateTime start;
	result r = SystemTime::GetCurrentTime(WALL_TIME, start);
	if (r != E_SUCCESS) {
		AppLogDebug("Set alarm has failed. start was = %d, ERroR was = %S", GetErrorMessage(r));
	}
	else {
		AppLogDebug("Set Alarm was SUCCESSSSSSSSSSS");
	}

	int c_hour = start.GetHour();
	int c_minute = start.GetMinute();

	if (c_hour > hours || (c_hour == hours && c_minute > minutes)) {
		start.AddMonths(1);
	}

	int year = start.GetYear();
	int month = start.GetMonth();
	int day = start.GetDay();
	int hour = hours; //start.GetHour();
	int minute = minutes; //start.GetMinute();
	int second = 0;

	Tizen::Base::DateTime alarmTime;
	r = alarmTime.SetValue( year,  month,  day,  hour,  minute,  second );

	return alarmTime;
#endif
	}

void TizenAlarm::SetSingleAlarm(int action, int hours, int minutes) {

	String *str2 = null;
	DateTime currentTime;
	DateTime nextAlarmTime;

	result r = E_FAILURE;
	int cmp = 0;

	nextAlarmTime = getAlarmTime(hours, minutes);

	str2 = new (std::nothrow) String("DateTime=");
	if (str2 == null)
	{
		return;
	}
	str2->Append("'");
	str2->Append(nextAlarmTime.ToString());
	str2->Append("'");

	GetCurrentDateTime(currentTime);
	cmp = DateTime::Compare(currentTime, nextAlarmTime);
	AppLog("TizenAlarm::SetSingleAlarm nextAlarmTime = %ls currentTime = %ls",
			nextAlarmTime.ToString().GetPointer(),
			currentTime.ToString().GetPointer());

	if(cmp <= 0 && nextAlarmTime.GetYear() < 9000)
	{
		String *str = new String("Alarm : ");//DO NOT REMOVE SPACES logic depends on it
		ArrayList* pArgList = new (std::nothrow) ArrayList();
		str->Append(action);

		if (pArgList != null)
		{
			pArgList->Construct();
			pArgList->Add(str);
		}

		AppManager* pAppManager = AppManager::GetInstance();
		if (pAppManager != 0) {
			if(pAppManager->IsAppLaunchRegistered() == false) {
				AppLogDebug("App was not registered so register it");
			} else {
				AppLogDebug("APp is already registered so why register again? Bug in code?");
			}

			r = pAppManager->RegisterAppLaunch(*str2, pArgList,
									AppManager::LAUNCH_OPTION_DEFAULT);
			AppLog("TizenAlarm::RegisterAppLaunch return code %s ", GetErrorMessage(r) );
		}
	}
	if (str2 != null)
	{
		delete str2;
		str2 = null;
	}
}


void TizenAlarm::CancelAlarm() {
	result r = E_SUCCESS;
	if (Tizen::App::AppManager::GetInstance()->IsAppLaunchRegistered() ) { //we have already registered it, so cancel it
		AppLogDebug("Will call UnregisterLaunch");
	} else {
		AppLogDebug("App is NOT registered so nothing to do for cancel alarm");
	}
	r = Tizen::App::AppManager::GetInstance()->UnregisterAppLaunch();
	AppLog("UnregisterAppLaunch = %s", GetErrorMessage(r)); // E_SUCCESS
}

void TizenAlarm::OnAlarmExpired(int action) {
	AppLog("TizenAlarm::OnAlarmExpired");
	if (action == DelayedActionsBase::WakeUp) {
		wakeUpAction();
	} else if (action >= GO_OUT_BATCH && action <= GO_OUT_BATCH + 3) {
		goOutAlarm(action % GO_OUT_BATCH);
	} else {
		AppLogDebug("Alarm undefined action = %d ", action );
	}
}


void TizenAlarm::wakeUpAction() {
	AppLogDebug("TizenAlarm::wakeUpAction");

	bool isScreenOn = PowerManager::IsScreenOn();
	bool isLocked = LockManager::GetInstance()->IsLocked();
	if (isScreenOn && !isLocked) {
		AppLogDebug("TizenAlarm::wakeUpAction : SCREEN is ON and DEVICE is NOT LOCKED");

	} else {
		AppLogDebug("TizenAlarm::wakeUpAction : screen off and device locked, so bring to FOREGROUND");
		//AppManager* pAppMgr = AppManager::GetInstance();
		//pAppMgr->LaunchApplication(L"Ea48obap0R",null); //TODO: make the launch args to be wakeup
		PowerManager::TurnScreenOn();
		PowerManager::KeepScreenOnState(true,false);
	}
	//updateLocation(); //FIXME later
	IntentParams::getInstance().setMode(IntentParams::WakeUpMode);
	//Desider.alarmCall();
//
//	if(GetAppState() == RUNNING)
//				{
//	          //ShowAlarmRingingForm();
//					AppLogDebug("------ShowAlarmRingingForm");
//				}
//				else
//				{
//	//				__isAlarmLaunchedAutomatically = true;
//				}
}

void TizenAlarm::ErrorMessage(void) {
	AppLogDebug("You have one Active Alarm!!");
}


#if 0

private static void goOutAlarm(int times)
	{
		MediaPlayer mp = new MediaPlayer();
		int r_id = R.raw.go_out1;
		if(times == 2)
			r_id = R.raw.go_out2;
		else if(times == 3)
			r_id = R.raw.go_out3;
		AssetFileDescriptor desc = App.getAppContext().getResources().openRawResourceFd(r_id);
		try
		{
			mp.setDataSource(desc.getFileDescriptor(), desc.getStartOffset(), desc.getLength());
		mp.setAudioStreamType(AudioManager.STREAM_ALARM);
		mp.prepare();
		mp.start();
		} catch (Exception e) {
			//Log.e("ccc", e.getMessage());
		}
		if(times == 3)
			goOutAlarmTurnOff();
	}
	private static native void goOutAlarmTurnOff();
#endif


void TizenAlarm::goOutAlarm(int times) {
	AppLogDebug("TizenAlarm::goOutAlarm: NOT IMPLEMENTED YET");
}

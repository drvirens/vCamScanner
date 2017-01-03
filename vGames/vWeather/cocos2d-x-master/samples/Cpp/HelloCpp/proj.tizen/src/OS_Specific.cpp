#include "AppDelegate.h"

#include "Logic/IntentParams.h"
#include "Logic/System.h"
#include "Logic/Location.h"
#include "Logic/PrefetchAction.h"
#include "Extension/Platform.h"
#include "Logic/Translations.h"
#include "TizenAlarm.h"

using namespace Tizen::App;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base;

using namespace cocos2d;

static int doScanLaunchParams(void* launchParams);

void AppDelegate::doTizenApplicationDidLaunchOnConditionMet(void* launchParams) {
	AppLogDebug("AppDelegate::doTizenApplicationDidLaunchOnConditionMet");

	CCAssert(launchParams!=0, "launchParams is NULL");

	int action = doScanLaunchParams(launchParams);
	TizenAlarm* alarm = TizenAlarm::Instance();
	if (alarm != 0 && action != -1) {
		AppLogDebug("Before calling OnAlarmExpired...");
		alarm->OnAlarmExpired(action);
		AppLogDebug("AppDelegate::Called OnAlarmExpired");
		return;
	}

	AppLogDebug("AppDelegate::doTizenApplicationDidLaunchOnConditionMet : NO ACTION FOUND");
}

int doScanLaunchParams(void* launchParams) {
	AppLogDebug("AppDelegate::doScanLaunchParams");
	int action = -1;
	Tizen::Base::Collection::IList* pArguments =
			(Tizen::Base::Collection::IList*) launchParams;
	if (pArguments == 0) {
		AppLogDebug("launchParams is NULL so return");
		return action;
	}
	if (pArguments->GetCount() == 0) {
		AppLogDebug("the launchParam list is EMPTY so return");
		return action;
	}
	String* str = dynamic_cast<String*>(pArguments->GetAt(0));
	if (str == null) {
		return action;
	}
	AppLogDebug("INCOMING argument is %S", str->GetPointer());

	String alarmStr = *str;
	const String tmp("Alarm");
	if (!alarmStr.StartsWith(tmp, 0)) {
		AppLogDebug("does not starts with Alarm");
		return action;
	}

	AppLogDebug("------is Alarm");
	str->Remove(0, 8);
	if (str->GetLength() > 0) {
		result retErr = Integer::Parse(*str, action);
		if (retErr != E_SUCCESS) {
			AppLogDebug("Integer::Parse FAILED");
		}
		if (GetLastResult() == E_SUCCESS) {
			AppLogDebug("ActionId: %d", action);
		}
	}

	return action;
}

int AppDelegate::scanLaunchParams(void* launchParams) {
	AppLogDebug("AppDelegate::scanLaunchParams");
	int action = doScanLaunchParams(launchParams);
	return action;
}


double Location::getLongitude()
{
	CCLOG("DelayedActions::getLongitude");
	double longitude = 0.0;
	CCCoreLocation* loc = CCCoreLocation::getInstance();
	if (loc) {
	 longitude = (double)loc->getGpsFixedLongitude();
	}
	return longitude;
}

double Location::getLatitude()
{
  CCLOG("DelayedActions::getLatitude");
  double latitude = 0.0;
  CCCoreLocation* loc = CCCoreLocation::getInstance();
  if (loc) {
	  latitude = loc->getGpsFixedLatitude();
  }
  return latitude;
}

void MusicBox::setMaxVolume()
{
	CCLOG("MusicBos::setMaxVolume");
}

void MusicBox::restoreVolume()
{
	CCLOG("MusicBox::restoreVolume");
}

R::LangCode getDeviceLang()
{
	CCLOG("DelayedActions::getDeviceLang");
	return R::EN;

//	JniMethodInfo methodInfo;
//	if (! JniHelper::getStaticMethodInfo(methodInfo, "ua/in/chaika/Alarm/IntentParams", "getLanguage", "()I"))
//	{
//		CCLOG("Lang error");
//		return R::EN;
//	}
//
//	jint x = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
//	methodInfo.env->DeleteLocalRef(methodInfo.classID);
//
//	CCLOG("Lang recieved %d", x);
//  return static_cast<R::LangCode>(x);
}

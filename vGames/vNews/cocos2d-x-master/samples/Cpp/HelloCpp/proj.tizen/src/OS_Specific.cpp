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
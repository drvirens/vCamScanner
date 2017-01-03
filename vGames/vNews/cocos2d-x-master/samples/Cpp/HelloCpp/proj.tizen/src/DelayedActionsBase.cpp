//
//  DelayedActionsBase.mm
//  vFishJoy
//
//  Created by Virendra Shakya on 10/13/13.
//
//

#include "Logic/DelayedActionsBase.h"
#include "cocos2d.h"
#include "TizenAlarm.h"


DelayedActionsBase::DelayedActionsBase() : mAlarmHandle(0) {
  CCLOG("DelayedActionsBase::DelayedActionsBase");
}
DelayedActionsBase::~DelayedActionsBase() {
  CCLOG("DelayedActionsBase::~DelayedActionsBase");
}

/*
 	public void setAlarm(Context context, int action, int hours, int minutes) {
		if (action == DISPLAY_LABEL) {

			setStatusBarIcon(context, true);
			saveNextAlarm(context, formatDigit(hours) + ":"
					+ formatDigit(minutes));

		} else {
			AlarmManager am = (AlarmManager) context
					.getSystemService(Context.ALARM_SERVICE);
			Intent intent = new Intent(context, Planer.class);
			intent.putExtra(ACTION, action);
			PendingIntent pi = PendingIntent.getBroadcast(context, action,
					intent, PendingIntent.FLAG_CANCEL_CURRENT);

			long milisecond = getAlarmTime(hours, minutes);
//			milisecond = System.currentTimeMillis()
//					+ (4 - action) * 5000 + 5000;
//			if(action >= GO_OUT_BATCH)
//				milisecond = System.currentTimeMillis()
//						+ (action % GO_OUT_BATCH)*10000 + 5000;

			am.set(AlarmManager.RTC_WAKEUP, milisecond, pi);
			// am.set(AlarmManager.RTC_WAKEUP, getAlarmTime(hours, minutes),
			// pi);

		}
	}
 */
void DelayedActionsBase::doSetActionTime(const Action a, const Time t) {
  CCLOG("DelayedActionsBase::doSetActionTime");

  if (a == DisplayLabel) {
	  CCLOG("doSetActionTime called with action == DisplayLabel");
	  //TODO:
//	  setStatusBarIcon(context, true);
//	  saveNextAlarm(context, formatDigit(hours) + ":" + formatDigit(minutes));
	  return;
  }

	  TizenAlarm* alarm = 0;
//	  if(!mAlarmHandle) {
		  alarm = TizenAlarm::Instance(); //new TizenAlarm();
//		  mAlarmHandle = alarm;
//	  }
//	  else {
//		  alarm = static_cast<TizenAlarm*>(mAlarmHandle);
//	  }

	 if( alarm ) {
	  alarm->SetSingleAlarm(a, t.getHour(), t.getMinute());
	 }
	 else {
		 CCLOG("alarm was null so no alarm set");
	 }
}

/*
 public void cancelAlarm(Context context, int action) {
		Intent intent = new Intent(context, Planer.class);
		intent.putExtra(ACTION, action);

		PendingIntent sender = PendingIntent.getBroadcast(context, action,
				intent, PendingIntent.FLAG_CANCEL_CURRENT);
		AlarmManager alarmManager = (AlarmManager) context
				.getSystemService(Context.ALARM_SERVICE);
		alarmManager.cancel(sender);

		if (action == WAKE_UP_ACTION) {
			setStatusBarIcon(context, false);
			saveNextAlarm(context, "");
		}
	}
 */
void DelayedActionsBase::doCancelAction(const Action a) {
  CCLOG("DelayedActionsBase::doCancelAction");

  TizenAlarm* alarm = 0;
//   if(!mAlarmHandle) {
 	  alarm = TizenAlarm::Instance(); //new TizenAlarm();
// 	  mAlarmHandle = alarm;
//   }
//   else {
// 	  alarm = static_cast<TizenAlarm*>(mAlarmHandle);
//   }

   if( alarm ) {
	   alarm->CancelAlarm();
   }
	 else {
		 CCLOG("alarm was null so no alarm CANCEL");
	 }
}


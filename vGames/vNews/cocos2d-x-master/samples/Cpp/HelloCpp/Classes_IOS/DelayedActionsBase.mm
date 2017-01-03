//
//  DelayedActionsBase.mm
//  vFishJoy
//
//  Created by Virendra Shakya on 10/13/13.
//
//

#include "DelayedActionsBase.h"
#include "cocos2d.h"


DelayedActionsBase::DelayedActionsBase() : mAlarmHandle(0) {
  CCLOG("DelayedActionsBase::DelayedActionsBase");
}
DelayedActionsBase::~DelayedActionsBase() {
  CCLOG("DelayedActionsBase::~DelayedActionsBase");
}

void DelayedActionsBase::doSetActionTime(const Action, const Time) {
  CCLOG("DelayedActionsBase::doSetActionTime");
}
void DelayedActionsBase::doCancelAction(const Action) {
  CCLOG("DelayedActionsBase::doCancelAction");
}


/*
 * DelayedActionsBase.h
 *
 *  Created on: Oct 13, 2013
 *      Author: vshakya
 */

#ifndef DELAYEDACTIONSBASE_H_
#define DELAYEDACTIONSBASE_H_

#include "Time.h"

class DelayedActionsBase {

public:
  enum Action
  {
    LaunchApp=1,
    WakeUp=2,
    
      //InternetFetch=4,
    DisplayLabel=5,
    
    GoOutFirst=1001,
    GoOutSecond=1002,
    GoOutThird=1003
  };


	DelayedActionsBase();
	virtual ~DelayedActionsBase();

	void doSetActionTime(const Action a, const Time t);
	void doCancelAction(const Action a);

private:
	void* mAlarmHandle;
};

#endif /* DELAYEDACTIONSBASE_H_ */

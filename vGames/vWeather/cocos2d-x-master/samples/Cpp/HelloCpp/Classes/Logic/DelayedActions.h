#ifndef DELAYEDACTIONS_H
#define DELAYEDACTIONS_H

#include "DelayedActionsBase.h"
#include "Time.h"

class DelayedActions : private DelayedActionsBase
{
public:
//    enum Action
//    {
//        LaunchApp=1,
//        WakeUp=2,
//
//        //InternetFetch=4,
//        DisplayLabel=5,
//
//        GoOutFirst=1001,
//        GoOutSecond=1002,
//        GoOutThird=1003
//    };

    void setActionTime(const Action a, const Time t);
    void cancelAction(const Action a);
  
    virtual ~DelayedActions();

protected:
  
    DelayedActions();

private:
    friend class System;


};

#endif // DELAYEDACTIONS_H

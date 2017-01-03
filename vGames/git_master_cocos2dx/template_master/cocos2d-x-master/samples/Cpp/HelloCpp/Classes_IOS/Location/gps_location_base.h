//
//  gps_location_base.h
//  vFishJoy
//
//  Created by Virendra Shakya on 10/14/13.
//
//

#ifndef _gps_location_base_h
#define _gps_location_base_h

#include "cocos2d.h"

class CoreLocationImpl;

#define LOCATION_KEY "LOCATION_KEY"

struct locationStruct {
  float longi;
  float lati;
};

class CCCoreLocationBase : public cocos2d::CCObject {
protected:
  void doGetLocationDone(float longi, float lati);
  CCCoreLocationBase();
  virtual ~CCCoreLocationBase();
  void doGetLocation(CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector);
  bool doIsLocationAvailable();
  
  void doCancelLocationUpdates();
  float doGetLastKnownLongitude() const;
  float doGetLastKnownLatitude() const;

protected:
  char _LOCATION_KEY[1000];
  cocos2d::SEL_CallFuncND _pSelector;
  cocos2d::CCObject* _pTarget;
  locationStruct _loc;
  CoreLocationImpl * _localisationImpl;
};

#endif

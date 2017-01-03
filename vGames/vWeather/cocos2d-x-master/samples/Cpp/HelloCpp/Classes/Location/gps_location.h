//
//  gps_location.h
//  vFishJoy
//
//  Created by Virendra Shakya on 10/14/13.
//
//

#ifndef __gps_location__
#define __gps_location__

#include "cocos2d.h"
#include "Location/gps_location_base.h"

USING_NS_CC;

class CCCoreLocation : public CCCoreLocationBase
{
public:
  CCCoreLocation();
  virtual ~CCCoreLocation();
  void getLocation(CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector);
  void getLocationDone(float longi, float lati);

  bool isLocationAvailable();

  void cancelLocationUpdates();
  
  void onLocationObtained(CCNode* node, void* data);
  float getGpsFixedLongitude() const;
  float getGpsFixedLatitude() const;
  
  float getLastKnownLongitude() const;
  float getLastKnownLatitude() const;

  static CCCoreLocation * getInstance();
  
private:
  static CCCoreLocation* myinstanceT;
  locationStruct* mGpsFixedLocation;
};





#endif /* defined(__gps_location__) */

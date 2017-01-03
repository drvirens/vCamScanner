//
//  gps_location.cpp
//  vFishJoy
//
//  Created by Virendra Shakya on 10/14/13.
//
//

#include "gps_location.h"

CCCoreLocation* CCCoreLocation::myinstanceT = 0;

CCCoreLocation::CCCoreLocation() : CCCoreLocationBase(), mGpsFixedLocation(0)
{
}

CCCoreLocation::~CCCoreLocation()
{
	CCLOG("CCCoreLocation::~CCCoreLocation");
}

void CCCoreLocation::getLocation(CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
  CCCoreLocationBase::doGetLocation(pTarget, pSelector);
}

void CCCoreLocation::getLocationDone(float longi, float lati)
{
  CCCoreLocationBase::doGetLocationDone(longi, lati);
}

bool CCCoreLocation::isLocationAvailable()
{
  return CCCoreLocationBase::doIsLocationAvailable();
}

void CCCoreLocation::cancelLocationUpdates() {
	CCCoreLocationBase::doCancelLocationUpdates();
}

void CCCoreLocation::onLocationObtained(CCNode* node, void* data) {
  CCLOG("CCCoreLocation::onLocationObtained");
  if (data) {
    mGpsFixedLocation = (static_cast<locationStruct*>(data));
  }
}

float CCCoreLocation::getGpsFixedLongitude() const {
  if (mGpsFixedLocation) {
    return mGpsFixedLocation->longi;
  }
  return 0.0f;
}

float CCCoreLocation::getGpsFixedLatitude() const {
  if (mGpsFixedLocation) {
    return mGpsFixedLocation->lati;
  }
  return 0.0f;
}

float CCCoreLocation::getLastKnownLongitude() const {
	return CCCoreLocationBase::doGetLastKnownLongitude();
}

float CCCoreLocation::getLastKnownLatitude() const {
  return CCCoreLocationBase::doGetLastKnownLongitude();
}


CCCoreLocation * CCCoreLocation::getInstance() {
  if (myinstanceT == 0) {
    myinstanceT = new CCCoreLocation();
  }
  return myinstanceT;
}

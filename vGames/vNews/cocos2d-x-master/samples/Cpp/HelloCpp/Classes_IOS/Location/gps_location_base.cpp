//
//  CCCoreLocation.cpp
//
//  Created by franck on 3/19/13.
//
//

#include "Location/gps_location_base.h"
#include "cocos-ext.h"
#import "Location/CoreLocation_interface.h"

using namespace cocos2d::extension;
using namespace cocos2d;

//static CCCoreLocationBase * myinstanceT=NULL;
//
//CCCoreLocationBase * CCCoreLocationBase::getInstance() {
//  if (myinstanceT==NULL) {
//    myinstanceT=new CCCoreLocationBase();
//  }
//  return myinstanceT;
//}

CCCoreLocationBase::CCCoreLocationBase() : _pTarget(0), _pSelector(0) {

    _LOCATION_KEY[0]='\0';
    CCUserDefault * d=CCUserDefault::sharedUserDefault();
    std::string buff=d->getStringForKey(LOCATION_KEY, std::string(_LOCATION_KEY));
    sprintf(_LOCATION_KEY,"%s",buff.c_str());
    CCLOG("loaded _LOCATION_KEY=<%s>",_LOCATION_KEY);
    
    _localisationImpl=new CoreLocationImpl();
  
}

CCCoreLocationBase::~CCCoreLocationBase() {
  delete _localisationImpl; _localisationImpl=0;
}

bool CCCoreLocationBase::doIsLocationAvailable() {
    if (_LOCATION_KEY[0]!='\0') {
      CCLOG("CCCoreLocationBase::doIsLocationAvailable returns TRUE");
      return true;
    }
    CCLOG("CCCoreLocationBase::doIsLocationAvailable returns FALSE !!");
    return false;
}

void CCCoreLocationBase::doGetLocation(CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector) {

	//CCLOG("CCCoreLocationBase::getLocation");
    _pSelector=pSelector;
    _pTarget=pTarget;
    
    _localisationImpl->init();
  
}

void CCCoreLocationBase::doGetLocationDone(float lati, float longi) {
    _loc.lati=lati;
    _loc.longi=longi;

    sprintf(_LOCATION_KEY,"lati=%f&longi=%f",lati, longi);
    CCUserDefault * d=CCUserDefault::sharedUserDefault();
    d->setStringForKey(LOCATION_KEY, std::string(_LOCATION_KEY));
    //CCLOG("setting LOCATION_KEY=%s",_LOCATION_KEY);
    
    if (_pTarget && _pSelector)
    {
        (_pTarget->*_pSelector)((CCNode *)this, (void *) &_loc);
    }    
}

void CCCoreLocationBase::doCancelLocationUpdates() {
  
}

float CCCoreLocationBase::doGetLastKnownLongitude() const {
  return 0.0f;
}

float CCCoreLocationBase::doGetLastKnownLatitude() const {
  return 0.0f;
}




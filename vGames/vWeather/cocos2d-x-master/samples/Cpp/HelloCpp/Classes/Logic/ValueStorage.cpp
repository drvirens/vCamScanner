//
//  ValueStorage.cpp
//  vFishJoy
//
//  Created by Virendra Shakya on 10/12/13.
//
//

#include "cocos2d.h"
#include "Logic/ValueStorage.h"

USING_NS_CC;

int ValueStorage::get(const Key k)
{
  //CCLOG("ValueStorage::get");
  
  CCString* keyStr = CCString::createWithFormat("%d", k);
  int value = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(keyStr->getCString(), 0);
  
  //CCLOG("ValueStorage::GET key = %s, value = %d", keyStr->getCString(), value);
  
  return value;
}

void ValueStorage::set(const Key k, const int value)
{
  //CCLOG("ValueStorage::set");
  CCString* keyStr = CCString::createWithFormat("%d", k);
  //CCLOG("ValueStorage::set key = %s, value = %d", keyStr->getCString(), value);
  
  cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey(keyStr->getCString(), value);
  cocos2d::CCUserDefault::sharedUserDefault()->flush();
}

//
//  AlarmListScreen.h
//  HelloCpp
//
//  Created by Virendra Shakya on 12/9/13.
//
//

#ifndef __HelloCpp__AlarmListScreen__
#define __HelloCpp__AlarmListScreen__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSlidingLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AlarmListScreen : public CCLayer//Color
{
public:
  static CCScene* scene();
  AlarmListScreen();
  virtual ~AlarmListScreen();
  virtual bool init();
  
private:
  CREATE_FUNC(AlarmListScreen);
  CCSlidingLayer* createAlarmsList();
  void createSideBar();
  void createHudMenu();
  void onInitCB();
  void setUpSidebarAnimation(const CCPoint& aPoint, SEL_CallFunc aSEL_CallFunc);
  void onShowSidebar();
  void onHideSidebar();
  void onSideBarButtonTapped( CCObject *obj ); 
  
  /** override functions */
  virtual bool ccTouchBegan( cocos2d::CCTouch * touch, cocos2d::CCEvent * event );
  virtual void ccTouchMoved( cocos2d::CCTouch * touch, cocos2d::CCEvent * event );
  virtual void ccTouchEnded( cocos2d::CCTouch * touch, cocos2d::CCEvent * event );
  virtual void registerWithTouchDispatcher();
//	virtual void onEnter();
//	virtual void onEnterTransitionDidFinish();
//	virtual void onExit();
  
private:
  typedef enum tagESideBarState
  {
    eWillShowSidebar,
    eWillHideSidebar,
    eShowingSidebar,
    eNotShowingSidebar
  } ESideBarState;
  
  ESideBarState iESideBarState;
  CCSlidingLayer* iAlarmsList;
  CCLayer* iLHSSideBar;
  CCLayer* iHudMenu;
  
  CCPoint iSideBarInvisiblePosition;
};


#endif /* defined(__HelloCpp__AlarmListScreen__) */

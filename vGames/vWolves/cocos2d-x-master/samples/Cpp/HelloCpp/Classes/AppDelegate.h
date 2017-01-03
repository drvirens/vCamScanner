#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "CCApplication.h"
#include "cocos2d.h"

USING_NS_CC;

/**
@brief	The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	/**
	@brief	Implement CCDirector and CCScene init code here.
	@return true	Initialize success, app continue.
	@return false	Initialize failed, app terminate.
	*/
	virtual bool applicationDidFinishLaunching();

	/**
	@brief  The function be called when the application enter background
	@param  the pointer of the application
	*/
	virtual void applicationDidEnterBackground();

	/**
	@brief  The function be called when the application enter foreground
	@param  the pointer of the application
	*/
	virtual void applicationWillEnterForeground();
  
  void bootUp(CCDirector* pDirector);
  
  static   long getCurrentScore() {
    return mCurrentScore;
  }
  static void setCurrentScore(long aCurrentScore) {
    mCurrentScore = aCurrentScore;
  }
  private:
  static long mCurrentScore;
};

#endif  // __APP_DELEGATE_H__


#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Location/gps_location.h"
#endif

/**
The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCCoreLocation* mCCCoreLocation;
#endif

  static bool isRunning()
  {
    return _is_running;
  }
  
  static void configureContentProviders();

private:

  
private:
  static bool _is_running;
};

#endif // _APP_DELEGATE_H_


//#include "CommonHeaders.h"

#include "AppDelegate.h"

#include <vector>
#include <string>

#include "ScriptScene.h"
#include "AppMacros.h"
#include "Logic/IntentParams.h"
#include "Scripts/WakeUpScript.h"
#include "Logic/System.h"
#include "SimpleAudioEngine.h"
#include "ContentProvider/JokesHolder.h"
#include "ContentProvider/VKRssJokeProvider.h"
#include "ContentProvider/Weather/WeatherCoUaProvider.h"
#include "ContentProvider/Weather/WeatherHolder.h"
#include "Logic/PrefetchAction.h"
#include "Logic/Translations.h"
#include <cstdlib>
#include <ctime>


USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

bool AppDelegate::_is_running = false;

AppDelegate::AppDelegate() {
  _is_running = false;
}

AppDelegate::~AppDelegate() 
{
	CCLOG("AppDelegate::~AppDelegate");
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if(mCCCoreLocation) {
		mCCCoreLocation->cancelLocationUpdates();
	}
  delete mCCCoreLocation; mCCCoreLocation=0;
#endif
}

bool AppDelegate::applicationDidFinishLaunching(bool isAutoLaunch, void* launchParams) {
  CCLOG("Finished launching");
  srand(time(0));
  System::_ld.init();
  
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
	CCSize frameSize = pEGLView->getFrameSize();
  
//#if 0
#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	mCCCoreLocation = CCCoreLocation::getInstance();
	cocos2d::CCObject *pTarget = mCCCoreLocation;
	cocos2d::SEL_CallFuncND pSelector = callfuncND_selector(CCCoreLocation::onLocationObtained);
	mCCCoreLocation->getLocation(pTarget, pSelector);
#endif
//#endif

    vector<string> searchPath;
	if (frameSize.height > mediumResource.size.height)
	{
        searchPath.push_back(largeResource.directory);
        pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
	else
    {
        searchPath.push_back(smallResource.directory);
        pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	IntentParams::Mode mode;
	if (isAutoLaunch) {
		CCLOG("isAutoLaunch TRUE");
		int action = scanLaunchParams(launchParams); //present in OS_Specific.cpp
		switch (action) {
			case 0: {
				mode = IntentParams::LaunchMode;
				break;
			}
			default:
			case 1: {
				mode = IntentParams::WakeUpMode;
				break;
			}
		}
	} else {
		CCLOG("isAutoLaunch FALSE");
		mode = IntentParams::getInstance().getMode();
	}

	  ScriptPtr main_script(0);
	  if(mode == IntentParams::WakeUpMode) {
		CCLOG("WakeUpMode MODE");
		main_script = ScriptPtr(new WakeUpScript);
	  }
	  else {
		CCLOG("launch  MODE");
		main_script = ScriptPtr(new MainScript);
	  }

	  loadTranslation(getDeviceLang());
	  configureContentProviders();

		//
		//JokesHolder::sharedHolder().updateJokes();

	  CCScene *pScene = ScriptScene::scene(main_script);
    pDirector->runWithScene(pScene);
    _is_running = true;

    return true;
}

void AppDelegate::configureContentProviders()
{
	CCLOG("Jokes load");
  VKRssJokeProvider* feed = 0;
  Weather::City default_city = Weather::City("New York", 74223);
  if(R::Language::getLangCode()=="uk")
  {
    feed = new VKRssJokeProvider("http://vk.com/humor_ukraine");
    default_city = Weather::City("Київ", 23);
  }
  else if(R::Language::getLangCode()=="ru")
  {
    feed = new VKRssJokeProvider("http://vk.com/megaotriv");
    default_city = Weather::City("Киев", 23);
  }
  else
    feed = new VKRssJokeProvider("http://feeds.sydv.net/latest-bash-quotes", false);
  
  JokesHolder::sharedHolder().addJokeProvider(JokeProviderPtr(feed));
  
  CCLOG("Weather load");
  Weather::WeatherHolder::getInstance().setProvider(
                                                    Weather::WeatherProviderPtr(new Weather::WeatherCoUaProvider()));
  Weather::WeatherHolder::getInstance().setDefaultCity(default_city);
}

bool isAlarmOn() {
	bool isOn = false;
	SimpleAudioEngine* audio = SimpleAudioEngine::sharedEngine();
	if (audio) {
		isOn = audio->isBackgroundMusicPlaying();
	}
	return isOn;
}

void AppDelegate::applicationDidEnterBackground() {
  CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  
  CCLOG("AppDelegate::applicationDidEnterBackground mode = %d", IntentParams::getInstance().getMode());
  //if alarm is ringing, then BACK press should snooze
  if(IntentParams::getInstance().getMode() == IntentParams::WakeUpMode
		  ||
		isAlarmOn()
		  )
  {
	CCLOG("snooze");
    System::getAlarm().setSnooze(Alarm::ShortSnooze);
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
      //CCDirector::sharedDirector()->end();
  }
  else {
	  CCLOG("Not in WakeUpMode so no snoozing");
  }
  
}

void AppDelegate::applicationDidLaunchOnConditionMet(void* launchParams) {
  CCLOG("AppDelegate::applicationDidLaunchOnConditionMet");

//below implementations in OS_Specific.cpp unit
#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
  doTizenApplicationDidLaunchOnConditionMet(launchParams);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  doIOSApplicationDidLaunchOnConditionMet(launchParams);
#endif
}


// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


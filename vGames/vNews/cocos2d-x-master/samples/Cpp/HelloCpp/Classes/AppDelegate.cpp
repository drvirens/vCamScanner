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


//viren+
#include "NewsHome.h"
#include "Global.h"
#include "FriendListScene.h"
#include "AddFriendScene.h"
#include "LevelChooser.h"
#include "SearchScene.h"
#include "SplashScene.h"
#include "TutorialScreen.h"
#include "AlarmListScreen.h"
//viren-

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

bool AppDelegate::applicationDidFinishLaunching() {
  CCLOG("Finished launching");
//  srand(time(0));
  System::_ld.init();
  
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
   pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
   // pEGLView->setDesignResolutionSize( designResolutionSize.height, designResolutionSize.width, kResolutionNoBorder);
	CCSize frameSize = pEGLView->getFrameSize();
  
    //Multi-device scaling magic.
  const CCSize& screenSize = CCDirector::sharedDirector()->getWinSize();
//  g_rigMaxRadius = MIN(screenSize.width, screenSize.height) * 0.4f;
//  g_rigMinRadius = g_rigMaxRadius * 0.1f;
  
  CCFileUtils::sharedFileUtils()->purgeCachedEntries();
	vector<string> searchPath;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	mCCCoreLocation = CCCoreLocation::getInstance();
	cocos2d::CCObject *pTarget = mCCCoreLocation;
	cocos2d::SEL_CallFuncND pSelector = callfuncND_selector(CCCoreLocation::onLocationObtained);
	mCCCoreLocation->getLocation(pTarget, pSelector);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  if(CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad)
  {
    if(screenSize.width != 768)
    {
        //iPad 3+
      g_screenScale = 4.f;
    }
    else
    {
        //iPad 1~2
      g_screenScale = 2.f;
    }
  }
  else
  {
    if(screenSize.width != 320)
    {
        //iPhone 4+
        //g_screenScale = 2.f;
      g_screenScale = 2.25f; //viren
    }
    else
    {
      g_screenScale = 1.f;
    }
  }
#endif
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
  if(screenSize.width >= 720) {
    g_screenScale = 2.25f;
  }
  else if( screenSize.width >= 480 ) {
    g_screenScale = 1.5f;
//    searchPaths.insert(searchPaths.begin(),"large");
  }
  else if( screenSize.width >= 320 ) {
    g_screenScale = 1.f;
//    searchPaths.insert(searchPaths.begin(),"normal");
  }
#endif


    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 60);

    loadTranslation(getDeviceLang());
  configureContentProviders();

//  CCScene *pScene = NewsHome::scene();

//
//  CCScene *pScene = FriendListScene::scene();
//  CCScene *pScene = AddFriendScene::scene();
//    CCScene *pScene = LevelChooser::scene();

    //CCScene *pScene = Splash::scene(); //<---splash
    //CCScene *pScene = AddFriendScene::scene(); //<-- Home screen
    //CCScene *pScene = SearchScene::scene();
  
  
    //CCScene *pScene = TutorialScreen::scene();
  CCScene *pScene = AlarmListScreen::scene();
  
    pDirector->runWithScene(pScene);
    _is_running = true;

    return true;
}

void AppDelegate::configureContentProviders()
{
//	CCLOG("Jokes load");
//  VKRssJokeProvider* feed = 0;
//  Weather::City default_city = Weather::City("New York", 74223);
//  if(R::Language::getLangCode()=="uk")
//  {
//    feed = new VKRssJokeProvider("http://vk.com/humor_ukraine");
//    default_city = Weather::City("Київ", 23);
//  }
//  else if(R::Language::getLangCode()=="ru")
//  {
//    feed = new VKRssJokeProvider("http://vk.com/megaotriv");
//    default_city = Weather::City("Киев", 23);
//  }
//  else
//    feed = new VKRssJokeProvider("http://feeds.sydv.net/latest-bash-quotes", false);
  
//  JokesHolder::sharedHolder().addJokeProvider(JokeProviderPtr(feed));
  
  CCLOG("Weather load");
  Weather::City default_city = Weather::City("New York", 74223);
  Weather::WeatherHolder::getInstance().setProvider(Weather::WeatherProviderPtr(new Weather::WeatherCoUaProvider()));
 // Weather::WeatherHolder::getInstance().setDefaultCity(default_city);
}

//bool isAlarmOn() {
//	bool isOn = false;
//	SimpleAudioEngine* audio = SimpleAudioEngine::sharedEngine();
//	if (audio) {
//		isOn = audio->isBackgroundMusicPlaying();
//	}
//	return isOn;
//}

void AppDelegate::applicationDidEnterBackground() {
  CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  
//  CCLOG("AppDelegate::applicationDidEnterBackground mode = %d", IntentParams::getInstance().getMode());
  //if alarm is ringing, then BACK press should snooze
//  if(IntentParams::getInstance().getMode() == IntentParams::WakeUpMode
//		  ||
//		isAlarmOn()
//		  )
//  {
//	CCLOG("snooze");
//    System::getAlarm().setSnooze(Alarm::ShortSnooze);
//    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//      //CCDirector::sharedDirector()->end();
//  }
//  else {
//	  CCLOG("Not in WakeUpMode so no snoozing");
//  }
  
}



// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


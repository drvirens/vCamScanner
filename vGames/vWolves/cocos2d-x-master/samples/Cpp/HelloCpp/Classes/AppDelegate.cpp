


#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "Game/Sounds.h"
#include "Game/WorldScene.h"
#include "Game/MenuScene.h"

#include <vector>
#include <string>

#include "AppMacros.h"

#include "GameManager.h"
#include "GameSceneLayer.h"


using namespace std;
using namespace CocosDenshion;

USING_NS_CC;

long AppDelegate::mCurrentScore = 0;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
  CCDirector* pDirector = CCDirector::sharedDirector();
  CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
  
  pDirector->setOpenGLView(pEGLView);
	CCSize frameSize = pEGLView->getFrameSize();
  
    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
  pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
  pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
#endif
  
  
  vector<string> searchPath;
  
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
  
    // if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height)
	{
    searchPath.push_back(largeResource.directory);
    
    pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
  else if (frameSize.height > smallResource.size.height)
  {
    searchPath.push_back(mediumResource.directory);
    
    pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
  }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
  {
    searchPath.push_back(smallResource.directory);
    
    pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
  }
  CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
 
  pDirector->setDisplayStats(false);
  pDirector->setAnimationInterval(1.0 / 60);
  
// 	CCScene *pScene = MenuScene::scene();
//  pDirector->runWithScene(pScene);
  bootUp(pDirector);
  
  return true;
}

void AppDelegate::bootUp(CCDirector* pDirector) {
    // load up the sprite cache resources for the platform
  TargetPlatform target = getTargetPlatform();
  DeviceSize deviceSize = kDeviceSizeLarge;
  DeviceType deviceType = kDeviceTypeiPad3;
  
    // iPhone 5 Retina Display
    // Set the device type
  deviceType = kDeviceTypeiPhone5;
    // setup the sprite frame cache using our spritesheet plist
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sheet_retina.plist");
    // setup the texture cache using our spritesheet image
  CCTextureCache::sharedTextureCache()->addImage("sheet_retina.png");
  deviceSize = kDeviceSizeNormal;
  
    // initialize the game manager first before the scene
  GameManager::sharedGameManager()->setDeviceSize(deviceSize);
  GameManager::sharedGameManager()->setDeviceType(deviceType);
  
    // create a scene. it's an autorelease object
  CCScene *pScene = GameSceneLayer::scene();
  GameManager::sharedGameManager()->showMainMenu();
  
    // run
  pDirector->runWithScene(pScene);
  
}


  // This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();
  
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

  // this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();
  
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}




#if 0 //original code

#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "Game/Sounds.h"
#include "Game/WorldScene.h"
#include "Game/MenuScene.h"

#include <vector>
#include <string>

#include "AppMacros.h"

using namespace std;
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
  CCDirector* pDirector = CCDirector::sharedDirector();
  CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
  
  pDirector->setOpenGLView(pEGLView);
	CCSize frameSize = pEGLView->getFrameSize();
  
    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
  pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
  pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
#endif
  
  
  vector<string> searchPath;
  
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
  
    // if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height)
	{
    searchPath.push_back(largeResource.directory);
    
    pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
  else if (frameSize.height > smallResource.size.height)
  {
    searchPath.push_back(mediumResource.directory);
    
    pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
  }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
  {
    searchPath.push_back(smallResource.directory);
    
    pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
  }
  
  
    // set searching path
  CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
  
  //CCLOG("SearchPath is set to be = [%s]", searchPath);
	
    // turn on display FPS
  pDirector->setDisplayStats(false);
  
  //CCDirector::sharedDirector()->setDepthTest(false);
  
    // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);
  
    // create a scene. it's an autorelease object
  
//  PreloadSounds::CorrectVolume();
//	PreloadSounds::Load();
  
    // create a scene. it's an autorelease object
	//CCScene *SceneForCached = World::scene(); // load recurce for this scene
	CCScene *pScene = MenuScene::scene();
    // run
  pDirector->runWithScene(pScene);
  
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

#endif


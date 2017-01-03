#include "MenuScene.h"

#include <string>

USING_NS_CC;

#include "WorldScene.h"
#include "Sounds.h"
#include "CommonFunc.h"


#include "ScoreScene.h"

CCScene* MenuScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
		return false;

	float hudScaled	 = 0.8f	 * CurrentScale();
	float hudPadding = 50.0f * CurrentScale(); // отступ от границ экрана

	CCSprite* pBackGround = CCSprite::create("BackGround/menu.png");

	//320/480
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	float scale = screenSize.height / pBackGround->getContentSize().height;
	pBackGround->setScale(scale);

	pBackGround->setAnchorPoint(ccp(0,0));
	pBackGround->setPosition(ccp (0,0) );
	this->addChild(pBackGround, 0);

	CCSprite* pTitle = CCSprite::create("Hud/Title.png");
	pTitle->setScale(scale);

	pTitle->setAnchorPoint(ccp(0.5f,1.0f));
	pTitle->setPosition(ccp (screenSize.width / 2, screenSize.height - hudPadding) );
	this->addChild(pTitle, 0);

	std::string volumeOn("Hud/VolumeOn.png");
	std::string volumeOff("Hud/VolumeOff.png");
	CCMenuItemToggle* ctrlVolume = CCMenuItemToggle::createWithTarget(this,
																	menu_selector(MenuScene::menuVolumeCallback), 
																	CCMenuItemImage::create(volumeOn.c_str(),volumeOff.c_str()),
																	CCMenuItemImage::create(volumeOff.c_str(),volumeOn.c_str()),
																	NULL );
	// sizeButon (volume, exit have one size)
	CCSize sizeButon =  ctrlVolume->getContentSize();
	sizeButon.height *= hudScaled;
	sizeButon.width  *= hudScaled;
			
	ctrlVolume->setAnchorPoint(ccp(0,0));
	ctrlVolume->setScale(hudScaled);

	ctrlVolume->setPosition( ccp( hudPadding  , hudPadding) );

	if (!gSoundCheck)
		ctrlVolume->setSelectedIndex(1);

	std::string exitGame("Hud/Exit.png");
	CCMenuItemImage *ctrlExitGame = CCMenuItemImage::create(exitGame.c_str(), exitGame.c_str(),
																		this,  menu_selector(MenuScene::menuCloseCallback) );
	ctrlExitGame->setAnchorPoint(ccp(0,0));
	ctrlExitGame->setScale(hudScaled);
	ctrlExitGame->setPosition( ccp( screenSize.width - sizeButon.width - hudPadding  , hudPadding) );

 
	std::string playGameDef("Hud/Play.png");
	CCMenuItemImage *ctrlPlayGame = CCMenuItemImage::create(playGameDef.c_str(), playGameDef.c_str(), 
																		this,  menu_selector(MenuScene::menuPlayCallback) );
	ctrlPlayGame->setScale(CurrentScale());
	ctrlPlayGame->setPosition( ccp( screenSize.width / 2  , screenSize.height / 2 - hudPadding ) );

	CCMenu* pMenu = CCMenu::create(ctrlVolume,ctrlExitGame,ctrlPlayGame, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	PreloadSounds::StopBackGround();

	return true;
}

void MenuScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}


void MenuScene::menuVolumeCallback(CCObject* pSender)
{
	gSoundCheck = !gSoundCheck;
}
 
void MenuScene::menuPlayCallback(CCObject* pSender)
{
  if(gSoundCheck && !gSoundMediaLoaded) {
      PreloadSounds::CorrectVolume();
      PreloadSounds::Load();
      gSoundMediaLoaded = true;
  }
	CCScene *pScene = World::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
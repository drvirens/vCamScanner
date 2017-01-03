#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
  if ( !CCLayer::init() )
  {
    return false;
  }
  
  CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                        "CloseNormal.png",
                                                        "CloseSelected.png",
                                                        this,
                                                        menu_selector(HelloWorld::menuCloseCallback) );
  pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
  
  CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
  pMenu->setPosition( CCPointZero );
  this->addChild(pMenu, 1);
  CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
  
  CCSize size = CCDirector::sharedDirector()->getWinSize();
  pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
  this->addChild(pLabel, 1);
  
  CCSprite* pSprite = CCSprite::create("HelloWorld.png");
  pSprite->setPosition( ccp(size.width/2, size.height/2) );
  this->addChild(pSprite, 0);
  
  return true;
}

#include "webview_plugin/ZYWebView.h"
#include "MAUtil/VirenString.h"
#include "FacebookDemoMoblet.h"
#include "Facebook/config.h"

void testFaceBook() {
  FacebookDemoMoblet *appMoblet = new FacebookDemoMoblet(CONFIG_APPLICATION_ID);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{

  testFaceBook();
}

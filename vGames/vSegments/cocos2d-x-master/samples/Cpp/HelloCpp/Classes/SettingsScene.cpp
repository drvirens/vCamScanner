//
//  SettingsScene.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 27..
//
//

#include "SettingsScene.h"
#include "MenuScene.h"
#include "Global.h"

#include "ScoreMenuLayer.h"

SettingsScene* SettingsScene::create()
{
    SettingsScene* pRet = new SettingsScene();
    if(pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

SettingsScene::SettingsScene()
{
}

bool SettingsScene::init()
{

    CCLayer* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255));
    addChild(backgroundColor);
  
  CCLayer* menuLayer = ScoreMenuLayer::create();
  addChild(menuLayer);
  
  const CCSize& windowSize = CCDirector::sharedDirector()->getWinSize();
  const CCPoint midPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.5f);
  const CCPoint lowerPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.15f);
  
  const CCPoint helpPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.80f);
  const CCPoint scorePoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.65f);
  const CCPoint accuracyPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.55f);
  const CCPoint helpLine3Point = ccp(windowSize.width * 0.5f, windowSize.height * 0.45f);
  
  
  CCSprite* scoreboard = CCSprite::create("scoreboard.png");
  scoreboard->setAnchorPoint(ccp(0.5f,0.5f));
  scoreboard->setPosition(midPoint);
  //menuLayer->addChild(scoreboard);
  
  CCMenu* menu = CCMenu::create();
  menu->setPosition(lowerPoint);
  CCMenuItemImage* back = CCMenuItemImage::create("back.png", "back_sel.png");
  back->setTarget(this, menu_selector(SettingsScene::pop));
  menu->addChild(back);
  
  menu->alignItemsHorizontallyWithPadding(20 * SCREEN_SCALE());
  
  menuLayer->addChild(menu);
  
  
  CCString* help = CCString::create("HELP");
  CCLabelTTF* labelLabel = CCLabelTTF::create(help->getCString(), DEFAULT_FONT,
                                         DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 1.5f);
  labelLabel->setColor(ccBLACK);
  labelLabel->setPosition(helpPoint);
  menuLayer->addChild(labelLabel);
  
  CCString* highscore = CCString::create("Draw/cut lines to make shape like white miniature.");
  CCLabelTTF* label = CCLabelTTF::create(highscore->getCString(), DEFAULT_FONT,
                                         DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() ); //* 1.5f);
  label->setColor(ccBLACK);
  label->setPosition(scorePoint);
  menuLayer->addChild(label);
  
  
  CCString* accuracy = CCString::create("Lines can be drawn simply by swiping.");
  CCLabelTTF* accuracyLabel = CCLabelTTF::create(accuracy->getCString(), DEFAULT_FONT,
                                                 DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() ); // * 0.75f);
  accuracyLabel->setColor(ccBLACK);
  accuracyLabel->setPosition(accuracyPoint);
  menuLayer->addChild(accuracyLabel);
  
  CCString* helpLine3 = CCString::create("For support, contact me at: viren_ca@hotmail.com");
  CCLabelTTF* helpLine3Label = CCLabelTTF::create(helpLine3->getCString(), DEFAULT_FONT,
                                                 DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() ); // * 0.75f);
  helpLine3Label->setColor(ccBLACK);
  helpLine3Label->setPosition(helpLine3Point);
  menuLayer->addChild(helpLine3Label);
  
    return true;
}

void SettingsScene::update(float dt)
{
}


void SettingsScene::pop()
{
  CCTransitionFade* fade = CCTransitionFade::create(0.25f, MenuScene::create());
  CCDirector::sharedDirector()->replaceScene(fade);
}


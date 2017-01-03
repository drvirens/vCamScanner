
#include "AboutGameLayer.h"
#include "Constants.h"
#include "GameManager.h"

using namespace cocos2d;

// Initialize our Main Menu Layer, and add the initial main menu with the title screen, play button and about button.
bool AboutGameLayer::init()
{
    // Initialize the parent
    if (!CCLayer::init()) return false;
  
    this->setKeypadEnabled(true);
    
    // Set the screen size to the full dimensions of the device (full screen)
    this->setContentSize(SCREEN_SIZE);
    
    CCSprite *aboutGameTitle = CCSprite::createWithSpriteFrameName("about_game.png");
    aboutGameTitle->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.2));
    aboutGameTitle->setScale(0.8f);
    this->addChild(aboutGameTitle);
    
    float labelScaleNormal = 1.0f;
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid854x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x400 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid720x480)
    {
        labelScaleNormal = 0.8f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeNormal)
    {
        labelScaleNormal = 0.8f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeSmall)
    {
        labelScaleNormal = 0.45f;
    }
    
    float labelScaleSmall = 0.8f;
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid854x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x400 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid720x480)
    {
        labelScaleSmall = 0.6f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeNormal)
    {
        labelScaleSmall = 0.7f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeSmall)
    {
        labelScaleSmall = 0.4f;
    }
  
  CCLabelBMFont *descriptionLabel1 = CCLabelBMFont::create("Tap on right side of the screen to kill wolf.", "markerFelt.fnt");
  descriptionLabel1->setScale(labelScaleNormal);
  descriptionLabel1->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.40));
  this->addChild(descriptionLabel1);
  
  CCLabelBMFont *descriptionLabel2 = CCLabelBMFont::create("Tap on left side to jump to avoid getting hurt.", "markerFelt.fnt");
  descriptionLabel2->setScale(labelScaleNormal);
  descriptionLabel2->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.60));
  this->addChild(descriptionLabel2);
  
  CCLabelBMFont *createdLabel = CCLabelBMFont::create("Tilt device to left or right to move on side of tilt.", "markerFelt.fnt");
  createdLabel->setScale(labelScaleNormal);
  createdLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.85));
  this->addChild(createdLabel);
  
  CCLabelBMFont *craigLabel = CCLabelBMFont::create("You must kill only black wolves, not white wloves.", "markerFelt.fnt");
  craigLabel->setScale(labelScaleNormal);
  craigLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2.35));
  this->addChild(craigLabel);

  
  CCLabelBMFont *copyrightLabel = CCLabelBMFont::create("Remember: LEFT = JUMP; RIGHT = SHOOT; TILT = MOVE", "markerFelt.fnt");
  copyrightLabel->setScale(labelScaleNormal);
  copyrightLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/3.15));
  this->addChild(copyrightLabel);
  
    // Back button
    createBackButton();
  
    // Initialization was successful
    return true;
}

void AboutGameLayer::createBackButton()
{
    // Create the backButton
    CCSprite *backButtonSpriteUp = CCSprite::createWithSpriteFrameName("main_button.png");
    CCSprite *backButtonSpriteDown = CCSprite::createWithSpriteFrameName("main_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    backButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *backButton = CCMenuItemSprite::create(backButtonSpriteUp, backButtonSpriteDown, this, menu_selector(AboutGameLayer::backButtonTouched));
    backButton->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleTo::create(0.4f, 1.1f), CCScaleTo::create(1.0f, 1.0f))));
    
    // Create the start game menu
    CCMenu *gameMenu = CCMenu::create(backButton, NULL);
    // Set the initial position off screen
    gameMenu->setPosition(ccp(SCREEN_WIDTH/2, -SCREEN_HEIGHT));
    // Set the tag of the start menu so that we can refer to it later using getChildByTag(...)
    gameMenu->setTag(kAboutGameLayer_BackMenu);
    
    // Create and run an animation that will slide the start game menu in from below the screen to its intended location
    CCActionInterval *moveAction = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/8));
    CCFiniteTimeAction *easeIn = CCEaseIn::create(moveAction, 0.2f);
    gameMenu->runAction(easeIn);
    
    // Add the start menu to the layer
    this->addChild(gameMenu);
}

void AboutGameLayer::backButtonTouched()
{
    this->getChildByTag(kAboutGameLayer_BackMenu)->stopAllActions();
    GameManager::sharedGameManager()->showMainMenu();
}

void AboutGameLayer::keyBackClicked()
{
	CCLOG("AboutGameLayer back key");
  
  //backButtonTouched();
	GameManager::sharedGameManager()->showMainMenu();
}



//
//  AlarmListScreen.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 12/9/13.
//
//

#include "AlarmListScreen.h"
#include "ExpandedViewPanel.h"
#include "ScreenHelper.h"

CCScene* AlarmListScreen::scene()
{
  CCScene * scene = NULL;
  do
  {
    scene = CCScene::create();
    CC_BREAK_IF(! scene);
    
    AlarmListScreen *layer = AlarmListScreen::create();
    CC_BREAK_IF(! layer);
    
    scene->addChild(layer);
  } while (0);
  return scene;
}

AlarmListScreen::AlarmListScreen()
  : iESideBarState(eNotShowingSidebar)
  , iAlarmsList(0)
  , iLHSSideBar(0)
  , iHudMenu(0)
{
  
}

AlarmListScreen::~AlarmListScreen()
{
  
}

CCSlidingLayer* AlarmListScreen::createAlarmsList()
{
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  CCSlidingLayer* list = CCSlidingLayer::create(
                                          Vertically,
                                          CCSizeMake(winSize.width, winSize.height),
                                          CCRectMake(0,0,winSize.width,winSize.height),
                                          ccc4(255,255,255,255));
  
  
  
  //TODO: read alarms from shared-defaults
  CCSize theSize = CCDirector::sharedDirector()->getWinSize();
  theSize.height = 40;
  
  CCNode* entryView = 0;
  entryView = CCSprite::create("violet.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
  entryView = CCSprite::create("red.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
//  entryView = ExpandedViewPanel::create("blue.png", "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
//  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
//  
//  entryView = ExpandedViewPanel::create("orange.png", "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
//  list->addChildWithSize( entryView, theSize, kAlignmentCenter);


  entryView = CCSprite::create("blue.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
  entryView = CCSprite::create("orange.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
  entryView = CCSprite::create("black.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
  entryView = CCSprite::create("green.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
  entryView = CCSprite::create("violet.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
  entryView = CCSprite::create("red.png"); //, "aSmallTitle", "aMainMenuTitle", "aNewsTitle", "aNewsSummary");
  list->addChildWithSize( entryView, theSize, kAlignmentCenter);
  
  return list;
}

void AlarmListScreen::onSideBarButtonTapped( CCObject *obj )
{
  iESideBarState = eWillShowSidebar;
  iLHSSideBar->setVisible(true);
  setUpSidebarAnimation(ccp(0,0), callfunc_selector(AlarmListScreen::onShowSidebar));
  
  //enable set touch now for ourselves since user may tap anywhere else on screen
  //in which case we need to simply hide the sidebar
  this->setTouchEnabled(true);
}

void AlarmListScreen::onShowSidebar()
{
  iLHSSideBar->setPosition(ccp(0,0)); //go back t actual position permanenetly
  iESideBarState = eShowingSidebar;
}

void AlarmListScreen::onHideSidebar()
{
  iLHSSideBar->setVisible(false);
  iLHSSideBar->setPosition(iSideBarInvisiblePosition); //go back t actual position permanenetly
  iESideBarState = eNotShowingSidebar;
}

void AlarmListScreen::setUpSidebarAnimation(const CCPoint& aPoint, SEL_CallFunc aSEL_CallFunc)
{
  CCMoveTo* moveTp = CCMoveTo::create(0.35f, aPoint);
  CCAction* delayedCb = CCSequence::createWithTwoActions(
                                                         moveTp,
                                                         CCCallFunc::create(this, aSEL_CallFunc));
  iLHSSideBar->runAction(delayedCb);
}


static const char *s_ObjImg[15] =
{
  "burger.png",//Triple Lindy
  "gear.png",//Peanut Envy
  "globe.png",//Rider's Block
  "profile.png",//That's No Moon
  "star.png"//,//It's Over 9000
};
static const char *s_ObjName[15] =
{
  "Triple Lindy",
  "Peanut Envy",
  "Rider's Block",
  "That's No Moon",
  "It's Over 9000"
};

void AlarmListScreen::createHudMenu()
{
  CCMenu *screenMenu = CCMenu::create();
  CCLayer *container = CCLayer::create();
  screenMenu->setTouchEnabled(true);
  container->addChild(screenMenu);
  
  CCSprite *sprite = CCSprite::create("MainBackFiller.png");
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  float bgScaleY = ( winSize.height ) / ( sprite->getContentSize().height );
  sprite->setScaleY(bgScaleY);
  container->addChild(sprite);
  container->setContentSize(sprite->getContentSize());
  
  for(int i = 0; i < 2; i++)
  {
    CCMenuItem *temp = CCMenuItemImage::create("red.png", "orange.png", this,
                                        menu_selector(AlarmListScreen::onSideBarButtonTapped));
      //temp->setScale(scale);
    
      //TODO: Use spritesheet
      //sprite = CCSprite::createWithSpriteFrameName(s_ObjImg[i]);
    sprite = CCSprite::create(s_ObjImg[i]);
    sprite->setPosition(ccp(29,28));
    
    temp->addChild(sprite);
    
    screenMenu->addChild(temp);
  } //end for
  screenMenu->alignItemsHorizontallyWithPadding(10.0f);
  
  int num_children = screenMenu->getChildrenCount();
  
  CCNode *first = (CCNode *)screenMenu->getChildren()->objectAtIndex(0);
  CCNode *last = (CCNode *)screenMenu->getChildren()->objectAtIndex(num_children-1);
  
  CCSize menu_size = CCSizeMake(last->convertToWorldSpace(last->getContentSize()).x - first->convertToWorldSpace(ccp(0,0)).x, first->convertToWorldSpace(first->getContentSize()).y - last->convertToWorldSpace(ccp(0.0f,0.0f)).y);
  
  container->setContentSize(menu_size);
  screenMenu->setAnchorPoint(ccp(0.0f,0.0f));
  screenMenu->setPosition(ccp(menu_size.width/2.0f, 450)); //menu_size.height/2.0f));
  
  
  container->setVisible(true);
  CCPoint containerPoint = container->getPosition();
  
  CCPoint hudPoint = ccp(20, containerPoint.y);
  container->setPosition(hudPoint);
  
    //TODO: Must be tall
  this->addChild(container);
  iHudMenu = container;

}

void AlarmListScreen::createSideBar()
{
  CCSprite *sprite = 0;

  CCMenu *screenMenu = CCMenu::create();
  CCLayer *container = CCLayer::create();
  screenMenu->setTouchEnabled(true);
  container->addChild(screenMenu);
  
  sprite = CCSprite::create("MainBackFiller.png");
  //sprite->setScale(scale);
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  float bgScaleY = ( winSize.height ) / ( sprite->getContentSize().height );
  sprite->setScaleY(bgScaleY);
  container->addChild(sprite);
  container->setContentSize(sprite->getContentSize());
  
  for(int i = 0; i < 5; i++)
  {
    
    CCMenuItem *temp = CCMenuItemImage::create("red.png", "orange.png");
    //temp->setScale(scale);
    
    //TODO: Use spritesheet
    //sprite = CCSprite::createWithSpriteFrameName(s_ObjImg[i]);
    sprite = CCSprite::create(s_ObjImg[i]);
    sprite->setPosition(ccp(29,28));
    
    temp->addChild(sprite);
    
    
    CCSize dim;
    dim.width = 200.0f;
    dim.height = 25.0f;
    
    
    CCLabelTTF *label = CCLabelTTF::create(s_ObjName[i],"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
    label->setPosition(ccp(161,30));
    //label->setColor(shadowColor);
    temp->addChild(label);
    
    
    screenMenu->addChild(temp);
  }
  screenMenu->alignItemsVerticallyWithPadding(0);
  
  int num_children = screenMenu->getChildrenCount();
  CCNode *first = (CCNode *)screenMenu->getChildren()->objectAtIndex(0);
  CCNode *last = (CCNode *)screenMenu->getChildren()->objectAtIndex(num_children-1);
  CCSize menu_size = CCSizeMake(last->convertToWorldSpace(last->getContentSize()).x - first->convertToWorldSpace(ccp(0,0)).x, first->convertToWorldSpace(first->getContentSize()).y - last->convertToWorldSpace(ccp(0.0f,0.0f)).y);
  
  container->setContentSize(menu_size);
  screenMenu->setAnchorPoint(ccp(0.0f,0.0f));
  screenMenu->setPosition(ccp(menu_size.width/2.0f,menu_size.height/2.0f));
  
  
  container->setVisible(false);
  CCPoint containerPoint = container->getPosition();
  
  iSideBarInvisiblePosition = ccp(-menu_size.width, containerPoint.y);
//  container->setPosition(0, containerPoint.y);
  container->setPosition(iSideBarInvisiblePosition);
  
  //TODO: Must be tall
  this->addChild(container);
  iLHSSideBar = container;
}

void AlarmListScreen::onInitCB()
{
  this->setPosition(ccp(0,0)); //go back t actual position permanenetly
}

bool AlarmListScreen::init()
{
  if ( !CCLayer::init() )
	{
		return false;
	}

  iAlarmsList = createAlarmsList();
  
  this->addChild(iAlarmsList);
  
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  this->setPosition(ccp(0,-winSize.height));
  
  CCMoveTo* moveTp = CCMoveTo::create(0.5f, ccp(0,0));
  CCAction* delayedCb = CCSequence::createWithTwoActions(
                                                     moveTp,
                                                     CCCallFunc::create(this, callfunc_selector(AlarmListScreen::onInitCB)));
  iAlarmsList->runAction(delayedCb);
  
  createHudMenu();
  createSideBar();
  return true;
}

bool AlarmListScreen::ccTouchBegan( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{
//	CCPoint touchLocation = touch->getLocation();
  
    // if touched outside the content rect do nothing
//	if (!contentRect_.containsPoint(touchLocation))
//		return false;
//  
//	if (contentRect_.containsPoint(touchLocation))
//	{
//		m_tBeginPos = touch->getLocation();
//  }
	return true;
}

void AlarmListScreen::ccTouchMoved( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{
//  isDragging_ = true;
//  
//	CCPoint curPos;
//	CCPoint nextPos;
//	CCPoint touchLocation;
//  
//  if(slideDirection_ == Vertically)
//  {
//		touchLocation = touch->getLocation();
//		float nMoveY = touchLocation.y - m_tBeginPos.y;
//    
//		curPos  = this->getPosition();
//		nextPos = ccp(curPos.x, curPos.y + nMoveY);
//	}
//  else if(slideDirection_ == Horizontally)
//  {
//		touchLocation = touch->getLocation();
//		float nMoveX = touchLocation.x - m_tBeginPos.x;
//    
//		curPos  = this->getPosition();
//		nextPos = ccp(curPos.x + nMoveX, curPos.y);
//	}
//	
//  this->setPosition(nextPos);
//  m_tBeginPos = touchLocation;
}

void AlarmListScreen::ccTouchEnded( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{
//	isDragging_ = false;
  switch(iESideBarState)
  {
    default: //FALL THRU
    case eNotShowingSidebar:
    {
      break;
    }
    case eWillShowSidebar:
    {
      break;
    }
    case eWillHideSidebar:
    {
      break;
    }
    case eShowingSidebar:
    {
      setUpSidebarAnimation(iSideBarInvisiblePosition, callfunc_selector(AlarmListScreen::onHideSidebar));
      
      this->setTouchEnabled(false);
      break;
    }
  }
}

void AlarmListScreen::registerWithTouchDispatcher()
{
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}



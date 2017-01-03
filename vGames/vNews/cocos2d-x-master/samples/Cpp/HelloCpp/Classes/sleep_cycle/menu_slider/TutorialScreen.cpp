//
//  TutorialScreen.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 12/9/13.
//
//

#include "TutorialScreen.h"
#include "VisibleRect.h"
#include "ExpandedViewPanel.h"
#include "ScreenHelper.h"

TutorialScreen::TutorialScreen()
  : iNewsViewPager(0)
  , m_pBolasSprites(0)
  , pScrollLevelLayer(0)
{
  
}

TutorialScreen::~TutorialScreen()
{
  
}

bool TutorialScreen::init()
{
  if ( !CCLayer::init() )
	{
		return false;
	}
  
  createEntriesForCateogries();
  m_pBolasSprites = CCArray::create();
  m_pBolasSprites->retain();

	CCSize size = CCDirector::sharedDirector()->getWinSize();
  
  pScrollLevelLayer = createInnerScrollableView("title", 1, CHILDRENT_TYPE);
  this->addChild(pScrollLevelLayer,1);
  return true;
}

CCScrollLayer* TutorialScreen::createInnerScrollableView(const char* inTitle, int aItemNum, ITEM_TYPE inType)
{
  if(inType != CHILDRENT_TYPE) {
    CCLOG("createInnerScrollableView can only be CHILD. so return null");
    return 0;
  }
//    //max 8 please
//  EntriesModel* theEntriesModel = iEntriesModel[aItemNum];
//  
//  if (theEntriesModel == 0) {
//    CCLOG("TODO: return an empty view here");
//  }
  
  iNewsViewPager = CCArray::create();
  int theEntriesModelCount = 5; //theEntriesModel->rowCount();
  for (int i=0; i < theEntriesModelCount; i++) {
    CCNode* entryView = 0;
    entryView = ExpandedViewPanel::create("violet.png", "aSmallTitle", "aMainMenuTitle",
                                          "aNewsTitle", "aNewsSummary");
    iNewsViewPager->addObject(entryView);
  }
  
  CCScrollLayer *pScrollLayer = CCScrollLayer::nodeWithLayers(iNewsViewPager, 0);
  pScrollLayer->setPagesIndicatorPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + 70));
  pScrollLayer->setDelegate(this);
  pScrollLayer->moveToPage(0);
    //  pScrollLayer->setPosition(ccp(120, size.height/2));
  
  return pScrollLayer;
}

void TutorialScreen::createEntriesForCateogries()
{
  
}

void TutorialScreen::scrollLayerScrollingStarted(CCScrollLayer* sender)
{
  
}

void TutorialScreen::scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page)
{
  if (sender->getShowPagesIndicator())
  {
    CCObject *item;
    CCARRAY_FOREACH(m_pBolasSprites, item)
    {
      CCSprite *sprite = (CCSprite*)item;
      removeChild(sprite, false);
    }
    
    m_pBolasSprites->removeAllObjects();
    
    int totalScreens = sender->getTotalScreens();
    int currentScreen = sender->getCurrentScreen();
    
    CCPoint pageIndicatorPosition = sender->getPagesIndicatorPosition();
    
      // Prepare Points Array
    float n = (float)totalScreens; //< Total points count in CGFloat.
    float pY = pageIndicatorPosition.y; //< Points y-coord in parent coord sys.
    float d = 30.0f; //< Distance between points.
    
    CCPoint* points = new CCPoint[totalScreens];
    for (int i = 0; i < totalScreens; ++i)
    {
      float pX = pageIndicatorPosition.x + d * ((float)i - 0.5f*(n-1.0f));
      points[i] = ccp(pX, pY);
    }
    
    for (int i = 0; i < totalScreens; i++) {
      
      CCSprite *bola;
      
      if (i == currentScreen) {
        bola = CCSprite::create("bola_roja.png");
      } else {
        bola = CCSprite::create("bola_gris.png");
      }
      
      bola->setPosition(points[i]);
      m_pBolasSprites->addObject(bola);
    }
    
    delete [] points;
    
    CCARRAY_FOREACH(m_pBolasSprites, item)
    {
      CCSprite *sprite = (CCSprite*)item;
      addChild(sprite);
    }
  }

}

cocos2d::CCScene* TutorialScreen::scene()
{
	CCScene *scene = CCScene::create(); // autorelease object
	TutorialScreen *tut = TutorialScreen::create(); // autorelease object
	scene->addChild(tut);
	return scene;
}

void TutorialScreen::backCallback(CCObject* pSender)
{
  
}


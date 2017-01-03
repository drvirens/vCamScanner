#include "LevelChooser.h"
#include "SimpleAudioEngine.h"
//#include "MainMenuScene.h"
//#include "GameScene.h"
#include "CCScrollLayer.h"
#include "MultiResolution.h"
//#include "CodeChecker.h"
//#include "UserInfoManager.h"
#include "CCScrollLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScrollLayer* pScrollLevelLayer;

CCScene* LevelChooser::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LevelChooser *pTestLayer = LevelChooser::create();

	// add layer as a child to scene
	scene->addChild(pTestLayer);


	// return the scene
	return scene;
}



void LevelChooser::scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page)
{
    //    CCLOG("AddFriendScene::scrollLayerScrolledToPageNumber , page = %d, remove below line", page);
    //  sender->setVisible(true); //only for testing remove afterwards viren
  
  
  
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

void LevelChooser::createEntriesForCateogries() {
  for (int i=0; i < kHomeUI_MaxCategories; i++) {
      //TODO:
    switch(i) {
      case 0: //news
      case 1: //tech
      case 2: //sports
        break; // etc
    }
    iEntriesModel[i] = EntriesModel::createTestEntriesModel(); //TODO: Should be done on LTask but ok for now
  }
}


CCScrollLayer* LevelChooser::createInnerScrollableView(const char* inTitle, int aItemNum, ITEM_TYPE inType)
{
  if(inType != CHILDRENT_TYPE) {
    CCLOG("createInnerScrollableView can only be CHILD. so return null");
    return 0;
  }
    //max 8 please
  EntriesModel* theEntriesModel = iEntriesModel[aItemNum];
  
  if (theEntriesModel == 0) {
    CCLOG("TODO: return an empty view here");
  }
  
  iNewsViewPager = CCArray::create();
  int theEntriesModelCount = theEntriesModel->rowCount();
  for (int i=0; i < theEntriesModelCount; i++) {
    CCNode* entryView = 0;
      //    if (i%2) {
    entryView = ExpandedViewPanel::create("violet.png", "aSmallTitle", "aMainMenuTitle",
                                          "aNewsTitle", "aNewsSummary");
    iNewsViewPager->addObject(entryView);
  }
  
  
    //TODO: Add sub-news to pLayers e.g images, media, video etc
  CCScrollLayer *pScrollLayer = CCScrollLayer::nodeWithLayers(iNewsViewPager, 0);
  pScrollLayer->setPagesIndicatorPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + 70));
  pScrollLayer->setDelegate(this);
  pScrollLayer->moveToPage(0);
    //  pScrollLayer->setPosition(ccp(120, size.height/2));
  
    //addChild(pScrollLayer);
  return pScrollLayer;
  
}

// on "init" you need to initialize your instance
bool LevelChooser::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

  iCategoryModel = CategoryModel::createTestCategoryModel();
  createEntriesForCateogries();
  m_pBolasSprites = CCArray::create();
  m_pBolasSprites->retain();

//    CodeChecker::initLevels();
  
	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();
  
  pScrollLevelLayer = createInnerScrollableView("title", 1, CHILDRENT_TYPE);
this->addChild(pScrollLevelLayer,1);


//	float scale = MultiResolution::getScale();
//	CCLabelBMFont* pLabel = CCLabelBMFont::create("Select Level", "futura-48.fnt");
//	pLabel->setPosition( ccp(size.width / 2, size.height - 50*scale) );
//	pLabel->setScale(MultiResolution::getScale());
//	this->addChild(pLabel, 1);
//
//	LevelLayer *level1 = new LevelLayer("lvl1.png", 1);
//	LevelLayer *level2 = new LevelLayer("lvl2.png", 2);
//	LevelLayer *level3 = new LevelLayer("lvl3.png", 3);
//	LevelLayer *level4 = new LevelLayer("lvl4.png", 4);
//
//    CCArray layers;
//	layers.addObject(level1);
//    layers.addObject(level2);
//    layers.addObject(level3);
//    layers.addObject(level4);
//
//    pScrollLevelLayer = CCScrollLayer::nodeWithLayers(&layers, 160, 60);
//    this->addChild(pScrollLevelLayer,1);
//	
//	CCLabelBMFont * pLabel1 = CCLabelBMFont::create( "go back", "futura-48.fnt" );
//	CCMenuItemLabel * pBack = CCMenuItemLabel::create(pLabel1, this, menu_selector(LevelChooser::backCallback));
//	CCMenu* pMenu = CCMenu::create(pBack, NULL);
//    pMenu->setPosition(ccp(size.width - 100, 50));
//
//	this->addChild(pMenu, 1);
//
//	CCSprite* pSprite = CCSprite::create("safe_background.jpg");
//	pSprite->setPosition( ccp(size.width / 2, size.height / 2) );
//	this->addChild(pSprite, 0);
	return true;
}

void LevelChooser::backCallback(CCObject* pSender) {
//	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, MainMenu::scene()));
}

#if 0
LevelLayer::LevelLayer(const char *picName, int levlNo) {
	this->levlNo = levlNo;
	pSpriteLvl = CCSprite::create(picName);
    pSpriteLvl->setAnchorPoint(ccp(0,0));
	addChild(pSpriteLvl);
	setContentSize(CCSizeMake(160, 160));
}

LevelLayer::~LevelLayer() {

}

void LevelLayer::onEnter(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,false);
    CCLayer::onEnter();
}

void LevelLayer::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool LevelLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent) {
	CCPoint point = touch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    point.x += (pScrollLevelLayer->currentScreen - 1) * pScrollLevelLayer->scrollWidth;
    return rect().containsPoint(point);
}

void LevelLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	CCPoint point = pTouch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    point.x += (pScrollLevelLayer->currentScreen - 1) * pScrollLevelLayer->scrollWidth;
    if (rect().containsPoint(point)) {
        CCScaleBy * firstAction = CCScaleBy::create(0.05f, 0.95f);
        CCScaleTo * secondAction = CCScaleTo::create(0.125f, 1);
        CCCallFunc * callStartGame = CCCallFunc::create(this, callfunc_selector(LevelLayer::gameSceneCallback));
        CCSequence * actionSequence = CCSequence::create(firstAction, secondAction, callStartGame, NULL);
        pSpriteLvl->runAction(actionSequence);
	}
}

CCRect LevelLayer::rect() {
    CCRect c = CCRectMake(this->getPosition().x, this->getPosition().y, this->getContentSize().width, this->getContentSize().height);
    return c;
}

void LevelLayer::gameSceneCallback()
{
//    UserInfoManager::loadLevelInfo(levlNo);
//	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, GameScene::scene(levlNo)));
}
#endif



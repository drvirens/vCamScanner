#include "NewsHome.h"

#include "SimpleAudioEngine.h"

#include "Widgets/WeatherWidget.h"
#include "Logic/PrefetchAction.h"

#include "VisibleRect.h"

#include "CPtExpandableListView.h"
#include "WeatherPanel.h"
#include "ContentProvider/LTaskManager.h"
#include "feedly/models/bk/categorymodel.h"
#include "feedly/models/entriesmodel.h"
#include "news_app/homeUI/Global.h"
#include "ExpandedViewPanel.h"


using namespace CocosDenshion;
using namespace cocos2d;

NewsHome::NewsHome()
            : iCategoryModel(0)
//            , iEntriesModel(0)
            , m_nMaxChapterId (kHomeUI_MaxCategories)
            , m_nMaxSectionId (kHomeUI_MaxCategoryEntries)
            {
  
            }


bool NewsHome::init()
{
  if ( !CCLayer::init() )
  {
    return false;
  }
    //CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255)); //WHITE
  CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 55, 55, 55));
  addChild(backgroundColor);
  
  createEntriesForCateogries();
  
  m_pBolasSprites = CCArray::create();
  m_pBolasSprites->retain();
  
  
  createLTaskManager();
  CCNode* appTitle = addAppTitle();
  
    //add title of app
  this->addChild(appTitle);
  
    //add weather
  addWeatherPanel(0, this);
  
    //add categories
  CCSize topSize = appTitle->getContentSize();
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  int idealHeight = winSize.height - topSize.height;
  int availableHeight = idealHeight - topSize.height; //adjust for weather panel
  
  //testExpandableList(availableHeight);
  
  addCategoryPanel(availableHeight);
  
  return true;
}


void NewsHome::createEntriesForCateogries() {
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


CCNode* NewsHome::addCategoryPanel(int aHeight) {
  
  m_nCurrentChapterId = m_nMaxChapterId-1;
  m_nCurrentSectionId = m_nMaxSectionId;;
  getChapters(m_nMaxChapterId);
  getSections(m_nMaxChapterId-1, m_nMaxSectionId);
  
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("items_bg.plist",  "items_bg.png");
  CCArray* array = CCArray::create();
  
  if (!iCategoryModel) {
    iCategoryModel = CategoryModel::createTestCategoryModel();
  }
  
  Category* theCategory = 0;
  int theCategorySize = iCategoryModel->rowCount();

  for (int i = 0; i < theCategorySize + 1; i++)
  {
    CPtExpandableListViewItem* item = CPtExpandableListViewItem::create();
    CCNode* expandedView = 0;
    if (i == theCategorySize) {
      //add contacts thing
      theCategory = new Category();
      theCategory->setLabel("See what my contacts see");
    } else {
      theCategory = iCategoryModel->at(i);
    }
    
    
    if (i == theCategorySize) {
      expandedView = CCSprite::create("bed_icon.png");
      item->setDisplayView(expandedView);
      item->setIndex(i);
      array->addObject(item);
    } else {
      expandedView = createItemViewByType(theCategory->label().c_str(), i);
      item->setDisplayView(expandedView);
      
      item->setHandler(this,
                       callfuncO_selector(NewsHome::setNormal),
                       callfuncO_selector(NewsHome::setSelected),
                       callfuncO_selector(NewsHome::getChildren));
      item->setIndex(i);
      
      CCArray* entries = getEntriesForCategory(i);
      item->setChildrenItem(entries);
        //item->setSelected(); //TODO: should this be selected by default NO
      array->addObject(item);
    }
    
  } //end for
  
  CPtExpandableListViewItemList * expandList = CPtExpandableListViewItemList::create();
  expandList->setListViewItems(array);
  //expandList->setWhichOneOpen(theCategorySize - 1);
  expandList->setWhichOneOpen(theCategorySize);
  
  CCSize containerSize = CCDirector::sharedDirector()->getWinSize();
  containerSize.height = aHeight;
    //containerSize.height /= 2;
  
  CPtExpandableListView*  leftPanel = CPtExpandableListView::create(expandList,
                                                                    containerSize, //CCSizeMake(246, 515),
                                                                    CCSizeMake(0.0f, 0.0f));
  leftPanel->getTabelView()->setDelegate(this);
  leftPanel->setPosition(ccp(0, 0)); //ccp(220, 135));
  leftPanel->getTabelView()->setTouchPriority(-200);

  this->addChild(leftPanel, 10);
  
  m_pListView = leftPanel;
  return m_pListView;
}

void NewsHome::getChapters(int inMaxChapterId)
{
  iCategoryModel = CategoryModel::createTestCategoryModel();  
}

void NewsHome::getSections(int inSelectedChapterId, int inMaxSectionId)
{
  if (inMaxSectionId == -1)
  {
    m_nCurrentChapterId = inSelectedChapterId;
    return;
  }
  
  if (inSelectedChapterId >= 0 && inSelectedChapterId <= iCategoryModel->rowCount())
  {
    m_nCurrentChapterId = inSelectedChapterId;
  }

}

//#if 0
CCNode* NewsHome::testExpandableList(int aHeight)
{
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("items_bg.plist",  "items_bg.png");
  
  
  CCArray * array = CCArray::create();
  
    // CPtChapter * chapter = NULL;
  CPtExpandableListViewItem * item = NULL;
  
//  CCArray * sections = CCArray::create();
//  CPtSection * section = NULL;
//  
//  
//  int i = 0;
//    //  for (int i = 0; i <5; i++)
//  {
//    item = CPtExpandableListViewItem::create();
//      //section = (CPtSection *) m_pSections->objectAtIndex(i);
//    section = new CPtSection();
//    section->m_nSectionId = i;
//    std::string tmp("Section_test");
//    section->m_sSectionName = tmp;
//    
//    if (section)
//    {
//      item->setDisplayView(createItemViewByType(section->m_sSectionName.c_str(), i, CHILDRENT_TYPE));
//      item->setHandler(this,
//                       callfuncO_selector(NewsHome::setNormalInnerScrollableView),
//                       callfuncO_selector(NewsHome::setSelectedInnerScrollableView), NULL);
//      
//      item->setIndex(i);
//      item->setItemType(CHILDRENT_TYPE);
//      
//    }
//    sections->addObject(item);
//  }
  
    //TODO: Keep category list restricted to 6-8 for phase I
  iCategoryModel = CategoryModel::createTestCategoryModel();
  Category* theCategory = 0;
    //TODO: This is the main blue list
  int theCategorySize = iCategoryModel->rowCount();
    //for (int i = 0; i <m_pChapters->count(); i++)
  for (int i = 0; i < theCategorySize; i++)
  {
    item = CPtExpandableListViewItem::create();
    
    theCategory = iCategoryModel->at(i);
    
    item->setDisplayView(createItemViewByType(theCategory->label().c_str(), i));
    item->setHandler(this,
                     callfuncO_selector(NewsHome::setNormal),
                     callfuncO_selector(NewsHome::setSelected),
                     callfuncO_selector(NewsHome::getChildren));
    item->setIndex(i);
    
      //TODO: Create sections here which is Viewpagers items
    CCArray* entries = getEntriesForCategory(i);
    item->setChildrenItem(entries);
      //item->setSelected(); //TODO: should this be selected by default NO
    array->addObject(item);
    
  } //end for
  
  CPtExpandableListViewItemList * expandList = CPtExpandableListViewItemList::create();
  expandList->setListViewItems(array);
    //expandList->setWhichOneOpen(m_nMaxChapterId-1);
  expandList->setWhichOneOpen(theCategorySize - 1);
  
  
  CCSize containerSize = CCDirector::sharedDirector()->getWinSize();
  {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize size2 = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCLog( "getWinSize width = %f, height = %f", size.width, size.height );
    CCLog( "getFrameSize 2 width = %f, height = %f", size2.width, size2.height );
  }
  
  containerSize.height = aHeight;
    //containerSize.height /= 2;
  
  CPtExpandableListView*  leftPanel = CPtExpandableListView::create(expandList,
                                                                    containerSize, //CCSizeMake(246, 515),
                                                                    CCSizeMake(0.0f, 0.0f));
  leftPanel->getTabelView()->setDelegate(this);
  leftPanel->setPosition(ccp(0, 0)); //ccp(220, 135));
  leftPanel->getTabelView()->setTouchPriority(-200);
    //m_cMaps->getElementByTags("2,0")->addChild(leftPanel, 10);
  
    //viren+
    //  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    //  leftPanel->getTabelView()->setPosition(ccp(0,0));
    //  leftPanel->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
  
    //leftPanel->setAnchorPoint(ccp(0, 0));
    //viren-
  this->addChild(leftPanel, 10);
  
  m_pListView = leftPanel;
  
  
  
    //    row->addChild(m_pListView);
    //    parent->addChild(row);
  
  return m_pListView;
}
//#endif



void NewsHome::scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page)
{
  //CCLOG("NewsHome::scrollLayerScrolledToPageNumber , page = %d", page);
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


CCNode* NewsHome::createInnerScrollableView(const char* inTitle, int aItemNum, ITEM_TYPE inType)
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
//      entryView = CCSprite::create("orange.png");
//    } else {
//      entryView = CCSprite::create("red.png");
//    }
    if (i%2) {
      entryView = ExpandedViewPanel::create("violet.png", "aSmallTitle", "aMainMenuTitle",
                                            "aNewsTitle", "aNewsSummary");
    } else {
      entryView = CCSprite::create("red.png");
    }
    
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

CCNode* NewsHome::createItemViewByType(const char* inTitle, int aItemNum, ITEM_TYPE inType)
{
  CCSprite *sprite = NULL;
  CCLabelTTF* title = CCLabelTTF::create(inTitle, DEFAULT_FONT,
                                              DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 1.2f );
  title->setColor(ccWHITE);
  
  CCSize size ;
  if (inType == PARENT_TYPE)
  {
    //should generate something like item_1_bg.png
    char item_x_bg[26] = {0};
    sprintf(item_x_bg, "item_%d_bg.png", (aItemNum + 1));
    
    sprite = CCSprite::createWithSpriteFrameName(item_x_bg); //"tansuo2.png");
    size = sprite->getContentSize();
  }
  else if(inType == CHILDRENT_TYPE)
  {
    CCNode* theChildViewPager = createInnerScrollableView(inTitle, aItemNum, inType);
    size = theChildViewPager->getContentSize();
    //theChildViewPager->setPosition(ccp(120, size.height/2 - 50));
    
    return theChildViewPager;
    
    
//    sprite = CCSprite::createWithSpriteFrameName("tansuo3.png");
//    title->setColor(ccc3(252, 245, 191));
//    CCSprite* icon = CCSprite::createWithSpriteFrameName("tansuo7.png");
//    size = sprite->getContentSize();
//    sprite->addChild(icon, 0,2);
//    sprite->setPosition(ccp(120, size.height/2));
//    icon->setAnchorPoint(CCPointZero);
//    icon->setVisible(false);
  }
  else
  {
    return sprite;
  }
  title->setPosition(ccp(size.width/5,size.height/2));
  sprite->addChild(title, 0, 1);
  
  return sprite;
  
}

void NewsHome::setNormal(CCObject *pObject)
{
  CPtExpandableListViewItem *item = (CPtExpandableListViewItem*) pObject;
  CCSprite *sprite = NULL;
  if (item)
  {
    sprite = (CCSprite*) item->getDisplayView();
    if (item->getItemType() == PARENT_TYPE)
    {
      int aItemNum = item->getIndex();
      
      char item_x_bg[26] = {0};
      sprintf(item_x_bg, "item_%d_bg.png", (aItemNum + 1));
      
      sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(item_x_bg)); //"tansuo2.png"));
      
    }else if(item->getItemType() == CHILDRENT_TYPE)
    {
      ((CCLabelTTF*) sprite->getChildByTag(1))->setColor(ccc3(252, 245, 191));
      sprite->getChildByTag(2)->setVisible(false);
    }
  }
}

void NewsHome::setSelected(CCObject *pObject)
{
  CPtExpandableListViewItem *item = (CPtExpandableListViewItem*) pObject;
  CCSprite *sprite = NULL;
  if (item)
  {
    sprite = (CCSprite*) item->getDisplayView();
    if (item->getItemType() == PARENT_TYPE)
    {
      int aItemNum = item->getIndex();
      
      char item_x_bg[26] = {0};
      sprintf(item_x_bg, "item_%d_bg.png", (aItemNum + 1));
      
      sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(item_x_bg)); //"tansuo1.png"));
    }
    else if(item->getItemType() == CHILDRENT_TYPE)
    {
      ((CCLabelTTF*) sprite->getChildByTag(1))->setColor(ccc3(35, 255, 1));
      sprite->getChildByTag(2)->setVisible(true);
    }
  }
  
}

void NewsHome::setNormalInnerScrollableView(CCObject *pObject)
{
  CPtExpandableListViewItem *item = (CPtExpandableListViewItem*) pObject;
  CCSprite *sprite = NULL;
  if (item)
  {
    sprite = (CCSprite*) item->getDisplayView();
    if (item->getItemType() == PARENT_TYPE)
    {
      
      sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tansuo2.png"));
    }else if(item->getItemType() == CHILDRENT_TYPE)
    {
      ((CCLabelTTF*) sprite->getChildByTag(1))->setColor(ccc3(252, 245, 191));
      sprite->getChildByTag(2)->setVisible(false);
    }
  }
}

void NewsHome::setSelectedInnerScrollableView(CCObject *pObject)
{
  CPtExpandableListViewItem *item = (CPtExpandableListViewItem*) pObject;
  CCSprite *sprite = NULL;
  if (item)
  {
    sprite = (CCSprite*) item->getDisplayView();
    if (item->getItemType() == PARENT_TYPE)
    {
      sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tansuo1.png"));
    }else if(item->getItemType() == CHILDRENT_TYPE)
    {
      ((CCLabelTTF*) sprite->getChildByTag(1))->setColor(ccc3(35, 255, 1));
      sprite->getChildByTag(2)->setVisible(true);
    }
  }
  
}


CCArray* NewsHome::getEntriesForCategory(int aCategoryId)
{
  CCArray* entries = CCArray::create();
  
  EntriesModel* theEntriesModel = iEntriesModel[aCategoryId];
  int theEntriesModelCount = theEntriesModel->rowCount();
  
  theEntriesModelCount = 1; //<----------- TODO: If their are multiple entries, it shows weird results
  int i=0;
  if (i < theEntriesModelCount)
//  for(int i=0; i < theEntriesModelCount; i++)
  {
    CPtExpandableListViewItem* item = CPtExpandableListViewItem::create();
    Entry* entry = theEntriesModel->at(i);
    if (entry) {
      item->setDisplayView(createItemViewByType(entry->title().c_str(), i, CHILDRENT_TYPE));
      item->setHandler(this,
                       callfuncO_selector(NewsHome::setNormalInnerScrollableView),
                       callfuncO_selector(NewsHome::setSelectedInnerScrollableView), NULL);
      item->setIndex(i);
      item->setItemType(CHILDRENT_TYPE);
    }
//    if (aCategoryId == 0) {
      entries->addObject(item);
//    }
  } //end for
  
  return entries;
}


void NewsHome::getChildren(CCObject* pObject)
{
  CPtExpandableListViewItem* items = (CPtExpandableListViewItem*) pObject;
  if (items && items->getItemType() == PARENT_TYPE)
  {
//    int chapterId = items->getIndex();
//    EntriesModel* theEntriesModel = iEntriesModel[chapterId];
//    
//    if(chapterId >= 0 && chapterId < theEntriesModel->rowCount())
//    {
//      getSections(chapterId);
//      
//      CCArray * sections = CCArray::create();
//      CPtSection * section = NULL;
//      
//      for (int i = 0; i <m_pSections->count(); i++)
//      {
//        CPtExpandableListViewItem* item = CPtExpandableListViewItem::create();
//        section = (CPtSection *) m_pSections->objectAtIndex(i);
//        if (section)
//        {
//          item->setDisplayView(createItemViewByType(section->getSectionName().c_str(), CHILDRENT_TYPE));
//          item->setHandler(this, callfuncO_selector(NewsHome::setNormal), callfuncO_selector(NewsHome::setSelected), NULL);
//          item->setIndex(i);
//          item->setItemType(CHILDRENT_TYPE);
//        }
//        sections->addObject(item);
//      }
//      
//      items->setChildrenItem(sections);
//      
//    }
  }
}


void NewsHome::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    //    m_nSelectIndex = cell->getIdx();
    //    CCLog("touch which one: %d", cell->getIdx());
    //    CCArray *array = cell->getChildren();
    //    CCSprite * tmp = (CCSprite*) array->objectAtIndex(0);
    //    if (tmp == selectNode)
    //    {
    //    }else
    //    {
    //        if (selectNode!= NULL)
    //        {
    //            ((CCLabelTTF*) selectNode->getChildByTag(1))->setColor(ccWHITE);
    //
    //        }
    //
    //         selectNode = tmp;
    //        ((CCLabelTTF*) selectNode->getChildByTag(1))->setColor(ccRED);
    //
    //    }
    //    updatePanel(cell->getIdx(), m_bChapterMode);
  
    //viren+
  m_pListView->tableCellTouched(table, cell);
    //viren-
  
  int index = cell->getIdx();
  //CCLog("the id: %d", index);
//  int before =  m_pListView->getItems()->getWhichOneOpen();
  m_pListView->setOpenItemByIndex(index);
//  int afeter = m_pListView->getItems()->getWhichOneOpen();
  
//  CPtExpandableListViewItem* item = (CPtExpandableListViewItem*)(m_pListView->getItems()->getListViewItems()->objectAtIndex(before));
//  if (before == afeter)
//  {
//    int count =   index - before;
//    if (count != 0)
//    {
////      if( m_nCurrentSectionIndex != count-1)
////      {
////        if (m_nCurrentSectionIndex != -1)
////        {
////          ((CPtExpandableListViewItem*) item->getChildren()->objectAtIndex(m_nCurrentSectionIndex))->setNormal();
////        }
////        m_nCurrentSectionIndex = count-1;
////        ((CPtExpandableListViewItem*) item->getChildren()->objectAtIndex(m_nCurrentSectionIndex))->setSelected();
////        
////      }
//      
//    }
//    
//  }else
//  {
////    
////    item->setNormal();
////    if (m_nCurrentSectionIndex != -1)
////    {
////      ((CPtExpandableListViewItem*) item->getChildren()->objectAtIndex(m_nCurrentSectionIndex))->setNormal();
////    }
////    
////    m_nCurrentSectionIndex = -1;
////    item = (CPtExpandableListViewItem*)(m_pListView->getItems()->getListViewItems()->objectAtIndex(afeter));
////    item->setSelected();
//  }
////  m_nCurrentChapterId = afeter;
////  CCLog("the current: chapter: %d, section: %d selectId: %d", m_nCurrentChapterId, m_nCurrentSectionIndex, index);
//  
////  updatePanel(m_nCurrentChapterId, m_nCurrentSectionIndex);
}


CCScene* NewsHome::scene()
{
    CCScene *scene = CCScene::create();
    NewsHome *layer = NewsHome::create();
    scene->addChild(layer);
    return scene;
}

CCNode* NewsHome::addAppTitle()
{
  const CCSize& windowSize = CCDirector::sharedDirector()->getWinSize();
  const CCPoint helpPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.95f);//0.80f);
  CCLabelTTF* labelLabel = CCLabelTTF::create("vNews", DEFAULT_FONT,
                                              DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 2.5f );
  labelLabel->setColor(ccWHITE);
  labelLabel->setPosition(helpPoint);
  
  return labelLabel;
}

CCNode* NewsHome::addWeatherPanel(CCNode* row, CCNode* parent)
{
  WeatherPanel* weatherPanel = new WeatherPanel(row, parent);
  weatherPanel->init();
  weatherPanel->setAnchorPoint(ccp(0.5f, 0.5f));
  return weatherPanel;
}

void NewsHome::createLTaskManager()
{
  CCNode* task_manager = &LTaskManager::sharedManager();
  this->addChild(task_manager);
  task_manager->schedule(schedule_selector(LTaskManager::updateEvent), 0.5f, kCCRepeatForever, 0.3f);
}




void NewsHome::menu1Callback(CCObject* pSender)
{
  CCLOG("NewsHome::menu1Callback");
}

void NewsHome::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}






#include "AddFriendScene.h"
//#include "JsonBox.h"
#include "ExpandedViewPanel.h"
#include "VisibleRect.h"
#include "SceneManager.h"

using namespace cocos2d;

  //adjustment so that we can cover the collapsed row
#define EXPANDED_VIEW_Y_POSITION_ADJUSTMENT 20
#define EXPANDED_VIEW_HEIGHT 180
#define EXPANDED_VIEW_Y_ORDINATE ( (EXPANDED_VIEW_HEIGHT) - (EXPANDED_VIEW_Y_POSITION_ADJUSTMENT) )



CCScene* AddFriendScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        AddFriendScene *layer = AddFriendScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AddFriendScene::init()
{
    bool bRet = false;
  iCategoryModel = 0;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        selectedindex = -1;
        btnTouched = false;

        mFriendList= CCArray::create();
        mFriendList->retain();
      
        //CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255)); //WHITE
        CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 55, 55, 55));
        addChild(backgroundColor);
      
      /*
       * Initialize HudLayer
       */
      _hudLayer = HudLayer::create();
      this->addChild(_hudLayer, 20);
      
     // _hudLayer->updateLives(this->_totalLife);

      
      
      CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("items_bg.plist",  "items_bg.png");      
      if (!iCategoryModel) {
        iCategoryModel = CategoryModel::createTestCategoryModel();
      }

      createEntriesForCateogries();
      
      m_pBolasSprites = CCArray::create();
      m_pBolasSprites->retain();

        onNodeLoaded(0,0);
        //viren+
      
      
        bRet = true;
    } while (0);

    return bRet;
}

#define SEARCH_BOX_PADDING_TOP 16
#define SEARCH_BOX_HEIGHT 36
#define SEARCH_BOX_Y_ORDINATE(CCSIZE) ( (CCSIZE.height) - ( SEARCH_BOX_HEIGHT / 2 ) ) - SEARCH_BOX_PADDING_TOP


void AddFriendScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
  CCSize containerSize = CCDirector::sharedDirector()->getWinSize();
  
  
  m_txtSearchField = CCEditBox::create(CCSizeMake(210, SEARCH_BOX_HEIGHT),
                                      CCScale9Sprite::create("yellow_edit.png")); //"transparent.png"));
  m_txtSearchField->retain();
  //m_txtSearchField->setPosition(ccp(138, 348));
  m_txtSearchField->setPosition(ccp(138, SEARCH_BOX_Y_ORDINATE(containerSize) )); //480-36/2)); //viren
  m_txtSearchField->setFontColor(ccc3(0,0,0));
  m_txtSearchField->setFont(FONT_LOGIN, 16);
  m_txtSearchField->setZOrder(99);
  this->addChild(m_txtSearchField);
  
  CCSize searchFieldPanelSize = m_txtSearchField->getContentSize();
  
  mTableViewFriend = CCTableView::create(this, CCSizeMake(containerSize.width, containerSize.height - searchFieldPanelSize.height - SEARCH_BOX_PADDING_TOP*2 ));
  mTableViewFriend->retain();
  mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
  mTableViewFriend->setVerticalFillOrder(kCCTableViewFillTopDown);
  mTableViewFriend->setDataSource(this);
  //mTableViewFriend->setViewSize(CCSizeMake(312, 300));
  mTableViewFriend->setDelegate(this);
  //  mTableViewFriend->reloadData(); //<----load up here?
  mTableViewFriend->setTouchPriority(-200);
  this->addChild(mTableViewFriend);

}

void AddFriendScene::buttonClicked(CCObject *pSender,CCControlEvent event)
{
	CCLOG("i was clicked");
    
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)pSender;
	switch (button->getTag()) {
	case 101:
		CCLOG("11111");
		mainScene->PopLayer();
		break;
	case 102:
		mainScene->PopLayer();
		break;
	case 103:
		this->doSearchFriend();
		break;
	}
}

void AddFriendScene::doSearchFriend()
{
	std::string sSearchField(m_txtSearchField->getText());
	sSearchField = trimRight(sSearchField);

	if (sSearchField.empty()) {
		CCMessageBox("AddFriendScene::doSearchFriend : searchField empty","ERROR");
		return;
	}

	this->ShowLoadingIndicator("Viren, it is Loading...");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(AddFriendScene::requestFinishedCallback));
	request->setTag("101");
    
	string _strUrl = CompleteUrl(URL_FRIEND_SEARCH);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/");
	_strUrl.append(sSearchField);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void AddFriendScene::addFriendRequest(std::string &targetUser)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(AddFriendScene::requestFinishedCallback));
	request->setTag("102");
    
	string _strUrl = CompleteUrl(URL_FRIEND_ADD_NEW);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void AddFriendScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
//	if (!this->ValidateResponseData(client,response))
//	{
//		return;
//	}
//    
//    std::vector<char> *buffer = response->getResponseData();
//	std::string content(buffer->begin(),buffer->end());
//    
//	CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
//	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
//	if (code != 200) {
//		if (code == 121) {
//			 CCMessageBox(GlobalData::getLocalString("friend_add_exist")->getCString(),"Success");
//		}
//		
//		return;
//	}
//    
//    std::string requestTag(response->getHttpRequest()->getTag());
//    
//    if (requestTag == "101") {
//		mFriendList->removeAllObjects();
//		CCDictionary * friendDictionary = dynamic_cast<CCDictionary *>(dictionary->objectForKey("searchUserAccount"));
//		if (friendDictionary != NULL)
//		{
//			  mFriendList->addObject(friendDictionary);
//		}
//        char strCount[20];
//        sprintf(strCount,"%d",mFriendList->count());
//        m_lblSearchCount->setString(strCount);
//        
//		selectedindex = -1;
//		this->mTableViewFriend->reloadData();
//    } else if (requestTag == "102"){
//       CCMessageBox(GlobalData::getLocalString("friend_add_success")->getCString(),"Success");
//    }
}


void AddFriendScene::toolBarTouchDownAction(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCControlButton *button = (CCControlButton *)pSender;
//	if (pCCControlEvent==CCControlEventTouchDown)
//	{
//		btnTouched = true;
//	}
//	else if (pCCControlEvent==CCControlEventTouchUpInside)
//	{
//		switch (button->getTag()) {
//		case 128:
//			{
//				btnTouched = false;
//				MainGameScene *mainScene = (MainGameScene *)this->getParent();
//				mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
//			}
//			break;
//		case 129:
//			{
//				btnTouched = false;
//				CCMessageDialog *box = CCMessageDialog::create();
//				box->setTitle(GlobalData::getLocalString("friend_add_confirm")->getCString());
//				box->setDelegate(this);
//				this->addChild(box);
//			}
//			break;
//		default:
//			break;
//		}
//	}
}

void AddFriendScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
//	CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//	sSelected->setVisible(true);


  CCSize size = this->cellSizeForTable(table); // CCSizeMake(312, 50);
  CCLayerColor* mask;
//  if(isV)
//    mask = CCLayerColor::create(ccc4(200, 0, 0, 100), 200, 80);
//  else
//    mask = CCLayerColor::create(ccc4(200, 0, 0, 100), 80, 200);

mask = CCLayerColor::create(ccc4(200, 0, 0, 100), size.width, size.height);

  cell->addChild(mask,100, 44);

}

void AddFriendScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
//	CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//	sSelected->setVisible(false);
cell->removeChildByTag(44, true);
}

void AddFriendScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
	if (btnTouched)
	{
		return;
	}
    if (selectedindex == cell->getIdx()) {
        selectedindex = -1;
    } else {
        selectedindex = cell->getIdx();
    }
  
  SceneManager* sceneMgr = SceneManager::shareSceneManager();
  if (sceneMgr) {
    sceneMgr->toScrollerScene(this);
  }
  
 //   table->reloadData();
}

unsigned int AddFriendScene::numberOfCellsInTableView(CCTableView *table)
{
//testing
  return iCategoryModel->rowCount();
//  if(mFriendList) {
//    return mFriendList->count();
//  }
//  return 0;
}

CCSize AddFriendScene::cellSizeForTable(CCTableView *table)
{
#if 0 //original
	return CCSizeMake(312, 50);
#endif

  return CCSizeMake(312, 50);
}

CCSize AddFriendScene::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
#if 0 //original
    if (selectedindex == idx ) {
        return CCSizeMake(312, 80);
    }
    return CCSizeMake(312, 50);
#endif
#if 0
  if (selectedindex == idx ) {
    return CCSizeMake(312, EXPANDED_VIEW_HEIGHT);
  }
#endif
  return cellSizeForTable(table);
}

void AddFriendScene::scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page)
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

void AddFriendScene::createEntriesForCateogries() {
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



CCScrollLayer* AddFriendScene::createInnerScrollableView(const char* inTitle, int aItemNum, ITEM_TYPE inType)
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
//      entryView = CCSprite::create("blue.png");
//    } else {
//      entryView = CCSprite::create("red.png");
//    }
   // entryView->setVisible(true);
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



CCTableViewCell* AddFriendScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	//CCDictionary *dict = (CCDictionary *)mFriendList->objectAtIndex(idx);
	bool selected = (idx==selectedindex);
	CCTableViewCell *cell = table->dequeueCell();
  
  Category* theCategory = 0;
  int theCategorySize = iCategoryModel->rowCount();
  theCategory = iCategoryModel->at(idx);
  
  
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();

		CCSize size = this->tableCellSizeForIndex(table, idx);

//		CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_cellhighlight.png"));
//		sSelected->setVisible(false);
//		sSelected->setTag(121);
//		sSelected->setPosition(ccp(13,size.height - 39));
//		sSelected->setAnchorPoint(CCPointZero);
//		cell->addChild(sSelected);
    
//    {
//    #if 0 //for testing
//      CCNode* entryView = ExpandedViewPanel::create("violet.png", "aSmallTitle", "aMainMenuTitle",
//                                              "aNewsTitle", "aNewsSummary");
//      entryView->setVisible(false);
//      entryView->setTag(121);
//      entryView->setPosition(ccp(13,size.height - EXPANDED_VIEW_Y_ORDINATE));
//      entryView->setAnchorPoint(CCPointZero);
//      entryView->setZOrder(99);
//      cell->addChild(entryView);
//    #endif
//      EntriesModel* theEntriesModel = iEntriesModel[idx];
//      int theEntriesModelCount = theEntriesModel->rowCount();
//      int i=0;
//    Entry* entry = theEntriesModel->at(i);
//    
//    CCLOG("this calls for one time???");
//    
//      CCScrollLayer* entryView = createInnerScrollableView(theCategory->label().c_str(), idx, CHILDRENT_TYPE);
//      entryView->setVisible(false);
//      entryView->setTag(121);
//      entryView->setPosition(ccp(13,size.height - EXPANDED_VIEW_Y_ORDINATE));
//      entryView->setAnchorPoint(CCPointZero);
//      entryView->setZOrder(99);
//      cell->addChild(entryView);
//      
//    }

//		CCSprite *sGroup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_dairy.png"));
    CCSprite *sGroup = CCSprite::create("friends_dairy.png");
		sGroup->setTag(122);
		sGroup->setPosition(ccp(11,size.height - CELL_ITEMS_Y - 10));
		sGroup->setAnchorPoint(CCPointZero);
		cell->addChild(sGroup);

//		CCLabelTTF *lblName = CCLabelTTF::create(dict->valueForKey("username")->getCString(), "Arial", 14.0);
    CCLabelTTF *lblName = CCLabelTTF::create("UserName", "Arial", 14.0);
		lblName->setPosition(ccp(51,size.height - CELL_ITEMS_Y));
		lblName->setAnchorPoint(CCPointZero);
		lblName->setColor(ccc3(248, 255, 38));
		lblName->setTag(123);
		cell->addChild(lblName);

		CCLabelTTF *lblLevel = CCLabelTTF::create("LV. 3", "Arial", 14.0);
		lblLevel->setPosition(ccp(165,size.height - CELL_ITEMS_Y));
		lblLevel->setAnchorPoint(CCPointZero);
		lblLevel->setColor(ccc3(248, 255, 38));
		lblLevel->setTag(124);
		cell->addChild(lblLevel);

		CCLabelTTF *lblFriend = CCLabelTTF::create("yishengsuoai", "Arial", 14.0);
		lblFriend->setPosition(ccp(218,size.height - CELL_ITEMS_Y));
		lblFriend->setAnchorPoint(CCPointZero);
		lblFriend->setColor(ccc3(248, 255, 38));
		lblFriend->setTag(125);
		cell->addChild(lblFriend);

		CCLabelTTF *lblStatus = CCLabelTTF::create("100", "Arial", 14.0);
		lblStatus->setPosition(ccp(283,size.height - CELL_ITEMS_Y));
		lblStatus->setAnchorPoint(CCPointZero);
		lblStatus->setColor(ccc3(248, 255, 38));
		lblStatus->setTag(126);
		cell->addChild(lblStatus);

//		int length = rand()%5;
		CCLayer *layer = CCLayer::create();
		layer->setTag(131);
		cell->addChild(layer);

		for (int i=0; i<5; i++) {
			CCSprite *sFriendheart = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_love.png"));
			sFriendheart->setPosition(ccp(218 + CELL_LOVE_XGAP * i,size.height - CELL_ITEMS_Y - 15));
			sFriendheart->setAnchorPoint(CCPointZero);
			layer->addChild(sFriendheart);
		}

		//CCControlButton * msgBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_emailbtn.png")));
//		CCControlButton * msgBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName("btn_bg.png"));

//    CCScale9Sprite* btnBg = CCScale9Sprite::create("green_edit.png");
//    CCControlButton * msgBtn = CCControlButton::create(btnBg);
//
//		msgBtn->setTitleBMFontForState("btn.fnt", CCControlStateNormal);
//		msgBtn->setTitleForState(CCString::create("信件"),CCControlStateNormal);
//		msgBtn->setPosition(ccp(81,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
//		msgBtn->setAnchorPoint(ccp(0,0.5));
//		msgBtn->setTag(128);
//		msgBtn->setPreferredSize(CCSizeMake(75,35));
//		msgBtn->setVisible(selected);
//		msgBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarTouchDownAction), CCControlEventTouchDown);
//		msgBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
//		cell->addChild(msgBtn);

		//CCControlButton * formationBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_cell_addfriend.png")));
        
//		CCControlButton * formationBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName("btn_bg.png"));
//		formationBtn->setTitleBMFontForState("btn.fnt", CCControlStateNormal);
//		formationBtn->setTitleForState(CCString::create("好友"),CCControlStateNormal);
//		formationBtn->setPosition(ccp(158,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
//		formationBtn->setAnchorPoint(ccp(0,0.5));
//		formationBtn->setTag(129);
//		formationBtn->setPreferredSize(CCSizeMake(74,34));
//		formationBtn->setVisible(selected);
//		formationBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarTouchDownAction), CCControlEventTouchDown);
//		formationBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
//		cell->addChild(formationBtn);
	}
	else
	{
		CCSize size = this->tableCellSizeForIndex(table, idx);

//#if 0 //for testing
//		//CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//    CCNode *entryView = (CCNode*)cell->getChildByTag(121);
//		entryView->setPosition(ccp(13,size.height - EXPANDED_VIEW_Y_ORDINATE));
//		if (selectedindex == idx ) {
//			entryView->setVisible(true);
//      entryView->setZOrder(99);
//		} else {
//			entryView->setVisible(false);
//		}
//#endif
//{
//  CCScrollLayer *entryView = (CCScrollLayer*)cell->getChildByTag(121);
//  entryView->setPosition(ccp(13,size.height - EXPANDED_VIEW_Y_ORDINATE));
//  CCLOG("selectedindex : %d, idx = %d", selectedindex, idx);
//  if (selectedindex == idx ) {
//    CCLOG("selectedindex == idx so show expanded view");
//    entryView->setVisible(true);
////    entryView->setZOrder(99);
//  } else {
//  CCLOG("selectedindex != idx so DONT show expanded view");
//    entryView->setVisible(false); //OIGINAL
//    //entryView->setVisible(true);
//   // entryView->setZOrder(-99);
//  }
//
//}

		CCSprite *sGroup = (CCSprite*)cell->getChildByTag(122);
		sGroup->setPosition(ccp(sGroup->getPosition().x,size.height - CELL_ITEMS_Y - 10));

		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
//		lblName->setString(dict->valueForKey("username")->getCString());
    lblName->setString("username");
		lblName->setPosition(ccp(lblName->getPosition().x,size.height - CELL_ITEMS_Y));

		CCLabelTTF *lblLevel = (CCLabelTTF*)cell->getChildByTag(124);
		//lblLevel->setString(string->getCString());
		lblLevel->setPosition(ccp(lblLevel->getPosition().x,size.height - CELL_ITEMS_Y));

		CCLabelTTF *lblFriend = (CCLabelTTF*)cell->getChildByTag(125);
		//		lblFriend->setString(string->getCString());
		lblFriend->setPosition(ccp(lblFriend->getPosition().x,size.height - CELL_ITEMS_Y));

		CCLabelTTF *lblStatus = (CCLabelTTF*)cell->getChildByTag(126);
		//		lblStatus->setString(string->getCString());
		lblStatus->setPosition(ccp(lblStatus->getPosition().x,size.height - CELL_ITEMS_Y));

		//        CCScale9Sprite *background = (CCScale9Sprite *)cell->getChildByTag(121);
		//        background->setContentSize(size);

		//CCControlButton *chatBtn = (CCControlButton *)cell->getChildByTag(127);
		//chatBtn->setPosition(ccp(chatBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		//chatBtn->setVisible(selected);

//		CCControlButton *msgBtn = (CCControlButton *)cell->getChildByTag(128);
//		msgBtn->setPosition(ccp(msgBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
//		msgBtn->setVisible(selected);

//		CCControlButton *formationBtn = (CCControlButton *)cell->getChildByTag(129);
//		formationBtn->setPosition(ccp(formationBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
//		formationBtn->setVisible(selected);

		//CCControlButton *deleteBtn = (CCControlButton *)cell->getChildByTag(130);
		//deleteBtn->setPosition(ccp(deleteBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		//deleteBtn->setVisible(selected);

		CCLayer *heartLayer = (CCLayer *)cell->getChildByTag(131);
		CCArray *array = heartLayer->getChildren();
		if (array!=NULL) {
			for (int i=0; i<array->count(); i++) {
				CCSprite *sprite = (CCSprite *)array->objectAtIndex(i);
				sprite->setPosition(ccp(sprite->getPosition().x,size.height - CELL_ITEMS_Y - 15));
			}
		}
	}

	return cell;
}

AddFriendScene::AddFriendScene()
{
    mTableViewFriend = NULL;
    mFriendList = NULL;
    m_txtSearchField = NULL;
    m_lblSearchCount = NULL;
  
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("friends.plist");
}

AddFriendScene::~AddFriendScene()
{
   mFriendList->release();
    CC_SAFE_RELEASE(mTableViewFriend);
    CC_SAFE_RELEASE(m_lblSearchCount);
    CC_SAFE_RELEASE(m_txtSearchField);
}

void AddFriendScene::didClickButton(CCMessageDialog* dialog,unsigned int index)
{
	if (index == 0)
	{
		CCDictionary *dict = (CCDictionary *)mFriendList->objectAtIndex(selectedindex);
    string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
		this->addFriendRequest(encryptedUserInfo);
	}
}

//SEL_CCControlHandler AddFriendScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
//  
//  CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", AddFriendScene::buttonClicked);
//	return NULL;
//}



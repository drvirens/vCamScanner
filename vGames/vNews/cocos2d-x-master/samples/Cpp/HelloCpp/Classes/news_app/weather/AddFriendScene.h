#ifndef __ADDFRIENDSCENE_SCENE_H__
#define __ADDFRIENDSCENE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"
#include "MainGameScene.h"
//#include "MainOuterLayer.h"
#include "Common/common.h"
#include "StringExt.h"
#include "CCMessageDialog.h"

#include "feedly/models/bk/categorymodel.h"
#include "feedly/models/entriesmodel.h"
#include "CCScrollLayer.h"
#include "news_app/homeUI/HomeUIConfig.h"

#include "news_app/hud/HudLayer.h"


using namespace cocos2d;
using namespace cocos2d::extension;

class AddFriendScene : public MainLayerBase,
public CCTableViewDataSource,
public CCTableViewDelegate,
public CCScrollLayerDelegate, 
//public CCBSelectorResolver,
//public CCNodeLoaderListener,
//public CCBMemberVariableAssigner,
public CCMessageDialogDelegate
{
public:
  enum ITEM_TYPE
  {
    PARENT_TYPE = 0,
    CHILDRENT_TYPE = 1
  };
  
CCScrollLayer* createInnerScrollableView(const char* inTitle, int aItemNum, ITEM_TYPE inType = PARENT_TYPE);
    //scroll layer
  void scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page);
  CCArray* getEntriesForCategory(int aCategoryId);
  void createEntriesForCateogries();
  
  HudLayer* _hudLayer;
  
  /////////////
  
    AddFriendScene();
    ~AddFriendScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);
    void doSearchFriend();
    void addFriendRequest(std::string &userinfo);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AddFriendScene, create);
    
	void buttonClicked(CCObject *pSender,CCControlEvent event);
    
    void toolBarTouchDownAction(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
	virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);

	virtual void didClickButton(CCMessageDialog* dialog,unsigned int index);
  
  virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
  


private:
	CCEditBox *m_txtSearchField;
    CCTableView* mTableViewFriend;
    unsigned int selectedindex;
    CCArray *mFriendList;
  CategoryModel* iCategoryModel; //collapsed view
  EntriesModel* iEntriesModel[kHomeUI_MaxCategories]; // 6
  CCArray *iNewsViewPager;
  CCArray *m_pBolasSprites; //page indicator

	bool btnTouched;
private:
    CCLabelTTF *m_lblSearchCount;
};

#endif  // __LOGINSCENE_SCENE_H__
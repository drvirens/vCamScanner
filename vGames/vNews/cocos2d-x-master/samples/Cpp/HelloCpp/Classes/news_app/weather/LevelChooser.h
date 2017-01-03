#ifndef __Level_Chooser_H__
#define __Level_Chooser_H__

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
#include "ExpandedViewPanel.h"
#include "VisibleRect.h"

using namespace cocos2d;

class LevelChooser: public CCLayer, public CCScrollLayerDelegate
{
public:

  //viren+
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
  
  CategoryModel* iCategoryModel; //collapsed view
  EntriesModel* iEntriesModel[kHomeUI_MaxCategories]; // 6
  CCArray *iNewsViewPager;
  CCArray *m_pBolasSprites; //page indicator
  
//viren-


	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();
	static cocos2d::CCScene* scene();
	void backCallback(CCObject* pSender);
	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(LevelChooser);
};


class LevelLayer : public CCLayer {

private:
    virtual void onEnter();
    virtual void onExit();
    
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *withEvent);
    
    void gameSceneCallback();
    bool containsTouchLocation(CCTouch* touch);
    CCRect rect();
	int levlNo;

public:
	LevelLayer(const char *picName, int levlNo);
	~LevelLayer();
	CCSprite* pSpriteLvl;
};

#endif // __Level_Chooser_H__

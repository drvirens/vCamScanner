//
//  TutorialScreen.h
//  HelloCpp
//
//  Created by Virendra Shakya on 12/9/13.
//
//

#ifndef __HelloCpp__TutorialScreen__
#define __HelloCpp__TutorialScreen__

#include "cocos2d.h"
#include "CCScrollLayer.h"

USING_NS_CC;

class TutorialScreen : public CCLayer, public CCScrollLayerDelegate
{
 public:
  TutorialScreen();
  virtual ~TutorialScreen();
  
  virtual bool init();
  
    //viren+
  enum ITEM_TYPE
  {
    PARENT_TYPE = 0,
    CHILDRENT_TYPE = 1
  };
  
  CCScrollLayer* createInnerScrollableView(const char* inTitle, int aItemNum, ITEM_TYPE inType = PARENT_TYPE);
  void createEntriesForCateogries();
  
  //CCScrollLayerDelegate
		/** Called when scroll layer begins scrolling.
		 * Usefull to cancel CCTouchDispatcher standardDelegates.
		 */
  virtual void scrollLayerScrollingStarted(CCScrollLayer* sender);
    
		/** Called at the end of moveToPage:
		 * Doesn't get called in selectPage:
		 */
  virtual void scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page);
  
  
	static cocos2d::CCScene* scene();
  void backCallback(CCObject* pSender);
  
 private:
  CREATE_FUNC(TutorialScreen);
  
//  CategoryModel* iCategoryModel; //collapsed view
//  EntriesModel* iEntriesModel[kHomeUI_MaxCategories]; // 6
  CCArray *iNewsViewPager;
  CCArray *m_pBolasSprites; //page indicator
  CCScrollLayer* pScrollLevelLayer;

};

#endif /* defined(__HelloCpp__TutorialScreen__) */

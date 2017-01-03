#ifndef __NewsHome_SCENE_H__
#define __NewsHome_SCENE_H__

#include <list>

#include "cocos2d.h"
#include "Core/Widget.h"
#include "CPtExpandableListView.h"
#include "CCScrollLayer.h"

#include "cocos-ext.h"

#include "feedly/models/bk/categorymodel.h"
#include "feedly/models/entriesmodel.h"

#include "VirenBaseLayer.h"

#include <vector>

#include "CPtListViewWidget.h"
#include "CPtTableItem.h"

#include "CPtExpandableListView.h"
#include "news_app/homeUI/HomeUIConfig.h"

using namespace cocos2d;
using namespace cocos2d::extension;


USING_NS_CC_EXT;
USING_NS_CC;
using namespace cocos2d::extension;



class NewsHome : public CCLayer, //VirenBaseLayer,
                  public CCTableViewDelegate,
                  public CCScrollLayerDelegate
{
private:
    //test expandablelist
  CCNode* testExpandableList(int aHeight);

  CPtExpandableListView *m_pListView;
  virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
  /**
   * Delegate to respond a table cell press event.
   *
   * @param table table contains the given cell
   * @param cell  cell that is pressed
   */
  virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){};
  
  /**
   * Delegate to respond a table cell release event
   *
   * @param table table contains the given cell
   * @param cell  cell that is pressed
   */
  virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){};
  


  virtual void scrollViewDidScroll(CCScrollView* view){};
  virtual void scrollViewDidZoom(CCScrollView* view){};
  
  //scroll layer
  void scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page);
  
  
  CCNode* createInnerScrollableView(const char* inTitle, int aItemNum, ITEM_TYPE inType = PARENT_TYPE);
  

  CCNode* createItemViewByType(const char* inTitle, int aItemNum, ITEM_TYPE inType = PARENT_TYPE);
  void setNormal(CCObject *pObject);
  void setSelected(CCObject *pObject);
  
  void getChildren(CCObject* pObject);
  
  void setNormalInnerScrollableView(CCObject *pObject);
  void setSelectedInnerScrollableView(CCObject *pObject);
  
  CCNode* addAppTitle();
  CCNode* addWeatherPanel(CCNode* row, CCNode* parent);
  void createLTaskManager();
  
private:
  Widget* _weather_widget;
  

  Category* iCurrentSelectedCategory;
  
  CCArray *iNewsViewPager;
  CCArray *m_pBolasSprites; //page indicator
  
  
  //viren+ final
  
//  CCArray *m_pChapters; //parent = row
//  CCArray *m_pSections; //children = expanded views

  CategoryModel* iCategoryModel; //collapsed view
  EntriesModel* iEntriesModel[kHomeUI_MaxCategories]; // 6 categories only for phase 1

  int m_nMaxChapterId;
  int m_nMaxSectionId;
  
  int m_nCurrentChapterId;
  int m_nCurrentSectionId;
  
  int m_nCurrentSectionIndex;
  
  CCNode* addCategoryPanel(int aHeight);
  void getChapters(int inMaxChapterId);
  void getSections(int inSelectedChapterId, int inMaxSectionId = -1);
  
  CCArray* getEntriesForCategory(int aCategoryId);
  void createEntriesForCateogries();


  //viren- final
  
  
public:
  NewsHome();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
  

  void menu1Callback(CCObject* pSender);

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(NewsHome);

};

#endif // __NewsHome_SCENE_H__

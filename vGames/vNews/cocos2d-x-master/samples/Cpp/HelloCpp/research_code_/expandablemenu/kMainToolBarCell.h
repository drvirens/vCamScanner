//
//  kMainToolBar.h
//
//  Created by kael on 1/8/13.
//
//

#ifndef __kMainToolBar__
#define __kMainToolBar__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
#define TOOLBARCELL_HERO 1
#define TOOLBARCELL_BAG  2
#define TOOLBARCELL_CARD 3
#define TOOLBARCELL_QUEST 4

// cell for each toolbar unit
class kMainToolBarCell:public cocos2d::CCLayer
{
public:
    ~kMainToolBarCell();
    kMainToolBarCell(unsigned short _t);
//    virtual bool init();
//    CREATE_FUNC(kMainToolBarCell);
    void iambeclick(CCObject* pSender,CCControlEvent*);
    void setType(const unsigned short& t){_type = t;}
    unsigned short getType()const{return _type;}
    void onExpand(const CCPoint& target,float dur);
    void onCompact(const CCPoint& target,float dur);
    unsigned short getW()const{return _w;}
    unsigned short getH()const{return _h;}
protected:
    unsigned short _type;
    unsigned short _w;
    unsigned short _h;
    CCControlButton* content;
};

#endif /* defined(__kMainToolBar__) */

//
//  Bz_gameControl.h
//  Bz_gameControl
//
//  Created by Binz_- on 13-6-26.
//
//

#ifndef __Bz_gameControl__Bz_gameControl__
#define __Bz_gameControl__Bz_gameControl__


#include <iostream>
#include "cocos2d.h"

/*****
 使用方法：
    1、在所在类里面导入此类的标示符：
        例如：HellloWorld.cpp   
                 extern const char* moveLeft;
                 extern const char* moveRight;
                 extern const char* jump;
    2、所在类里面，将需要关联的函数于观察者中心的标示符连接。
        例如：HellloWorld.cpp 
                 ADD_OBSERVER(moveLeft, HelloWorld::leftMoving);
                 ADD_OBSERVER(moveRight, HelloWorld::rightMoving);
                 ADD_OBSERVER(jump, HelloWorld::jumpping);
    3、具体查看HelloWorld的用法。
 *****/

#define POST_MSG(_MsgTag_) CCNotificationCenter::sharedNotificationCenter()->postNotification(_MsgTag_,this)
#define POST_MSG_WITH(_MsgTag_,_SENDER_) CCNotificationCenter::sharedNotificationCenter()->postNotification(_MsgTag_,_SENDER_)
#define ADD_OBSERVER(_MsgTag_,_CALLBACK_) CCNotificationCenter::sharedNotificationCenter()->addObserver(this,\
callfuncO_selector(_CALLBACK_),_MsgTag_, NULL)
#define DEL_OBSERVER(_MsgTag_) CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,_MsgTag_)

class Bz_btnItem;
using namespace cocos2d;
class gameControl:public CCLayer{
    
private:
    bool m_bIsTouchEventHappenInBtnBegin;//按钮事件促发位置
public:
    /*****
     按钮促发事件设置、访问方法
     *****/
    inline void setTouchEventHappenInBtnBegin(bool isbegin){m_bIsTouchEventHappenInBtnBegin = isbegin;}
    inline bool getTouchEventHappenInBtnBegin(){return m_bIsTouchEventHappenInBtnBegin;}
    
    
private:
    Bz_btnItem *m_leftBtn;
    Bz_btnItem *m_rightBtn;
    Bz_btnItem *m_jumpBtn;
    
protected:
    CCSize winSize;
    //初始化按钮数据
    void initWithButton();
    //获取按钮矩形框
    CCRect getBtnRect(Bz_btnItem *btn);
    
    
    
    
public:
    bool init();
    CREATE_FUNC(gameControl);
    

protected:
    /*****
     点击促发事件
     *****/
    //处理点击事件
    void doWithTouchEvent(CCPoint btnPos);
    void doWithMoveTouchEvent(CCSet *pTouch);
    void removeTouchEvent(CCPoint endPos);
    //判断是否点中按钮
    bool judgeIsTouchedBtn(CCPoint btnPos,CCRect btnRect);
    //在通知中心标志事件，以便其他地方可以接收到访问
    void postToNotificationCenter();
    
    
    /*****
     触摸事件
     *****/
    virtual void registerWithTouchDispatcher();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);
    /*生命周期*/
    virtual void onExit();
    
    /*****
     更新
     *****/
    void update(float dt);
    
    
};

#endif /* defined(__Bz_gameControl__Bz_gameControl__) */

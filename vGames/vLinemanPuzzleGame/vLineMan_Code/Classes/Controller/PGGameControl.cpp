//
//  Bz_gameControl.cpp
//  Bz_gameControl
//
//  Created by Binz_- on 13-6-26.
//
//

#include "PGGameControl.h"
#include "PGBtnItem.h"

const char * doSomething = "doSomething";

const char* moveLeft = "leftMoving";
const char* moveRight = "RightMoving";
const char* jump = "jumpping";
 

bool gameControl::init(){
    if (!CCLayer::init()) return false;
    /*屏幕大小*/
    winSize = CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    m_bIsTouchEventHappenInBtnBegin = true;
    /*按钮纹理*/
    CCTexture2D* t1 = CCTextureCache::sharedTextureCache()->addImage("control_btn2.png");
    CCTexture2D* t2 = CCTextureCache::sharedTextureCache()->addImage("control_btn1.png");
    
    /*按钮*/
    m_leftBtn = Bz_btnItem::createWithNormalTexAndSelectedTex(t1, t2);
    m_rightBtn = Bz_btnItem::createWithNormalTexAndSelectedTex(t1, t2);
    m_jumpBtn = Bz_btnItem::createWithNormalTexAndSelectedTex(t1, t2);
    
    
    //    m_leftBtn = Bz_btnItem::createWithNormalFileAndSelectedFile("跳跃.png", "跳跃2.png");
    //    m_rightBtn = Bz_btnItem::createWithNormalFileAndSelectedFile("跳跃.png", "跳跃2.png");
    //    m_jumpBtn = Bz_btnItem::createWithNormalFileAndSelectedFile("跳跃.png", "跳跃2.png");
    //
    
    
    initWithButton();//初始化设置按钮数据
    
    
    /*添加对象*/
    addChild(m_leftBtn);
    addChild(m_rightBtn);
    addChild(m_jumpBtn);
    scheduleUpdate();
        
    return true;
}
void
gameControl::initWithButton(){
    /*位置*/
    m_leftBtn->setPosition(ccp(winSize.width/8,
                               winSize.height/8));
    m_rightBtn->setPosition(ccp(winSize.width*2/8+20,
                                winSize.height/8));
    m_jumpBtn->setPosition(ccp(winSize.width*7/8,
                               winSize.height/8));
    /*旋转*/
    m_leftBtn->setRotation(-90);
    m_rightBtn->setRotation(90);
    m_jumpBtn->setRotation(0);
    
}

void
gameControl::postToNotificationCenter(){
    if(m_leftBtn->getIsSelect()) POST_MSG(moveLeft);
    if(m_rightBtn->getIsSelect()) POST_MSG(moveRight);
    if(m_jumpBtn->getIsSelect()) POST_MSG(jump);
}

CCRect
gameControl::getBtnRect(Bz_btnItem *btn){
    CCSize s = btn->getContentSize();
    return CCRectMake(btn->getPosition().x - s.width/2, btn->getPosition().y - s.height/2, s.width, s.width);
}

bool
gameControl::judgeIsTouchedBtn(cocos2d::CCPoint pos, cocos2d::CCRect rect){
    if (rect.containsPoint(pos))
        return true;
    return false;
}

void
gameControl::update(float dt){
    postToNotificationCenter();
}

void gameControl::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void gameControl::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void
gameControl::ccTouchesBegan(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSetIterator iter = pTouch->begin();
    std::cout<<"begin:"<<pTouch->count()<<std::endl;
    for (; iter != pTouch->end(); iter++) {
        CCTouch *pT = (CCTouch*)(*iter);
        doWithTouchEvent(pT->getLocation());
        
    }
//    if(m_bIsTouchEventHappenInBtnBegin)
//        postToNotificationCenter();
}
void
gameControl::doWithTouchEvent(cocos2d::CCPoint pos){
    /*获取按钮矩形框*/
    CCRect rectLeft = getBtnRect(m_leftBtn);
    CCRect rectRight = getBtnRect(m_rightBtn);
    CCRect rectJump = getBtnRect(m_jumpBtn);
    
    /*设置纹理状态*/
    if (!m_leftBtn->getIsSelect())
        m_leftBtn->showButtonTexture(judgeIsTouchedBtn(pos, rectLeft));
    if (!m_rightBtn->getIsSelect())
        m_rightBtn->showButtonTexture(judgeIsTouchedBtn(pos, rectRight));
    if (!m_jumpBtn->getIsSelect())
        m_jumpBtn->showButtonTexture(judgeIsTouchedBtn(pos, rectJump));
    
    
}
void
gameControl::ccTouchesMoved(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent)
{
    doWithMoveTouchEvent(pTouch);
    
//        m_leftBtn->showButtonTexture(0);
//        m_rightBtn->showButtonTexture(0);
//        m_jumpBtn->showButtonTexture(0);
    
}

void
gameControl::doWithMoveTouchEvent(cocos2d::CCSet *pTouch){
    
    /*获取按钮矩形框*/
    CCRect rectLeft = getBtnRect(m_leftBtn);
    CCRect rectRight = getBtnRect(m_rightBtn);
    CCRect rectJump = getBtnRect(m_jumpBtn);
    
    CCSetIterator iter = pTouch->begin();
    
    for (; iter != pTouch->end(); iter++) {
        CCTouch *pT = (CCTouch*)(*iter);
        if(judgeIsTouchedBtn(pT->getLocation(), rectLeft)){
            m_leftBtn->showButtonTexture(1);
            pTouch->removeObject(pT);
            break;
        }else
            m_leftBtn->showButtonTexture(0);
    }
    iter = pTouch->begin();
    for (; iter != pTouch->end(); iter++) {
        CCTouch *pT = (CCTouch*)(*iter);
        if(judgeIsTouchedBtn(pT->getLocation(), rectRight)){
            m_rightBtn->showButtonTexture(1);
            pTouch->removeObject(pT);
            break;
        }else
            m_rightBtn->showButtonTexture(0);
    }
    iter = pTouch->begin();
    for (; iter != pTouch->end(); iter++) {
        CCTouch *pT = (CCTouch*)(*iter);
        if(judgeIsTouchedBtn(pT->getLocation(), rectJump)){
            m_jumpBtn->showButtonTexture(1);
            pTouch->removeObject(pT);
            break;
        }else
            m_jumpBtn->showButtonTexture(0);
    }
    
    
//    /*设置纹理状态*/
//    if (!judgeIsTouchedBtn(pos, rectLeft)){
//        if (m_leftBtn->getIsSelect())
//            m_leftBtn->showButtonTexture(0);
//    }else
//        m_leftBtn->showButtonTexture(1);
//    
//    if (!judgeIsTouchedBtn(pos, rectRight)){
//        if (m_rightBtn->getIsSelect())
//            m_rightBtn->showButtonTexture(0);
//    }else
//        m_rightBtn->showButtonTexture(1);
//    if (!judgeIsTouchedBtn(pos, rectJump)){
//        if (m_jumpBtn->getIsSelect())
//            m_jumpBtn->showButtonTexture(0);
//    }else
//        m_jumpBtn->showButtonTexture(1);
//
//    
//    m_leftBtn->showButtonTexture(judgeIsTouchedBtn(pos, rectLeft));
//    m_rightBtn->showButtonTexture(judgeIsTouchedBtn(pos, rectRight));
//    m_jumpBtn->showButtonTexture(judgeIsTouchedBtn(pos, rectJump));

}
void
gameControl::ccTouchesEnded(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSetIterator iter = pTouch->begin();
    std::cout<<"end:"<<pTouch->count()<<std::endl;
    for (; iter != pTouch->end(); iter++) {
        CCTouch *pT = (CCTouch*)(*iter);
        removeTouchEvent(pT->getLocation());
    }
}

void
gameControl::removeTouchEvent(cocos2d::CCPoint pos){
    /*获取按钮矩形框*/
    CCRect rectLeft = getBtnRect(m_leftBtn);
    CCRect rectRight = getBtnRect(m_rightBtn);
    CCRect rectJump = getBtnRect(m_jumpBtn);
    /*设置纹理状态*/
    if (judgeIsTouchedBtn(pos, rectLeft))
        m_leftBtn->showButtonTexture(0);
    if (judgeIsTouchedBtn(pos, rectRight))
        m_rightBtn->showButtonTexture(0);
    if (judgeIsTouchedBtn(pos, rectJump))
        m_jumpBtn->showButtonTexture(0);
    
}
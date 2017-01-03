//
//  PhysicsSprite.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-20.
//
//

#ifndef __PuzzleGame__PhysicsSprite__
#define __PuzzleGame__PhysicsSprite__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using std::list;

#define POST_MSG(_MsgTag_) CCNotificationCenter::sharedNotificationCenter()->postNotification(_MsgTag_,this)
#define POST_MSG_WITH(_MsgTag_,_SENDER_) CCNotificationCenter::sharedNotificationCenter()->postNotification(_MsgTag_,_SENDER_)
#define ADD_OBSERVER(_MsgTag_,_CALLBACK_) CCNotificationCenter::sharedNotificationCenter()->addObserver(this,\
callfuncO_selector(_CALLBACK_),_MsgTag_, NULL)
#define DEL_OBSERVER(_MsgTag_) CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,_MsgTag_)

//box2d碰撞检测
/*用于放入碰撞检测需要的数据*/
class Contact{
public:
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    
    b2Body *bodyA;
    b2Body *bodyB;
    
};
class ContactListener : public b2ContactListener , public CCObject{
public:
    /*开始碰撞时候会调用此方法*/
    virtual void BeginContact(b2Contact* contact);
    /*结束碰撞会调用此方法*/
    virtual void EndContact(b2Contact* contact);
    /*开始碰撞之前调用*/
    virtual void PreSolve(b2Contact* contact,const b2Manifold* oldManfold);
    /*碰撞结束之后*/
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    /*碰撞列表，用于存储碰撞信息*/
    std::list<Contact> contact_list;
private:
    Contact mc;//用于存储b2Contact相关信息
};

class SpriteBody : public CCSprite{
public:
    SpriteBody();
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
    
    //給刚体施加力
    void applyFroce(b2Vec2 force,b2Vec2 point);
    //給刚体施加水平冲量
    void applyLinearImpulse(b2Vec2 speed,b2Vec2 point);
    b2Vec2 getLinearImpulse();
    //水平阻力
    void setLinearDamping(float damping);
    //水平移动刚体
    void setTransform(b2Vec2 pos,float32 angle);
    //设置是否已经休眠
    void setIsAwake(bool flag);
    //设置是否固定旋转
    void setFixedRotation(bool flag);
    //唤醒刚体
    void awakeBody();
    //设置角度
    void setAngle(float angle);
private:
    CC_SYNTHESIZE(b2Body*, m_pBody, PhysicsBody);
};

#endif /* defined(__PuzzleGame__PhysicsSprite__) */

//
//  BasicPhysics.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-19.
//
//

/*
    box2d物理插件:
    
    该插件形式为单例(不支持多个物理世界）— 可用于模拟地球物理现象  如太空之类的这个还没考虑上
 
    BasicPhysics::sharedPhysics 产生单例
 
    方法有createBody产生刚体 销毁刚体
 */

#ifndef __PuzzleGame__BasicPhysics__
#define __PuzzleGame__BasicPhysics__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D.h"
#include "GLES-Render.h"
#include "PhysicsSprite.h"
#include "PlistLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class BasicPhysics : public CCObject{
public:
    BasicPhysics(){};
    virtual ~BasicPhysics(){};
    //物理环境的单例
    static BasicPhysics* sharedPhysics();
    //释放单例 消除世界
    void end();
    
    //初始化物理世界
    void initWithPhysics();
    
    //更新
    void update(float dt);
    //产生刚体
    void createBody(SpriteBody *sprite,
                    CCPoint position,
                    b2BodyType type,
                    float density,
                    float friction,
                    float restitution,
                    CCSize sprContentSize);
    void createBodyInCircle(SpriteBody *sprite,
                            CCPoint position,
                            b2BodyType type,
                            float density,
                            float friction,
                            float restitution,
                            float radius);
    
    //删除刚体
    void destroyBody(SpriteBody *sprite);
    //绘图
    void draw();
private:
    CC_SYNTHESIZE_READONLY(b2World*, world_, World);
    CC_SYNTHESIZE(int, PTM_RATIO, RATIO);
    b2Body* groundBody;
    GLESDebugDraw *m_debugDraw;
    ContactListener *contactListener;
    void crateEdgeShape(b2Body* groundBody,b2EdgeShape groundBox);
};

#endif /* defined(__PuzzleGame__BasicPhysics__) */

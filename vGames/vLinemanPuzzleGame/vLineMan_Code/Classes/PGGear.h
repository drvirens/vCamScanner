//
//  PGGear.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-10.
//
//

#ifndef __PuzzleGame__PGGear__
#define __PuzzleGame__PGGear__

#include "cocos2d.h"
#include "PGElement.h"
#include "BasicPhysics.h"
#include "PhysicsSprite.h"

using namespace cocos2d;

class PGGear : public PGElement{
public:
    PGGear();
    ~PGGear();
    
    //添加刺轮到屏幕上
    void addGearToScreen(CCLayer* layer,CCPoint position);
    //移除齿轮
    void removeGearFromScreen(CCLayer* layer);
    //检测是否有精灵碰撞到刺轮
    bool spriteIsContactGear(CCSprite *sprite);
    //更新
    void gearRotation();
    //移动
    virtual void moveElement(float speedX,float speedY);
    //获得元素位置
    virtual CCPoint getElementPosition();
private:
    CC_SYNTHESIZE(SpriteBody*, gearBody, GearBody);
    CC_SYNTHESIZE(float, angle, Angle);//旋转角度
};

#endif /* defined(__PuzzleGame__PGGear__) */

//
//  PGBox.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-11.
//
//

#ifndef __PuzzleGame__PGBox__
#define __PuzzleGame__PGBox__

#include "cocos2d.h"
#include "PGElement.h"
#include "PhysicsSprite.h"
#include "BasicPhysics.h"

using namespace cocos2d;

class PGBox : public PGElement{
public:
    PGBox();
    ~PGBox();
    //添加可以移动的箱子到屏幕上
    void addBoxToScreen(CCLayer* layer,CCPoint position);
    //移除箱子
    void removeBoxFromScreen(CCLayer *layer);
    //检测是否有精灵碰撞到箱子
    bool spriteIsContactBox(CCSprite *sprite);
    //移动
    virtual void moveElement(float speedX,float speedY);
    //获得元素位置
    virtual CCPoint getElementPosition();
private:
    CC_SYNTHESIZE(SpriteBody*,boxBody,BoxBody);
};

#endif /* defined(__PuzzleGame__PGBox__) */

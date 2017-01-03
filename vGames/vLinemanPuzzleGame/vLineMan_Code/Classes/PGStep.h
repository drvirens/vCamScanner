//
//  PGStep.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-13.
//
//

#ifndef __PuzzleGame__PGStep__
#define __PuzzleGame__PGStep__

#include "cocos2d.h"
#include "PGElement.h"
#include "PhysicsSprite.h"
#include "BasicPhysics.h"

using namespace cocos2d;

class PGStep : public PGElement{
public:
    PGStep();
    ~PGStep();
    
    //添加台阶(需要添加到哪个层中,位置)
    void addStepToScreen(CCLayer* layer,CCPoint pos);
    //移除台阶
    void removeStepFromScreen(CCLayer* layer);
    //移动
    virtual void moveElement(float speedX,float speedY);
    //获得元素位置
    virtual CCPoint getElementPosition();
private:
    CC_SYNTHESIZE(SpriteBody*, stepBody, StepBody);
};

#endif /* defined(__PuzzleGame__PGStep__) */

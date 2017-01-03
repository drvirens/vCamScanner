//
//  PGLevel2Scene.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-23.
//
//

#ifndef __PuzzleGame__PGLevel2Scene__
#define __PuzzleGame__PGLevel2Scene__

#include "cocos2d.h"
#include "PGElement.h"
#include "PGBox.h"
#include "PGStep.h"
#include "PGGear.h"
#include "PGPlayer.h"

#include "PGLevelScene.h"

using namespace cocos2d;

class PGLevel2Scene : public PGLevelScene{
public:
    PGLevel2Scene();
    ~PGLevel2Scene();
    
    static CCScene* scene();
    virtual bool init();
    
    CCArray *elements;
    CCArray *backgrounds;
    
    //移动场景
    virtual bool moveLevelScene(float speedX,float speedY);
    //是否碰到了齿轮
    virtual void isContactGear();
    
    CREATE_FUNC(PGLevel2Scene);
private:
    //添加背景(背景和地面)
    void addGameBackground(CCLayer* layer,CCPoint pos);
    //是否允许移动背景
    bool isAllowMoveScene(float dir);
    //添加可移动箱子
    void addGameBoxs(CCLayer* layer);
    //添加台阶
    void addGameSteps(CCLayer* layer);
    //添加齿轮
    void addGameGear(CCLayer* layer);
    //是否player碰撞到了可以移动箱子
    bool playerisContactBox(PGElement *element);
};

#endif /* defined(__PuzzleGame__PGLevel2Scene__) */

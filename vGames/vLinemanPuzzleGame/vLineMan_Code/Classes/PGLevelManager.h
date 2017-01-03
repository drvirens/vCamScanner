//
//  PGLevelManager.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-12.
//
//

#ifndef __PuzzleGame__PGLevelManager__
#define __PuzzleGame__PGLevelManager__

#include "cocos2d.h"

#include "BasicPhysics.h"
#include "PGPlayer.h"
#include "PGGameControl.h"
#include "PGPausePlugin.h"
#include "PGLevelScene.h"
#include "PGLevel1Scene.h"

//屏幕移动最大距离
#define Scene_Move_MAX_Width 1920
//屏幕移动最小距离
#define Scene_Move_MIN_Width 243

using namespace cocos2d;

class PGLevelManager : public CCLayer{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(PGLevelManager);
    
    void playerMoveLeft();
    void playerMoveRight();
    void playerJumping();
    
    void update(float dt);
    void draw();
    
    void contactBegining();
    void contactEnded();
    
private:
    //目前是哪个关卡的场景
    PGLevelScene *currentScene;
    CCSize winSize;
    //参考点
    CCPoint referPoint;
    //玩家起始点(坐标,如果有存储点就改变)
    CCPoint startPos;
    //游戏主循环
    void gameSchedule();
    //添加暂停按钮
    void addPauseButton();
    void menu_callbackEvent();
    //调整场景位置
    void adjustPosition();
};
#endif /* defined(__PuzzleGame__PGLevelManager__) */

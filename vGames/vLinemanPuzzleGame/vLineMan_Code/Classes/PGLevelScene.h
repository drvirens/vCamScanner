//
//  PGLevelScene.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-22.
//
//

#ifndef __PuzzleGame__PGLevelScene__
#define __PuzzleGame__PGLevelScene__

#include "cocos2d.h"

using namespace cocos2d;

class PGLevelScene : public CCLayer{
public:
    PGLevelScene(){};
    ~PGLevelScene(){};
    
    //移动场景
    virtual bool moveLevelScene(float speedX,float speedY)=0;
    //是否碰到了齿轮
    virtual void isContactGear()=0;
};

#endif /* defined(__PuzzleGame__PGLevelScene__) */

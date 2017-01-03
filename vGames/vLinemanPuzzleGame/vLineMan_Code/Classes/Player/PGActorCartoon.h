//
//  Bz_ActorCartoon.h
//  Bz_aminationDmo
//
//  Created by Binz_- on 13-7-27.
//
//

#ifndef __Bz_aminationDmo__Bz_ActorCartoon__
#define __Bz_aminationDmo__Bz_ActorCartoon__
#include "PGAnimation.h"
#include <iostream>
class Bz_ActorCartoon:public Bz_Animation{
public:
    //传入plist文件名，不需要带后缀！
    void createWithActorPlistFileName(const char* fileName);
public:
    //站立动作
    void actStanding(CCSprite *spr,float delay,int times);
    //左走
    void actLeftMoving(CCSprite *spr,float delay,int times);
    //右走
    void actRightMoving(CCSprite *spr,float delay,int times);
    //左跳
    void actLeftJumpping(CCSprite *spr,float delay,int times);
    //右跳
    void actRightJumpping(CCSprite *spr,float delay,int times);
    //正面跳
    void actFrontJumpping(CCSprite *spr,float delay,int times);
    //左死亡
    void actLeftDying(CCSprite *spr,float delay,int times);
    //右死亡
    void actRightDying(CCSprite *spr,float delay,int times);
    //右推
    void actRightPush(CCSprite *spr,float delay,int times);
    //右推
    void actLeftPush(CCSprite *spr,float delay,int times);
    //停止当前动作
    void actStopCurrentCartoon(CCSprite *spr);
};
#endif /* defined(__Bz_aminationDmo__Bz_ActorCartoon__) */

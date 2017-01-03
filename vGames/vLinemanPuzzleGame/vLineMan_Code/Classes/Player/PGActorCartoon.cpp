//
//  Bz_ActorCartoon.cpp
//  Bz_aminationDmo
//
//  Created by Binz_- on 13-7-27.
//
//

#include "PGActorCartoon.h"
void
Bz_ActorCartoon::createWithActorPlistFileName(const char *file){
    Bz_Animation::createWithPlistFileName(file);
}

void
Bz_ActorCartoon::actStanding(cocos2d::CCSprite *spr, float delay, int times){
    Bz_ActorCartoon::makingAction(spr, "stand", 1, 1, delay, times);
}

void
Bz_ActorCartoon::actLeftMoving(CCSprite *spr,float delay,int times){
    Bz_ActorCartoon::makingAction(spr, "leftMove", 1, 4, delay, times);
}

void
Bz_ActorCartoon::actRightMoving(cocos2d::CCSprite *spr, float delay, int times){
    Bz_ActorCartoon::makingAction(spr, "rightMove", 1, 4, delay, times);
}

void
Bz_ActorCartoon::actLeftJumpping(cocos2d::CCSprite *spr, float delay, int times){
    Bz_ActorCartoon::makingAction(spr, "leftJump", 1, 4, delay, times);
}

void
Bz_ActorCartoon::actRightJumpping(cocos2d::CCSprite *spr, float delay, int times){
    Bz_ActorCartoon::makingAction(spr, "rightJump", 1, 4, delay, times);
}

void
Bz_ActorCartoon::actFrontJumpping(cocos2d::CCSprite *spr, float delay, int times){
    Bz_ActorCartoon::makingAction(spr, "frontJump", 1, 4, delay, times);
}

void
Bz_ActorCartoon::actLeftDying(cocos2d::CCSprite *spr, float delay, int times){
    Bz_ActorCartoon::makingAction(spr, "leftdying", 1, 8, delay, times);
}

void
Bz_ActorCartoon::actRightDying(cocos2d::CCSprite *spr, float delay, int times){
    Bz_ActorCartoon::makingAction(spr, "rightdying", 1, 8, delay, times);
}

void
Bz_ActorCartoon::actLeftPush(cocos2d::CCSprite *spr, float delay, int times) {
    Bz_ActorCartoon::makingAction(spr, "leftpush", 1, 4, delay, times);
}

void
Bz_ActorCartoon::actRightPush(cocos2d::CCSprite *spr, float delay, int times) {
    Bz_ActorCartoon::makingAction(spr, "rightpush", 1, 4, delay, times);
}

void
Bz_ActorCartoon::actStopCurrentCartoon(CCSprite *spr){
    spr->stopAction(m_action);
}

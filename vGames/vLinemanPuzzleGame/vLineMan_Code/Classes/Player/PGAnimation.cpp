//
//  Bz_Animation.cpp
//  Bz_aminationDmo
//
//  Created by Binz_- on 13-7-27.
//
//

#include "PGAnimation.h"
void
Bz_Animation::createWithPlistFileName(const char * fileName){
    //创建cache
    m_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    char strPlist[64] = {0};
    char strPng[64] = {0};
    sprintf(strPlist,"%s.plist",fileName);
    sprintf(strPng,"%s.pvr.ccz",fileName);
    //sprintf(strPng,"%s.png",fileName);
    m_cache->addSpriteFramesWithFile(strPlist, strPng);
}

void
Bz_Animation::makingAction(CCSprite *spr,const char *fileName, int beginIndex, int endIndex, float delay, int times){
    spr->stopAllActions();
    CCArray* animFrames = CCArray::create();
    char str[64] = {0};
    for(int i = beginIndex; i <= endIndex; i++){
        sprintf(str, "%s0%d.png",fileName, i);
        CCSpriteFrame* frame = m_cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,delay);
    animation->setLoops(times);

    m_action = CCAnimate::create(animation);
    
    spr->runAction(m_action);
}
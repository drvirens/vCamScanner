//
//  Bz_Animation.h
//  Bz_aminationDmo
//
//  Created by Binz_- on 13-7-27.
//
//

#ifndef __Bz_aminationDmo__Bz_Animation__
#define __Bz_aminationDmo__Bz_Animation__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class Bz_Animation{
public:
    /**
     * 传入plist文件名，无需后缀！
     */
    void createWithPlistFileName(const char * file);
    /**
     * 创建动作
    */
    void makingAction(CCSprite *spr,const char* fileName,int beginIndex,int endIndex,float delay,int times);
protected:
    CCAnimate* m_action;                            //动作对象
private:
    CCSpriteFrameCache* m_cache;                    //帧缓存
};
#endif /* defined(__Bz_aminationDmo__Bz_Animation__) */

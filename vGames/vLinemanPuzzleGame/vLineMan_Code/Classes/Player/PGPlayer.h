//
//  PGPlayer.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-30.
//
//

/*
    文件说明:
    
        玩家类,此类在游戏中是单例,一个游戏只要一个主角.
    
        所以创建时候只要创建单例就好:如下
        
        PGPlayer::sharedPlayer()->createPlayer(this);//this代表是要加入到哪个层中
 
        在配置文件PlayerConfig中可以修改相关的信息
 
        要获得插件的相关信息 如大小 需要调用此方法
 
        getSpriteBody()//返回SpriteBody类 此是继承自CCSprite
 */

#ifndef __PuzzleGame__PGPlayer__
#define __PuzzleGame__PGPlayer__

#include "cocos2d.h"
#include "PlistLoader.h"
#include "BasicPhysics.h"
#include "PhysicsSprite.h"
#include "PGActorCartoon.h"

typedef enum PlayerDirection{
    p_static = 0,
    p_left = -1,
    p_right = 1,
    p_jump = 2
}PlayerDirection;

using namespace cocos2d;

class PGPlayer : public CCObject{
public:
    PGPlayer();
    virtual ~PGPlayer();
    
    /*产生玩家单例*/
    static PGPlayer* sharedPlayer();
    /*产生玩家对象*/
    void createPlayer(CCLayer* layer);
    /*删除游戏玩家*/
    void deletePlayer(CCLayer* layer);
    /*移动玩家*/
    void playerMoveingInBox2d(PlayerDirection dir);//左边或者右边
    void playerJumpingInBox2d();
    /*调整玩家方向*/
    void adjustPlayerAnimation(PlayerDirection dir);
private:
    CC_SYNTHESIZE(SpriteBody*, sprite, SpriteBody);
    //player速度
    CC_SYNTHESIZE(float, speed, Speed);
    //是否食持续碰撞
    CC_SYNTHESIZE(bool, isContinueCollde, IsContinueCollde);
    //玩家动画
    CC_SYNTHESIZE(Bz_ActorCartoon, animation, Animation);
    
    PlistLoader *plist;
    
    CCAnimate *moveAnim;
    CCAnimate *jumpAnim;
    CCAnimate *pushAnim;
    
    PlayerDirection oldDir;
    
    void addPlayerBodyToScreen(CCLayer* layer,CCTexture2D *playerTex);
};

#endif /* defined(__PuzzleGame__PGPlayer__) */

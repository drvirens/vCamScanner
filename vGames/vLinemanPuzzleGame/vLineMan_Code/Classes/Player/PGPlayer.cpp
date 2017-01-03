//
//  PGPlayer.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-30.
//
//

#include "PGPlayer.h"

using namespace cocos2d;

static PGPlayer* player;

PGPlayer* PGPlayer::sharedPlayer(){
    if (!player) {
        player=new PGPlayer();
    }
    return player;
}

PGPlayer::PGPlayer(){
    //是否有碰撞到其它刚体
    isContinueCollde=true;
    plist=PlistLoader::initWithPlistFile("PlayerConfig.plist");
    //获取玩家的速度
    CCString *speedStr=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PlayerMoveSpeed"));
    speed=speedStr->floatValue();
}

PGPlayer::~PGPlayer(){
    CC_SAFE_DELETE(plist);
}

void PGPlayer::createPlayer(CCLayer* layer){
    CCString *file=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PlayerFileName"));
    //用纹理缓存（资源池）加载纹理
    CCTexture2D *playerTex=CCTextureCache::sharedTextureCache()->addImage(file->getCString());
    
    //添加玩家刚体
    this->addPlayerBodyToScreen(layer, playerTex);
}

void PGPlayer::deletePlayer(CCLayer* layer){
    CCString *file=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PlayerFileName"));
    //删除纹理
    CCTextureCache::sharedTextureCache()->removeTextureForKey(file->getCString());
}

void PGPlayer::addPlayerBodyToScreen(CCLayer* layer,CCTexture2D *playerTex){
    //添加玩家精灵
    CCString *imageSizeStr=dynamic_cast<CCString*>(plist->getObjectFromFileKey("ImagePreSize"));
    CCSize imageSize=CCSizeFromString(imageSizeStr->getCString());
    CCString *positionStr=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PlayerPosition"));
    CCPoint position=CCPointFromString(positionStr->getCString());
    
    CCSpriteFrame *frame1=CCSpriteFrame::createWithTexture(playerTex, CCRectMake(0, 0, imageSize.width, imageSize.height));
    sprite=new SpriteBody();
    
    sprite->initWithSpriteFrame(frame1);
    sprite->setPosition(position);
    sprite->autorelease();
    
    CCString *playerTag=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PlayerTag"));
    CCString *playerZOrder=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PlayerZOrder"));

    layer->addChild(sprite,playerZOrder->intValue(),playerTag->intValue());
    
    //玩家动画类
    animation.createWithActorPlistFileName("Actor");
    animation.actStanding(sprite, 0.5, -1);
    oldDir=p_static;
    
    //生成刚体
    BasicPhysics::sharedPhysics()->createBody(sprite,
                                              sprite->getPosition() ,
                                              b2_dynamicBody,
                                              0.8f,0.5f,0.0f,
                                              CCSizeMake(45, 80));
    //设置固定旋转
    sprite->setFixedRotation(true);
}

void PGPlayer::adjustPlayerAnimation(PlayerDirection dir){
    CCLOG("%d-%d",oldDir,dir);
    if (dir>0&&oldDir!=dir) {//右边且不是同一个方向
        animation.actRightMoving(sprite, 0.5, -1);
    }else if(dir<0&&oldDir!=dir){//左边
        animation.actLeftMoving(sprite, 0.5, -1);
    }
    oldDir=dir;
}

void PGPlayer::playerMoveingInBox2d(PlayerDirection dir){
    
    this->adjustPlayerAnimation(dir);
    
    float posX=sprite->getPosition().x;
    int PTM_RATIO=BasicPhysics::sharedPhysics()->getRATIO();
    sprite->setTransform(b2Vec2((posX+dir*speed)/PTM_RATIO,
                                sprite->getPosition().y/PTM_RATIO),0);
}

void PGPlayer::playerJumpingInBox2d(){
    if (!(sprite->getLinearImpulse().y>=-2.0f&&this->getIsContinueCollde())){
        return;
    }
    //判断player目前方向
    if (oldDir==p_right) {
        animation.actLeftJumpping(sprite, -0.5f, -1);
    }else if(oldDir==p_left){
        animation.actLeftJumpping(sprite, -0.5f, -1);
    }
    oldDir=p_jump;
    int PTM_RATIO=BasicPhysics::sharedPhysics()->getRATIO();
    sprite->applyLinearImpulse(b2Vec2(0,8.5f),
                               b2Vec2(sprite->getPosition().x/PTM_RATIO,
                                      sprite->getPosition().y/PTM_RATIO));
}
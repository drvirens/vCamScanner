//
//  PGLevelManager.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-12.
//
//

#include "PGLevelManager.h"

extern const char* moveLeft;
extern const char* moveRight;
extern const char* jump;

extern const char* contactBegin;
extern const char* contactEnd;

CCScene* PGLevelManager::scene(){
    CCScene* scene=CCScene::create();
    PGLevelManager *layer=PGLevelManager::create();
    scene->addChild(layer);
    return scene;
}

bool PGLevelManager::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    //获得窗口大小
    winSize=CCDirector::sharedDirector()->getWinSize();
    
    //添加关卡背景和元素的层
    currentScene=PGLevel1Scene::create();
    currentScene->setPosition(ccp(0,0));
    this->addChild(currentScene);
    
    //添加游戏控制和主角的层
    //添加玩家
    PGPlayer::sharedPlayer()->createPlayer(this);
    referPoint=PGPlayer::sharedPlayer()->getSpriteBody()->getPosition();
    //初始化开始坐标
    startPos=referPoint;
    
    //游戏控制层
    gameControl *control=gameControl::create();
    this->addChild(control,90);
    
    //添加暂停按钮
    this->addPauseButton();
    
    //添加观察者
    ADD_OBSERVER(moveLeft, PGLevelManager::playerMoveLeft);
    ADD_OBSERVER(moveRight, PGLevelManager::playerMoveRight);
    ADD_OBSERVER(jump, PGLevelManager::playerJumping);
    
    //box2d碰撞检测
    ADD_OBSERVER(contactBegin,PGLevelManager::contactBegining);
    ADD_OBSERVER(contactEnd,PGLevelManager::contactEnded);
    
    //更新函数
    scheduleUpdate();
    
    return true;
}

void PGLevelManager::update(float dt){
    BasicPhysics::sharedPhysics()->update(dt);
    //碰撞检测
    currentScene->isContactGear();
}

void PGLevelManager::draw(){
    CCLayer::draw();
    BasicPhysics::sharedPhysics()->draw();
}

void PGLevelManager::addPauseButton(){
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCSprite *btn1=CCSprite::create("buttons.png",CCRectMake(80*2, 0, 80, 75));
    btn1->setScale(0.8f);
    CCSprite *btn2=CCSprite::create("buttons.png",CCRectMake(80*3, 0, 85, 75));
    btn2->setScale(0.8f);
    CCMenuItemSprite *pauseBtn=CCMenuItemSprite::create(btn1, btn2,
                                                        this,
                                                        menu_selector(PGLevelManager::menu_callbackEvent));
    CCMenu *menu=CCMenu::create(pauseBtn,NULL);
    menu->setPosition(ccp(size.width-40,size.height-30));
    this->addChild(menu,80);
}

void PGLevelManager::menu_callbackEvent(){
    PGPausePlugin::sharedPlugin()->createPlugin(this);
}

#pragma mark-
#pragma mark player moving method
void PGLevelManager::adjustPosition(){
    //box2d世界中玩家实际位置(调整位置)
    float realPlayerPos=PGPlayer::sharedPlayer()->getSpriteBody()->getPhysicsBody()->GetTransform().p.x*BasicPhysics::sharedPhysics()->getRATIO();
    if (realPlayerPos<=Scene_Move_MIN_Width&&referPoint.x<=Scene_Move_MIN_Width) {
        referPoint.x=realPlayerPos;
    }else if(referPoint.x>=(Scene_Move_MAX_Width-Scene_Move_MIN_Width+10)){
        referPoint.x=realPlayerPos+(Scene_Move_MAX_Width-Scene_Move_MIN_Width*2);
    }
}

void PGLevelManager::playerMoveLeft(){
    //this->adjustPosition();
    float playerSpeed=PGPlayer::sharedPlayer()->getSpeed();
    if (referPoint.x<Scene_Move_MIN_Width||
        referPoint.x>(Scene_Move_MAX_Width-Scene_Move_MIN_Width)) {
        if (referPoint.x<=0) return;
        referPoint=ccpAdd(referPoint, ccp(-playerSpeed,0));
        PGPlayer::sharedPlayer()->playerMoveingInBox2d(p_left);
        return;
    }else{
        PGPlayer::sharedPlayer()->adjustPlayerAnimation(p_left);
        referPoint=ccpAdd(referPoint, ccp(-playerSpeed,0));
        if(!currentScene->moveLevelScene(playerSpeed, 0)){//如果没有移动就复位
            referPoint=ccpAdd(referPoint,ccp(playerSpeed,0));
        }
    }
}

void PGLevelManager::playerMoveRight(){
    this->adjustPosition();
    float playerSpeed=PGPlayer::sharedPlayer()->getSpeed();
    if (referPoint.x<=Scene_Move_MIN_Width||
        referPoint.x>=(Scene_Move_MAX_Width-Scene_Move_MIN_Width)) {
        if (referPoint.x>=Scene_Move_MAX_Width) return;
        referPoint=ccpAdd(referPoint, ccp(playerSpeed,0));
        PGPlayer::sharedPlayer()->playerMoveingInBox2d(p_right);
        return;
    }else{
        PGPlayer::sharedPlayer()->adjustPlayerAnimation(p_right);
        referPoint=ccpAdd(referPoint,ccp(playerSpeed,0));
        if(!currentScene->moveLevelScene(-playerSpeed, 0)){//如果没有移动就复位
            referPoint=ccpAdd(referPoint,ccp(-playerSpeed,0));
        }
    }
}

void PGLevelManager::playerJumping(){
    PGPlayer::sharedPlayer()->playerJumpingInBox2d();
}

#pragma mark -
#pragma mark contact Event
void PGLevelManager::contactBegining(){
    if ((int)(PGPlayer::sharedPlayer()->getSpriteBody()->getLinearImpulse().y)==0) return;
    PGPlayer::sharedPlayer()->setIsContinueCollde(true);
}

void PGLevelManager::contactEnded(){
    if ((int)(PGPlayer::sharedPlayer()->getSpriteBody()->getLinearImpulse().y)==0) return;
    PGPlayer::sharedPlayer()->setIsContinueCollde(false);
}
//
//  PGLevel1Scene.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-12.
//
//

#include "PGLevel1Scene.h"

PGLevel1Scene::PGLevel1Scene(){}
PGLevel1Scene::~PGLevel1Scene(){
    CC_SAFE_DELETE_ARRAY(elements);
    CC_SAFE_DELETE_ARRAY(backgrounds);
}

CCScene* PGLevel1Scene::scene(){
    CCScene *scene = CCScene :: create();
    PGLevel1Scene *layer = PGLevel1Scene::create();
    scene->addChild(layer);
    return scene;
}

bool PGLevel1Scene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    //游戏中的元素数组
    elements=CCArray::create();
    elements->retain();
    backgrounds=CCArray::create();
    backgrounds->retain();
    
    //添加背景
    this->addGameBackground(this,ccp(size.width/2-20,size.height/2));
    this->addGameBackground(this,ccp((size.width/2+size.width)-25,size.height/2));
    this->addGameBackground(this,ccp((size.width/2+size.width*2)-30,size.height/2));
    this->addGameBackground(this,ccp((size.width/2+size.width*3)-35,size.height/2));
    this->addGameBackground(this,ccp((size.width/2+size.width*4)-40,size.height/2));
    
    //添加box和step
    this->addGameBoxs(this);
    this->addGameSteps(this);
    this->addGameGear(this);
    
    return true;
}

void PGLevel1Scene::isContactGear(){
    CCSprite *player=PGPlayer::sharedPlayer()->getSpriteBody();
    for (int i=0; i<elements->count(); i++) {
        PGGear *gear=dynamic_cast<PGGear*>(elements->objectAtIndex(i));
        if (gear!=NULL) {//如果是box对象
            //旋转齿轮
            gear->gearRotation();
            if (gear->spriteIsContactGear(player)) {
                CCLOG("---contact gear---");
            }
        }
    }
}

#pragma mark -
#pragma mark secne move event
bool PGLevel1Scene::moveLevelScene(float speedX,float speedY){
    if(!this->isAllowMoveScene(speedX)){
        return false;
    }else{
        //遍历
        for (int i=0;i<backgrounds->count();i++) {
            CCSprite *sprite=dynamic_cast<CCSprite*>(backgrounds->objectAtIndex(i));
            sprite->setPosition(ccpAdd(sprite->getPosition(),ccp(speedX,speedY)));
        }
        for (int i=0; i<elements->count(); i++) {
            PGElement *element=dynamic_cast<PGElement*>(elements->objectAtIndex(i));
            if(this->playerisContactBox(element,speedX)) continue;//是否在推箱子
            element->moveElement(speedX, speedY);
        }
    }
    return true;
}

bool PGLevel1Scene::playerisContactBox(PGElement *element,int playerDir){
    if (element->getElementPosition().x==100000) {
        PGBox *box=(PGBox*)element;
        if(box->spriteIsContactBox(PGPlayer::sharedPlayer()->getSpriteBody())&&
           ccpSub(PGPlayer::sharedPlayer()->getSpriteBody()->getPosition(),
                  box->getBoxBody()->getPosition()).y<=1.0f){
               //判断实际方向是否和player方向一致
               float subPosX=ccpSub(PGPlayer::sharedPlayer()->getSpriteBody()->getPosition(),
                              box->getBoxBody()->getPosition()).x;
               int realDir=subPosX/abs(subPosX);//实际方向
               int realPlayerDir=playerDir/abs(playerDir);//玩家运动方向
               if (realDir==realPlayerDir) {
                   return true;
               }
        }
    }
    return false;
}

bool PGLevel1Scene::isAllowMoveScene(float dir){
    CCPoint playerPos=PGPlayer::sharedPlayer()->getSpriteBody()->getPosition();
    CCPoint realPos=ccpAdd(ccp(-dir,0), playerPos);
    
    for (int i=0; i<elements->count(); i++) {
        PGElement *element=dynamic_cast<PGElement*>(elements->objectAtIndex(i));
        CCPoint elementPos=element->getElementPosition();
        if (abs(ccpSub(realPos,elementPos).x)<=41) {
            if (abs(ccpSub(realPos,elementPos).y)<=20.0f) {
                return false;
            }
            continue;
        }
    }
    return true;
}

#pragma mark -
#pragma mark 游戏元素

void PGLevel1Scene::addGameBackground(CCLayer *layer, CCPoint pos){
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCSprite *bg=CCSprite::create("background1.png");
    bg->setPosition(ccp(pos.x, pos.y));
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bg->setScale(0.5f);
#endif
    layer->addChild(bg);
    backgrounds->addObject(bg);
    
    CCSprite *green=CCSprite::create("green.png");
    green->setScale(0.5f);
    green->setPosition(ccp(pos.x,pos.y));
    layer->addChild(green,70);
    backgrounds->addObject(green);
}

void PGLevel1Scene::addGameBoxs(CCLayer* layer){
    PGBox *box=new PGBox();
    box->addBoxToScreen(this, ccp(100, 200));
    elements->addObject(box);
    box->release();
    
    PGBox *box2=new PGBox();
    box2->addBoxToScreen(this, ccp(580, 225));
    elements->addObject(box2);
    box2->release();

    PGBox *box3=new PGBox();
    box3->addBoxToScreen(this, ccp(1600, 105));
    elements->addObject(box3);
    box3->release();
}

void PGLevel1Scene::addGameSteps(CCLayer* layer){
    //添加台阶1
    for (int i=0;i<3; i++) {
        PGStep *step=new PGStep();
        step->addStepToScreen(this, ccp(410,100+30*i));
        elements->addObject(step);
        step->release();
    }
    //添加台阶2
    for (int i=0;i<3; i++) {
        PGStep *step=new PGStep();
        step->addStepToScreen(this, ccp(440,100+30*i));
        elements->addObject(step);
        step->release();
    }
    //添加台阶3
    for (int i=0; i<3; i++) {
        PGStep *step=new PGStep();
        step->addStepToScreen(this, ccp(530-30*i,100));
        elements->addObject(step);
        step->release();
    }
    //添加台阶4
    for (int i=0; i<3; i++) {
        PGStep *step=new PGStep();
        step->addStepToScreen(this, ccp(600-30*i,150));
        elements->addObject(step);
        step->release();
    }
    //添加台阶5
    PGStep *step=new PGStep();
    step->addStepToScreen(this, ccp(758, 100));
    elements->addObject(step);
    step->release();
    //添加台阶6
    for (int i=0; i<2; i++) {
        PGStep *step=new PGStep();
        step->addStepToScreen(this, ccp(1350,100+30*i));
        elements->addObject(step);
        step->release();
    }
    //添加台阶7
    for (int i=0; i<3; i++) {
        PGStep *step=new PGStep();
        step->addStepToScreen(this, ccp(1380,100+30*i));
        elements->addObject(step);
        step->release();
    }
    //添加台阶8
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            PGStep *step=new PGStep();
            step->addStepToScreen(this, ccp(1620+30*i,169+30*j));
            elements->addObject(step);
            step->release();
        }
    }
    //添加台阶9
    for (int i=0; i<2; i++) {
        PGStep *step=new PGStep();
        step->addStepToScreen(this, ccp(1720+30*i,169));
        elements->addObject(step);
        step->release();
    }
}

void PGLevel1Scene::addGameGear(CCLayer *layer){
    //齿轮1
    for (int i=0; i<4; i++) {
        PGGear *gear=new PGGear();
        gear->addGearToScreen(this,ccp(570+48*i,105));
        elements->addObject(gear);
        gear->release();
    }
    //齿轮2
    for (int i=0; i<4; i++) {
        PGGear *gear2=new PGGear();
        gear2->addGearToScreen(this,ccp(890+120*i,105));
        elements->addObject(gear2);
        gear2->release();
    }
    //齿轮3
    for (int i=0; i<2; i++) {
        PGGear *gear=new PGGear();
        gear->addGearToScreen(this, ccp(1480, 170+43*i));
        elements->addObject(gear);
        gear->release();
    }
    //齿轮4
    for (int i=0; i<2; i++) {
        PGGear *gear=new PGGear();
        gear->addGearToScreen(this, ccp(1580, 170+43*i));
        elements->addObject(gear);
        gear->release();
    }
}
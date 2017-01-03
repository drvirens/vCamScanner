//
//  PGBox.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-11.
//
//

#include "PGBox.h"

PGBox::PGBox(){}
PGBox::~PGBox(){
    CC_SAFE_DELETE(boxBody);
}

void PGBox::addBoxToScreen(CCLayer *layer, CCPoint point){
    boxBody=new SpriteBody();
    boxBody->initWithFile("box.png");
    boxBody->setPosition(point);
    boxBody->autorelease();
    layer->addChild(boxBody);
    
    BasicPhysics::sharedPhysics()->createBody(boxBody,
                                              boxBody->getPosition(),
                                              b2_dynamicBody,
                                              0.0f, 1.0f, 0.0f,
                                              boxBody->getContentSize());
}

void PGBox::removeBoxFromScreen(CCLayer *layer){
    if (!boxBody) {
        CCLOG("不存在box组件");
        return;
    }
    BasicPhysics::sharedPhysics()->destroyBody(boxBody);
    layer->removeChild(boxBody, true);
}


bool PGBox::spriteIsContactBox(CCSprite* sprite){
    CCRect spriteRect=CCRectMake(sprite->getPosition().x-sprite->getContentSize().width/2,
                                 sprite->getPosition().y-sprite->getContentSize().height/2,
                                 sprite->getContentSize().width,
                                 sprite->getContentSize().height);
    CCRect boxRect=CCRectMake(boxBody->getPosition().x-boxBody->getContentSize().width/2,
                              boxBody->getPosition().y-boxBody->getContentSize().height/2,
                              boxBody->getContentSize().width,
                              boxBody->getContentSize().height);
    if (boxRect.intersectsRect(spriteRect)) {
        return true;
    }
    return false;
}

void PGBox::moveElement(float speedX, float speedY){
    int PTM_RATIO=BasicPhysics::sharedPhysics()->getRATIO();
    boxBody->setTransform(b2Vec2((boxBody->getPosition().x+speedX)/PTM_RATIO,
                                 (boxBody->getPosition().y+speedY)/PTM_RATIO),0);
}

CCPoint PGBox::getElementPosition(){
    return ccp(100000,0);
}
//
//  PGGear.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-10.
//
//

#include "PGGear.h"

PGGear::PGGear(){
    angle=0;
}

PGGear::~PGGear(){
    CC_SAFE_DELETE(gearBody);
}

void PGGear::addGearToScreen(CCLayer *layer, CCPoint point){
    gearBody=new SpriteBody();
    gearBody->initWithFile("gameProp1.png", CCRectMake(0, 0, 46, 46));
    gearBody->setPosition(point);
    //gearBody->autorelease();
    
    layer->addChild(gearBody);
    
    BasicPhysics::sharedPhysics()->createBodyInCircle(gearBody,
                                                      gearBody->getPosition(),
                                                      b2_staticBody,
                                                      1.0f,1.0f,0.0f,
                                                      0.7f);
}

void PGGear::removeGearFromScreen(CCLayer *layer){
    if (!gearBody) {
        CCLOG("gearBody is not created!");
        return;
    }
    BasicPhysics::sharedPhysics()->destroyBody(gearBody);
    layer->removeChild(gearBody, true);
}

bool PGGear::spriteIsContactGear(CCSprite* sprite){
    CCRect gearRect=CCRectMake(gearBody->getPosition().x-gearBody->getContentSize().width/2,
                               gearBody->getPosition().y-gearBody->getContentSize().height/2,
                               gearBody->getContentSize().width-9,
                               gearBody->getContentSize().height);
    CCRect spriteRect=CCRectMake(sprite->getPosition().x-sprite->getContentSize().width/2,
                                 sprite->getPosition().y-sprite->getContentSize().height/2,
                                 sprite->getContentSize().width-10,
                                 sprite->getContentSize().height);
    
    if (gearRect.intersectsRect(spriteRect)) {
        return true;
    }
    return false;
}

void PGGear::moveElement(float speedX, float speedY){
    int PTM_RATIO=BasicPhysics::sharedPhysics()->getRATIO();
    gearBody->setTransform(b2Vec2((gearBody->getPosition().x+speedX)/PTM_RATIO,
                                 (gearBody->getPosition().y+speedY)/PTM_RATIO),(angle/180)*M_PI);
}

void PGGear::gearRotation(){
    angle-=1;
    int PTM_RATIO=BasicPhysics::sharedPhysics()->getRATIO();
    gearBody->setTransform(b2Vec2(gearBody->getPosition().x/PTM_RATIO,
                                  gearBody->getPosition().y/PTM_RATIO),
                           (angle/180)*M_PI);
}

CCPoint PGGear::getElementPosition(){
    return gearBody->getPosition();
}
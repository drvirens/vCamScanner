//
//  PGStep.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-13.
//
//

#include "PGStep.h"

PGStep::PGStep(){
}

PGStep::~PGStep(){
    CC_SAFE_DELETE(stepBody);
}

void PGStep::addStepToScreen(CCLayer *layer, CCPoint pos){
    stepBody=new SpriteBody();
    stepBody->initWithFile("gameProp1.png", CCRectMake(14, 132, 34, 38));
    stepBody->setPosition(pos);
    stepBody->autorelease();
    layer->addChild(stepBody);
    
    BasicPhysics::sharedPhysics()->createBody(stepBody,
                                              stepBody->getPosition(),
                                              b2_staticBody,
                                              0.8f, 1.0f, 0.0f,
                                              CCSizeMake(33, 37));
}

void PGStep::removeStepFromScreen(CCLayer *layer){
    if (!stepBody) {
        CCLOG("stepBody is not created!");
        return;
    }
    BasicPhysics::sharedPhysics()->destroyBody(stepBody);
    layer->removeChild(stepBody, true);
}

void PGStep::moveElement(float speedX, float speedY){
    int PTM_RATIO=BasicPhysics::sharedPhysics()->getRATIO();
    stepBody->setTransform(b2Vec2((stepBody->getPosition().x+speedX)/PTM_RATIO,
                                 (stepBody->getPosition().y+speedY)/PTM_RATIO),0);
}

CCPoint PGStep::getElementPosition(){
    return stepBody->getPosition();
}
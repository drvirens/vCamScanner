//
//  PGLevel2Scene.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-23.
//
//

#include "PGLevel2Scene.h"

PGLevel2Scene::PGLevel2Scene(){
    
}

PGLevel2Scene::~PGLevel2Scene(){
    
}

CCScene* PGLevel2Scene::scene(){
    CCScene* scene=CCScene::create();
    PGLevel2Scene *layer=PGLevel2Scene::create();
    scene->addChild(layer);
    return scene;
}

bool PGLevel2Scene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    //初始化
    //数组
    elements=CCArray::create();
    elements->retain();
    backgrounds=CCArray::create();
    backgrounds->retain();
    
    
    return true;
}

bool PGLevel2Scene::moveLevelScene(float speedX, float speedY){
    return true;
}

void PGLevel2Scene::isContactGear(){
    
}

#pragma mark -
#pragma mark 游戏元素

void PGLevel2Scene::addGameBackground(CCLayer *layer, CCPoint pos){
    
}

void PGLevel2Scene::addGameBoxs(CCLayer *layer){
    
}

void PGLevel2Scene::addGameGear(CCLayer *layer){
    
}

void PGLevel2Scene::addGameSteps(CCLayer *layer){
    
}
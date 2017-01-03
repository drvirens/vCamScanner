//
//  PGPausePlugin.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-21.
//
//

#include "PGPausePlugin.h"

static PGPausePlugin* pausePlugin;

PGPausePlugin* PGPausePlugin::sharedPlugin(){
    if (!pausePlugin) {
        pausePlugin=new PGPausePlugin();
        pausePlugin->autorelease();
        pausePlugin->retain();
    }
    return pausePlugin;
}

PGPausePlugin::PGPausePlugin(){
    isFristCreate=false;
    notificationType=new PluginNotificationType();
    size=CCDirector::sharedDirector()->getWinSize();
    //获得配置文件
    plist=PlistLoader::initWithPlistFile("PGPausePluginConfig.plist");
    plist->retain();
}

PGPausePlugin::~PGPausePlugin(){
}

void PGPausePlugin::end(){
    CC_SAFE_DELETE(notificationType);
    CC_SAFE_DELETE(plist);
    CC_SAFE_RELEASE(pausePlugin);
}

#pragma mark -
#pragma mark public method create and delete
void PGPausePlugin::createPlugin(CCLayer* layer){
    if (isFristCreate) return;
    isFristCreate=true;
    
    //绑定层
    this->glayer=layer;
    //产生背景
    this->createBackground(glayer);
    //产生插件按钮
    this->createPluginButton(glayer);
    //游戏暂停
    layer->pauseSchedulerAndActions();
}

void PGPausePlugin::deletePlugin(CCLayer* layer){
    /*已经删除.标记不是第一次产生*/
    if (isFristCreate) isFristCreate=false;
    PlistLoader *tempPlist=PlistLoader::initWithPlistFile("PGPausePluginConfig.plist");
    //get speed String
    CCString *speedStr=dynamic_cast<CCString*>(tempPlist->getObjectFromFileKey("MoveSpeed"));
    //get pause plugin tag
    CCString *tag=dynamic_cast<CCString*>(tempPlist->getObjectFromFileKey("PausePluginTag"));
    CCSprite *pauseBg=dynamic_cast<CCSprite*>(layer->getChildByTag(tag->intValue()));
    pauseBg->runAction(CCMoveTo::create(speedStr->intValue(), ccp(size.width+pauseBg->getContentSize().width/2,size.height/2)));
    CCMenu *menu=dynamic_cast<CCMenu*>(layer->getChildByTag(tag->intValue()-1));
    CCMoveTo *moveTo=CCMoveTo::create(1.0f, ccp(size.width+menu->getContentSize().width/2,size.height/2));
    CCCallFuncND *func=CCCallFuncND::create(this, callfuncND_selector(PGPausePlugin::delete_funcND), layer);
    menu->runAction(CCSequence::create(moveTo,func,NULL));
}

void PGPausePlugin::delete_funcND(CCObject* object, void *data){
    CCLayer* layer=(CCLayer*)(data);
    //get pause plugin tag
    PlistLoader *tempPlist=PlistLoader::initWithPlistFile("PGPausePluginConfig.plist");
    CCString *tag=dynamic_cast<CCString*>(tempPlist->getObjectFromFileKey("PausePluginTag"));
    layer->removeChildByTag(tag->intValue(), true);
    layer->removeChildByTag(tag->intValue()-1, true);
    layer->resumeSchedulerAndActions();
}

#pragma mark -
#pragma mark private method
void PGPausePlugin::createBackground(CCLayer* layer){
    //get background image
    CCString *pauseBtnSpr=dynamic_cast<CCString*>(plist->getObjectFromFileKey("BackgroundImage"));
    //get speed String
    CCString *speedStr=dynamic_cast<CCString*>(plist->getObjectFromFileKey("MoveSpeed"));
    //get pause plugin tag
    CCString *tag=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PausePluginTag"));
    
    CCSprite *pauseBg=CCSprite::create(pauseBtnSpr->getCString());
    pauseBg->setPosition(ccp(size.width+pauseBg->getContentSize().width/2,size.height/2));
    pauseBg->runAction(CCMoveTo::create(speedStr->intValue(), ccp(size.width+20,
                                                  size.height/2)));
    layer->addChild(pauseBg,100,tag->intValue());
}

void PGPausePlugin::createPluginButton(CCLayer* layer){
    /*从配置文件中获得图片信息*/
    CCString *btnImages=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PluginBtnImages"));
    CCTexture2D *btnTexture=CCTextureCache::sharedTextureCache()->addImage(btnImages->getCString());
    CCArray *buttons=CCArray::create();
    CCString *cols=dynamic_cast<CCString*>(plist->getObjectFromFileKey("BtnImageCols"));
    CCString *rows=dynamic_cast<CCString*>(plist->getObjectFromFileKey("BtnImageRows"));
    CCString *btnSizeStr=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PluginButtonPreSize"));
    CCSize btnSize=CCSizeFromString(btnSizeStr->getCString());
    
    for (int i=0; i<cols->intValue(); i++) {//列
        for (int j=0; j<rows->intValue(); j++) {//行
            CCSprite *btnSpr=CCSprite::createWithTexture(btnTexture,CCRectMake(btnSize.width*j, btnSize.height*i, btnSize.width, btnSize.height));
            buttons->addObject(btnSpr);
        }
    }
    /*产生按钮*/
    CCMenuItemToggle* bgMusicToggle=this->createBgMusicBtn(buttons);
    CCMenuItemToggle* bgEffectToggle=this->createEffectBtn(buttons);
    CCMenuItemSprite* homeBtn=this->createHomeBtn(buttons);
    CCMenuItemSprite* backBtn=this->createBackBtn(buttons);
    
    //get speed String
    CCString *speedStr=dynamic_cast<CCString*>(plist->getObjectFromFileKey("MoveSpeed"));
    //get pause plugin tag
    CCString *tag=dynamic_cast<CCString*>(plist->getObjectFromFileKey("PausePluginTag"));
    /*产生插件的按钮菜单*/
    CCMenu *pluginMenu=CCMenu::create(bgMusicToggle,bgEffectToggle,homeBtn,backBtn,NULL);
    pluginMenu->alignItemsVerticallyWithPadding(5.0f);
    pluginMenu->setPosition(ccp(size.width+pluginMenu->getContentSize().width/2,size.height/2));
    pluginMenu->runAction(CCMoveTo::create(speedStr->intValue(), ccp(size.width-50,
                                               size.height/2)));
    layer->addChild(pluginMenu,101,tag->intValue()-1);
}

#pragma mark -
#pragma mark background music toggle 
CCMenuItemToggle* PGPausePlugin::createBgMusicBtn(CCArray* sprites){
    /*背景音乐按钮开着时候*/
    CCSprite *openbtnSpr=dynamic_cast<CCSprite*>(sprites->objectAtIndex(11));
    CCSprite *openbtnSprUse=dynamic_cast<CCSprite*>(sprites->objectAtIndex(10));
    CCMenuItemSprite *openMenuBtn=CCMenuItemSprite::create(openbtnSpr,openbtnSprUse);
    /*背景音乐按钮关闭*/
    CCSprite *closebtnSpr=dynamic_cast<CCSprite*>(sprites->objectAtIndex(9));
    CCSprite *closebtnSprUse=dynamic_cast<CCSprite*>(sprites->objectAtIndex(8));
    CCMenuItemSprite *closeMenuBtn=CCMenuItemSprite::create(closebtnSpr, closebtnSprUse);
    /*背景音乐开关*/
    CCMenuItemToggle *bgMusicToggle=CCMenuItemToggle::createWithTarget(this,menu_selector(PGPausePlugin::musicSetting),openMenuBtn,closeMenuBtn,NULL);
    bgMusicToggle->setScale(0.5f);
    return bgMusicToggle;
}

void PGPausePlugin::musicSetting(CCObject* sender){
 
}

#pragma mark effect toggle
CCMenuItemToggle* PGPausePlugin::createEffectBtn(CCArray *sprites){
    /*音效按钮开着时候*/
    CCSprite *openbtnSpr=dynamic_cast<CCSprite*>(sprites->objectAtIndex(3));
    CCSprite *openbtnSprUse=dynamic_cast<CCSprite*>(sprites->objectAtIndex(2));
    CCMenuItemSprite *openMenuBtn=CCMenuItemSprite::create(openbtnSpr,openbtnSprUse);
    /*音效按钮关闭*/
    CCSprite *closebtnSpr=dynamic_cast<CCSprite*>(sprites->objectAtIndex(1));
    CCSprite *closebtnSprUse=dynamic_cast<CCSprite*>(sprites->objectAtIndex(0));
    CCMenuItemSprite *closeMenuBtn=CCMenuItemSprite::create(closebtnSpr, closebtnSprUse);
    /*音效开关*/
    CCMenuItemToggle *bgEffectToggle=CCMenuItemToggle::createWithTarget(this,menu_selector(PGPausePlugin::effectSetting),openMenuBtn,closeMenuBtn,NULL);
    bgEffectToggle->setScale(0.5f);
    return bgEffectToggle;
}

void PGPausePlugin::effectSetting(CCObject* sender){
    
}

#pragma mark home button 
CCMenuItemSprite* PGPausePlugin::createHomeBtn(CCArray* sprites){
    CCSprite *homeBtn=dynamic_cast<CCSprite*>(sprites->objectAtIndex(7));
    CCSprite *homeBtnUse=dynamic_cast<CCSprite*>(sprites->objectAtIndex(6));
    CCMenuItemSprite *homeSprite=CCMenuItemSprite::create(homeBtn, homeBtnUse, this, menu_selector(PGPausePlugin::homeSetting));
    homeSprite->setScale(0.5f);
    return homeSprite;
}

void PGPausePlugin::homeSetting(CCObject* sender){
    //跳进主场景
    
}

#pragma mark back button
CCMenuItemSprite* PGPausePlugin::createBackBtn(CCArray* sprites){
    CCSprite *backBtn=dynamic_cast<CCSprite*>(sprites->objectAtIndex(5));
    CCSprite *backBtnUse=dynamic_cast<CCSprite*>(sprites->objectAtIndex(4));
    CCMenuItemSprite *backSprite=CCMenuItemSprite::create(backBtn, backBtnUse, this, menu_selector(PGPausePlugin::backFunc));
    backSprite->setScale(0.5f);
    return backSprite;
}

void PGPausePlugin::backFunc(CCObject* sender){
    this->deletePlugin(glayer);
}
//
//  PGPausePlugin.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-21.
//
//

/*
    PGPausePlugin文件功能说明:
    
        
 */

#ifndef __PuzzleGame__PGPausePlugin__
#define __PuzzleGame__PGPausePlugin__

#include "cocos2d.h"
#include "PlistLoader.h"

using namespace cocos2d;

class PluginNotificationType{
private:
    CC_SYNTHESIZE_READONLY(const char*, music, Music);
    CC_SYNTHESIZE_READONLY(const char*, effect, Effect);
    CC_SYNTHESIZE_READONLY(const char*, home, Home);
    CC_SYNTHESIZE_READONLY(const char*, back, Back);
public:
    PluginNotificationType(){
        music="Background";
        effect="Effect";
        home="Home";
        back="Back";
    };
};

class PGPausePlugin : public cocos2d::CCObject{
public:
    PGPausePlugin();
    virtual ~PGPausePlugin();
    /*产生插件的单例*/
    static PGPausePlugin* sharedPlugin();
    /*产生插件*/
    void createPlugin(CCLayer* layer);
    /*移除插件*/
    void deletePlugin(CCLayer* layer);
    /*删除单例*/
    void end();
private:
    /*观察者模式中的类型*/
    CC_SYNTHESIZE_READONLY(PluginNotificationType*, notificationType, NotificationType);
    
    CCSize size;
    bool isFristCreate;//是否为第一次产生
    PlistLoader *plist;//该插件的配置文件
    
    CCLayer *glayer;
    
    /*产生背景*/
    void createBackground(CCLayer *layer);
    void createPluginButton(CCLayer *layer);
    /*添加插件的每一个按钮*/
    CCMenuItemToggle* createBgMusicBtn(CCArray* sprites);
    CCMenuItemToggle* createEffectBtn(CCArray* sprites);
    CCMenuItemSprite* createHomeBtn(CCArray* sprites);
    CCMenuItemSprite* createBackBtn(CCArray* sprites);
    
    /*按钮对应的回调事件*/
    void musicSetting(cocos2d::CCObject *sender);
    void effectSetting(cocos2d::CCObject *sender);
    void homeSetting(cocos2d::CCObject *sender);
    void backFunc(cocos2d::CCObject *sender);
    
    /*移除相对应回调方法*/
    void delete_funcND(CCObject* object,void* data);
};

#endif /* defined(__PuzzleGame__PGPausePlugin__) */

#ifndef __MENUSCENE_SCENE_H__
#define __MENUSCENE_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene*			scene();
	virtual bool						init();  
	CREATE_FUNC(MenuScene);

	// a selector callback
	virtual void						menuCloseCallback(CCObject* pSender);
	virtual void						menuVolumeCallback(CCObject* pSender);
	virtual void						menuPlayCallback(CCObject* pSender);
	
};

#endif // __MENUSCENE_SCENE_H__

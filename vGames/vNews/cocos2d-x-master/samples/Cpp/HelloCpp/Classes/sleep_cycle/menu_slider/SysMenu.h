#ifndef __SYS_MENU_H__
#define __SYS_MENU_H__

#include "cocos2d.h"

class SysMenu : public cocos2d::CCLayer
{
public:
	SysMenu(void);
	virtual ~SysMenu(void);

	bool init(void);

	static cocos2d::CCScene* scene(void);

	void onNewGame(CCObject* pSender);
	void onSettings(CCObject* pSender);
	void onQuit(CCObject* pSender);

	CREATE_FUNC(SysMenu);
};

#endif
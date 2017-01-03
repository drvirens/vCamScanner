#ifndef __SETTINGS_LAYER_H__
#define __SETTINGS_LAYER_H__

#include "cocos2d.h"

class SettingsLayer : public cocos2d::CCLayer
{
public:
	SettingsLayer(void);
	virtual ~SettingsLayer(void);

	bool init(void);

	void backCallback(CCObject* pSender);

	CREATE_FUNC(SettingsLayer);
};

#endif
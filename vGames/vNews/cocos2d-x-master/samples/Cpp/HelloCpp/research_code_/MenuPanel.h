

#ifndef __MENU_PANEL_H__
#define __MENU_PANEL_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuPanel : public CCMenu
{
public:
	MenuPanel(){}
	virtual ~MenuPanel(){}
	static MenuPanel* create(CCMenuItem* item, ...);
	static MenuPanel* createWithArray(CCArray* pArrayOfItems);
	static MenuPanel* createWithItems(CCMenuItem* item, va_list args);
	static MenuPanel* create();
	virtual void registerWithTouchDispatcher();
};

#endif //__MENU_PANEL_H__
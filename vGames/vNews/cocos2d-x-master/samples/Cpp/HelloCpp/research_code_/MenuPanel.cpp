#include "MenuPanel.h"

#define kItemTag 0

MenuPanel* MenuPanel::create(CCMenuItem* item, ...)
{
	/*
	va_list args;
	va_start(args, item);
	MenuPanel *pRet = new MenuPanel();
	if (pRet && pRet->createWithItems(item,args))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet);
	return NULL;*/
	
    va_list args;
    va_start(args,item);
    
    MenuPanel *pRet = MenuPanel::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;

}

MenuPanel* MenuPanel::createWithArray(CCArray* pArrayOfItems)
{
    MenuPanel *pRet = new MenuPanel();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

MenuPanel* MenuPanel::createWithItems(CCMenuItem* item, va_list args)
{
    CCArray* pArray = NULL;
    if( item )
    {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
        }
    }
    
    return MenuPanel::createWithArray(pArray);
}

MenuPanel* MenuPanel::create()
{
	return MenuPanel::create(NULL, NULL);
}



void MenuPanel::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class AttemptScrollLayer : public CCLayer 
{
protected:
	
	// Holds the height and width of the screen when the class was inited
	int startHeight;
	int startWidth;
	
	// A count of the total screens available
	int totalScreens;
	int contentSize;
	int widthOffset;

	// The initial point the user starts their swipe
	int startSwipe;	

	void moveToPage(int page);
	void moveToNextPage();
	void moveToPreviousPage();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchMoved(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *withEvent);
    
public:
	// Holds the current page being displayed
	int currentScreen;
	int scrollWidth;
	int scrollHeight;
	void redrawAttempts(bool isPressed);
	static AttemptScrollLayer* layerWithLayers();
	bool initWithLayers();
	CREATE_FUNC(AttemptScrollLayer);
};
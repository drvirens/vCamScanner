#include "CCScrollLayerVert.h"

CCScrollLayerVert* CCScrollLayerVert::layerWithLayers()
{	
	CCScrollLayerVert *pRet = new CCScrollLayerVert();
	if (pRet && pRet->initWithLayers())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCScrollLayerVert::initWithLayers()
{	
	//_localLayers = layers;
	if (CCLayer::init())
	{	
		// Make sure the layer accepts touches
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);

		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCSize size = screenSize;
		size.height = size.width/3;
		size.width = size.width/6 - 10;
		
		heightOffset = 3;
		currentScreen = 1;
		
		// offset added to show preview of next/previous screens
		scrollWidth  = 10;
		scrollHeight = heightOffset + 48;
		startWidth = 10;
		startHeight = (int)CCDirector::sharedDirector()->getWinSize().height - 100;
		
		// Setup a count of the available screens
		totalScreens = 0;

		return true;	
	}
	else
	{
		return false;
	}	
}

void CCScrollLayerVert::addAttempt(CCLabelBMFont* lastAttempt) {
	this->addChild(lastAttempt);
	totalScreens++;
}

void CCScrollLayerVert::moveToPage(int page)
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(0, -((page-1)*scrollHeight))));
	this->runAction(changePage);
	currentScreen = page;	
}

void CCScrollLayerVert::moveToNextPage()
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(0, -(((currentScreen+1)-1)*scrollHeight))));
	
	this->runAction(changePage);
	currentScreen = currentScreen+1;	
}

void CCScrollLayerVert::moveToPreviousPage()
{	
	CCEaseBounce* changePage =CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(0, -(((currentScreen-1)-1)*scrollHeight))));
	this->runAction(changePage);
	currentScreen = currentScreen-1;	
}

void CCScrollLayerVert::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool CCScrollLayerVert::ccTouchBegan(CCTouch *touch, CCEvent *withEvent)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	startSwipe = (int)touchPoint.y;
	return true;
}

void CCScrollLayerVert::ccTouchMoved(CCTouch *touch, CCEvent *withEvent)
{	
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	this->setPosition(ccp(0,(-(currentScreen-1)*scrollHeight)+(touchPoint.y-startSwipe)));
}

void CCScrollLayerVert::ccTouchEnded(CCTouch *touch, CCEvent *withEvent)
{
	
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	int newY = (int)touchPoint.y;
	//currentScreen = currentScreen - (newY - startSwipe)/scrollHeight;
	if (currentScreen<1)
		currentScreen = 1;
	if (currentScreen>totalScreens)
		currentScreen = totalScreens;
	if ( (newY - startSwipe) < -scrollHeight / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
	}
	else if ((newY - startSwipe) > scrollHeight / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
	}
	else
	{
		this->moveToPage(currentScreen);		
	}		
}
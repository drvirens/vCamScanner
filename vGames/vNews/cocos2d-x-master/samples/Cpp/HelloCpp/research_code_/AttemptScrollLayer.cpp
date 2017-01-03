#include "AttemptScrollLayer.h"
#include "CodeChecker.h"

AttemptScrollLayer* AttemptScrollLayer::layerWithLayers()
{	
	AttemptScrollLayer * pRet = new AttemptScrollLayer();
	if (pRet && pRet->initWithLayers())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool AttemptScrollLayer::initWithLayers()
{	
	if (CCLayer::init())
	{		
		// Make sure the layer accepts touches
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);

		currentScreen = 1;

		int topPanel = 120;
		int bottomPanel = 50;
		scrollWidth  = (int)CCDirector::sharedDirector()->getWinSize().width;
		scrollHeight = (int)CCDirector::sharedDirector()->getWinSize().height - topPanel - bottomPanel;



		startWidth = 5;
		startHeight = (int)CCDirector::sharedDirector()->getWinSize().height - topPanel - 15;

		// Setup a count of the available screens
		totalScreens = 1;
		contentSize = scrollWidth;
		widthOffset = 0;

		return true;	
	}
	else
	{
		return false;
	}	
}

void AttemptScrollLayer::redrawAttempts(bool isPressed) {
	this->removeAllChildren();
    if (CodeChecker::attempts.size() == 0) return;
    int i=0;
	int j=0;
	int hSpace = 20;
	int vSpace = 0;
	bool isFirst = false;
    int attemptSize = 0;

	if (isPressed) {
	 isFirst = true;
	}

    Attempt a = *CodeChecker::attempts.rbegin();
    CCLabelBMFont* lastAttempt = CCLabelBMFont::create((a.attempt + ":" + a.results).c_str(), "futura-48.fnt");
    attemptSize = lastAttempt->getContentSize().width;
    contentSize = (attemptSize + hSpace);
	for (std::list<Attempt>::reverse_iterator it = CodeChecker::attempts.rbegin(); it != CodeChecker::attempts.rend(); ++it) {
		Attempt a = *it;
		CCLabelBMFont* lastAttempt = CCLabelBMFont::create((a.attempt + ":" + a.results).c_str(), "futura-48.fnt");
        attemptSize = lastAttempt->getContentSize().width;
		if ((lastAttempt->getContentSize().height + vSpace) * (j+1) - vSpace > scrollHeight) {
			j=0;
			i++;
			if (startWidth + (lastAttempt->getContentSize().width + hSpace) * (i+1) -
				hSpace - (totalScreens-1) * contentSize > contentSize) {
					totalScreens++;
			}
		}
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		lastAttempt->setAnchorPoint(ccp(0, 0));
		if (!isFirst) {
			lastAttempt->setPosition(ccp(startWidth + (lastAttempt->getContentSize().width + hSpace) * i,
				startHeight - lastAttempt->getContentSize().height - (lastAttempt->getContentSize().height + vSpace) * j));
		} else {
			lastAttempt->setPosition(ccp(size.width/2 - lastAttempt->getContentSize().width/2, size.height/2 + startHeight/2));
		}


		if (isFirst) {
			CCFadeIn *pFadeIn = CCFadeIn::create(1.0);
			CCMoveTo *pMoveBy = CCMoveTo::create(0.8, ccp(startWidth + (lastAttempt->getContentSize().width + hSpace) * i,
				startHeight - lastAttempt->getContentSize().height - (lastAttempt->getContentSize().height + vSpace) * j));

			lastAttempt->runAction(pFadeIn);
			lastAttempt->runAction(pMoveBy);
			isFirst = false;
		}

		this->addChild(lastAttempt);
		j++;
	}
}

void AttemptScrollLayer::moveToPage(int page)
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(-((page-1)*contentSize),0)));
	this->runAction(changePage);
	currentScreen = page;	
}

void AttemptScrollLayer::moveToNextPage()
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(-(((currentScreen+1)-1)*contentSize),0)));

	this->runAction(changePage);
	currentScreen = currentScreen+1;	
}

void AttemptScrollLayer::moveToPreviousPage()
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(-(((currentScreen-1)-1)*contentSize),0)));
	this->runAction(changePage);
	currentScreen = currentScreen-1;	
}

void AttemptScrollLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool AttemptScrollLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	startSwipe = (int)touchPoint.x;
	return true;
}

void AttemptScrollLayer::ccTouchMoved(CCTouch *touch, CCEvent *withEvent)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	this->setPosition(ccp((-(currentScreen-1)*contentSize)+(touchPoint.x-startSwipe),0));
}

void AttemptScrollLayer::ccTouchEnded(CCTouch *touch, CCEvent *withEvent)
{

	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	int newX = (int)touchPoint.x;

	if ( (newX - startSwipe) < -contentSize / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
	}
	else if ( (newX - startSwipe) > contentSize / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
	}
	else
	{
		this->moveToPage(currentScreen);
	}
}
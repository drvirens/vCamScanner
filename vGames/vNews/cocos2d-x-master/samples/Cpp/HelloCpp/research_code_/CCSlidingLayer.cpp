#include "CCSlidingLayer.h"

#define FRAME_RATE 60
#define BOUNCE_TIME 0.2f

USING_NS_CC;

CCSlidingLayer::CCSlidingLayer()
{	
	slideDirection_ = Vertically;
	contentRect_ = CCRectMake(0,0,0,0);
	direction_ = BounceDirectionStayingStill;
	isDragging_ = false;
    
	lasty = 0;
	xvel = 0;

	childCount = 0;
	verticalMargins = 0.0f;
	horizontalMargins = 0.0f;
}

CCSlidingLayer* CCSlidingLayer::create(SlideDirection slideDirection, CCSize contentSize, CCRect contentRect, ccColor4B color)
{
    CCSlidingLayer * pLayer = new CCSlidingLayer();
    if( pLayer && pLayer->initSlidingLayer(slideDirection, contentSize, contentRect, color))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool CCSlidingLayer::initSlidingLayer(SlideDirection slideDirection, CCSize contentSize, CCRect contentRect, ccColor4B color)
{
	if ( CCLayerColor::initWithColor( color ) )
	{
        slideDirection_ = slideDirection;
		this->setContentSize(contentSize);

        isDragging_ = false;
        lasty = 0.0f;
        xvel = 0.0f;
        direction_ = BounceDirectionStayingStill;
        contentRect_ = contentRect;
		
		childCount = 0;
		verticalMargins = contentRect.size.height * 0.025;
		horizontalMargins = contentRect.size.width * 0.04;

        if(slideDirection_ == Vertically) {
			CCPoint newPosition = CCPointMake(contentRect.origin.x, contentRect_.size.height - this->getContentSize().height);
			this->setPosition(newPosition);
        }
        else if(slideDirection_ == Horizontally){
            this->setPosition(ccp(contentRect.origin.x, contentRect.origin.y));
        }
		this->scheduleUpdate();
		this->setTouchEnabled(true);
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************/
/*					ONLY SUPPORTS VERTICAL LAYERS					  */
/**********************************************************************/
void CCSlidingLayer::addChildWithSize(CCNode* child, CCSize size, MyAlignment alignment)
{
	direction_ = BounceDirectionStayingStill;
	// Current CCLayerColor height
	float currentHeight = this->getContentSize().height;
	// Total contained height with this new child
	float containedHeight = verticalMargins * 2 + size.height;	
	for (int i = 0; i< childCount; i++)
		containedHeight += this->getChildByTag(i)->getContentSize().height;
	// See if we have to increase CCLayerColors height
	if (currentHeight < containedHeight)
	{
		// Set new height
		this->setContentSize(CCSize(this->getContentSize().width, containedHeight));
		// Since the items are added top->button we have to re-position them
		if (childCount>0)
			for (int i = 0; i< childCount; i++)
				this->getChildByTag(i)->setPositionY(this->getChildByTag(i)->getPositionY()+containedHeight-currentHeight);
	}
	// We now calculate the position for the new item		 
	float nextYPos = this->getContentSize().height-verticalMargins -(size.height*0.5);
	for (int i = 0; i< childCount; i++) 
		nextYPos -= this->getChildByTag(i)->getContentSize().height;
	// Switch alignment
	switch (alignment)
	{
		case kAlignmentCenter:
			child->setAnchorPoint(ccp(0.5f,0.5f));
			child->setPosition(ccp(this->getContentSize().width * 0.5, nextYPos)); 
			break;
		case kAlignmentLeft:
			child->setAnchorPoint(ccp(0.0f,0.5f));
			child->setPosition(ccp(horizontalMargins, nextYPos)); 
			break;
		case kAlignmentRight:
			child->setAnchorPoint(ccp(1.0f,0.5f));
			child->setPosition(ccp(this->getContentSize().width-horizontalMargins, nextYPos)); 
			break;
		case kAlignmentTop:
			child->setAnchorPoint(ccp(0.5f,1.0f));
			child->setPosition(ccp(this->getContentSize().width * 0.5, nextYPos)); 
			break;
		case kAlignmentBottom:
			child->setAnchorPoint(ccp(0.5f,0.0f));
			child->setPosition(ccp(this->getContentSize().width * 0.5, nextYPos)); 
			break;
		default:
			break;
	}
	// Set tags and add to the layer
	child->setTag(childCount);
	this->addChild(child,0,childCount++);
	// Position the CCLayerColor at the top
	this->setPositionY(contentRect_.size.height-this->getContentSize().height);
}

void CCSlidingLayer::update(float time)
{    
	// Round xvel 2 decs
	xvel = round(xvel);

	CCPoint pos = this->getPosition();
    // positions for slidingLayer
    float right = pos.x + 0 + this->getContentSize().width;
    float left = pos.x + 0;
    float bottom = pos.y + 0;
    float top = pos.y + 0 + this->getContentSize().height;
    
    // Bounding area of slidingview
    float minX = contentRect_.origin.x;
    float maxX;
    
    float minY;
    float maxY = contentRect_.origin.y + contentRect_.size.height;

	
	if (this->getContentSize().height < contentRect_.size.height) 
		minY = contentRect_.size.height - this->getContentSize().height;
	else
		minY = contentRect_.origin.y; 
	if (this->getContentSize().width < contentRect_.size.width) 
		maxX = contentRect_.size.width -  this->getContentSize().width;
	else
		maxX = contentRect_.origin.x + contentRect_.size.width;

	//CCLOG("Dir: %i,PosY: %f, Top: %f, MaxY: %f",direction_,pos.y,top,maxY);

    if(!isDragging_) {
        static float friction = 0.96f;
        if(slideDirection_ == Horizontally){
			// new case: contentRect bigger than layer
			if (this->getContentSize().width < contentRect_.size.width) {
				if(left < minX && direction_ != BounceDirectionGoingLeft) {
					xvel = 0;
					direction_ = BounceDirectionGoingLeft;
				}
				else if(left > minX && direction_ != BounceDirectionGoingRight) {       
					xvel = 0;
					direction_ = BounceDirectionGoingRight;
				}
			}
            else if(left > minX && direction_ != BounceDirectionGoingLeft) {
                xvel = 0;
                direction_ = BounceDirectionGoingLeft;
            }
            else if(right < maxX && direction_ != BounceDirectionGoingRight) {
                xvel = 0;
                direction_ = BounceDirectionGoingRight;
            }
        }
        else if(slideDirection_ == Vertically) {
			// new case: contentRect bigger than layer
			if (this->getContentSize().height < contentRect_.size.height) {
				if(top > maxY && direction_ != BounceDirectionGoingUp) {
					xvel = 0;
					direction_ = BounceDirectionGoingUp;
				}
				else if(top < maxY && direction_ != BounceDirectionGoingDown) {       
					xvel = 0;
					direction_ = BounceDirectionGoingDown;
				}
			}
            else if(bottom > minY && direction_ != BounceDirectionGoingUp) {
                xvel = 0;
                direction_ = BounceDirectionGoingUp;
            }
            else if(top < maxY && direction_ != BounceDirectionGoingDown) {       
                xvel = 0;
                direction_ = BounceDirectionGoingDown;
            }
        }
        if(direction_ == BounceDirectionGoingRight) {
            if(xvel >= 0) {
                float delta = (maxX - right);
                float yDeltaPerFrame = (delta / (BOUNCE_TIME * FRAME_RATE));
                xvel = yDeltaPerFrame;
            }
            if((right + 0.5f) == maxX) {                
                pos.x = right -  this->getContentSize().width;
                xvel = 0;
                direction_ = BounceDirectionStayingStill;
            }
        }
        else if(direction_ == BounceDirectionGoingLeft) {
            if(xvel <= 0) {
                float delta = (minX - left);
                float yDeltaPerFrame = (delta / (BOUNCE_TIME * FRAME_RATE));
                xvel = yDeltaPerFrame;
            }
            if((left + 0.5f) == minX) {   
                pos.x = left - 0;
                xvel = 0;
                direction_ = BounceDirectionStayingStill;
            }
        }
        else if(direction_ == BounceDirectionGoingDown) {
            if(xvel >= 0) {
                float delta = (maxY - top);
                float yDeltaPerFrame = (delta / (BOUNCE_TIME * FRAME_RATE));
                xvel = yDeltaPerFrame;
            }
            if((top + 0.5f) == maxY) {
                pos.y = top -  this->getContentSize().height;
                xvel = 0;
                direction_ = BounceDirectionStayingStill;
            }
        }
        else if(direction_ == BounceDirectionGoingUp) {
            if(xvel <= 0) {
                float delta = (minY - bottom);
                float yDeltaPerFrame = (delta / (BOUNCE_TIME * FRAME_RATE));
                xvel = yDeltaPerFrame;
            }
            if((bottom + 0.5f) == minY) {
                
                pos.y = bottom - 0;
                xvel = 0;
                direction_ = BounceDirectionStayingStill;
            }
        }
        else {
            xvel *= friction;
        }
        if(slideDirection_ == Horizontally) {
            pos.x += xvel;
        }
        else if (slideDirection_ == Vertically) {
				pos.y += xvel;
        }
		this->setPosition(pos);
    }
    else {
        if(slideDirection_ == Horizontally) {
            if(left <= minX || right >= maxX) {
                direction_ = BounceDirectionStayingStill;
            }
            if(direction_ == BounceDirectionStayingStill) {
                xvel = (pos.x - lasty)/2;
                lasty = pos.x;
            }
        }
        else if(slideDirection_ == Vertically){
            if(bottom <= minY || top >= maxY) {     
                direction_ = BounceDirectionStayingStill;
            }
            if(direction_ == BounceDirectionStayingStill) {
                xvel = (pos.y - lasty)/2;
                lasty = pos.y;
            }
        }
    }

}

bool CCSlidingLayer::ccTouchBegan( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{
	CCPoint touchLocation = touch->getLocation();    

	// if touched outside the content rect do nothing
	if (!contentRect_.containsPoint(touchLocation))
		return false;

	if (contentRect_.containsPoint(touchLocation))
	{
		m_tBeginPos = touch->getLocation();    
    }
	return true;
}

void CCSlidingLayer::ccTouchMoved( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{
    isDragging_ = true; 

	CCPoint curPos;
	CCPoint nextPos;
	CCPoint touchLocation;

    if(slideDirection_ == Vertically) {
		touchLocation = touch->getLocation();    
		float nMoveY = touchLocation.y - m_tBeginPos.y;

		curPos  = this->getPosition();
		nextPos = ccp(curPos.x, curPos.y + nMoveY);
	}
	
    else if(slideDirection_ == Horizontally) {
		touchLocation = touch->getLocation();    
		float nMoveX = touchLocation.x - m_tBeginPos.x;

		curPos  = this->getPosition();
		nextPos = ccp(curPos.x + nMoveX, curPos.y);
	}
	
    this->setPosition(nextPos);
    m_tBeginPos = touchLocation;
}

void CCSlidingLayer::ccTouchEnded( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{
	isDragging_ = false;
}

void CCSlidingLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}

void CCSlidingLayer::onEnter()
{
    CCLayerColor::onEnter();
}
 
void CCSlidingLayer::onEnterTransitionDidFinish()
{
    CCLayerColor::onEnterTransitionDidFinish();
}
 
void CCSlidingLayer::onExit()
{
    CCLayerColor::onExit();
}

float CCSlidingLayer::round(float r) 
{
	if ((r > 0.00) && (r < 0.1)) {direction_ = BounceDirectionStayingStill; return 0.0f;}
	else if ((r < 0.00) && (r > -0.1))  {direction_ = BounceDirectionStayingStill; return 0.0f;}
	else return r;
}
#include "cocos2d.h"

using namespace cocos2d;

typedef enum {
    Vertically,
    Horizontally
} SlideDirection;

typedef enum{
    BounceDirectionGoingUp = 1,
    BounceDirectionStayingStill = 0,
    BounceDirectionGoingDown = -1,
    BounceDirectionGoingLeft = 2,
    BounceDirectionGoingRight = 3
} BounceDirection;

typedef enum{
    kAlignmentCenter = 0,
    kAlignmentLeft = 1,
    kAlignmentRight = 2,
    kAlignmentTop = 3,
    kAlignmentBottom = 4,
} Alignment;

class CCSlidingLayer : public CCLayerColor
{
public:		
	virtual ~CCSlidingLayer(){};
	CCSlidingLayer();

	// Constructors
    CREATE_FUNC(CCSlidingLayer);
	static CCSlidingLayer* create(SlideDirection slideDirection, CCSize contentSize, CCRect contentRect, ccColor4B color);
	virtual bool initSlidingLayer(SlideDirection slideDirection, CCSize contentSize, CCRect contentRect, ccColor4B color);
	
	// Update function
	void update(float time);

	// Adds items from Top to Bottom and also increment size of the layer (not contentRect_) if needed
	void addChildWithSize(CCNode* child, CCSize size, Alignment alignment);

	// Control parameters
	SlideDirection slideDirection_;
	CCRect contentRect_;
	BounceDirection direction_;
    
	// Tells if the user is dragging or not
	bool isDragging_;
    
	// Scrolling parameters
    CCPoint m_tBeginPos;
	float lasty;
	float xvel;

	// Child count for adding items
	int childCount;

	// Margins (if desired to use)
	float verticalMargins;
	float horizontalMargins;
	
	// Getters
	int getChildCount(){return childCount;}
	float getVerticalMargins(){return verticalMargins;}
	float getHorizontalMargins(){return horizontalMargins;}
	CCRect getContentRect(){return contentRect_;}
	bool isDragging(){return isDragging_;}

	// Setters
	void setVerticalMargins(float vM){verticalMargins = vM;}
	void setHorizontalMargins(float hM){horizontalMargins=hM;}
	void setContentRect(CCRect newRect){contentRect_=newRect;}

    /** override functions */	
    virtual bool ccTouchBegan( cocos2d::CCTouch * touch, cocos2d::CCEvent * event );
    virtual void ccTouchMoved( cocos2d::CCTouch * touch, cocos2d::CCEvent * event );
    virtual void ccTouchEnded( cocos2d::CCTouch * touch, cocos2d::CCEvent * event );
    virtual void registerWithTouchDispatcher();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
private:
	float round(float r);
};


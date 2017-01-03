#include "CommonFunc.h"

#include <cstdlib> // srand

#include "GameObjects/Wolf.h"


/*
====================
DeclareAnimationAndSprite
====================
*/
void DeclareAnimationAndSprite (	cocos2d::CCSprite *sprite,	cocos2d::CCAnimation *animation, const char *fileNameTemplate, 
									int from, int to, float playingTime )
{
	for( int frame = from; frame < to; ++frame)
	{
		char szFileName[150] = {0};
		sprintf(szFileName, fileNameTemplate, frame);
    //CCLOG("DeclareAnimationAndSprite: szFileName=%s", szFileName);
		animation->addSpriteFrameWithFileName(szFileName);
	}

	animation->setDelayPerUnit( playingTime / static_cast<float>(to) );
	animation->setRestoreOriginalFrame( true );

	char szInitSprite[150] = {0};
	sprintf(szInitSprite, fileNameTemplate, from);
	sprite->initWithFile(szInitSprite);
}

/*
====================
DeclareAnimation
====================
*/
void DeclareAnimation (	cocos2d::CCAnimation	*animation, const char	*fileNameTemplate, 
						int from,	int to,		float playingTime )
{
	for( int frame = from; frame < to; ++frame)
	{
		char szFileName[150] = {0};
		sprintf(szFileName, fileNameTemplate, frame);
		animation->addSpriteFrameWithFileName(szFileName);
	}

	animation->setDelayPerUnit( playingTime / static_cast<float>(to) );
	animation->setRestoreOriginalFrame( true );
}

/*
====================
HideChildrensNotEqSprite
====================
*/
void HideChildrensNotEqSprite( cocos2d::CCLayer* layer, cocos2d::CCSprite* sprite)
{
	cocos2d::CCArray *arrChilds = layer->getChildren();

	for ( int i = 0 ; i < arrChilds->count(); ++i)
	{
		cocos2d::CCSprite* child = (cocos2d::CCSprite*) arrChilds->objectAtIndex(i);
		if (child->isEqual(sprite))
			child->setVisible(true);
		else
			child->setVisible(false);
	}
}

/*
====================
CurrentScale
====================
*/
float CurrentScale()
{
	cocos2d::CCSize screenSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	float scale = screenSize.height / 768 ;
  //CCLOG("SCALE: screenSize.height is [%f], CurrentScale is [%f]", screenSize.height, scale);
	//return scale;
  return 1.2f;//viren: experimental cuz images too small
}

/*
====================
IsOutScreen
====================
*/
bool IsOutScreen( const cocos2d::CCRect& rectSprite, float centerScreen, float frontierLeft, float frontierRight )
{
	bool retVal = false;

	if ( (rectSprite.origin.x > centerScreen && rectSprite.origin.x > frontierRight) ||								// Все еще за левой границей  	
		 (rectSprite.origin.x < centerScreen && ( rectSprite.origin.x + rectSprite.size.width ) < frontierLeft) )	//					правой 
		retVal = true;

	return retVal;
}

/*
====================
RandomFloat
====================
*/
float RandomFloat(float lo, float hi)
{
	const int RAND_LIMIT = 32767;
	float r = (float)(std::rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = (hi - lo) * r + lo;
	return r;
}

/*
====================
RandomInt
====================
*/
int RandomInt()
{
	int r = 2.0 * std::rand() / RAND_MAX;
	return r;
}

 
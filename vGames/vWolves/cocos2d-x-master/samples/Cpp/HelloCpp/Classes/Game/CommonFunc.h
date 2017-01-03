/*
===================================================================================
Description
		REMARK
		
Copyright (c) TexnoDog, 2011.
Author	  Klimontov Michael (KlimontovM@gmail.com)
===================================================================================
*/

#ifndef __COMMON_FUNC_H__
#define __COMMON_FUNC_H__

#include "cocos2d.h"
#include "Definition.h"


/*
====================
Enums for current action
====================
*/
namespace kLooking
{
	enum
	{
		Left,
		Right
	};
}

namespace kAct
{
	enum
	{
		Death,
		Hit,
		Blink
	};
}

/*
====================
DeclareAnimationAndSprite
		This function fills the CCAnimation from files according to string template. 

Remark:
		sprite and animation should be initialized before call this function.
Example:
		CCSprite* sprite = new CCSprite();
		CCAnimation* animation = CCAnimation::animation();
		DeclareAnimationAndSprite(sprite, animation,"runFrame_000%02d.png", 0, 25, 1.0f);
====================
*/
void DeclareAnimationAndSprite (	cocos2d::CCSprite *sprite,	cocos2d::CCAnimation *animation, const char *fileNameTemplate, 
									int from, int to, float playingTime );

/*
====================
HideChildrensNotEqSprite
		 Hide all children layer which don't equal with sprite
====================
*/
void HideChildrensNotEqSprite( cocos2d::CCLayer* layer, cocos2d::CCSprite* sprite);

/*
====================
CurrentScale
		This function get scale for sample texture

Remark:
		Screen size 1024 X 768 without scale.
		Returned scale by height.
====================
*/
float CurrentScale();

/*
====================
IsOutScreen
		Determines when is object out off-screen
====================
*/
bool IsOutScreen( const cocos2d::CCRect& rectSprite, float centerScreen, float frontierLeft, float frontierRight );

/*
====================
RandomFloat
		Random floating point number in range [lo, hi]
====================
*/
float RandomFloat(float lo, float hi);

/*
====================
RandomInt
		Random int number in range [0,1]
====================
*/
int RandomInt();
 


#endif //__COMMON_FUNC_H__
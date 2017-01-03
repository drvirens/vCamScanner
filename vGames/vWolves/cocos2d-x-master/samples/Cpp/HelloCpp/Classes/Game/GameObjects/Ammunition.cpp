#include "Ammunition.h"

#include <cmath> // sta::abs
#include "../CommonFunc.h"
#include "../Sounds.h"

#include "cocos2d.h"

//USING_NS_CC;
using namespace cocos2d;


/*
===================================================================================
Class	Bullet
===================================================================================
*/

/*
====================
init
====================
*/
bool Bullet::init()
{
	if(! CCLayer::init())
		return false;

//viren+
	//SPEED_BULLET= 10 * CurrentScale();
  SPEED_BULLET= 5 * CurrentScale();
  //viren-

	isDeath		= false;
	pSounds		= NULL;

	m_animBullet = new CCSprite();
	CCAnimation* animation = CCAnimation::create(); //viren
	DeclareAnimationAndSprite(m_animBullet,animation,"RedHood/Ammunition/munitions_0%02d.png",1,18,0.5f);

	m_animBullet->setAnchorPoint(ccp(0,0));		

	m_animBullet->setScale(CurrentScale() * 0.4 /*ratio size a bullet  unto the red hat*/);
//  m_animBullet->setScale(CurrentScale() /*ratio size a bullet  unto the red hat*/); //viren
  
  //viren+
//	m_sizeScale.setSize(	m_animBullet->getContentSize().width * CurrentScale(),
//							m_animBullet->getContentSize().height * CurrentScale() );

  //float theScaleFactor = 0.5f;
//  m_sizeScale.setSize(	m_animBullet->getContentSize().width * theScaleFactor,
//  							m_animBullet->getContentSize().height * theScaleFactor );
  //viren-
	addChild(m_animBullet);
		
	CCAnimate *animate = CCAnimate::create(animation);
	m_animBullet->runAction(CCRepeatForever::create(animate));

	m_animBullet->setVisible(true);

    return true;
}

/*
====================
GetPositionRect
====================
*/
cocos2d::CCRect Bullet::GetPositionRect()
{
	cocos2d::CCRect rectSprite = cocos2d::CCRectMake( this->getPosition().x ,
														this->getPosition().y ,
														m_sizeScale.width,
														m_sizeScale.height );
	return rectSprite;
}

/*
====================
UpdatePosition
====================
*/
void Bullet::UpdatePosition()
{
	cocos2d::CCPoint pos = this->getPosition();
	this->setPosition(ccpAdd(pos,m_speed));
}

/*
====================
UpdatePositionRelationOfHero
====================
*/
void Bullet::UpdatePositionRelationOfHero(const cocos2d::CCPoint& speedHero)
{
	cocos2d::CCPoint pos = this->getPosition();
	cocos2d::CCPoint newPos = ccpAdd(pos,m_speed);
	newPos.x -= speedHero.x;
	this->setPosition(newPos);
}

/*
====================
Run
====================
*/
void Bullet::Run( int whereRun, const cocos2d::CCPoint& position, float offsetX , float speedPlayer)
{	
	cocos2d::CCPoint newPosition(position);

	switch (whereRun)
	{
		case kLooking::Right: m_speed.x		 = SPEED_BULLET + speedPlayer;
								newPosition.x += offsetX;
							break;
		case kLooking::Left : m_speed.x		 = -( SPEED_BULLET + std::abs(speedPlayer) );
								newPosition.x	-= offsetX;
							break;
	}
		 
	this->setPosition(newPosition);
	this->setVisible(true);

	if ( pSounds && gSoundCheck )
		pSounds->PlayAttack();
}

/*
====================
SetDeath
====================
*/
void Bullet::SetDeath()
{
	isDeath = true;
	this->setVisible(false);
}

#include "RedHood.h"

#include "../CommonFunc.h"


using namespace cocos2d;

/*
===================================================================================
Class RedHood
===================================================================================
*/

/*
====================
init
====================
*/
bool RedHood::init()
{
	if(! CCLayer::init())
		return false;

	//__________________________ Property _____________________________________

	MAX_JUMP		= CCDirector::sharedDirector()->getWinSize().height / 2  * 0.75f; // 70% of half heiht world
	m_whereLooking	= kLooking::Left;
	m_speed.x		= 0;
	isBlink			= false;
	isDeath			= false;
	isCanShoot		= true;
	pSounds			= NULL;
	//____________________________ LEFT ______________________________________

	m_animRunLeft = new CCSprite();

	CCAnimation* animationLeft = new CCAnimation();
	animationLeft->init();
	DeclareAnimationAndSprite(m_animRunLeft,animationLeft,"RedHood/Move/Left/moveleft_000%02d.png",1,25,1.0f);
	m_animRunLeft->setAnchorPoint(ccp(0,0));	//viren
	m_animRunLeft->setVisible(false);
		
	CCAnimate *animateLeft = CCAnimate::create(animationLeft);
	m_animRunLeft->runAction(CCRepeatForever::create(animateLeft));
	addChild(m_animRunLeft);


	m_spriteStandLeft = CCSprite::create("RedHood/Move/Left/moveleft_00001.png");
	m_spriteStandLeft->setAnchorPoint(ccp(0,0));
	m_spriteStandLeft->setVisible(false);
	//m_spriteStandLeft->setPositionY(7); поправка на высоту.

	addChild(m_spriteStandLeft);
		

	//____________________________ RIGHT _____________________________________

	m_animRunRight = new CCSprite();
	CCAnimation* animationRight = new CCAnimation();
	animationRight->init();
	DeclareAnimationAndSprite(m_animRunRight,animationRight,"RedHood/Move/Right/moveright_000%02d.png",1,25,1.0f);
	m_animRunRight->setAnchorPoint(ccp(0,0));		
	m_animRunRight->setVisible(false);

	CCAnimate *animateRight = CCAnimate::create(animationRight);
	m_animRunRight->runAction(CCRepeatForever::create(animateRight));

	addChild(m_animRunRight);

	m_spriteStandRight = CCSprite::create("RedHood/Move/Right/moveright_00001.png");
	m_spriteStandRight->setAnchorPoint(ccp(0,0));
	m_spriteStandRight->setVisible(false);


	addChild(m_spriteStandRight);

	return true;
}


/*
====================
update
====================
*/
void RedHood::update(CCTime dt)
{
	cocos2d::CCAction *act	= NULL;

	 // bad!! float replace future TDEL
	if ( m_speed.x == 0)
	{
		if ( m_whereLooking == kLooking::Right)
			HideChildrensNotEqSprite(this, m_spriteStandRight);
		else if ( m_whereLooking == kLooking::Left)
			HideChildrensNotEqSprite(this, m_spriteStandLeft);
	}

	if ( m_speed.x > 0)
	{
		m_whereLooking = kLooking::Right;
		HideChildrensNotEqSprite(this, m_animRunRight);
	}

	if ( m_speed.x < 0)
	{
		m_whereLooking = kLooking::Left;
		HideChildrensNotEqSprite(this, m_animRunLeft);
	}

	// has hit?
	act =  this->getActionByTag(kAct::Blink);
	if (!act && isBlink )
	{
		isBlink = false;
	}


}

/*
====================
RunJump
====================
*/
void RedHood::RunJump()
{
	//float jump = 6.5f * CurrentScale();
  float jump = 3.5f * CurrentScale(); //viren
	m_speed.y = jump;
	
	if ( pSounds && gSoundCheck )
		pSounds->PlayJump();
}

/*
====================
StopJump
====================
*/	
void RedHood::StopJump( float altitudeGround )
{
	m_speed.y = 0;
	this->setPositionY(altitudeGround);
}

/*
====================
SetReverseSpeedY
====================
*/
void RedHood::SetReverseSpeedY()
{
	m_speed.y *= -1;
}

/*
====================
SetWorldScale
====================
*/
void RedHood::SetWorldScale (float scale)
{
	this->setScale(scale);
		
	m_sizeScale.setSize(m_spriteStandRight->getContentSize().width * scale,
						m_spriteStandRight->getContentSize().height * scale
						);
}

/*
====================
GetPositionCenter
====================
*/
cocos2d::CCPoint RedHood::GetPositionCenter()
{
	cocos2d::CCPoint pos = this->getPosition();
	pos.x += m_sizeScale.width /2 ;
	pos.y += m_sizeScale.height /2 ;

	return pos;
}

/*
====================
GetPositionRect
====================
*/
cocos2d::CCRect RedHood::GetPositionRect()
{
	cocos2d::CCRect rectSprite = cocos2d::CCRectMake(	this->getPosition().x ,
														this->getPosition().y ,
														m_sizeScale.width,
														m_sizeScale.height );
	return rectSprite;
}

/*
====================
UpdatePositionY
====================
*/
void RedHood::UpdatePositionY()
{
	cocos2d::CCPoint pos = this->getPosition();
	pos.y+=m_speed.y;
	this->setPositionY(pos.y);
}

/*
====================
UpdatePositionX
====================
*/
void RedHood::UpdatePositionX()
{
	cocos2d::CCPoint pos = this->getPosition();
	pos.x+=m_speed.x;
	this->setPositionX(pos.x);;
}

/*
====================
SetSpeedY
====================
*/
void RedHood::SetSpeedY(float newSpeedY)
{
	m_speed.y = newSpeedY;
}

/*
====================
SetSpeedX
====================
*/
void RedHood::SetSpeedX(float newSpeedX)
{
	m_speed.x = newSpeedX;
}

/*
====================
GetSpeed
====================
*/
cocos2d::CCPoint& RedHood::GetSpeed()
{
	return m_speed;
}

/*
====================
GetReverseSpeed
====================
*/
cocos2d::CCPoint RedHood::GetReverseSpeed()
{
	return ccpMult(m_speed,-1);
}

/*
====================
WhereToLooks
====================
*/
int RedHood::WhereToLooks()
{
	return m_whereLooking;
}

/*
====================
GetSizeScale
====================
*/
const cocos2d::CCSize&	RedHood::GetSizeScale()
{
	return m_sizeScale;
}

/*
====================
SetDamage
====================
*/
void RedHood::SetDamage()
{
//viren+
//	CCActionInterval* action = CCBlink::actionWithDuration(3, 12);
  CCBlink* action = new CCBlink();
  //action->initWithDuration(3, 12);
  action->initWithDuration(0.5, 10);
  
  //CCActionInterval* action = CCBlink::actionWithDuration(3, 12);
//viren-
	isBlink = true;
	
	cocos2d::CCAction  *actBlink = this->runAction(action);	  
	actBlink->setTag(kAct::Blink);
}

/*
====================
SetDamage
====================
*/
void RedHood::SetDeath()
{
	if ( pSounds && gSoundCheck && !isDeath)
		pSounds->PlayDeath();
	isDeath = true;
}
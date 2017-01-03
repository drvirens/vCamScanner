#include "Wolf.h"

#include "../CommonFunc.h"
#include "../GameObjects/Ammunition.h"

/*
===================================================================================
Class Wolf
===================================================================================
*/

/*
====================
SetWorldScale
====================
*/
void Wolf::SetWorldScale (float scale)
{
	this->setScale(scale);
	m_sizeScale.setSize( m_animRunLeft->getContentSize().width * scale,
						 m_animRunLeft->getContentSize().height * scale );
}

/*
====================
GetPositionCenter
====================
*/
cocos2d::CCPoint Wolf::GetPositionCenter()
{
	cocos2d::CCPoint pos = this->getPosition();
	pos.x += m_sizeScale.width  / 2 ;
	pos.y += m_sizeScale.height / 2 ;

	return pos;
}

/*
====================
GetSizeScale
====================
*/
const cocos2d::CCSize&	Wolf::GetSizeScale()
{
	return m_sizeScale;
}

/*
====================
GetPositionRect
====================
*/
cocos2d::CCRect	 Wolf::GetPositionRect()
{
	cocos2d::CCRect rectSprite = cocos2d::CCRectMake(this->getPosition().x ,
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
void Wolf::UpdatePosition()
{
	cocos2d::CCPoint pos = this->getPosition();
	this->setPosition(ccpAdd(pos,m_speed));
}

/*
====================
UpdatePositionRelationOfHero
====================
*/
void Wolf::UpdatePositionRelationOfHero(const cocos2d::CCPoint& speedHero)
{
	cocos2d::CCPoint pos = this->getPosition();
	cocos2d::CCPoint newPos = ccpAdd(pos,m_speed);
	newPos.x -= speedHero.x;
	this->setPosition(newPos);
}

/*
====================
RecoverSpeed
====================
*/
void Wolf::RecoverSpeed()
{
	m_speed = m_snapSpeed;
}

/*
====================
StopSpeed
====================
*/
void Wolf::StopSpeed()
{
	m_snapSpeed = m_speed;
	m_speed.setPoint(0,0);
}

/*
====================
GetSpeed
====================
*/
cocos2d::CCPoint& Wolf::GetSpeed()
{
	return		m_speed;
}

/*
====================
SetSpeed
====================
*/
void Wolf::SetSpeed( float x, float y)
{
	m_speed.setPoint(x,y);
}

/*
====================
SetReverseSpeed
====================
*/
void Wolf::SetReverseSpeed()
{
	m_speed = ccpMult(m_speed,-1);
}

/*
====================
SetDeath
====================
*/
void Wolf::SetDeath()
{
	isDeathing = true;

	HideChildrensNotEqSprite(this, m_spriteDeath);
	Wolf::StopSpeed();

	if ( pSounds && gSoundCheck )
		pSounds->PlayDeath();

	cocos2d::CCAnimate *animateDeath = cocos2d::CCAnimate::create(m_animationDeath);
	cocos2d::CCAction  *actDeath	 = m_spriteDeath->runAction(animateDeath->reverse());
	actDeath->setTag(kAct::Death);


}

/*
====================
WillBeKilled
====================
*/
bool Wolf::WillBeKilled ( std::vector<Bullet*>& setBullets )
{	
	for (int i = 0 ; i< setBullets.size(); ++i)
	{
  //viren+
//		if ( !isDeathing && !setBullets[i]->isDeath && cocos2d::CCRect::CCRectIntersectsRect( GetPositionRect(), setBullets[i]->GetPositionRect() )  )
    cocos2d::CCRect thePositionRect = GetPositionRect();
		if ( !isDeathing
              && !setBullets[i]->isDeath
              && thePositionRect.intersectsRect( setBullets[i]->GetPositionRect() )  )
    //viren-
		{
			SetDeath();
			setBullets[i]->SetDeath();
			return true;
		}
	}
	return false;
}

/*
====================
SetHit
====================
*/
void Wolf::SetHit()
{
	isHit = true;

	cocos2d::CCSprite		*spriteHit		= NULL;
	cocos2d::CCAnimation	*animationHit	= NULL;

	switch(m_whereLooking)
	{
		case kLooking::Left:
				spriteHit	 = m_spriteHitLeft;
				animationHit = m_animationHitLeft;
			break;
		case kLooking::Right:
				spriteHit	 = m_spriteHitRight;
				animationHit = m_animationHitRight;
			break;
	}
				
	HideChildrensNotEqSprite(this, spriteHit);
	StopSpeed();

	cocos2d::CCAnimate	*animateHit = cocos2d::CCAnimate::create(animationHit);
	cocos2d::CCAction	*actHit 	= spriteHit->runAction(animateHit);
	actHit->setTag(kAct::Hit);	
}

/*
====================
WhereToLooks
====================
*/
int Wolf::WhereToLooks()
{
	return m_whereLooking;
}	

/*
====================
update
====================
*/
void Wolf::update(cocos2d::CCTime dt)
{
	cocos2d::CCSprite *hit	= NULL;
	cocos2d::CCSprite *run	= NULL;
	cocos2d::CCAction *act	= NULL;

	// Where looks wolf
	switch(m_whereLooking)
	{
		case kLooking::Left:
				run = m_animRunLeft;
				hit = m_spriteHitLeft;
			break;
		case kLooking::Right:
				run = m_animRunRight;
				hit = m_spriteHitRight;
			break;
	}

	// Hit action
	act =  hit->getActionByTag(kAct::Hit);
	if (!act &&  !isDeathing  && isHit)
	{
		//return speed and show animation of moving 
		HideChildrensNotEqSprite(this, run);
		RecoverSpeed();
		isHit = false;
	}

	// Death action
	act =  m_spriteDeath->getActionByTag(kAct::Death);
	if (!act && isDeathing )
	{
		isDeath = true;
	}

	// Look is changing 
	if ( /*m_whereLooking == kLooking::Left &&*/  !isDeathing && m_speed.x > 0)
	{
		m_whereLooking = kLooking::Right;
		HideChildrensNotEqSprite(this, m_animRunRight);
	}

	if ( /* m_whereLooking == kLooking::Right && */!isDeathing && m_speed.x < 0)
	{
		m_whereLooking = kLooking::Left;
		HideChildrensNotEqSprite(this, m_animRunLeft);
	}

}

/*
===================================================================================
Class	WhiteWolf
===================================================================================
*/

/*
====================
init
====================
*/
bool WhiteWolf::init( )
{
	using namespace cocos2d;
	
		 
	//////////////////////////////////////////////////////////////////////////
	// super init first
	//////////////////////////////////////////////////////////////////////////

	if(! CCLayer::init())
		return false;
	//////////////////////////////////////////////////////////////////////////
	// add your codes below...
	//////////////////////////////////////////////////////////////////////////
	isDeath		= false;
	isDeathing	= false;
	isHit		= false;
	isOutScreen = false;
	pSounds		= NULL;

	DISTANCE_ATTACK =  65	 * CurrentScale();
	//MAX_SPEED		=  15.0f * CurrentScale();
  MAX_SPEED		=  8.0f * CurrentScale(); //viren

	m_whereLooking	= kLooking::Right;
	m_speed			= ccp( MAX_SPEED, 0 );
	//____________________________ LEFT ______________________________________

	m_animRunLeft = new CCSprite();
	CCAnimation* animationLeft = new CCAnimation();
	animationLeft->init();

	DeclareAnimationAndSprite(m_animRunLeft,animationLeft,"WhiteWolf/Move/Left/moveleft_000%02d.png",0,25,1.0f);
	m_animRunLeft->setAnchorPoint(ccp(0,0));
	m_animRunLeft->setVisible(false);	

	CCAnimate *animateLeft = CCAnimate::create(animationLeft);
	m_animRunLeft->runAction(CCRepeatForever::create(animateLeft));

	addChild(m_animRunLeft);

		
	m_spriteHitLeft = new CCSprite();
	m_animationHitLeft = new CCAnimation();
	m_animationHitLeft->init();
	 
	DeclareAnimationAndSprite(m_spriteHitLeft,m_animationHitLeft,"WhiteWolf/Hit/Left/hitleft_000%02d.png",0,25,0.6f);
	m_spriteHitLeft->setAnchorPoint(ccp(0,0));
	m_spriteHitLeft->setPositionX( -DISTANCE_ATTACK); //Only for left side
	m_spriteHitLeft->setVisible(false);
		
	addChild(m_spriteHitLeft);


	//____________________________ RIGHT ______________________________________

	m_animRunRight = new CCSprite();
	CCAnimation* animationRight = new CCAnimation();
	animationRight->init();

	DeclareAnimationAndSprite(m_animRunRight,animationRight,"WhiteWolf/Move/Right/moveright_000%02d.png",0,25,1.0f);
	m_animRunRight->setAnchorPoint(ccp(0,0));
	m_animRunRight->setVisible(false);	

	CCAnimate *animateRight = CCAnimate::create(animationRight);
	m_animRunRight->runAction(CCRepeatForever::create(animateRight));

	addChild(m_animRunRight);


	m_spriteHitRight = new CCSprite();
	m_animationHitRight = new CCAnimation();
	m_animationHitRight->init();
	 
	DeclareAnimationAndSprite(m_spriteHitRight,m_animationHitRight,"WhiteWolf/Hit/Right/hitright_000%02d.png",0,25,0.6f);
	m_spriteHitRight->setAnchorPoint(ccp(0,0));
	//m_spriteHitRight->setPositionX( -distanceAttack);
	m_spriteHitRight->setVisible(false);

	addChild(m_spriteHitRight);

	//____________________________ Death _____________________________________

	m_spriteDeath = new CCSprite();
	m_animationDeath = new CCAnimation();
	m_animationDeath->init();

	DeclareAnimationAndSprite(m_spriteDeath,m_animationDeath,"WhiteWolf/Death/death_%02d.png",1,12,0.4f);
	m_spriteDeath->setAnchorPoint(ccp(0,0));
	m_spriteDeath->setVisible(false);
	addChild(m_spriteDeath);

	return true;
}

/*
====================
update
====================
*/
void WhiteWolf::update(cocos2d::CCTime dt)
{
	Wolf::update(dt);
}


/*
===================================================================================
Class	WhiteWolf
===================================================================================
*/

/*
====================
init
====================
*/
bool BlackWolf::init( )
{
	using namespace cocos2d;
	
	//////////////////////////////////////////////////////////////////////////
	// super init first
	//////////////////////////////////////////////////////////////////////////

	if(! CCLayer::init())
		return false;
	//////////////////////////////////////////////////////////////////////////
	// add your codes below...
	//////////////////////////////////////////////////////////////////////////
	isDeath		= false;
	isDeathing	= false;
	isHit		= false;
	isOutScreen = false;
	pSounds		= NULL;

	DISTANCE_ATTACK =  65	 * CurrentScale();
	//MAX_SPEED		=  14.0f * CurrentScale();
  MAX_SPEED		=  7.0f * CurrentScale(); //viren

	m_whereLooking	= kLooking::Right;
	m_speed			= ccp( MAX_SPEED, 0 );

	//____________________________ LEFT ______________________________________

	m_animRunLeft = new CCSprite();
	CCAnimation* animationLeft = new CCAnimation();
	animationLeft->init();

	DeclareAnimationAndSprite(m_animRunLeft,animationLeft,"BlackWolf/Move/Left/moveleft_000%02d.png",0,25,1.0f);
	m_animRunLeft->setAnchorPoint(ccp(0,0));
	m_animRunLeft->setVisible(false);	

	CCAnimate *animateLeft = CCAnimate::create(animationLeft);
	m_animRunLeft->runAction(CCRepeatForever::create(animateLeft));

	addChild(m_animRunLeft);


	m_spriteHitLeft = new CCSprite();
	m_animationHitLeft = new CCAnimation();
	m_animationHitLeft->init();
	 
	DeclareAnimationAndSprite(m_spriteHitLeft,m_animationHitLeft,"BlackWolf/Hit/Left/hitleft_000%02d.png",0,25,0.6f);
	m_spriteHitLeft->setAnchorPoint(ccp(0,0));
	m_spriteHitLeft->setPositionX( -DISTANCE_ATTACK); //Only for left side
	m_spriteHitLeft->setVisible(false);

	addChild(m_spriteHitLeft);

	//____________________________ RIGHT ______________________________________

	m_animRunRight = new CCSprite();
	CCAnimation* animationRight = new CCAnimation();
	animationRight->init();

	DeclareAnimationAndSprite(m_animRunRight,animationRight,"BlackWolf/Move/Right/moveright_000%02d.png",0,25,1.0f);
	m_animRunRight->setAnchorPoint(ccp(0,0));
	m_animRunRight->setVisible(false);	

	CCAnimate *animateRight = CCAnimate::create(animationRight);
	m_animRunRight->runAction(CCRepeatForever::create(animateRight));

	addChild(m_animRunRight);

		
	m_spriteHitRight = new CCSprite();
	m_animationHitRight = new CCAnimation();
	m_animationHitRight->init();
	 
	DeclareAnimationAndSprite(m_spriteHitRight,m_animationHitRight,"BlackWolf/Hit/Right/hitright_000%02d.png",0,25,0.6f);
	m_spriteHitRight->setAnchorPoint(ccp(0,0));
	//m_spriteHitRight->setPositionX( -distanceAttack);
	m_spriteHitRight->setVisible(false);

	addChild(m_spriteHitRight);

	//____________________________ Death _____________________________________

	m_spriteDeath = new CCSprite();
	m_animationDeath = new CCAnimation();
	m_animationDeath->init();
	 
	DeclareAnimationAndSprite(m_spriteDeath,m_animationDeath,"BlackWolf/Death/death_%02d.png",1,12,0.4f);
	m_spriteDeath->setAnchorPoint(ccp(0,0));
	m_spriteDeath->setVisible(false);
	addChild(m_spriteDeath);

	return true;
}

/*
====================
update
====================
*/
void BlackWolf::update(cocos2d::CCTime dt)
{
	Wolf::update(dt);
}

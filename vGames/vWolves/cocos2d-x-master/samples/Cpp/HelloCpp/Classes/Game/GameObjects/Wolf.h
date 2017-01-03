#ifndef __WHITE_WOLF_H__
#define __WHITE_WOLF_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "../Definition.h"
#include "../Sounds.h"

class Wolf : public cocos2d::CCLayer
{
public:

	float						DISTANCE_ATTACK;
	float						MAX_SPEED;

	void						SetWorldScale (float scale);
	cocos2d::CCPoint			GetPositionCenter();
	const cocos2d::CCSize&		GetSizeScale();
	cocos2d::CCRect				GetPositionRect();

	void						UpdatePosition();
	void						UpdatePositionRelationOfHero(const cocos2d::CCPoint& speedHero);

	void						RecoverSpeed();
	void						StopSpeed();
	cocos2d::CCPoint&			GetSpeed(); //del
	void						SetSpeed( float x, float y);
	void						SetReverseSpeed();

	void						SetDeath();
	bool						WillBeKilled( std::vector<Bullet*>& setBullets );
	void						SetHit();
	int							WhereToLooks();

	bool						isDeathing;
	bool						isDeath;
	bool						isHit;
	bool						isOutScreen;

	virtual void				update(cocos2d::CCTime dt);

	ISounds						*pSounds;

protected:

	cocos2d::CCSize				m_sizeScale;
	
	cocos2d::CCPoint			m_speed;
	cocos2d::CCPoint			m_snapSpeed;
	int							m_whereLooking;


	// Left
	cocos2d::CCSprite			*m_animRunLeft;
	cocos2d::CCSprite			*m_spriteHitLeft;
	cocos2d::CCAnimation		*m_animationHitLeft;
	
	// Right
	cocos2d::CCSprite			*m_animRunRight;
	cocos2d::CCAnimation		*m_animationHitRight;
	cocos2d::CCSprite			*m_spriteHitRight;

	// Death
	cocos2d::CCSprite			*m_spriteDeath;
	cocos2d::CCAnimation		*m_animationDeath;
	
};

/*
===================================================================================
class  WhiteWolf
===================================================================================
*/
class WhiteWolf  :   public Wolf
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool
	virtual bool				init();  
	virtual						~WhiteWolf(){};
	// implement the "static node()" method manually
	CREATE_FUNC(WhiteWolf);

	virtual void				update(cocos2d::CCTime dt);
};

/*
===================================================================================
class  BlackWolf
===================================================================================
*/
class BlackWolf  :   public Wolf
{
public:
	virtual bool				init();  
	virtual						~BlackWolf(){};
	CREATE_FUNC(BlackWolf);

	virtual void				update(cocos2d::CCTime dt);
};


#endif //__WHITE_WOLF_H__
#ifndef __RED_HOOD__
#define __RED_HOOD__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "../Sounds.h"

class RedHood  : public cocos2d::CCLayer
{
public:
	
	float							MAX_JUMP;

	virtual bool					init();
	CREATE_FUNC(RedHood);

	void							SetWorldScale ( float scale );
	const cocos2d::CCSize&			GetSizeScale();	
	cocos2d::CCPoint				GetPositionCenter();
	cocos2d::CCRect					GetPositionRect();	

	void							UpdatePositionY();
	void							UpdatePositionX();

	void							SetSpeedY( float newSpeedY );
	void							SetSpeedX( float newSpeedX );
	void							SetReverseSpeedY();
	cocos2d::CCPoint				GetReverseSpeed();
	cocos2d::CCPoint&				GetSpeed();

	void							RunJump();	
	void							StopJump( float altitudeGround );

	int								WhereToLooks();
	void							SetDamage();
	void							SetDeath();
	
	bool							isBlink;
	bool							isCanShoot;
	bool							isDeath;

	virtual void					update(cocos2d::CCTime dt);

	ISounds*						pSounds;

private:
	// According to size screen 
	cocos2d::CCSize				m_sizeScale;
	cocos2d::CCPoint			m_speed;

	int							m_whereLooking;



	cocos2d::CCSprite*			m_animRunLeft;
	cocos2d::CCSprite*			m_spriteStandLeft;

	cocos2d::CCSprite*			m_animRunRight;
	cocos2d::CCSprite*			m_spriteStandRight;
	
};

#endif // __RED_HOOD__
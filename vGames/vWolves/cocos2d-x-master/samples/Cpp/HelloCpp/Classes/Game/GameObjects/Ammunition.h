#ifndef __AMMUNITION_H__
#define __AMMUNITION_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "../Definition.h"



class Bullet  : public cocos2d::CCLayer
{
public:

	float							SPEED_BULLET;

	virtual bool					init();  
	CREATE_FUNC(Bullet);

	cocos2d::CCRect					GetPositionRect();
	void							UpdatePosition();
	void							UpdatePositionRelationOfHero(const cocos2d::CCPoint& speedHero);

	void							Run( int whereRun, const cocos2d::CCPoint& position, float offsetX , float speedPlayer = 0);

	void							SetDeath();
	bool							isDeath;

	ISounds							*pSounds;

private:

	cocos2d::CCPoint				m_speed;

	cocos2d::CCSprite				*m_animBullet;
	cocos2d::CCSize					m_sizeScale;

};

#endif //__AMMUNITION_H__
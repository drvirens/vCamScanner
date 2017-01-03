#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "cocos2d.h"


#include "Definition.h"


#include <list>

class World : public cocos2d::CCLayer
{
public:
  void startNewGame();

	float								ALTITUDE_GROUND;//level ground axis y;
	float								WORLD_SCALE;
	float								WORLW_WIDTH;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool						init();  
    static cocos2d::CCScene*			scene();
	virtual								~World();
    CREATE_FUNC(World);    
    
    virtual void						menuCloseCallback(cocos2d::CCObject* pSender);

   
	virtual void						ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent );
	virtual void						didAccelerate( cocos2d::CCAcceleration* pAccelerationValue );
	virtual void						keyBackClicked();

	void								GameLoop(cocos2d::CCTime dt);

private:
  void goHome();
  void initHud();
  
	void								UpdateLabel(int kLayer, int val);
	void								GenerateWolf (Wolf* wolf);


	bool								isBackGroundRun;	//Edge;

	RedHood								*m_redHood;
	int									m_lifesRedHood;
	int									m_killsRedHood;

	std::vector<Wolf*>					m_enemies;
	std::vector<Wolf*>					m_friends;
	std::vector<Bullet*>				m_bullets;

	cocos2d::CCSprite*					m_backGround;

	SoundsRedHat						*m_soundHood;
	SoundsWolf							*m_soundWolf;
	SoundsBullet						*m_soundBullet;
};

#endif  // __WORLD_SCENE_H__
#include "WorldScene.h"

#include <cmath>	// sta::abs
#include <cstdio>	// sprintf

#include "GameObjects/Ammunition.h"
#include "GameObjects/Wolf.h"
#include "GameObjects/RedHood.h"
#include "CommonFunc.h"

#include "Sounds.h"

#include "ScoreScene.h"
#include "MenuScene.h"

#include "HudLayer.h"
#include "GameManager.h"
#include "GameOverLayer.h"

using namespace cocos2d;

void World::initHud()
{
  HudLayer *hudLayer = HudLayer::create();
  hudLayer->init();
  hudLayer->setTag(kHudLayer);
  
  hudLayer->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT);
  //hudLayer->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT);
  
  float hudScaled = CurrentScale() * 0.75f;
	hudLayer->setAnchorPoint(ccp(0,0));
	hudLayer->setScale(hudScaled);
  
  CCActionInterval *moveToAction = CCMoveTo::create(0.6f,
                  ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT-(hudLayer->getContentSize().height/2)));
  CCActionInterval *easeInAction = CCEaseIn::create(moveToAction, 1.0f);
  hudLayer->runAction(easeInAction);
  this->addChild(hudLayer); //TODO: Z-order???
}

void World::startNewGame()
{
  //distanceTick = 0;
  
  //CCSprite *getReadySprite = CCSprite::createWithSpriteFrameName("get_ready.png");
  CCSprite *getReadySprite = CCSprite::createWithSpriteFrameName("get_ready.png");
  getReadySprite->setPosition(ccp(-getReadySprite->getContentSize().width, SCREEN_HEIGHT/2));
  getReadySprite->setTag(kGameplayLayer_GetReadySprite);
  
  CCFiniteTimeAction *actionSequence = CCSequence::create(
              CCEaseIn::create(CCMoveTo::create(0.6f, ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)), 1.0f),
              //CCCallFunc::create(this, callfunc_selector(GameplayLayer::normalVelocity)),
              CCDelayTime::create(4.0f), //viren: was 1.0f
              CCEaseOut::create(CCMoveTo::create(0.6f, ccp(SCREEN_WIDTH*2, SCREEN_HEIGHT/2)), 1.0f),
//              CCCallFunc::create(this, callfunc_selector(World::initHud)),
//              CCCallFunc::create(this, callfunc_selector(GameplayLayer::initMiraPlayer)),
                                                          NULL
                                                          );
  getReadySprite->runAction(actionSequence);
  this->addChild(getReadySprite);
  
}



CCScene* World::scene()
{
    CCScene * scene = NULL;
	do
	{
	// 'scene' is an autorelease object
    scene = CCScene::create();
    CC_BREAK_IF(! scene);

    // 'layer' is an autorelease object
    World *layer = World::create();
    CC_BREAK_IF(! layer);

    // add layer as a child to scene
    scene->addChild(layer);
	}while (0);
    // return the scene
    return scene;
}


namespace kLayer
{
	enum
	{
		HudLife,
		HudKills
	};
}

void World::UpdateLabel(int kLayer, int val)
{		
	CCLabelBMFont	*label	= (CCLabelBMFont*)getChildByTag(kLayer);
		
	if (label)
	{
		char bufferInfo [10] = {0};
		sprintf(bufferInfo, "%i", val);
		label->setString(bufferInfo);
	}
}

/*
====================
GenInfoWolf
		Generation of information about wolf.
Remark:
		Wolf should be init before call this function.
====================
*/
void World::GenerateWolf(Wolf* wolf)
{
	wolf->setAnchorPoint(ccp(0,0));
	wolf->SetWorldScale(CurrentScale());
			
	cocos2d::CCPoint position(0,ALTITUDE_GROUND);

	int	  turn	= RandomInt();
	float width	= cocos2d::CCDirector::sharedDirector()->getWinSize().width;
	//float speed	= RandomFloat(5.5f , 12.0f) * CurrentScale();
  float speed	= RandomFloat(0.5f , 2.5f) * CurrentScale();//viren

	//float distance = RandomFloat(1.5f , 2.0f);
  float distance = RandomFloat(1.0f , 3.0f);

	if ( turn == 0 )	//Located on the left. Goes to the right.
	{
		position.x = -width * distance;
	}
	else 
	{
		position.x = 2 * width * distance;
		speed = -speed;
	}

	wolf->setPosition(position);
	wolf->SetSpeed(speed,0);

	// sound
	wolf->pSounds = m_soundWolf;

}

// on "init" you need to initialize your instance
bool World::init()
{

    //////////////////////////////////////////////////////////////////////////
    // super init first
    //////////////////////////////////////////////////////////////////////////

    if(! CCLayer::init())
		return false;
		
	this->setTouchEnabled(true);
	this->setAccelerometerEnabled(true);
	this->setKeypadEnabled(true);
    //////////////////////////////////////////////////////////////////////////
    // add your codes below...
    //////////////////////////////////////////////////////////////////////////

	m_backGround = CCSprite::create("BackGround/background_day.png");

	//320/480
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	float scale = screenSize.height / m_backGround->getContentSize().height;
	m_backGround->setScale(scale);

	CCPoint pos(0,0);
	m_backGround->setAnchorPoint(pos);
	pos.x -=  m_backGround->getContentSize().width/2 * scale -  screenSize.width/2;
	m_backGround->setPosition(pos);
    this->addChild(m_backGround, 0);
		

		
	WORLD_SCALE		= scale;
	WORLW_WIDTH		= m_backGround->getContentSize().width * WORLD_SCALE;
	//ALTITUDE_GROUND = 35 * CurrentScale();
  ALTITUDE_GROUND = 25 * CurrentScale(); //viren
	isBackGroundRun = false;

	//m_lifesRedHood	= 9;
  m_lifesRedHood	= GameManager::sharedGameManager()->getStartingLives();
	m_killsRedHood	= 0;
		
	m_soundHood		= new SoundsRedHat();
	m_soundBullet	= new SoundsBullet();
	m_soundWolf		= new SoundsWolf();

	//_____________________________ HUD ______________________________________
  
  //initHud(); //TODO: Use callback sequence
		
	float hudScaled = CurrentScale() * 0.5f;

	//float hudScaled = 0.3f; //CurrentScale() ;

	CCSprite* pHeart = CCSprite::create("Hud/heart.png");
	pHeart->setAnchorPoint(ccp(0,0));
	pHeart->setScale(hudScaled);

	CCSize sizeHeart =   pHeart->getContentSize();
	sizeHeart.height *= hudScaled;
	sizeHeart.width  *= hudScaled;
	pHeart->setPosition( ccp(sizeHeart.width/2, screenSize.height - ( sizeHeart.height * 1.5f)) );
	this->addChild(pHeart);


	CCSprite* pKilled = CCSprite::create("Hud/killed.png");
	pKilled->setAnchorPoint(ccp(0,0));
	// hudScaled - the same size
	pKilled->setScale(hudScaled);
	pKilled->setPosition( ccp(sizeHeart.width/2, screenSize.height - ( sizeHeart.height * 2.5f)) );
	this->addChild(pKilled);

 
	CCLabelBMFont* lifes = CCLabelBMFont::create("0",  "markerFelt.fnt");
	lifes->setAnchorPoint( ccp(0,0) );
	lifes->setScale ( CurrentScale() );
	//lifes->setPosition ( ccp (sizeHeart.width * 1.7 , screenSize.height - ( sizeHeart.height * 1.55f)));
  //viren+ make overlay for now as hudlabels not working
  int theX = sizeHeart.width * 1.7;
  int theY = screenSize.height - ( sizeHeart.height * 1.55f);
  CCLOG("theX = %d, theY = %d", theX, theY);
  CCPoint thePoint = ccp (theX , theY);
//  theX = theX + 500;
//  theY = theY - 150;
//  CCLOG("new theX = %d, theY = %d", theX, theY);
  lifes->setPosition ( thePoint );
  
  //viren-
		
	addChild(lifes, 1, kLayer::HudLife);
	UpdateLabel(kLayer::HudLife, m_lifesRedHood);
		
	CCLabelBMFont* kills = CCLabelBMFont::create("0",  "markerFelt.fnt");
	kills->setAnchorPoint( ccp(0,0) );
	kills->setScale ( CurrentScale() );
	kills->setPosition ( ccp (sizeHeart.width * 1.7 , screenSize.height - ( sizeHeart.height * 2.6f)));
		
	addChild(kills, 1, kLayer::HudKills);
	UpdateLabel(kLayer::HudKills, m_killsRedHood);

	//_____________________________ Hat ______________________________________

	m_redHood = new RedHood();
	m_redHood->init();
	m_redHood->setAnchorPoint(ccp(0,0));
	m_redHood->SetWorldScale( CurrentScale() );	
	m_redHood->setPosition(screenSize.width/2 - m_redHood->GetSizeScale().width/2 ,ALTITUDE_GROUND);
	m_redHood->pSounds = m_soundHood;
	
	m_redHood->setPositionY(ALTITUDE_GROUND);

	addChild(m_redHood);

	//_____________________________ Wolfs_____________________________________
	// Generate the wolves ...
	// Total 4 enemy 3 friend
	for (int i = 0 ; i < 4; ++i)
	{
		BlackWolf*	wEnemy = new BlackWolf();
		wEnemy->init();
		GenerateWolf(wEnemy);
			
		this->addChild(wEnemy);
		m_enemies.push_back(wEnemy);

		if (i < 3)
		{
			WhiteWolf*	wFriend = new WhiteWolf();
			wFriend->init();
			
			GenerateWolf(wFriend);
			
			this->addChild(wFriend);
			m_friends.push_back(wFriend);
		}
	}
  
  // --------------- Virens HUD
  //initHud(); //TODO: Use callback sequence : label update not working
  

//	if (gSoundCheck)
//		PreloadSounds::PlayBackGround();
	
	this->schedule( schedule_selector(World::GameLoop));

    return true;
}

/*
====================
ccTouchesBegan
====================
*/
void World::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	
    CCPoint	point;
    CCTouch	*touch;

	float speedHood  = 5 * CurrentScale();

    for(  ; it != pTouches->end(); ++it )
    {
		touch = (CCTouch*)(*it);
		point = touch->getLocationInView();
		
		float t = point.x;
		
		// Jump - left half screen 
		if ( point.x < CCDirector::sharedDirector()->getWinSize().width/2 )
		{
			if ( m_redHood->GetSpeed().y == 0 )
				m_redHood->RunJump();
			
		}

		// Hit - right half screen 
		if ( point.x > CCDirector::sharedDirector()->getWinSize().width/2 )
		{
			CCPoint posPlayer = m_redHood->GetPositionCenter();
			Bullet* shot = new Bullet();
			shot->init();
			shot->pSounds = m_soundBullet;


			shot->Run(m_redHood->WhereToLooks() , posPlayer ,m_redHood->GetSizeScale().width/2, m_redHood->GetSpeed().x );

			m_bullets.push_back(shot);
			addChild(shot);
		}
    }
}

/*
====================
didAccelerate
====================
*/
void World::didAccelerate(CCAcceleration* pAccelerationValue)
{
  //CCLOG("World::didAccelerate");
  if (!pAccelerationValue) {
    //CCLOG("pAccelerationValue is NULL so return");
    return;
  }
	//float speed = pAccelerationValue->x * 9.18;
  float speed = pAccelerationValue->x * 8.18; //viren
	//m_redHood->SetSpeedX(speed * 3); //viren
  m_redHood->SetSpeedX(speed * 1);
}

void World::goHome()
{
  //this->getChildByTag(kGameOverLayer_PlayAgainMenu)->stopAllActions();
  //GameManager::sharedGameManager()->showMainMenu();
  
  GameManager::sharedGameManager()->endGame(); //will take you to home
}

/*
====================
keyBackClicked
====================
*/
void World::keyBackClicked()
{
  CCLOG("back key pressed");
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
//	CCScene *pScene = MenuScene::scene();
//	CCDirector::sharedDirector()->replaceScene(pScene);
  
  goHome();
#endif
}

/*
====================
menuCloseCallback
====================
*/
void World::menuCloseCallback(CCObject* pSender)
{
	// Exit
	CCDirector::sharedDirector()->end();
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

/*
====================
~World()
====================
*/
World::~World()
{
	delete m_soundHood;
	delete m_soundWolf;
	delete m_soundBullet;
}

/*
====================
GameLoop
====================
*/
void World::GameLoop(cocos2d::CCTime dt)
{
	if (m_lifesRedHood < 1)
	{
		m_redHood->SetDeath();
		// Change the game state to score
    //viren : use better game over scene
//		CCScene *pScene = ScoreScene::scene(m_killsRedHood);
//		CCDirector::sharedDirector()->replaceScene(pScene);

//    GameOverLayer* gameOverLayer = GameManager::sharedGameManager()->getGameOverLayer();
//    if (!gameOverLayer) {
//      gameOverLayer = GameOverLayer::create();
//      gameOverLayer->retain();
//      gameOverLayer->setTag(kGameManager_GameOverLayer);
//      GameManager::sharedGameManager()->setGameOverLayer(gameOverLayer);
//    }
//    
    
    
    
//    CCScene *gameOverLayer = GameOverLayer::scene();
//    gameOverLayer->retain();
//    gameOverLayer->setTag(kGameManager_GameOverLayer);
//    //::scene(m_killsRedHood);
//    CCDirector::sharedDirector()->replaceScene(gameOverLayer);

    GameManager::sharedGameManager()->endGame();
    return;
	}

	// Jump Red Hat
	if (m_redHood->getPosition().y > m_redHood->MAX_JUMP) 
	{
		m_redHood->SetReverseSpeedY();
	}
	else if (m_redHood->getPositionY()  < ALTITUDE_GROUND )
	{
		m_redHood->StopJump(ALTITUDE_GROUND);
	}

	float screenWidth		= CCDirector::sharedDirector()->getWinSize().width;
	float halfScreenWidth	= screenWidth/2.0f;
	float leftFrontier		= 50;
	float rightFrontier		= WORLW_WIDTH - screenWidth - 50;

	// For entities (wolfs, ammo)
	cocos2d::CCPoint reverseSpeedHat( m_redHood->GetReverseSpeed() );


	// Working with the background and the location of Hats
		// If we are not achieved the left boundary and position Hats is center then move background
	if ( m_redHood->WhereToLooks() == kLooking::Left && (std::abs(m_backGround->getPosition().x) >= leftFrontier && m_redHood->GetPositionCenter().x <= halfScreenWidth) ||
		// If we are not achieved the right boundary 
		m_redHood->WhereToLooks() == kLooking::Right && (std::abs(m_backGround->getPosition().x) <= rightFrontier && m_redHood->GetPositionCenter().x >= halfScreenWidth) )
	{
		m_backGround->setPosition(ccpAdd(m_backGround->getPosition(),
											ccp( reverseSpeedHat.x, 0)) );
		isBackGroundRun = true;
	}// Boundary movement background  is reached. Can move Hat.
	else if	(	// should not go beyond the screen
				m_redHood->WhereToLooks() == kLooking::Left && m_redHood->getPosition().x > 0 && 
				(m_redHood->GetPositionCenter().x > halfScreenWidth || std::abs(m_backGround->getPosition().x) <= leftFrontier) 
				||
				m_redHood->WhereToLooks() == kLooking::Right && m_redHood->getPosition().x + m_redHood->GetSizeScale().width < screenWidth && 
				(m_redHood->GetPositionCenter().x < halfScreenWidth || std::abs(m_backGround->getPosition().x) >= rightFrontier)
	)
	{
		m_redHood->UpdatePositionX();
		isBackGroundRun = false;
	}

	m_redHood->UpdatePositionY();
 	m_redHood->update(dt);
	
	// Update position of shells
	for (int i = 0 ; i< m_bullets.size(); ++i)
	{
		// Move the wolf relative to hats.
		if (isBackGroundRun)
			m_bullets[i]->UpdatePositionRelationOfHero(m_redHood->GetSpeed());
		else 
			m_bullets[i]->UpdatePosition(); // Hat began the really to move.

		if ( IsOutScreen(m_bullets[i]->GetPositionRect(),halfScreenWidth,leftFrontier, screenWidth)  || m_bullets[i]->isDeath )
		{
			m_bullets[i]->SetDeath();
			removeChild(m_bullets[i], true);
			m_bullets.erase(m_bullets.begin()+i);
		}
	}
 
	// Enemies...
	for (int i = 0 ; i< m_enemies.size(); ++i)
	{
		if (m_enemies[i]->isDeath)
		{	 	 
			removeChild(m_enemies[i], true);
			m_enemies.erase(m_enemies.begin()+i);
			
			// Generate a new wolf
			BlackWolf*	wEnemy = new BlackWolf();
			wEnemy->init();	
			GenerateWolf(wEnemy);
			this->addChild(wEnemy);
			m_enemies.push_back(wEnemy);
		}
		else 
		{
			CCRect enemyRect = m_enemies[i]->GetPositionRect();
			
			// Move the wolf relative to hats.
			if (isBackGroundRun)
				m_enemies[i]->UpdatePositionRelationOfHero(m_redHood->GetSpeed());
			else 
				m_enemies[i]->UpdatePosition(); // Hat began the really to move.

			// Boundary movement of the wolf
			int limitBoundaries = 100;
			// m_enemies[i]->m_whereLooking == kLooking the wolf did not depart greatly from the Hat
			if ( ( m_enemies[i]->WhereToLooks() == kLooking::Left && m_enemies[i]->GetPositionCenter().x <= /*0*/-limitBoundaries ) ||
				 ( m_enemies[i]->WhereToLooks() == kLooking::Right && m_enemies[i]->GetPositionCenter().x >= screenWidth+limitBoundaries ) )
			{
				m_enemies[i]->SetReverseSpeed();
			}


			if ( !IsOutScreen(enemyRect,halfScreenWidth,leftFrontier, screenWidth) && !m_enemies[i]->isDeathing ) // � �������� ��������� � �� �������
			{
				// Do  I need to attack.
				float distanceToAttack = m_enemies[i]->GetPositionCenter().x - m_redHood->GetPositionCenter().x ;		 
		
				if(	m_enemies[i]->isHit != true	&&																					// Wolf does is not beat
					!m_redHood->isBlink && 																							// Hat does is not blink
					m_enemies[i]->WhereToLooks() !=  m_redHood->WhereToLooks()  &&													// Looked at each other
					m_redHood->getPosition().y <  m_enemies[i]->getPosition().y + m_enemies[i]->GetPositionCenter().y &&			// Reaches a height whether the attack		
					( 
					  ( std::abs(distanceToAttack - m_redHood->GetSizeScale().width )  <=  m_enemies[i]->DISTANCE_ATTACK ) ||		// Left hit, falls into the distance attack + adjusting the position of Hat
					  ( std::abs( distanceToAttack  + m_enemies[i]->GetSizeScale().width/2 )  <=  m_enemies[i]->DISTANCE_ATTACK )	// Right hit + adjusting
					) 	
				)
				{
					m_enemies[i]->SetHit();
					m_redHood->SetDamage();

					--m_lifesRedHood;
					UpdateLabel(kLayer::HudLife, m_lifesRedHood);
          
          GameManager::sharedGameManager()->takeLife();

				}
			
				// causes damage to the Hat without attacking
				if(!m_redHood->isBlink && 
					m_enemies[i]->WhereToLooks() ==  m_redHood->WhereToLooks() && //Looks in one direction
					//CCRect::CCRectIntersectsRect( enemyRect, m_redHood->GetPositionRect() ) ) //viren
          enemyRect.intersectsRect( m_redHood->GetPositionRect() ) )
				{
					m_redHood->SetDamage();

					--m_lifesRedHood;
					UpdateLabel(kLayer::HudLife, m_lifesRedHood);
          
          GameManager::sharedGameManager()->takeLife();
				}

				if (m_enemies[i]->WillBeKilled(m_bullets))
				{
					++m_killsRedHood;
					UpdateLabel(kLayer::HudKills, m_killsRedHood);
          
          GameManager::sharedGameManager()->increaseScore( kUnitScoreIncrease_KilledBlackWolf );
				}
			}

			m_enemies[i]->update(dt);
		}
	}

	// Friends...
	for (int i = 0 ; i < m_friends.size(); ++i)
	{
		if (m_friends[i]->isDeath)
		{	 
			Wolf* tmp = m_friends[i];
			removeChild(m_friends[i], true);
			m_friends.erase(m_friends.begin()+i);

			// Generate a new wolf
			WhiteWolf*	wFriend = new WhiteWolf();
			wFriend->init();
			GenerateWolf(wFriend);	
			this->addChild(wFriend);
			m_friends.push_back(wFriend);

		}
		else 
		{
			CCRect friendRect = m_friends[i]->GetPositionRect();
			
			// Move the wolf relative to hats.
			if (isBackGroundRun)
				m_friends[i]->UpdatePositionRelationOfHero(m_redHood->GetSpeed());
			else 
				m_friends[i]->UpdatePosition(); // Hat began the really to move.

			// Boundary movement of the wolf
			int limitBoundaries = 100;
			
			if ( ( m_friends[i]->WhereToLooks() == kLooking::Left && m_friends[i]->GetPositionCenter().x <= /*0*/-limitBoundaries ) ||
				 ( m_friends[i]->WhereToLooks() == kLooking::Right && m_friends[i]->GetPositionCenter().x >= screenWidth+limitBoundaries ) )
			{
				m_friends[i]->SetReverseSpeed();
			}


			if ( !IsOutScreen(friendRect,halfScreenWidth,leftFrontier, screenWidth) )
			{
				if (m_friends[i]->WillBeKilled(m_bullets))
				{
					m_redHood->SetDamage();
					
					--m_lifesRedHood;
					UpdateLabel(kLayer::HudLife, m_lifesRedHood);
          
          GameManager::sharedGameManager()->takeLife();
				}
			}

			m_friends[i]->update(dt);
		}
	}
}


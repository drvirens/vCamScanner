#include "ScoreScene.h"

#include <string>
#include <cstdio> // sprintf

USING_NS_CC;


#include "Sounds.h"
#include "CommonFunc.h"

#include "WorldScene.h"
#include "MenuScene.h"

CCScene* ScoreScene::scene( int score)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	ScoreScene *layer = ScoreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	layer->UpdateScore(score );
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
		return false;


	float hudScaled	 = 0.8f	 * CurrentScale();
	float hudPadding = 50.0f * CurrentScale(); // отступ от границ экрана
		  m_score	 = 0;

	CCSprite* pBackGround = CCSprite::create("BackGround/menu.png");

	//320/480
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	float scale = screenSize.height / pBackGround->getContentSize().height;
	pBackGround->setScale(scale);

	pBackGround->setAnchorPoint(ccp(0,0));
	pBackGround->setPosition(ccp (0,0) );
	this->addChild(pBackGround, 0);


	CCSprite* pTitle = CCSprite::create("Hud/score.png");
	pTitle->setScale(scale);

	pTitle->setAnchorPoint(ccp(0.5f,1.0f));
	pTitle->setPosition(ccp (screenSize.width / 2, screenSize.height - hudPadding) );
	this->addChild(pTitle, 0);


	std::string againPlay("Hud/Again.png");
	CCMenuItemImage* ctrlAgainPlay = CCMenuItemImage::create(	againPlay.c_str(), againPlay.c_str(),
																		this,  menu_selector(ScoreScene::menuAgainPlayCallback) );
	// sizeButon (volume, exit have one size)
	CCSize sizeButon =  ctrlAgainPlay->getContentSize();
	sizeButon.height *= hudScaled;
	sizeButon.width  *= hudScaled;
			
	ctrlAgainPlay->setAnchorPoint(ccp(0,0));
	ctrlAgainPlay->setScale(hudScaled);
	ctrlAgainPlay->setPosition( ccp( hudPadding  , hudPadding) );

 

	std::string exitGame("Hud/Exit.png");
	CCMenuItemImage *ctrlExitGame = CCMenuItemImage::create(	exitGame.c_str(), exitGame.c_str(),
																			this,  menu_selector(ScoreScene::menuCloseCallback) );
	ctrlExitGame->setAnchorPoint(ccp(0,0));
	ctrlExitGame->setScale(hudScaled);
	ctrlExitGame->setPosition( ccp( screenSize.width - sizeButon.width - hudPadding  , hudPadding) );



	CCSprite* pSkull = CCSprite::create("Hud/killed.png");
	pSkull->setScale(CurrentScale());
	pSkull->setPosition( ccp( screenSize.width / 3  , screenSize.height / 2 - hudPadding ) );
	this->addChild(pSkull, 0);


	CCLabelBMFont* kills = CCLabelBMFont::create("0",  "Hud/digits.fnt");
	kills->setScale ( CurrentScale() * 2 );
	kills->setPosition ( ccp (screenSize.width / 4 * 2.6f , screenSize.height / 2 - hudPadding));
		
	addChild(kills, 1 , 13);


	CCMenu* pMenu = CCMenu::create(ctrlAgainPlay,ctrlExitGame, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	PreloadSounds::StopBackGround();

	return true;
}

void ScoreScene::UpdateScore( int score)
{
	CCLabelBMFont	*label	= (CCLabelBMFont*)getChildByTag(13);
		
	if (label)
	{
		char bufferInfo [10] = {0};
		sprintf(bufferInfo, "%i", score);
		label->setString(bufferInfo);
	}
}

void ScoreScene::menuCloseCallback(CCObject* pSender)
{
	CCScene *pScene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}


void ScoreScene::menuAgainPlayCallback(CCObject* pSender)
{
	CCScene *pScene = World::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
 
 
#include "SysMenu.h"
//#include "GameLayer.h"
//#include "GameControlMenu.h"
#include "SettingsLayer.h"

using namespace cocos2d;

SysMenu::SysMenu(void)
{

}

SysMenu::~SysMenu(void)
{

}

bool SysMenu::init(void)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		// ��һ��ͼƬ������ı���
		CCSprite* sp = CCSprite::spriteWithFile("bg.png");
		CC_BREAK_IF(!sp);
		sp->setAnchorPoint(CCPointZero);
		this->addChild(sp, 0, 1);

		// ���ò˵�������
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(25);

		// ��һ����5���˵���
		CCMenuItemFont* newGame = CCMenuItemFont::itemWithString("NewGame", this, menu_selector(SysMenu::onNewGame));
		CC_BREAK_IF(!newGame);

		CCMenuItemFont* loadGame = CCMenuItemFont::itemWithString("Load");
		CC_BREAK_IF(!loadGame);

		CCMenuItemFont* gameSettings = CCMenuItemFont::itemWithString("Option", this, menu_selector(SysMenu::onSettings));
		CC_BREAK_IF(!gameSettings);

		CCMenuItemFont* help = CCMenuItemFont::itemWithString("Help");
		CC_BREAK_IF(!help);

		CCMenuItemFont* quit = CCMenuItemFont::itemWithString("Quit", this, menu_selector(SysMenu::onQuit));
		CC_BREAK_IF(!quit);

		// ����Щ�˵�����뵽�˵�������
		CCMenu* menu = CCMenu::menuWithItems(newGame, loadGame, gameSettings, help, quit, NULL);
		CC_BREAK_IF(!menu);

		// ���ò˵������򲼾���ʾ
		menu->alignItemsVertically();
		// ���˵������������
		this->addChild(menu, 1, 2);

		bRet = true;
	} while (false);

	return bRet;
}

CCScene* SysMenu::scene(void)
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::node();
		CC_BREAK_IF(!scene);

		SysMenu* layer = SysMenu::node();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);
	} while (false);

	return scene;
}

void SysMenu::onNewGame(CCObject* pSender)
{
//	CCScene* scene = CCScene::node();
//	// ��Ϸ��Ϳ��Ʋ�
//	scene->addChild(GameLayer::node());
//	scene->addChild(GameControlMenu::node());
//	// ���ҵ�����������л�����Ϸ����
//	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::transitionWithDuration(1.2f, scene));
}

void SysMenu::onSettings(CCObject* pSender)
{
	CCScene* scene = CCScene::node();
	scene->addChild(SettingsLayer::node());
	// ���ű任�л�����Ϸ���û���
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::transitionWithDuration(1.2f, scene));
}

void SysMenu::onQuit(CCObject* pSender);
{
	CCDirector::sharedDirector()->end();
}
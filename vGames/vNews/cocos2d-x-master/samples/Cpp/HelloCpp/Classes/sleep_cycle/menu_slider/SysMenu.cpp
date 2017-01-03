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

		// 用一个图片做画面的背景
		CCSprite* sp = CCSprite::spriteWithFile("bg.png");
		CC_BREAK_IF(!sp);
		sp->setAnchorPoint(CCPointZero);
		this->addChild(sp, 0, 1);

		// 设置菜单项字体
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(25);

		// 逐一创建5个菜单项
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

		// 将这些菜单项都加入到菜单对象中
		CCMenu* menu = CCMenu::menuWithItems(newGame, loadGame, gameSettings, help, quit, NULL);
		CC_BREAK_IF(!menu);

		// 设置菜单以纵向布局显示
		menu->alignItemsVertically();
		// 将菜单加入主层对象
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
//	// 游戏层和控制层
//	scene->addChild(GameLayer::node());
//	scene->addChild(GameControlMenu::node());
//	// 从右到左滚动画面切换到游戏场景
//	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::transitionWithDuration(1.2f, scene));
}

void SysMenu::onSettings(CCObject* pSender)
{
	CCScene* scene = CCScene::node();
	scene->addChild(SettingsLayer::node());
	// 缩放变换切换到游戏设置画面
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::transitionWithDuration(1.2f, scene));
}

void SysMenu::onQuit(CCObject* pSender);
{
	CCDirector::sharedDirector()->end();
}
#include "SettingsLayer.h"
#include "SysMenu.h"

using namespace coocs2d;

SettingsLayer::SettingsLayer(void)
{

}

SettingsLayer::~SettingsLayer(void)
{

}

bool SettingsLayer::init(void)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		// ���ñ�������
		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		// ��һ������״̬�Ĳ˵�����Ϊ����
		CCMenuItemFont* title1 = CCMenuItemFont::itemWithString("Sound");
		CC_BREAK_IF(!title1);
		title1->setEnabled(false);

		// ����ѡ������
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);

		// ���ÿ��л��Ĳ˵���˵�״̬��������
		CCMenuItemToggle* item1 = CCMenuItemToggle::itemWithTarget(NULL, NULL, CCMenuItemFont::itemWithString("On"),
			CCMenuItemFont::itemWithString("Off"), NULL);

		CC_BREAK_IF(!item1);

		// ���ñ�������
		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		CCMenuItemFont* title2 = CCMenuItemFont::itemWithString("Music");
		CC_BREAK_IF(!title2);
		title2->setEnabled(false);

		// ����ѡ������
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCMenuItemToggle* item2 = CCMenuItemToggle::itemWithTarget(NULL, NULL, 
			CCMenuItemFont::itemWithString("On"), CCMenuItemFont::itemWithString("Off"), NULL);
		CC_BREAK_IF(!item2);

		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		CCMenuItemFont* title3 = CCMenuItemFont::itemWithString("AI");
		CC_BREAK_IF(!title3);
		title3->setEnabled(false);

		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCMenuItemFont* item3 = CCMenuItemToggle::itemWithTarget(NULL, NULL, 
			CCMenuItemFont::itemWithString("Attack"), CCMenuItemFont::itemWithString("Defense"), NULL);
		CC_BREAK_IF(!item3);

		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		CCMenuItemFont* title4 = CCMenuItemFont::itemWithString("AI");
		CC_BREAK_IF(!title4);
		title4->setEnabled(false);

		// ���ö�ѡ��Ч�������ȼ���һ����ѡ��(subItems)���ټ���һ�������˶���Ӳ˵�������
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCMenuItemToggle* item4 = CCMenuItemToggle::itemWithTarget(NULL, NULL,
			CCMenuItemFont::itemWithString("Easy"), NULL);
		CC_BREAK_IF(!item4);
		
		CCArray< CCMenuItem* > * more_items = CCArray< CCMenuItem* >::arrayWithObject(
			CCMenuItemFont::itemWithString("Normal"), CCMenuItemFont::itemWithString("Hard"), CCMenuItemFont::itemWithString("Nightmare"), NULL);
		CC_BREAK_IF(!more_items);
		item4->getSubItems()->addObjectsFromArray(more_items);
		item4->setSelectedIndex(0);

		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCLabelBMFont* label = CCLabelBMFont::labelWithString("Go back", "font01.fnt");
		CC_BREAK_IF(!label);
		CCMenuItemLabel* back = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(SettingsLayer::backCallback));
		CC_BREAK_IF(!back);
		back.setScale(0.8f);

		// ��ϴ����˵���
		CCMenu* menu = CCMenu::menuWithItems(title1, title2, item1, item2, title3, title4, item3, item4, back, NULL);
		CC_BREAK_IF(!menu);
		
		// ���ö��еĲ˵����
		menu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
		this->addChild(menu);

		// �ֹ�΢��һ�����һ���˵����λ��
		cocos2d::CCPoint cp_back = back->getPosition();
		cp_back.y -= 50.0f;
		back->setPosition(cp_back);

		bRet = true;

	} while (false);

	return bRet;
}

void SettingsLayer::backCallback(CCObject* pSender)
{
	CCScene* scene = CCScene::node();
	scene->addChild(SysMenu::node());
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::transitionWithDuration(1.2f, scene));
}
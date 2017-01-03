//
//  kMainToolBar.cpp
//
//  Created by kael on 1/8/13.
//
//

#include "kMainToolBarCell.h"
//#include "kMainUiLayer.h"
#include "kConstDefine.h"
kMainToolBarCell::kMainToolBarCell(unsigned short _t)
{
    char name[16];
    sprintf(name, "tb%d.png",_t);
    _type = _t;
    
    CCTexture2D *pTextureShadow = CCTextureCache::sharedTextureCache()->addImage(name);
    CCSpriteFrame* shadowFrame = CCSpriteFrame::createWithTexture(pTextureShadow, CCRectMake(0, 0, pTextureShadow->getPixelsWide(), pTextureShadow->getPixelsHigh()));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(shadowFrame, name);
    CCSpriteFrame *spf2=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    
    // create from sprite frames cache
    CCScale9Sprite *backgroundButton2 = CCScale9Sprite::createWithSpriteFrame(spf2);//
    content = CCControlButton::create(backgroundButton2);
    content->setTouchPriority(TOUCH_PRIORITY_MAINVIEW);
    content->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
    content->setPreferredSize(spf2->getRect().size);
    content->addTargetWithActionForControlEvents(this, cccontrol_selector(kMainToolBarCell::iambeclick), CCControlEventTouchUpInside);
    _w = spf2->getRect().size.width;
    _h = spf2->getRect().size.height;
    content->setOpacity(0);
    this->addChild(content);
}

kMainToolBarCell::~kMainToolBarCell()
{
    this->removeAllChildrenWithCleanup(true);
}

void kMainToolBarCell::onExpand(const CCPoint& target,float dur)
{
    this->setVisible(true);
    CCMoveTo* move = CCMoveTo::create(dur,target);
    CCEaseBackOut* bo = CCEaseBackOut::create(move);
    CCFadeIn* fi = CCFadeIn::create(dur);
    content->runAction(fi);
    this->runAction(bo);
}

void kMainToolBarCell::onCompact(const CCPoint& target,float dur)
{
    CCMoveTo* move = CCMoveTo::create(dur,target);
    CCFadeOut* fo = CCFadeOut::create(dur);
    content->runAction(fo);
    this->runAction(move);
}

void kMainToolBarCell::iambeclick(CCObject* pSender,CCControlEvent*)
{
    if(this->getParent()!=NULL)
    {
        // parent is mainuilayer
//        kMainUiLayer* m = (kMainUiLayer*)this->getParent();
//        m->onToolBarClicked(_type);
    }
}
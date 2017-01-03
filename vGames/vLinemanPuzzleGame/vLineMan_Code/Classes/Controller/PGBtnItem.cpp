//
//  Bz_btnItem.cpp
//  Bz_gameControl
//
//  Created by Binz_- on 13-6-26.
//
//


#include "PGBtnItem.h"
Bz_btnItem::~Bz_btnItem(){
    CC_SAFE_RELEASE(m_texNormal);
    CC_SAFE_RELEASE(m_texSelected);
}
bool
Bz_btnItem::init()
{
    if(!CCSprite::init()) return false;
    
    if (!m_texNormal) m_texNormal = NULL;
    if (!m_texSelected) m_texSelected = NULL;
    
    m_bIsSelected = false;
    
    initWithTexture(m_texNormal);
    
    return true;
}
bool
Bz_btnItem::initWithNormalTexAndSelectedTex(CCTexture2D *normal,CCTexture2D *selected)
{
    
    CCAssert(normal != NULL, "normal texture is NULL");
    CCAssert(selected != NULL, "selected texture is NULL");
    
    setNormalTex(normal);
    setSelectedTex(selected);
    
    return init();
}

Bz_btnItem* Bz_btnItem::createWithNormalTexAndSelectedTex(CCTexture2D *normal,CCTexture2D *selected)
{
    Bz_btnItem *item = new Bz_btnItem();
    if (item && item->initWithNormalTexAndSelectedTex(normal,selected)) {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return NULL;
}

Bz_btnItem*
Bz_btnItem::createWithNormalFileAndSelectedFile(const char *normal, const char *selected){
    Bz_btnItem *item = new Bz_btnItem();
    if (item && item->initWithNormalFileAndSelectedFile(normal,selected)) {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return NULL;
}
bool
Bz_btnItem::initWithNormalFileAndSelectedFile(const char *normal, const char *selected){
    CCAssert(normal != NULL, "normal texture is NULL");
    CCAssert(selected != NULL, "selected texture is NULL");
    
    setNormalTex(normal);
    setSelectedTex(selected);
    
    return init();
}

/*
 
 */

void
Bz_btnItem::showButtonTexture(bool isSelected)
{
    m_bIsSelected = isSelected;
    if (!m_bIsSelected)
        setTexture(m_texNormal);
    else
        setTexture(m_texSelected);
    
}
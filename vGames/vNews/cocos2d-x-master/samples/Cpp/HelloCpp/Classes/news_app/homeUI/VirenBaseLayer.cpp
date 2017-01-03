//
//  VirenBaseLayer.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 11/30/13.
//
//

#include "VirenBaseLayer.h"

void VirenBaseLayer::doAlignItemsHorizontallyWithPadding(float padding)
{
  
  float width = -padding;
  if (m_pChildren && m_pChildren->count() > 0)
  {
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
      CCNode* pChild = dynamic_cast<CCNode*>(pObject);
      if (pChild)
      {
        width += pChild->getContentSize().width * pChild->getScaleX() + padding;
      }
    }
  }
  
  float x = -width / 2.0f;
  if (m_pChildren && m_pChildren->count() > 0)
  {
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
      CCNode* pChild = dynamic_cast<CCNode*>(pObject);
      if (pChild)
      {
        pChild->setPosition(ccp(x + pChild->getContentSize().width * pChild->getScaleX() / 2.0f, 0));
        x += pChild->getContentSize().width * pChild->getScaleX() + padding;
      }
    }
  }
}

  //Menu - Alignment
void VirenBaseLayer::doAlignItemsVertically()
{
  this->doAlignItemsVerticallyWithPadding(kDefaultVirenPadding);
}

void VirenBaseLayer::doAlignItemsVerticallyWithPadding(float padding)
{
  float height = -padding;
  if (m_pChildren && m_pChildren->count() > 0)
  {
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
      CCNode* pChild = dynamic_cast<CCNode*>(pObject);
      if (pChild)
      {
        height += pChild->getContentSize().height * pChild->getScaleY() + padding;
      }
    }
  }
  
  float y = height / 2.0f;
  if (m_pChildren && m_pChildren->count() > 0)
  {
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
      CCNode* pChild = dynamic_cast<CCNode*>(pObject);
      if (pChild)
      {
        pChild->setPosition(ccp(0, y - pChild->getContentSize().height * pChild->getScaleY() / 2.0f));
        y -= pChild->getContentSize().height * pChild->getScaleY() + padding;
      }
    }
  }
}

void VirenBaseLayer::doAlignItemsHorizontally(void)
{
  this->doAlignItemsHorizontallyWithPadding(kDefaultVirenPadding);
}

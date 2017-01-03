//
//  ExpandedViewPanel.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 12/1/13.
//
//

#include "ExpandedViewPanel.h"
#include "news_app/homeUI/Global.h"

ExpandedViewPanel* ExpandedViewPanel::create(char* aBackgroundImage, char* aSmallTitle,
                          char* aMainMenuTitle, char* aNewsTitle,
                          char* aNewsSummary)
{
  ExpandedViewPanel* p = new ExpandedViewPanel(0, aBackgroundImage, aSmallTitle, aMainMenuTitle,
                                              aNewsTitle, aNewsSummary);
  if (p) {
    p->init();
    p->retain();
  }
  return p;
}

ExpandedViewPanel::ExpandedViewPanel(CCNode* parent, char* aBackgroundImage, char* aSmallTitle,
                                     char* aMainMenuTitle, char* aNewsTitle,
                                     char* aNewsSummary)
                  : m_pSpriteFixedBackgroundImage(0)
                  , m_pBackgroundImage(aBackgroundImage)
                  , m_pSmallTitle(aSmallTitle)
                  , m_pMainMenuTitle(aMainMenuTitle)
                  , m_pNewsTitle(aNewsTitle)
                  , m_pNewsSummary(aNewsSummary)
{
  
}

ExpandedViewPanel::~ExpandedViewPanel() {
  
}
/*
 Expanded view :
 
 +-------------------------------------+
 |   MENU TITLE                        |------> Background image = full view
 |                                     |
 |                                     |
 |   Title of news                     |
 |   News summary                      |
 |                                     |
 +-------------------------------------+
 
 */
bool ExpandedViewPanel::init() {
  if ( !CCNode::init() ) {
    return false;
  }
  
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  

  m_pSpriteFixedBackgroundImage = CCSprite::create("blue.png");
  int padding = winSize.width/25;
  float aX = (winSize.width - (2*padding)) / m_pSpriteFixedBackgroundImage->getContentSize().width;
  float aY = ((winSize.width/2)) / m_pSpriteFixedBackgroundImage->getContentSize().height;
  m_pSpriteFixedBackgroundImage->setScaleX(aX);
  m_pSpriteFixedBackgroundImage->setScaleY(aY);
  m_pSpriteFixedBackgroundImage->setAnchorPoint(ccp(0, 0));
  m_pSpriteFixedBackgroundImage->setPosition(ccp(padding/2, 0));
  addChild(m_pSpriteFixedBackgroundImage, 0);
  
  
  //
  //dynamc image
  //
  if (m_pBackgroundImage) {
    m_pBackgroundImage = "umbrella.png";
  }
  m_pSpriteBackgroundImage = CCSprite::create(m_pBackgroundImage);
  CCSize neededSize = m_pSpriteFixedBackgroundImage->getContentSize();
  CCSize imageSize = m_pSpriteBackgroundImage->getContentSize();
  
  aX = (neededSize.width - (2*padding)) / imageSize.width;
  aY = ((neededSize.width)) / imageSize.height;
  m_pSpriteBackgroundImage->setScaleX(aX);
  m_pSpriteBackgroundImage->setScaleY(aY);
  m_pSpriteBackgroundImage->setAnchorPoint(ccp(0, 0));
  m_pSpriteBackgroundImage->setPosition(ccp(padding/2, 0));
  addChild(m_pSpriteBackgroundImage);

//  //
//  //gradient layer
//  //
//  m_pGradientOverlay = CCLayerGradient::create(ccc4(255, 255, 255, 127), ccc4(0, 0, 0, 127));
//  m_pGradientOverlay->setContentSize(neededSize);
//  m_pSpriteBackgroundImage->setScaleX(aX);
//  m_pSpriteBackgroundImage->setScaleY(aY);
//  m_pSpriteBackgroundImage->setAnchorPoint(ccp(0, 0));
//  m_pSpriteBackgroundImage->setPosition(ccp(padding/2, 0));
//  m_pSpriteBackgroundImage->addChild(m_pGradientOverlay);
//  
  //
  //Main menu title (should be with white background)
  //
  m_pLabelMainMenuTitle = CCLabelTTF::create(m_pMainMenuTitle, DEFAULT_FONT,
                                              DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 0.65f );
  m_pLabelMainMenuTitle->setColor(ccBLUE); //ideally we want transparent
  m_pLabelMainMenuTitle->setAnchorPoint(ccp(0.0f, 0.0f));
  m_pLabelMainMenuTitle->setPosition(ccp(padding, padding*3));
  m_pSpriteBackgroundImage->addChild(m_pLabelMainMenuTitle);
  
  //
  //white background for main menu title
  //
  m_pSpriteMainMenuTitleBackground = CCLayerColor::create(ccc4(255, 255, 255, 255));
  //m_pSpriteBackgroundImage->addChild(m_pSpriteMainMenuTitleBackground);
  
  
  //
  //news title
  //
  m_pLabelNewsTitle = CCLabelTTF::create(m_pNewsTitle, DEFAULT_FONT,
                                             DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 0.55f );
  m_pLabelNewsTitle->setColor(ccWHITE); //ideally we want transparent
  m_pLabelNewsTitle->setAnchorPoint(ccp(0.0f, 0.0f));
  m_pLabelNewsTitle->setPosition(ccp(padding, padding));
  m_pSpriteBackgroundImage->addChild(m_pLabelNewsTitle);
  
  
  //
  //news title
  //
  m_pLabelNewsSummary = CCLabelTTF::create(m_pNewsSummary, DEFAULT_FONT,
                                         DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 0.45f );
  m_pLabelNewsSummary->setColor(ccWHITE); //ideally we want transparent
  m_pLabelNewsSummary->setAnchorPoint(ccp(0.0f, 0.0f));
  m_pLabelNewsSummary->setPosition(ccp(padding, 0));
  m_pSpriteBackgroundImage->addChild(m_pLabelNewsSummary);
  
  return true;

}



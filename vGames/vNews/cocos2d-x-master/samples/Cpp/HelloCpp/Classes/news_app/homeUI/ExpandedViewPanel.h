//
//  ExpandedViewPanel.h
//  HelloCpp
//
//  Created by Virendra Shakya on 12/1/13.
//
//

#ifndef __HelloCpp__ExpandedViewPanel__
#define __HelloCpp__ExpandedViewPanel__

#include "cocos2d.h"
#include "VirenBaseLayer.h"

USING_NS_CC;

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


class ExpandedViewPanel : public VirenBaseLayer //CCNode //CCLayer //VirenBaseLayer
{
public:
  ExpandedViewPanel(CCNode* parent, char* aBackgroundImage, char* aSmallTitle,
                    char* aMainMenuTitle, char* aNewsTitle,
                    char* aNewsSummary);
  static ExpandedViewPanel* create(char* aBackgroundImage, char* aSmallTitle,
                                   char* aMainMenuTitle, char* aNewsTitle,
                                   char* aNewsSummary);
  virtual ~ExpandedViewPanel();
  virtual bool init();
  
protected: /* in z-order from back to front */
  CCSprite* m_pSpriteFixedBackgroundImage;
  CCSprite* m_pSpriteBackgroundImage;
  CCLayerGradient* m_pGradientOverlay;
  CCLabelTTF *m_pLabelSmallTitle;
  CCLayerColor* m_pSpriteMainMenuTitleBackground;
  CCLabelTTF *m_pLabelMainMenuTitle; //which title menu user selected
  CCLabelTTF *m_pLabelNewsTitle;
  CCLabelTTF *m_pLabelNewsSummary;
  
  char* m_pBackgroundImage;
  char* m_pSmallTitle;
  char* m_pMainMenuTitle;
  char* m_pNewsTitle;
  char* m_pNewsSummary;
};

#endif /* defined(__HelloCpp__ExpandedViewPanel__) */

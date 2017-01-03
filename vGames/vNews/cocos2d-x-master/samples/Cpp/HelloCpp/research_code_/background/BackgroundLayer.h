//
//  BackgroundLayer.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__BackgroundLayer__
#define __TheAdventuresOfMira__BackgroundLayer__

#include "cocos2d.h"
#include "Constants.h"
#include "CCParallaxScrollNode.h"

class BackgroundLayer : public cocos2d::CCLayer
{
private:
    CCParallaxScrollNode *parallax;
    bool mAllowParallax;
  
public:
    
    virtual bool init();
    
    CREATE_FUNC(BackgroundLayer);
  
    void disableParallax();
  
    void hideWind();
    void showWind();
    
    void update(float dt);
};

#endif /* defined(__TheAdventuresOfMira__BackgroundLayer__) */

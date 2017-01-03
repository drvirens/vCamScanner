

#ifndef __TheAdventuresOfMira__GameOverLayer__
#define __TheAdventuresOfMira__GameOverLayer__

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public cocos2d::CCLayer
{
private:
    void createPlayAgainButton();
public:
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    void playAgainButtonTouched();
    void mainButtonTouched();
  
    static CCScene* scene();
  
    virtual void keyBackClicked();
};

#endif /* defined(__TheAdventuresOfMira__GameOverLayer__) */

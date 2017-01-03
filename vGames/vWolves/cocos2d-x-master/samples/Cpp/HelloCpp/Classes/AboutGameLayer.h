
#ifndef __Viren_Jumping_Line_Man__AboutGameLayer__
#define __Viren_Jumping_Line_Man__AboutGameLayer__

#include "cocos2d.h"

class AboutGameLayer : public cocos2d::CCLayer
{
private:
    void createBackButton();
public:
    CREATE_FUNC(AboutGameLayer);
    virtual bool init();
    void backButtonTouched();
  
    virtual void keyBackClicked();
};

#endif /* defined(__Viren_Jumping_Line_Man__AboutGameLayer__) */

//
//  PGElement.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-7-18.
//
//

/*
    游戏中所有元素的一个基类,主要为了实现多态
 */

#ifndef __PuzzleGame__PGElement__
#define __PuzzleGame__PGElement__

#include "cocos2d.h"

typedef enum ElementType{
    e_surface = -1,
    e_inside = 1,
}ElementType;

using namespace cocos2d;

class PGElement : public CCObject{
public:
    PGElement(){};
    ~PGElement(){};
    
    virtual void moveElement(float speedX,float speedY)=0;
    virtual CCPoint getElementPosition()=0;
private:
    CC_SYNTHESIZE(ElementType, e_Type, Type);
};

#endif /* defined(__PuzzleGame__PGElement__) */

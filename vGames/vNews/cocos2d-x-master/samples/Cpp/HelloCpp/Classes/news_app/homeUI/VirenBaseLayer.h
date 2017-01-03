//
//  VirenBaseLayer.h
//  HelloCpp
//
//  Created by Virendra Shakya on 11/30/13.
//
//

#ifndef __HelloCpp__VirenBaseLayer__
#define __HelloCpp__VirenBaseLayer__

#include "cocos2d.h"
USING_NS_CC;

const static int kDefaultVirenPadding =  5;

class VirenBaseLayer : public CCLayer {
 protected:
  void doAlignItemsHorizontallyWithPadding(float padding);
  void doAlignItemsVertically();
  void doAlignItemsVerticallyWithPadding(float padding);
  void doAlignItemsHorizontally(void);

};

#endif /* defined(__HelloCpp__VirenBaseLayer__) */

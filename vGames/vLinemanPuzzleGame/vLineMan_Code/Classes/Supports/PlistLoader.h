//
//  PlistLoader.h
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-19.
//
//

#ifndef __PuzzleGame__PlistLoader__
#define __PuzzleGame__PlistLoader__

#include "cocos2d.h"

using namespace cocos2d;

class CC_DLL PlistLoader : public CCObject{
public:
    virtual ~PlistLoader();
    //初始化plist文件
    static PlistLoader* initWithPlistFile(const char* fileName);
    //获得文件中的某个对象
    CCObject* getObjectFromFileKey(const char* key);
private:
    //用于存储Plist的每一行数据的字典
    CC_SYNTHESIZE(CCDictionary*, plistDir_, Dictionary);
};

#endif /* defined(__PuzzleGame__PlistLoader__) */

//
//  PlistLoader.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-19.
//
//

#include "PlistLoader.h"

using namespace cocos2d;

PlistLoader::~PlistLoader(){
    
}

PlistLoader* PlistLoader::initWithPlistFile(const char *fileName){
    PlistLoader* file=new PlistLoader();
    file->autorelease();//自动释放
  
    // viren+
    //const char* plistPath=CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
    std::string tmp = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName); //viren
    const char* plistPath= tmp.c_str();
    //viren-
  
    CCDictionary *plistDir=CCDictionary::createWithContentsOfFileThreadSafe(plistPath);
    file->setDictionary(plistDir);
    
    return file;
}

CCObject* PlistLoader::getObjectFromFileKey(const char *key){
    CCAssert(plistDir_!=NULL, "plist File is null!");
    CCObject *plistKey=dynamic_cast<CCObject*>(plistDir_->objectForKey(key));
    return plistKey;
}
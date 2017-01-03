//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "ScreenHelper.h"

using namespace cocos2d;

bool ScreenHelper::isCinematic = false;

float RandomFloat(float min, float max)
{
    float number = CCRANDOM_0_1();
    number *= (max-min);
    number += min;
    return number;
}
int RandomInt(int min, int max)
{
    float number = CCRANDOM_0_1();
    number *= (float)(max-min);
    number += (float)min;
    return (int)number;
}


CCPoint ScreenHelper::m_Anchors[ANCHOR_MAX];
float ScreenHelper::m_TextureScale = 1.0f;
float ScreenHelper::m_TextureScaleX;
float ScreenHelper::m_TextureScaleY;
float ScreenHelper::m_ScaleX;
float ScreenHelper::m_ScaleY;
float ScreenHelper::m_CameraZoom = 1.0f;

const float ScreenHelper::getPTMScaled()
{
    return 16.0f * (m_TextureScale);
}
void ScreenHelper::setCameraZoom(float zoom,float smooth)
{
    if(smooth)
    {
        const float maxDelta = 0.002f;
        if(zoom < m_CameraZoom)
        {
            m_CameraZoom = MAX(zoom,(m_CameraZoom-maxDelta));
        }
        else if(zoom > m_CameraZoom)
        {
            m_CameraZoom = MIN(zoom,(m_CameraZoom+maxDelta));
        }
    }
    else
    {
        m_CameraZoom = zoom;
    }
}
void ScreenHelper::Init()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    if(1 /*different sized assets affect this*/)
    {
        m_ScaleX = s.width/480.0f;
        m_ScaleY = s.height/320.0f;
        
        m_TextureScaleX = m_ScaleX;
        m_TextureScaleY = m_ScaleY;
    }
    if(m_TextureScaleX > m_TextureScaleY)
        m_TextureScale = m_TextureScaleY;
    else
        m_TextureScale = m_TextureScaleX;

    m_Anchors[ANCHOR_LEFT] = ccp(0.0f,s.height/2.0f);
    m_Anchors[ANCHOR_CENTER] = ccp(s.width/2.0f,s.height/2.0f);
    m_Anchors[ANCHOR_RIGHT] = ccp(s.width,s.height/2.0f);

    
    m_Anchors[ANCHOR_TOP_LEFT] = ccp(0.0f,s.height);
    m_Anchors[ANCHOR_TOP_CENTER] = ccp(s.width/2.0f,s.height);
    m_Anchors[ANCHOR_TOP_RIGHT] = ccp(s.width,s.height);

    m_Anchors[ANCHOR_BOTTOM_LEFT] = ccp(0.0f,0.0f);
    m_Anchors[ANCHOR_BOTTOM_CENTER] = ccp(s.width/2.0f,0.0f);
    m_Anchors[ANCHOR_BOTTOM_RIGHT] = ccp(s.width,0.0f);
}
CCPoint ScreenHelper::getAnchorPointPlusOffset(ANCHOR anchorID,float x, float y)
{
    if(isCinematic)
    {
        float newX = m_Anchors[anchorID].x+m_TextureScale*x;
        float newY = m_Anchors[anchorID].y+m_TextureScale*y;
        return CCPointMake(newX,newY);
    }
    else
    {
        float newX = m_Anchors[anchorID].x+m_ScaleX*x;
        float newY = m_Anchors[anchorID].y+m_ScaleY*y;
        return CCPointMake(newX,newY);
    }
}

bool ScreenHelper::AddOBBSpriteToCache(const char *name, const char *plistName)
{
    unsigned long pSize;
    unsigned char * pData = 0;
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) && !defined KINDLE__
//    std::vector<std::string> paths;
//    paths.push_back("/mnt/sdcard/Android/obb");
//    CCFileUtils::sharedFileUtils()->setSearchPaths(paths);
//#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("main.1.com.LudicrousGames.MonkeyDroid.zip");
    //CCLOG(fullPath.c_str());
    pData = CCFileUtils::sharedFileUtils()->getFileDataFromZip(fullPath.c_str(), name, &pSize);
    //CCLOG("%d",pData);
    if(pData)
    {
        CCImage* img = new CCImage();
        img->initWithImageData(pData, pSize);
        CCTextureCache::sharedTextureCache()->addUIImage(img, CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(name, plistName));
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName);
        return true;
    }
    return false;
 
#else
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName,name);
#endif
}
cocos2d::CCSprite* CreateOBBSprite(const char *name)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) && !defined KINDLE__
//    std::vector<std::string> paths;
//    paths.push_back("/mnt/sdcard/Android/obb");
//    CCFileUtils::sharedFileUtils()->setSearchPaths(paths);
//#endif
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("main.1.com.LudicrousGames.MonkeyDroid.zip");
    unsigned long pSize;
    unsigned char * pData = 0;
    pData = CCFileUtils::sharedFileUtils()->getFileDataFromZip(fullPath.c_str(), name, &pSize);
    if(pData)
    {
        CCImage* img = new CCImage();
        img->initWithImageData(pData, pSize);
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addUIImage(img, name);
        CCSprite* sprite = CCSprite::createWithTexture(texture);
        return sprite;
    }
    else
    {
        return NULL;
    }

}

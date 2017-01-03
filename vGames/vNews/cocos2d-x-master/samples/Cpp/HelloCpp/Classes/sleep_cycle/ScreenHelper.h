//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __SCREEN_HELPER_H__
#define __SCREEN_HELPER_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"

float RandomFloat(float min, float max);
int RandomInt(int min, int max);

class ScreenHelper
{
public:
    enum ANCHOR
    {
        ANCHOR_TOP_LEFT = 0,
        ANCHOR_TOP_CENTER = 1,
        ANCHOR_TOP_RIGHT = 2,
        ANCHOR_LEFT = 3,
        ANCHOR_CENTER = 4,
        ANCHOR_RIGHT = 5,
        ANCHOR_BOTTOM_LEFT = 6,
        ANCHOR_BOTTOM_CENTER = 7,
        ANCHOR_BOTTOM_RIGHT = 8,
        ANCHOR_MAX = 9
    };
    static void Init();
    static const cocos2d::CCPoint &getAnchorPoint(ANCHOR anchorID){return m_Anchors[anchorID];}
    static cocos2d::CCPoint getAnchorPointPlusOffset(ANCHOR anchorID,float x, float y);
    static const float getTextureScale(){return m_TextureScale;}
    static const float getTextureScaleX(){return m_TextureScaleX;}
    static const float getTextureScaleY(){return m_TextureScaleY;}
    static const float getScaleX(){return m_ScaleX;}
    static const float getScaleY(){return m_ScaleY;}
    static const float getPTMScaled();
    static void setCameraZoom(float zoom,float smooth = true);
    static float getCameraZoom(){return m_CameraZoom;}
    static bool isCinematic;
    static bool AddOBBSpriteToCache(const char *name, const char *plistName);
    static cocos2d::CCSprite* CreateOBBSprite(const char *name);
protected:
    static cocos2d::CCPoint m_Anchors[ANCHOR_MAX];
    static float m_TextureScale;
    static float m_TextureScaleX;
    static float m_TextureScaleY;
    static float m_ScaleX;
    static float m_ScaleY;
    static float m_CameraZoom;
};

#define PTM_RATIO (ScreenHelper::getPTMScaled())


#endif // __SCREEN_HELPER_H__

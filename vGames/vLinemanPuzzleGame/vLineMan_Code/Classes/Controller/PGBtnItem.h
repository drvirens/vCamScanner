//
//  Bz_btnItem.h
//  Bz_gameControl
//
//  Created by Binz_- on 13-6-26.
//
//

#ifndef __Bz_gameControl__Bz_btnItem__
#define __Bz_gameControl__Bz_btnItem__


#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;
class Bz_btnItem:public CCSprite{
    
private:
    bool m_bIsSelected;//被选择状态
    /******
     小图
     ******/
    CCTexture2D *m_texNormal;//选择前的纹理
    CCTexture2D *m_texSelected;//选择后的纹理
public:
    
    inline bool getIsSelect(){return m_bIsSelected;}
    inline void setIsSelected(bool isSelected){m_bIsSelected = isSelected;}
    
    inline CCTexture2D* getNormalTex(){return m_texNormal;}
    inline CCTexture2D* getSelectedTex(){return m_texSelected;}
    
    inline void setNormalTex(CCTexture2D* tex){m_texNormal = tex;}
    inline void setSelectedTex(CCTexture2D* tex){m_texSelected = tex;}
    
    inline void setNormalTex(const char* file){m_texNormal = CCTextureCache::sharedTextureCache()->addImage(file);}
    inline void setSelectedTex(const char* file){m_texSelected = CCTextureCache::sharedTextureCache()->addImage(file);}
    
public:
    ~Bz_btnItem();
    bool init();
    bool initWithNormalTexAndSelectedTex(CCTexture2D *normal,CCTexture2D *selected);
    
    static Bz_btnItem* createWithNormalTexAndSelectedTex(CCTexture2D *normal,CCTexture2D *selected);
    
    
    static Bz_btnItem* createWithNormalFileAndSelectedFile(const char* normal,const char* selected);
    bool initWithNormalFileAndSelectedFile(const char* normal,const char* selected);
    
    
    void showButtonTexture(bool isSelected);
    
};


#endif /* defined(__Bz_gameControl__Bz_btnItem__) */

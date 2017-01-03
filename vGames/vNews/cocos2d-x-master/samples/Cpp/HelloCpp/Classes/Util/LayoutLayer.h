/*
 *   FILE: LayoutLayer.h
 * AUTHOR: Michael David Plotz
 *   DATE: Sun Jul 14 12:41:38 PDT 2013
 */

#ifndef __CCNODEUTIL_LAYOUTLAYER_H__
#define __CCNODEUTIL_LAYOUTLAYER_H__

#include "cocos2d.h"
#include "CCNodeUtil.h"

#define hll() (LayoutLayer::create()->setLayoutBehavior(LAYOUT_HORIZONTAL))
#define vll() (LayoutLayer::create()->setLayoutBehavior(LAYOUT_VERTICAL))
#define oll() (LayoutLayer::create()->setLayoutBehavior(LAYOUT_OVER))

USING_NS_CC;
using namespace std;

NS_CC_UTIL_BEGIN

enum LayoutBehaviorType
{
    LAYOUT_NONE,
    LAYOUT_HORIZONTAL,
    LAYOUT_VERTICAL,
    LAYOUT_OVER,
};

enum LayoutSizingPolicy
{
    LAYOUT_SIZING_NONE,
    LAYOUT_SIZING_EQUAL,
};

class FlexNode;
class HLayoutBehavior;
class LayoutBehavior;
class OverLayoutBehavior;
class VLayoutBehavior;

class LayoutLayer : public CCLayer, public CCRGBAProtocol
{
public:
    static LayoutLayer *create();

    LayoutLayer();
    virtual ~LayoutLayer();

    bool initLayoutLayer();

    Alignment getAlignment() const { return m_alignment; }
    LayoutLayer *setAlignment(Alignment value) { m_alignment = value; return this; }

    CCSize getMinSize();
    LayoutLayer *setMinSize(const CCSize& value);

    const CCSize& getPadding() const { return m_padding; }
    LayoutLayer *setPadding(const CCSize& value) { m_padding = value; return this; }

    const CCSize& getMargin() const { return m_margin; }
    LayoutLayer *setMargin(const CCSize& value) { m_margin = value; return this; }

    LayoutLayer *setLayoutBehavior(LayoutBehaviorType value);
    LayoutLayer *setWidthSizingPolicy(LayoutSizingPolicy value) { m_widthSizingPolicy = value; return this; }
    LayoutLayer *setHeightSizingPolicy(LayoutSizingPolicy value) { m_heightSizingPolicy = value; return this; }

    LayoutLayer *setFrozen(bool value) { m_frozen = value; return this; }
    bool getFrozen() { return m_frozen; }

    LayoutLayer *fitToContents();
    LayoutLayer *fitWidthToContents();
    LayoutLayer *fitHeightToContents();
    LayoutLayer *clear();

    LayoutLayer *doLayout(CCSize minSize = CCSizeZero);

    const CCNode *getBackground() const { return m_background; }
    LayoutLayer *setBackground(CCNode *newBackground);
    NodeList& getChildrenList() { return m_children; }
    list<FlexNode *>& getFlexNodes() { return m_flexNodes; }

    // ========================================================================== //
    // inherited from CCNode                                                      //

    virtual void setContentSize(const CCSize& size);
    virtual void addChild(CCNode *child);
    virtual void addChild(CCNode *child, int zOrder);
    virtual void addChild(CCNode *child, int zOrder, int tag);
    virtual void removeChild(CCNode *child, bool cleanup);
    virtual void removeChild(CCNode *child) { this->removeChild(child, true); }

    // ========================================================================== //
    // inherited from CCRGBAProtocol                                              //

//    virtual void setColor(const ccColor3B& value);
//    virtual const ccColor3B& getColor() { return m_color; }
//    virtual GLubyte getOpacity(void) { return m_opacity; }
//    virtual void setOpacity(GLubyte value);
//    virtual void setOpacityModifyRGB(bool value);
//    virtual bool isOpacityModifyRGB(void) { return m_opacityModifyRGB; }
  
    //viren+
  
  cocos2d::CCArray* getRGBAChildren() {
    return getChildren();
  }

  cocos2d::CCNode* getRGBAParent() ;
  
  /**
   * Changes the color with R,G,B bytes
   *
   * @param color Example: ccc3(255,100,0) means R=255, G=100, B=0
   */
  virtual void setColor(const ccColor3B& color) ;
  
  /**
   * Returns color that is currently used.
   *
   * @return The ccColor3B contains R,G,B bytes.
   */
  virtual const ccColor3B& getColor(void)
     { return m_color; }
  
  /**
   * Returns the displayed color.
   *
   * @return The ccColor3B contains R,G,B bytes.
   */
  virtual const ccColor3B& getDisplayedColor(void)
      { return _displayedColor; }
  
  /**
   * Returns the displayed opacity.
   *
   * @return  The opacity of sprite, from 0 ~ 255
   */
  virtual GLubyte getDisplayedOpacity(void)
      { return _displayedOpacity; }
  /**
   * Returns the opacity.
   *
   * The opacity which indicates how transparent or opaque this node is.
   * 0 indicates fully transparent and 255 is fully opaque.
   *
   * @return  The opacity of sprite, from 0 ~ 255
   */
  virtual GLubyte getOpacity(void)
    { return m_opacity; }
  
  /**
   * Changes the opacity.
   *
   * @param   value   Goes from 0 to 255, where 255 means fully opaque and 0 means fully transparent.
   */
  virtual void setOpacity(GLubyte opacity);
  
    // optional
  
  /**
   * Changes the OpacityModifyRGB property.
   * If thie property is set to true, then the rendered color will be affected by opacity.
   * Normally, r = r * opacity/255, g = g * opacity/255, b = b * opacity/255.
   *
   * @param   bValue  true then the opacity will be applied as: glColor(R,G,B,opacity);
   *                  false then the opacity will be applied as: glColor(opacity, opacity, opacity, opacity);
   */
  virtual void setOpacityModifyRGB(bool bValue) ;
  
  /**
   * Returns whether or not the opacity will be applied using glColor(R,G,B,opacity)
   * or glColor(opacity, opacity, opacity, opacity)
   *
   * @return  Returns opacity modify flag.
   */
  virtual bool isOpacityModifyRGB(void)
    { return m_opacityModifyRGB; }
  
  /**
   *  whether or not color should be propagated to its children.
   */
  virtual bool isCascadeColorEnabled(void)
    { return _cascadeOpacityEnabled; }
  
  virtual void setCascadeColorEnabled(bool cascadeColorEnabled)
    { _cascadeColorEnabled = cascadeColorEnabled; }
  
  /**
   *  recursive method that updates display color
   */
  virtual void updateDisplayedColor(const ccColor3B& parentColor) {
		_displayedColor.r = m_color.r * parentColor.r/255.0;
		_displayedColor.g = m_color.g * parentColor.g/255.0;
		_displayedColor.b = m_color.b * parentColor.b/255.0;
		
		if (_cascadeColorEnabled)
		{
			CCObject *obj = NULL;
			CCARRAY_FOREACH(getRGBAChildren(), obj)
			{
				CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(obj);
				if (item)
				{
					item->updateDisplayedColor(_displayedColor);
				}
			}
		}
	}

  
  /**
   *  whether or not opacity should be propagated to its children.
   */
  virtual bool isCascadeOpacityEnabled(void)
  { return _cascadeOpacityEnabled; }
  virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
    { _cascadeOpacityEnabled = cascadeOpacityEnabled; }
  
  /**
   *  recursive method that updates the displayed opacity.
   */
  virtual void updateDisplayedOpacity(GLubyte parentOpacity)  {
		_displayedOpacity = m_opacity * parentOpacity/255.0;
		
		if (_cascadeOpacityEnabled)
		{
			CCObject* pObj;
			CCARRAY_FOREACH(getRGBAChildren(), pObj)
			{
				CCRGBAProtocol* item = dynamic_cast<CCRGBAProtocol*>(pObj);
				if (item)
				{
					item->updateDisplayedOpacity(_displayedOpacity);
				}
			}
		}
	}

  //viren-

protected:
private:
    LayoutLayer(const LayoutLayer& orig);
    LayoutLayer& operator=(const LayoutLayer& rhs);

    void fitChildrenSizes(bool fitWidth, bool fitHeight);
    CCSize getSizeOfLargestChild();

    LayoutBehavior *m_layoutBehavior;

    Alignment m_alignment;
    CCSize m_minSize;
    CCSize m_padding;
    CCSize m_margin;
    LayoutSizingPolicy m_widthSizingPolicy;
    LayoutSizingPolicy m_heightSizingPolicy;

    bool m_frozen;

    CCNode *m_background;
    NodeList m_children;
    list<FlexNode *> m_flexNodes;

    ccColor3B m_color;
    GLubyte m_opacity;
    bool m_opacityModifyRGB;
  
    //viren+
  GLubyte		_displayedOpacity;
	cocos2d::ccColor3B	_displayedColor;
	bool		_cascadeOpacityEnabled, _cascadeColorEnabled;
  //viren-

};

class LayoutBehavior
{
public:
    static LayoutBehavior* getLayoutBehavior(LayoutBehaviorType type);

    LayoutBehavior();
    virtual ~LayoutBehavior();

    virtual void doLayout(LayoutLayer *layer) { }
    virtual CCSize getMinSize(LayoutLayer *layer) { return CCSizeZero; }

protected:
private:
    LayoutBehavior(const LayoutBehavior& orig);
    LayoutBehavior& operator=(const LayoutBehavior& rhs);
};

class HLayoutBehavior : public LayoutBehavior
{
public:
    HLayoutBehavior();
    virtual ~HLayoutBehavior();

    virtual void doLayout(LayoutLayer *layer);
    virtual CCSize getMinSize(LayoutLayer *layer);

protected:
private:
    HLayoutBehavior(const HLayoutBehavior& orig);
    HLayoutBehavior& operator=(const HLayoutBehavior& rhs);
};

class VLayoutBehavior : public LayoutBehavior
{
public:
    VLayoutBehavior();
    virtual ~VLayoutBehavior();

    virtual void doLayout(LayoutLayer *layer);
    virtual CCSize getMinSize(LayoutLayer *layer);

protected:
private:
    VLayoutBehavior(const VLayoutBehavior& orig);
    VLayoutBehavior& operator=(const VLayoutBehavior& rhs);
};

class OverLayoutBehavior : public LayoutBehavior
{
public:
    OverLayoutBehavior();
    virtual ~OverLayoutBehavior();

    virtual void doLayout(LayoutLayer *layer);
    virtual CCSize getMinSize(LayoutLayer *layer);

protected:
private:
    OverLayoutBehavior(const OverLayoutBehavior& orig);
    OverLayoutBehavior& operator=(const OverLayoutBehavior& rhs);
};

NS_CC_UTIL_END

#endif /* __CCNODEUTIL_LAYOUTLAYER_H__ */


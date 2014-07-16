
/*
 *
 *  Created by wangbin
 *
 */

#ifndef MT_B_LJCCControlButton_h
#define MT_B_LJCCControlButton_h

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
    
class CCButton : public ControlButton
{        
public:
    CCButton();
    virtual ~CCButton();
    static CCButton* create(Size btnSize, bool bSwall=true);
    static CCButton* create(Node* label, Scale9Sprite* backgroundSprite);
    static CCButton* create(std::string title, const char * fontName, float fontSize, bool bSwall=true);
    static CCButton* create(Scale9Sprite* sprite);
    static CCButton* create(const char* fileName,bool bSwall=true);
    static CCButton* create(const char* fileName,const char* labNameStr);
    
    static CCButton* create(const char* fileName,Color3B pColor);
    static CCButton* create(const char* fileName,const char* titleImageName,Color3B pColor);
    
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void needsLayout();
    virtual void setBackgroundSpriteForState(Scale9Sprite* sprite, State state);
    virtual void setEnabled(bool enabled);
    virtual void setSelected(bool enabled);
    virtual void setHighlighted(bool enabled);
    void         setAreaOutResponse(bool bValue){m_bResponseArea=bValue;}
    
    void setTitleImage(const char* pszPngname);
    void setTitleImage(Sprite* pSprite);
    void setTitleImage(const char* pszPngname, float scale);
private:
    float           m_dragDistancePercent;
    Point           m_beginPoint;
    bool            m_bResponseArea;
};

#endif

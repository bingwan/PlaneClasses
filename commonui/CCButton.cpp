

/*
 *
 *  Created by wangbin
 *
 */

#include <iostream>
#include "CCButton.h"
#include "CommonDef.h"
#include "UserData.h"

CCButton::CCButton():
m_dragDistancePercent(0.25),
m_beginPoint(Point(0,0)),
m_bResponseArea(false)
{
    setAdjustBackgroundImage(false);
}
//=============================================================
//=============================================================
CCButton::~CCButton()
{
} 
//=============================================================
//=============================================================
bool CCButton::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    
    if (!isVisible()) // 父视图改变visible 不影响孩子的变量   //不可见不处理touch
    { 
        return false;
    }
    Node* fatherNode = getParent();
    if(!fatherNode)
        return false;
    Point touchPointInWorld = pTouch->getLocation();
    Rect  selfRect = boundingBox();
    Point selfOriginInWorld = fatherNode->convertToWorldSpace(selfRect.origin);
    Rect  selfRectInWorld = Rect(selfOriginInWorld.x,selfOriginInWorld.y,selfRect.size.width,selfRect.size.height);
    if(selfRectInWorld.containsPoint(touchPointInWorld) == false)
    {
        return false;
    }
    for (Node *c = this->_parent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false) //若父亲有不可见的则不处理touch
        {
            return false;
        }
        
        if (!m_bResponseArea)
        {
            Rect  rect = c->boundingBox();
            Node* parentNode = c->getParent();
            if(parentNode)
            {
                Point originInWorld = parentNode->convertToWorldSpace(rect.origin);
                
                Rect rectInWorld = Rect(originInWorld.x,originInWorld.y,rect.size.width,rect.size.height);
                if(rectInWorld.containsPoint(touchPointInWorld) == false)
                {
                    return false;  // 不在父视图区域内 按钮不响应
                }
            }
        }

    }
    if (!isTouchInside(pTouch) || !isEnabled())
    {
        return false;
    }
    _isPushed = true;
    setHighlighted(true);
    sendActionsForControlEvents(Control::EventType::TOUCH_DOWN);
    
    m_beginPoint = pTouch->getLocation();
    return true;
}
//=============================================================
//=============================================================
void CCButton::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    Point movePoint = pTouch->getLocation();
    float distanceX = fabsf(movePoint.x-m_beginPoint.x);
    float distanceY = fabsf(movePoint.y-m_beginPoint.y);
    Size contentSize = getContentSize();
    if(distanceX >= contentSize.width*m_dragDistancePercent || distanceY >= contentSize.height*m_dragDistancePercent)
    {
        if(isHighlighted())
        {
            _state = Control::State::NORMAL;
            _isPushed = false;
            setHighlighted(false);
        }
        return;
    }
    
    ControlButton::onTouchMoved(pTouch, pEvent);
}
//=============================================================
//=============================================================

void CCButton::onTouchEnded(Touch *pTouch, Event *pEvent)
{    
    _state =  Control::State::NORMAL;
    _isPushed = false;
    bool oldHigh = isHighlighted();
    setHighlighted(false);
    
    if(oldHigh)
    {
        if (isTouchInside(pTouch))
        {
            sendActionsForControlEvents(Control::EventType::TOUCH_UP_INSIDE);
            
            //music
            //UserData::shareUserData()->playEffect("btn.mp3");
        }
        else
        {
            sendActionsForControlEvents(Control::EventType::TOUCH_UP_INSIDE);
        }
    }
    
   
    
}
//=============================================================
//=============================================================
CCButton* CCButton::create(Size btnSize, bool bSwall)
{
    CCButton *pRet = new CCButton();
    pRet->setSwallowsTouches(bSwall);
    pRet->init();
    pRet->setContentSize(btnSize);
    pRet->autorelease();
    return pRet;
}
//=============================================================
//=============================================================
CCButton* CCButton::create(Node* label, Scale9Sprite* backgroundSprite)
{
    CCButton *pRet = new CCButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    pRet->setAdjustBackgroundImage(false);
    return pRet;
}
//=============================================================
//=============================================================
CCButton* CCButton::create(std::string title, const char * fontName, float fontSize, bool bSwall)
{
    CCButton *pRet = new CCButton();
    pRet->setSwallowsTouches(bSwall);
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    pRet->setAdjustBackgroundImage(false);
    return pRet;
}
//=============================================================
//=============================================================
CCButton* CCButton::create(Scale9Sprite* sprite)
{
    CCButton *pRet = new CCButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    pRet->setAdjustBackgroundImage(false);
    return pRet;
}

CCButton* CCButton::create(const char* fileName,Color3B pColor)
{
    Scale9Sprite *sprite=Scale9Sprite::create(fileName);
    CCButton *pRet = new CCButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    pRet->setAdjustBackgroundImage(false);
    Scale9Sprite *pColorSpr=Scale9Sprite::create(fileName);
    pColorSpr->setColor(Color3B::GRAY);
    pRet->setZoomOnTouchDown(false);
    pRet->setBackgroundSpriteForState(pColorSpr, Control::State::HIGH_LIGHTED);
    return pRet;
}

CCButton* CCButton::create(const char* fileName,const char* titleImageName,Color3B pColor)
{
    Scale9Sprite *sprite=Scale9Sprite::create(fileName);
    CCButton *pRet = new CCButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    pRet->setAdjustBackgroundImage(false);
    Scale9Sprite *pColorSpr=Scale9Sprite::create(fileName);
    pColorSpr->setColor(Color3B::GRAY);
    pRet->setZoomOnTouchDown(false);
    pRet->setBackgroundSpriteForState(pColorSpr, Control::State::HIGH_LIGHTED);
    Size butSize=pRet->getContentSize();
    Sprite *pImageSpr=CCSprite::create(titleImageName);
    pImageSpr->setPosition(Point(butSize.width*0.5,butSize.height*0.5));
    pRet->addChild(pImageSpr,10000);
    return pRet;
}
//=============================================================
//=============================================================

CCButton* CCButton::create(const char* fileName,bool bSwall)
{
    if(!fileName)
        return NULL;
    Texture2D* pTexture = TextureCache::getInstance()->addImage(fileName);
    if(!pTexture)
    {
        fileName = "Icon-72.png";
    }
    Scale9Sprite *sprite = Scale9Sprite::create(fileName);
    CCButton *pRet = new CCButton();
    pRet->setSwallowsTouches(bSwall);
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    pRet->setAdjustBackgroundImage(false);
    return pRet;
}
//=============================================================
//=============================================================

CCButton* CCButton::create(const char* fileName,const char* labNameStr)
{
//    CCScale9Sprite *sprite=CCScale9Sprite::create(fileName);
//    CCButton *pRet = new CCButton();
//    pRet->initWithBackgroundSprite(sprite);
//    pRet->autorelease();
//    pRet->setAdjustBackgroundImage(false);
//    CCLabelTTF *pShowLab = CCLabelTTF::create(labNameStr, "", TIPS_BUTTON_SIZE);
//    CCSize butSize=pRet->getContentSize();
//    pRet->addChild(pShowLab);
//    pShowLab->setPosition(ccp(butSize.width*0.5,butSize.height*0.5));
    //return pRet;
}
//=============================================================
//=============================================================
void CCButton::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    if(enabled)
    {
        _state = Control::State::NORMAL;
    }
    else
    {
        _state = Control::State::DISABLED;
    }
    needsLayout();
}
//=============================================================
//=============================================================
void CCButton::setSelected(bool enabled)
{
    Control::setSelected(enabled);
    if(enabled)
    {
        _state = Control::State::SELECTED;
    }
    else
    {
        _state = Control::State::NORMAL;
    }
    needsLayout();
}
//=============================================================
//=============================================================
void CCButton::setHighlighted(bool enabled)
{
    ControlButton::setHighlighted(enabled);
    
    if(enabled)
    {
        _state = Control::State::HIGH_LIGHTED;
    }
    else
    {
        _state = Control::State::NORMAL;
    }

    needsLayout();
    
//    Scale9Sprite* pBgSprite = getBackgroundSpriteForState(_state);
//    if(!pBgSprite)
//        return;
//    Size bgSize = pBgSprite->getContentSize();
//    Node* pNode = getChildByTag(998);
//    if(pNode)
//    {
//        pNode->setPosition(Point(bgSize.width*0.5,bgSize.height*0.5));
//    }
    
}
//=============================================================
//=============================================================
void CCButton::needsLayout()
{
   ControlButton::needsLayout();
}
//=============================================================
//=============================================================
void CCButton::setBackgroundSpriteForState(Scale9Sprite* sprite, Control::State state)
{
    ControlButton::setBackgroundSpriteForState(sprite, state);
}
//=============================================================
//=============================================================

void CCButton::setTitleImage(const char* pszPngname)
{
    Size contentSize = getContentSize();
    
    if(pszPngname == NULL)
    {
        return;
    }
    removeChildByTag(998);
    
    Sprite* ptitleImage = Sprite::create(pszPngname);
    ptitleImage->setPosition(Point(contentSize.width*0.5,contentSize.height*0.5));
    ptitleImage->setTag(998);
    addChild(ptitleImage);

}
void CCButton::setTitleImage(Sprite* pSprite)
{
    Size contentSize = getContentSize();
    
    if(pSprite == NULL)
    {
        return;
    }
    removeChildByTag(998);
    
    pSprite->setPosition(Point(contentSize.width*0.5,contentSize.height*0.5));
    pSprite->setTag(998);
    addChild(pSprite);
    
}

void CCButton::setTitleImage(const char *pszPngname, float fScale)
{
    Size contentSize = getContentSize();
    
    if(pszPngname == NULL)
    {
        return;
    }
    removeChildByTag(998);
    
    Sprite* ptitleImage = Sprite::create(pszPngname);
    ptitleImage->setPosition(Point(contentSize.width*0.5,contentSize.height*0.5));
    ptitleImage->setTag(998);
    ptitleImage->setScale(fScale, fScale);
    addChild(ptitleImage);
}









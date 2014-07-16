
/*
 *
 *  Created by wangbin
 *
 */


#include "BWCCMenuItemImage.h"
#include "UserData.h"


BWCCMenuItemImage::BWCCMenuItemImage():
m_imageAnchorPoint(Point(0.5,0.5)),
m_target(NULL),
m_currentSelectorState(ISSE_UNKNOWN),
m_beginSelector(NULL),
m_moveSelector(NULL),
m_titleImageNor(NULL),
m_titleImageSel(NULL),
m_titleImageDis(NULL),
m_titleLabelNor(NULL),
m_titleLabelSel(NULL),
m_titleLabelDis(NULL),
m_selectedAble(true),
m_unselectedAble(true)
{
}

BWCCMenuItemImage::~BWCCMenuItemImage()
{
}

BWCCMenuItemImage* BWCCMenuItemImage::create(CCLabelStroke *titleLabelNor,CCLabelStroke *titleLabelSel, CCLabelStroke *titleLabelDis,Object* target, SEL_MenuHandler selector)
{
    BWCCMenuItemImage* item =  new BWCCMenuItemImage();
    item->autorelease();
    item->initWithNormalSprite(titleLabelNor,titleLabelSel,titleLabelDis,target,selector);
    return item;
}

BWCCMenuItemImage* BWCCMenuItemImage::create(Sprite* normalImage, Sprite *selectedImage,Sprite *disabledImage, Object* target, SEL_MenuHandler selector)
{
    BWCCMenuItemImage* item =  new BWCCMenuItemImage();
    item->autorelease();
    item->initWithNormalSprite(normalImage, selectedImage, disabledImage, target, selector);
    return item;
}


BWCCMenuItemImage* BWCCMenuItemImage::create(const char *normalImage, const char *selectedImage, const char *disabledImage, Object* target, SEL_MenuHandler selector)
{
    BWCCMenuItemImage* pBtn =  new BWCCMenuItemImage();
    pBtn->autorelease();
    pBtn->initWithNormalImage(normalImage, selectedImage, disabledImage, target, selector);
    
    Node *pNormalSprite = NULL;
    Node *pSelectedSprite = NULL;
    Node *pDisabledSprite = NULL;
    
    if (normalImage)
    {
        pNormalSprite = Sprite::create(normalImage);
    }
    
    if (selectedImage)
    {
        pSelectedSprite = Sprite::create(selectedImage);
    }
    
    if(disabledImage)
    {
        pDisabledSprite = Sprite::create(disabledImage);
    }
        
    pBtn->setNormalImage(pNormalSprite);
    pBtn->setSelectedImage(pSelectedSprite);
    pBtn->setDisabledImage(pDisabledSprite);
    return  pBtn;
}

// title label
void BWCCMenuItemImage::setTitleNormalLabel(CCLabelStroke* var)
{
    if(var)
    {
        addChild(var, CIZ_TITLE_LABEL);
        var->setVisible(true);
    }
    if(m_titleLabelNor)
    {
        m_titleLabelNor->removeFromParentAndCleanup(true);
    }
    m_titleLabelNor = var;
}

void BWCCMenuItemImage::setTitleSelectedLabel(CCLabelStroke* var)
{
    if(var)
    {
        addChild(var,CIZ_TITLE_LABEL);
        var->setVisible(false);
    }
    if(m_titleLabelSel)
    {
        m_titleLabelSel->removeFromParentAndCleanup(true);
    }
    m_titleLabelSel = var;
}

void BWCCMenuItemImage::setTitleDisabledLabel(CCLabelStroke* var)
{
    if(var)
    {
        addChild(var,CIZ_TITLE_LABEL);
        var->setVisible(false);
    }
    
    if(m_titleLabelDis)
    {
        m_titleLabelDis->removeFromParentAndCleanup(true);
    }
    m_titleLabelDis = var;
}

// title image
void BWCCMenuItemImage::setTitleNormalImage(Sprite* var)
{
    if(var)
    {
        var->setAnchorPoint(Point(0.5,0.5));
        var->setPosition(Point(getContentSize().width/2,getContentSize().height/2));
        addChild(var,CIZ_TITLE_IMAGE);
        var->setVisible(true);
    }
    if(m_titleImageNor)
    {
        m_titleImageNor->removeFromParentAndCleanup(true);
    }
    m_titleImageNor = var;
}

void BWCCMenuItemImage::setTitleSelectedImage(Sprite* var)
{
    if(var)
    {
        var->setAnchorPoint(Point(0.5,0.5));
        var->setPosition(Point(getContentSize().width/2,getContentSize().height/2));
        addChild(var,CIZ_TITLE_IMAGE);
        var->setVisible(false);
    }
    if(m_titleImageSel)
    {
        m_titleImageSel->removeFromParentAndCleanup(true);
    }
    m_titleImageSel = var;
}

void BWCCMenuItemImage::setTitleDisabledImage(Sprite* var)
{
    if(var)
    {
        var->setAnchorPoint(Point(0.5,0.5));
        var->setPosition(Point(getContentSize().width/2,getContentSize().height/2));
        addChild(var,CIZ_TITLE_IMAGE);
        var->setVisible(false);
    }

    if(m_titleImageDis)
    {
        m_titleImageDis->removeFromParentAndCleanup(true);
    }
    m_titleImageDis = var;
}

void BWCCMenuItemImage::setTitleSprite(Sprite* titleSpriteNor,Sprite* titleSpriteSel,Sprite* titleSpriteDis)
{
    if(titleSpriteNor)
    {
        setTitleNormalImage(titleSpriteNor);
    }
    if(titleSpriteSel)
    {
        setTitleSelectedImage(titleSpriteSel);
    }
       
    if(titleSpriteDis)
    {
        setTitleDisabledImage(titleSpriteDis);
    }
}


void BWCCMenuItemImage::setTitleImage(const char* titleImageNor,const char* titleImageSel, const char* titleImageDis)
{
    Sprite* titleSpriteNor = NULL;
    Sprite* titleSpriteSel = NULL;
    Sprite* titleSpriteDis = NULL;
    
    if(titleImageNor)
        titleSpriteNor = CCSprite::create(titleImageNor);
    
    if(titleImageSel)
        titleSpriteSel = CCSprite::create(titleImageSel);
    
    if(titleImageDis)
        titleSpriteDis = CCSprite::create(titleImageDis);
    
    setTitleSprite(titleSpriteNor, titleSpriteSel, titleSpriteDis);
}

// bg
void BWCCMenuItemImage::setNormalImage(Node* var)
{
    
    if (var)
    {
        Sprite* norSprite = (Sprite*)var;
        Size size = norSprite->getContentSize();
        setContentSize(size);
        addChild(var,CIZ_BG_IMAGE);
        var->setAnchorPoint(m_imageAnchorPoint);
        var->setPosition(Point(getContentSize().width*m_imageAnchorPoint.x,getContentSize().height*m_imageAnchorPoint.y));
        var->setVisible(true);
    }
    if (_normalImage)
    {
        removeChild(_normalImage, true);
    }
    _normalImage = var;
}

void BWCCMenuItemImage::setSelectedImage(Node* var)
{
    if (var)
    {
        addChild(var,CIZ_BG_IMAGE);
        var->setAnchorPoint(m_imageAnchorPoint);
        var->setPosition(Point(getContentSize().width*m_imageAnchorPoint.x,getContentSize().height*m_imageAnchorPoint.y));
        var->setVisible(false);
    }
    if (_selectedImage)
    {
        removeChild(_selectedImage, true);
    }
    _selectedImage = var;
}

void BWCCMenuItemImage::setDisabledImage(Node* var)
{
    if (var)
    {
        addChild(var,CIZ_BG_IMAGE);
        var->setAnchorPoint(m_imageAnchorPoint);
        var->setPosition(Point(getContentSize().width*m_imageAnchorPoint.x,getContentSize().height*m_imageAnchorPoint.y));
        var->setVisible(false);
    }
    if (_disabledImage)
    {
        removeChild(_disabledImage, true);
    }
    _disabledImage = var;
}



void BWCCMenuItemImage::setImageAnchorPoint(Point anchorPoint)
{
    m_imageAnchorPoint = anchorPoint;
}

Point BWCCMenuItemImage::getImageAnchorPoint()
{
    return m_imageAnchorPoint;
}


void BWCCMenuItemImage::setIsEnabled(bool bEnabled)
{
    CCMenuItemImage::setEnabled(bEnabled);
    
    if (m_titleImageSel)
    {
        m_titleImageSel->setVisible(false);
    }
    if (bEnabled)
    {
        if(m_titleImageNor)
        m_titleImageNor->setVisible(true);
        
        if (m_titleImageDis)
        {
            m_titleImageDis->setVisible(false);
        }
    }
    else
    {
        if (m_titleImageDis)
        {
            m_titleImageDis->setVisible(true);
            if(m_titleImageNor)
            m_titleImageNor->setVisible(false);
        }
        else
        {
            if(m_titleImageNor)
            m_titleImageNor->setVisible(true);
        }
    }
    
    //label 
    if (m_titleLabelSel)
    {
        m_titleLabelSel->setVisible(false);
    }
    if (bEnabled)
    {
        if(m_titleLabelNor)
            m_titleLabelNor->setVisible(true);
        
        if (m_titleLabelDis)
        {
            m_titleLabelDis->setVisible(false);
        }
    }
    else
    {
        if (m_titleLabelDis)
        {
            m_titleLabelDis->setVisible(true);
            if(m_titleLabelNor)
                m_titleLabelNor->setVisible(false);
        }
        else
        {
            if(m_titleLabelNor)
                m_titleLabelNor->setVisible(true);
        }
    }
}

void BWCCMenuItemImage::selected()
{
    if(m_selectedAble == false) return;
    CCMenuItemImage::selected();
    
    if (m_titleImageDis)
    {
        m_titleImageDis->setVisible(false);
    }
    if (m_titleImageSel)
    {
        if(m_titleImageNor)
        m_titleImageNor->setVisible(false);
        m_titleImageSel->setVisible(true);
    }
    else
    {
        if(m_titleImageNor)
            m_titleImageNor->setVisible(true);
    }
    
    //label
    if (m_titleLabelDis)
    {
        m_titleLabelDis->setVisible(false);
    }
    if (m_titleLabelSel)
    {
        if(m_titleLabelNor)
            m_titleLabelNor->setVisible(false);
        m_titleLabelSel->setVisible(true);
    }
    else
    {
        if(m_titleLabelNor)
            m_titleLabelNor->setVisible(true);
    }
    
   
    if(m_currentSelectorState == ISSE_UNKNOWN)
    {
        m_currentSelectorState = ISSE_MOVE;
        if (m_target)
        {
            (m_target->*m_beginSelector)(this);
        }
    }
    else  //todo
    {
        if (m_target&&m_moveSelector)
        {
            (m_target->*m_moveSelector)(this);
        }
    }
}

void BWCCMenuItemImage::unselected()
{
    if(!m_unselectedAble) return;
    CCMenuItemImage::unselected();
    
    if(m_titleImageNor)
    m_titleImageNor->setVisible(true);
    
    if (m_titleImageSel)
    {
        m_titleImageSel->setVisible(false);
    }
    
    if (m_titleImageDis)
    {
        m_titleImageDis->setVisible(false);
    }
    
    //label
    if(m_titleLabelNor)
        m_titleLabelNor->setVisible(true);
    
    if (m_titleLabelSel)
    {
        m_titleLabelSel->setVisible(false);
    }
    
    if (m_titleLabelDis)
    {
        m_titleLabelDis->setVisible(false);
    }
    
    m_currentSelectorState = ISSE_UNKNOWN;
}


void BWCCMenuItemImage::setTitleString(const char* titleString,const char* fontName,float fontSize, ItemStateEnum itemState,
                                       Color3B textColor,
                                       int lineWidth, Color3B lineColor )
{
    CCLabelStroke* titleLabel = NULL;
    if(lineWidth > 0)
    {
        titleLabel = CCLabelStroke::labelWithString(titleString, fontName, fontSize, lineWidth, lineColor,CCLabelStroke::STE_ALL);
    }
    else
    {
        titleLabel = CCLabelStroke::labelWithString(titleString, fontName, fontSize);
    }
    titleLabel->setColor(textColor);
    titleLabel->setAnchorPoint(Point(0.5,0.5));
    titleLabel->setPosition(Point(getContentSize().width/2,getContentSize().height/2));
    switch (itemState)
    {
        case ISE_NORMAL:
        {
            setTitleNormalLabel(titleLabel);
        }
            break;
    case ISE_SELECT:
        {
            setTitleSelectedLabel(titleLabel);
        }
        break;
    case ISE_DISABLE:
        {
            setTitleDisabledLabel(titleLabel);
        }
        break;
        default:
            break;
    }
}


void BWCCMenuItemImage::setTarget(Object *target, SEL_MenuHandler selector, itemSelectorStateEnum selectorState)
{
    m_target = target;
    switch (selectorState) 
    {
        case ISSE_BEGIN:
        {
            m_beginSelector = selector;
        }
            break;
        case ISSE_MOVE:
        {
            m_moveSelector = selector;
        }
            break;
        case ISSE_END:
        {
        }
            break;
        default:
            break;
    }
}

void BWCCMenuItemImage::activate()
{
    MenuItem::activate();
    
    if (_enabled)
    {
        //music
        //UserData::shareUserData()->playEffect("btn.mp3");
    }
}


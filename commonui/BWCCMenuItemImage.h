
/*
 *
 *  Created by wangbin
 *
 */

#ifndef BWCCMenuItemImage_h
#define BWCCMenuItemImage_h

#include "cocos2d.h"
#include "CCLabelStroke.h"
USING_NS_CC;


class  BWCCMenuItemImage : public MenuItemImage
{
public:
    
    enum itemSelectorStateEnum
    {
        ISSE_UNKNOWN = 0,
        ISSE_BEGIN   = 1,
        ISSE_MOVE    = 2,
        ISSE_END     = 3
        
    };
    
    enum ItemStateEnum
    {
        ISE_UNKNOWN   = 0,
        ISE_NORMAL    = 1,
        ISE_SELECT    = 2,
        ISE_DISABLE    = 3
    };
    
    enum ChildItemZ
    {
        CIZ_UNKNOWN         = 0,
        CIZ_BG_IMAGE        = 10,
        CIZ_TITLE_IMAGE     = 20,
        CIZ_TITLE_LABEL     = 30,
        CIZ_OTHER           = 40,
    };

    BWCCMenuItemImage();
    virtual ~BWCCMenuItemImage();
    
    static BWCCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, Object* target, SEL_MenuHandler selector);
    
     static BWCCMenuItemImage* create(Sprite* normalImage, Sprite *selectedImage,Sprite *disabledImage, Object* target, SEL_MenuHandler selector);
    
    static BWCCMenuItemImage* create(CCLabelStroke *titleLabelNor,CCLabelStroke *titleLabelSel, CCLabelStroke *titleLabelDis,Object* target, SEL_MenuHandler selector);

    virtual void setNormalImage(Node* var);
    virtual void setSelectedImage(Node* var);
    virtual void setDisabledImage(Node* var);
    
    void setTitleNormalImage(Sprite* var);
    void setTitleSelectedImage(Sprite* var);
    void setTitleDisabledImage(Sprite* var);
    Sprite* getTitleNormalImage(){ return m_titleImageNor; }
    Sprite* getTitleSelectImage(){ return m_titleImageSel; }
    Sprite* getTitleDisableImage(){ return m_titleImageDis; }

    virtual void selected();
    virtual void unselected();
    virtual void setIsEnabled(bool bEnabled);
    
    void    setImageAnchorPoint(Point anchorPoint);
    
    void    setTarget(Object *target, SEL_MenuHandler selector, itemSelectorStateEnum selectorState);
    void    setTitleImage(const char* titleImageNor,const char* titleImageSel, const char* titleImageDis);
    void    setTitleSprite(Sprite* titleSpriteNor,Sprite* titleSpriteSel,Sprite* titleSpriteDis);

    void    setTitleString(const char* titleStringNor,const char* fontName,float fontSize, ItemStateEnum itemState, Color3B textColor =  Color3B::WHITE,int lineWidth = 0, Color3B lineColor =  Color3B::BLACK);
    void    setTitleDisabledLabel(CCLabelStroke* var);
    void    setTitleSelectedLabel(CCLabelStroke* var);
    void    setTitleNormalLabel(CCLabelStroke* var);
    Point   getImageAnchorPoint();
    
    void    setSelectedAble(bool able){m_selectedAble = able;}
    bool    getSelectedAble(){return  m_selectedAble;}
    
    void    setUnSelectedAble(bool able){m_unselectedAble = able;}
    bool    getUnSelectedAble(){return  m_unselectedAble;}
    
    virtual void activate();

    
private:
    
    Point             m_imageAnchorPoint;
    Object*           m_target;
    SEL_MenuHandler     m_beginSelector;
    SEL_MenuHandler     m_moveSelector;
    
    itemSelectorStateEnum m_currentSelectorState;
    
    Sprite*       m_titleImageNor;
    Sprite*       m_titleImageSel;
    Sprite*       m_titleImageDis;
    
    CCLabelStroke*  m_titleLabelNor;
    CCLabelStroke*  m_titleLabelSel;
    CCLabelStroke*  m_titleLabelDis;
    
    bool            m_selectedAble;
    bool            m_unselectedAble;

};

#endif

//
//
//  Created by wangbin on 13-1-14.
//
//

#ifndef __ESGame__BWSelectLevelLayer__
#define __ESGame__BWSelectLevelLayer__

#include <iostream>
#include "CCCutTouchLayer.h"
#include "CommonDef.h"
#include "cocos2d.h"
#include "BWMenu.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BWSelectLevelLayer : public CCCutTouchLayer
{
public:
    BWSelectLevelLayer();
    ~BWSelectLevelLayer();
    static BWSelectLevelLayer*       create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool            initWithColor(const Color4B& color, GLfloat w, GLfloat h);
    virtual void            onEnter();
    virtual void            onExit();
    void                    showUI(Node* pNode,void* p);
    int                     getLayerID();
    
protected:
    void                    functionLayer(int nLayerID);
    void                    menuItemCallbackSet();
    void                    registerCmd();
    void                    initUI();
    void                    clickCombat(Ref *pObject);
    void                    clickBack(Ref *pObject);
    void                    clickLevel(Ref* pOj,Control::EventType controlEvent);
private:
    RenderTexture*          m_pRenderTexture;
    Point                   m_pointBegin;
    Layer*                  m_pBgLayer;
    Sprite*                 m_pBgSprite;
    bool                    m_bScrolled;
    bool                    m_bMoved;
    int                     m_nLayerID;
    CCCutTouchLayer*        _pUILayer;
    Menu*                   _pUIMenu;
    BWMenu*                 _pMenuDungeon;
    std::map<int , DungeonFlagData> _mapGroup;
    
};

#endif /* defined(__ESGame__BWSelectLevelLayer__) */

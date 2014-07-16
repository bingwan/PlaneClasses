//
//
//  Created by wangbin on 13-1-14.
//
//

#ifndef __ESGame__BWHomeLayer__
#define __ESGame__BWHomeLayer__

#include <iostream>
#include "CCCutTouchLayer.h"
#include "CommonDef.h"
#include "cocos2d.h"
#include "BWCCMenuItemImage.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class BWHomeLayer : public CCCutTouchLayer
{
public:
    BWHomeLayer();
    ~BWHomeLayer();
    static BWHomeLayer*       create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool            initWithColor(const Color4B& color, GLfloat w, GLfloat h);
    virtual void            onEnter();
    virtual void            onExit();
    
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
    void                    showUI(Node* pNode,void* p);
    int                     getLayerID();

protected:
    void                    functionLayer(int nLayerID);
    void                    menuItemCallbackSet();
    void                    registerCmd();
    void                    initUI();
    void                    clickBack();
    void                    showLevelTooLowTip(const char *languageKey, int minLevel);
    void                    clickCombat(Ref *pRef);
    void                    clickGoShop(Ref *pRef);
    void                    deaccelerateScrolling(float dt);
    void                    refreshPos(Point newPos);
    void                    clickBuilding(Ref* pRef);
    void                    clickEdit(Ref* pRef);
    void                    clickBuildingDetail(Ref* pRef);
    void                    setBtnDetailVisible(bool bVisible,bool bAnimate);
    void                    setInfoBgVisible(bool bViaible,bool bAnimate );
    void                    clickShowSetting(Ref *pRef);
    void                    enterFunctionLayer(Ref* pRef);
    void                    clickUpgradeBuilding(Ref* pRef);
    
    void                    clickEdit(Ref* pObject,Control::EventType controlEvent);
    void                    clickLevel(Ref* pObject,Control::EventType controlEvent);

private:
    Layer*                  m_pBgLayer;
    Sprite*                 m_pBgSprite;
    CCCutTouchLayer*        _pUILayer;
    Menu*                   _pUIMenu;
    BWCCMenuItemImage*      _pBtnInfo;
    BWCCMenuItemImage*      _pBtnUpgrade;
    BWCCMenuItemImage*      _pBtnFunction;
    std::vector<BWCCMenuItemImage*> _vBtnDetail;
    EBuildingType               _eBuildingType;
    
    Layer*                  _pBuildingInfoLayer;
    
};



#endif /* defined(__ESGame__BWHomeLayer__) */

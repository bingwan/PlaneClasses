//
//
//  Created by wangbin 
//
//

#ifndef __BWCombatLayer__
#define __BWCombatLayer__

#include <iostream>
#include "CCCutTouchLayer.h"
#include "CommonDef.h"
#include "cocos2d.h"
#include "BWUnit.h"
#include "BWUnit.h"
#include "BWransformSprite.h"

#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


class BWCombatLayer : public CCCutTouchLayer 
{
public:
    BWCombatLayer();
    virtual ~BWCombatLayer();
    static BWCombatLayer*     create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool            initWithColor(const Color4B& color, GLfloat w, GLfloat h);
    virtual void            onEnter();
    virtual void            onExit();
    
    virtual bool            onTouchBegan(Touch *touch, Event *unused_event);
    virtual void            onTouchMoved(Touch *touch, Event *unused_event);
    virtual void            onTouchEnded(Touch *touch, Event *unused_event);
    virtual void            onTouchCancelled(Touch *touch, Event *unused_event);
    
    virtual void            onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    virtual void            onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
    
    void                    showUI(Node* pNode,void* p);
    int                     getLayerID();
    virtual void            update(float dt);
    void                    addUnit(BWUnit* pCell);
    void                    addBWUnitToBWCombatLayer(BWUnit *pBWUnit);
    void					addEffect(UnitData *pInfo);
	int						getNearestEnemy(BWUnit *pBWUnit);
	
    void                    clearAllCter();
    int                     getCombatWidth(){return _nCombatWidth;}
protected:
    void                    menuItemCallbackSet();
    void                    registerCmd();
    void                    initUI();
    void                    clickBack();
    void                    initBgMapUI();
    void                    initCter();
    void                    beginUpdate();
    void                    initUILayer();
    void                    clickSkillBtn(Ref* pBtn);
    void                    clickPause(Ref* pBtn);
    void                    leaveDelay(float dt);
    void                    clickCreateTroop(Ref* pBtn);
    void                    updatePos(float dt);
    void                    clickBack(Ref* pObject,Control::EventType controlEvent);
    void                    updateBg(float dt);
    void                    updateCreateNpc(float dt);
private:
    Layer*                  _pBgLayer;
    int                     _nWaveOrder;
    Layer*                  _pBgLayerFar;
    Layer*                  _pBgLayerCombat;
    Layer*					_pBgLayerUI;
    float                   _fCombatTime;
    float                   _fOneWaveTime;
    int                     _nWaveIndex;
    LabelTTF*               _pLabelAllCterNum;
    int                     _nCterNum;
	BWUnit*					_pMonster;
	Menu* 					_pMenuSkillSlots;
    Menu*					_pMenuTroopSlots;
    Menu*					_pMenuItemSlots;
    Menu*					_pMenuSysSlots;
    int                     _nCombatWidth;
    BWransformSprite*       _pBgSprite;
    //std::map<int, NpcData>  _mapCurLevelNpcData;
    LevelData _levelData;
    
};

#endif /* defined(__ESGame__BWCombatLayer__) */

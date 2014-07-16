//
//  BWCombatLayer.cpp
//
//  Created by wangbin on 13-1-14.
//
//

#include "BWCombatLayer.h"
#include "CommonDef.h"
#include "NotificationManager.h"
#include "UIManager.h"
#include "CCAPI.h"
#include "ResManager.h"
#include "RootLayer.h"
#include "BWStreamFile.h"
#include "BWUnitManager.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
#include "CCButton.h"

USING_NS_CC_EXT;

#define COMBAT_BG_Z     20
#define COMBAT_UI_Z     30

//#define BG_STATIC_Z     10
#define BG_FAR_Z        20
#define BG_MID_Z        30
#define BG_COMBAT_Z     40
#define BG_FRONT_Z      50
#define BG_UI_Z			100

#define BG_COMBAT_LAYER_EFFECT_AFTER_Z 10
#define BG_COMBAT_LAYER_ROLE_Z         20
#define BG_COMBAT_LAYER_EFFECT_FRONT_Z 30

#define BG_STATIC_SPEED     0
#define BG_FAR_SPEED        20
#define BG_MID_SPEED        30
#define BG_COMBAT_SPEED     40
#define BG_FRONT_SPEED      50


BWCombatLayer::BWCombatLayer():
_pBgLayer(NULL),
_pBgLayerCombat(NULL),
_pBgLayerUI(NULL),
_fOneWaveTime(0),
_nWaveIndex(0)
{
    _nCterNum =0;
    _nWaveOrder = 0;
    _fCombatTime =0;
}
//=============================================================
//=============================================================
BWCombatLayer::~BWCombatLayer()
{
  
}
//=============================================================
//=============================================================
BWCombatLayer* BWCombatLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    BWCombatLayer * pLayer = new BWCombatLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}
//=============================================================
//=============================================================
bool BWCombatLayer::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
    if(CCCutTouchLayer::initWithColor(color, w, h))
    {
        setTag(eUILayerId_Combat);
        registerCmd();
        setTouchEnabled(true);
        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        return true;
    }
    return false;
}
//=============================================================
//=============================================================
void BWCombatLayer::registerCmd()
{    
    NotificationManager::shareInstance()->registerCmd(this,eGAME_CMD_ID_ShowCombat ,callfuncND_selector(BWCombatLayer::showUI));
}
//=============================================================
//=============================================================
void BWCombatLayer::onEnter()
{
    CCCutTouchLayer::onEnter();
    
    _pBgLayer = Layer::create();
    _pBgLayer->setAnchorPoint(Point(0,0));
    _pBgLayer->setPosition(Point(0,0));
    addChild(_pBgLayer,COMBAT_BG_Z);

    initBgMapUI();
    initUILayer();
    
    initCter();
    beginUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_bg3.mp3",true);
}

void BWCombatLayer::onExit()
{
    _nCterNum =0;
    _nWaveOrder = 0;
    _fCombatTime =0;
    
    removeAllChildren();

    CCCutTouchLayer::onExit();
}

void BWCombatLayer::showUI(Node* pNode,void* p)
{
    eUILayerId layerId = (eUILayerId)getTag();
    UIManager::shareInstance()->showUI(layerId);
}


void BWCombatLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    return ;
}


void BWCombatLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
}

void BWCombatLayer::initBgMapUI()
{
    Size contentSize = getContentSize();

    _pBgLayerFar        = CCLayer::create();
    _pBgLayerCombat     = CCLayer::create();
    _pBgLayerUI		    = CCLayer::create();
 
    _pBgLayer->addChild(_pBgLayerFar,BG_FAR_Z);
    _pBgLayer->addChild(_pBgLayerCombat,BG_COMBAT_Z);
    _pBgLayer->addChild(_pBgLayerUI, BG_UI_Z);
    
    
    _pBgSprite = BWransformSprite::create("map_bg3.png");
    _pBgSprite->setAnchorPoint(Point(0.5,0));
    _pBgSprite->setPosition(Point(contentSize.width*0.5,0));
    _pBgLayerFar->addChild(_pBgSprite);
    
    _pBgSprite->setTransformSpeed(0,100);
}


void BWCombatLayer::initCter()
{
    UnitData unitData;
    unitData.nId = 1 ;
    BWUnitManager::shareBWUnitManager()->createHero(&unitData);
    BWUnit* pHero = BWUnitManager::shareBWUnitManager()->getHero();
    if(!pHero)
    {
        return;
    }
    addUnit(pHero);

    ResManager::shareResManager()->loadLevelXml(1, &_levelData);
}

void BWCombatLayer::addUnit(BWUnit* pUnit)
{
    Size contentSize = getContentSize();

    if(!pUnit)
    {
        return;
    }
    Sprite* pSpriteChr = pUnit->getTextureSprite();
    if(!pSpriteChr)
    {
        //log("error=getTabID=%d", pUnit->getID());
         return;
    }
    pSpriteChr->setPosition(pUnit->getUnitData()->pos);
    _pBgLayerCombat->addChild(pSpriteChr);
}

void BWCombatLayer::beginUpdate()
{
    schedule(schedule_selector(BWCombatLayer::update));
}

void BWCombatLayer::update(float dt)
{
    _fCombatTime += dt;
    updatePos(dt);
    BWUnitManager::shareBWUnitManager()->update(dt);
    updateBg(dt);
    
    updateCreateNpc(dt);
}

void BWCombatLayer::updateCreateNpc(float dt)
{
    BWUnit* pHero = BWUnitManager::shareBWUnitManager()->getHero();
    if(!pHero)
    {
        return;
    }
    int nHeroSpeed = pHero->getSpeed();
    int nWayLen = nHeroSpeed * _fCombatTime;
    
    Point heroPos = pHero->getPosition();
    
    std::vector<int> vNpcId;
    
    std::map<int, NpcData>::iterator it = _levelData.mapLevelNpc.begin();
    while (it != _levelData.mapLevelNpc.end())
    {
        NpcData* pNpcData = &it->second;
        ++it;
        if(!pNpcData)
        {
            continue;
        }
        Point npcPos = pNpcData->pos;
        heroPos.y = nWayLen + heroPos.y;
        Point movePos = npcPos - heroPos;
        float fDis = movePos.getLength();
        
        int nMoveY = npcPos.y - heroPos.y;
        
        if((nMoveY >0 && pNpcData->triggerDistance>0 && fDis <= fabs(pNpcData->triggerDistance)) ||
           (nMoveY <0 && pNpcData->triggerDistance<0 && fDis >= fabs(pNpcData->triggerDistance))
           )
        {
            //create
            Point npcNewPos = Point(npcPos.x,npcPos.y-nWayLen);
            
            UnitData unitData;
            unitData.nId = pNpcData->nTabId;
            unitData.pos = npcNewPos;
            unitData.actionData = pNpcData->actData;
            unitData.mapSlotData = pNpcData->mapSlotData;
            BWUnitManager::shareBWUnitManager()->createMonsterDelay(&unitData);
            
            vNpcId.push_back(pNpcData->index);
        }
    }
    
    for(int i=0;i<vNpcId.size();++i)
    {
        _levelData.mapLevelNpc.erase(vNpcId[i]);
    }
    vNpcId.clear();
}


void BWCombatLayer::updateBg(float dt)
{
    _pBgSprite->tick(dt);
}

void BWCombatLayer::updatePos(float dt)
{
}

void BWCombatLayer::initUILayer()
{
    Size contentSize = getContentSize();

    CCButton*  pBtnBack = CCButton::create("back",COMMON_FONT,50);
    pBtnBack->setPosition(Point(50,contentSize.height-50));
    pBtnBack->addTargetWithActionForControlEvents(this, cccontrol_selector(BWCombatLayer::clickBack), Control::EventType::TOUCH_UP_INSIDE);
    _pBgLayerUI->addChild(pBtnBack);

}

void BWCombatLayer::clickBack(Ref* pObject,Control::EventType controlEvent)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowHome);
}

void BWCombatLayer::clickPause(Ref* pBtn)
{
    clearAllCter();
    schedule(schedule_selector(BWCombatLayer::leaveDelay), 0.3);
}

void BWCombatLayer::leaveDelay(float dt)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowSelDungeon);
}

void BWCombatLayer::clickSkillBtn(Ref* pBtn)
{
}

void  BWCombatLayer::clearAllCter()
{
    BWUnitManager::shareBWUnitManager()->deleteAllUnitDelay();
}

bool BWCombatLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    if(CCCutTouchLayer::onTouchBegan(touch, unused_event))
    {
        return true;
    }
    return false;
}

void BWCombatLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    Point prePos = touch->getPreviousLocation();
    Point curPos =  touch->getLocation();
    Point movePos = curPos-prePos;
    
    BWUnit* pHero = BWUnitManager::shareBWUnitManager()->getHero();
    if(!pHero)
    {
        return;
    }
    Point oldPos = pHero->getPosition();
    Point newPos = oldPos + movePos;
    
    Size combatSize = _pBgLayerCombat->getContentSize();
    newPos.x = newPos.x >= combatSize.width ? combatSize.width  : newPos.x;
    newPos.x = newPos.x <= 0 ? 0  : newPos.x;
    pHero->setPosition(newPos);
    
}

void BWCombatLayer::onTouchEnded(Touch *touch, Event *unused_event)
{}

void BWCombatLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{}


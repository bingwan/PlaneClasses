

#include "BWShowBulletLayer.h"
#include "CCScrollLayer.h"
#include "BWTextEdit.h"
#include "BWEditLayer.h"
#include "BWDetailNPCLayer.h"
#include "BWMenu.h"
#include "BWEditBulletLayer.h"
#include "ResManager.h"
#include "CCButton.h"
#include "BWUnitManager.h"
#include "CCAPI.h"

BWShowBulletLayer::BWShowBulletLayer()
{
}

BWShowBulletLayer::~BWShowBulletLayer()
{
}


BWShowBulletLayer* BWShowBulletLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    BWShowBulletLayer * pLayer = new BWShowBulletLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool BWShowBulletLayer::initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
    if(CCCutTouchLayer::initWithColor(color, width, height))
    {
        setTouchEnabled(true);
        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        return true;
    }
    return false;
}

void BWShowBulletLayer::initUI()
{
    Size contentSize = getContentSize();
    Size scrolSize = Size(contentSize.width,100);
    
    CCScrollLayer* pScrollLayer = CCScrollLayer::scrollLayerWidthColor(Color4B(),scrolSize);
    pScrollLayer->setAnchorPoint(Point(0,0));
    pScrollLayer->setPosition(Point(0,0));
    addChild(pScrollLayer);
    
    std::map<int, BulletTabData>* pMapBullet = ResManager::shareResManager()->getBulletMap();
    if(!pMapBullet)
    {
        return;
    }

    std::map<int, BulletTabData>::iterator it = pMapBullet->begin();
    while (it != pMapBullet->end())
    {
        BulletTabData* pBulletTabData = &it->second;
        ++it;
        if(!pBulletTabData)
        {
            continue;
        }
        
        int nBulletId = pBulletTabData->nId;
        
        char text[256];
        sprintf(text, "%d",nBulletId);
        
        CCButton* pBtnBullet = CCButton::create(text,COMMON_FONT,50);
        pBtnBullet->setPosition(Point(50,contentSize.height-50));
        pBtnBullet->addTargetWithActionForControlEvents(this, cccontrol_selector(BWShowBulletLayer::clickBullet), Control::EventType::TOUCH_UP_INSIDE);
        pBtnBullet->setTag(nBulletId);
        addChild(pBtnBullet);
    }
    
    CCButton*  pBtnBack = CCButton::create("back",COMMON_FONT,50);
    pBtnBack->setPosition(Point(50,contentSize.height-50));
    pBtnBack->addTargetWithActionForControlEvents(this, cccontrol_selector(BWShowBulletLayer::clickBack), Control::EventType::TOUCH_UP_INSIDE);
    addChild(pBtnBack);
    
    UnitData unitData;
    unitData.nId = 1 ;
    unitData.pos = CCGET_CENTER(this);
    
    BWUnitManager::shareBWUnitManager()->createHero(&unitData);
    BWUnit* pHero = BWUnitManager::shareBWUnitManager()->getHero();
    if(!pHero)
    {
        return;
    }
    Sprite* pSpriteChr = pHero->getTextureSprite();
    if(!pSpriteChr)
    {
        return;
    }
    pSpriteChr->setPosition(pHero->getUnitData()->pos);
    addChild(pSpriteChr);
    
    schedule(schedule_selector(BWShowBulletLayer::update));
}

void BWShowBulletLayer::update(float dt)
{
    BWUnitManager::shareBWUnitManager()->update(dt);
}


void BWShowBulletLayer::clickBullet(Ref* pObject,Control::EventType controlEvent)
{
    CCButton* pBtn = (CCButton*)pObject;
    int nBulletId = pBtn->getTag();
    
    BulletTabData* pBulletTabData = ResManager::shareResManager()->getBulletTabData(nBulletId);
    if(!pBulletTabData)
        return;
    
    BWUnit* pHero = BWUnitManager::shareBWUnitManager()->getHero();
    if(!pHero)
    {
        return;
    }
    
    pHero->deleteSlot();

    std::map<int,SlotData> mapslot;
    SlotData slotData;
    slotData.nId = 1;
    slotData.nBulletId = nBulletId;
    
    pHero->setSlotMapData(&mapslot);
    pHero->initSlot();
    
}


void BWShowBulletLayer::clickBack(Ref* pObject,Control::EventType controlEvent)
{
    removeFromParentAndCleanup(true);
}








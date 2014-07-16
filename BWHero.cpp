

#include "BWHero.h"
#include "CCAPI.h"
#include "UserData.h"
#include "BWUnitManager.h"

BWHero::BWHero()
{
    _fBulletGroupTime = 0;
    _fBulletSpaceTime = 0;
}


BWHero::~BWHero()
{
}

bool BWHero::init(UnitData* pInfo)
{
    m_pData = ResManager::shareResManager()->getHeroTabData(pInfo->nId);
    if(!m_pData)
    {
        log("error=pHeroData=pCaterInfo->nTabId=%d",pInfo->nId);
        return false;
    }
    BWUnit::init(pInfo);
    
    _pTextureSprite = Sprite::create(m_pData->pszIcon);
    _pTextureSprite->retain();
    
//    SlotData slotData;    //bingwan test
//    slotData.nId = 1;
//    slotData.nBulletId = 101001;
//    slotData.nBulletSpeed = 2000;
//    slotData.pos = Point(0,0);
//    _unitData.mapSlotData.insert(std::make_pair(slotData.nId,slotData));
    
//    SlotData slotData2;  //bingwan test
//    slotData2.nId = 2;
//    slotData2.nBulletId = 101001;
//    slotData2.nBulletSpeed = 200;
//    slotData2.pos = Point(80,50);
//    _unitData.mapSlotData.insert(std::make_pair(slotData2.nId,slotData2));
//    
    initSlot();

    return true;
}


void  BWHero::update(float dt)
{
    BWUnit::update(dt);
}

void BWHero::updatePos(float dt)
{
}

void BWHero::updateSlot(float dt)
{
}

void BWHero::collide(BWUnit* pFromUnit)  //碰撞通知
{
}

void BWHero::addBullet()
{
}






#include "BWMonster.h"
#include "CCAPI.h"
#include "BWUnitManager.h"

BWMonster::BWMonster()
{
}

BWMonster::~BWMonster()
{
}

bool BWMonster::init( UnitData* pInfo)
{
    m_pData = ResManager::shareResManager()->getMonsterData(pInfo->nId);
    if(!m_pData)
    {
        log("error=MonsterTabData=pCaterInfo->nTabId=%d",pInfo->nId);
        return false;
    }
    
    BWUnit::init(pInfo);
    
    _pTextureSprite = Sprite::create(m_pData->pszIcon);
    _pTextureSprite->retain();
    _pTextureSprite->setPosition(pInfo->pos);
    
    initSlot();
    
    BWUnitManager::shareBWUnitManager()->playAction(getTextureSprite(), &_unitData.actionData);

    return true;
}

void BWMonster::update(float dt)
{
    BWUnit::update(dt);
}


void BWMonster::collide(BWUnit* pFromUnit)
{
    BWUnit::collide(pFromUnit);
    
    if(pFromUnit->getUnitType() == EUnitType_Hero ||
       pFromUnit->getUnitType() == EUnitType_HeroBullet
       )
    {
        setDead(true);
        BWUnitManager::shareBWUnitManager()->deleteUnitDelay(this);
    }
}

























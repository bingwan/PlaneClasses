

#include "BWSlot.h"
#include "CCAPI.h"
#include "UserData.h"
#include "BWUnitManager.h"
#include "BWActionInterval.h"


BWSlot::BWSlot()
{
    _fBulletGroupTime = 0;
    _fBulletSpaceTime = 0;
}

BWSlot::~BWSlot()
{
}

void BWSlot::init(SlotData* pSlotData)
{
    _slotData = *pSlotData;
    
    BulletTabData*  pBulletTabData = ResManager::shareResManager()->getBulletTabData(_slotData.nBulletId);
    if(!pBulletTabData)
    {
        return;
    }
    _bulletTabData = *pBulletTabData;
    
    BWUnitManager::shareBWUnitManager()->playAction(this,&_slotData.actionData);
    
    _slotData.fFireTime = 0.5;
    _slotData.fFreeTime = 0.0;
    _slotData.fBulletSpaceTime = 0.1;
    
    //xz
    //_slotData.pos =
    
    RotateBy* pRotate = RotateBy::create(1.0, 360);
    RepeatForever* pEver = RepeatForever::create(pRotate);
    runAction(pEver);
}

BWSlot* BWSlot::create(SlotData* pSlotData)
{
    BWSlot* pSlot = new BWSlot();
    pSlot->init(pSlotData);
    pSlot->autorelease();
    return pSlot;
}

void  BWSlot::update(float dt)
{
    updatePos(dt);
    updateBullet(dt);
}

void BWSlot::updatePos(float dt)
{
}

void BWSlot::updateBullet(float dt)
{
    _fBulletGroupTime += dt;
    
    if(_fBulletGroupTime <= _slotData.fFireTime)
    {
        _fBulletSpaceTime += dt;
        if(_fBulletSpaceTime >= _slotData.fBulletSpaceTime)
        {
            _fBulletSpaceTime = 0;
            addBullet();
        }
    }
    else if(_fBulletGroupTime >= _slotData.fFireTime + _slotData.fFreeTime)
    {
        _fBulletGroupTime = 0;
    }
}


void BWSlot::addBullet()
{
    for( int i=0;i<_bulletTabData.nLineCount;++i)
    {
        UnitData bulletData;
        bulletData.nId = _bulletTabData.nId;
        bulletData.eType = _pParentUnit->getUnitType();;
        
        Point pos = getPosition();
        if(!getParent())
        {
            continue;
        }
        pos = getParent()->convertToWorldSpace(pos);
        if(getParent()->getParent() == NULL)
        {
            continue;
        }
        pos = getParent()->getParent()->convertToNodeSpace(pos);
        bulletData.pos = pos;
        bulletData.nBulletIndex = i;
        
        bulletData.pSlot = this;
        
        BWUnitManager::shareBWUnitManager()->createHeroBulletDelay(&bulletData);
    }
}







#include "BWItem.h"
#include "CCAPI.h"
#include "UserData.h"
#include "BWUnitManager.h"

BWItem::BWItem()
{
}

BWItem::~BWItem()
{
}

bool BWItem::init(UnitData* pInfo)
{
    BWUnit::init(pInfo);
    
    BWUnitManager::shareBWUnitManager()->playAction(getTextureSprite(), &_unitData.actionData);

    return true;
}

void BWItem::update(float dt)
{
    BWUnit::update(dt);
}



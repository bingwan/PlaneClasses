
#include "BWUnit.h"
#include "ResManager.h"
#include "cocos2d.h"
#include "CCAPI.h"
#include "ResManager.h"
#include "BuffManager.h"
#include "BuffProcess.h"
#include "UIManager.h"
#include "BWCombatLayer.h"
#include "BWUnitManager.h"


BWUnit::BWUnit()
{
    _bDead = false;
}

BWUnit::~BWUnit()
{
    if(_pTextureSprite)
    {
        _pTextureSprite->release();
        _pTextureSprite = NULL;
    }
}

bool BWUnit::init(UnitData* pInfo)
{
    _unitData = *pInfo;
    return  true;
}

void BWUnit::initSlot()
{
    std::map<int,SlotData>::iterator it =  _unitData.mapSlotData.begin();
    while (it != _unitData.mapSlotData.end())
    {
        SlotData* pSlotData = &it->second;
        ++it;
        if(!pSlotData)
        {
            log("BWUnit::initSlot:pSlotData==null");
            continue;
        }
        BWSlot* pSlot = BWSlot::create(pSlotData);
        if(!pSlot)
        {
            log("BWUnit::initSlot:pSlot==null");
            continue;
        }
        pSlot->setParentUnit(this);
        _mapSlot.insert(std::make_pair(pSlotData->nId, pSlot));
        pSlot->setPosition(pSlotData->pos);
        _pTextureSprite->addChild(pSlot);
        pSlot->setPosition(pSlotData->pos);
    }
}

void BWUnit::deleteSlot()
{
    _unitData.mapSlotData.clear();
    std::map<int,BWSlot*>::iterator it =  _mapSlot.begin();
    while (it != _mapSlot.end())
    {
        BWSlot* pSlot = it->second;
        ++it;
        if(!pSlot)
            continue;
        
        pSlot->removeFromParent();
    }
}



void BWUnit::updateBuff(float dt)
{
	std::vector<int> vToDeleteBuff;
    for(int i=0;i<_vBuff.size();i++)
    {
        BuffObject* pBuff = _vBuff[i];
        if(!pBuff)
            continue;
        BuffProcess* pProcess = BuffManager::share()->getBuffProcess(pBuff);
        if(!pProcess)
            continue;
        if(pBuff->getFinished())
        {
            vToDeleteBuff.push_back(i);
        }
        else
        {
			pProcess->onTickProcessBuff(this, pBuff, dt);
        }
    }
    for(int i=0;i<vToDeleteBuff.size();i++)
    {
        deleteBuffWithIndex(vToDeleteBuff[i]);
    }
    vToDeleteBuff.clear();

}

void BWUnit::update(float dt)
{
	updateBuff(dt);
    updatePos(dt);
    updateSlot(dt);
}

void BWUnit::updateSlot(float dt)
{
    std::map<int,BWSlot*>::iterator it = _mapSlot.begin();
    while (it != _mapSlot.end())
    {
        BWSlot* pSlot = it->second;
        ++it;
        if(!pSlot)
        {
            continue;
        }
        pSlot->update(dt);
    }
}

void BWUnit::updatePos(float dt)
{
}

void BWUnit::updateBlood()
{
}

void BWUnit::addBuff(int nBuffId,BWUnit* pFromBWUnit,BuffStateType eType)
{
    BuffObject* pBuff = BuffManager::share()->createBuffObject(nBuffId);
    if(!pBuff)
    {
        return;
    }
    BuffProcess* pNewProcess = BuffManager::share()->getBuffProcess(pBuff);
    if(!pNewProcess)
    {
        return;
    }
    pBuff->setBuffStateType(eType);
    if(pFromBWUnit)
    {
        pBuff->setFromCter(pFromBWUnit);
    }
    int nOldProcessIndex = getSameProcessIndex(pNewProcess);
    if(nOldProcessIndex != -1)
    {
        BuffObject* pBuff = _vBuff[nOldProcessIndex];
        if(!pBuff)
        {
            return;
        }
        deleteBuffWithIndex(nOldProcessIndex);
    }
    
    pNewProcess->onStartProcessBuff(this,pBuff);
	if(pNewProcess->isOnced())
	{
        pNewProcess->onEndProcessBuff(this, pBuff);
        BuffManager::share()->deleteBuff(pBuff);
	}
    else
    {
        _vBuff.push_back(pBuff);
    }
}

int BWUnit::getBuffIndex(BuffObject* pBuff)
{
    for(int buffIndex = 0; buffIndex != _vBuff.size();++buffIndex)
	{
		if(_vBuff[buffIndex] != NULL)
		{
			if (pBuff == _vBuff[buffIndex] )
			{
                return buffIndex;
			}
		}
	}
    return -1;
}

void BWUnit::deleteBuffWithIndex( int nIndex)
{
    if(nIndex >= _vBuff.size() || nIndex<0)
    {
        return;
    }
    BuffObject* pBuff = _vBuff[nIndex];
    if(!pBuff)
    {
        return;
    }
    _vBuff.erase(_vBuff.begin()+nIndex);
    deleteBuff(pBuff);
}

void BWUnit::deleteBuff(BuffObject* pBuff)
{
    if(!pBuff)
        return;
    BuffProcess* pNewProcess = BuffManager::share()->getBuffProcess(pBuff);
    if(!pNewProcess)
        return;
    pNewProcess->onEndProcessBuff(this,pBuff);
    BuffManager::share()->deleteBuff(pBuff);
	
}

int BWUnit::getSameProcessIndex(BuffProcess* pNewProcess)
{
    for(int buffIndex = 0; buffIndex != _vBuff.size();++buffIndex)
	{
		if(_vBuff[buffIndex] != NULL)
		{
			BuffProcess* pIndexBuffProcess = BuffManager::share()->getBuffProcess(_vBuff[buffIndex]);
			if (pIndexBuffProcess == pNewProcess)
			{
                return buffIndex;
			}
		}
	}
    return -1;
}

void BWUnit::collide(BWUnit* pFromUnit)
{
}

void BWUnit::deadDelay()
{
    _bDead = true;
    BWUnitManager::shareBWUnitManager()->deleteUnitDelay(this);
}

void  BWUnit::addBullet()
{
}
void BWUnit::remove()
{
    _pTextureSprite->stopAllActions();
    _pTextureSprite->removeFromParent();
}








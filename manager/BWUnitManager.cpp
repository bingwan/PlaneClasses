

#include <iostream>
#include "BWUnitManager.h"
#include "CCAPI.h"
#include "BWCombatLayer.h"
#include "UIManager.h"
#include "BWMonster.h"
#include "BWHero.h"
#include "BWBullet.h"
#include "BWItem.h"
#include "BWActionInterval.h"

static BWUnitManager* m_pInstance = NULL;
BWUnitManager* BWUnitManager::shareBWUnitManager()
{
    if( NULL == m_pInstance)
    {
        m_pInstance = new BWUnitManager();
    }
    return m_pInstance;
}

BWUnitManager::BWUnitManager()
{
    _pHero = NULL;
    _nUnitCount = 0;
}


BWUnitManager::~BWUnitManager()
{
}

void BWUnitManager::init()
{  
}

void BWUnitManager::update(float dt)
{
    //删除单元
    for(int i=0;i<_vNeedDeleteUnit.size();i++)
    {
        BWUnit* pUnit = _vNeedDeleteUnit[i];
        if(!pUnit)
        {
            continue;
        }
        deleteUnit(pUnit);
    }
    _vNeedDeleteUnit.clear();

    //创建怪物
    for(int i=0;i<_vCreateMonsterDelay.size();i++)
    {
        UnitData* pInfo = &_vCreateMonsterDelay[i];
        
        if(!pInfo)
        {
            continue;
        }
        BWUnit* pUnit = createMonster(pInfo);
        addToScene(pUnit);
    }
    _vCreateMonsterDelay.clear();
    
    //创建敌人子弹
    for(int i=0;i<_vCreateEnemyBulletDelay.size();i++)
    {
        UnitData* pInfo = &_vCreateEnemyBulletDelay[i];
        
        if(!pInfo)
        {
            continue;
        }
        BWUnit* pUnit = createEnemyBullet(pInfo);
        addToScene(pUnit);
        pUnit->beginAction();

    }
    _vCreateEnemyBulletDelay.clear();
    
    //创建我方子弹
    for(int i=0;i<_vCreateHeroBulletDelay.size();i++)
    {
        UnitData* pInfo = &_vCreateHeroBulletDelay[i];
        
        if(!pInfo)
        {
            continue;
        }
        BWUnit* pUnit = createMyBullet(pInfo);
        addToScene(pUnit);
        pUnit->beginAction();
    }
    _vCreateHeroBulletDelay.clear();
    
    //创建物品
    for(int i=0;i<_vCreateItemDelay.size();i++)
    {
        UnitData* pInfo = &_vCreateItemDelay[i];
        
        if(!pInfo)
        {
            continue;
        }
        BWUnit* pUnit = createItem(pInfo);
        addToScene(pUnit);
        pUnit->beginAction();

    }
    _vCreateItemDelay.clear();
    
        
    //更新怪物
    std::map<int, BWUnit*>::iterator itMonster = _mapMonster.begin();
    while (itMonster != _mapMonster.end())
    {
        BWUnit* pUnit = itMonster->second;
        ++itMonster;
        if(!pUnit)
            continue;
        pUnit->update(dt);
    }
    
    //更新敌人子弹
    std::map<int, BWUnit*>::iterator itEnemyBullet = _mapEnemyButtlet.begin();
    while (itEnemyBullet != _mapEnemyButtlet.end())
    {
        BWUnit* pUnit = itEnemyBullet->second;
        ++itEnemyBullet;
        if(!pUnit)
            continue;
        pUnit->update(dt);
    }
    //更新子弹
    std::map<int, BWUnit*>::iterator itMyBullet = _mapHeroButtlet.begin();
    while (itMyBullet != _mapHeroButtlet.end())
    {
        BWUnit* pUnit = itMyBullet->second;
        ++itMyBullet;
        if(!pUnit)
            continue;
        pUnit->update(dt);
    }
    
    //更新物品
    std::map<int, BWUnit*>::iterator itItem = _mapItem.begin();
    while (itItem != _mapItem.end())
    {
        BWUnit* pUnit = itItem->second;
        ++itItem;
        if(!pUnit)
            continue;
        pUnit->update(dt);
    }
    //更新英雄
    _pHero->update(dt);
    
    checkCollide(dt);
}

void BWUnitManager::checkCollide(float dt)
{
    Rect heroRect = _pHero->getBoundingBox();
    
    //更新怪物
    std::map<int, BWUnit*>::iterator itMonster = _mapMonster.begin();
    while (itMonster != _mapMonster.end())
    {
        BWUnit* pUnitMonster = itMonster->second;
        ++itMonster;
        if(!pUnitMonster)
        {
            continue;
        }
        
        Rect monsterRect = pUnitMonster->getBoundingBox();
        bool bCollide = monsterRect.intersectsRect(heroRect);
        if(bCollide)
        {
            if(pUnitMonster->getDead() == false) //怪物没死
            {
                _pHero->collide(pUnitMonster);
                pUnitMonster->collide(_pHero);
            }
        }
        
        std::map<int, BWUnit*>::iterator itMyBullet = _mapHeroButtlet.begin(); //英雄子弹
        while (itMyBullet != _mapHeroButtlet.end())
        {
            BWUnit* pUnitMyBullet = itMyBullet->second;
            ++itMyBullet;
            if(!pUnitMyBullet)
            {
                continue;
            }
            Rect myBulletRect = pUnitMyBullet->getBoundingBox();
            bool bCollide = monsterRect.intersectsRect(myBulletRect);
            if(bCollide && pUnitMonster->getDead() == false)
            {
                pUnitMyBullet->deadDelay();
                pUnitMonster->collide(pUnitMyBullet);
            }
        }
    }
    
    
    //更新敌人子弹
    std::map<int, BWUnit*>::iterator itEnemyBullet = _mapEnemyButtlet.begin();
    while (itEnemyBullet != _mapEnemyButtlet.end())
    {
        BWUnit* pUnitEnemyBullet = itEnemyBullet->second;
        ++itEnemyBullet;
        if(!pUnitEnemyBullet)
        {
            continue;
        }
        
        Rect monsterRect = pUnitEnemyBullet->getBoundingBox();
        bool bCollide = monsterRect.intersectsRect(heroRect);
        if(bCollide)
        {
            _pHero->collide(pUnitEnemyBullet);
            pUnitEnemyBullet->deadDelay();
        }
    }
    
}


void BWUnitManager::addToScene(BWUnit *pUnit)
{
    BWCombatLayer* pScene = (BWCombatLayer*)UIManager::shareInstance()->getUILayer(eUILayerId_Combat);
    if(!pScene)
    {
        return;
    }
    pScene->addUnit(pUnit);
}

BWUnit* BWUnitManager::createHero(UnitData* pInfo)
{
    pInfo->eType = EUnitType_Hero;
    _nUnitCount++;
    pInfo->nUuid = _nUnitCount;
    
    _pHero = new BWHero();
    _pHero->init(pInfo);
    return _pHero;
}

BWUnit*  BWUnitManager::createMonster(UnitData* pInfo)
{
    pInfo->eType = EUnitType_Monster;
    _nUnitCount++;
    pInfo->nUuid = _nUnitCount;
    
    BWUnit* pMonster = new BWMonster();
    pMonster->init(pInfo);
    _mapMonster.insert(std::make_pair(pInfo->nUuid, pMonster));
    return pMonster;
}

BWUnit*  BWUnitManager::createEnemyBullet(UnitData* pInfo)
{
    pInfo->eType = EUnitType_EnemyBullet;
    _nUnitCount++;
    pInfo->nUuid = _nUnitCount;
    
    BWUnit* pUnit = new BWBullet();
    pUnit->init(pInfo);
    _mapEnemyButtlet.insert(std::make_pair(pInfo->nUuid, pUnit));
    return pUnit;
}

BWUnit*  BWUnitManager::createItem(UnitData* pInfo)
{
    pInfo->eType = EUnitType_Item;
    _nUnitCount++;
    pInfo->nUuid = _nUnitCount;
    
    BWUnit* pUnit = new BWItem();
    pUnit->init(pInfo);
    _mapItem.insert(std::make_pair(pInfo->nUuid, pUnit));
    return pUnit;
}

BWUnit*  BWUnitManager::createMyBullet(UnitData* pInfo)
{
    pInfo->eType = EUnitType_HeroBullet;
    _nUnitCount++;
    pInfo->nUuid = _nUnitCount;
    
    BWUnit* pUnit = new BWBullet();
    pUnit->init(pInfo);
    _mapHeroButtlet.insert(std::make_pair(pInfo->nUuid, pUnit));
    return pUnit;
}

BWUnit* BWUnitManager::getMonster(int nUuId)
{
    std::map<int, BWUnit*>:: iterator it = _mapMonster.find(nUuId);
    if(it != _mapMonster.end())
    {
        return it->second;
    }
    return NULL;
}

void BWUnitManager::deleteUnitDelay(BWUnit* pUnit)
{
    if(!pUnit)
    {
        return ;
    }
    _vNeedDeleteUnit.push_back(pUnit);
}

void BWUnitManager::deleteAllUnitDelay()
{
    _vNeedDeleteUnit.clear();

    std::map<int, BWUnit*>:: iterator itMonster = _mapMonster.begin();
    while (itMonster != _mapMonster.end())
    {
        _vNeedDeleteUnit.push_back(itMonster->second);
        ++itMonster;
    }
}

void BWUnitManager::deleteAllUnit()
{
}

int BWUnitManager::getAllCterNum()
{
    int nNum = _mapMonster.size();
    return nNum;
}

//EUnitType_Unknown       =0,
//EUnitType_Hero          =1,
//EUnitType_Item          =2,
//EUnitType_Monster       =3,
//EUnitType_EnemyBullet   =4,
//EUnitType_MyBullet      =5,


void  BWUnitManager::deleteUnit(BWUnit* pUnit)
{
    switch (pUnit->getUnitType())
    {
        case EUnitType_Hero:
        {
        }
            break;
        case EUnitType_Monster:
        {
            deleteMonster(pUnit->getUuId());
        }
            break;
        case EUnitType_EnemyBullet:
        {
            deleteEnemyBullet(pUnit->getUuId());
        }
            break;
        case EUnitType_HeroBullet:
        {
            deleteMyBullet(pUnit->getUuId());
        }
            break;
        default:
            break;
    }
}
void BWUnitManager::deleteMonster(int nUuId)
{
    std::map<int, BWUnit*>:: iterator it = _mapMonster.find(nUuId);
    if(it != _mapMonster.end())
    {
        BWUnit* pBWUnit = it->second;
        if(!pBWUnit)
            return;
        pBWUnit->remove();
        delete pBWUnit;
        pBWUnit = NULL;
        _mapMonster.erase(it);
    }
}

void BWUnitManager::deleteEnemyBullet(int nUuId)
{
    std::map<int, BWUnit*>:: iterator it = _mapEnemyButtlet.find(nUuId);
    if(it != _mapEnemyButtlet.end())
    {
        BWUnit* pBWUnit = it->second;
        if(!pBWUnit)
            return;
        pBWUnit->remove();
        delete pBWUnit;
        pBWUnit = NULL;
        _mapEnemyButtlet.erase(it);
    }
}

void BWUnitManager::deleteMyBullet(int nUuId)
{
    std::map<int, BWUnit*>:: iterator it = _mapHeroButtlet.find(nUuId);
    if(it != _mapHeroButtlet.end())
    {
        BWUnit* pBWUnit = it->second;
        if(!pBWUnit)
        {
            return;
        }
        pBWUnit->remove();
        delete pBWUnit;
        pBWUnit = NULL;
        _mapHeroButtlet.erase(it);
    }
}

void BWUnitManager::createMonsterDelay(UnitData* pInfo)
{
    _vCreateMonsterDelay.push_back(*pInfo);
}

void BWUnitManager::createHeroBulletDelay(UnitData* pInfo)
{
    _vCreateHeroBulletDelay.push_back(*pInfo);
}

void BWUnitManager::playAction(Node* pSprite,ActionData* pActionData)
{
    
    int totalRepeatCount = pActionData->repeatCount;
    ActionType actType = pActionData->actType;
    
    int totalReverse = pActionData->reverseFlag;
    int totalRepeatReverse = pActionData->repeatReverseFlag;
    
    Vector<FiniteTimeAction*> vActionArray;
    
    if(pActionData->movData.order != 0)
    {
        moveData  movData = pActionData->movData;
        float moveDuration = movData.duration;
        Point endPoint = movData.endPoint;
        BWMoveBy* moveBy = BWMoveBy::create(moveDuration, endPoint);
        
        int reverse = movData.reverseFlag;
        int repeatCount = movData.repeatCount;
        int repeatReverse = movData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(moveBy, repeatCount);
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = moveBy->reverse();
            FiniteTimeAction* sequence = CCSequence::create(moveBy,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(movData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(movData.order);
            vActionArray.pushBack(sequence);
        }
    }
    
    if(pActionData->bezData.order != 0)
    {
        bezierData  bezData = pActionData->bezData;
        float bezierDuration = bezData.duration;
        BWBezierConfig config;
        config.controlPoint_1 = bezData.onePoint;
        config.controlPoint_2 = bezData.twoPoint;
        config.endPosition = bezData.endPoint;
        BWBezierBy* bezierBy = BWBezierBy::create(bezierDuration, config);
        
        int reverse = bezData.reverseFlag;
        int repeatCount = bezData.repeatCount;
        int repeatReverse = bezData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(bezierBy, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = bezierBy->reverse();
            FiniteTimeAction* sequence = CCSequence::create(bezierBy,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(bezData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(bezData.order);
            vActionArray.pushBack(sequence);
        }
        
    }
    if(pActionData->jumData.order != 0)
    {
        jumpData jumData = pActionData->jumData;
        float duration = jumData.duration;
        float height = jumData.height;
        Point endPoint = jumData.endPoint;
        int jumpCount = jumData.jumCount;
        JumpBy* jumpBy = CCJumpBy::create(duration, endPoint, height, jumpCount);
        
        int reverse = jumData.reverseFlag;
        int repeatCount = jumData.repeatCount;
        int repeatReverse = jumData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(jumpBy, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = jumpBy->reverse();
            FiniteTimeAction* sequence = CCSequence::create(jumpBy,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(jumData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(jumData.order);
            vActionArray.pushBack(sequence);
        }
    }
    if(pActionData->scaData.order != 0)
    {
        scaleData scaData = pActionData->scaData;
        float duration = scaData.duration;
        float scalX = scaData.sx;
        float scalY = scaData.sy;
        ScaleBy* scaleBy = CCScaleBy::create(duration, scalX,scalY);
        
        int reverse = scaData.reverseFlag;
        int repeatCount = scaData.repeatCount;
        int repeatReverse = scaData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(scaleBy, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = scaleBy->reverse();
            FiniteTimeAction* sequence = CCSequence::create(scaleBy,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(scaData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(scaData.order);
            vActionArray.pushBack(sequence);
        }
    }
    if(pActionData->rotData.order != 0)
    {
        rotateData rotData = pActionData->rotData;
        float duration = rotData.duration;
        float angle = rotData.angle;
        RotateBy* rotateBy = CCRotateBy::create(duration, angle);
        
        int reverse = rotData.reverseFlag;
        int repeatCount = rotData.repeatCount;
        int repeatReverse = rotData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(rotateBy, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = rotateBy->reverse();
            FiniteTimeAction* sequence = CCSequence::create(rotateBy,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(rotData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(rotData.order);
            vActionArray.pushBack(sequence);
        }
        
    }
    if(pActionData->tinData.order != 0)
    {
        tintData tinData = pActionData->tinData;
        float duration = tinData.duration;
        float red = tinData.deltaRed;
        float green = tinData.deltaGreen;
        float blue = tinData.deltaBlue;
        
        TintBy* tintBy = CCTintBy::create(duration, red, green, blue);
        
        int reverse = tinData.reverseFlag;
        int repeatCount = tinData.repeatCount;
        int repeatReverse = tinData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(tintBy, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = tintBy->reverse();
            FiniteTimeAction* sequence = CCSequence::create(tintBy,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(tinData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(tinData.order);
            vActionArray.pushBack(sequence);
        }
    }
    if(pActionData->fadInData.order != 0)
    {
        fadeInData fadInData = pActionData->fadInData;
        float duration = fadInData.duration;
        FadeIn* fadeIn = CCFadeIn::create(duration);
        
        int reverse = fadInData.reverseFlag;
        int repeatCount = fadInData.repeatCount;
        int repeatReverse = fadInData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(fadeIn, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = fadeIn->reverse();
            FiniteTimeAction* sequence = CCSequence::create(fadeIn,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(fadInData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(fadInData.order);
            vActionArray.pushBack(sequence);
        }
    }
    if(pActionData->fadOutData.order != 0)
    {
        fadeOutData fadOutData = pActionData->fadOutData;
        float dutation = fadOutData.duration;
        FadeOut* fadeOut = CCFadeOut::create(dutation);
        
        int reverse = fadOutData.reverseFlag;
        int repeatCount = fadOutData.repeatCount;
        int repeatReverse = fadOutData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(fadeOut, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = fadeOut->reverse();
            FiniteTimeAction* sequence = CCSequence::create(fadeOut,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(fadOutData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(fadOutData.order);
            vActionArray.pushBack(sequence);
        }
    }
    if(pActionData->bliData.order != 0)
    {
        blinkData bliData = pActionData->bliData;
        float duration = bliData.duration;
        int count = bliData.count;
        Blink* blink = CCBlink::create(duration, count);
        
        int reverse = bliData.reverseFlag;
        int repeatCount = bliData.repeatCount;
        int repeatReverse = bliData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(blink, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = blink->reverse();
            FiniteTimeAction* sequence = CCSequence::create(blink,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(bliData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(bliData.order);
            vActionArray.pushBack(sequence);
        }
    }
    if(pActionData->skeData.order != 0)
    {
        skewData skeData = pActionData->skeData;
        float duration = skeData.duration;
        float skewX = skeData.deltaSkewX;
        float skewY = skeData.deltaSkewY;
        SkewBy* skew = CCSkewBy::create(duration, skewX, skewY);
        
        int reverse = skeData.reverseFlag;
        int repeatCount = skeData.repeatCount;
        int repeatReverse = skeData.repeatReverseFlag;
        Repeat* repeat=NULL;
        if(reverse == 0)
        {
            repeat = CCRepeat::create(skew, repeatCount);
            
        }
        else if(reverse == 1)
        {
            ActionInterval* reverse = skew->reverse();
            FiniteTimeAction* sequence = CCSequence::create(skew,reverse,NULL);
            repeat = CCRepeat::create(sequence, repeatCount);
        }
        if(repeatReverse == 0)
        {
            repeat->setTag(skeData.order);
            vActionArray.pushBack(repeat);
            
        }
        else if(repeatReverse == 1)
        {
            ActionInterval* reverse = repeat->reverse();
            FiniteTimeAction* sequence = CCSequence::create(repeat,reverse,NULL);
            sequence->setTag(skeData.order);
            vActionArray.pushBack(sequence);
        }
    }
    if(pActionData->delayData.order != 0)
    {
        delayTimeData delayData = pActionData->delayData;
        float duration = delayData.duration;
        
        
        DelayTime* delayTime = CCDelayTime::create(duration);
        delayTime->setTag(delayData.order);
        vActionArray.pushBack(delayTime);
        
    }
    
    for(int i=0; i<vActionArray.size(); ++i)
    {
        FiniteTimeAction* act = (FiniteTimeAction*)vActionArray.at(i);
        int actIndex = act->getTag()-1;
        if(i != actIndex)
        {
            vActionArray.swap(i, actIndex);
        }
    }
    
    if(vActionArray.size() != 0)
    {
        FiniteTimeAction* totalFiniteTimeAction = NULL;
        switch (actType)
        {
            case AT_SEQ:
            {
                totalFiniteTimeAction = Sequence::create(vActionArray);
                
            }
                break;
            case AT_SPAWN:
            {
                totalFiniteTimeAction = Spawn::create(vActionArray);
            }
                break;
                
            default:
                break;
        }
        
        if(totalRepeatCount != -1)
        {
            Repeat* totalRepeat = NULL;
            if(totalReverse == 0)
            {
                totalRepeat = CCRepeat::create(totalFiniteTimeAction, totalRepeatCount);
            }
            else if(totalReverse == 1)
            {
                
                FiniteTimeAction* totalReverse = totalFiniteTimeAction->reverse();
                FiniteTimeAction* totalSeq = CCSequence::create(totalFiniteTimeAction,totalReverse,NULL);
                totalRepeat = CCRepeat::create(totalSeq, totalRepeatCount);
            }
            if(totalRepeatReverse == 0)
            {
                FiniteTimeAction*  totalRepeatReverse = totalRepeat->reverse();
                FiniteTimeAction* editSeq = CCSequence::create(totalRepeat,totalRepeatReverse,NULL);
                editSeq->setTag(EDIT_MOVEACTION_TAG);
                pSprite->runAction(editSeq);
            }
            else if(totalRepeatReverse ==1)
            {
                FiniteTimeAction* totalRepeatReverse = totalRepeat->reverse();
                FiniteTimeAction* totalRepeatSeq = CCSequence::create(totalRepeat,totalRepeatReverse,NULL);
                
                FiniteTimeAction* totalRepeatSeqReverse = totalRepeatSeq->reverse();
                FiniteTimeAction* editSeq = CCSequence::create(totalRepeatSeq,totalRepeatSeqReverse,NULL);
                editSeq->setTag(EDIT_MOVEACTION_TAG);
                pSprite->runAction(editSeq);
            }
        }
        else if(totalRepeatCount == -1)
        {
            totalRepeatCount = 1;
            Repeat *totalRepeatEver = NULL;
            if(totalReverse == 0)
            {
                totalRepeatEver  = CCRepeat::create((ActionInterval*)totalFiniteTimeAction,totalRepeatCount);
                
            }
            else if(totalReverse == 1)
            {
                
                FiniteTimeAction* totalReverse = totalFiniteTimeAction->reverse();
                FiniteTimeAction* totalSeq = CCSequence::create(totalFiniteTimeAction,totalReverse,NULL);
                totalRepeatEver = CCRepeat::create((ActionInterval*)totalSeq,totalRepeatCount);
            }
            FiniteTimeAction* totalRepeatEverReverse = totalRepeatEver->reverse();
            FiniteTimeAction* editSeq = CCSequence::create(totalRepeatEver,totalRepeatEverReverse,NULL);
            editSeq->setTag(EDIT_MOVEACTION_TAG);
            pSprite->runAction(editSeq);
        }
    }
}



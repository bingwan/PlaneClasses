

#include "BuffProcessInherit.h"
#include "BuffObject.h"
#include "BuffManager.h"
#include "ResManager.h"

//================================================================
//================================================================
Buff001::Buff001(){}
Buff001::~Buff001(){}

bool Buff001::isContinued()
{
	return true;
}
bool Buff001::isOnced()
{
	return false;
}
bool Buff001::onStartProcessBuff(BWUnit* pBWUnit,BuffObject* pBuff)
{
	if ( NULL == pBuff || NULL == pBWUnit )
	{
		return false;
	}
    float fDur = pBuff->getBuffParam(eParamEnum_Dur);
    pBuff->setContinuTime(fDur);
    
    float fSpeedPercent = pBuff->getBuffParam(eParamEnum_Speeed);

	return true;
}
bool Buff001::onTickProcessBuff(BWUnit* pBWUnit,BuffObject* pBuff,float dt)
{
	if ( NULL == pBuff || NULL == pBWUnit )
	{
		return false;
	}
    
    float fOldTime = pBuff->getElapsedTime();
    if(fOldTime >= pBuff->getContinuTime())
    {
        pBuff->setFinished(true);
        onEndProcessBuff(pBWUnit,pBuff);
    }
    pBuff->setElapsedTime(fOldTime + dt);
        
	return true;
}
bool Buff001::onEndProcessBuff(BWUnit* pBWUnit,BuffObject* pBuff)
{
	if ( NULL == pBuff || NULL == pBWUnit )
	{
		return false;
	}   

    
	return true;
}

//================================================================
//================================================================
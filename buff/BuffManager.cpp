

#include "BuffManager.h"
#include "BuffObject.h"
#include "BuffProcess.h"
#include "BuffProcessInherit.h"
#include "CCAPI.h"
#include "ResManager.h"

static BuffManager* s_pBufferManager = NULL;

BuffManager* BuffManager::share()
{
    if( NULL == s_pBufferManager)
    {
        s_pBufferManager = new BuffManager();
    }
    return s_pBufferManager;
}
BuffManager::BuffManager()
{
}

BuffManager::~BuffManager()
{
}

bool BuffManager::init()
{
    intBuffProcess();
	return true;
}

void BuffManager::intBuffProcess()
{
    m_mapBuffProcess[Buff001::BUFF_ID] = new Buff001();

}

BuffObject* BuffManager::addBuffObject( Character* pCharacter,int buffTemplateId,unsigned int& buffUid, bool bTick)
{
	if(pCharacter == NULL || buffTemplateId ==  eBufferType_UNKNOWN)
		return NULL;
    BuffObject* pBuff = createBuffObject(buffTemplateId);
    pBuff->setTick(bTick);
    buffUid = pBuff->getUid();
    return pBuff;
}

BuffObject* BuffManager::createBuffObject(int nBuffId)
{
    
    BuffTabData* pBuffData = ResManager::shareResManager()->getBuffData(nBuffId);
    if(!pBuffData)
        return NULL;
    BuffObject* pBuff = new  BuffObject();
	pBuff->setBuffTemplateId(nBuffId);
    return pBuff;
}

BuffProcess* BuffManager::getBuffProcess( BuffObject* pBuff)
{
	BuffTabData* pBuffData = ResManager::shareResManager()->getBuffData(pBuff->getBuffTemplateId());
	if(pBuffData)
	{
		std::map<int, BuffProcess*>::iterator it = m_mapBuffProcess.find(pBuffData->eType);
		if (it != m_mapBuffProcess.end())
		{
			return it->second;
		}
	}
	return NULL;
}

void  BuffManager::deleteBuff(BuffObject* pBuff)
{
    if(!pBuff)
        return;
    if(pBuff)
    {
        delete pBuff;
        pBuff = NULL;
    }
}


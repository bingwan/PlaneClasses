

#include "BuffObject.h"
#include "BuffManager.h"
#include "ResManager.h"

#define MAX_BUFF_PARAM_NUM 10


BuffObject::BuffObject():
m_BuffTemplateId(-1),
m_Finished(false),
m_ContinueTime(0),
m_ElapsedTime(0),
m_tickCount(0),
m_soundValue(0.f),
m_itemId(0),
m_bTick(true),
m_index(0)
{
}
BuffObject::~BuffObject()
{	
}

bool BuffObject::setBuffTemplateId(int buffId)
{
	BuffTabData* pBuffData = ResManager::shareResManager()->getBuffData(buffId);
    if(!pBuffData)
        return false;
    m_BuffTemplateId = pBuffData->nId;
	m_vParm.push_back(pBuffData->nParm1);
    m_vParm.push_back(pBuffData->nParm2);
    m_vParm.push_back(pBuffData->nParm3);
    m_vParm.push_back(pBuffData->nParm4);
    m_vParm.push_back(pBuffData->nParm5);    
	return false;
}
float BuffObject::getBuffParam(int index)
{
    if(index>= m_vParm.size() || index<0)
    {
        return 0;
    }
	return m_vParm[index];
}
bool BuffObject::setBuffParam(int index,std::string param)
{
    return true;
}





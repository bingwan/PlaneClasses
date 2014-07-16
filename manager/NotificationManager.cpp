

#include "NotificationManager.h"
#include "UIManager.h"

NotificationManager* NotificationManager::shareInstance()
{
    static NotificationManager* s_NotiInstance = NULL;
    if(NULL == s_NotiInstance)
    {
        s_NotiInstance = new NotificationManager();
    }
    return s_NotiInstance;
}
//=============================================================
//=============================================================
NotificationManager::NotificationManager()
{}
//=============================================================
//=============================================================
NotificationManager::~NotificationManager()
{}
//=============================================================
//=============================================================
void NotificationManager::pushCMD(eGAME_CMD_ID eCmdId)
{
    std::vector<std::string> empty;
    pushCMD(eCmdId,empty);
}
//=============================================================
//=============================================================
void NotificationManager::pushCMD(eGAME_CMD_ID eCmdId,float fParm,float fParm2)
{
    std::vector<std::string> vParm;
    char chrParm[64];
    sprintf(chrParm, "%f",fParm);
    vParm.push_back(chrParm);
    
    char chrParm2[64];
    sprintf(chrParm2, "%f",fParm2);
    vParm.push_back(chrParm2);
    pushCMD(eCmdId,vParm);
}
//=============================================================
//=============================================================
void NotificationManager::pushCMD(eGAME_CMD_ID eCmdId,std::vector<std::string> vParm)
{
    CommandData* pCommandData = getCommand(eCmdId);
    if(!pCommandData)
    {
        return;
    }
    pCommandData->vCommandParmData = vParm;    
    
    m_vCommandParmData = pCommandData->vCommandParmData;
    for(int i=0;i<pCommandData->vLayerCommandData.size();i++)
    {
        LayerCommandDta* pLayerCommand = &pCommandData->vLayerCommandData[i];
        if(pLayerCommand)
        {
            if(pLayerCommand->pTarget && pLayerCommand->pFunc)
            {
                Object* pTarget = pLayerCommand->pTarget;
                if(pTarget)
                {
                    (pTarget->*pLayerCommand->pFunc)(NULL,NULL);
                }
            }
        }
    }
    m_vCommandParmData.clear();
}
//=============================================================
//=============================================================
int  NotificationManager::haveToPush(CommandData* pCommandData)
{
    for(int i=0;i<m_vToPushComand.size();i++)
    {
        if(pCommandData == m_vToPushComand[i])
        {
            return i;
        }
    }
    return -1;
}
//=============================================================
//=============================================================
void NotificationManager::removeCMD(eGAME_CMD_ID eCmdId,Object* pObj)
{
    CommandData* pCommandData = getCommand(eCmdId);
    if(pCommandData)
    {
        int nDelIndex = -1;
        for(int i=0;i<pCommandData->vLayerCommandData.size();i++)
        {
            LayerCommandDta* pLayerCommand = &pCommandData->vLayerCommandData[i];
            if(pLayerCommand)
            {
                if(pLayerCommand->pTarget ==  pObj )
                {
                    pLayerCommand->pTarget = NULL;
                    nDelIndex = i;
                }
            }
        }
        if(nDelIndex != -1)
        {
            pCommandData->vLayerCommandData.erase(pCommandData->vLayerCommandData.begin() + nDelIndex);
        }
    }
}
//=============================================================
//=============================================================
void NotificationManager::update(float dt)
{
}
//=============================================================
//=============================================================
void NotificationManager::removePushed(CommandData* pComand)
{
    int index = haveToPush(pComand);
    if(index != -1)
    {
        m_vToPushComand.erase(m_vToPushComand.begin() + index);
    }
}
//=============================================================
//=============================================================
const char* NotificationManager::getCMDParm(int nIndex)
{
    if(nIndex >= m_vCommandParmData.size())
    {
        return NULL;
    }
    return m_vCommandParmData[nIndex].c_str();
}
//=============================================================
//=============================================================
void NotificationManager::registerCmd(Object* pTarget, eGAME_CMD_ID cmdId,SEL_CallFuncND pFunc)
{
    CommandData* pCommandData = getCommand(cmdId);
    if(pCommandData)
    {
        LayerCommandDta layerCommandDta;
        layerCommandDta.pTarget = pTarget;
        layerCommandDta.pFunc = pFunc;
        pCommandData->vLayerCommandData.push_back(layerCommandDta);
    }
    else
    {
        LayerCommandDta layerCommandDta;
        layerCommandDta.pTarget = pTarget;
        layerCommandDta.pFunc = pFunc;
        
        CommandData commandData;
        commandData.nCommandId = cmdId;
        commandData.vLayerCommandData.push_back(layerCommandDta);
        m_mapCommand.insert(std::make_pair(commandData.nCommandId, commandData));
    }
}
//=============================================================
//=============================================================
CommandData* NotificationManager::getCommand(eGAME_CMD_ID cmdId)
{
    std::map<eGAME_CMD_ID, CommandData>::iterator it = m_mapCommand.find(cmdId);
    if(it != m_mapCommand.end())
    {
        return &it->second;
    }
    return NULL;
}
//=============================================================
//=============================================================







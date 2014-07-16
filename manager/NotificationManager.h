

#ifndef __NotificationManager__
#define __NotificationManager__

#include <iostream>
#include "cocos2d.h"
#include "CommonDef.h"
USING_NS_CC;

enum EventCmd
{
    eEventCmd_UnKnown = 0,
};

class NotificationManager : public Node
{
public:
    NotificationManager();
    virtual ~NotificationManager();
    
    static NotificationManager* shareInstance();
    void                    pushCMD(eGAME_CMD_ID eCmdId);
    void                    pushCMD(eGAME_CMD_ID eCmdId,float fParm,float fParm2=0);
    void                    pushCMD(eGAME_CMD_ID eCmdId,std::vector<std::string> vParm);
    const char*             getCMDParm(int nIndex);
    CommandData*            getCommand(eGAME_CMD_ID cmdId);
    void                    registerCmd(Object* pTarget,eGAME_CMD_ID cmdId,SEL_CallFuncND pFunc);
    
    virtual void            update(float dt);
    
    void                    removeCMD(eGAME_CMD_ID eCmdId,Object* pObj);
    
    void removePushed(CommandData* pComand);
    int haveToPush(CommandData* pCommandData);

private:
    std::map<eGAME_CMD_ID, CommandData>  m_mapCommand;
    std::vector<std::string>              m_vCommandParmData;
    std::vector<CommandData*>             m_vToPushComand;
};


#endif /* defined(__NotificationManager__) */

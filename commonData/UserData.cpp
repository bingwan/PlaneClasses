

/*
 *
 *  Created by wangbin
 *
 */

#include "UserData.h"
#include "CommonDef.h"
#include "NotificationManager.h"
#include "RootLayer.h"
#include "ResManager.h"
#include "CCAPI.h"
#include "BWStreamFile.h"

UserData* UserData::shareUserData()
{
    static UserData* s_UIInstance = NULL;
    if(NULL == s_UIInstance)
    {
        s_UIInstance = new UserData();
    }
    return s_UIInstance;
}
//=============================================================
//=============================================================
UserData::UserData()
{
    CleanUp();
}

//=============================================================
//=============================================================
UserData::~UserData()
{
}

void UserData::CleanUp()
{

}
//=============================================================
//=============================================================
bool UserData::initUser(const char* szIp,int nPort)
{
   
    return false;
}

bool UserData::socketUpdate(float dt)
{
    return true;
}

//=============================================================
//=============================================================
void UserData::update(float dt)
{
//    if(!_bAbleUpdateSocket)
//        return;
//    
//    bool bToNet = false;
//    if(isConnecting())
//    {
//        if(socketUpdate(dt))
//        {
//            bToNet = true;
//        }
//        else
//        {
//             bToNet = false;
//        }
//    }
//    if(bToNet==false)
//    {
//        log("掉线");
//        _bAbleUpdateSocket = false;
//        disConnect();
//        NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowSelRole);
//    }
}




TroopData*  UserData::getTroopInCombatData(int nIndex)
{
    if(nIndex <0 || nIndex >= _vTroopInCombat.size())
    {
        return NULL;
    }
    return &_vTroopInCombat[nIndex];
}










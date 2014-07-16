//
//  UserData.h
//  ESGame
//
//  Created by wangbin on 13-1-14.
//
//

#ifndef __UserData__
#define __UserData__
#include "CommonDef.h"
#include "cocos2d.h"
#include "CommonDef.h"

class UserData : public Ref
{
public:
    UserData();
    void CleanUp();
    virtual ~UserData();
    static UserData*                shareUserData();
    bool                            initUser(const char* szIp,int nPort);
    
    bool                            socketUpdate(float dt);
    virtual void                    update(float dt);
    bool                            isConnecting();
    bool                            connect();
    void                            setDungeonId(int nCamId){_nCamId = nCamId;}
    int                             getDungeonId(){return _nCamId;}
    void                            setAbleUpdateSocket(bool bAble){_bAbleUpdateSocket = bAble;}
    std::vector<TroopData>*         getTroopInCombat(){return &_vTroopInCombat;}
    TroopData*                      getTroopInCombatData(int nIndex);
    int                             getDunGroup(){return _nDunGroup;}
    void                            setDunGroup(int nGroupId){_nDunGroup = nGroupId; }
    void                            setUserId(uint64_t uId){_nUserId = uId;}
    uint64_t                        getUserId(){return _nUserId;}

    
    void                            setGameServerIp(std::string strIp){_strGameServerIp = strIp;};
    void                            setGameSeverPort(int  nPort){_nGameServerPort = nPort; };
    
    std::string                     getGameServerIp(){return _strGameServerIp;};
    int                             getGameServerPort(){return _nGameServerPort;};
    
    std::map<int,HeroData>*         getHeroBag(){return   &_mapHeroBag;}
    std::map<int,TroopData>*        getTroopBag(){return  &_mapTroopBag;}
    
    void                            setGold(int nGold){_nGold = nGold;}
    int                             getGold(){return _nGold;}
    
    void                            setDiamond(int nDiamond){_nDiamond = nDiamond;}
    int                             getDiamond(){return _nDiamond;}
    
    void                            setMagicKey(int nKey){_nMagicKey = nKey;}
    int                             getMagicKey(){return _nMagicKey;}
    
    void                            setNickName(std::string nickName){_strNickName = nickName;};
    std::string                     getNickName(){return _strNickName;}
    
    void                            setCreateRoleTabId(int nId){_nCreateRoleTabId = nId;}
    int                             getCreateRoleTabId(){return _nCreateRoleTabId;}
    
    void                            setAccount(std::string strAccount){_strAccount = strAccount;}
    std::string                     getAccount(){return _strAccount;}
    
    void                            setPass(std::string strPass){_strPass = strPass;}
    std::string                     getPsss(){return _strPass;}
    
    std::map<int,SkillData>*        getCombatSkill(){return &_mapSkill;};
    
    void setLevelId(int nLevelId){_nLevelId = nLevelId;}

    int getLevelId(){return _nLevelId;}
private:
    bool                                    _bAbleUpdateSocket;
    int                                     _nCamId;
    std::vector<TroopData>                  _vTroopInCombat;
    int                                     _nDunGroup;
    uint64_t                                _nUserId;
    std::string                             _strGameServerIp;
    int                                     _nGameServerPort;
    std::map<int,HeroData>                  _mapHeroBag;
    std::map<int,TroopData>                 _mapTroopBag;
    int                                     _nGold;
    int                                     _nDiamond;
    int                                     _nMagicKey;
    std::string                             _strNickName;
    int                                     _nCreateRoleTabId;
    std::string                             _strAccount;
    std::string                             _strPass;
    std::map<int,SkillData>                 _mapSkill;
    int _nLevelId;
    
};

#endif /* defined(__UserData__) */





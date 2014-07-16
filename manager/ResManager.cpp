

#include "ResManager.h"
#include "CommonDef.h"
#include "NotificationManager.h"
#include "RootLayer.h"
#include "CCAPI.h"


ResManager* ResManager::shareResManager()
{
    static ResManager* s_UIInstance = NULL;
    if(NULL == s_UIInstance)
    {
        s_UIInstance = new ResManager();
    }
    return s_UIInstance;
}

//=============================================================
//=============================================================
ResManager::ResManager()
{
}

//=============================================================
//=============================================================
ResManager::~ResManager()
{
}

//=============================================================
//=============================================================
void ResManager::init()
{
    loadLayersTab("layers.tab");
    loadSkillTab("skill.tab");
    loadEffectTab("effect.tab");
    loadBuffTab("buff.tab");
    loadCampaignTab("dungeon.tab");
    loadDiamondTab("diamond.tab");
    loadMonsterTab("monster.tab");
    loadLanguageTab("language.tab");
    loadHeroTab("hero.tab");
    loadBulletTab("bullet.tab");
}

bool ResManager::loadLayersTab(const char* szFileName)
{
    log("loadLayersTab");
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    //std::set<std::string>  pSet;
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        UILayerData* pTabData = (UILayerData*)it->second;
       // log("pTabDataeLayerId=%d",pTabData->eLayerId);
       // log("pTabDataZ=%d",pTabData->nZOrder);
        m_mapLayerData.insert(std::make_pair(pTabData->eLayerId, *pTabData));
        ++it;
    }
    //m_vAllString.push_back(pSet);
    delete Table;
    return true;
}
//=============================================================
//=============================================================
UILayerData* ResManager::getLayerData(eUILayerId eLayerId)
{
    std::map<eUILayerId, UILayerData>::iterator it = m_mapLayerData.find(eLayerId);
    if(it != m_mapLayerData.end())
    {
        return &it->second;
    }
    return NULL;
}

bool ResManager::loadSkillTab(const char* szFileName)
{
//    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
//    ResourcesPath.append("/");
//    ResourcesPath.append(szFileName);
//    LoadTable*  Table = new LoadTable();
//    Table->setStringSet(&m_vAllString);
//    Table->ReadFile(ResourcesPath);
//    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
//    if(!pMap)
//        return false;
//    std::map<int,TabElementData*>::const_iterator it = pMap->begin(); 
//    while(it != pMap->end())
//    {
//        TSkillData *pTabData = (TSkillData*)it->second;
//        log("SkillData=%d", pTabData->nID);
//        TSkillDetailData pDetail;
//        pDetail.setData(pTabData);
//        m_mapSkill.insert(std::make_pair(pDetail.nID, pDetail));
//        ++it;
//    }
//    delete Table;
//    return true;
}

//TSkillDetailData* ResManager::getSkillData(int nID)
//{
//    std::map<int,TSkillDetailData>::iterator it = m_mapSkill.find(nID);
//    if(it != m_mapSkill.end())
//    {
//        return &it->second;
//    }
//    return NULL;
//}


bool ResManager::loadBulletTab(const char *szFileName)
{
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        BulletTabData* pTabData = (BulletTabData*)it->second;
        log("BulletData=%d",pTabData->nId);
        m_mapBullet.insert(std::make_pair(pTabData->nId,*pTabData));
        ++it;
    }
    delete Table;
    return true;
}

BulletTabData* ResManager::getBulletTabData(int nId)
{
    std::map<int,BulletTabData>::iterator it = m_mapBullet.find(nId);
    if(it != m_mapBullet.end())
    {
        return &it->second;
    }
    return NULL;
}


bool ResManager::loadEffectTab(const char* szFileName)
{
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        EffectTabData* pTabData = (EffectTabData*)it->second;
        log("TEffectData=%d",pTabData->nID);
        m_mapEffect.insert(std::make_pair(pTabData->nID, *pTabData));
        ++it;
    }
    delete Table;
    return true;
}

EffectTabData* ResManager::getEffectData(int nID)
{
    std::map<int,EffectTabData>::iterator it = m_mapEffect.find(nID);
    if(it != m_mapEffect.end())
    {
        return &it->second;
    }
    return NULL;
}


bool ResManager::loadBuffTab(const char* szFileName)
{
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        BuffTabData* pTabData = (BuffTabData*)it->second;
        m_mapBuff.insert(std::make_pair(pTabData->nId, *pTabData));
        ++it;
    }
    delete Table;
    return true;
}

BuffTabData*  ResManager::getBuffData(int nId)
{
    std::map<int,BuffTabData>::iterator it = m_mapBuff.find(nId);
    if(it != m_mapBuff.end())
    {
        return &it->second;
    }
    return NULL;
}

bool ResManager::loadCampaignTab(const char* szFileName)
{
    std::string strDocPath = FileUtils::getInstance()->getWritablePath();
    strDocPath.append("/");
    strDocPath.append(szFileName);
    
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        DungeonTabData* pTabData = (DungeonTabData*)it->second;
        log("DungeonData=%d",pTabData->nId);
        DungeonTabDataDetail detail;
        detail.setData(pTabData);
        m_mapDungeon.insert(std::make_pair(detail.nId, detail));
        ++it;
    }
    delete Table;
    return true;
}

DungeonTabDataDetail* ResManager::getDungenonData(int nId)
{
    std::map<int,DungeonTabDataDetail>::iterator it =  m_mapDungeon.find(nId);
    if(it != m_mapDungeon.end())
    {
        return &it->second;
    }
    return NULL;
}
//
//bool ResManager::loadGroupTab(const char* szFileName)
//{
//    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
//    ResourcesPath.append("/");
//    ResourcesPath.append(szFileName);
//    LoadTable*  Table = new LoadTable();
//    Table->setStringSet(&m_vAllString);
//    Table->ReadFile(ResourcesPath);
//    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
//    if(!pMap)
//        return false;
//    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
//    while(it != pMap->end())
//    {
//        GroupTabData* pTabData = (GroupTabData*)it->second;
//        GroupTabDataDetail detail;
//        detail.setData(pTabData);
//        log("GroupTabData=%d",detail.nId);
//
//        m_mapGroupMonster.insert(std::make_pair(detail.nId, detail));
//        ++it;
//    }
//    delete Table;
//    return true;
//}
//GroupTabDataDetail*  ResManager::getGroupData(int nId)
//{
//    std::map<int,GroupTabDataDetail>::iterator it =  m_mapGroupMonster.find(nId);
//    if(it != m_mapGroupMonster.end())
//    {
//        return &it->second;
//    }
//    return NULL;
//}

bool ResManager::loadHeroTab(const char *szFileName)
{
    std::string strResPath = CCAPI::shareCCAPI()->getResourcePath();
    strResPath.append("/");
    strResPath.append(szFileName);
    
    LoadTable *pTable = new LoadTable();
    pTable->setStringSet(&m_vAllString);
    pTable->ReadFile(strResPath);
    
    const std::map<int, TabElementData*> *pMap = pTable->getTabMap();
    if(!pMap)
    {
        return false;
    }
    std::map<int, TabElementData*>::const_iterator itr = pMap->begin();
    while(itr != pMap->end())
    {
        HeroTabData *pData = (HeroTabData *)itr->second;
        log("THeroDataID = %d", pData->nId);
        m_mapHero.insert(std::make_pair(pData->nId, *pData));
        itr++;
    }
    delete pTable;
    return true;
}

HeroTabData*  ResManager::getHeroTabData(int nId)
{
    std::map<int,HeroTabData>::iterator it =  m_mapHero.find(nId);
    if(it != m_mapHero.end())
    {
        return &it->second;
    }
    return NULL;
}

bool ResManager::loadDiamondTab(const char* szFileName)
{
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        EDiamondTabData* pTabData = (EDiamondTabData*)it->second;
        log("EDiamondTabData=%d",pTabData->nId);
        m_mapDiamond.insert(std::make_pair(pTabData->nId, *pTabData));
        ++it;
    }
    delete Table;
    return true;
}

EDiamondTabData* ResManager::getDiamondData(int nId)
{
    std::map<int,EDiamondTabData>::iterator it =  m_mapDiamond.find(nId);
    if(it != m_mapDiamond.end())
    {
        return &it->second;
    }
    return NULL;
}

bool ResManager::loadMonsterTab(const char *szFileName)
{
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        MonsterTabData* pTabData = (MonsterTabData*)it->second;
        log("MonsterTabData=%d",pTabData->nID);
        m_mapMonster.insert(std::make_pair(pTabData->nID, *pTabData));
        ++it;
    }
    delete Table;
    return true;
}


MonsterTabData* ResManager::getMonsterData(int nId)
{
    std::map<int,MonsterTabData>::iterator it =  m_mapMonster.find(nId);
    if(it != m_mapMonster.end())
    {
        return &it->second;
    }
    return NULL;
}

bool ResManager::loadLanguageTab(const char *szFileName)
{
    std::string ResourcesPath = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(szFileName);
    LoadTable*  Table = new LoadTable();
    Table->setStringSet(&m_vAllString);
    Table->ReadFile(ResourcesPath);
    const  std::map<int,TabElementData*>* pMap = Table->getTabMap();
    if(!pMap)
        return false;
    std::map<int,TabElementData*>::const_iterator it = pMap->begin();
    while(it != pMap->end())
    {
        LanguageTabData* pTabData = (LanguageTabData*)it->second;
        log("LanguageTabData=%s",pTabData->pszKey);
        m_mapLanguage.insert(std::make_pair(pTabData->pszKey, *pTabData));
        ++it;
    }
    delete Table;
    return true;
}
const char* ResManager::getStringForKey(const char* pszKey)
{
    std::map<std::string, LanguageTabData>::iterator it =  m_mapLanguage.find(pszKey);
    if(it != m_mapLanguage.end())
    {
        LanguageTabData* pLanguage = &it->second;
        if(LANGUAGE_TYPE == LANGUAGE_CN)
        {
            return pLanguage->pszCnString;
        }
        else if(LANGUAGE_TYPE == LANGUAGE_EN)
        {
           // return pLanguage->pszEnString;
        }
    }
    return NULL;
}



bool ResManager::loadLevelXml(int nLevel,LevelData* pLevelData)
{
	char levelName[COMMON_STRING_SIZE] = {0,0};
	sprintf(levelName,"%d_npc.xml", nLevel);
    XMLDocument tempDoc;

	std::string DocumentsPath = FileUtils::getInstance()->getWritablePath();
    DocumentsPath.append(levelName);
	std::string ResourcesPath  = CCAPI::shareCCAPI()->getResourcePath();
    ResourcesPath.append("/");
    ResourcesPath.append(levelName);
	if(tempDoc.LoadFile(DocumentsPath.c_str()) != XML_SUCCESS)
	{
		if(tempDoc.LoadFile(ResourcesPath.c_str()) != XML_SUCCESS)
		{
            log("error=loadLevelXml=nLevel=%d",nLevel);
			return false;
		}
	}
	XMLElement* pRoot = tempDoc.RootElement();
	if(!pRoot)
    {
		return false;
    }
    XMLElement* edit_npcs = pRoot->FirstChildElement("edit_npcs");
    if(!edit_npcs)
    {
        return false;
    }
    
    pLevelData->nScreenCount = pRoot->IntAttribute("screen_count");

    
    XMLElement* pNpcEle = edit_npcs->FirstChildElement("npc");
    while(pNpcEle)
    {
        NpcData  npcData;
        
        npcData.index               = pNpcEle->IntAttribute("index");
        npcData.nTabId              = pNpcEle->IntAttribute("npc_id");
        npcData.zOrder              = pNpcEle->IntAttribute("zorder");
        npcData.pos.x               = pNpcEle->IntAttribute("posx");
        npcData.pos.y               = pNpcEle->IntAttribute("posy");
        npcData.rotate              = pNpcEle->FloatAttribute("rotate");
        npcData.scale               = pNpcEle->FloatAttribute("scale");
        npcData.opacity             = pNpcEle->FloatAttribute("opacity");
        npcData.triggerDistance     = pNpcEle->IntAttribute("trigger_dist");
        
        
        ActionData* pAct = &npcData.actData;
        readActionData(pNpcEle, pAct);
        
        std::map<int,SlotData>* pMapSlotData = &npcData.mapSlotData;
        readBulletData(pNpcEle, pMapSlotData);
        
        pLevelData->mapLevelNpc.insert(std::make_pair(npcData.index, npcData));
        pNpcEle = pNpcEle->NextSiblingElement("npc");
    }

    
    
    return true;
}

void ResManager::readActionData(XMLElement* pNpc,ActionData* pActionData)
{
    XMLElement* pActions = pNpc->FirstChildElement("actions");
    if(pActions)
    {
        if(pActionData == NULL)
            pActionData = new ActionData;
        
        int repeatCount = 1;
        ActionType Type = AT_UNKNOWN;
        
        repeatCount = pActions->IntAttribute("repeatcount");
        
        if(repeatCount == 0)
        {
            repeatCount=1;
        }
        pActionData->repeatCount = repeatCount;
        int type = 0;
        type = pActions->IntAttribute("ActionType");
        Type = ActionType (type);
        pActionData->actType = Type;
        
        pActionData->reverseFlag = pActions->IntAttribute("reverse");
        
        pActionData->repeatReverseFlag = pActions->IntAttribute("repeatreverse");
        
        XMLElement* pAction = pActions->FirstChildElement("action");
        while (pAction)
        {
            int actType             = pAction->IntAttribute("type");
            int order               = pAction->IntAttribute("order");
            float fDuration         = pAction->FloatAttribute("duration");
            
            int reverse = 0;
            int repeatCount = 0;
            int repeatReverse = 0;
            
            reverse         = pAction->IntAttribute("reverse");
            repeatCount     = pAction->IntAttribute("repeatcount");
            repeatReverse   = pAction->IntAttribute("repeatreverse");
            
            switch (actType)
            {
                case AT_MOVE:
                {
                    pActionData->movData.reverseFlag = reverse;
                    pActionData->movData.repeatCount = repeatCount;
                    pActionData->movData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->movData.order = order;
                    pActionData->movData.duration = fDuration;
                    pActionData->movData.actType =(ActionType)actType;
                    
                    
                    Point endPoint;
                    endPoint.x = pAction->FloatAttribute("endposx");
                    endPoint.y = pAction->FloatAttribute("endposy");
                    pActionData->movData.endPoint = endPoint;
                    
                }
                    break;
                case AT_BEZIER:
                {
                    pActionData->bezData.reverseFlag = reverse;
                    pActionData->bezData.repeatCount = repeatCount;
                    pActionData->bezData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->bezData.order = order;
                    pActionData->bezData.duration = fDuration;
                    pActionData->bezData.actType = (ActionType)actType;
                    
                    Point onePoint;
                    Point twoPoint;
                    Point endPoint;

                    onePoint.x = pAction->FloatAttribute("bezieroneposx");
                    onePoint.y = pAction->FloatAttribute("bezieroneposy");
                    twoPoint.x = pAction->FloatAttribute("beziertwoposx");
                    twoPoint.y = pAction->FloatAttribute("beziertwoposy");
                    endPoint.x = pAction->FloatAttribute("bezierendposx");
                    endPoint.y = pAction->FloatAttribute("bezierendposy");
                    
                    pActionData->bezData.onePoint = onePoint;
                    pActionData->bezData.twoPoint = twoPoint;
                    pActionData->bezData.endPoint = endPoint;
                    
                }
                    break;
                case AT_JUMP:
                {
                    pActionData->jumData.reverseFlag = reverse;
                    pActionData->jumData.repeatCount = repeatCount;
                    pActionData->jumData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->jumData.order = order;
                    pActionData->jumData.duration = fDuration;
                    pActionData->jumData.actType = (ActionType)actType;
                    
                    int count = 0;
                    count = pAction->IntAttribute("jumpcount");
                                        
                    Point endPoint;
                    endPoint.x = pAction->FloatAttribute("jumpendposx");
                    endPoint.y = pAction->FloatAttribute("jumpendposy");
                    
                    pActionData->jumData.jumCount = count;
                    pActionData->jumData.height = pAction->FloatAttribute("jumpheight");
                    pActionData->jumData.endPoint = endPoint;
                }
                    break;
                case AT_SCALE:
                {
                    pActionData->scaData.reverseFlag = reverse;
                    pActionData->scaData.repeatCount = repeatCount;
                    pActionData->scaData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->scaData.order = order;
                    pActionData->scaData.duration = fDuration;
                    pActionData->scaData.actType = (ActionType)actType;
            
                    pActionData->scaData.sx =  pAction->FloatAttribute("scalex");
                    pActionData->scaData.sy =  pAction->FloatAttribute("scaley");
                    
                }
                    break;
                case AT_ROTATE:
                {
                    pActionData->rotData.reverseFlag = reverse;
                    pActionData->rotData.repeatCount = repeatCount;
                    pActionData->rotData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->rotData.order = order;
                    pActionData->rotData.duration = fDuration;
                    pActionData->rotData.actType = (ActionType)actType;
                    
                    pActionData->rotData.angle = pAction->FloatAttribute("angle");
                    
                }
                    break;
                case AT_TINT:
                {
                    pActionData->tinData.reverseFlag = reverse;
                    pActionData->tinData.repeatCount = repeatCount;
                    pActionData->tinData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->tinData.order = order;
                    pActionData->tinData.duration = fDuration;
                    pActionData->tinData.actType = (ActionType)actType;
                    
                    pActionData->tinData.deltaRed = pAction->IntAttribute("red");
                    pActionData->tinData.deltaRed = pAction->IntAttribute("green");
                    pActionData->tinData.deltaRed = pAction->IntAttribute("blue");
                    
                }
                    break;
                case AT_FADEIN:
                {
                    pActionData->fadInData.reverseFlag = reverse;
                    pActionData->fadInData.repeatCount = repeatCount;
                    pActionData->fadInData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->fadInData.order = order;
                    pActionData->fadInData.duration = fDuration;
                    pActionData->fadInData.actType = (ActionType)actType;
                }
                    break;
                case AT_FADEOUT:
                {
                    pActionData->fadOutData.reverseFlag = reverse;
                    pActionData->fadOutData.repeatCount = repeatCount;
                    pActionData->fadOutData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->fadOutData.order = order;
                    pActionData->fadOutData.duration = fDuration;
                    pActionData->fadOutData.actType = (ActionType)actType;
                }
                    break;
                case AT_BLINK:
                {
                    pActionData->bliData.reverseFlag = reverse;
                    pActionData->bliData.repeatCount = repeatCount;
                    pActionData->bliData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->bliData.order = order;
                    pActionData->bliData.duration = fDuration;
                    pActionData->bliData.actType = (ActionType)actType;
                    pActionData->bliData.count = pAction->IntAttribute("count");
                }
                    break;
                case AT_SKEW:
                {
                    pActionData->skeData.reverseFlag = reverse;
                    pActionData->skeData.repeatCount = repeatCount;
                    pActionData->skeData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->skeData.order = order;
                    pActionData->skeData.duration = fDuration;
                    pActionData->skeData.actType = (ActionType)actType;
                    
                    pActionData->skeData.deltaSkewX = pAction->FloatAttribute("skewx");
                    pActionData->skeData.deltaSkewY = pAction->FloatAttribute("skewy");
                }
                case AT_DELAY:
                {
                    pActionData->delayData.reverseFlag = reverse;
                    pActionData->delayData.repeatCount = repeatCount;
                    pActionData->delayData.repeatReverseFlag = repeatReverse;
                    
                    pActionData->delayData.order = order;
                    pActionData->delayData.duration = fDuration;
                    pActionData->delayData.actType = (ActionType)actType;
                    
                }
                default:
                    break;
            }
            
            pAction = pAction->NextSiblingElement("action");
        }
    }
}
void ResManager::readBulletData(XMLElement* pNpc,std::map<int,SlotData>* pMapSlotData)
{
    XMLElement* pSlots = pNpc->FirstChildElement("slots");
    if(pSlots)
    {
        XMLElement* pSlot = pSlots->FirstChildElement("slot");
        while (pSlot)
        {
            int slot_id   = pSlot->IntAttribute("slot_id");
            int bullet_id = pSlot->IntAttribute("bullet_id");
            int slot_x = pSlot->IntAttribute("slot_pos_x");
            int slot_y = pSlot->IntAttribute("slot_pos_y");

            int bullet_speed = pSlot->IntAttribute("bullet_speed");

            float bullet_firetime = pSlot->FloatAttribute("fire_time");
            float bullet_freetime = pSlot->FloatAttribute("free_time");
            float bullet_spacetime = pSlot->FloatAttribute("bullet_space_time");
            
            SlotData slotData;
            
            slotData.nId = slot_id;
            slotData.nBulletId = bullet_id;
            slotData.pos.x = slot_x;
            slotData.pos.y = slot_y;
            slotData.nBulletSpeed = bullet_speed;
            slotData.fFireTime = bullet_firetime;
            slotData.fFreeTime = bullet_freetime;
            slotData.fBulletSpaceTime = bullet_spacetime;

            readActionData(pSlot,&slotData.actionData);

            
            pMapSlotData->insert(std::make_pair(slotData.nId, slotData));
            pSlot = pSlot->NextSiblingElement("slot");
        }
    }
}





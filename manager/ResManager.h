

#ifndef __ResManager__
#define __ResManager__

#include "CommonDef.h"
#include "Tab.h"

#include "external/tinyxml2/tinyxml2.h"
using namespace tinyxml2;


class ResManager
{
public:
    ResManager();
    virtual ~ResManager();
    static ResManager*                      shareResManager();
    void                                    init();
    std::map<eUILayerId,UILayerData>*       getLayersData(){return &m_mapLayerData;}
    UILayerData*                            getLayerData(eUILayerId eLayerId);
    const char*                             getStringForKey(const char* szKey);
    CharacterTabData*                       getCharacterTabData(int nId);
    BuffTabData*                            getBuffData(int nId);
    EffectTabData*							getEffectData(int nID);
    DungeonTabDataDetail*                   getDungenonData(int nId);
    std::map<int, EDiamondTabData>*         getDiamondMap(){return &m_mapDiamond;}
    EDiamondTabData*                        getDiamondData(int nId);
    MapTabDataDetail*                       getMapScreenData(int nId);
    HeroTabData*                           	getHeroTabData(int nId);
    MonsterTabData*                         getMonsterData(int nId);
    std::string                             getBuildingName(EBuildingType type);
    BulletTabData*                          getBulletTabData(int nId);
    bool                                    loadLevelXml(int nLevel,LevelData* pLevelData);
    
    std::map<int, MonsterTabData>* 			getMonsterMap(){return  &m_mapMonster;}
    std::map<int, BulletTabData>*           getBulletMap(){return &m_mapBullet;}

protected:
    bool                                    loadLayersTab(const char* szFileName);
    bool                                    loadSkillTab(const char* szFileName);
    bool									loadEffectTab(const char *szFileName);
    bool                                    loadAnimateTab(const char* szFileName);
    bool                                    loadBuffTab(const char* szFileName);
    bool                                    loadCampaignTab(const char* szFileName);
    bool                                    loadDiamondTab(const char* szFileName);
    bool									loadHeroTab(const char *szFileName);
    bool									loadMonsterTab(const char *szFileName);
    bool									loadLanguageTab(const char *szFileName);
    void                                    readActionData(XMLElement* pNpc,ActionData* pActionData);
    bool                                    loadBulletTab(const char *szFileName);
    void                                    readBulletData(XMLElement* pNpc,std::map<int,SlotData>* pMapSlotData);

    
private:
    std::map<int, int>                      m_mTabEquipBindSkillData;
    std::map<eUILayerId,UILayerData>        m_mapLayerData;
    std::map<std::string, LanguageTabData>  m_mapLanguage;
    std::map<int, EDiamondTabData>          m_mapDiamond;
    std::set<std::string>                   m_vAllString;
    std::map<int, EffectTabData>			m_mapEffect;
    std::map<int, BuffTabData>              m_mapBuff;
    std::map<int, DungeonTabDataDetail>     m_mapDungeon;
    std::map<int, MonsterTabData>			m_mapMonster;
    std::map<int, HeroTabData>				m_mapHero;
    std::map<int, MapTabDataDetail>			m_mapSceen;
    std::map<int, BulletTabData>			m_mapBullet;

    
};

#define GET_STRING(key) ResManager::shareResManager()->getStringForKey(key)

#endif /* defined(__ResManager__) */






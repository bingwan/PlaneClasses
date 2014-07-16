
#ifndef BWUnitManager_h
#define BWUnitManager_h

#include "cocos2d.h"
#include "CommonDef.h"
#include "BWUnit.h"

USING_NS_CC;



class  BWUnitManager : public Ref
{
public:
    
	BWUnitManager();
	virtual			~BWUnitManager();
    static BWUnitManager*				shareBWUnitManager();
    
    void								init();
    virtual void						update(float dt);
    BWUnit*								createHero(UnitData* info);
    void								deleteAllUnit();
    void								deleteAllUnitDelay();
    void                                deleteMonster(int nMapID);
    BWUnit*                            	getHero(){return _pHero;}
    BWUnit*								getMonster(int nMapID);
    void								addToScene(BWUnit *pUnit);
    int                                 getAllCterNum();
    void								deleteUnitDelay(BWUnit* pUnit);

    void                                createMonsterDelay(UnitData* pInfo);
    void                                createHeroBulletDelay(UnitData* pInfo);

    void                                playAction(Node* pSprite,ActionData* pActionData);

    
protected:
    BWUnit*                             createEnemyBullet(UnitData* pInfo);
    BWUnit*								createMonster(UnitData* info);
    void								deleteUnit(BWUnit* pUnit);
    BWUnit*                             createMyBullet(UnitData* pInfo);
    BWUnit*                             createItem(UnitData* pInfo);
    void                                checkCollide(float dt);
    void                                deleteEnemyBullet(int nUuId);
    void                                deleteMyBullet(int nUuId);
private:
    BWUnit*								_pHero;
    std::vector<BWUnit*>                _vNeedDeleteUnit;
    
    std::map<int, BWUnit*>				_mapMonster;
    std::vector<UnitData>			    _vCreateMonsterDelay;

    std::map<int, BWUnit*>				_mapHeroButtlet;
    std::vector<UnitData>			    _vCreateHeroBulletDelay;

    std::map<int, BWUnit*>				_mapEnemyButtlet;
    std::vector<UnitData>			    _vCreateEnemyBulletDelay;

    std::map<int, BWUnit*>				_mapItem;
    std::vector<UnitData>			    _vCreateItemDelay;
    
    int _nUnitCount;

};

#endif

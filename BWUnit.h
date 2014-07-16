

#ifndef __BWUnit__
#define __BWUnit__

#include "Commondef.h"
#include "cocos2d.h"
#include "BuffObject.h"
#include "BuffProcess.h"
#include "ResManager.h"
#include "BWSlot.h"

USING_NS_CC;

class BWUnit 
{
    
public:
    
    BWUnit();
    virtual ~BWUnit();
    virtual bool                init(UnitData* pInfo);
    virtual void                update(float dt);
    void                        setSpeed(float speed){ _fSpeed = speed;}
    virtual void                setHP(int nHp){ _nHP = nHp;}
    virtual int                 getHP(){return _nHP;}
    virtual int                 getMaxHP(){return _nMaxHP;}
    virtual int                 getSpeed(){return 0;}
    virtual int                 getMaxSpeed(){return _fMaxSpeed;}
    virtual int                 getResID(){return _nResID;}
    virtual int					getAttackNatureOfRole(){return -1;}
    int							getAttackNature(int nSkillID);
    float						getAttackAddRatio(){return 1;}
    float						getAttackReduceRation(){return 0;}
    void                        updateBuff(float dt);
    void                        initAct();
    void						setBeHit(BWUnit *pBWUnit, int nTrickID);
    bool						setAct(int nAct);
    bool						beAttacked();
    void                        onNotifyContactBegin(BWUnit* pCharacterB);
    bool                        getNeedToDelete(){return _bNeedToDelete;}
    void                        setNeedToDelete(bool bToDelete){_bNeedToDelete = bToDelete;}
    void                        addBuff(int nBuffId,BWUnit* pFromCharacter,BuffStateType eType);
    void                        deleteBuffWithIndex( int nIndex);
    void                        deleteBuff(BuffObject* pBuff);
    int                         getBuffIndex(BuffObject* pBuff);
    int                         getSameProcessIndex(BuffProcess* pNewProcess);
    int                         getBuffId();    
    void						updateBlood();
    virtual int					getInitDefenseMagicValue(){return 0;}
    virtual int					getInitSpeed(){return 0;}
    Point                       getPosition(){return _pTextureSprite->getPosition();}
    void                        setPosition(Point pos){_pTextureSprite->setPosition(pos);}
    Sprite*                     getTextureSprite(){return  _pTextureSprite;}
    Rect                        getBoundingBox(){ return _pTextureSprite->getBoundingBox();}

    virtual void                collide(BWUnit* pFromUnit);
    void						deadDelay();
    virtual void                addBullet();
    
    virtual void                beginAction(){}
    virtual void                endAction(Node* pNode){}
    
    int                         getUuId(){return _unitData.nUuid;}
    EUnitType                   getUnitType(){return _unitData.eType;}
    virtual void                remove();

    void                        setDead(bool bDead){_bDead = bDead;}
    bool                        getDead(){return _bDead;}
    
    virtual void                updatePos(float dt);
    
    UnitData*                   getUnitData(){return &_unitData;}
    void                        deleteSlot();
    void                        setSlotMapData(std::map<int,SlotData>* pMap){_unitData.mapSlotData = *pMap;}
    void                        initSlot();
    
protected:
    void                        updateSlot(float dt);
protected:
    Sprite*                     _pTextureSprite;
    UnitData                    _unitData;
    

private:
    int							_nResID;
    bool                        _bNeedToDelete;
    std::vector<BuffObject*>    _vBuff;
    int							_nMaxHP;
    int                         _nHP;
    float						_fMaxSpeed;
    float                       _fSpeed;
    bool                        _bDead;
    std::map<int,BWSlot*>       _mapSlot;
    
    //bool _bToDelete;
    
};

#endif /* defined(__BWUnit__) */

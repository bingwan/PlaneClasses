

#ifndef __BWSlot__
#define __BWSlot__

#include "CommonDef.h"
#include "BWUnit.h"

class BWSlot : public Node
{
public:
    BWSlot();
    virtual ~BWSlot();
    
    static BWSlot*              create(SlotData* pSlotData);
    void                        init(SlotData* pSlotData);
    virtual void                update(float dt);
    virtual void                addBullet();
    void                        setParentUnit(BWUnit* pUnit){ _pParentUnit = pUnit;}
    
    
    SlotData*                   getSlotData(){return &_slotData;}
protected:
    void updatePos(float dt);
    void updateBullet(float dt);
    //void playAction(Node* pSprite,ActionData* pActionData);
    
    
private:
    BulletTabData               _bulletTabData;
    float                       _fBulletGroupTime;
    float                       _fBulletSpaceTime;
    SlotData                    _slotData;
    BWUnit*                     _pParentUnit;

};

#endif /* defined(__COCTD__Hero__) */

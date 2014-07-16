

#ifndef __COCTD__Bullet__
#define __COCTD__Bullet__

#include "BWUnit.h"
#include "BWSlot.h"


class BWBullet : public BWUnit
{
public:
    BWBullet();
    virtual ~BWBullet();
    virtual bool                init(UnitData* pInfo);
    virtual void                update(float dt);
    virtual void                beginAction();
    virtual void                endAction(Node* pNode);
    
    virtual void                onEnter();
    
    void setSlot(BWSlot* pSlot);
    BWSlot* getSlot(){return _pSlot;}
    
protected:
    void beginActionMove();
    void beginActionSine();
    void beginActionBezier();
    void beginActionCircle();
    void beginActionCircleMove();
    
private:
    BulletTabData*				m_pData;
    BWSlot*                     _pSlot;

};

#endif /* defined(__COCTD__Hero__) */

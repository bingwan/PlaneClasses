

#ifndef __COCTD__Hero__
#define __COCTD__Hero__

#include "BWUnit.h"

class BWHero : public BWUnit
{
public:
    BWHero();
    virtual ~BWHero();
    virtual bool                init(UnitData* pInfo);
    virtual void                update(float dt);
    
    virtual void                collide(BWUnit* pFromUnit);
    virtual void                addBullet();
    
    virtual int                 getSpeed(){return m_pData->nSpeed;}

protected:
    void updatePos(float dt);
    void updateSlot(float dt);
private:
    
    HeroTabData*				m_pData;
    BulletTabData               _bulletTabData;
    
    float _fBulletGroupTime;
    float _fBulletSpaceTime;

};

#endif /* defined(__COCTD__Hero__) */

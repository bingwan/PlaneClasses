

#ifndef __COCTD__BWMonster__
#define __COCTD__BWMonster__

#include "BWUnit.h"

class BWMonster : public BWUnit
{
public:
    BWMonster();
	virtual ~BWMonster();
    virtual bool                init(UnitData* pInfo);
    virtual void                update(float dt);
    virtual void                collide(BWUnit* pFromUnit);

protected:
    virtual int					getInitHP(){return m_pData->nInitHP;}
    virtual int					getInitSpeed(){return m_pData->nInitSpeed;}
private:
    MonsterTabData*             m_pData;
};

#endif /* defined(__COCTD__BWMonster__) */

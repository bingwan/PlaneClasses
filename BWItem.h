

#ifndef __BWItem__
#define __BWItem__

#include "BWUnit.h"

class BWItem : public BWUnit
{
public:
    BWItem();
    virtual ~BWItem();
    virtual bool                init(UnitData* pInfo);
    virtual void                update(float dt);

protected:
private:

};

#endif /* defined(__COCTD__Hero__) */

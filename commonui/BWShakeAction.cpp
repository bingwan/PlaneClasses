

/*
 *
 *  Created by wangbin
 *
 */

#include "BWShakeAction.h"

BWShakeAction::BWShakeAction()
{
}
//=============================================================
//=============================================================
BWShakeAction::~BWShakeAction()
{
}
//=============================================================
//=============================================================
BWShakeAction* BWShakeAction::create(float duration, float fR)
{
    BWShakeAction *pAction = new BWShakeAction();
    pAction->initWithDuration(duration, fR);
    pAction->autorelease();
    return pAction;
}
//=============================================================
//=============================================================
bool BWShakeAction::initWithDuration(float duration, float fR)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fR = fR;
        return true;
    }
    
    return false;
}
//=============================================================
//=============================================================

BWShakeAction* BWShakeAction::clone(void) const
{
	BWShakeAction* a = new BWShakeAction();
	a->initWithDuration(_duration, m_fR);
	a->autorelease();
	return a;
}

//=============================================================
//=============================================================
void BWShakeAction::startWithTarget(Node *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_oldPos = pTarget->getPosition();
}
//=============================================================
//=============================================================
void BWShakeAction::update(float time)
{
    //CCPoint oldPoint =  ((CCNode*)(m_pTarget))->getPosition();
    
    float fDegree =  360 * CCRANDOM_0_1();
    
    float fRadian = CC_DEGREES_TO_RADIANS(fDegree);
    float fX = m_oldPos.x +  m_fR * cos(fRadian);
    float fY = m_oldPos.y +  m_fR * sin(fRadian);
    Point newPoint = Point(fX,fY);
    ((Node*)(_target))->setPosition(newPoint);

}
//=============================================================
//=============================================================
void BWShakeAction::stop(void)
{
    ((Node*)(_target))->setPosition(m_oldPos);

    CCActionInterval::stop();
}
//=============================================================
//=============================================================

BWShakeAction* BWShakeAction::reverse() const
{
    BWShakeAction* a = new BWShakeAction();
	a->initWithDuration(_duration, m_fR);
	a->autorelease();
	return a;
}



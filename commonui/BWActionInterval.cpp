
//
//  BWBizerActionAppDelegate.h
//  BWBizerAction
//
//  Created by wangbin on 5/25/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "BWActionInterval.h"
#include "CCSprite.h"
#include "CCNode.h"
#include "CCStdC.h"
#include "CCActionInstant.h"
#include <stdarg.h>
#include "cocos2d.h"

USING_NS_CC;

//BWActionInterval* BWActionInterval::create(float d)
//{
//    BWActionInterval *pAction = new BWActionInterval();
//    pAction->initWithDuration(d);
//    pAction->autorelease();
//    return pAction;
//}

bool BWActionInterval::initWithDuration(float d)
{
    _duration = d;
    if (_duration == 0)
    {
        _duration = FLT_EPSILON;
    }
    m_elapsed = 0;
    m_bFirstTick = true;
    m_bRotHead = true;
    return true;
}

bool BWActionInterval::isDone(void) const
{
    //ActionInterval
    return m_elapsed >= _duration;
}

void BWActionInterval::step(float dt)
{
    if (m_bFirstTick)
    {
        m_bFirstTick = false;
        m_elapsed = 0;
    }
    else
    {
        m_elapsed += dt;
    }
    
    this->update(MAX (0,                                  // needed for rewind. elapsed could be negative
                      MIN(1, m_elapsed /
                          MAX(_duration, FLT_EPSILON)   // division by 0
                          )
                      )
                 );
}

void BWActionInterval::setAmplitudeRate(float amp)
{
    CC_UNUSED_PARAM(amp);
    CCAssert(0, "");
}

float BWActionInterval::getAmplitudeRate(void)
{
    CCAssert(0, "");
    return 0;
}

void BWActionInterval::startWithTarget(Node *pTarget)
{
    CCFiniteTimeAction::startWithTarget(pTarget);
    m_elapsed = 0.0f;
    m_bFirstTick = true;
}



//
// ===============================================MoveBy
//
BWMoveBy* BWMoveBy::create(float duration, const Point& deltaPosition)
{
    BWMoveBy *pRet = new BWMoveBy();
    pRet->initWithDuration(duration, deltaPosition);
    pRet->autorelease();
    return pRet;
}

bool BWMoveBy::initWithDuration(float duration, const Point& toPosition)
{
    if (BWActionInterval::initWithDuration(duration))
    {
        m_positionDelta = toPosition;
        return true;
    }
    return false;
}

void BWMoveBy::startWithTarget(Node *pTarget)
{
    BWActionInterval::startWithTarget(pTarget);
    m_previousPosition = m_startPosition = pTarget->getPosition();
    
    float fRadian = atanf(m_positionDelta.x/(float)m_positionDelta.y);
    if((m_positionDelta.y < 0 && m_positionDelta.x < 0)
       || (m_positionDelta.y < 0 && m_positionDelta.x > 0))
    {
        fRadian += M_PI;
    }
    
    m_fRotation = fRadian*180.0/M_PI;
}

BWMoveBy* BWMoveBy::reverse(void) const
{
    return BWMoveBy::create(_duration, Point( -m_positionDelta.x, -m_positionDelta.y));
}
BWMoveBy* BWMoveBy::clone() const
{
    auto* a = new BWMoveBy();
	a->initWithDuration(_duration, m_positionDelta);
	a->autorelease();
	return a;
}

void BWMoveBy::update(float t)
{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
        Point currentPos = _target->getPosition();
        Point diff = ccpSub(currentPos, m_previousPosition);
        m_startPosition = ccpAdd( m_startPosition, diff);
        Point newPos =  ccpAdd( m_startPosition, ccpMult(m_positionDelta, t) );
        _target->setPosition(newPos);
        m_previousPosition = newPos;
        
        if(m_bRotHead)
        _target->setRotation(m_fRotation);
#else
        _target->setPosition(ccpAdd( m_startPosition, ccpMult(m_positionDelta, t)));
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
}

//
// ================================================MoveTo
//
BWMoveTo* BWMoveTo::create(float duration, const Point& position)
{
    BWMoveTo *pRet = new BWMoveTo();
    pRet->initWithDuration(duration, position);
    pRet->autorelease();

    return pRet;
}

bool BWMoveTo::initWithDuration(float duration, const Point& position)
{
    if (BWActionInterval::initWithDuration(duration))
    {
        m_endPosition = position;
        return true;
    }
    return false;
}


void BWMoveTo::startWithTarget(Node *pTarget)
{
    BWMoveBy::startWithTarget(pTarget);
    m_positionDelta =  m_endPosition- pTarget->getPosition() ;
    float fRadian = atanf(m_positionDelta.y/m_positionDelta.x);
    m_fRotation = fRadian*180.0/M_PI;
}

BWMoveTo* BWMoveTo::reverse(void) const
{
    return BWMoveTo::create(_duration, m_endPosition);
}

BWMoveTo* BWMoveTo::clone() const
{
    auto* a = new BWMoveTo();
	a->initWithDuration(_duration, m_endPosition);
	a->autorelease();
	return a;
}

//================================================jumpby
BWJumpBy* BWJumpBy::create(float duration, const Point& position, float height, unsigned int jumps)
{
    BWJumpBy *pJumpBy = new BWJumpBy();
    pJumpBy->initWithDuration(duration, position, height, jumps);
    pJumpBy->autorelease();

    return pJumpBy;
}

bool BWJumpBy::initWithDuration(float duration, const Point& position, float height, unsigned int jumps)
{
    if (BWActionInterval::initWithDuration(duration))
    {
        m_delta = position;
        m_height = height;
        m_nJumps = jumps;
        return true;
    }
    return false;
}

BWJumpBy* BWJumpBy::clone() const
{
    auto* a = new BWJumpBy();
	a->initWithDuration(_duration, m_delta,m_height,m_nJumps);
	a->autorelease();
	return a;
}


void BWJumpBy::startWithTarget(Node *pTarget)
{
    BWActionInterval::startWithTarget(pTarget);
    m_previousPos = m_startPosition = pTarget->getPosition();
}

void BWJumpBy::update(float t)
{
    // parabolic jump (since v0.8.2)
    if (_target)
    {
        float frac = fmodf( t * m_nJumps, 1.0f );
        float y = m_height * 4 * frac * (1 - frac);
        
       // float fA = m_height * 4 ;
       // float y =   - frac*frac * fA + fA * frac + 5;
        

        y += m_delta.y * t;
        float x = m_delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
        Point currentPos = _target->getPosition();

        Point diff = ccpSub( currentPos, m_previousPos );
        m_startPosition = ccpAdd( diff, m_startPosition);

        Point newPos = ccpAdd( m_startPosition, ccp(x,y));
        _target->setPosition(newPos);
        m_previousPos = newPos;
        
        if(m_bRotHead)
        {
            Point dirPoint = ccpSub( currentPos,newPos );
            float fRadian = atanf(dirPoint.y/dirPoint.x);
            if((dirPoint.y > 0 && dirPoint.x > 0)
               || (dirPoint.y < 0 && dirPoint.x > 0))
            {
                fRadian = M_PI_2 - fRadian;
            }
            else if((dirPoint.y < 0 && dirPoint.x < 0)||
                    (dirPoint.y > 0 && dirPoint.x < 0))
            {
                fRadian = -M_PI_2 - fRadian;
            }
            float m_fRotation = fRadian*180.0/M_PI;
            _target->setRotation(m_fRotation);
        }
       
#else
        _target->setPosition(ccpAdd( m_startPosition, ccp(x,y)));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

//m_delta = position;
//m_height = height;
//m_nJumps = jumps;

BWJumpBy* BWJumpBy::reverse(void) const
{
    return BWJumpBy::create(_duration, m_delta,m_height, m_nJumps);
}

//
// ==================================================JumpTo
//

BWJumpTo* BWJumpTo::create(float duration, const Point& position, float height, int jumps)
{
    BWJumpTo *pJumpTo = new BWJumpTo();
    pJumpTo->initWithDuration(duration, position, height, jumps);
    pJumpTo->autorelease();

    return pJumpTo;
}

void BWJumpTo::startWithTarget(Node *pTarget)
{
    BWJumpBy::startWithTarget(pTarget);
    m_delta = Point(m_delta.x - m_startPosition.x, m_delta.y - m_startPosition.y);
}

// Bezier cubic formula:
//    ((1 - t) + t)3 = 1 
// Expands to¡­ 
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1 
static inline float bezierat( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a + 
            3*t*(powf(1-t,2))*b + 
            3*powf(t,2)*(1-t)*c +
            powf(t,3)*d );
}

BWJumpTo* BWJumpTo::clone() const
{
    auto* a = new BWJumpTo();
	a->initWithDuration(_duration, m_delta,m_height,m_nJumps);
	a->autorelease();
	return a;
}

BWJumpTo* BWJumpTo::reverse(void) const
{
    return BWJumpTo::create(_duration, m_delta,m_height, m_nJumps);
}

//
// =======================================BezierBy
//

BWBezierBy* BWBezierBy::create(float t, const BWBezierConfig& c)
{
    BWBezierBy *pBezierBy = new BWBezierBy();
    pBezierBy->initWithDuration(t, c);
    pBezierBy->autorelease();

    return pBezierBy;
}

bool BWBezierBy::initWithDuration(float t, const BWBezierConfig& c)
{
    if (BWActionInterval::initWithDuration(t))
    {
        m_sConfig = c;
        return true;
    }

    return false;
}

BWBezierBy* BWBezierBy::clone() const
{
    auto* a = new BWBezierBy();
	a->initWithDuration(_duration,m_sConfig);
	a->autorelease();
	return a;
}


void BWBezierBy::startWithTarget(Node *pTarget)
{
    BWActionInterval::startWithTarget(pTarget);
    m_previousPosition = m_startPosition = pTarget->getPosition();
}


void BWBezierBy::update(float time)
{
    if (_target)
    {
        float xa = 0;
        float xb = m_sConfig.controlPoint_1.x;
        float xc = m_sConfig.controlPoint_2.x;
        float xd = m_sConfig.endPosition.x;

        float ya = 0;
        float yb = m_sConfig.controlPoint_1.y;
        float yc = m_sConfig.controlPoint_2.y;
        float yd = m_sConfig.endPosition.y;

        float x = bezierat(xa, xb, xc, xd, time);
        float y = bezierat(ya, yb, yc, yd, time);

#if CC_ENABLE_STACKABLE_ACTIONS
        Point currentPos = _target->getPosition();
        Point diff = ccpSub(currentPos, m_previousPosition);
        m_startPosition = ccpAdd( m_startPosition, diff);

        Point newPos = ccpAdd( m_startPosition, ccp(x,y));
        _target->setPosition(newPos);

        m_previousPosition = newPos;
        
        if(m_bRotHead)
        {
            Point dirPoint = ccpSub(newPos, currentPos);
            float fRadian = atanf(dirPoint.y/dirPoint.x);
            
            
            if((dirPoint.y > 0 && dirPoint.x > 0)
               || (dirPoint.y < 0 && dirPoint.x > 0))
            {
                fRadian = M_PI_2 - fRadian;
            }
            else if((dirPoint.y < 0 && dirPoint.x < 0)||
                    (dirPoint.y > 0 && dirPoint.x < 0))
            {
                fRadian = -M_PI_2 - fRadian;
            }
            
            float m_fRotation = fRadian*180.0/M_PI;
            _target->setRotation(m_fRotation);
        }        
#else
        _target->setPosition(ccpAdd( m_startPosition, ccp(x,y)));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

BWBezierBy* BWBezierBy::reverse(void) const 
{
    BWBezierConfig r;

    r.endPosition = ccpNeg(m_sConfig.endPosition);
    r.controlPoint_1 = ccpAdd(m_sConfig.controlPoint_2, ccpNeg(m_sConfig.endPosition));
    r.controlPoint_2 = ccpAdd(m_sConfig.controlPoint_1, ccpNeg(m_sConfig.endPosition));

    BWBezierBy *pAction = BWBezierBy::create(_duration, r);
    return pAction;
}

//
// ==============================================BezierTo
//

BWBezierTo* BWBezierTo::create(float t, const BWBezierConfig& c)
{
    BWBezierTo *pBezierTo = new BWBezierTo();
    pBezierTo->initWithDuration(t, c);
    pBezierTo->autorelease();

    return pBezierTo;
}

bool BWBezierTo::initWithDuration(float t, const BWBezierConfig &c)
{
    bool bRet = false;
    
    if (BWActionInterval::initWithDuration(t))
    {
        m_sToConfig = c;
    }
    
    return bRet;
}

BWBezierTo* BWBezierTo::clone() const
{
    auto* a = new BWBezierTo();
	a->initWithDuration(_duration,m_sToConfig);
	a->autorelease();
	return a;
}
BWBezierTo* BWBezierTo::reverse(void) const
{
  
    return BWBezierTo::create(_duration, m_sToConfig);
}


void BWBezierTo::startWithTarget(CCNode *pTarget)
{
    BWBezierBy::startWithTarget(pTarget);
    m_sConfig.controlPoint_1 = ccpSub(m_sToConfig.controlPoint_1, m_startPosition);
    m_sConfig.controlPoint_2 = ccpSub(m_sToConfig.controlPoint_2, m_startPosition);
    m_sConfig.endPosition = ccpSub(m_sToConfig.endPosition, m_startPosition);
}

//
// ==================================================BWSineBy
//

BWSineBy* BWSineBy::create(float t, Point endPoint,float fA)
{
    BWSineBy *pSineBy = new BWSineBy();
    pSineBy->initWithDuration(t, endPoint,fA);
    pSineBy->autorelease();
    
    return pSineBy;
}

bool BWSineBy::initWithDuration(float t, Point endPoint,float fA)
{
    if (BWActionInterval::initWithDuration(t))
    {
        m_endPosition = endPoint;
        m_fA = fA;
         return true;
    }
    
    return false;
}

BWSineBy* BWSineBy::clone() const
{
    auto* a = new BWSineBy();
	a->initWithDuration(_duration,m_endPosition,m_fA);
	a->autorelease();
	return a;
}

BWSineBy* BWSineBy::reverse(void) const
{
    BWBezierConfig r;
    BWSineBy *pAction = BWSineBy::create(_duration, m_endPosition,m_fA);
    return pAction;
}

void BWSineBy::startWithTarget(Node *pTarget)
{
    BWActionInterval::startWithTarget(pTarget);
    m_previousPosition = m_startPosition = pTarget->getPosition();
    float fDis =  m_endPosition.getLength();
    m_fW = 2*M_PI/fDis;
}



void BWSineBy::update(float time)
{
    if (_target)
    {
        //CCLog("%f",time);
        Point dir =  m_endPosition ;
        float fDis = ccpLength(m_endPosition);

        float fOldX = fDis * time;
        float fOldY = m_fA * sinf(m_fW * fOldX);
        float fOldC = sqrtf(powf(fOldX, 2)+powf(fOldY, 2));
        
        float fRotRadian = atanf(fOldY/fOldX) + atanf(dir.y/dir.x);
        if(m_endPosition.x < 0)
            fRotRadian += M_PI;
        float fRotOldX = fOldC * cos(fRotRadian);
        float fRotOldY = fOldC * sin(fRotRadian);
        
        float fNewX = fRotOldX + m_startPosition.x;
        float fNewY = fRotOldY + m_startPosition.y;
        
        Point currentPos = _target->getPosition();
        Point newPos = ccp( fNewX, fNewY);
        _target->setPosition(newPos);
        
        
        if(m_bRotHead)
        {
            Point dirPoint = ccpSub(newPos, currentPos);
            float fRadian = atanf(dirPoint.y/dirPoint.x);
            if((dirPoint.y > 0 && dirPoint.x > 0)
               || (dirPoint.y < 0 && dirPoint.x > 0))
            {
                fRadian = M_PI_2 - fRadian;
            }
            else if((dirPoint.y < 0 && dirPoint.x < 0)||
                    (dirPoint.y > 0 && dirPoint.x < 0))
            {
                fRadian = -M_PI_2 - fRadian;
            }
            
            float m_fRotation = fRadian*180.0/M_PI;
            _target->setRotation(m_fRotation);
        }
    }
}




//
// =============================================BWCircleBy
//

BWCircleBy* BWCircleBy::create(float t, Point dirPoint,float fB,Point movePos)
{
    BWCircleBy *pCircleBy = new BWCircleBy();
    pCircleBy->initWithDuration(t, dirPoint,fB,movePos);
    pCircleBy->autorelease();
    
    return pCircleBy;
}

bool BWCircleBy::initWithDuration(float t, Point dirPoint,float fB,Point movePos)
{
    if (BWActionInterval::initWithDuration(t))
    {
        m_dirPoint = dirPoint;
        m_fA = dirPoint.getLength();
        m_fB = fB;
        m_bClock = false;
        m_moveToPos = movePos;
        return true;
    }
    
    return false;
}

BWCircleBy* BWCircleBy::clone() const
{
    auto* a = new BWCircleBy();
	a->initWithDuration(_duration,m_dirPoint,m_fB,m_moveToPos);
	a->autorelease();
	return a;
}

BWCircleBy* BWCircleBy::reverse(void) const
{
    BWCircleBy *pAction = BWCircleBy::create(_duration, m_dirPoint,m_fB,m_moveToPos);
    return pAction;
}

void BWCircleBy::startWithTarget(Node *pTarget)
{
    BWActionInterval::startWithTarget(pTarget);
    m_previousPosition = m_startPosition = pTarget->getPosition();
    float fDis =  m_dirPoint.getLength();
    m_fA = fDis*0.5;
}


void BWCircleBy::update(float time) //time 0--1
{
    if (_target)
    {
        //CCLog("%f",time);
        Point dir =  m_dirPoint ;
        
        float fRadianMin = 0;
        float fRadianMax = 2*M_PI;
        
        if(m_dirPoint.x > 0)
        {
            fRadianMin = -M_PI;
            if(m_bClock)
            {
                time = 1-time;
            }
        }
        else
        {
            if(m_bClock)
            {
                time = 1-time;
            }
        }
        float fRadian = fRadianMin + fRadianMax * time;
        float fOldX = m_fA * cosf(fRadian);
        float fOldY = m_fB * sinf(fRadian);
        
        
        if(m_dirPoint.x > 0)
        {
            fOldX += m_fA;
        }
        else
        {
            fOldX -= m_fA;
        }
        float fOldC = sqrtf(powf(fOldX, 2)+powf(fOldY, 2));
        
        float fRotRadian = atanf(fOldY/fOldX) + atanf(dir.y/dir.x);
        if(fOldX < 0 )
            fRotRadian += M_PI;
        
        
        float fRotOldX = fOldC * cos(fRotRadian);
        float fRotOldY = fOldC * sin(fRotRadian);

        
        float fNewX = fRotOldX + m_startPosition.x;
        float fNewY = fRotOldY + m_startPosition.y;
        
        Point currentPos = _target->getPosition();
        Point newPos = Point( fNewX, fNewY);
        
        if(m_moveToPos.x != 0 || m_moveToPos.y != 0)
        {
            Point stepMovePos = m_moveToPos * time ;
            newPos = newPos + stepMovePos;
        }
        
       _target->setPosition(newPos);
        
        if(m_bRotHead)
        {
            Point dirPoint = newPos-currentPos;
            float fRadian = atanf(dirPoint.y/dirPoint.x);
            if((dirPoint.y > 0 && dirPoint.x > 0)
               || (dirPoint.y < 0 && dirPoint.x > 0))
            {
                fRadian = M_PI_2 - fRadian;
            }
            else if((dirPoint.y < 0 && dirPoint.x < 0)||
                    (dirPoint.y > 0 && dirPoint.x < 0))
            {
                fRadian = -M_PI_2 - fRadian;
            }
            
            float m_fRotation = fRadian*180.0/M_PI;
            _target->setRotation(m_fRotation);
        }
    }
}









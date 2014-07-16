//
//  BWBizerActionAppDelegate.h
//  BWBizerAction
//
//  Created by wangbin on 5/25/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#ifndef __ACTION_BWINTERVAL_ACTION_H__
#define __ACTION_BWINTERVAL_ACTION_H__

#include "CCNode.h"
#include "CCAction.h"
#include "CCProtocols.h"
#include "CCSpriteFrame.h"
#include "CCAnimation.h"
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class BWActionInterval : public ActionInterval
{
public:
    //ActionInterval
    
    inline float    getElapsed(void) { return m_elapsed; }
    void            setRotHead(bool bRotHead){m_bRotHead = bRotHead;}
    
    //static BWActionInterval* create(float d);
    bool            initWithDuration(float d);

    virtual bool isDone(void) const override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    
    void   setAmplitudeRate(float amp);
    float  getAmplitudeRate(void);
    
    virtual BWActionInterval* reverse() const override = 0;
	virtual BWActionInterval* clone() const override  = 0;

protected:
    float  m_elapsed;
    bool   m_bFirstTick;
    bool   m_bRotHead;
};

class  BWMoveBy : public BWActionInterval
{
public:
    bool initWithDuration(float duration, const Point& deltaPosition);
    
    virtual BWMoveBy* clone() const override;
    virtual BWMoveBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

public:
    static BWMoveBy* create(float duration, const Point& deltaPosition);
protected:
    Point m_positionDelta;
    Point m_startPosition;
    Point m_previousPosition;
    float m_fRotation;
};

class  BWMoveTo : public BWMoveBy
{
public:
    bool initWithDuration(float duration, const Point& position);

    virtual BWMoveTo* clone() const override;
    virtual BWMoveTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    //virtual void update(float time) override;
    
public:
    static BWMoveTo* create(float duration, const Point& position);
protected:
    Point m_endPosition;
};



/** @brief Moves a CCNode object simulating a parabolic jump movement by modifying it's position attribute.
*/
class BWJumpBy : public BWActionInterval
{
public:
    bool initWithDuration(float duration, const Point& position, float height, unsigned int jumps);
    
    virtual BWJumpBy* clone() const override;
    virtual BWJumpBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

public:
    static BWJumpBy* create(float duration, const Point& position, float height, unsigned int jumps);
protected:
    Point         m_startPosition;
    Point         m_delta;
    float           m_height;
    unsigned int    m_nJumps;
    Point         m_previousPos;
};

class BWJumpTo : public BWJumpBy
{
public:
    
    virtual BWJumpTo* clone() const override;
    virtual BWJumpTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    //virtual void update(float time) override;
    

public:
    static BWJumpTo* create(float duration, const Point& position, float height, int jumps);
};

typedef struct _ccBezierConfig {
    Point endPosition;
    Point controlPoint_1;
    Point controlPoint_2;
} BWBezierConfig;

class BWBezierBy : public BWActionInterval
{
public:
    bool initWithDuration(float t, const BWBezierConfig& c);
    
    virtual BWBezierBy* clone() const override;
    virtual BWBezierBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

public:
    static BWBezierBy* create(float t, const BWBezierConfig& c);
protected:
    BWBezierConfig m_sConfig;
    Point m_startPosition;
    Point m_previousPosition;
    
};

class BWBezierTo : public BWBezierBy
{
public: //BezierTo
    virtual BWBezierTo* clone() const override;
    virtual BWBezierTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
   // virtual void update(float time) override;

public:

    static BWBezierTo* create(float t, const BWBezierConfig& c);
    bool initWithDuration(float t, const BWBezierConfig &c);
    
protected:
    BWBezierConfig m_sToConfig;
};

class BWSineBy : public BWActionInterval
{
public:
    bool initWithDuration(float t, Point endPoint,float fA);
    
    virtual BWSineBy* clone() const override;
    virtual BWSineBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
public:
    static BWSineBy* create(float t, Point endPoint,float fA);
protected:
    Point   m_startPosition;
    Point   m_previousPosition;
    float   m_fW;
    Point   m_endPosition;
    float   m_fA;
};


class BWCircleBy : public BWActionInterval
{
public:
    bool    initWithDuration(float t, Point dirPoint,float fB,Point movePos);
    void    setClock(bool bClock){m_bClock = bClock;}
    
    virtual BWCircleBy* clone() const override;
    virtual BWCircleBy* reverse() const override ;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
public:
    static BWCircleBy* create(float t, Point dirPoint2a,float fB,Point movePos);
protected:
    Point   m_startPosition;
    Point   m_previousPosition;
    Point   m_dirPoint;
    float   m_fA;
    float   m_fB;
    bool    m_bClock;
    Point   m_moveToPos;
};

#endif //__ACTION_CCINTERVAL_ACTION_H__

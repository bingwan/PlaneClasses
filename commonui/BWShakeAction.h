
/*
 *
 *  Created by wangbin
 *
 */

#ifndef __BWShakeAction_H__
#define __BWShakeAction_H__

#include "cocos2d.h"
USING_NS_CC;

class BWShakeAction : public ActionInterval
{
public:
    
    BWShakeAction();
    virtual ~BWShakeAction();

    bool initWithDuration(float duration, float fR);
    
    virtual void stop(void);
    
    virtual BWShakeAction* clone() const override;
    virtual BWShakeAction* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
public:
    static BWShakeAction* create(float duration, float fR);
    
private:
    float m_fR;
    Point m_oldPos;

};

#endif // __BWShakeAction_H__

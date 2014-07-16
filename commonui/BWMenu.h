
/*
 *
 *  Created by wangbin
 *
 */

#ifndef __BWMenu_H__
#define __BWMenu_H__

#include "cocos2d.h"

USING_NS_CC;

class  BWMenu : public Menu
{
public:
	BWMenu();
	virtual ~BWMenu();
	//virtual void        registerWithTouchDispatcher();
    virtual bool        onTouchBegan(Touch* touch, Event* event);
	virtual void        onTouchMoved(Touch* touch, Event* event);
    
    void                setPreventTouchFlag(bool preventFlag){m_preventTouchFlag = preventFlag;}
    
    CREATE_FUNC(BWMenu);

private:
    bool                m_preventTouchFlag;
    float               m_dragDisPercent;
    Point               m_beginPoint;
};

#endif // __BWMenu_H__

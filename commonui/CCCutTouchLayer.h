

/*
 *
 *  Created by wangbin
 *
 */

#ifndef MT_B_LJCutTouchLayer_h
#define MT_B_LJCutTouchLayer_h

#include "cocos2d.h"
USING_NS_CC;

class  CCCutTouchLayer : public LayerColor
{
public:
    CCCutTouchLayer();
	virtual ~CCCutTouchLayer();
	CREATE_FUNC(CCCutTouchLayer);
    
    static CCCutTouchLayer * create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool            initWithColor(const Color4B& color, GLfloat w, GLfloat h);

    //virtual void            registerWithTouchDispatcher(void);
    virtual bool            onTouchBegan(Touch* touch, Event* event);
    //virtual void            visit();
    virtual void            onNotification();
    void                    setClipsToBounds(bool toBounds){m_bClipsToBounds = toBounds;}
    void                    setPreventTouch(bool prevent){m_bPreventTouch = prevent;}
    
    void                    setThePriority(int nPrio){ m_nPriority=nPrio;}
    
    virtual void onEnter();
    virtual void onExit();

protected:
private:
    void                afterDraw();
    void                beforeDraw();
private:
    bool                m_bClipsToBounds;
    bool                m_bPreventTouch;
    int                 m_nPriority;
    
};

#endif

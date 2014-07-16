

#ifndef BWShowBulletLayer_h
#define BWShowBulletLayer_h

#include "cocos2d.h"
#include "CommonDef.h"
#include "CCCutTouchLayer.h"

#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class  BWShowBulletLayer : public CCCutTouchLayer
{
    
public:
	BWShowBulletLayer();
	virtual			~BWShowBulletLayer();
    static          BWShowBulletLayer* create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool    initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
    void            clickBack(Ref* pObject,Control::EventType controlEvent);
protected:
    void        initUI();
    void        clickBullet(Ref* pObject,Control::EventType controlEvent);
    
    void update(float dt);
private:
    
};

#endif
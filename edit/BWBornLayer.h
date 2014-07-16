

#ifndef FlyFlyRookie_BWBornLayer_h
#define FlyFlyRookie_BWBornLayer_h

#include "cocos2d.h"
#include "CommonDef.h"
USING_NS_CC;

struct editNpcStr;

class BWDetailNPCLayer;
class BWMenu;
class CCScrollLayer;
class BWEditBulletLayer;

class  BWBornLayer : public cocos2d::CCLayerColor
{
public:
	BWBornLayer();
	virtual			~BWBornLayer();
	virtual bool	init(); 
    CREATE_FUNC(BWBornLayer);
    void            setEnable(bool ableFlag);
    void            setBornData(NpcData* pBornDataStr);
	void			getBornData();
    virtual bool    initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
    void            addTextField(ccColor4B color, int count);
    void            back(Object* pObject);
    void            setdetailLayer(BWDetailNPCLayer* layer);
    void            setEditBulletLayer(BWEditBulletLayer* layer);

    
protected:
private:
       
    BWDetailNPCLayer*               m_detailLayer;
    CCMenu*                         m_menu;
    CCScrollLayer*                  m_scrollLayer;
    NpcData*                        m_npcItemDataStr;
    CCArray*                        m_idTextFieldArray;
    CCArray*                        m_rateTextFieldArray;
};

#endif


#ifndef FlyFlyRookie_BWEditBulletLayer_h
#define FlyFlyRookie_BWEditBulletLayer_h

#include "cocos2d.h"
#include "CommonDef.h"
#include "cocos-ext.h"
USING_NS_CC;

USING_NS_CC_EXT;

class BWDetailNPCLayer;
class BWMenu;
class CCScrollLayer;


class  BWEditBulletLayer : public cocos2d::CCLayerColor
{
public:
	BWEditBulletLayer();
	virtual			~BWEditBulletLayer();
	virtual bool	init(); 
    CREATE_FUNC(BWEditBulletLayer);
    void            setEnable(bool ableFlag);
    virtual bool    initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
   
    void            back(Object* pObject);
    void            setOwnedLayer(BWDetailNPCLayer* layer);
    
    void            setBulletData(BulletSlotData* pBulletDataStr,int bulletIndex);
    void            getBulletData(BulletSlotData* pBulletDataStr,int bulletIndex);
    
    void            sortAction(ActionData* pActionDataStr);
    void            editBulletAction(Object* p);
    void            editSlotAction(Object* p);
    void            deleteSlot(Object* p);
    
protected:
private:

    CCScrollLayer*                  m_scrollLayer;
    CCMenu*                         m_menu;

    BulletSlotData*                 m_bulletDataStr;
    int                             m_bulletIndex;
    BWDetailNPCLayer*               m_ownedLayer;
    
    EditBox* m_slotIdField;
    EditBox* m_slotVisibleField;
    EditBox* m_slotRotatePosXField;
    EditBox* m_slotRotatePosYField;
    EditBox* m_slotFirePosXField;
    EditBox* m_slotFirePosYField;
    EditBox* m_slotPosXField;
    EditBox* m_slotPosYField;
    EditBox* m_slotIntervalField;
    EditBox* m_slotRotateField;
    
    
    EditBox* m_bulletIdField;
    EditBox* m_bulletTypeField;
    EditBox* m_bulletEndIdField;
    
   
    
};

#endif

#ifndef FlyFlyRookie_BWActionLayer_h
#define FlyFlyRookie_BWActionLayer_h

#include "cocos2d.h"
#include "CommonDef.h"
#include "CCScrollLayer.h"
#include "BWMenu.h"
#include "CCCutTouchLayer.h"


#include "cocos-ext.h"
USING_NS_CC;

USING_NS_CC_EXT;

struct editNpcStr;

class BWDetailNPCLayer;
class BWMenu;
class BWCCScrollLayer;
class BWEditBulletLayer;

class  BWActionLayer : public CCCutTouchLayer
{
public:
	BWActionLayer();
	virtual			~BWActionLayer();
	virtual bool	init(); 
    CREATE_FUNC(BWActionLayer);
    
    static BWActionLayer*       create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool                initWithColor(const Color4B& color, GLfloat w, GLfloat h);

    void            setEnable(bool ableFlag);
    void            setActionData(ActionData* pActionDataStr);
	void			getActionData(ActionData* pActionDataStr);
    void            addTextField(Color4B color);
    void            clickClose(Ref* pObject);
    void            setdetailLayer(BWDetailNPCLayer* layer);
    void            setEditBulletLayer(BWEditBulletLayer* layer);
    void            selectActionType(Ref* pObject);
    void            selectReverse(Ref* pObject);
    void            sortAction(ActionData* pActionDataStr);
protected:
private:
    //bezier
    EditBox* m_bezierDurationField;
    EditBox* m_bezierOnePointXField;
    EditBox* m_bezierOnePointYField;
    EditBox* m_bezierTwoPointXField;
    EditBox* m_bezierTwoPointYField;
    EditBox* m_bezierEndPointXField;
    EditBox* m_bezierEndPointYField;
    EditBox* m_bezierOrderField;
    EditBox* m_bezierRepeatCountField;
    
    //jump
    EditBox* m_jumpDurationField;
    EditBox* m_jumpHeightField;
    EditBox* m_jumpEndPointXField;
    EditBox* m_jumpEndPointYField;
    EditBox* m_jumpCountField;
    EditBox* m_jumpOrderField;
    EditBox* m_jumpRepeatCountField;
    
    //scale
    EditBox* m_scaleDurationField;
    EditBox* m_scaleXField;
    EditBox* m_scaleYField;
    EditBox* m_scaleOrderField;
    EditBox* m_scaleRepeatCountField;
    
    //rotate
    EditBox* m_rotateDurationField;
    EditBox* m_rotateAngleField;
    EditBox* m_rotateOrderField;
    EditBox* m_rotateRepeatCountField;
    
    //tint
    EditBox* m_tintDurationField;
    EditBox* m_tintRedField;
    EditBox* m_tintGreenField;
    EditBox* m_tintBlueField;
    EditBox* m_tintOrderField;
    EditBox* m_tintRepeatCountField;
    
    //fadeIn
    EditBox* m_fadeInDurationField;
    EditBox* m_fadeInOrderField;
    EditBox* m_fadeInRepeatCountField;
    
    //fadeOut
    EditBox* m_fadeOutDurationField;
    EditBox* m_fadeOutOrderField;
    EditBox* m_fadeOutRepeatCountField;
    
    //blink
    EditBox* m_blinkDurationField;
    EditBox* m_blinkCountField;
    EditBox* m_blinkOrderField;
    EditBox* m_blinkRepeatCountField;
    
    //skew
    EditBox* m_skewDurationField;
    EditBox* m_skewXField;
    EditBox* m_skewYField;
    EditBox* m_skewOrderField;
    EditBox* m_skewRepeatCountField;
    
    //move
    EditBox* m_moveDurationField;
    EditBox* m_moveEndPointXField;
    EditBox* m_moveEndPointYField;
    EditBox* m_moveOrderField;
    EditBox* m_moveRepeatCountField;
    
    //sine
    EditBox* m_sineDurationField;
    EditBox* m_sineOrderField;
    EditBox* m_sineEndPointXField;
    EditBox* m_sineEndPointYField;
    EditBox* m_sineAField;
    EditBox* m_sineRepeatCountField;


    
    //repeat
    EditBox* m_repeatCountField;
    
    BWDetailNPCLayer*               m_detailLayer;
    BWEditBulletLayer*              m_editBulletLayer;
    editNpcStr*                     m_currentNpc;
    Menu*                           m_menu;
    ActionType                      m_actionType;
    MenuItemToggle*                 m_actionTypeTogItem;
    BWMenu*                         m_scrolMenu;
    CCScrollLayer*                  m_scrollLayer;
    ActionData*                     m_pActionData;
    BulletSlotData*                 m_pBulletData;
    int                             m_bulletIndex;
    EditBox*                        m_delayTimeDurationField;
    EditBox*                        m_delayTimeOrderField;
    
};

#endif
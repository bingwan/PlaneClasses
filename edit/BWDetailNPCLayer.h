

#ifndef __BWDETALLAYER_H__
#define __BWDETALLAYER_H__

#include "cocos2d.h"
#include "BWMenu.h"
#include "CCScrollLayer.h"
#include "CCCutTouchLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class BWEditLayer; 
struct EditNpcData;
class BWActionLayer;


class  BWDetailNPCLayer : public CCCutTouchLayer
{
public:
    
	BWDetailNPCLayer();
	virtual ~BWDetailNPCLayer();
	CREATE_FUNC(BWDetailNPCLayer);
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    
	void			clickConfirm(Object* pObject);
	void            clickBack(Object* pObject);
	void			setSelectNpcId(int npcId);
	void			dataToText(EditNpcData* pNpc);
	void			textToData(EditNpcData* pNpc);
    void            setEnable(bool ableFlag);
    void            editNpcAction(CCObject* pObject);
    void            setBulletData();
   // void            getBulletData(editNpcStr* pNpc);
    void            editBullet(CCObject* pObject);
    void            addSlot(Object* pObject);
    
    void            bornItem(Object* pObject);
    void            setEditLayer(BWEditLayer* player){m_ownedLayer = player;}
    
    
    virtual void            onEnter();
    virtual void            onExit();
    
    static BWDetailNPCLayer*   create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool                initWithColor(const Color4B& color, GLfloat w, GLfloat h);

protected:
    bool initUI();
    void initBottomMenu();

private:
	BWEditLayer*	m_ownedLayer;
	int				m_npcId;
    CCScrollLayer*  m_actionScrollayer;
    Menu*           m_menu;
    BWActionLayer*  m_actionLayer;
	
	
	EditBox* m_posXEdit;				//位置
	EditBox* m_posYEdit;				//位置
	EditBox* m_rotateEdit;				//角度

	EditBox* m_MaxAppearNumEdit;		//最大出现次数
	EditBox* m_TriggerDisEdit;          //触发距离 负数＝左边，正数＝右边
	EditBox* m_moveTypeEdit;			//移动类型
    EditBox* m_scaleEdit;               //放大
    EditBox* m_opacityEdit;             //透明
    EditBox* m_zOrderEdit;   
    EditBox* m_flipXEdit; 
    EditBox* m_flipYEdit;
    
    BWMenu*                      m_scrollMenu;
    CCScrollLayer*               m_scrollLayer;
    EditNpcData*                  m_pCurNpcData;

};

#endif // __BWDETALLAYER_H__	


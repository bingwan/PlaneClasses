
#ifndef __BWTEXTEDIT_H__
#define __BWTEXTEDIT_H__

#include "cocos2d.h"
#include "CommonDef.h"
#include "CCCutTouchLayer.h"
#include "CCScrollLayer.h"
USING_NS_CC;

class BWKeyboardNotificationLayer : public CCCutTouchLayer
{
public:
    BWKeyboardNotificationLayer();
	
    virtual void onClickTrackNode(bool bClicked) = 0;
	virtual void setPos(CCPoint pos);

    // CCLayer
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
	//interface
	const char* getString();
	void		setString(const char* pStr);
    
    void       setPTrackNodeSize(CCSize size);
    void       setPTrackNodePosition(CCPoint point);
protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
	CCPoint  m_Pos;
	char	 m_String[COMMON_STRING_SIZE];
	float	 m_adjustVert;
	bool	 m_EditFlag;
    
    bool m_keyBoardIsShow;

	
	
};


class BWTextFieldTTFDefault : public BWKeyboardNotificationLayer
{
public:
    
    BWTextFieldTTFDefault();
    virtual void onClickTrackNode(bool bClicked);
    virtual void onEnter();
    
};



#endif //__BWTEXTEDIT_H__
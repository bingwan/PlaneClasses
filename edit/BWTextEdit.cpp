

#include "BWTextEdit.h"

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

BWKeyboardNotificationLayer::BWKeyboardNotificationLayer()
: m_pTrackNode(0),
m_beginPos(CCPointZero),
m_Pos(CCPointZero),
m_keyBoardIsShow(false)
{
	m_adjustVert = 0;
	m_EditFlag = false;
	memset(m_String,0,COMMON_STRING_SIZE);
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}



bool BWKeyboardNotificationLayer::onTouchBegan(Touch *touch, Event *event)
{
    m_beginPos = touch->getLocation();
    return true;
}

void BWKeyboardNotificationLayer::onTouchEnded(Touch *touch, Event *event)
{
    if (! m_pTrackNode)
    {
        return;
    }
    CCPoint endPos = touch->getLocation();
    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(touch);
    rect = getRect(m_pTrackNode);
    this->onClickTrackNode(rect.containsPoint( point));

}
void BWKeyboardNotificationLayer::setPos(CCPoint pos)
{
	m_Pos = pos;	
}
const char* BWKeyboardNotificationLayer::getString()
{
//	CCTextFieldTTF* pTextField = (CCTextFieldTTF*)m_pTrackNode;
//	if (pTextField)
//	{
//		strncpy(m_String,pTextField->getString(),COMMON_STRING_SIZE);
//	}
//	return m_String;;
}

void BWKeyboardNotificationLayer::setString(const char* pStr)
{
	CCTextFieldTTF* pTextField = (CCTextFieldTTF*)m_pTrackNode;
	if (pTextField)
	{
		pTextField->setString(pStr);
	}
	strncpy(m_String,pStr,COMMON_STRING_SIZE);
}


void BWKeyboardNotificationLayer::setPTrackNodeSize(cocos2d::CCSize size)
{
    m_pTrackNode->setContentSize(size);
}
void BWKeyboardNotificationLayer::setPTrackNodePosition(CCPoint point)
{
    m_pTrackNode->setPosition(point);
}


BWTextFieldTTFDefault::BWTextFieldTTFDefault()
{
    TextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(m_String, CCSizeZero, TextHAlignment::CENTER, "", 25);
    addChild(pTextField);
    pTextField->setPosition(m_Pos);
    m_pTrackNode = pTextField;
}

void BWTextFieldTTFDefault::onClickTrackNode(bool bClicked)
{
    TextFieldTTF * pTextField = (TextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        // BWTextFieldTTFDefault be clicked
        //CCLOG("BWTextFieldTTFDefault:CCTextFieldTTF attachWithIME");
		m_EditFlag = true;
        pTextField->attachWithIME();
        pTextField->setString("");
    }
    else
    {
        // BWTextFieldTTFDefault not be clicked
        //CCLOG("BWTextFieldTTFDefault:CCTextFieldTTF detachWithIME");
		m_EditFlag = false;
        pTextField->detachWithIME();
    }
}

void BWTextFieldTTFDefault::onEnter()
{
    BWKeyboardNotificationLayer::onEnter();
    TextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(m_String,COMMON_FONT,30);
	addChild(pTextField);
	pTextField->setPosition(m_Pos);
    m_pTrackNode = pTextField;
    
}



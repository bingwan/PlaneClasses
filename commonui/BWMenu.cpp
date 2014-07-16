
/*
 *
 *  Created by wangbin
 *
 */
#include "BWMenu.h"


BWMenu::BWMenu():
m_preventTouchFlag(false),
m_dragDisPercent(0.25),
m_beginPoint(Point::ZERO)
{
    setSwallowsTouches(false);
}

BWMenu::~BWMenu()
{
}


//void BWMenu::registerWithTouchDispatcher() //3.0 去掉
//{    
//    CCDirector::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, Menu::HANDLER_PRIORITY, m_preventTouchFlag);
//}

bool BWMenu::onTouchBegan(Touch* touch,Event* event)
{
    if(!isVisible())
        return false;
    
    if (_state != Menu::State::WAITING || !isEnabled())
    {
        return false;
    }
    
    Node* fatherNode = getParent();
    if(!fatherNode)
        return false;
    Point touchPointInWorld = touch->getLocation();
    
    Rect  selfRect = boundingBox();
    Point selfOriginInWorld = fatherNode->convertToWorldSpace(selfRect.origin);
    
    Rect selfRectInWorld = Rect(selfOriginInWorld.x,selfOriginInWorld.y,selfRect.size.width,selfRect.size.height);
    if(selfRectInWorld.containsPoint(touchPointInWorld) == false)
    {
        //return false;
    }
    
    for (Node *c = this->_parent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false) //若父亲有不可见的则不处理touch
        {
            return false;
        }
        
        Rect  rect = c->boundingBox();
        Node* parentNode = c->getParent();
        if(parentNode)
        {
            Point originInWorld = parentNode->convertToWorldSpace(rect.origin);
            
            Rect rectInWorld = Rect(originInWorld.x,originInWorld.y,rect.size.width,rect.size.height);
            if(rectInWorld.containsPoint(originInWorld))
            {
                //return false; //不在父视图中 不处理touch
            }
        }
        
    }    
    _selectedItem = this->getItemForTouch(touch);
    if (_selectedItem)
    {
        _state = Menu::State::TRACKING_TOUCH;
        _selectedItem->selected();
        m_beginPoint =  touchPointInWorld;
        return true;
    }
    return false;
    
}

void BWMenu::onTouchMoved(Touch* touch, Event* event)
{
    Point touchPoint = touch->getLocation();
	if(_selectedItem != NULL  )
	{
        Size itemSize = _selectedItem->getContentSize();
        float distanceX = fabsf(touchPoint.x-m_beginPoint.x);
        float distanceY = fabsf(touchPoint.y-m_beginPoint.y);
        if(distanceX >= m_dragDisPercent*itemSize.width || distanceY >=  m_dragDisPercent*itemSize.height);
        {
            _selectedItem->unselected();
            _selectedItem = NULL;
        }
	}
}







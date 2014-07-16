
/*
 *
 *  Created by wangbin
 *
 */

#include <iostream>
#include "CCCutTouchLayer.h"

CCCutTouchLayer::CCCutTouchLayer():
m_bClipsToBounds(false),
m_bPreventTouch(true),
m_nPriority(0)
{
    ignoreAnchorPointForPosition(false);
}


//=============================================================
//=============================================================
CCCutTouchLayer::~CCCutTouchLayer()
{
}


//=============================================================
//=============================================================
CCCutTouchLayer * CCCutTouchLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    CCCutTouchLayer * pLayer = new CCCutTouchLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}
//=============================================================
//============================ =================================
bool CCCutTouchLayer::initWithColor(const Color4B& color, GLfloat w, GLfloat h) 
{
    if(CCLayerColor::initWithColor(color, w, h))
    {
        setTouchEnabled(true);
        return true;
    }
    return false;
}

void CCCutTouchLayer::onEnter()
{
    CCLayerColor::onEnter();
}


void CCCutTouchLayer::onExit()
{
    CCLayerColor::onExit();
}


//=============================================================
//=============================================================
bool CCCutTouchLayer::onTouchBegan(Touch* touch, Event* event)  //截住touch
{
    if(!m_bPreventTouch)
        return false;
    if(!isVisible())
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
        return false;
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
            if(rectInWorld.containsPoint(touchPointInWorld) == false)  // 不在父视图区域内
            {
                return false;
            }
        }
    }
    return true;
}
//=============================================================
//=============================================================
void CCCutTouchLayer::beforeDraw()
{
    if (m_bClipsToBounds)
    {
        Point screenPos = this->convertToWorldSpace(Point::ZERO);
        float scaleX = this->getScaleX();
        float scaleY = this->getScaleY();
        for (Node *p = _parent; p != NULL; p = p->getParent())
        {
            scaleX *= p->getScaleX();
            scaleY *= p->getScaleY();
        }
       Rect frame = Rect(screenPos.x, screenPos.y, getContentSize().width*scaleX, getContentSize().height*scaleY);
       glEnable(GL_SCISSOR_TEST);
        Director::getInstance()->getOpenGLView()->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
    }
}
//=============================================================
//=============================================================
void CCCutTouchLayer::afterDraw()
{
    if (m_bClipsToBounds)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}
//=============================================================
//=============================================================
//void CCCutTouchLayer::visit()
//{
//    CCLayerColor::visit();
//    return;  //bingwan test
//	// quick return if not visible
//	if (!isVisible())
//    {
//		return;
//    }
//    
//	kmGLPushMatrix();
//	
//    if (m_pGrid && m_pGrid->isActive())
//    {
//        m_pGrid->beforeDraw();
//        this->transformAncestors();
//    }
//    
//	this->transform();
//    this->beforeDraw();
//    
//	if(m_pChildren)
//    {
//		ccArray *arrayData = m_pChildren->data;
//		unsigned int i=0;
//		
//		// draw children zOrder < 0
//		for( ; i < arrayData->num; i++ )
//        {
//			CCNode *child =  (CCNode*)arrayData->arr[i];
//			if ( child->getZOrder() < 0 )
//            {
//				child->visit();
//			}
//            else
//            {
//				break;
//            }
//		}
//		
//		// this draw
//		this->draw();
//		
//		// draw children zOrder >= 0
//		for( ; i < arrayData->num; i++ )
//        {
//			CCNode* child = (CCNode*)arrayData->arr[i];
//			child->visit();
//		}
//        
//	}
//    else
//    {
//		this->draw();
//    }
//    
//    this->afterDraw();
//	if ( m_pGrid && m_pGrid->isActive())
//    {
//		m_pGrid->afterDraw(this);
//    }
//    
//	kmGLPopMatrix();
//}
//=============================================================
//=============================================================
void CCCutTouchLayer::onNotification()
{
}
//=============================================================
//=============================================================


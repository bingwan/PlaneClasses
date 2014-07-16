
/*
 *
 *  Created by wangbin
 *
 */

#include "CCScrollLayer.h"
USING_NS_CC;

CCScrollLayer::CCScrollLayer():
m_beginPoint(Point::ZERO),
m_containBeginTouchPointFlag(false),
m_contentLayer(NULL),
m_pagingEnable(false),
m_toBoundsDuration(0.3),
m_nextPageDuration(0.3),
m_pageColumnsIndex(0), //列
m_pageRowIndex(0), //行
m_pageMovePercent(0.25),
m_delegate(NULL),
m_touchBeginSelector(NULL),
m_touchMoveSelector(NULL),
m_touchEndSelector(NULL),
m_actionEndSelector(NULL),
m_touchCancelSelector(NULL),
m_endFlag(false),
m_boundsDragDistance(Vertex2F(30,30)),           //超出边界的距离
m_HMoveAbleFlag(false),
m_VMoveAbleFlag(false),
m_decelerateBeginSelector(NULL),
m_decelerateMoveSelector(NULL),
m_decelerateEndSelector(NULL),
m_actionBeginSelector(NULL),
m_actionMoveSelector(NULL),
m_decelerateFlag(false),
m_scrollDotVSprite(NULL),
m_scrollDotHSprite(NULL),
m_percentOfMoveWhenDragOut(0.25),
m_bShowVDot(false),
m_bShowHDot(false),
m_2fLastMoveDis(Vertex2F(0, 0)),
m_fDeceleratePercent(0.95)
{
   ignoreAnchorPointForPosition(false);
}
//=============================================================
//=============================================================
CCScrollLayer::~CCScrollLayer()
{
}
//=============================================================
//=============================================================
CCScrollLayer* CCScrollLayer::scrollLayerWidthColor(const Color4B color,Size size)
{
    CCScrollLayer* scrollLayer = CCScrollLayer::create();
    scrollLayer->initWithColorWidthHeight(color, size.width, size.height);
    return  scrollLayer;
}
//=============================================================
//=============================================================
bool CCScrollLayer::initWithColorWidthHeight(const Color4B color, GLfloat width, GLfloat height)
{
    CCLayerColor::initWithColor(color, width, height);
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    m_contentLayer = CCLayer::create();
    m_contentLayer->setAnchorPoint(Point(0,0));
    m_contentLayer->setPosition(Point(0,0));
    addChild(m_contentLayer);
    
    
    //滑动条
    m_scrollDotVSprite = CCSprite::create("scroll_dot.png");
    //m_scrollDotVSprite->setAnchorPoint(Point(0.5,0));
    Size size = getContentSize();
    Size dotSize = m_scrollDotVSprite->getContentSize();
    m_scrollDotVSprite->setPosition(Point(size.width-dotSize.width,size.height-dotSize.height));
    addChild(m_scrollDotVSprite);
    
    m_scrollDotHSprite = CCSprite::create("scroll_dot.png");
    //m_scrollDotHSprite->setAnchorPoint(Point(0.5,0));
    m_scrollDotHSprite->setPosition(Point(0,0));
    m_scrollDotHSprite->setPosition(Point(dotSize.width,dotSize.height));
    addChild(m_scrollDotHSprite);
    
    m_scrollDotVSprite->setVisible(false);
    m_scrollDotHSprite->setVisible(false);
    
    m_scrollDotVSprite->setOpacity(255*0.5);
    m_scrollDotHSprite->setOpacity(255*0.5);
    
    
    setScrollContentSize(getContentSize());
    setPageSize(getContentSize());
    
    
    Point position = Point(0,m_contentLayer->getContentSize().height - getContentSize().height);
    setContentOffset(position,false);
    
    m_pageColumnsIndex = (m_contentLayer->getContentSize().height-1)/m_pageSize.height;
    

    
	return true;
}
//=============================================================
//=============================================================
void CCScrollLayer::setScrollDotHSprite(const char *pImageNameStr)
{
    Sprite *pDotSpr = Sprite::create(pImageNameStr);
    m_scrollDotHSprite->setTexture(pDotSpr->getTexture());
    m_scrollDotHSprite->setTextureRect(pDotSpr->getTextureRect());
    m_scrollDotHSprite->setContentSize(pDotSpr->getContentSize());
}
//=============================================================
//=============================================================
void CCScrollLayer::setScrollDotVSprite(const char *pImageNameStr)
{
    Sprite *pDotSpr = Sprite::create(pImageNameStr);
    m_scrollDotVSprite->setTexture(pDotSpr->getTexture());
    m_scrollDotVSprite->setTextureRect(pDotSpr->getTextureRect());
    m_scrollDotVSprite->setContentSize(pDotSpr->getContentSize());
}
//=============================================================
//=============================================================
//void CCScrollLayer::registerWithTouchDispatcher(void)
//{    
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, Menu::HANDLER_PRIORITY, false);
//}
//=============================================================
//=============================================================
void CCScrollLayer::setContentOffset(Point offsetPoint,bool actionFlag)
{
    Point position = Point(-offsetPoint.x,-offsetPoint.y);
    if(actionFlag == true)
    {
        moveToAction(position, m_toBoundsDuration);
    }
    else
    {
        m_contentLayer->setPosition(position);
    }
}
//=============================================================
//=============================================================
void CCScrollLayer::setEndFlag(bool flag)
{
}
//=============================================================
//=============================================================
Point CCScrollLayer::getContentOffset()
{
    Point position = m_contentLayer->getPosition();
    Point offset = Point(-position.x,-position.y);
    return offset;
}
//=============================================================
//=============================================================
void CCScrollLayer::refreshDotPosition()
{
    if(m_bShowHDot)
    {
        m_scrollDotHSprite->setVisible(true);
        float dotWidthPercent = getContentSize().width/m_contentLayer->getContentSize().width;
        float dotWidth = dotWidthPercent* getContentSize().width;
        m_scrollDotHSprite->setScaleX(dotWidth/m_scrollDotVSprite->getContentSize().width);
        
        Point offSetPoint =  getContentOffset();
        float maxSpace = m_contentLayer->getContentSize().width - getContentSize().width;
        
        if(offSetPoint.x!=0)
        {
            float positionPercent = offSetPoint.x/maxSpace;
            float percentwidth = positionPercent* (getContentSize().width - dotWidth);
            m_scrollDotHSprite->setPosition(Point(dotWidth/2+percentwidth,m_scrollDotHSprite->getPosition().y));
        }
    }
    else
    {
        m_scrollDotHSprite->setVisible(false);
    }
    if(m_bShowVDot)
    {
        m_scrollDotVSprite->setVisible(true);
        float dotHeightPercent = getContentSize().height/m_contentLayer->getContentSize().height;
        float dotHeight = dotHeightPercent* getContentSize().height;
        m_scrollDotVSprite->setScaleY(dotHeight/m_scrollDotVSprite->getContentSize().height);
        
        float maxSpace = m_contentLayer->getContentSize().height - getContentSize().height;
        Point offSetPoint =  getContentOffset();
        
        if(offSetPoint.y!=0)
        {
            float positionPercent = offSetPoint.y/maxSpace;
            float percentHeight = positionPercent*(getContentSize().height-dotHeight);
            m_scrollDotVSprite->setPosition(Point(m_scrollDotVSprite->getPosition().x,dotHeight/2+percentHeight));
        }
    }
    else
    {
        m_scrollDotVSprite->setVisible(false);
    }
}
//=============================================================
//=============================================================
void CCScrollLayer::setScrollContentSize(Size contentSize)
{
    m_contentLayer->setContentSize(contentSize);
    Point position = Point(0,m_contentLayer->getContentSize().height - getContentSize().height);
    setContentOffset(position,false);
    
    Size size = getContentSize();
    if(contentSize.width < size.width)      contentSize.width = size.width;
    if(contentSize.height < size.height)    contentSize.height = size.height;
    m_contentLayer->setContentSize(contentSize);
    
    if(m_contentLayer->getContentSize().width > getContentSize().width)    //横竖是否可移动
    {
        m_HMoveAbleFlag = true;
        m_bShowHDot = true;
    }
    if(m_contentLayer->getContentSize().height > getContentSize().height)
    {
        m_VMoveAbleFlag = true;
        m_bShowVDot = true;
    }
    //设置边条长度
    refreshDotPosition();    
}
//=============================================================
//=============================================================
void CCScrollLayer::setPageSize(Size pageSize)
{
    m_pageSize = pageSize;
    m_pageColumnsIndex = (m_contentLayer->getContentSize().height-1)/m_pageSize.height;
}
//=============================================================
//=============================================================
Size CCScrollLayer::getScrollContentSize()
{
    return  m_contentLayer->getContentSize();
}
//=============================================================
//=============================================================
void CCScrollLayer::beforeDraw()
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
   // CCEGLView::getInstance()->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
    
}
//=============================================================
//=============================================================
void CCScrollLayer::afterDraw()
{
    glDisable(GL_SCISSOR_TEST);
}
//=============================================================
//=============================================================
//void CCScrollLayer::visit()
//{
//	// quick return if not visible
//	if (!isVisible())
//    {
//		return;
//    }
//    
//	kmGLPushMatrix();
//	
//    if (_grid && _grid->isActive())
//    {
//        _grid->beforeDraw();
//        this->transformAncestors();
//    }
//    
//	this->transform();
//    this->beforeDraw();
//    
//	if(_children)
//    {
//		ccArray *arrayData = _children->data;
//		unsigned int i=0;
//		
//		// draw children zOrder < 0
//		for( ; i < arrayData->num; i++ )
//        {
//			Node *child =  (Node*)arrayData->arr[i];
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
//			Node* child = (Node*)arrayData->arr[i];
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
//	if ( _grid && _grid->isActive())
//    {
//		_grid->afterDraw(this);
//    }
//    
//	kmGLPopMatrix();
//}
//=============================================================
//=============================================================
void CCScrollLayer::addSubChild(Node* node)
{
     m_contentLayer->addChild(node);
}
//=============================================================
//=============================================================
void CCScrollLayer::addSubChild(Node* node,int zOrder)
{
    m_contentLayer->addChild(node,zOrder);
}
//=============================================================
//=============================================================
void CCScrollLayer::moveToAction(Point toPoint, float duration)
{
    sendSelector(SSTE_ACTION_BEGIN);

    ActionInterval* moveTo = CCMoveTo::create(duration, toPoint);
    
    FiniteTimeAction *expire;
    
    expire = CallFuncN::create(CC_CALLBACK_1(CCScrollLayer::scrollDidEnd,this));
    FiniteTimeAction* seq = CCSequence::create(moveTo,
                                          expire,
                                           NULL);
	m_contentLayer->runAction(seq);
    schedule(schedule_selector(CCScrollLayer::actionTick));
}
//=============================================================
//=============================================================
void CCScrollLayer::actionTick(float dt)
{
    sendSelector(SSTE_ACTION_MOVE);
    refreshDotPosition();
}
//=============================================================
//=============================================================
#pragma mark 翻页 边界归位 时停止滑动
void CCScrollLayer::scrollDidEnd(Node* pNode)
{
    unschedule(schedule_selector(CCScrollLayer::actionTick));
    sendSelector(SSTE_ACTION_END);
}
void CCScrollLayer::refreshPosition()
{
    moveToEndPosition(false, m_contentLayer->getPosition());
}
//=============================================================
//=============================================================
void CCScrollLayer::refreshDragOrientation(Point toPoint)
{
    m_boundsDragOriation.HOriention = DOE_UNKNOWN;
    m_boundsDragOriation.VOriention = DOE_UNKNOWN;
    
    Size contentlayerSize = m_contentLayer->getContentSize();
    if(toPoint.x >= 0) //向右拖出边界
    {
        if(toPoint.x >= m_boundsDragDistance.x)
        {
            m_boundsDragOriation.HOriention = DOE_RIGHT;
        }
    }
    else if(toPoint.x <= -(contentlayerSize.width - getContentSize().width))  //向左拖出边界
    {
        float dragDistance = fabsf(-(contentlayerSize.width - getContentSize().width)-toPoint.x);
        if(dragDistance >= m_boundsDragDistance.x)
        {
            m_boundsDragOriation.HOriention = DOE_LEFT;
        }
    }
    
    if(toPoint.y >= 0) //向上拖出边界
    {
        if(toPoint.y >= m_boundsDragDistance.y)
        {
            m_boundsDragOriation.VOriention = DOE_UP;
        }
    }
    else if(toPoint.y <= -(contentlayerSize.height - getContentSize().height)) //向下拖出边界
    {
        float dragDistance = fabsf(-(contentlayerSize.height - getContentSize().height) - toPoint.y);
        if(dragDistance >= m_boundsDragDistance.y)
        {
            m_boundsDragOriation.VOriention = DOE_DOWN;
        }
    }
}
//=============================================================
//=============================================================
bool CCScrollLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!isVisible()) // 父视图改变visible 不影响孩子的变量   //不可见依然接收touch
    { 
        return false;
    }
    
    Node* fatherNode = getParent();
    if(!fatherNode)
        return false;
    
    Point touchPointInWorld = pTouch->getLocation();
    
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
            if(rectInWorld.containsPoint(touchPointInWorld) == false)
            {
                return false;
            }
        }
        
    }
    
   // CCSetIterator it = pTouches->begin();
    Touch* touch = pTouch;
	m_beginPoint = touch->getLocation();
    
    Node* parent = getParent();
    Point localPoint = parent->convertToNodeSpace(m_beginPoint);
    Rect boundRect = boundingBox();
    
    bool unmoveAbleFlag = getContentSize().equals(m_contentLayer->getContentSize());// CCSize::CCSizeEqualToSize(getContentSize(),m_contentLayer->getContentSize());
    if(boundRect.containsPoint(localPoint) && unmoveAbleFlag==false) //点击开始在区域内
    {
        m_containBeginTouchPointFlag = true;
        m_2fLastMoveDis = vertex2(0, 0);
        
        sendSelector(SSTE_TOUCH_BEGIN);
       
        if(m_decelerateFlag)
        {
            m_decelerateFlag = false;
            unschedule(schedule_selector(CCScrollLayer::decelerateTick));
            
        }
        moveToEndPosition(false,m_contentLayer->getPosition());
        return true;
    }
    else
    {
        m_containBeginTouchPointFlag = false;
        return false;
    }
}
//=============================================================
//=============================================================
void CCScrollLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//CCSetIterator it = pTouches->begin();
    Touch* touch = pTouch;
	
	Point movePoint = touch->getLocation();
	Point prePoint = touch->getPreviousLocation();
    
    if(!m_containBeginTouchPointFlag)
        return;
    
    float fMoveX = movePoint.x - prePoint.x;
    float fMoveY = movePoint.y - prePoint.y;
    m_2fLastMoveDis = vertex2(fMoveX, fMoveY);
    
    Node* parent = getParent();
    Point localPoint = parent->convertToNodeSpace(movePoint);
    Rect boundRect = boundingBox();
    
    if(boundRect.containsPoint(localPoint))
    {
        float moveX = movePoint.x - prePoint.x;
        float moveY = movePoint.y - prePoint.y;
        
        Point movePoint = Point::ZERO;
        
        if(m_HMoveAbleFlag)    //横竖是否可移动
        {
            if(m_boundsDragOriation.HOriention != DOE_UNKNOWN) //没超出边界时
            {
                moveX *= m_percentOfMoveWhenDragOut;
            }
            movePoint = Point(m_contentLayer->getPosition().x + moveX,m_contentLayer->getPosition().y);
            
        }
        if(m_VMoveAbleFlag)
        {
            if(m_boundsDragOriation.VOriention != DOE_UNKNOWN) //没超出边界时
            {
                moveY *= m_percentOfMoveWhenDragOut;
            }
            movePoint = Point(movePoint.x,m_contentLayer->getPosition().y + moveY);
        }
        
        refreshDragOrientation(movePoint);     //移动时刷新数据
        m_contentLayer->setPosition(movePoint);  
        refreshDotPosition();
        sendSelector(SSTE_TOUCH_MOVE);
                  
    }
    else //手势移动到边界之外  可能不进入
    {
        m_containBeginTouchPointFlag = false;
        if(m_pagingEnable == true)
        {
            nextPageAction(localPoint);
        }
        else
        {
            moveToEndPosition(false,m_contentLayer->getPosition());
            sendSelector(SSTE_TOUCH_END);
           // beginDeclerate();  //开始减速
        }
    }
    
}

//=============================================================
//=============================================================
void CCScrollLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    Touch* touch = pTouch;
	Point endPoint = touch->getLocation();
    
    Node* parent = getParent();
    if(!parent)
    {
        return;
    }
    Point localPoint = parent->convertToNodeSpace(endPoint);
    Rect boundRect = boundingBox();
    
    if(boundRect.containsPoint(localPoint) && m_containBeginTouchPointFlag)  //结束点是否在区域内
    {
        if(m_pagingEnable == true)
        {
            nextPageAction(localPoint);
        }
        else
        {
            beginDeclerate();  //开始减速
        }
        sendSelector(SSTE_TOUCH_CANCEL);
    }
    else
    {
        if(m_pagingEnable == true)
        {
            if(m_containBeginTouchPointFlag)
            {
                nextPageAction(localPoint);
            }
            
//            setPageRowCount(m_pageRowIndex+1,true);
//            setPageColumnsCount(m_pageColumnsIndex+1,true);
        }
        else
        {
            moveToEndPosition(true, m_contentLayer->getPosition());
        }
    }
}
//=============================================================
//=============================================================
void CCScrollLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
//    CCTouch* touch = pTouch;
//	Point endPoint = touch->getLocation();
//    
//    CCNode* parent = getParent();
//    if(!parent)
//    {
//        return;
//    }
//    Point localPoint = parent->convertToNodeSpace(endPoint);
//    CCRect boundRect = boundingBox();
//    
//    if(boundRect.containsPoint(localPoint) && m_containBeginTouchPointFlag)  //结束点是否在区域内
//    {
//        if(m_pagingEnable == true)
//        {
//            nextPageAction(localPoint);
//        }
//        else
//        {
//            beginDeclerate();  //开始减速
//        }
//        sendSelector(SSTE_TOUCH_CANCEL);
//    }
//    else
//    {
//        if(m_pagingEnable == true)
//        {
//            //nextPageAction(localPoint);
//            setPageRowCount(m_pageRowIndex+1,true);
//            setPageColumnsCount(m_pageColumnsIndex+1,true);
//        }
//        else
//        {
//            moveToEndPosition(true, m_contentLayer->getPosition());
//        }
//    }
}

//=============================================================
//=============================================================
#pragma  翻页
void CCScrollLayer::nextPageAction(Point endPoint)
{
    int allPageRow = (m_contentLayer->getContentSize().width-1)/m_pageSize.width + 1;
    int allPageColumns = (m_contentLayer->getContentSize().height-1)/m_pageSize.height + 1;
    
    Point toPoint = Point(-m_pageRowIndex*m_pageSize.width,-m_pageColumnsIndex*m_pageSize.height);
    
    if(endPoint.x - m_beginPoint.x > m_pageSize.width*m_pageMovePercent )
    {
        m_pageRowIndex--;
        m_pageRowIndex = m_pageRowIndex < 0 ? 0 : m_pageRowIndex;
        toPoint = Point(-m_pageRowIndex*m_pageSize.width,toPoint.y);
    }
    else if(endPoint.x - m_beginPoint.x < -m_pageSize.width*m_pageMovePercent)
    {
        m_pageRowIndex++;
        int lastPageRowIndex = allPageRow-1;
        m_pageRowIndex = m_pageRowIndex > lastPageRowIndex ? lastPageRowIndex : m_pageRowIndex;
        toPoint = Point(-m_pageRowIndex*m_pageSize.width,toPoint.y);
    }
    if(endPoint.y - m_beginPoint.y > m_pageSize.height* m_pageMovePercent )
    {
        m_pageColumnsIndex--;
        m_pageColumnsIndex = m_pageColumnsIndex < 0 ? 0 : m_pageColumnsIndex;
        toPoint = Point(toPoint.x,-m_pageColumnsIndex*m_pageSize.height);
    }
    else if(endPoint.y - m_beginPoint.y < -m_pageSize.height * m_pageMovePercent)
    {
        m_pageColumnsIndex++;
        int lastPageColumnsIndex = allPageColumns-1;
        m_pageColumnsIndex = m_pageColumnsIndex > lastPageColumnsIndex ? lastPageColumnsIndex : m_pageColumnsIndex;
        toPoint = Point(toPoint.x,-m_pageColumnsIndex*m_pageSize.height);
    }
    
    moveToEndPosition(true,toPoint);
}
//=============================================================
//=============================================================
#pragma mark 若超出边界 获得正确的位置 和 超出方向
Point CCScrollLayer::getCorrectPoint(Point toPoint)
{
    m_boundsDragOriation.HOriention = DOE_UNKNOWN;
    m_boundsDragOriation.VOriention = DOE_UNKNOWN;
    
    Size contentlayerSize = m_contentLayer->getContentSize();
    Point toCorrectPosition = toPoint;
    if(toPoint.x >= 0) //向右拖出边界
    {
        if(toPoint.x >= m_boundsDragDistance.x)
        {
            m_boundsDragOriation.HOriention = DOE_RIGHT;
        }
        toCorrectPosition = Point(0,toPoint.y);
    }
    else if(toPoint.x <= -(contentlayerSize.width - getContentSize().width))  //向左拖出边界
    {
        float dragDistance = fabsf(-(contentlayerSize.width - getContentSize().width)-toPoint.x);
        if(dragDistance >= m_boundsDragDistance.x)
        {
            m_boundsDragOriation.HOriention = DOE_LEFT;
        }
        toCorrectPosition = Point(-(contentlayerSize.width - getContentSize().width),toPoint.y);
    }
    
    if(toPoint.y >= 0) //向上拖出边界
    {
        if(toPoint.y >= m_boundsDragDistance.y)
        {
            m_boundsDragOriation.VOriention = DOE_UP;
        }
        toCorrectPosition = Point(toCorrectPosition.x,0);
    }
    else if(toPoint.y <= -(contentlayerSize.height - getContentSize().height)) //向下拖出边界
    {
        float dragDistance = fabsf(-(contentlayerSize.height - getContentSize().height) - toPoint.y);
        if(dragDistance >= m_boundsDragDistance.y)
        {
            m_boundsDragOriation.VOriention = DOE_DOWN;
        }
        
        toCorrectPosition = Point(toCorrectPosition.x,-(contentlayerSize.height - getContentSize().height));
    }
    return toCorrectPosition;
}
//=============================================================
//=============================================================
#pragma  边界归位
void CCScrollLayer::moveToEndPosition(bool auctionFlag,Point toEndPoint)  //边界位置恢复
{
    Point toPosition = getCorrectPoint(toEndPoint);
    
    if(auctionFlag == true)
    {
        moveToAction(toPosition,m_toBoundsDuration);
    }
    else
    {
        m_contentLayer->setPosition(toPosition);
    }
}
//=============================================================
//=============================================================
#pragma mark 设置竖直方向 页数
void  CCScrollLayer::setPageColumnsCount(int columnsCount,bool animateFlag) //竖直方向
{
    int allPageColumns = (m_contentLayer->getContentSize().height-1)/m_pageSize.height + 1;
    Point toPoint = Point(-m_pageRowIndex*m_pageSize.width,-m_pageColumnsIndex*m_pageSize.height);
    
    m_pageColumnsIndex =  columnsCount-1;
    int lastPageColumnsIndex = allPageColumns-1;
    m_pageColumnsIndex = m_pageColumnsIndex > lastPageColumnsIndex ? lastPageColumnsIndex : m_pageColumnsIndex;
    m_pageColumnsIndex = m_pageColumnsIndex < 0 ? 0 : m_pageColumnsIndex;
    toPoint = Point(toPoint.x,-m_pageColumnsIndex*m_pageSize.height);
    
    moveToEndPosition(animateFlag,toPoint);
}
//=============================================================
//=============================================================
#pragma mark 设置水平方向 页数
void  CCScrollLayer::setPageRowCount(int rowCount,bool animateFlag) //水平方向
{
    int allPageRow = (m_contentLayer->getContentSize().width-1)/m_pageSize.width + 1;
    Point toPoint = Point(-m_pageRowIndex*m_pageSize.width,-m_pageColumnsIndex*m_pageSize.height);
    
    m_pageRowIndex =  rowCount-1;
    int lastPageRowIndex = allPageRow-1;
    m_pageRowIndex = m_pageRowIndex > lastPageRowIndex ? lastPageRowIndex : m_pageRowIndex;
    m_pageRowIndex = m_pageRowIndex < 0 ? 0 : m_pageRowIndex;
    toPoint = Point(-m_pageRowIndex*m_pageSize.width,toPoint.y);
    
    moveToEndPosition(animateFlag,toPoint);
}

//=============================================================
//=============================================================
#pragma mark 开始减速
void CCScrollLayer::beginDeclerate()
{
    sendSelector(SSTE_DECELERATE_BEGIN);
    
    if(!m_HMoveAbleFlag)    //横竖是否可移动
    {
        m_2fLastMoveDis.x = 0;
    }
    if(!m_VMoveAbleFlag)
    {
        m_2fLastMoveDis.y = 0;
    }
    
    if(m_decelerateFlag == false  )
    {
        if( fabs(m_2fLastMoveDis.x) > 0.1 || fabs(m_2fLastMoveDis.y) > 0.1)
        {
            m_decelerateFlag = true;
            schedule(schedule_selector(CCScrollLayer::decelerateTick));
        }
    }
}
//=============================================================
//=============================================================
void CCScrollLayer::stopDecelerate()
{
    m_contentLayer->stopAllActions();
    if(m_decelerateFlag)
    {
        m_decelerateFlag = false;
        unschedule(schedule_selector(CCScrollLayer::decelerateTick));
    }
    
    //getCorrectPoint(m_contentLayer->getPosition());
   // moveToEndPosition(false,m_contentLayer->getPosition());
    setContentOffset(Point(0,0),false);
}
//=============================================================
//=============================================================
#pragma mark 减速tick
void CCScrollLayer::decelerateTick(float dt)  
{
    Point oldPosition = m_contentLayer->getPosition();
    refreshDragOrientation(oldPosition);
    if(m_boundsDragOriation.HOriention != DOE_UNKNOWN)
    {
        m_2fLastMoveDis.x = 0;
    }
    if(m_boundsDragOriation.VOriention != DOE_UNKNOWN)
    {
        m_2fLastMoveDis.y = 0;
    }
    
    if(m_2fLastMoveDis.x ==0 && m_2fLastMoveDis.y ==0)
    {
        m_decelerateFlag = false;
        unschedule(schedule_selector(CCScrollLayer::decelerateTick));
        moveToEndPosition(true,oldPosition);
        sendSelector(SSTE_DECELERATE_END);
        return;
    }
    
    m_2fLastMoveDis.x = fabs(m_2fLastMoveDis.x) < 0.1 ? 0 : m_2fLastMoveDis.x;
    m_2fLastMoveDis.y = fabs(m_2fLastMoveDis.y) < 0.1 ? 0 : m_2fLastMoveDis.y;
    
    if(m_2fLastMoveDis.x ==0 && m_2fLastMoveDis.y ==0)
    {
        m_decelerateFlag = false;
        unschedule(schedule_selector(CCScrollLayer::decelerateTick));
        moveToEndPosition(false,oldPosition);
        sendSelector(SSTE_DECELERATE_END);
        return;
    }
    m_2fLastMoveDis.x = m_2fLastMoveDis.x*m_fDeceleratePercent;
    m_2fLastMoveDis.y = m_2fLastMoveDis.y*m_fDeceleratePercent;
    float fNewX = m_contentLayer->getPosition().x + m_2fLastMoveDis.x;
    float fNewY = m_contentLayer->getPosition().y + m_2fLastMoveDis.y;
    Point newPoint = Point(fNewX,fNewY);
    moveToEndPosition(false,newPoint);
    sendSelector(SSTE_DECELERATE_MOVE);
    refreshDotPosition();
}
//=============================================================
//=============================================================
void CCScrollLayer::removeAllContentChildrenWithCleanup(bool cleanup)
{
    m_contentLayer->removeAllChildrenWithCleanup(cleanup);
}
//=============================================================
//=============================================================
# pragma mark 设置回调函数
void CCScrollLayer::setDelegate(Object *delegate, SEL_CallFuncN selector, ScrollSelectorTypeEnum selectorType)
{
    m_delegate = delegate;
    switch (selectorType)
    {
        case SSTE_TOUCH_BEGIN:
        {
            m_touchBeginSelector = selector;
        }
            break;
        case SSTE_TOUCH_MOVE:
        {
            m_touchMoveSelector = selector;
        }
            break;
        case SSTE_TOUCH_END:
        {
            m_touchEndSelector = selector;
        }
            break;
        case SSTE_TOUCH_CANCEL:
        {
            m_touchCancelSelector = selector;
        }
            break;
        case SSTE_ACTION_BEGIN:
        {
            m_actionBeginSelector = selector;
        }
            break;
        case SSTE_ACTION_MOVE:
        {
            m_actionMoveSelector = selector;
        }
            break;
        case SSTE_ACTION_END:
        {
            m_actionEndSelector = selector;
        }
            break;
        case SSTE_DECELERATE_BEGIN:
        {
            m_decelerateBeginSelector = selector;
        }
            break;
        case SSTE_DECELERATE_MOVE:
        {
            m_decelerateMoveSelector = selector;
        }
            break;
        case SSTE_DECELERATE_END:
        {
            m_decelerateEndSelector = selector;
        }
            break;
        default:
            break;
    }
}
//=============================================================
//=============================================================
void CCScrollLayer::sendSelector(ScrollSelectorTypeEnum type)
{
    switch (type)
    {
        case SSTE_TOUCH_BEGIN:
        {
            if(m_delegate!=NULL&&m_touchBeginSelector!=NULL)
            {
                (m_delegate->*m_touchBeginSelector)(this);
            }
        }
            break;
        case SSTE_TOUCH_MOVE:
        {
            if(m_delegate&&m_touchMoveSelector) //回调移动函数
            {
                (m_delegate->*m_touchMoveSelector)(this);
            }
        }
            break;
        case SSTE_TOUCH_END:
        {
            if(m_delegate!=NULL&&m_touchEndSelector!=NULL) //回调end函数
            {
                (m_delegate->*m_touchEndSelector)(this);
            }
        }
            break;
        case SSTE_TOUCH_CANCEL:
        {
            if(m_delegate!=NULL&&m_touchCancelSelector!=NULL) //回调end函数
            {
                (m_delegate->*m_touchEndSelector)(this);
            }
        }
            break;
        case SSTE_ACTION_BEGIN:
        {
            
            if(m_delegate!=NULL&&m_actionBeginSelector!=NULL)
            {
                (m_delegate->*m_actionBeginSelector)(this);
            }
        }
            break;
        case SSTE_ACTION_MOVE:
        {
            
            if(m_delegate!=NULL&&m_actionMoveSelector!=NULL)
            {
                (m_delegate->*m_actionMoveSelector)(this);
            }
        }
            break;
        case SSTE_ACTION_END:
        {
            if(m_delegate!=NULL&&m_actionEndSelector!=NULL)
            {
                (m_delegate->*m_actionEndSelector)(this);
            }
        }
            break;
        case SSTE_DECELERATE_BEGIN:
        {
            if(m_delegate!=NULL&&m_decelerateBeginSelector!=NULL)
            {
                (m_delegate->*m_decelerateBeginSelector)(this);
            }
        }
            break;
        case SSTE_DECELERATE_MOVE:
        {
            if(m_delegate!=NULL&&m_decelerateMoveSelector!=NULL)
            {
                (m_delegate->*m_decelerateMoveSelector)(this);
            }
        }
            break;
        case SSTE_DECELERATE_END:
        {
            if(m_delegate!=NULL&&m_decelerateEndSelector!=NULL)
            {
                (m_delegate->*m_decelerateEndSelector)(this);
            }
        }
            break;
            
        default:
            break;
    }
}
//=============================================================
//=============================================================

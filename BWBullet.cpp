

#include "BWBullet.h"
#include "CCAPI.h"
#include "UserData.h"

#include "BWActionInterval.h"
#include "BWUnitManager.h"

BWBullet::BWBullet()
{
}

BWBullet::~BWBullet()
{
}

bool BWBullet::init(UnitData* pInfo)
{
    BWUnit::init(pInfo);
    
    m_pData = ResManager::shareResManager()->getBulletTabData(pInfo->nId);
    
    _pTextureSprite = Sprite::create(m_pData->pszIcon);
    _pTextureSprite->retain();
    
    _pSlot = pInfo->pSlot;
    
    _pTextureSprite->setPosition(pInfo->pos);
    return true;
}

void BWBullet::onEnter()
{
    
}

void BWBullet::update(float dt)
{
    BWUnit::update(dt);
}

void BWBullet::beginAction()
{
    switch (m_pData->eType)
    {
        case EBulletType_move:
        {
            beginActionMove();
        }
            break;
        case EBulletType_sine:
        {
            beginActionSine();
        }
            break;
        case EBulletType_bezier:
        {
            beginActionBezier();
        }
            break;
        case EBulletType_circle:
        {
            beginActionCircle();
        }
            break;
        case EBulletType_circle_move:
        {
            beginActionCircleMove();
        }
            break;
        default:
            break;
    }
}

void BWBullet::endAction(Node* pNode)
{
    setDead(true);
    BWUnitManager::shareBWUnitManager()->deleteUnitDelay(this);
}

void BWBullet::beginActionMove()
{
    switch (m_pData->eLineType)
    {
        case EBulletLineType_xie_mut: 
        {
            int nLineDegree = m_pData->nBeginDegree + m_pData->nSpaceDegree*_unitData.nBulletIndex;
            float nRadian = CC_DEGREES_TO_RADIANS(nLineDegree);
            int X = m_pData->nLen * cos(nRadian);
            int Y = m_pData->nLen * sin(nRadian);
            
            Point toPointBy = Point(X,Y);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);

            Point moveByPoint = endPoint - getPosition();
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            BWMoveBy* pMoveBy = BWMoveBy::create(fDur,moveByPoint);
            
            Sequence* pSeq = Sequence::create(pMoveBy,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
            
        }
            break;
        case EBulletLineType_v_mut:
        {
            
            int posX = m_pData->nBeginX +  m_pData->nSpaceX * _unitData.nBulletIndex;
            Point movePos = Point(posX,m_pData->nBeginY);
            Point newPoint =  _pSlot->convertToWorldSpace(movePos);
            newPoint = getTextureSprite()->getParent()->convertToNodeSpace(newPoint);
            setPosition(newPoint);
            
            Point toPointBy = Point(0,m_pData->nLen);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - newPoint;
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            BWMoveBy* pMoveBy = BWMoveBy::create(fDur,endByPoint);
            
            Sequence* pSeq = Sequence::create(pMoveBy,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
        }
            break;
            
        default:
            break;
    }
}

void BWBullet::beginActionSine()
{
    switch (m_pData->eLineType)
    {
        case EBulletLineType_xie_mut:
        {
            int nLineDegree = m_pData->nBeginDegree + m_pData->nSpaceDegree*_unitData.nBulletIndex;
            float nRadian = CC_DEGREES_TO_RADIANS(nLineDegree);
            int X = m_pData->nLen * cos(nRadian);
            int Y = m_pData->nLen * sin(nRadian);
            
            
            Point toPointBy = Point(X,Y);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - getPosition();
            
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            BWSineBy* pSineBy = BWSineBy::create(fDur, endByPoint, m_pData->nSineA);
            
            Repeat* pRepeat = Repeat::create(pSineBy, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
            
        }
            break;
        case EBulletLineType_v_mut:
        {
            int posX = m_pData->nBeginX +  m_pData->nSpaceX * _unitData.nBulletIndex;
            Point movePos = Point(posX,m_pData->nBeginY);
            Point newPoint =  _pSlot->convertToWorldSpace(movePos);
            newPoint = getTextureSprite()->getParent()->convertToNodeSpace(newPoint);
            setPosition(newPoint);
            
            Point toPointBy = Point(0,m_pData->nLen);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - newPoint;
            

            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            
            BWSineBy* pSineBy = BWSineBy::create(fDur, endByPoint, m_pData->nSineA);
            
            Repeat* pRepeat = Repeat::create(pSineBy, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
        }
            break;
        default:
            break;
    }
}


void BWBullet::beginActionBezier()
{
    switch (m_pData->eLineType)
    {
        case EBulletLineType_xie_mut:
        {
            int nLineDegree = m_pData->nBeginDegree + m_pData->nSpaceDegree*_unitData.nBulletIndex;
            float nRadian = CC_DEGREES_TO_RADIANS(nLineDegree);
            int X = m_pData->nLen * cos(nRadian);
            int Y = m_pData->nLen * sin(nRadian);
            
            
            Point toPointBy = Point(X,Y);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - getPosition();
            
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            
            
            
            BWBezierConfig config;
            config.controlPoint_1 = Point(-300,endByPoint.y*0.2);
            config.controlPoint_2 = Point(300,endByPoint.y*0.8);
            config.endPosition = endByPoint;
            
            BWBezierBy* pBezier = BWBezierBy::create(fDur,  config);
            Repeat* pRepeat = Repeat::create(pBezier, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
            
        }
            break;
        case EBulletLineType_v_mut:
        {
            
            int posX = m_pData->nBeginX +  m_pData->nSpaceX * _unitData.nBulletIndex;
            Point movePos = Point(posX,m_pData->nBeginY);
            Point newPoint =  _pSlot->convertToWorldSpace(movePos);
            newPoint = getTextureSprite()->getParent()->convertToNodeSpace(newPoint);
            setPosition(newPoint);
            
            Point toPointBy = Point(0,m_pData->nLen);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - newPoint;
            
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            
            BWBezierConfig config;
            config.controlPoint_1 = Point(-300,endByPoint.y*0.2);
            config.controlPoint_2 = Point(300,endByPoint.y*0.8);
            config.endPosition = endByPoint;
            
            BWBezierBy* pBezier = BWBezierBy::create(fDur,  config);
            Repeat* pRepeat = Repeat::create(pBezier, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
        }
            break;
            
        default:
            break;
    }
}

void BWBullet::beginActionCircle()
{
    switch (m_pData->eLineType)
    {
        case EBulletLineType_xie_mut:
        {
            int nLineDegree = m_pData->nBeginDegree + m_pData->nSpaceDegree*_unitData.nBulletIndex;
            float nRadian = CC_DEGREES_TO_RADIANS(nLineDegree);
            int X = m_pData->nLen * cos(nRadian);
            int Y = m_pData->nLen * sin(nRadian);
            
            Point toPointBy = Point(X,Y);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - getPosition();
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            
            BWCircleBy* pCircleBy = BWCircleBy::create(fDur, endByPoint, m_pData->nSineA,Point(0,0));
            Repeat* pRepeat = Repeat::create(pCircleBy, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
            
        }
            break;
        case EBulletLineType_v_mut:
        {
            
            int posX = m_pData->nBeginX +  m_pData->nSpaceX * _unitData.nBulletIndex;
            Point movePos = Point(posX,m_pData->nBeginY);
            Point newPoint =  _pSlot->convertToWorldSpace(movePos);
            newPoint = getTextureSprite()->getParent()->convertToNodeSpace(newPoint);
            setPosition(newPoint);
            
            Point toPointBy = Point(0,m_pData->nLen);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - newPoint;
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            
            BWCircleBy* pCircleBy = BWCircleBy::create(fDur, endByPoint, m_pData->nSineA,Point(0,0));
            Repeat* pRepeat = Repeat::create(pCircleBy, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
        }
            break;
            
        default:
            break;
    }
}

void BWBullet::beginActionCircleMove()
{
    switch (m_pData->eLineType)
    {
        case EBulletLineType_xie_mut:
        {
            int nLineDegree = m_pData->nBeginDegree + m_pData->nSpaceDegree*_unitData.nBulletIndex;
            float nRadian = CC_DEGREES_TO_RADIANS(nLineDegree);
            int X = m_pData->nLen * cos(nRadian);
            int Y = m_pData->nLen * sin(nRadian);
            
            Point toPointBy = Point(X,Y);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - getPosition();
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            
            BWCircleBy* pCircleBy = BWCircleBy::create(fDur, endByPoint, m_pData->nSineA,endByPoint);
            Repeat* pRepeat = Repeat::create(pCircleBy, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
            
        }
            break;
        case EBulletLineType_v_mut:
        {
            
            int posX = m_pData->nBeginX +  m_pData->nSpaceX * _unitData.nBulletIndex;
            Point movePos = Point(posX,m_pData->nBeginY);
            Point newPoint =  _pSlot->convertToWorldSpace(movePos);
            
            if(getTextureSprite()->getParent() == NULL)
            {
                return;
            }
            newPoint = getTextureSprite()->getParent()->convertToNodeSpace(newPoint);
            setPosition(newPoint);
            
            Point toPointBy = Point(0,m_pData->nLen);
            Point endPoint =  _pSlot->convertToWorldSpace(toPointBy);
            endPoint = getTextureSprite()->getParent()->convertToNodeSpace(endPoint);
            Point endByPoint = endPoint - newPoint;
            
            int   nSpeed = _pSlot->getSlotData()->nBulletSpeed;
            float fDur = m_pData->nLen / (float)nSpeed;
            
            BWCircleBy* pCircleBy = BWCircleBy::create(fDur, endByPoint, m_pData->nSineA,endByPoint);
            Repeat* pRepeat = Repeat::create(pCircleBy, m_pData->nRepeat);
            Sequence* pSeq = Sequence::create(pRepeat,
                                              CallFuncN::create(CC_CALLBACK_1(BWBullet::endAction,this)),
                                              NULL);
            _pTextureSprite->runAction(pSeq);
        }
            break;
            
        default:
            break;
    }
}







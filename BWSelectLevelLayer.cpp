
//
//  Created by wangbin on 13-1-14.
//
//

#include "BWSelectLevelLayer.h"
#include "CommonDef.h"
#include "NotificationManager.h"
#include "UIManager.h"
#include "CCAPI.h"
#include "ResManager.h"
#include "RootLayer.h"
#include "BWStreamFile.h"
#include "BWMenu.h"
#include "UserData.h"
#include "CCButton.h"
#include "CCScrollLayer.h"

USING_NS_CC_EXT;

BWSelectLevelLayer::BWSelectLevelLayer():
m_pointBegin(Point::ZERO),
m_pBgLayer(NULL),
m_pBgSprite(NULL),
m_bScrolled(false),
m_nLayerID(-1),
m_bMoved(false),
m_pRenderTexture(NULL)
{
}

BWSelectLevelLayer::~BWSelectLevelLayer()
{
}

BWSelectLevelLayer* BWSelectLevelLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    BWSelectLevelLayer * pLayer = new BWSelectLevelLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool BWSelectLevelLayer::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
    if(CCCutTouchLayer::initWithColor(color, w, h))
    {
        setTag(eUILayerId_Sel_Dun);
        registerCmd();
        return true;
    }
    return false;
}

void BWSelectLevelLayer::registerCmd()
{    
    NotificationManager::shareInstance()->registerCmd(this,eGAME_CMD_ID_ShowSelDungeon ,callfuncND_selector(BWSelectLevelLayer::showUI));
}

void BWSelectLevelLayer::onEnter()
{
    CCCutTouchLayer::onEnter();
    Size contentSize = getContentSize();
    
    CCScrollLayer* pScrollLayer = CCScrollLayer::scrollLayerWidthColor(Color4B(0,0,0,0),contentSize);
    pScrollLayer->setAnchorPoint(Point(0,0));
    pScrollLayer->setPosition(Point(0,0));
    addChild(pScrollLayer);
    
    float fSpaceY = 50;
    float fSpaceX = 60;
    
    float fWidth = 100;
    float fHeight = 100;
    
    float fOriginX = 20;
    float fOriginY = 200;
    
    int nIndexX = 0;
    int nIndexY = 0;
    
    int nAllCount = 10;
    for(int i=0;i<nAllCount;++i)
    {
        CCButton*  pBtnLevel = CCButton::create("input.png");
        //nIndexX = i;
        nIndexY = i;
        Point pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
        pos.x = pScrollLayer->getContentSize().width*0.5;
        
        pBtnLevel->setPosition(pos);
        pBtnLevel->addTargetWithActionForControlEvents(this, cccontrol_selector(BWSelectLevelLayer::clickLevel), Control::EventType::TOUCH_UP_INSIDE);
        pBtnLevel->setTag(i+1);
        pScrollLayer->addSubChild(pBtnLevel);
    }
    Size scrollSize = Size(pScrollLayer->getContentSize().width,fOriginY*2+(fHeight + fSpaceY)*(nAllCount-1)+fHeight);
    pScrollLayer->setScrollContentSize(scrollSize);
    
    
}

void BWSelectLevelLayer::onExit()
{
    CCCutTouchLayer::onExit();
    removeAllChildren();
}

void BWSelectLevelLayer::showUI(Node* pNode,void* p)
{
    eUILayerId layerId = (eUILayerId)getTag();
    UIManager::shareInstance()->showUI(layerId);
}

void BWSelectLevelLayer::clickCombat(Ref *pObject)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowCombat);
}

void BWSelectLevelLayer::clickBack(Ref *pObject)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowSelGroup);
}

void BWSelectLevelLayer::clickLevel(Ref* pOj,Control::EventType controlEvent)
{
    CCButton* pBtn = (CCButton*)pOj;
    int nLevelId = pBtn->getTag();
    UserData::shareUserData()->setLevelId(nLevelId);
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowCombat);
    
}

//void BWSelectLevelLayer::ccTouchesBegan(Set *touches, Event *event)
//{
//}
//
//void BWSelectLevelLayer::ccTouchesMoved(Set *touches, Event *event)
//{
//}
//
//
//void BWSelectLevelLayer::ccTouchesEnded(Set *touches, Event *event)
//{
//}
//void BWSelectLevelLayer::ccTouchesCancelled(Set *touches, Event *event)
//{
//}



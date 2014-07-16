//
//  RootLayer.cpp
//
//  Created by wangbin on 13-1-14.
//
//

#include "RootLayer.h"
#include "CommonDef.h"
#include "cocos-ext.h"
#include "CCAPI.h"
#include "ResManager.h"
#include "NotificationManager.h"
USING_NS_CC_EXT;

#define LOADING_LAYER_TAG 999

RootLayer::RootLayer():
m_pNetPreventLay(NULL),
m_bShowLoading(false),
m_pAlertLayer(NULL)
{
}
//=============================================================
//=============================================================
RootLayer::~RootLayer()
{
}
static RootLayer* s_homeLayer = NULL;
RootLayer*RootLayer::shareRootLayer()
{
    if(NULL == s_homeLayer)
    {
        Size appSize = CCAPI::shareCCAPI()->getAppSize();
        s_homeLayer = RootLayer::create(Color4B(0, 0, 200, 0), appSize.width, appSize.height);
        s_homeLayer->setPreventTouch(false);
    }
    return s_homeLayer;
}
//=============================================================
//=============================================================
RootLayer* RootLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    RootLayer * pLayer = new RootLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}
//=============================================================
//=============================================================
bool RootLayer::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
    if(CCCutTouchLayer::initWithColor(color, w, h))
    {
        setTouchEnabled(false);
        return true;
    }
    return false;
}
#pragma mark  TIPS_LAYER
void RootLayer::showTipsMessage(const char *pMess)
{
    int pLayTag = 22111;
    Node *pNode=getChildByTag(pLayTag);
    if (pNode)
    {
        tipsMessageDisappear(pNode);
    }
    
    Size contentSize  = getContentSize();

    CCCutTouchLayer *pCutLay = CCCutTouchLayer::create(Color4B(0, 0, 0, 180), contentSize.width*0.6, contentSize.height*0.2);
    pCutLay->setAnchorPoint(Point(0.5,0.5));
    pCutLay->setPosition(Point(contentSize.width*0.5,contentSize.height*0.5));
    addChild(pCutLay,TIPS_LAYER_Z);
    pCutLay->setTag(pLayTag);
    
    Size layerSize =pCutLay->getContentSize();
    LabelTTF* pLabel = LabelTTF::create(pMess, COMMON_FONT, FONT_SIZE_32);
    pLabel->setPosition(Point(layerSize.width*0.5,layerSize.height*0.5));
    pCutLay->addChild(pLabel);
    
    
    float movDis = contentSize.height*0.08;
    FiniteTimeAction *pMov  = MoveBy::create(0.5f, Point(0,movDis));
    
    FiniteTimeAction *pFout = FadeOut::create(0.3f);
    CallFuncN *cal = CallFuncN::create(this, callfuncN_selector(RootLayer::tipsMessageDisappear));
    FiniteTimeAction *pSeq = Sequence::create(
                                              CCDelayTime::create(0.3f),
                                              pMov,
                                              CCDelayTime::create(0.3f),
                                              cal,
                                              NULL);
    pCutLay->runAction(pSeq);
}

void RootLayer::tipsMessageDisappear(Node *sender)
{
    sender->stopAllActions();
    sender->removeFromParentAndCleanup(true);
    sender=NULL;
}


void RootLayer::showConnectNetTips()
{
    Size appSize = CCAPI::shareCCAPI()->getAppSize();
    
    if( getChildByTag(LOADING_LAYER_TAG))
    {
        removeChildByTag(LOADING_LAYER_TAG);
    }
    
    m_pNetPreventLay = CCCutTouchLayer::create(Color4B(0, 0, 0, 0), appSize.width, appSize.height);
    m_pNetPreventLay->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    m_pNetPreventLay->setTag(LOADING_LAYER_TAG);
    addChild(m_pNetPreventLay,TIPS_LAYER_Z);
    m_pNetPreventLay->setAnchorPoint(Point(0,0));
    
    Sprite *pLoadSpr = CCAPI::shareCCAPI()->getActionSprite("ui_loading_", 0.06f, 15);
    m_pNetPreventLay->addChild(pLoadSpr);
    pLoadSpr->setPosition(Point(appSize.width*0.5,appSize.height*0.5));

    if(m_bShowLoading)
    {
        unschedule(schedule_selector(RootLayer::waitEnd));
        log("====unscheduleStop");
        m_bShowLoading = false;
    }
    scheduleOnce(schedule_selector(RootLayer::waitEnd), 3.0f);
    m_bShowLoading = true;
    log("====scheduleOnceBegin");
    
}
void RootLayer::hideConnectNetTips()
{
    if(m_bShowLoading)
    {
        unschedule(schedule_selector(RootLayer::waitEnd));
        m_bShowLoading = false;
        log("=================unschedule");
    }
    if( getChildByTag(LOADING_LAYER_TAG))
    {
        removeChildByTag(LOADING_LAYER_TAG);
    }
}

void RootLayer::showMessageDefault(const char* pszMsg)
{
    CCAPI::shareCCAPI()->showAlertView(pszMsg, NULL, "OK");
}

void RootLayer::waitEnd(float dt)
{
    //const char* pszMsg = ResManager::shareResManager()->getStringForKey("key_un_receive");
    showMessageDefault("服务器未返回数据");
    log("=================waitEnd");
    hideConnectNetTips();
}

void RootLayer::onEnter()
{
    CCCutTouchLayer::onEnter();
}

void RootLayer::onExit()
{
    CCCutTouchLayer::onExit();
}

void RootLayer::clickSelectGroupLevel(Object* p)
{
    //CCControlButton* pButton = (CCControlButton*)p;
}

void RootLayer::showAlertLayer(const char* pszMsg, const char* pszOk ,const char* pszCancel ,eGAME_CMD_ID cmdOk,eGAME_CMD_ID cmdCancel)
{
    if(m_pAlertLayer)
    {
        return;
    }
//    CCSize contentSize = getContentSize();
//    m_pAlertLayer = CCCutTouchLayer::create(ccc4(0, 0, 0, 120),APP_WIDTH,APP_HEIGHT);
//    m_pAlertLayer->setPosition(ccp(contentSize.width*0.5,contentSize.height*0.5));
//    addChild(m_pAlertLayer,TIPS_LAYER_Z);
//    
//    CCScale9Sprite* pSpriteBg = CCScale9Sprite::create("Icon-72.png");
//    pSpriteBg->setContentSize(CCSizeMake(200, 200));
//    pSpriteBg->setPosition(ccp(contentSize.width*0.5,contentSize.height*0.5));
//    m_pAlertLayer->addChild(pSpriteBg);
//    
//    CCSize spriteBgSize = pSpriteBg->getContentSize();
//    
//    
//    CCLabelTTF* pLabelMsg = CCLabelTTF::create(pszMsg, KCOMMONFONT, FONT_SIZE_30);
//    pLabelMsg->setPosition(ccp(spriteBgSize.width*0.5,spriteBgSize.height*0.6));
//    m_pAlertLayer->addChild(pLabelMsg);
//    
//    CCButton* pButtonOk = CCButton::create(pszOk, KCOMMONFONT, FONT_SIZE_30);
//    pButtonOk->setPosition(ccp(spriteBgSize.width*0.5,spriteBgSize.height*0.25));
//    pButtonOk->addTargetWithActionForControlEvents(this, cccontrol_selector(RootLayer::clickOkButton),  Control::EventType::TOUCH_UP_INSIDE);
//    pButtonOk->setTag(cmdOk);
//    pSpriteBg->addChild(pButtonOk);
//    
//    if(pszCancel)
//    {
//        pButtonOk->setPosition(ccp(spriteBgSize.width*0.25,spriteBgSize.height*0.25));
//        CCButton* pButtonCancel = CCButton::create(pszCancel, KCOMMONFONT, FONT_SIZE_30);
//        pButtonCancel->setPosition(ccp(spriteBgSize.width*0.75,spriteBgSize.height*0.25));
//        pButtonCancel->addTargetWithActionForControlEvents(this, cccontrol_selector(RootLayer::clickButtonCancel), Control::EventType::TOUCH_UP_INSIDE);
//        pButtonCancel->setTag(cmdCancel);
//        pSpriteBg->addChild(pButtonCancel);
//    }
}

//void RootLayer::clickOkButton( CCButton* pButton)
//{
//    if(m_pAlertLayer)
//    {
//        m_pAlertLayer->removeFromParent();
//        m_pAlertLayer = NULL;
//    }
//    int nCmd = pButton->getTag();
//    NotificationManager::shareInstance()->pushCMD((eGAME_CMD_ID)nCmd);
//    
//}
//
//void RootLayer::clickButtonCancel( CCButton* pButton)
//{
//    if(m_pAlertLayer)
//    {
//        m_pAlertLayer->removeFromParent();
//        m_pAlertLayer = NULL;
//    }
//    int nCmd = pButton->getTag();
//    NotificationManager::shareInstance()->pushCMD((eGAME_CMD_ID)nCmd);
//}








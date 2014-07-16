

/*
 *
 *  Created by wangbin
 *
 */

#include "RootScene.h"
#include "CCAPI.h"

RootScene::RootScene():
m_pMemoryLabel(NULL)
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Point(0.5f, 0.5f));
}
//=============================================================
//=============================================================
RootScene::~RootScene()
{
}
//=============================================================
//=============================================================
bool RootScene::init()
{
    if(CCScene::init())
    {
        return true;
    }
    return false;
}
//=============================================================
//=============================================================
RootScene *RootScene::create()
{
    RootScene *pRet = new RootScene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}
//=============================================================
//=============================================================
void RootScene::updateLabel(float dt)
{
    if(!m_pMemoryLabel) return;
    float fMemory = CCAPI::shareCCAPI()->getMemory();
    char szMemory[64]={};
    sprintf(szMemory, "%0.4f",(float)fMemory);
    m_pMemoryLabel->setString(szMemory);
}
//=============================================================
//=============================================================
void RootScene::showMemoryLabel()
{
    Size contentSize = getContentSize();
    m_pMemoryLabel = LabelTTF::create("memory", "Arial", 35);
    m_pMemoryLabel->setPosition(Point(contentSize.width*0.1,contentSize.height*0.2));
    m_pMemoryLabel->setColor(Color3B::RED);
    addChild(m_pMemoryLabel,999);
    schedule(schedule_selector(RootScene::updateLabel),1.0);
}
//=============================================================
//=============================================================





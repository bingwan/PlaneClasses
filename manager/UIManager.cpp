

#include "UIManager.h"
#include "CommonDef.h"
#include "NotificationManager.h"
#include "RootLayer.h"
#include "ResManager.h"
#include "BWHomeLayer.h"
#include "BWCombatLayer.h"
#include "CCAPI.h"
#include "BWSelectLevelLayer.h"

UIManager* UIManager::shareInstance()
{
    static UIManager* s_UIInstance = NULL;
    if(NULL == s_UIInstance)
    {
        s_UIInstance = new UIManager();
    }
    return s_UIInstance;
}
//=============================================================
//=============================================================
UIManager::UIManager()
{}
//=============================================================
//=============================================================
UIManager::~UIManager()
{
    std::map<eUILayerId,CCCutTouchLayer*>::iterator it = m_mapLayer.begin();
    while (it != m_mapLayer.end())
    {
        CC_SAFE_RELEASE(it->second);
        it++;
    }
}
//=============================================================
//=============================================================
void UIManager::RegisterAllUILayer()
{
    Size appSize = CCAPI::shareCCAPI()->getAppSize();
    
    std::map<eUILayerId,UILayerData>* pMapLayersData = ResManager::shareResManager()->getLayersData();
    if(!pMapLayersData)
    {
        return;
    }
    std::map<eUILayerId,UILayerData>::iterator it = pMapLayersData->begin();
    while (it != pMapLayersData->end())
    {
        CCCutTouchLayer* pCutLayer = NULL;
        switch ((int)it->first)
        {
            case eUILayerId_Home:
            {
                pCutLayer = BWHomeLayer::create(Color4B(0, 0, 0, 0), appSize.width, appSize.height);
            }
                break;
            case eUILayerId_Combat:
            {
                pCutLayer = BWCombatLayer::create(Color4B(0, 0, 0, 0),  appSize.width, appSize.height);
            }
                break;
            case eUILayerId_Shop:
            {
                //pCutLayer = GTShopLayer::create(Color4B(0, 0, 0, 0),  appSize.width, appSize.height);
            }
                break;
            case eUILayerId_Login_test:
            {
            }
                break;
            case eUILayerId_Edit:
            {
                //pCutLayer = HomeLayer::create(Color4B(0, 0, 0,0),  appSize.width, appSize.height);
            }
                break;
            case eUILayerId_Sel_Group:
            {
            }
                break;
            case eUILayerId_Sel_Dun:
            {
                pCutLayer = BWSelectLevelLayer::create(Color4B(0, 0, 0,0),  appSize.width, appSize.height);
            }
                break;
            case eUILayerId_SelRole:
            {
            }
                break;
            case eUILayerId_CreateRole:
            {
            }
                break;
            case eUILayerId_ServerList:
            {
            }
                break;
            case eUILayerId_Register:
            {
            }
                break;
            case eUILayerId_Login:
            {
            }
                break;
            
        }
        CC_SAFE_RETAIN(pCutLayer);
        if(pCutLayer)
        {
             m_mapLayer.insert(std::make_pair(it->first, pCutLayer));
        }
        it++;
    }
}
//=============================================================
//=============================================================
CCCutTouchLayer* UIManager::getUILayer(eUILayerId eLayerId)
{
    std::map<eUILayerId,CCCutTouchLayer*>::iterator it = m_mapLayer.find(eLayerId);
    if(it != m_mapLayer.end())
    {
        return it->second;
    }
    return NULL;
}
//=============================================================
//=============================================================
void UIManager::showUI(eUILayerId eLayerId)
{
    if(eUILayerId_Unknown == eLayerId )
        return;
    RootLayer* pRootLayer = RootLayer::shareRootLayer();
    CCCutTouchLayer* pNewLayer = getUILayer(eLayerId);
    if(!pNewLayer)
        return;
    UILayerData* pLayerData = ResManager::shareResManager()->getLayerData(eLayerId);
    if(!pLayerData)
        return;
    //if(pLayerData->bCleanPreLayer)
    {
        removeAllUI();
    }
    Size rootLayerSize = pRootLayer->getContentSize();
    pNewLayer->setAnchorPoint(Point(0.5,0.5));
    pNewLayer->setPosition(Point(rootLayerSize.width*0.5,rootLayerSize.height*0.5));
    pRootLayer->addChild(pNewLayer,pLayerData->nZOrder);
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    CCTextureCache::getInstance()->removeUnusedTextures();


}
//=============================================================
//=============================================================
void UIManager::removeUI(eUILayerId eLayerId)
{
    if(eUILayerId_Unknown == eLayerId)
        return;
    CCCutTouchLayer* pCutLayer = getUILayer(eLayerId);
    if(!pCutLayer)
        return;
    RootLayer::shareRootLayer()->removeChild(pCutLayer);
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

}
//=============================================================
//=============================================================
void UIManager::removeAllUI()
{
    RootLayer* pRootLayer = RootLayer::shareRootLayer();
    pRootLayer->removeAllChildren();
    

}
//=============================================================
//=============================================================












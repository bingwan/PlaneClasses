//
//  BWHomeLayer.cpp
//  ESGame
//
//  Created by wangbin on 13-1-14.
//
//

#include "BWHomeLayer.h"
#include "CommonDef.h"
#include "NotificationManager.h"
#include "UIManager.h"
#include "CCAPI.h"
#include "ResManager.h"
#include "RootLayer.h"
#include "BWStreamFile.h"
#include "BWMenu.h"
#include "BWCCMenuItemImage.h"
#include "UserData.h"
#include "CCButton.h"
#include "BWEditLayer.h"

USING_NS_CC_EXT;

BWHomeLayer::BWHomeLayer():
m_pBgLayer(NULL),
m_pBgSprite(NULL)
{
    _eBuildingType = EBuildingType_unknown;
}

BWHomeLayer::~BWHomeLayer()
{
}

BWHomeLayer* BWHomeLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    BWHomeLayer * pLayer = new BWHomeLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool BWHomeLayer::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
    if(CCCutTouchLayer::initWithColor(color, w, h))
    {
        setTag(eUILayerId_Home);
        registerCmd();
        return true;
    }
    return false;
}


void BWHomeLayer::registerCmd()
{    
    NotificationManager::shareInstance()->registerCmd(this,eGAME_CMD_ID_ShowHome ,callfuncND_selector(BWHomeLayer::showUI));
}

void BWHomeLayer::onEnter()
{
    CCCutTouchLayer::onEnter();
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    initUI();
}

void BWHomeLayer::onExit()
{
    CCCutTouchLayer::onExit();
    removeAllChildren();
    _vBtnDetail.clear();
}
void BWHomeLayer::showUI(Node* pNode,void* p)
{
    eUILayerId layerId = (eUILayerId)getTag();
    UIManager::shareInstance()->showUI(layerId);
}
void BWHomeLayer::initUI()
{
    Size cntentSize = getContentSize();
    CCButton*  pBtnCloseGuide = CCButton::create("level",COMMON_FONT,50);
    pBtnCloseGuide->setPosition(Point(cntentSize.width*0.5,cntentSize.height*0.5));
    pBtnCloseGuide->addTargetWithActionForControlEvents(this, cccontrol_selector(BWHomeLayer::clickLevel), Control::EventType::TOUCH_UP_INSIDE);
    addChild(pBtnCloseGuide);
    
    CCButton*  pBtnEdit = CCButton::create("edit",COMMON_FONT,50);
    pBtnEdit->setPosition(Point(cntentSize.width*0.5,cntentSize.height*0.2));
    pBtnEdit->addTargetWithActionForControlEvents(this, cccontrol_selector(BWHomeLayer::clickEdit), Control::EventType::TOUCH_UP_INSIDE);
    addChild(pBtnEdit);
    
}
void BWHomeLayer::clickLevel(Ref* pObject,Control::EventType controlEvent)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowSelDungeon);
}

void BWHomeLayer::clickEdit(Ref* pObject,Control::EventType controlEvent)
{
    Size cntentSize = getContentSize();
    
    BWEditLayer* pCutLayer = BWEditLayer::create();
    pCutLayer->ignoreAnchorPointForPosition(false);
    pCutLayer->setPosition(Point(cntentSize.width*0.5,cntentSize.height*0.5));
    addChild(pCutLayer);

}

void BWHomeLayer::clickShowSetting(Object *pObject)
{
}


void BWHomeLayer::clickCombat(Object *pObject)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowSelGroup);
}
void BWHomeLayer::clickGoShop(Object *pObject)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowShop);
}

void BWHomeLayer::clickEdit(Object* pObject)
{
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowEditHome);
}

void BWHomeLayer::clickBuilding(Object* pObject)
{
    BWCCMenuItemImage* pBtn = (BWCCMenuItemImage*)pObject;
    _eBuildingType = (EBuildingType)pBtn->getTag();
    
//    BuildingData* pBuilding = UserData::shareUserData()->getBuildingData(_eBuildingType);
//
//    if(!pBuilding)
//        return;
   // _pBtnUpgrade->setTitleNormalLabel();
    setBtnDetailVisible(false, false);
    setBtnDetailVisible(true,true);
    
    switch (_eBuildingType)
    {
        case EBuildingType_hall:
        case EBuildingType_buildGold1:
        case EBuildingType_buildGold2:
        case EBuildingType_buildGold3:
        case EBuildingType_buildMagic:
        case EBuildingType_goldWarehouse:
        {
            //_pBtnFunction->setVisible(false);
            enterFunctionLayer(NULL);
            return;
        }
            break;
        default:
            break;
    }
}

void BWHomeLayer::setBtnDetailVisible(bool bVisible,bool bAnimate)
{
    Size contentSize = getContentSize();
    float fSpaceY = 100;
    float fFirstY = contentSize.height*0.5 - fSpaceY;
    
    float fFirstDur = 0.25;
    
    for(int i=0;i<_vBtnDetail.size();i++)
    {
        int nPosI = _vBtnDetail.size()-1 -i;
        BWCCMenuItemImage* pBtn = _vBtnDetail[i];
        Point pos = pBtn->getPosition();
        
        if(bVisible)
        {
            pos.x = contentSize.width - 100;
            pos.y = fFirstY + fSpaceY * nPosI;
        }
        else
        {
            pos.x = contentSize.width + pBtn->getContentSize().width;
        }
        if(bAnimate)
        {
            MoveTo* pMove = MoveTo::create(fFirstDur, pos);
            EaseBackInOut* pEase = EaseBackInOut::create(pMove);
            pBtn->runAction(pEase);
            fFirstDur = fFirstDur + 0.06*nPosI;
        }
        else
        {
            pBtn->stopAllActions();
            pBtn->setPosition(pos);
        }
    }
}

void BWHomeLayer::clickBuildingDetail(Object* pObject)
{
     setBtnDetailVisible(false,true);
//     BuildingData* pBuilding =  UserData::shareUserData()->getBuildingData(_eBuildingType);
//     if(!pBuilding)
//         return;
    
    //setInfoBgVisible(true,true);
    //_pBuildingInfoLayer->setVisible(true);
    //Sprite* p
    // building_info_bg
    
//    Size contentSize = getContentSize();
//
//    GTBuildingInfoLayer* pInfoLayer = GTBuildingInfoLayer::create(Color4B(0,200,0,0), contentSize.width, contentSize.height);
//    pInfoLayer->setPosition(Point(contentSize.width*0.5,contentSize.height*0.5));
//    addChild(pInfoLayer);
    
    
    
}

void BWHomeLayer::clickUpgradeBuilding(Object* pObject)
{

}

void BWHomeLayer::enterFunctionLayer(Object* pObject)
{
}



bool BWHomeLayer::onTouchBegan(Touch *touch, Event *event)
{
    return false;
}

void BWHomeLayer::onTouchMoved(Touch *touch, Event *event)
{}

void BWHomeLayer::onTouchEnded(Touch *touch, Event *event)
{}

void BWHomeLayer::onTouchCancelled(Touch *touch, Event *event)
{}

//void BWHomeLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
//{
//}
//
//void BWHomeLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
//{}
//
//
//void BWHomeLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
//{}
//
//
//void BWHomeLayer::onTouchesCancelled(const std::vector<Touch*>&touches, Event *event)
//{}

void BWHomeLayer::refreshPos(Point newPos)
{
}

void BWHomeLayer::deaccelerateScrolling(float dt)
{
}












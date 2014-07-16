

#include "BWDetailNPCLayer.h"
#include "BWEditLayer.h"
#include "BWTextEdit.h"
#include "BWMenu.h"
#include "BWEditBulletLayer.h"
#include "BWActionLayer.h"
#include "BWBornLayer.h"
#include "CCAPI.h"

BWDetailNPCLayer::BWDetailNPCLayer():
m_ownedLayer(NULL),
m_npcId(INVALID_ID),
m_posXEdit(NULL),
m_posYEdit(NULL),
m_rotateEdit(NULL),
m_TriggerDisEdit(NULL),
m_menu(NULL),
m_zOrderEdit(NULL),
m_scrollMenu(NULL),
m_scrollLayer(NULL),
m_flipXEdit(NULL),
m_flipYEdit(NULL)
{	
}

BWDetailNPCLayer::~BWDetailNPCLayer()
{
	m_ownedLayer = NULL;
	m_npcId = INVALID_ID;
}

BWDetailNPCLayer* BWDetailNPCLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    BWDetailNPCLayer * pLayer = new BWDetailNPCLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool BWDetailNPCLayer::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
    if(CCCutTouchLayer::initWithColor(color, w, h))
    {
        setTouchEnabled(true);
        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        return true;
    }
    return false;
}

    
void  BWDetailNPCLayer::onEnter()
{
    CCCutTouchLayer::onEnter();
    initUI();
}

void  BWDetailNPCLayer::onExit()
{
    CCCutTouchLayer::onExit();
    removeAllChildren();
}

bool BWDetailNPCLayer::initUI()
{
    Size contentSize = getContentSize();

    CCScrollLayer* pScrollLayer = CCScrollLayer::scrollLayerWidthColor(Color4B(),contentSize);
    pScrollLayer->setAnchorPoint(Point(0,0));
    pScrollLayer->setPosition(Point(0,0));
    addChild(pScrollLayer);
    
    
    Size inputSize = Size(100,60);
    int nFontSize = 30;

    float fSpaceY = 20;
    float fSpaceX = 10;
    
    float fWidth = 100;
    float fHeight = 100;
    
    float fOriginX = 20;
    float fOriginY = 20;
    
    int nIndexX = 0;
    int nIndexY = 0;
    Point pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    const char* randId = "npcId";
	LabelTTF *Index1Label = CCLabelTTF::create(randId,"", nFontSize);
    Index1Label->setPosition(pos);
	pScrollLayer->addSubChild(Index1Label);
   
    nIndexX++;
    //nIndexY = 0;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	LabelTTF *pLabelId = CCLabelTTF::create("id","", nFontSize);
	pLabelId->setPosition(pos);
	pScrollLayer->addSubChild(pLabelId);

    nIndexX++;
    //nIndexY = 0;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    const char* posX = "posX";
	LabelTTF *posXLabel = CCLabelTTF::create(posX,"", nFontSize);
	posXLabel->setPosition(pos);
	pScrollLayer->addSubChild(posXLabel);
    
    nIndexX++;
    //nIndexY = 0;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    m_posXEdit = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_posXEdit->setText("posX");
	m_posXEdit->setPosition(pos);
	pScrollLayer->addSubChild(m_posXEdit);
	
    nIndexX++;
    //nIndexY = 0;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    const char* posY = "posY";
	LabelTTF *posYLabel = CCLabelTTF::create(posY,"", nFontSize);
	posYLabel->setPosition(pos);
	pScrollLayer->addSubChild(posYLabel);
	
    nIndexX++;
    //nIndexY = 0;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	m_posYEdit = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_posYEdit->setText("posY");
	m_posYEdit->setPosition(pos);
	pScrollLayer->addSubChild(m_posYEdit);
	
    nIndexX = 0;
    nIndexY = 1;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	const char* rotate = "rotate";
	LabelTTF *rotateLabel = LabelTTF::create(rotate,"", nFontSize);
	rotateLabel->setPosition(pos);
	pScrollLayer->addSubChild(rotateLabel);

    nIndexX++;
    nIndexY = 1;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	m_rotateEdit = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_rotateEdit->setText("rotate");
	m_rotateEdit->setPosition(pos);
	pScrollLayer->addSubChild(m_rotateEdit);
		
	nIndexX++;
    nIndexY = 1;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    const char* trigger = "trigger";
	LabelTTF *TriggerDisLabel = CCLabelTTF::create(trigger,"", nFontSize);
	TriggerDisLabel->setPosition(pos);
	pScrollLayer->addSubChild(TriggerDisLabel);
	
	nIndexX++;
    nIndexY = 1;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	m_TriggerDisEdit = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_TriggerDisEdit->setText("trigger");
	m_TriggerDisEdit->setPosition(pos);
	pScrollLayer->addSubChild(m_TriggerDisEdit);

    nIndexX++;
    nIndexY = 1;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    LabelTTF* label = LabelTTF::create("Z:","", 30);
	label->setPosition(pos);
	pScrollLayer->addSubChild(label);
	
    nIndexX++;
    nIndexY = 1;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	m_zOrderEdit = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_zOrderEdit->setText("zOrder");
	m_zOrderEdit->setPosition(pos);
	pScrollLayer->addSubChild(m_zOrderEdit);
    
    nIndexX = 0;
    nIndexY = 2;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    label = LabelTTF::create("水平翻转","", 30);
	label->setPosition(pos);
	pScrollLayer->addSubChild(label);
	
    nIndexX ++;
    nIndexY = 2;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	m_flipXEdit = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_flipXEdit->setText("0");
	m_flipXEdit->setPosition(pos);
	pScrollLayer->addSubChild(m_flipXEdit);
    
    nIndexX ++;
    nIndexY = 2;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
    label = LabelTTF::create("竖直翻转","", 30);
	label->setPosition(pos);
	pScrollLayer->addSubChild(label);
    
	nIndexX ++;
    nIndexY = 2;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    pos.y = contentSize.height - pos.y;
	m_flipYEdit = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_flipYEdit->setText("0");
	m_flipYEdit->setPosition(pos);
	pScrollLayer->addSubChild(m_flipYEdit);
    
    initBottomMenu();
    
	return true;
}

void BWDetailNPCLayer::initBottomMenu()
{
    Size contentSize = getContentSize();
    int nFontSize = 30;
    
    float fSpaceY = 20;
    float fSpaceX = 10;
    
    float fWidth = 100;
    float fHeight = 100;
    
    float fOriginX = 20;
    float fOriginY = 20;
    
    int nIndexX = 0;
    int nIndexY = 0;
   
    
    m_menu = Menu::create();
	m_menu->setPosition(Point(0,0));
	addChild(m_menu);
    
    Point pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
	LabelTTF* confirmLabel = LabelTTF::create("保存", "", 30);
	MenuItemLabel* confirmItem = MenuItemLabel::create(confirmLabel, this, menu_selector(BWDetailNPCLayer::clickConfirm));
	confirmItem->setPosition(pos);
    m_menu->addChild(confirmItem, 0);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    LabelTTF* actionLabel = LabelTTF::create("编辑动作", "Arial", 30);
    MenuItemLabel* actionItem = MenuItemLabel::create(actionLabel, this, menu_selector(BWDetailNPCLayer::editNpcAction));
    actionItem->setPosition(pos);
    m_menu->addChild(actionItem,0);
    
}

void BWDetailNPCLayer::bornItem(Ref* pObject)
{
    Size winSize = getContentSize();
    
    BWBornLayer* bornLayer = BWBornLayer::create();
    bornLayer->initWithColorWidthHeight(Color4B(100, 200, 100, 255), winSize.width,winSize.height);
    bornLayer->setAnchorPoint(Point(0,0));
    bornLayer->setPosition(Point(0,0));
    bornLayer->setdetailLayer(this);
    addChild(bornLayer);
    
    setEnable(false);
    bornLayer->setVisible(true);
    bornLayer->setEnable(true);
    bornLayer->setBornData(&m_pCurNpcData->npcData);
}

#pragma add slot
void BWDetailNPCLayer::addSlot(Ref* pObject)
{
    Size winSize = getContentSize();
    BWEditBulletLayer* editBulletLayer = BWEditBulletLayer::create();
    editBulletLayer->initWithColorWidthHeight(Color4B(100, 200, 200, 255), winSize.width, winSize.height);
    editBulletLayer->setOwnedLayer(this);
    editBulletLayer->setVisible(true);
    editBulletLayer->setEnable(true);
    editBulletLayer->setAnchorPoint(Point(0,0));
    editBulletLayer->setPosition(Point(0,0));
    addChild(editBulletLayer);

    
    setEnable(false);
}

#pragma  npc Action
void BWDetailNPCLayer::editNpcAction(Ref* pObject)
{
    Size contentSize = getContentSize();
    
    BWActionLayer* pActionLayer = BWActionLayer::create(Color4B(0, 0, 0, 255), contentSize.width,contentSize.height);
    pActionLayer->setAnchorPoint(Point(0,0));
    pActionLayer->setPosition(Point(0,0));
    pActionLayer->setdetailLayer(this);
    addChild(pActionLayer);
    
    pActionLayer->setActionData(&m_pCurNpcData->npcData.actData);
}

void BWDetailNPCLayer::setSelectNpcId(int npcId) //npcId=guid
{
	m_npcId = npcId;
    m_pCurNpcData = m_ownedLayer->getNpcData(m_npcId);
	dataToText(m_pCurNpcData);
}

void BWDetailNPCLayer::setBulletData()
{
}

#pragma edit bullet
void BWDetailNPCLayer::editBullet(Ref* pObject)
{
}

void BWDetailNPCLayer::textToData(EditNpcData* pNpc)
{
    if(!pNpc) return;
	
	const char* pPosXEdit = m_posXEdit->getText();
	pNpc->npcData.pos.x = atof(pPosXEdit);
	const char* pPosYEdit = m_posYEdit->getText();
	pNpc->npcData.pos.y = atof(pPosYEdit);
	
	const char* npcRotate = m_rotateEdit->getText();
	pNpc->npcData.rotate= atof(npcRotate);

	const char* pTriggerDis = m_TriggerDisEdit->getText();
	pNpc->npcData.triggerDistance= atof(pTriggerDis);

    const char* zOrder = m_zOrderEdit->getText();
	pNpc->npcData.zOrder= atoi(zOrder);
    
    const char* flipX = m_flipXEdit->getText();
	pNpc->npcData.flipX= atoi(flipX);
    
    const char* flipY = m_flipYEdit->getText();
	pNpc->npcData.flipY= atoi(flipY);
}

void BWDetailNPCLayer::dataToText(EditNpcData* pNpc)
{
    if(pNpc == NULL)
        return;
    m_zOrderEdit->setText("0");
    m_posXEdit->setText("0");
    m_posYEdit->setText("0");
    m_rotateEdit->setText("0");
    m_TriggerDisEdit->setText("0");
    m_flipXEdit->setText("0");
    m_flipYEdit->setText("0");
    
	char tempMsg[COMMON_STRING_SIZE]={0,0};
	memset(tempMsg,0,COMMON_STRING_SIZE);
	sprintf(tempMsg,"%.2f",pNpc->npcData.pos.x);
	m_posXEdit->setText(tempMsg);
	
	memset(tempMsg,0,COMMON_STRING_SIZE);
	sprintf(tempMsg,"%.2f",pNpc->npcData.pos.y);
	m_posYEdit->setText(tempMsg);
	
	memset(tempMsg,0,COMMON_STRING_SIZE);
	sprintf(tempMsg,"%.2f",pNpc->npcData.rotate);
	m_rotateEdit->setText(tempMsg); 

	memset(tempMsg,0,COMMON_STRING_SIZE);
	sprintf(tempMsg,"%.2f",pNpc->npcData.triggerDistance);
	m_TriggerDisEdit->setText(tempMsg);
	
    memset(tempMsg,0,COMMON_STRING_SIZE);
	sprintf(tempMsg,"%d",pNpc->npcData.zOrder);
	m_zOrderEdit->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
	sprintf(tempMsg,"%d",pNpc->npcData.flipX);
	m_flipXEdit->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
	sprintf(tempMsg,"%d",pNpc->npcData.flipY);
	m_flipYEdit->setText(tempMsg);
    
    //setBulletData();
}

void BWDetailNPCLayer::clickConfirm(Ref* pObject)
{
    setVisible(false);
    
	textToData(m_pCurNpcData);
	m_ownedLayer->reDrawNpc(m_npcId);
	//m_ownedLayer->returnFromDetailNpcLayer();
}

void BWDetailNPCLayer::setEnable(bool ableFlag)
{
//    setTouchEnabled(ableFlag);
//    m_menu->setTouchEnabled(ableFlag);
//    m_scrollMenu->setTouchEnabled(ableFlag);
//    m_posXEdit->setTouchEnabled(ableFlag);
//    m_posYEdit->setTouchEnabled(ableFlag);
//    m_rotateEdit->setTouchEnabled(ableFlag);
//    m_TriggerDisEdit->setTouchEnabled(ableFlag);
//    m_zOrderEdit->setTouchEnabled(ableFlag);
//    m_flipXEdit->setTouchEnabled(ableFlag);
//    m_flipYEdit->setTouchEnabled(ableFlag);
    
    
}

bool BWDetailNPCLayer::onTouchBegan(Touch *touch, Event *event)
{
    if(CCCutTouchLayer::onTouchBegan(touch, event))
    {
        return true;
    }
    return false;
}

void BWDetailNPCLayer::onTouchMoved(Touch *touch, Event *event)
{
}

void BWDetailNPCLayer::onTouchEnded(Touch *touch, Event *event)
{
}





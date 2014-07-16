

#include "BWEditBulletLayer.h"
#include "CCScrollLayer.h"
#include "BWTextEdit.h"
#include "BWEditLayer.h"
#include "BWDetailNPCLayer.h"
#include "BWMenu.h"
#include "BWActionLayer.h"



BWEditBulletLayer::BWEditBulletLayer():
m_bulletIdField(NULL),
m_slotPosXField(NULL),
m_slotPosYField(NULL),
m_slotIntervalField(NULL),
m_bulletDataStr(NULL),
m_slotRotateField(NULL),
m_bulletIndex(-1),
m_scrollLayer(NULL),
m_slotIdField(NULL),
m_slotRotatePosXField(NULL),
m_slotRotatePosYField(NULL),
m_slotFirePosXField(NULL),
m_slotFirePosYField(NULL),
m_bulletTypeField(NULL),
m_bulletEndIdField(NULL),
m_slotVisibleField(NULL)
{
}

BWEditBulletLayer::~BWEditBulletLayer()
{
}

bool BWEditBulletLayer::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
   
    
    m_scrollLayer = CCScrollLayer::scrollLayerWidthColor(ccc4(30, 60, 70, 255), Size(winSize.width,winSize.height/2));
    m_scrollLayer->setAnchorPoint(ccp(0,0));
    m_scrollLayer->setPosition(ccp(0,0));
    addChild(m_scrollLayer);
    
    int spaceX = 10;
    int spaceY = 30;
    float width = 110;
    float height = 30;
    
    int fontSize = 20;
    
    int widthCount = 0;
    int heightCount = 0;
    
    Size inputSize = Size(100,60);
    
    const char* slotId = "slotId"; //gBWLocalizationManagerPtr->getText("key_edit_solt_id");
    
    CCLabelTTF* label = CCLabelTTF::create(slotId, "", fontSize);
    CCPoint position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotIdField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotIdField;
    m_slotIdField->setText("slotId");
    m_slotIdField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotIdField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotIdField);
    
    const char* rotate = "rotate";//gBWLocalizationManagerPtr->getText("key_edit_solt_rotate");
    label = CCLabelTTF::create(rotate, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotRotateField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotRotateField;
    m_slotRotateField->setText("rotate");
    m_slotRotateField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotRotateField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotRotateField);
    
    
    const char* interval = "interval"; //gBWLocalizationManagerPtr->getText("key_edit_solt_interval");
    label = CCLabelTTF::create(interval, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotIntervalField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotIntervalField;
    m_slotIntervalField->setText("interval");
    m_slotIntervalField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotIntervalField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotIntervalField);
    
    heightCount++;
    widthCount = 0;
    
    const char* posX = "posX";//gBWLocalizationManagerPtr->getText("key_edit_solt_pos_x");
    
    label = CCLabelTTF::create(posX, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotPosXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotPosXField;
    m_slotPosXField->setText("posX");
    m_slotPosXField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotPosXField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotPosXField);
    
    const char* posY = "posY";//gBWLocalizationManagerPtr->getText("key_edit_solt_pos_y");
    label = CCLabelTTF::create(posY, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotPosYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotPosYField;
    m_slotPosYField->setText("posY");
    m_slotPosYField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotPosYField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotPosYField);
    
    
    const char* visible = "visible";//gBWLocalizationManagerPtr->getText("key_edit_solt_visible");
    label = CCLabelTTF::create(visible, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotVisibleField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotVisibleField;
    m_slotVisibleField->setText("visible");
    m_slotVisibleField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotVisibleField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotVisibleField);
    
    
    heightCount++;
    widthCount = 0;
    
    const char* rotatePosX = "rotatePosX";//gBWLocalizationManagerPtr->getText("key_edit_solt_rotate_pos_x");
    label = CCLabelTTF::create(rotatePosX, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotRotatePosXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotRotatePosXField;
    m_slotRotatePosXField->setText("rotatePosX");
    m_slotRotatePosXField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotRotatePosXField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotRotatePosXField);
    
    
    const char* rotatePosY = "rotatePosY";//gBWLocalizationManagerPtr->getText("key_edit_solt_rotate_pos_y");
    label = CCLabelTTF::create(rotatePosY, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotRotatePosYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotRotatePosYField;
    m_slotRotatePosYField->setText("rotatePosY");
    m_slotRotatePosYField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotRotatePosYField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotRotatePosYField);
    
    heightCount++;
    widthCount = 0;
    
    const char* firePosX = "firePosX";//gBWLocalizationManagerPtr->getText("key_edit_solt_fire_pos_x");
    label = CCLabelTTF::create(firePosX, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotFirePosXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotFirePosXField;
    m_slotFirePosXField->setText("firePosX");
    m_slotFirePosXField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotFirePosXField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotFirePosXField);
    
    
    const char* firePosY = "firePosY";// gBWLocalizationManagerPtr->getText("key_edit_solt_fire_pos_y");
    label = CCLabelTTF::create(firePosY, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_slotFirePosYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_slotFirePosYField;
    m_slotFirePosYField->setText("firePosY");
    m_slotFirePosYField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_slotFirePosYField->setPosition(position);
    m_scrollLayer->addSubChild(m_slotFirePosYField);
    
    heightCount++;
    widthCount = 0;
    
    const char* bulletId = "bulletId";//gBWLocalizationManagerPtr->getText("key_edit_bullet_id");
    label = CCLabelTTF::create(bulletId, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_bulletIdField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_bulletIdField;
    m_bulletIdField->setText("bulletId");
    m_bulletIdField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_bulletIdField->setPosition(position);
    m_scrollLayer->addSubChild(m_bulletIdField);
    
    
    const char* bulletType = "bulletType";//gBWLocalizationManagerPtr->getText("key_edit_bullet_type");
    label = CCLabelTTF::create(bulletType, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_bulletTypeField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_bulletTypeField;
    m_bulletTypeField->setText("bulletType");
    m_bulletTypeField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_bulletTypeField->setPosition(position);
    m_scrollLayer->addSubChild(m_bulletTypeField);
    
    
    const char* bulletEndId = "bulletEndId";//gBWLocalizationManagerPtr->getText("key_edit_bullet_end_id");
    label = CCLabelTTF::create(bulletEndId, "", fontSize);
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(position);
    label->setColor(ccORANGE);
    m_scrollLayer->addSubChild(label);
    
    m_bulletEndIdField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
    m_bulletEndIdField;
    m_bulletEndIdField->setText("bulletEndId");
    m_bulletEndIdField->setAnchorPoint(ccp(0,0));
    position = ccp(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_bulletEndIdField->setPosition(position);
    m_scrollLayer->addSubChild(m_bulletEndIdField);
    
    heightCount++;
    m_scrollLayer->setScrollContentSize(CCSizeMake(winSize.width, spaceY + (spaceY+height)*heightCount));
    
    m_menu = CCMenu::create();
    m_menu->setAnchorPoint(ccp(0,0));
    m_menu->setPosition(ccp(0,0));
    addChild(m_menu);
    
    CCLabelTTF* backLabel = CCLabelTTF::create("返回", "", 30);
    CCMenuItemLabel* backItem = CCMenuItemLabel::create(backLabel, this, menu_selector(BWEditBulletLayer::back));
    backItem->setPosition(ccp(winSize.width-100,50));
    m_menu->addChild(backItem, 0);
    
    
    CCLabelTTF* slotLabel = CCLabelTTF::create("炮筒动作", "", 30);
    CCMenuItemLabel* slotItem = CCMenuItemLabel::create(slotLabel, this, menu_selector(BWEditBulletLayer::editSlotAction));
    slotItem->setPosition(ccp(winSize.width-100,100));
    m_menu->addChild(slotItem, 0);
    
    CCLabelTTF* bulletLabel = CCLabelTTF::create("子弹动作", "", 30);
    CCMenuItemLabel* bulletItem = CCMenuItemLabel::create(bulletLabel, this, menu_selector(BWEditBulletLayer::editBulletAction));
    bulletItem->setPosition(ccp(winSize.width-100,150));
    m_menu->addChild(bulletItem, 0);
    
    CCLabelTTF* deleteLabel = CCLabelTTF::create("删除", "", 30);
    deleteLabel->setColor(ccRED);
    CCMenuItemLabel* deleteItem = CCMenuItemLabel::create(deleteLabel, this, menu_selector(BWEditBulletLayer::deleteSlot));
    deleteItem->setPosition(ccp(winSize.width-100,200));
    m_menu->addChild(deleteItem, 0);
    
    
    return true;
}

bool BWEditBulletLayer::initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
    CCLayerColor::initWithColor(color, width, height);
    return  true;
}

void BWEditBulletLayer::deleteSlot(Object* p)
{
    m_bulletDataStr->vBornSlot[m_bulletIndex].clear();
    
    m_bulletDataStr->vBornSlot.erase(m_bulletDataStr->vBornSlot.begin() + m_bulletIndex);
    
    m_ownedLayer->setEnable(true);
    m_ownedLayer->setBulletData();
    
    removeFromParentAndCleanup(true);
}
 

void BWEditBulletLayer::editSlotAction(Object* p)
{
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    
//    BWActionLayer* actionLayer = BWActionLayer::create();
//    actionLayer->initWithColor(ccc4(50, 200, 10, 255), winSize.width,winSize.height/2);
//    actionLayer->setVisible(true);
//    actionLayer->setEnable(true);
//    actionLayer->setEditBulletLayer(this);
//    actionLayer->setAnchorPoint(ccp(0,0));
//    actionLayer->setPosition(ccp(0,winSize.height/2));
//    addChild(actionLayer);
//    
//    ActionData* pActionData = &m_bulletDataStr->vBornSlot[m_bulletIndex].slotActionData;
//    actionLayer->setActionData(pActionData);
//    
//    setEnable(false);
}


void BWEditBulletLayer::editBulletAction(Object* p)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    BWActionLayer* actionLayer = BWActionLayer::create(Color4B(10, 200, 10, 255), winSize.width,winSize.height/2);
    actionLayer->setVisible(true);
    actionLayer->setEnable(true);
    actionLayer->setEditBulletLayer(this);
    actionLayer->setAnchorPoint(ccp(0,0));
    actionLayer->setPosition(ccp(0,winSize.height/2));
    addChild(actionLayer);
    
    ActionData* pActionData = &m_bulletDataStr->vBornSlot[m_bulletIndex].bulData.bulletActionData;
    actionLayer->setActionData(pActionData);
    setEnable(false);
}

void BWEditBulletLayer::setOwnedLayer(BWDetailNPCLayer* layer)
{
    m_ownedLayer = layer;
}

void BWEditBulletLayer::back(Object* pObject)
{
    getBulletData(m_bulletDataStr, m_bulletIndex);
    m_ownedLayer->setEnable(true);
    m_ownedLayer->setBulletData();
    
    removeFromParentAndCleanup(true);
}


void BWEditBulletLayer::setBulletData(BulletSlotData* pBulletDataStr,int bulletIndex)
{
    m_bulletDataStr = pBulletDataStr;
    m_bulletIndex = bulletIndex;
        
    m_slotIdField->setText("0");
    m_slotIntervalField->setText("0");
    m_slotPosXField->setText("0");
    m_slotPosYField->setText("0");
    m_slotRotateField->setText("0");
    m_slotRotatePosXField->setText("0");
    m_slotRotatePosYField->setText("0");
    m_slotFirePosXField->setText("0");
    m_slotFirePosYField->setText("0");
    m_slotVisibleField->setText("0");
    
    m_bulletIdField->setText("-1");
    m_bulletTypeField->setText("0");
    m_bulletEndIdField->setText("-1");
    
    
    char tempMsg[COMMON_STRING_SIZE]={0,0};
    

    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_bulletDataStr->vBornSlot[m_bulletIndex].slot_id);
    m_slotIdField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_bulletDataStr->vBornSlot[m_bulletIndex].slot_visible);
    m_slotVisibleField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].born_interval);
    m_slotIntervalField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].slot_rotate );
    m_slotRotateField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].slot_pos_x);
    m_slotPosXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].slot_pos_y);
    m_slotPosYField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].rotate_pos_x);
    m_slotRotatePosXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].rotate_pos_y);
    m_slotRotatePosYField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].fire_pos_x);
    m_slotFirePosXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_bulletDataStr->vBornSlot[m_bulletIndex].fire_pos_y);
    m_slotFirePosYField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    int bulletId = m_bulletDataStr->vBornSlot[m_bulletIndex].bulData.bulletId;
    sprintf(tempMsg,"%d",bulletId);
    m_bulletIdField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    int bulletType = m_bulletDataStr->vBornSlot[m_bulletIndex].bulData.bulletType;
    sprintf(tempMsg,"%d",bulletType);
    m_bulletTypeField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    int bulletEndId = m_bulletDataStr->vBornSlot[m_bulletIndex].bulData.bulletEndId;
    sprintf(tempMsg,"%d",bulletEndId);
    m_bulletEndIdField->setText(tempMsg);
    
}

void BWEditBulletLayer::getBulletData(BulletSlotData* pBulletDataStr,int bulletIndex)
{
    if(!m_bulletDataStr) return;
    
    BornSlot born = m_bulletDataStr->vBornSlot[m_bulletIndex];
    
    const char* slotIdText = m_slotIdField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].slot_id = atoi(slotIdText);
    
    const char* slotVisibleText = m_slotVisibleField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].slot_visible = atoi(slotVisibleText);
    

    const char* bulletIntervalText = m_slotIntervalField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].born_interval = atof(bulletIntervalText);
    
    const char* slotRotateText = m_slotRotateField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].slot_rotate = atof(slotRotateText);
    
    const char* slotPosXText = m_slotPosXField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].slot_pos_x = atof(slotPosXText);
    
    const char* slotPosYText = m_slotPosYField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].slot_pos_y = atof(slotPosYText);

    const char* rotatePosXText = m_slotRotatePosXField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].rotate_pos_x = atof(rotatePosXText);
    
    const char* rotatePosYText = m_slotRotatePosYField->getText();

    m_bulletDataStr->vBornSlot[m_bulletIndex].rotate_pos_y = atof(rotatePosYText);

    const char* firePosXText = m_slotFirePosXField->getText();

    m_bulletDataStr->vBornSlot[m_bulletIndex].fire_pos_x = atof(firePosXText);
    
    const char* firePosYText = m_slotFirePosYField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].fire_pos_y = atof(firePosYText);

    const char* bulletIdText = m_bulletIdField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].bulData.bulletId = atoi(bulletIdText);
    
    const char* bulletTypeText = m_bulletTypeField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].bulData.bulletType = (characterTypeEnum)atoi(bulletTypeText);
    
    const char* bulletEndIdText = m_bulletEndIdField->getText();
    m_bulletDataStr->vBornSlot[m_bulletIndex].bulData.bulletEndId = atoi(bulletEndIdText);

    
}


void BWEditBulletLayer::setEnable(bool ableFlag)
{
//    setTouchEnabled(ableFlag);
//    m_menu->setTouchEnabled(ableFlag);
//    
//    m_slotIdField->setTouchEnabled(ableFlag);
//    m_slotIntervalField->setTouchEnabled(ableFlag);
//    m_slotPosXField->setTouchEnabled(ableFlag);
//    m_slotPosYField->setTouchEnabled(ableFlag);
//    m_slotRotateField->setTouchEnabled(ableFlag);
//    m_slotRotatePosXField->setTouchEnabled(ableFlag);
//    m_slotRotatePosYField->setTouchEnabled(ableFlag);
//    m_slotFirePosXField->setTouchEnabled(ableFlag);
//    m_slotFirePosYField->setTouchEnabled(ableFlag);
//    m_slotVisibleField->setTouchEnabled(ableFlag);
//    
//    m_bulletIdField->setTouchEnabled(ableFlag);
//    m_bulletTypeField->setTouchEnabled(ableFlag);
//    m_bulletEndIdField->setTouchEnabled(ableFlag);
    
}





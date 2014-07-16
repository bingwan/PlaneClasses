
#include "BWActionLayer.h"
#include "CCScrollLayer.h"
#include "BWTextEdit.h"
#include "BWEditLayer.h"
#include "BWDetailNPCLayer.h"
#include "BWMenu.h"
#include "BWEditBulletLayer.h"
#include "BWActionInterval.h"
#include "CCAPI.h"

BWActionLayer::BWActionLayer():
m_bezierDurationField(NULL),
m_bezierOnePointXField(NULL),
m_bezierOnePointYField(NULL),
m_bezierTwoPointXField(NULL),
m_bezierTwoPointYField(NULL),
m_bezierEndPointXField(NULL),
m_bezierEndPointYField(NULL),
m_jumpDurationField(NULL),
m_jumpHeightField(NULL),
m_jumpEndPointXField(NULL),
m_jumpEndPointYField(NULL),
m_jumpCountField(NULL),
m_scaleDurationField(NULL),
m_scaleXField(NULL),
m_scaleYField(NULL),
m_rotateDurationField(NULL),
m_rotateAngleField(NULL),
m_tintDurationField(NULL),
m_tintRedField(NULL),
m_tintGreenField(NULL),
m_tintBlueField(NULL),
m_fadeInDurationField(NULL),
m_fadeOutDurationField(NULL),
m_blinkDurationField(NULL),
m_blinkCountField(NULL),
m_skewDurationField(NULL),
m_skewXField(NULL),
m_skewYField(NULL),
m_moveDurationField(NULL),
m_moveEndPointXField(NULL),
m_moveEndPointYField(NULL),
m_moveOrderField(NULL),
m_detailLayer(NULL),
m_bezierOrderField(NULL),
m_jumpOrderField(NULL),
m_scaleOrderField(NULL),
m_rotateOrderField(NULL),
m_tintOrderField(NULL),
m_fadeInOrderField(NULL),
m_fadeOutOrderField(NULL),
m_blinkOrderField(NULL),
m_skewOrderField(NULL),
m_repeatCountField(NULL),
m_menu(NULL),
m_actionType(AT_UNKNOWN),
m_actionTypeTogItem(NULL),
m_bezierRepeatCountField(NULL),
m_jumpRepeatCountField(NULL),
m_scaleRepeatCountField(NULL),
m_rotateRepeatCountField(NULL),
m_tintRepeatCountField(NULL),
m_fadeInRepeatCountField(NULL),
m_fadeOutRepeatCountField(NULL),
m_blinkRepeatCountField(NULL),
m_skewRepeatCountField(NULL),
m_moveRepeatCountField(NULL),
m_pBulletData(NULL),
m_delayTimeDurationField(NULL),
m_delayTimeOrderField(NULL),
m_bulletIndex(-1),
m_editBulletLayer(NULL)
{
}

BWActionLayer::~BWActionLayer()
{
}

BWActionLayer* BWActionLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    BWActionLayer * pLayer = new BWActionLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}


bool BWActionLayer::initWithColor(const Color4B& color, GLfloat width, GLfloat height)
{
    //color = Color4B(0,0,0,200);
    if(CCCutTouchLayer::initWithColor(color, width, height))
    {
        setTouchEnabled(true);
        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        
        addTextField(color);
        
        m_menu = CCMenu::create();
        m_menu->setAnchorPoint(Point(0,0));
        m_menu->setPosition(Point(0,0));
        addChild(m_menu);
        // m_menu->setIsVisible(false);
        
        LabelTTF* backLabel = LabelTTF::create("返回", "", 30);
        MenuItemLabel* backItem = MenuItemLabel::create(backLabel,CC_CALLBACK_1(BWActionLayer::clickClose,this));
        backItem->setPosition(Point(width-50,80));
        m_menu->addChild(backItem, 0);
        return true;
    }
    return false;
}

void BWActionLayer::setdetailLayer(BWDetailNPCLayer* layer)
{
    m_detailLayer = layer;
}

void BWActionLayer::setEditBulletLayer(BWEditBulletLayer* layer)
{
    m_editBulletLayer = layer;
}

void BWActionLayer::clickClose(Ref* pRef)
{
    getActionData(m_pActionData);
    sortAction(m_pActionData);
    
    removeFromParent();
}

void BWActionLayer::addTextField(Color4B color)
{
    
	Size contentSize = getContentSize();
    
    m_scrollLayer = CCScrollLayer::scrollLayerWidthColor(color,contentSize);
    m_scrollLayer->setAnchorPoint(Point(0,0));
    m_scrollLayer->setPosition(Point(0,0));
    addChild(m_scrollLayer);
    
    m_scrolMenu = BWMenu::create();
    m_scrolMenu->setAnchorPoint(Point(0,0));
    m_scrolMenu->setPosition(Point(0,0));
    m_scrollLayer->addSubChild(m_scrolMenu);

    
    int nFontSize = 30;
    
    float fSpaceY = 50;
    float fSpaceX = 60;
    
    float fWidth = 100;
    float fHeight = 100;
    
    float fOriginX = 20;
    float fOriginY = 20;
    
    int nIndexX = 0;
    int nIndexY = 0;
    
    //move
    Size inputSize = Size(100, 60);
    
    Point pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    LabelTTF* label = LabelTTF::create("移动时间:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_moveDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_moveDurationField->setText("Duration");
    m_moveDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_moveDurationField);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("order", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_moveOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_moveOrderField->setText("Order");
    m_moveOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_moveOrderField);
    

    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    LabelTTF* noreverseLabel = LabelTTF::create("noReverse", "", nFontSize);
    LabelTTF* reverseLabel = LabelTTF::create("reverse", "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    MenuItemLabel* noReverseItem = MenuItemLabel::create(noreverseLabel);
    MenuItemLabel* reverseItem = MenuItemLabel::create(reverseLabel);
    MenuItemToggle* tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_MOVE);
    m_scrolMenu->addChild(tog, 40);


    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("repeatCount", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_moveRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_moveRepeatCountField->setText("count");
    m_moveRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_moveRepeatCountField);
    
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* noReverse = "noReverse";
    const char* reverse = "reverse";
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_MOVE+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("移动结束点X", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_moveEndPointXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_moveEndPointXField->setText("moveEndPosX");
    m_moveEndPointXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_moveEndPointXField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("移动结束点Y", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_moveEndPointYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_moveEndPointYField->setText("moveEndPosY");
    m_moveEndPointYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_moveEndPointYField);
    
    //==================================================
    nIndexX=0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("曲线:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_bezierDurationField->setText("Duration");
    m_bezierDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierDurationField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* order = "order";
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_bezierOrderField->setText("Order");
    m_bezierOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierOrderField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_BEZIER);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* repeatCount ="repeatCount";
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_bezierRepeatCountField->setText("count");
    m_bezierRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierRepeatCountField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_BEZIER+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
   
    nIndexX=0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("点1X", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierOnePointXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_bezierOnePointXField->setText("OnePointX");
    m_bezierOnePointXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierOnePointXField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("点1Y", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierOnePointYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_bezierOnePointYField->setText("OnePointY");
    m_bezierOnePointYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierOnePointYField);
    

    
    nIndexX=0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("点2X", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierTwoPointXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));; 
    m_bezierTwoPointXField->setText("TwoPointX");
    m_bezierTwoPointXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierTwoPointXField);
    
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("点2Y", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierTwoPointYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));; 
    m_bezierTwoPointYField->setText("TwoPointY");
    m_bezierTwoPointYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierTwoPointYField);
    

    nIndexX=0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("点3X", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierEndPointXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));; 
    m_bezierEndPointXField->setText("EndPointX");
    m_bezierEndPointXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierEndPointXField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("点3Y", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_bezierEndPointYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));; 
    m_bezierEndPointYField->setText("EndPointY");
    m_bezierEndPointYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_bezierEndPointYField);
    
    //========================================================
    //jump
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("跳时间:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_jumpDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_jumpDurationField->setText("jumpDuration");
    m_jumpDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_jumpDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_jumpOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_jumpOrderField->setText("Order");
    m_jumpOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_jumpOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_JUMP);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_jumpRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_jumpRepeatCountField->setText("count");
    m_jumpRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_jumpRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_JUMP+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    //========================================================
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("跳高度", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_jumpHeightField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_jumpHeightField->setText("jumpHeight");
    m_jumpHeightField->setPosition(pos);
    m_scrollLayer->addSubChild(m_jumpHeightField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("跳次数", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_jumpCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_jumpCountField->setText("jumpCount");
    m_jumpCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_jumpCountField);
    
    //========================================================
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("跳结束点X", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_jumpEndPointXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_jumpEndPointXField->setText("jumpEndPointX");
    m_jumpEndPointXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_jumpEndPointXField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("跳结束点Y", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_jumpEndPointYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_jumpEndPointYField->setText("jumpEndPointY");
    m_jumpEndPointYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_jumpEndPointYField);
    
    //========================================================
    //scale
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    
    label = LabelTTF::create("放大时间", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_scaleDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_scaleDurationField->setText("scaleDuration");
    m_scaleDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_scaleDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_scaleOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_scaleOrderField->setText("Order");
    m_scaleOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_scaleOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_SCALE);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_scaleRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_scaleRepeatCountField->setText("count");
    m_scaleRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_scaleRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_SCALE+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    //========================================================
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("放大X:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_scaleXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_scaleXField->setText("scaleX");
    m_scaleXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_scaleXField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("放大Y:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_scaleYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_scaleYField->setText("scaleY");
    m_scaleYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_scaleYField);
    
    //========================================================
    //rotate
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("旋转时间:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_rotateDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_rotateDurationField->setText("rotateDuration");
    m_rotateDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_rotateDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_rotateOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_rotateOrderField->setText("Order");
    m_rotateOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_rotateOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    // Point(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    tog->setPosition(pos);
    tog->setTag(AT_ROTATE);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_rotateRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_rotateRepeatCountField->setText("count");
    m_rotateRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_rotateRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_ROTATE+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);

    //========================================================
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("旋转角度:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_rotateAngleField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_rotateAngleField->setText("rotateAngle");
    m_rotateAngleField->setPosition(pos);
    m_scrollLayer->addSubChild(m_rotateAngleField);
    
    //========================================================
    //tint
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("渐变时间:", "", nFontSize);
    // Point(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_tintDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_tintDurationField->setText("tintDuration");
    m_tintDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_tintDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_tintOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_tintOrderField->setText("Order");
    m_tintOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_tintOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_TINT);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_tintRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_tintRepeatCountField->setText("count");
    // Point(spaceX+ width/2+(spaceX + width)*(widthCount++), spaceY + (spaceY+height)*heightCount);
    m_tintRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_tintRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_TINT+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    //========================================================
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("红:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_tintRedField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_tintRedField->setText("tintRed");
    m_tintRedField->setPosition(pos);
    m_scrollLayer->addSubChild(m_tintRedField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("绿:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_tintGreenField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_tintGreenField->setText("tintGreen");
    m_tintGreenField->setPosition(pos);
    m_scrollLayer->addSubChild(m_tintGreenField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("蓝:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_tintBlueField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_tintBlueField->setText("tintBlue");
    m_tintBlueField->setPosition(pos);
    m_scrollLayer->addSubChild(m_tintBlueField);

    //========================================================
    //fadeIn
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("出现时间:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_fadeInDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_fadeInDurationField->setText("fadeInDuration");
    m_fadeInDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_fadeInDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_fadeInOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_fadeInOrderField->setText(order);
    m_fadeInOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_fadeInOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_FADEIN);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_fadeInRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_fadeInRepeatCountField->setText("count");
    m_fadeInRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_fadeInRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_FADEIN+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    

    //========================================================
    //fadeOut
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(" 消失时间:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_fadeOutDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_fadeOutDurationField->setText("fadeOutDuration");
    m_fadeOutDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_fadeOutDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_fadeOutOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_fadeOutOrderField->setText("Order");
    m_fadeOutOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_fadeOutOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_FADEOUT);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_fadeOutRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_fadeOutRepeatCountField->setText("count");
    m_fadeOutRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_fadeOutRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_FADEOUT+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);

    //========================================================
    //blink
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("闪烁:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_blinkDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_blinkDurationField->setText("blinkDur");
    m_blinkDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_blinkDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_blinkOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_blinkOrderField->setText("Order");
    m_blinkOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_blinkOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_BLINK);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_blinkRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_blinkRepeatCountField->setText("count");
    m_blinkRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_blinkRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_BLINK+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    
    //========================================================
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("闪烁次数:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_blinkCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_blinkCountField->setText("blinkCount");
    m_blinkCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_blinkCountField);
  
    //========================================================
    //skew
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("翻转:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_skewDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_skewDurationField->setText("skewDuration");
    m_skewDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_skewDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_skewOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_skewOrderField->setText("Order");
    m_skewOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_skewOrderField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_SKEW);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_skewRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_skewRepeatCountField->setText("count");
    m_skewRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_skewRepeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_SKEW+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    //========================================================
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("翻转X:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_skewXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_skewXField->setText("skewX");
    m_skewXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_skewXField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("翻转Y:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_skewYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_skewYField->setText("skewY");
    m_skewYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_skewYField);
    
    //========================================================
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("延迟时间:", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_delayTimeDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_delayTimeDurationField->setText("delayDur");
    m_delayTimeDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_delayTimeDurationField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(order, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_delayTimeOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_delayTimeOrderField->setText("Order");
    m_delayTimeOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_delayTimeOrderField);
    
    //================================================
    //sine
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("Sine", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_sineDurationField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_sineDurationField->setText("Duration");
    m_sineDurationField->setPosition(pos);
    m_scrollLayer->addSubChild(m_sineDurationField);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("order", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_sineOrderField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_sineOrderField->setText("Order");
    m_sineOrderField->setPosition(pos);
    m_scrollLayer->addSubChild(m_sineOrderField);
    
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create("noReverse", "", nFontSize);
    reverseLabel = LabelTTF::create("reverse", "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(ActionType_sine);
    m_scrolMenu->addChild(tog, 40);
    
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("repeatCount", "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::RED);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_sineRepeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_sineRepeatCountField->setText("count");
    m_sineRepeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_sineRepeatCountField);
    
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::RED);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(ActionType_sine+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    
    nIndexX = 0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("结束点X:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_sineEndPointXField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_sineEndPointXField->setText("endPosX");
    m_sineEndPointXField->setPosition(pos);
    m_scrollLayer->addSubChild(m_sineEndPointXField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("结束点Y:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_sineEndPointYField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_sineEndPointYField->setText("EndPosY");
    m_sineEndPointYField->setPosition(pos);
    m_scrollLayer->addSubChild(m_sineEndPointYField);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create("sineA:", "", nFontSize);
    label->setPosition(pos);
    m_scrollLayer->addSubChild(label);
    
    nIndexX++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_sineAField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_sineAField->setText("sineA");
    m_sineAField->setPosition(pos);
    m_scrollLayer->addSubChild(m_sineAField);
    
    //============================================================
    
    nIndexX =0;
    nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    LabelTTF* seqLabel = LabelTTF::create("序列", "", nFontSize);
    seqLabel->setColor(Color3B::BLUE);
    LabelTTF* spawnLabel = LabelTTF::create("同步", "", nFontSize);
    spawnLabel->setColor(Color3B::BLUE);
    MenuItemLabel* seqItem = MenuItemLabel::create(seqLabel);
    MenuItemLabel* spawnItem = MenuItemLabel::create(spawnLabel);
    m_actionTypeTogItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectActionType,this),seqItem,NULL);
    m_actionTypeTogItem->addSubItem(spawnItem);
    m_actionTypeTogItem->setPosition(pos);
    m_scrolMenu->addChild(m_actionTypeTogItem, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::BLUE);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_REPEAT);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = LabelTTF::create(repeatCount, "", nFontSize);
    label->setPosition(pos);
    label->setColor(Color3B::BLUE);
    m_scrollLayer->addSubChild(label);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_repeatCountField = EditBox::create(inputSize, Scale9Sprite::create("input.png"));;
    m_repeatCountField->setText("count");
    m_repeatCountField->setPosition(pos);
    m_scrollLayer->addSubChild(m_repeatCountField);
    
    nIndexX ++;
    //nIndexY++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    noreverseLabel = LabelTTF::create(noReverse, "", nFontSize);
    reverseLabel = LabelTTF::create(reverse, "", nFontSize);
    reverseLabel->setColor(Color3B::BLUE);
    noReverseItem = MenuItemLabel::create(noreverseLabel);
    reverseItem = MenuItemLabel::create(reverseLabel);
    tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(BWActionLayer::selectReverse,this),noReverseItem,NULL);
    tog->addSubItem(reverseItem);
    tog->setPosition(pos);
    tog->setTag(AT_REPEAT+REPEAT_COUNT_TAG);
    m_scrolMenu->addChild(tog, MENU_UNUSED_Z);

    nIndexY++;
    m_scrollLayer->setScrollContentSize(Size(contentSize.width*2, fSpaceY + (fSpaceY+fHeight) * nIndexY));
    
}

void BWActionLayer::selectReverse(Ref* pRef)
{
    MenuItemToggle* selItem = (MenuItemToggle*)pRef;
    int index = selItem->getSelectedIndex();
    if(index==0)
    {
         log("noReverse");
    }
    else
    {
        log("reverse");
    }
}

void BWActionLayer::selectActionType(Ref* pRef)
{
    MenuItemToggle* selItem = (MenuItemToggle*)pRef;
    int index = selItem->getSelectedIndex();
    
    switch (index)
    {
        case 0:
        {
            log("seq");
            m_actionType = AT_SEQ;
        }
            break;
            
        case 1:
        {
            log("spawn");
            m_actionType = AT_SPAWN;
        }
            break;
            
        default:
            break;
    }
}

bool BWActionLayer::init()
{
	if ( !CCLayer::init() ) 
	{
		return false;
	}
	return true;
}

void BWActionLayer::setActionData(ActionData* pActionDataStr)
{
    if(!pActionDataStr) return;
    m_pActionData = pActionDataStr;
    
    m_actionType = AT_SEQ;
    m_actionType = m_pActionData->actType;
   
    switch (m_actionType)
    {
        case AT_SEQ:
        {
            m_actionTypeTogItem->setSelectedIndex(0);
            m_actionType = AT_SEQ;
        }
            break;
        case AT_SPAWN:
        {
            m_actionTypeTogItem->setSelectedIndex(1);
            m_actionType = AT_SPAWN;
        }
            break;
        case AT_UNKNOWN:
        {
            m_actionTypeTogItem->setSelectedIndex(0);
            m_actionType = AT_SEQ;
        }
        default:
            break;
    }
    m_repeatCountField->setText("1");
    
    m_moveDurationField->setText("0");
    m_moveOrderField->setText("0");
    m_moveEndPointXField->setText("0");
    m_moveEndPointYField->setText("0");
    m_moveRepeatCountField->setText("1");

    
    m_bezierDurationField->setText("0");
    m_bezierOrderField->setText("0");
    m_bezierOnePointXField->setText("0");
    m_bezierOnePointYField->setText("0");
    m_bezierTwoPointXField->setText("0");
    m_bezierTwoPointYField->setText("0");
    m_bezierEndPointXField->setText("0");
    m_bezierEndPointYField->setText("0");
    m_bezierRepeatCountField->setText("1");

    
    m_jumpDurationField->setText("0");
    m_jumpOrderField->setText("0");
    m_jumpHeightField->setText("0");
    m_jumpCountField->setText("0");
    m_jumpEndPointXField->setText("0");
    m_jumpEndPointYField->setText("0");
    m_jumpRepeatCountField->setText("1");

    
    m_rotateDurationField->setText("0");
    m_rotateOrderField->setText("0");
    m_rotateAngleField->setText("0");
    m_rotateRepeatCountField->setText("1");


    m_scaleDurationField->setText("0");
    m_scaleOrderField->setText("0");
    m_scaleXField->setText("0");
    m_scaleYField->setText("0");
    m_scaleRepeatCountField->setText("1");

    
    m_tintDurationField->setText("0");
    m_tintOrderField->setText("0");
    m_tintRedField->setText("0");
    m_tintGreenField->setText("0");
    m_tintBlueField->setText("0");
    m_tintRepeatCountField->setText("1");

    
    m_fadeInDurationField->setText("0");
    m_fadeInOrderField->setText("0");
    m_fadeInRepeatCountField->setText("1");

    
    m_fadeOutDurationField->setText("0");
    m_fadeOutOrderField->setText("0");
    m_fadeOutRepeatCountField->setText("1");

    
    m_blinkDurationField->setText("0");
    m_blinkOrderField->setText("0");
    m_blinkCountField->setText("0");
    m_blinkRepeatCountField->setText("1");

    
    m_skewDurationField->setText("0");
    m_skewOrderField->setText("0");
    m_skewXField->setText("0");
    m_skewYField->setText("0");
    m_skewRepeatCountField->setText("1");
    
    
    m_delayTimeOrderField->setText("0");
    m_delayTimeDurationField->setText("0");
    
    
    //sine
    m_sineDurationField->setText("0");
    m_sineOrderField->setText("0");
    m_sineEndPointXField->setText("0");
    m_sineEndPointYField->setText("0");
    m_sineAField->setText("0");
    m_sineRepeatCountField->setText("0");
    
    
    char tempMsg[COMMON_STRING_SIZE]={0,0};
    
    //repeat
    MenuItemToggle* tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_REPEAT);
    int reverse = m_pActionData->reverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    int count = m_pActionData->repeatCount;
    sprintf(tempMsg,"%d",count);
    m_repeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_REPEAT+REPEAT_COUNT_TAG);
    reverse = m_pActionData->repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->delayData.duration);
    m_delayTimeDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->delayData.order);
    m_delayTimeOrderField->setText(tempMsg);
    
    
    //move
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->movData.duration);
    m_moveDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->movData.order);
    m_moveOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->movData.repeatCount);
    m_moveRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_MOVE);
    reverse = m_pActionData->movData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_MOVE+REPEAT_COUNT_TAG);
    reverse = m_pActionData->movData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->movData.endPoint.x);
    m_moveEndPointXField->setText(tempMsg);

    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->movData.endPoint.y);
    m_moveEndPointYField->setText(tempMsg);
    
    //bezier
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bezData.duration);
    m_bezierDurationField->setText(tempMsg);

    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->bezData.order);
    m_bezierOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->bezData.repeatCount);
    m_bezierRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BEZIER);
    reverse = m_pActionData->bezData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BEZIER+REPEAT_COUNT_TAG);
    reverse = m_pActionData->bezData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bezData.onePoint.x);
    m_bezierOnePointXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bezData.onePoint.y);
    m_bezierOnePointYField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bezData.twoPoint.x);
    m_bezierTwoPointXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bezData.twoPoint.y);
    m_bezierTwoPointYField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bezData.endPoint.x);
    m_bezierEndPointXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bezData.endPoint.y);
    m_bezierEndPointYField->setText(tempMsg);
    
    //jump
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->jumData.duration);
    m_jumpDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->jumData.order);
    m_jumpOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->jumData.repeatCount);
    m_jumpRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_JUMP);
    reverse = m_pActionData->jumData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_JUMP+REPEAT_COUNT_TAG);
    reverse = m_pActionData->jumData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->jumData.height);
    m_jumpHeightField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->jumData.jumCount);
    m_jumpCountField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->jumData.endPoint.x);
    m_jumpEndPointXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->jumData.endPoint.y);
    m_jumpEndPointYField->setText(tempMsg);
    
    //scale
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->scaData.duration);
    m_scaleDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->scaData.order);
    m_scaleOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->scaData.repeatCount);
    m_scaleRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SCALE);
    reverse = m_pActionData->scaData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SCALE+REPEAT_COUNT_TAG);
    reverse = m_pActionData->scaData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->scaData.sx);
    m_scaleXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->scaData.sy);
    m_scaleYField->setText(tempMsg);
    
    //rotate
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->rotData.duration);
    m_rotateDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->rotData.order);
    m_rotateOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->rotData.repeatCount);
    m_rotateRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_ROTATE);
    reverse = m_pActionData->rotData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_ROTATE+REPEAT_COUNT_TAG);
    reverse = m_pActionData->rotData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->rotData.angle);
    m_rotateAngleField->setText(tempMsg);
    
    //tint
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->tinData.duration);
    m_tintDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->tinData.order);
    m_tintOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->tinData.repeatCount);
    m_tintRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_TINT);
    reverse = m_pActionData->tinData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_TINT+REPEAT_COUNT_TAG);
    reverse = m_pActionData->tinData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->tinData.deltaRed);
    m_tintRedField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->tinData.deltaGreen);
    m_tintGreenField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->tinData.deltaBlue);
    m_tintBlueField->setText(tempMsg);

    //fadeIn
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->fadInData.duration);
    m_fadeInDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->fadInData.order);
    m_fadeInOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->fadInData.repeatCount);
    m_fadeInRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEIN);
    reverse = m_pActionData->fadInData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEIN+REPEAT_COUNT_TAG);
    reverse = m_pActionData->fadInData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    //fadeOut
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->fadOutData.duration);
    m_fadeOutDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->fadOutData.order);
    m_fadeOutOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->fadOutData.repeatCount);
    m_fadeOutRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEOUT);
    reverse = m_pActionData->fadOutData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEOUT+REPEAT_COUNT_TAG);
    reverse = m_pActionData->fadOutData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    //blink
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->bliData.duration);
    m_blinkDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->bliData.order);
    m_blinkOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->bliData.repeatCount);
    m_blinkRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BLINK);
    reverse = m_pActionData->bliData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BLINK+REPEAT_COUNT_TAG);
    reverse = m_pActionData->bliData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->bliData.count);
    m_blinkCountField->setText(tempMsg);
    
    //skew
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->skeData.duration);
    m_skewDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->skeData.order);
    m_skewOrderField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->skeData.repeatCount);
    m_skewRepeatCountField->setText(tempMsg);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SKEW);
    reverse = m_pActionData->skeData.reverseFlag;
    tog->setSelectedIndex(reverse);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SKEW+REPEAT_COUNT_TAG);
    reverse = m_pActionData->skeData.repeatReverseFlag;
    tog->setSelectedIndex(reverse);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->skeData.deltaSkewX);
    m_skewXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->skeData.deltaSkewY);
    m_skewYField->setText(tempMsg);
    
    //sine
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%.2f",m_pActionData->sineActionData.fDur);
    m_sineDurationField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%f",m_pActionData->sineActionData.endPos.x);
    m_sineEndPointXField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%f",m_pActionData->sineActionData.endPos.y);
    m_sineEndPointYField->setText(tempMsg);
    
    memset(tempMsg,0,COMMON_STRING_SIZE);
    sprintf(tempMsg,"%d",m_pActionData->sineActionData.nA);
    m_sineAField->setText(tempMsg);
    
}

void BWActionLayer::getActionData(ActionData* pActionDataStr)
{
    if(!m_pActionData)
        return;
    
    m_pActionData->actType = m_actionType;
    
    const char* repeatCountText = m_repeatCountField->getText();
    m_pActionData->repeatCount = atoi(repeatCountText);
    
    MenuItemToggle* tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_REPEAT);
    int reverse = tog->getSelectedIndex();
    m_pActionData->reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_REPEAT +REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->repeatReverseFlag = reverse;
    

    const char* delayDurationText = m_delayTimeDurationField->getText();
    m_pActionData->delayData.duration = atof(delayDurationText);
    
    const char* delayOrderText = m_delayTimeOrderField->getText();
    m_pActionData->delayData.order = atoi(delayOrderText);
    
    m_pActionData->delayData.actType = AT_DELAY;
    
    //move
    const char* moveDurationText = m_moveDurationField->getText();
    m_pActionData->movData.duration = atof(moveDurationText);
    
    m_pActionData->movData.actType = AT_MOVE;
    
    const char* moveOrderText = m_moveOrderField->getText();
    m_pActionData->movData.order = atoi(moveOrderText);
    
    const char* moveRepeatCountText = m_moveRepeatCountField->getText();
    m_pActionData->movData.repeatCount = atoi(moveRepeatCountText);
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_MOVE);
    reverse = tog->getSelectedIndex();
    m_pActionData->movData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_MOVE+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->movData.repeatReverseFlag = reverse;
    
    const char* moveEndPointXText = m_moveEndPointXField->getText();
    m_pActionData->movData.endPoint.x = atof(moveEndPointXText);
    
    const char* moveEndPointYText = m_moveEndPointYField->getText();
    m_pActionData->movData.endPoint.y = atof(moveEndPointYText);
    
    //bezier
    m_pActionData->bezData.actType = AT_BEZIER;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BEZIER);
    reverse = tog->getSelectedIndex();
    m_pActionData->bezData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BEZIER+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->bezData.repeatReverseFlag = reverse;
    
    const char* bezierDurationText = m_bezierDurationField->getText();
    m_pActionData->bezData.duration = atof(bezierDurationText);
    
    const char* bezierOrderText = m_bezierOrderField->getText();
    m_pActionData->bezData.order = atoi(bezierOrderText);
    
    const char* bezierRepeatCountText = m_bezierRepeatCountField->getText();
    m_pActionData->bezData.repeatCount = atoi(bezierRepeatCountText);
    
    const char* bezierOnePointXText = m_bezierOnePointXField->getText();
    m_pActionData->bezData.onePoint.x = atof(bezierOnePointXText);
    
    const char* bezierOnePointYText = m_bezierOnePointYField->getText();
    m_pActionData->bezData.onePoint.y = atof(bezierOnePointYText);
    
    const char* bezierTwoPointXText = m_bezierTwoPointXField->getText();
    m_pActionData->bezData.twoPoint.x = atof(bezierTwoPointXText);
    
    const char* bezierTwoPointYText = m_bezierTwoPointYField->getText();
    m_pActionData->bezData.twoPoint.y = atof(bezierTwoPointYText);
    
    const char* bezierEndPointXText = m_bezierEndPointXField->getText();
    m_pActionData->bezData.endPoint.x = atof(bezierEndPointXText);
    
    const char* bezierEndPointYText = m_bezierEndPointYField->getText();
    m_pActionData->bezData.endPoint.y = atof(bezierEndPointYText);
    
    //jump
    m_pActionData->jumData.actType = AT_JUMP;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_JUMP);
    reverse = tog->getSelectedIndex();
    m_pActionData->jumData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_JUMP+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->jumData.repeatReverseFlag = reverse;
    
    const char* jumpDurationText = m_jumpDurationField->getText();
    m_pActionData->jumData.duration = atof(jumpDurationText);
    
    const char* jumpOrderText = m_jumpOrderField->getText();
    m_pActionData->jumData.order = atoi(jumpOrderText);
    
    const char* jumpRepeatCountText = m_jumpRepeatCountField->getText();
    m_pActionData->jumData.repeatCount = atoi(jumpRepeatCountText);
    
    const char* jumpHeightText = m_jumpHeightField->getText();
    m_pActionData->jumData.height = atof(jumpHeightText);
    
    const char* jumpCountText = m_jumpCountField->getText();
    m_pActionData->jumData.jumCount = atoi(jumpCountText);
    
    const char* jumpEndPointXText = m_jumpEndPointXField->getText();
    m_pActionData->jumData.endPoint.x = atof(jumpEndPointXText);
    
    const char* jumpEndPointYText = m_jumpEndPointYField->getText();
    m_pActionData->jumData.endPoint.y = atof(jumpEndPointYText);
    
    //scale
    m_pActionData->scaData.actType = AT_SCALE;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SCALE);
    reverse = tog->getSelectedIndex();
    m_pActionData->scaData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SCALE+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->scaData.repeatReverseFlag = reverse;
    
    const char* scaleDurationText = m_scaleDurationField->getText();
    m_pActionData->scaData.duration = atof(scaleDurationText);
    
    const char* scaleOrderText = m_scaleOrderField->getText();
    m_pActionData->scaData.order = atoi(scaleOrderText);
    
    const char* scaleRepeatCountText = m_scaleRepeatCountField->getText();
    m_pActionData->scaData.repeatCount = atoi(scaleRepeatCountText);
    
    const char* scaleXText = m_scaleXField->getText();
    m_pActionData->scaData.sx = atof(scaleXText);
    
    const char* scaleYText = m_scaleYField->getText();
    m_pActionData->scaData.sy = atof(scaleYText);
    
    //rotate
    m_pActionData->rotData.actType = AT_ROTATE;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_ROTATE);
    reverse = tog->getSelectedIndex();
    m_pActionData->rotData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_ROTATE+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->rotData.repeatReverseFlag = reverse;
    
    const char* rotateDurationText = m_rotateDurationField->getText();
    m_pActionData->rotData.duration = atof(rotateDurationText);
    
    const char* rotateOrderText = m_rotateOrderField->getText();
    m_pActionData->rotData.order = atoi(rotateOrderText);
    
    const char* rotateRepeatCountText = m_rotateRepeatCountField->getText();
    m_pActionData->rotData.repeatCount = atoi(rotateRepeatCountText);
    
    const char* rotateAngleText = m_rotateAngleField->getText();
    m_pActionData->rotData.angle = atof(rotateAngleText);
    
    //tint
    m_pActionData->tinData.actType = AT_TINT;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_TINT);
    reverse = tog->getSelectedIndex();
    m_pActionData->tinData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_TINT+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->tinData.repeatReverseFlag = reverse;
    
    const char* tintDurationText = m_tintDurationField->getText();
    m_pActionData->tinData.duration = atof(tintDurationText);
    
    const char* tintOrderText = m_tintOrderField->getText();
    m_pActionData->tinData.order = atoi(tintOrderText);
    
    const char* tintRepeatCountText = m_tintRepeatCountField->getText();
    m_pActionData->tinData.repeatCount = atoi(tintRepeatCountText);
    
    const char* tintRedText = m_tintRedField->getText();
    m_pActionData->tinData.deltaRed = atof(tintRedText);
    
    const char* tintGreenText = m_tintGreenField->getText();
    m_pActionData->tinData.deltaGreen = atof(tintGreenText);
    
    const char* tintBlueText = m_tintBlueField->getText();
    m_pActionData->tinData.deltaBlue = atof(tintBlueText);

    //fadeIn
     m_pActionData->fadInData.actType = AT_FADEIN;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEIN);
    reverse = tog->getSelectedIndex();
    m_pActionData->fadInData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEIN+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->fadInData.repeatReverseFlag = reverse;
    
    const char* fadeInDurationText = m_fadeInDurationField->getText();
    m_pActionData->fadInData.duration = atof(fadeInDurationText);
    
    const char* fadeInOrderText = m_fadeInOrderField->getText();
    m_pActionData->fadInData.order = atoi(fadeInOrderText);
    
    const char* fadeInRepeatCountText = m_fadeInRepeatCountField->getText();
    m_pActionData->fadInData.repeatCount = atoi(fadeInRepeatCountText);
    
    //fadeOut
    m_pActionData->fadOutData.actType = AT_FADEOUT;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEOUT);
    reverse = tog->getSelectedIndex();
    m_pActionData->fadOutData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_FADEOUT+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->fadOutData.repeatReverseFlag = reverse;
    
    const char* fadeOutDurationText = m_fadeOutDurationField->getText();
    m_pActionData->fadOutData.duration = atof(fadeOutDurationText);
    
    const char* fadeOutOrderText = m_fadeOutOrderField->getText();
    m_pActionData->fadOutData.order = atoi(fadeOutOrderText);
    
    const char* fadeOutRepeatCountText = m_fadeOutRepeatCountField->getText();
    m_pActionData->fadOutData.repeatCount = atoi(fadeOutRepeatCountText);
    
    //blink
    m_pActionData->bliData.actType = AT_BLINK;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BLINK);
    reverse = tog->getSelectedIndex();
    m_pActionData->bliData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_BLINK+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->bliData.repeatReverseFlag = reverse;
    
    const char* blinkDurationText = m_blinkDurationField->getText();
    m_pActionData->bliData.duration = atof(blinkDurationText);
    
    const char* blinkOrderText = m_blinkOrderField->getText();
    m_pActionData->bliData.order = atoi(blinkOrderText);
    
    const char* blinkRepeatCountText = m_blinkRepeatCountField->getText();
    m_pActionData->bliData.repeatCount = atoi(blinkRepeatCountText);
    
    const char* blinkCountText = m_blinkCountField->getText();
    m_pActionData->bliData.count = atoi(blinkCountText);
    //skew
    
    m_pActionData->skeData.actType = AT_SKEW;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SKEW);
    reverse = tog->getSelectedIndex();
    m_pActionData->skeData.reverseFlag = reverse;
    
    tog = (MenuItemToggle*)m_scrolMenu->getChildByTag(AT_SKEW+REPEAT_COUNT_TAG);
    reverse = tog->getSelectedIndex();
    m_pActionData->skeData.repeatReverseFlag = reverse;
    
    const char* skewDurationtext = m_skewDurationField->getText();
    m_pActionData->skeData.duration = atof(skewDurationtext);
    
    const char* skewOrderText = m_skewOrderField->getText();
    m_pActionData->skeData.order = atoi(skewOrderText);
    
    const char* skewRepeatCountText = m_skewRepeatCountField->getText();
    m_pActionData->skeData.repeatCount = atoi(skewRepeatCountText);
    
    const char* skewXText = m_skewXField->getText();
    m_pActionData->skeData.deltaSkewX = atof(skewXText);
    
    const char* skewYText = m_skewYField->getText();
    m_pActionData->skeData.deltaSkewY = atof(skewYText);
    
    
    //sine
    const char* pszText = m_sineDurationField->getText();
    m_pActionData->sineActionData.fDur = atof(pszText);
    
    pszText = m_sineEndPointXField->getText();
    m_pActionData->sineActionData.endPos.x = atof(pszText);

    pszText = m_sineEndPointYField->getText();
    m_pActionData->sineActionData.endPos.y = atof(pszText);

    pszText = m_sineAField->getText();
    m_pActionData->sineActionData.nA = atoi(pszText);
}

void BWActionLayer::setEnable(bool ableFlag)
{
//    setTouchEnabled(ableFlag);
//    m_scrollLayer->setTouchEnabled(ableFlag);
//    m_scrolMenu->setTouchEnabled(ableFlag);
//    m_menu->setTouchEnabled(ableFlag);
    
//    m_repeatCountField->setTouchEnabled(ableFlag);
//    m_bezierDurationField->setTouchEnabled(ableFlag);
//    m_bezierOnePointXField->setTouchEnabled(ableFlag);
//    m_bezierOnePointYField->setTouchEnabled(ableFlag);
//    m_bezierTwoPointXField->setTouchEnabled(ableFlag);
//    m_bezierTwoPointYField->setTouchEnabled(ableFlag);
//    m_bezierEndPointXField->setTouchEnabled(ableFlag);
//    m_bezierEndPointYField->setTouchEnabled(ableFlag);
//    m_jumpDurationField->setTouchEnabled(ableFlag);
//    m_jumpHeightField->setTouchEnabled(ableFlag);
//    m_jumpCountField->setTouchEnabled(ableFlag);
//    m_jumpEndPointXField->setTouchEnabled(ableFlag);
//    m_jumpEndPointYField->setTouchEnabled(ableFlag);
//    m_scaleDurationField->setTouchEnabled(ableFlag);
//    m_rotateAngleField->setTouchEnabled(ableFlag);
//    m_bezierOrderField->setTouchEnabled(ableFlag);
//    m_jumpOrderField->setTouchEnabled(ableFlag);
//    m_rotateOrderField->setTouchEnabled(ableFlag);
//    m_moveDurationField->setTouchEnabled(ableFlag);
//    m_moveEndPointXField->setTouchEnabled(ableFlag);
//    m_moveEndPointYField->setTouchEnabled(ableFlag);
//    m_moveOrderField->setTouchEnabled(ableFlag);
//    m_bezierRepeatCountField->setTouchEnabled(ableFlag);
//    m_jumpRepeatCountField->setTouchEnabled(ableFlag);
//    m_rotateRepeatCountField->setTouchEnabled(ableFlag);
//    m_moveRepeatCountField->setTouchEnabled(ableFlag);
//
//
//    m_scaleXField->setTouchEnabled(ableFlag);
//    m_scaleYField->setTouchEnabled(ableFlag);
//    m_rotateDurationField->setTouchEnabled(ableFlag);
//    m_fadeInDurationField->setTouchEnabled(ableFlag);
//    m_fadeOutDurationField->setTouchEnabled(ableFlag);
//    
//    m_tintDurationField->setTouchEnabled(ableFlag);
//    m_tintRedField->setTouchEnabled(ableFlag);
//    m_tintGreenField->setTouchEnabled(ableFlag);
//    m_tintBlueField->setTouchEnabled(ableFlag);
//
//    m_blinkDurationField->setTouchEnabled(ableFlag);
//    m_blinkCountField->setTouchEnabled(ableFlag);
//    m_skewDurationField->setTouchEnabled(ableFlag);
//    m_skewXField->setTouchEnabled(ableFlag);
//    m_skewYField->setTouchEnabled(ableFlag);
//    m_scaleOrderField->setTouchEnabled(ableFlag);
//    m_tintOrderField->setTouchEnabled(ableFlag);;
//    m_fadeInOrderField->setTouchEnabled(ableFlag);
//    m_fadeOutOrderField->setTouchEnabled(ableFlag);
//    m_blinkOrderField->setTouchEnabled(ableFlag);
//    m_skewOrderField->setTouchEnabled(ableFlag);
//    m_scaleRepeatCountField->setTouchEnabled(ableFlag);
//    m_tintRepeatCountField->setTouchEnabled(ableFlag);
//    m_fadeInRepeatCountField->setTouchEnabled(ableFlag);
//    m_fadeOutRepeatCountField->setTouchEnabled(ableFlag);
//    m_blinkRepeatCountField->setTouchEnabled(ableFlag);
//    m_skewRepeatCountField->setTouchEnabled(ableFlag);
//    m_delayTimeDurationField->setTouchEnabled(ableFlag);
//    m_delayTimeOrderField->setTouchEnabled(ableFlag);
    
}

bool greaterMarkAction(const ActionIntervalData action1, const ActionIntervalData action2)
{
	return action1.order < action2.order;
}

void BWActionLayer::sortAction(ActionData* pActionDataStr)
{
    ActionData* actData = pActionDataStr;
    actData->actionArray.clear();
    
    if(actData->movData.order != 0)
    {
        actData->actionArray.push_back(actData->movData);
    }
    if(actData->bezData.order != 0)
    {
        actData->actionArray.push_back(actData->bezData);
    }
    if(actData->jumData.order != 0)
    {
        actData->actionArray.push_back(actData->jumData);
    }
    if(actData->scaData.order != 0)
    {
        actData->actionArray.push_back(actData->scaData);
    }
    if(actData->rotData.order != 0)
    {
        actData->actionArray.push_back(actData->rotData);
    }
    if(actData->tinData.order != 0)
    {
        actData->actionArray.push_back(actData->tinData);
    }
    if(actData->fadInData.order != 0)
    {
        actData->actionArray.push_back(actData->fadInData);
    }
    if(actData->fadOutData.order != 0)
    {
        actData->actionArray.push_back(actData->fadOutData);
    }
    if(actData->bliData.order != 0)
    {
        actData->actionArray.push_back(actData->bliData);
    }
    if(actData->skeData.order != 0)
    {
        actData->actionArray.push_back(actData->skeData);
    }
    if(actData->delayData.order !=0)
    {
        actData->actionArray.push_back(actData->delayData);
    }
    if(actData->sineActionData.order !=0)
    {
        actData->actionArray.push_back(actData->sineActionData);
    }
    
    std::sort(actData->actionArray.begin(),actData->actionArray.end(), greaterMarkAction);
}





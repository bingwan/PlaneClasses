

#include "BWBornLayer.h"
#include "CCScrollLayer.h"
#include "BWTextEdit.h"
#include "BWEditLayer.h"
#include "BWDetailNPCLayer.h"
#include "BWMenu.h"
#include "BWEditBulletLayer.h"


BWBornLayer::BWBornLayer():
m_menu(NULL),
m_idTextFieldArray(NULL),
m_rateTextFieldArray(NULL),
m_npcItemDataStr(NULL)
{
    m_idTextFieldArray = CCArray::create();
    CC_SAFE_RETAIN(m_idTextFieldArray);
    
    m_rateTextFieldArray = CCArray::create();
    CC_SAFE_RETAIN(m_rateTextFieldArray);
}

BWBornLayer::~BWBornLayer()
{
    m_idTextFieldArray->removeAllObjects();
    m_rateTextFieldArray->removeAllObjects();
    
    CC_SAFE_RELEASE(m_idTextFieldArray);
    CC_SAFE_RELEASE(m_rateTextFieldArray);
}

bool BWBornLayer::initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
    
    LayerColor::initWithColor(color, width, height);
    setTouchEnabled(true);
    addTextField(color,13);
    
    m_menu = CCMenu::create();
    m_menu->setAnchorPoint(ccp(0,0));
    m_menu->setPosition(ccp(0,0));
    addChild(m_menu);
    
    CCLabelTTF* backLabel = CCLabelTTF::create("返回", "", 30);
    CCMenuItemLabel* backItem = CCMenuItemLabel::create(backLabel, this, menu_selector(BWBornLayer::back));
    backItem->setPosition(ccp(width-50,80));
    m_menu->addChild(backItem, 0);
    
    
    return true;
}

void BWBornLayer::setdetailLayer(BWDetailNPCLayer* layer)
{
    m_detailLayer = layer;
}
void BWBornLayer::back(Object* pObject)
{
    getBornData();
    
    if(m_detailLayer != NULL)
    {
        m_detailLayer->setEnable(true);
    }
    
    removeFromParentAndCleanup(true);
}

void BWBornLayer::addTextField(ccColor4B color, int count)
{
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_scrollLayer = CCScrollLayer::scrollLayerWidthColor(color, getContentSize());
    m_scrollLayer->setAnchorPoint(ccp(0,0));
    m_scrollLayer->setPosition(ccp(0,0));
    addChild(m_scrollLayer);

    int allCount = count;
    
    int spaceX = 10;
    int spaceY = 30;
    float width = 110;
    float height = 30;
    
    int fontSize = 20;

    m_idTextFieldArray->removeAllObjects();
    m_rateTextFieldArray->removeAllObjects();
    
    for(int i=0; i<allCount; ++i)
    {
        char indexString[256] = {0};
        sprintf(indexString,"%s%d","生成物品ID",allCount-i);
        CCLabelTTF* idLabel = CCLabelTTF::create(indexString, "", fontSize);
        CCPoint position = ccp(spaceX + width/2+(spaceX + width)*0, spaceY + (spaceY+height)*i);
        idLabel->setPosition(position);
        idLabel->setColor(ccRED);
        m_scrollLayer->addSubChild(idLabel);
//        
//        BWTextFieldTTFDefault* idTextField = new BWTextFieldTTFDefault();
//        idTextField->autorelease();
//        idTextField->setString("0");
//        position = ccp(spaceX+ width/2+(spaceX + width)*1, spaceY + (spaceY+height)*i);
//        idTextField->setPosition(position);
//        m_scrollLayer->addSubChild(idTextField);
        
        
      //  const char* rate = gBWLocalizationManagerPtr->getString("key_edit_rate");
        
        CCLabelTTF* rateLabel = CCLabelTTF::create("rate", "", fontSize);
        position = ccp(spaceX + width/2+(spaceX + width)*2, spaceY + (spaceY+height)*i);
        rateLabel->setPosition(position);
        rateLabel->setColor(ccRED);
        m_scrollLayer->addSubChild(rateLabel);
        
//        BWTextFieldTTFDefault* rateTextField = new BWTextFieldTTFDefault();
//        rateTextField->autorelease();
//        rateTextField->setString("0");
//        position = ccp(spaceX+ width/2+(spaceX + width)*3, spaceY + (spaceY+height)*i);
//        rateTextField->setPosition(position);
//        m_scrollLayer->addSubChild(rateTextField);
        
        //m_idTextFieldArray->addObject(idTextField);
        //m_rateTextFieldArray->addObject(rateTextField);
        
    }
    m_scrollLayer->setScrollContentSize(CCSizeMake(winSize.width, spaceY + (spaceY+height)*allCount));
    
}


bool BWBornLayer::init()
{
	if ( !CCLayer::init() ) 
	{
		return false;
	}
	return true;
}

void BWBornLayer::setBornData(NpcData* pDataStr)
{
    if(!pDataStr) return;
    m_npcItemDataStr = pDataStr;
    
//    int fieldCount = m_idTextFieldArray->count()-1;
//    int count = m_npcItemDataStr->bornRateArray.size();
//    for(int i=0; i<count; ++i)
//    {
//        int  id = m_npcItemDataStr->bornRateArray[i].ID;
//        int  rate = m_npcItemDataStr->bornRateArray[i].appearRate;
//        char idString[256] = {0};
//        char rateString[256] = {0};
//        sprintf(idString,"%d",id);
//        sprintf(rateString,"%d",rate);
//        
//        BWTextFieldTTFDefault* idTextRield = (BWTextFieldTTFDefault*)m_idTextFieldArray->objectAtIndex(fieldCount-i);
//        BWTextFieldTTFDefault* rateTextRield = (BWTextFieldTTFDefault*)m_rateTextFieldArray->objectAtIndex(fieldCount-i);
//        
//        idTextRield->setString(idString);
//        rateTextRield->setString(rateString);
//    }
}

void BWBornLayer::getBornData()
{
    
//    if(!m_npcItemDataStr) return;
//    int count = m_idTextFieldArray->count();
//    
//    
//    int size = 0;
//    for(int i=count-1; i>=0; --i)
//    {
//        BWTextFieldTTFDefault* idTextRield = (BWTextFieldTTFDefault*)m_idTextFieldArray->objectAtIndex(i);
//        const char* idString = idTextRield->getString();
//        int id = atoi(idString);
//        if(id != 0)
//        {
//            size++;
//        }
//        else
//        {
//            break;
//        }
//    }
//    m_npcItemDataStr->bornRateArray.resize(size);
//    
//    for(int i=count-1; i>=0; --i)
//    {
//        BWTextFieldTTFDefault* idTextRield = (BWTextFieldTTFDefault*)m_idTextFieldArray->objectAtIndex(i);
//        BWTextFieldTTFDefault* rateTextRield = (BWTextFieldTTFDefault*)m_rateTextFieldArray->objectAtIndex(i);
//        
//        const char* idString = idTextRield->getString();
//        const char* rateString = rateTextRield->getString();
//        
//        int id = atoi(idString);
//        int rate = atoi(rateString);
//        if(id != 0)
//        {
//            npcItemIndexStr bornData;
//            bornData.ID = id;
//            bornData.appearRate = rate;
//            int index = count-i-1;
//            m_npcItemDataStr->bornRateArray[index]= bornData;
//        }
//        else
//        {
//            break;
//        }
//    }
}

void BWBornLayer::setEnable(bool ableFlag)
{
    setTouchEnabled(ableFlag);
    m_scrollLayer->setTouchEnabled(ableFlag);
    m_menu->setTouchEnabled(ableFlag);
}




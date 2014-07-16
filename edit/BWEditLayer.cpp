

#include "BWEditLayer.h"
#include "BWDetailNPCLayer.h"
#include "BWTextEdit.h"
#include "BWMenu.h"
#include "CCScrollLayer.h"
#include "CommonDef.h"
#include "CCLabelStroke.h"
#include "BWCCMenuItemImage.h"
#include "ResManager.h"
#include "CCScrollLayer.h"
#include "CCButton.h"
#include "CCAPI.h"
#include "BWActionInterval.h"
#include "BWUnitManager.h"

int EditNpcData::npcIdGen = 1;

#define EDIT_CIRCLE_PNG "Icon-72.png"

BWEditLayer::BWEditLayer():
m_LevelIdEdit(NULL),
m_LevelNameEdit(NULL),
m_TileNumLabel(NULL),
m_isTouchLayerFlag(false),
m_LevelType(LTE_COMMON),
m_LevelEnterNumPerDay(0),
m_LevelDistance(0),
m_TileTemplateId(INVALID_ID),
m_pMoveLayer(NULL),
m_NpcPropertyLayer(NULL),
m_SelectNpcId(INVALID_ID),
m_bgSpriteArray(NULL),
m_npcListMenu(NULL),
m_itemListMenu(NULL),
m_touchCircleFlag(false),
m_bottomLayer(NULL),
m_editMenu(NULL),
m_bottomMenu(NULL),
m_lockTogItem(NULL),
m_bglistLayer(NULL),
m_userLevelIdEdit(NULL),
m_levelBgId(0),
m_flagSprite(NULL),
m_screenCountField(NULL),
m_guidField(NULL),
m_difficultyField(NULL),
m_timeLimitField(NULL),
m_fogField(NULL),
m_fogStarTimeField(NULL),
m_fogEndTimeField(NULL),
m_agentFieldArray(NULL),
m_screenCount(0),
m_agentCountField(NULL),
m_fogKepTimeField(NULL),
m_scale(0.25),
m_oldSelSpriteId(-1),
m_rainField(NULL),
m_snowField(NULL)
{
    m_agentFieldArray = Array::create();
    m_agentFieldArray->retain();
    
    _nLevelScreenCount = 0;
}
BWEditLayer::~BWEditLayer()
{
    clearNpcInfo();
    clearAllData();
    
	m_bgSpriteArray->removeAllObjects();
    CC_SAFE_RELEASE_NULL(m_bgSpriteArray);
    
    m_agentFieldArray->removeAllObjects();
    m_agentFieldArray->release();
}

void BWEditLayer::onEnter()
{
    Layer::onEnter();
    initUI();
    
}

void BWEditLayer::onExit()
{
    Layer::onExit();
}


void  BWEditLayer::initUI()
{
	setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	m_bgSpriteArray = Array::create();
	CC_SAFE_RETAIN(m_bgSpriteArray);

    Size contentSize = getContentSize();
    
	//动态layer
	m_pMoveLayer = LayerColor::create(Color4B(200,0,0,200), UI_RES_WIDTH, UI_RES_HEIGHT);
	m_pMoveLayer->setAnchorPoint(Point(0.5,0));
	m_pMoveLayer->setPosition(Point(contentSize.width*0.5,0));
     m_startPos = m_pMoveLayer->getPosition();
	addChild(m_pMoveLayer,MOVE_LAYER_Z);

	//npc列表x
	drawNpcList();
	//drawItemList();
    
    //npc编辑layer
	m_circleSprite = Sprite::create("rank_bg.png");
	m_circleSprite->setPosition(Point(contentSize.width/2 -100,contentSize.height/2 - 50));
	addChild(m_circleSprite,MOVE_CIRCLE_Z);
    m_circleSprite->setVisible(false);

    
    CCScrollLayer* pNpcEditScrolLayer = CCScrollLayer::scrollLayerWidthColor(Color4B(0,200,0,200), Size(contentSize.width,100));
    pNpcEditScrolLayer->setPosition(Point(0,0));
    pNpcEditScrolLayer->setAnchorPoint(Point(0,0));
    Size showMwnuLayerSize = pNpcEditScrolLayer->getContentSize();
    pNpcEditScrolLayer->setPosition(Point(0,0));
    addChild(pNpcEditScrolLayer,BOTTOM_LAYER_Z);
    
    pNpcEditScrolLayer->setScrollContentSize(Size(contentSize.width*2,pNpcEditScrolLayer->getContentSize().height));
    
    m_editMenu = BWMenu::create();
    m_editMenu->setPreventTouchFlag(false);
	m_editMenu->setAnchorPoint(Point(0,0));
	m_editMenu->setPosition(Point(0,0));
	pNpcEditScrolLayer->addSubChild(m_editMenu);
    
    int nFontSize = 30;
    
    float fSpaceY = 20;
    float fSpaceX = 10;
    
    float fWidth = 100;
    float fHeight = 100;
    
    float fOriginX = 20;
    float fOriginY = 20;
    
    int nIndexX = 0;
    int nIndexY = 0;
    
    
	//复制按钮
    Point pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
	LabelTTF* label = LabelTTF::create("copy", "", nFontSize);
	label->setColor(Color3B::RED);
	MenuItemLabel* labelItem = MenuItemLabel::create(label,CC_CALLBACK_1(BWEditLayer::clickEditMenu,this));
    labelItem->setPosition(pos);
    labelItem->setTag(EIE_COPY);
    m_editMenu->addChild(labelItem,MENU_UNUSED_Z); 
	
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* createtring = "play";
    label = CCLabelTTF::create(createtring, "", nFontSize);
	label->setColor(Color3B::RED);
    labelItem = CCMenuItemLabel::create(label, CC_CALLBACK_1(BWEditLayer::clickEditMenu,this));
	labelItem->setPosition(pos);
    labelItem->setTag(EIE_ACTION);
	m_editMenu->addChild(labelItem,MENU_UNUSED_Z);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* stopString = "stop";
    label = CCLabelTTF::create(stopString, "", nFontSize);
	label->setColor(Color3B::RED);
	labelItem = CCMenuItemLabel::create(label,CC_CALLBACK_1(BWEditLayer::clickEditMenu,this));
	labelItem->setPosition(pos);
    labelItem->setTag(EIE_STOP);
	m_editMenu->addChild(labelItem,MENU_UNUSED_Z);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* deleteString = "delete";
    label = CCLabelTTF::create(deleteString, "", nFontSize);
	label->setColor(Color3B::RED);
	MenuItemLabel* deleteItem = CCMenuItemLabel::create(label, CC_CALLBACK_1(BWEditLayer::clickEditMenu,this));
	deleteItem->setPosition(pos);
    deleteItem->setTag(EIE_DELETE);
	m_editMenu->addChild(deleteItem,MENU_UNUSED_Z);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* leftRotateString ="LR";
    label = CCLabelTTF::create(leftRotateString, "", nFontSize);
    label->setColor(Color3B::RED);
    MenuItemLabel* rotateLeftItem = CCMenuItemLabel::create(label, CC_CALLBACK_1(BWEditLayer::clickEditMenu,this));
    rotateLeftItem->setPosition(pos);
    rotateLeftItem->setTag(EIE_ROTATE_LEFT);
    m_editMenu->addChild(rotateLeftItem,MENU_UNUSED_Z); 
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* rightRotateString ="RR";
    label = CCLabelTTF::create(rightRotateString, "", nFontSize);
    label->setColor(Color3B::RED);
    labelItem = CCMenuItemLabel::create(label, CC_CALLBACK_1(BWEditLayer::clickEditMenu,this));
    labelItem->setPosition(pos);
    labelItem->setTag(EIE_ROTATE_RIGHT);
    m_editMenu->addChild(labelItem,MENU_UNUSED_Z); 
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* editString = "edit";
    label = CCLabelTTF::create(editString, "", nFontSize);
	label->setColor(Color3B::RED);
    labelItem = CCMenuItemLabel::create(label, CC_CALLBACK_1(BWEditLayer::clickEditMenu,this));
    labelItem->setPosition(pos);
    labelItem->setTag(EIE_EDIT);
    m_editMenu->addChild(labelItem,MENU_UNUSED_Z);

    
    
    //Size scrolSize = Size(contentSize.width,pNpcEditScrolLayer->getContentSize().height);
    //pNpcEditScrolLayer->setScrollContentSize(scrolSize);

    //======================================
    Size inputSize = Size(100,60);

    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_EditLoad = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_EditLoad->setText("1");
	m_EditLoad->setPosition(pos);
	pNpcEditScrolLayer->addSubChild(m_EditLoad);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = CCLabelTTF::create("load", "", nFontSize);
	label->setColor(Color3B::RED);
    labelItem = MenuItemLabel::create(label,CC_CALLBACK_1(BWEditLayer::clickLoadLevelNpc,this));
    labelItem->setPosition(pos);
    labelItem->setTag(EIE_EDIT);
    m_editMenu->addChild(labelItem,MENU_UNUSED_Z);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    m_EditSave = EditBox::create(inputSize, Scale9Sprite::create("input.png"));
	m_EditSave->setText("1");
	m_EditSave->setPosition(pos);
	pNpcEditScrolLayer->addSubChild(m_EditSave);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    label = CCLabelTTF::create("save", "", nFontSize);
	label->setColor(Color3B::RED);
    labelItem = MenuItemLabel::create(label,CC_CALLBACK_1(BWEditLayer::clickSaveLevelNpc,this));
    labelItem->setPosition(pos);
    labelItem->setTag(EIE_EDIT);
    m_editMenu->addChild(labelItem,MENU_UNUSED_Z);
    
    nIndexX++;
    pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,nIndexY);
    const char* pszClose = "close";
    label = CCLabelTTF::create(pszClose, "", nFontSize);
	label->setColor(Color3B::RED);
    labelItem = MenuItemLabel::create(label,CC_CALLBACK_1(BWEditLayer::clickClose,this));
    labelItem->setPosition(pos);
    labelItem->setTag(EIE_EDIT);
    m_editMenu->addChild(labelItem,MENU_UNUSED_Z);
    
    //=======================================
    m_NpcPropertyLayer = BWDetailNPCLayer::create(Color4B(0,0,200,255), contentSize.width, contentSize.height);
    m_NpcPropertyLayer->setAnchorPoint(Point(0.5,0));
    m_NpcPropertyLayer->setPosition(Point(contentSize.width*0.5,0));
    m_NpcPropertyLayer->setEditLayer(this);
    addChild(m_NpcPropertyLayer,DETAIL_Z);
    m_NpcPropertyLayer->setVisible(false);
}

void BWEditLayer::clickClose(Ref* pObj)
{
    removeFromParent();
}

//点击加载关卡
void BWEditLayer::clickLoadLevelNpc(Ref* pObj)
{
    const char* npcFileName = m_EditLoad->getText();
	int npcFileId = atoi(npcFileName);
	if(npcFileId == 0)
    {
        return;
    }
    LevelData levelData;
    ResManager::shareResManager()->loadLevelXml(npcFileId, &levelData);
    
    _nLevelScreenCount = levelData.nScreenCount;
    
    clearNpcInfo();
    
    std::map<int,NpcData>::iterator it = levelData.mapLevelNpc.begin();
    while(it != levelData.mapLevelNpc.end())
    {
        NpcData* pNpc = &it->second;
        EditNpcData* pNpcData = new EditNpcData();
        pNpcData->npcData = *pNpc;
        m_mapNpcs[pNpcData->guid] = pNpcData;
        ++it;
    }
    
    drawNpcInfo();
}

//点击保存关卡
void BWEditLayer::clickSaveLevelNpc(Ref* pObj)
{
    const char* pLevelFileName = m_EditSave->getText();
	int nLevelNpcId = atoi(pLevelFileName);
	char  chrNpcFile[COMMON_STRING_SIZE] = {0};
	sprintf(chrNpcFile,"%d_npc",nLevelNpcId);
	saveNpcXmlFile(chrNpcFile);
}


void BWEditLayer::setEnable(bool flag)
{
}

void BWEditLayer::showQuitAlert()
{
}

void BWEditLayer::showSaveAlert()
{
}


void BWEditLayer::saveAllFile()
{

}


#pragma mark 上下
void BWEditLayer::clickUpAndDown(Ref* pRef)
{
}

#pragma mark 减屏
void BWEditLayer::clickSubScreen(Ref* pRef)
{
    int screenCount = m_mainLayerData.tileGroup.vTiles.size();

    if(screenCount == 2) return;
    //LevelTile levelTile = m_mainLayerData.tileGroup.vTiles[screenCount-1];
//    if(levelTile.pSprite)
//    {
//        //levelTile.pSprite->removeFromParentAndCleanup(true);
//    }
    
    m_mainLayerData.tileGroup.vTiles.erase(m_mainLayerData.tileGroup.vTiles.end());
    clean();
    editLevelMapData();
    buildLevel();
    
    
    m_screenCount = m_mainLayerData.tileGroup.vTiles.size();
    
    char countString[256] = {0};
    sprintf(countString, "%d",m_screenCount);
    m_screenCountField->setText(countString);
}

#pragma mark 加屏
void BWEditLayer::clickAddScreen(Ref* pRef)  //加屏
{
    //int screenCount = m_mainLayerData.tileGroup.vTiles.size();
    //LevelTile lastTile = m_mainLayerData.tileGroup.vTiles[screenCount-1];
    LevelTile newTile;
//    newTile.pSprite = NULL;
//    newTile.tid =  lastTile.tid;
//    newTile.pos = Vertex2F(lastTile.pos.x+1290,lastTile.pos.y);
    m_mainLayerData.tileGroup.vTiles.push_back(newTile);
    
    clean();
    editLevelMapData();
    buildLevel();
    
    m_screenCount = m_mainLayerData.tileGroup.vTiles.size();
    
    char countString[256] = {0};
    sprintf(countString, "%d",m_screenCount);
    m_screenCountField->setText(countString);
}

#pragma mark 背景加屏到 main layer
void  BWEditLayer::editLevelMapData()
{}

#pragma mark 选择模板
void  BWEditLayer::selectScreenCount(int screenCount) // 
{
    if(screenCount==0) return;
    LevelTileGroup group =   m_mainLayerData.tileGroup;
    
    LevelTile tile2 = group.vTiles[1];
    
    for(int i=0; i<m_mainLayerData.tileGroup.vTiles.size(); i++)
    {        
        LevelTile& lt = m_mainLayerData.tileGroup.vTiles[i];
//        if(lt.pSprite)
//        {
//           // lt.pSprite->removeFromParentAndCleanup(true);
//        }
    }
    
    m_mainLayerData.tileGroup.vTiles.clear();
    
    for(int i=0;i<screenCount;++i)
    {
        LevelTile tile;
//        tile.tid = tile2.tid;
//        tile.pos = Vertex2F(tile2.pos.x*i,tile2.pos.y);
//        tile.pSprite = NULL;
        m_mainLayerData.tileGroup.vTiles.push_back(tile);
    }
    
    clean();
    editLevelMapData();
    buildLevel();
    
}

void BWEditLayer::clickModel(Ref* pRef)
{
}

void  BWEditLayer::addBird(const char* baseName,Point position,int zOrder)
{
}


void BWEditLayer::clickBgList(Ref* pRef)
{
    MenuItemSprite* selectItem = (MenuItemSprite*)pRef;
	int bgId = selectItem->getTag();
    selectEditLevel(bgId);
}

void BWEditLayer::sortAllNpcActionData()
{
    std::map<int,EditNpcData*>::iterator it = m_mapNpcs.begin();
    while(it != m_mapNpcs.end())
    {
        sortAction(&it->second->npcData.actData);
        ++it;
    }
}

void BWEditLayer::setLevelDataToField()
{
    char temp[COMMON_STRING_SIZE] = {0};
    sprintf(temp,"%d",m_levelInfo.guide);
    m_guidField->setText(temp);
    
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%d",m_levelInfo.difficulty);
    m_difficultyField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%.02f",m_levelInfo.timelimit);
    m_timeLimitField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%d",m_levelInfo.fog);
    m_fogField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%d",m_levelInfo.rain);
    m_rainField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%d",m_levelInfo.snow);
    m_snowField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%.02f",m_levelInfo.fog_time_start);
    m_fogStarTimeField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%.02f",m_levelInfo.fog_time_end);
    m_fogEndTimeField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%.02f",m_levelInfo.fog_keep_time);
    m_fogKepTimeField->setText(temp);
    
    memset(temp,0,COMMON_STRING_SIZE);
    sprintf(temp,"%.d",m_levelInfo.agent_count);
    m_agentCountField->setText(temp);
    
    int agentCount = m_levelInfo.vAgents.size();
    for(int i=0;i<agentCount;++i)
    {
        if(i<10)
        {
            EditBox* agentField = (EditBox*)m_agentFieldArray->getObjectAtIndex(i);
            
            memset(temp,0,COMMON_STRING_SIZE);
            sprintf(temp,"%.d",m_levelInfo.vAgents[i]);
            agentField->setText(temp);
        }
    }
}

// 选择背景类型 
void BWEditLayer::loadLevelOld(Ref* pRef)
{
}

void BWEditLayer::loadNpc(std::map<int,ObjectDataTemplate>& mapCurrentNpcItemMap)
{
    std::map<int,ObjectDataTemplate>::iterator it = mapCurrentNpcItemMap.begin();
    while(it != mapCurrentNpcItemMap.end())
    {
        ObjectDataTemplate& odt = it->second;
        
        EditNpcData* pNpcData = new EditNpcData();
        
        pNpcData->editNpcType = odt.characterType;
        
        pNpcData->npcData = odt.npcItemData;
        
		m_mapNpcs[pNpcData->guid] = pNpcData;
        
        ++it;
    }
}

#pragma mark  点击保存文件
void BWEditLayer::saveLevel(Ref* pRef)
{    
    showSaveAlert();
    m_circleSprite->setVisible(false);
    m_lockTogItem->setSelectedIndex(1); //锁定
    
}


#pragma mark  保存npc和物品文件
bool BWEditLayer::saveNpcXmlFile(const char* pNpcName)
{
	XMLDocument doc;
    const char* header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    doc.Parse(header);
    
    XMLElement* edit_root = doc.NewElement("edit_root") ;
	edit_root->SetAttribute( "file_version", "2" );
    doc.LinkEndChild(edit_root);
    
    XMLElement* edit_npcs = doc.NewElement("edit_npcs");
    edit_root->LinkEndChild(edit_npcs);

    std::map<int,EditNpcData*>::iterator it = m_mapNpcs.begin();
    
    int nIndex = 1;
    while(it != m_mapNpcs.end())
    {
        XMLElement* npc = doc.NewElement("npc");
        edit_npcs->LinkEndChild(npc);
        
        npc->SetAttribute("index", nIndex++);
        npc->SetAttribute("npc_id",  it->second->npcData.nTabId);

        npc->SetAttribute("zorder", it->second->npcData.zOrder);
        npc->SetAttribute("posx", it->second->npcData.pos.x);
        npc->SetAttribute("posy", it->second->npcData.pos.y);
        
        npc->SetAttribute("flipx", it->second->npcData.flipX);
        npc->SetAttribute("flipy", it->second->npcData.flipY);
        
        npc->SetAttribute("rotate", it->second->npcData.rotate);
        npc->SetAttribute("scale", it->second->npcData.scale);
        npc->SetAttribute("opacity", it->second->npcData.opacity);
        npc->SetAttribute("trigger_dist", it->second->npcData.triggerDistance);
        
        // save npc action
        ActionData* pActionData = &it->second->npcData.actData;
        if(pActionData)
        {
            XMLElement* pEleCreate = doc.NewElement("actions");
            npc->LinkEndChild(pEleCreate);
            saveActionData(pActionData,pEleCreate,&doc);
        }
        //save slot
        std::map<int,SlotData>* pMapSlotData = &it->second->npcData.mapSlotData;
        XMLElement* pSlots = doc.NewElement("slots");
        npc->LinkEndChild(pSlots);
        saveSlotData(pMapSlotData,pSlots,&doc);
        
        ++it;
    }
    
    std::string fullpath = FileUtils::getInstance()->getWritablePath();
    fullpath.append(pNpcName);
    fullpath.append(".xml");
    doc.SaveFile(fullpath.c_str());
    return true;
}

#pragma mark 编辑属性
void BWEditLayer::clickEdit()
{
    if(m_SelectNpcId == INVALID_ID)
        return;

    m_NpcPropertyLayer->setSelectNpcId(m_SelectNpcId);
    m_NpcPropertyLayer->setVisible(true);
    
    //m_NpcPropertyLayer->setEnable(true);
    //setListMenuEnable(false);
    //m_bottomMenu->setTouchEnabled(false);
   
   // m_circleSprite->setVisible(false);
    //setTouchEnabled(false);
    
    //setEnable(false);
    
}
bool BWEditLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    //m_editMenu->setTouchEnabled(false);
    Size winSize = CCDirector::getInstance()->getWinSize();
    m_beginPoint = touch->getLocation();
//	if(m_lockTogItem->getSelectedIndex() == 1)
//	{
//		m_isTouchLayerFlag = true;  //锁定
//		return true;
//	}
	
	if(m_circleSprite->isVisible() == true)
	{
		Rect circleRect = m_circleSprite->boundingBox();
		Point touchPos = m_beginPoint;
		
		if(circleRect.containsPoint(touchPos))
		{
			m_beginPoint = touchPos;
            m_isTouchLayerFlag = false;
			return true;   //点击的圆圈
		}
	}
	//点击npc
	m_SelectNpcId = INVALID_ID;
	int npcId = 0;
	int layerId = 0;
	m_circleSprite->setVisible(false);
    
    Point centerPoint = Point(winSize.width/2,winSize.height/2);
    Point dir = m_beginPoint - centerPoint;
    Point moveTouchPoint = dir * m_scale;
    Point newtouchPos = m_beginPoint + moveTouchPoint;
    Point touchNpcPos =  m_pMoveLayer->convertToNodeSpace(newtouchPos);
    
	if(true == isTouchNpc(touchNpcPos,npcId))
	{
		m_SelectNpcId = npcId;
        
        if(m_oldSelSpriteId != INVALID_ID)  //红色的还原
        {
            std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(m_oldSelSpriteId);
            
            if(itNpc != m_mapNpcs.end())
            {
                Sprite* pNpcSprite = itNpc->second->pNpcSprite;
                
                if(pNpcSprite != NULL)
                {
                    //pNpcSprite->setColor(Color3B::WHITE);
                    m_oldSelSpriteId=INVALID_ID;
                }
            }
        }
		
		std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(m_SelectNpcId);
		if(itNpc != m_mapNpcs.end())
		{
			Sprite*  pNpcSprite = itNpc->second->pNpcSprite;
            if(pNpcSprite!=NULL)
            {
                m_oldSelSpriteId = m_SelectNpcId;
                //pNpcSprite->setColor(Color3B::RED);
                
                Point wordPoint = m_pMoveLayer->convertToWorldSpace(pNpcSprite->getPosition());
                Point newtouchPos = wordPoint - moveTouchPoint;
                m_circleSprite->setPosition(newtouchPos);
                m_circleSprite->setVisible(true);
                m_circleSprite->setRotation(0);
                
            }
		}
	}
	else if(true == isTouchLayer(m_beginPoint,layerId))
	{
		m_isTouchLayerFlag = true;
        if(m_oldSelSpriteId != INVALID_ID) //红色的还原
        {
            std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(m_oldSelSpriteId);
            
            if(itNpc != m_mapNpcs.end())
            {
                Sprite*  pNpcSprite = itNpc->second->pNpcSprite;
                if(pNpcSprite!=NULL)
                {
                    //pNpcSprite->setColor(Color3B::WHITE);
                    m_oldSelSpriteId = INVALID_ID;
                }
            }
        }
	}
    return true;

}
void BWEditLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point touchLocation = touch->getLocation();
	Point pretouchLocation = touch->getPreviousLocation();
	
    float fMoveY = touchLocation.y - pretouchLocation.y;
    float fMoveX = touchLocation.x - pretouchLocation.x;
    
	if(m_isTouchLayerFlag == true)
	{
        m_pMoveLayer->setPosition( Point(m_pMoveLayer->getPosition().x + fMoveX,m_pMoveLayer->getPosition().y + fMoveY) );
        
	}
    else //npc
    {
        if(m_SelectNpcId != INVALID_ID)
        {
            std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(m_SelectNpcId);
            if(itNpc != m_mapNpcs.end())
            {
                Sprite* pSprite = itNpc->second->pNpcSprite;
                pSprite->setPosition(Point(pSprite->getPosition().x + fMoveX, pSprite->getPosition().y + fMoveY ));
                
                Point wordPoint = m_pMoveLayer->convertToWorldSpace(pSprite->getPosition());
                m_circleSprite->setPosition(wordPoint);
            }
        }
    }
}

void BWEditLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    
	m_isTouchLayerFlag = false;
    
    EditNpcData* pCurNpcData =  getNpcData(m_SelectNpcId);
    if(pCurNpcData)
    {
        if(pCurNpcData->pNpcSprite)
        {
            pCurNpcData->npcData.pos.x = pCurNpcData->pNpcSprite->getPosition().x;
            pCurNpcData->npcData.pos.y = pCurNpcData->pNpcSprite->getPosition().y;
        }
    }
}

#pragma mark 判断是点击场景中npc
bool BWEditLayer::isTouchNpc(Point touchPos,int& npcId)
{
	EditNpcData npcData;

	std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.begin();
	while(itNpc != m_mapNpcs.end())
	{
		EditNpcData* pNpcData = itNpc->second;
		if (pNpcData->pNpcSprite)
		{
			Rect rect = pNpcData->pNpcSprite->boundingBox();
			if(true == rect.containsPoint(touchPos))
			{
				npcId = pNpcData->guid;
				return true;
			}
		}
		++itNpc;
	}
	return false;
}
#pragma mark 判断是点击移动layer
bool BWEditLayer::isTouchLayer(Point touchPos,int& layerId)
{
	Size winSize = CCDirector::getInstance()->getWinSize();
	if(touchPos.y<winSize.height - NPC_LIST_HEIGHT - ITEM_LIST_HEIGHT)
	{
		return true;
	}
	return false;
}
#pragma mark  计算移动layer移动距离
void BWEditLayer::getMoveLayerPosChange(Point& change)
{
	change.x = m_pMoveLayer->getPosition().x - m_startPos.x ;
	change.y = m_pMoveLayer->getPosition().y - m_startPos.y ;
}
#pragma mark  取editnpc模板
EditNpcData* BWEditLayer::getNpcData(int npcId)
{
	std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(npcId);
	if(itNpc != m_mapNpcs.end())
	{
		return itNpc->second;   
	}
	return NULL;
}
void BWEditLayer::returnFromDetailNpcLayer()
{
	m_NpcPropertyLayer->setVisible(false);
    m_NpcPropertyLayer->setEnable(false);
    setEnable(true);
    
}

void BWEditLayer::returnToMainScene(Ref* p)
{
    showQuitAlert();
    m_lockTogItem->setSelectedIndex(1);
}

void BWEditLayer::tick(float dt)
{
}
#pragma mark  编辑完后重新贴图片
void BWEditLayer::reDrawNpc(int npcId)
{
	EditNpcData* pNpcData = getNpcData(npcId);
	if (pNpcData)
	{
		Point pos = pNpcData->npcData.pos;
		pNpcData->pNpcSprite->setPosition(pos);
		pNpcData->pNpcSprite->setRotation(pNpcData->npcData.rotate);
        pNpcData->pNpcSprite->setFlippedX(pNpcData->npcData.flipX);
        pNpcData->pNpcSprite->setFlippedY(pNpcData->npcData.flipY);
        pNpcData->pNpcSprite->setZOrder(pNpcData->npcData.zOrder);
	}
    m_circleSprite->setVisible(true);
}

//-----------------------------------------
#pragma mark  加载地图
//-----------------------------------------
bool BWEditLayer::loadLevel(int n)
{
    return false;
}

void BWEditLayer::selectEditLevel(int level)
{
    loadLevel(level);
}

#pragma mark 保存地图
void BWEditLayer::saveLevelMap(const char* levelfile)
{}


#pragma mark  贴关卡文件中的背景
bool BWEditLayer::buildLevel()
{
    return false;
}

#pragma mark  点击物品
void BWEditLayer::clickItemList(Ref* pRef)
{

}

#pragma mark  点击npc列表 
void BWEditLayer::clickNpcList(Ref* pRef,Control::EventType controlEvent)
{
	Size contentSize = getContentSize();
	
	CCButton* selectItem = (CCButton*)pRef;
	int npcListId = selectItem->getTag();

	EditNpcData* pNpcData = new EditNpcData();
	m_SelectNpcId = pNpcData->guid;
	int nNpcId = npcListId;
    
    MonsterTabData* pMonsterTabData = ResManager::shareResManager()->getMonsterData(nNpcId);
    if(!pMonsterTabData)
    {
        log("pMonsterTabData=nNpcId=%d",nNpcId);
        return;
    }
    npcItemIndexStr nis;
    nis.nId = nNpcId;
    Point changePos;
    getMoveLayerPosChange(changePos);
    Point pos;
    pos.x = contentSize.width/2 - changePos.x;
    pos.y = contentSize.height/2 - changePos.y;

    Sprite* pSprite = Sprite::create(pMonsterTabData->pszIcon);
    pSprite->setPosition(pos);
    m_pMoveLayer->addChild(pSprite,99999);
    
    
    m_oldSelSpriteId = pNpcData->guid;
    
    pNpcData->pNpcSprite = pSprite;
    pNpcData->editNpcType = CTE_NPC;

	m_mapNpcs[pNpcData->guid] = pNpcData;
}

#pragma mark  清除背景data信息
void BWEditLayer::clearAllData()
{
}

void BWEditLayer::clean()
{
}

void BWEditLayer::setListMenuEnable(bool enableFlag)
{
}

#pragma mark  编辑npc
void BWEditLayer::copyNpc()
{
    EditNpcData* pOldNpcData =  getNpcData(m_SelectNpcId);
    
    if(!pOldNpcData)
        return;
    Sprite* oldSprite = (Sprite*)pOldNpcData->pNpcSprite;

    int nNpcId = pOldNpcData->npcData.nTabId;
    MonsterTabData* pMonsterTabData = ResManager::shareResManager()->getMonsterData(nNpcId);
    if(!pMonsterTabData)
        return;
    std::string strNpcPng = pMonsterTabData->pszIcon;
    
    EditNpcData* pNewNpc = new EditNpcData();
    Sprite* pSprite = Sprite::create(strNpcPng.c_str());
    Point copyPosition = Point(oldSprite->getPosition().x + 150,oldSprite->getPosition().y);
    pSprite->setRotation(oldSprite->getRotation());
    pSprite->setPosition(copyPosition);
    pSprite->setScale(oldSprite->getScale());
    pSprite->setFlippedX(oldSprite->isFlippedX());
    pSprite->setFlippedY(oldSprite->isFlippedY());
    
    
    pNewNpc->npcData = pOldNpcData->npcData;
    pNewNpc->npcData.pos = pSprite->getPosition();     //存位置
    pNewNpc->npcData.rotate = pSprite->getRotation();  //存角度
    
    m_pMoveLayer->addChild(pSprite,MOVE_NPCS_Z);
    pNewNpc->pNpcSprite = pSprite;
    pNewNpc->editNpcType = pOldNpcData->editNpcType;
    
    m_mapNpcs[pNewNpc->guid] =pNewNpc;

}

void BWEditLayer::stopMoveAction()
{
    EditNpcData* pCurNpcData =  getNpcData(m_SelectNpcId);
    if(!pCurNpcData)
        return;
    NpcData npcData = pCurNpcData->npcData;
    Sprite* pSprite = (Sprite*)pCurNpcData->pNpcSprite;
    pSprite->stopActionByTag(EDIT_MOVEACTION_TAG);
    pSprite->setPosition(npcData.pos);
    pSprite->setRotation(npcData.rotate);
    pSprite->setOpacity(255);
    pSprite->setScale(npcData.scale);
}

void BWEditLayer::playAction()
{
    if(m_SelectNpcId == INVALID_ID)
        return;
	
    std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(m_SelectNpcId);
    if(itNpc != m_mapNpcs.end())
    {
        Sprite* pSprite = (Sprite*)itNpc->second->pNpcSprite;
        EditNpcData* pEditNpcData = itNpc->second;
    
        if(!pEditNpcData)
            return;
        
        BWUnitManager::shareBWUnitManager()->playAction(pSprite, &(pEditNpcData->npcData.actData));
    }
}

void BWEditLayer::deleteNpc()
{
    if(m_oldSelSpriteId != INVALID_ID)
    {
        std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(m_oldSelSpriteId);
        Sprite* pNpcSprite = NULL;
        if(itNpc != m_mapNpcs.end())
        {
            pNpcSprite = itNpc->second->pNpcSprite;
        }
        if(pNpcSprite!=NULL)
        {
            pNpcSprite->setColor(Color3B::WHITE);
            m_oldSelSpriteId = INVALID_ID;
        }
    }
    
    std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.find(m_SelectNpcId);
    if(itNpc != m_mapNpcs.end())
    {
        itNpc->second->pNpcSprite->removeFromParentAndCleanup(true);
        itNpc->second->pNpcSprite=NULL;
        
        CC_SAFE_DELETE(itNpc->second);
        m_mapNpcs.erase(itNpc);
        m_circleSprite->setVisible(false);
    }
}

float BWEditLayer::getNpcOpacity()
{
    EditNpcData* currentNpc =  getNpcData(m_SelectNpcId);
    if(!currentNpc)  return 255;
    return currentNpc->npcData.opacity;
}

void BWEditLayer::setNpcOpacity(float npcOpacity)
{
    EditNpcData* pCurNpcData =  getNpcData(m_SelectNpcId);
    if(!pCurNpcData)
        return;
    pCurNpcData->npcData.opacity = npcOpacity;
    pCurNpcData->pNpcSprite->setOpacity(npcOpacity);
}

float BWEditLayer::getNpcScale()
{
    EditNpcData* pCurNpcData =  getNpcData(m_SelectNpcId);
    if(!pCurNpcData)  return 1.0;
    return pCurNpcData->npcData.scale;
}

void BWEditLayer::setNpcScale(float npcScale)
{
    EditNpcData* pCurNpcData =  getNpcData(m_SelectNpcId);
    if(!pCurNpcData)
        return;
    pCurNpcData->npcData.scale = npcScale;
    pCurNpcData->pNpcSprite->setScale(npcScale);
}

#pragma mark 
void BWEditLayer::clickEditMenu(Ref* pRef)
{
	MenuItemSprite* selectItem = (MenuItemSprite*)pRef;
	int editMenuItemId = selectItem->getTag();
    
    switch (editMenuItemId) 
    {
        case EIE_COPY:
        {
            copyNpc();
        }
            break;
        case EIE_ACTION:
        {
            playAction();
        }
            break;
        case EIE_STOP:
        {
            stopMoveAction();
        }
            break;
        case EIE_DELETE:
        {
            deleteNpc();
        }
            break;
        case EIE_ROTATE_LEFT:
        {
            rotateBy(-ROTATE_CHANGE);
        }
            break;
        case EIE_ROTATE_RIGHT:
        {
           rotateBy(ROTATE_CHANGE);
        }
            break;
        case EIE_EDIT:
        {
            clickEdit();
        }
            break;
        default:
            break;
    }
}

void BWEditLayer::rotateBy(float degree)
{
    EditNpcData* pCurNpcData =  getNpcData(m_SelectNpcId);
    if(!pCurNpcData)
        return;
    
    Sprite* currentSprite = pCurNpcData->pNpcSprite;
    float oldDegree = currentSprite->getRotation();
    float newDegree = oldDegree + degree;
    pCurNpcData->pNpcSprite->setRotation(newDegree);
    pCurNpcData->npcData.rotate = newDegree;
}

#pragma mark  播放动画
bool BWEditLayer::startAnim(Sprite* pSprite, int animId)
{
	return true;
}

#pragma mark 锁定npc
void BWEditLayer::clickLock(Ref* pRef)
{
	MenuItemToggle* selectItem = (MenuItemToggle*)pRef;
	int selectIndex = selectItem->getSelectedIndex();
	if(selectIndex == 0)
	{
        setListMenuEnable(true);
	}
	else if(selectIndex == 1)  //lock
	{
        m_SelectNpcId = INVALID_ID;
        setListMenuEnable(false);
        m_circleSprite->setVisible(false);
	}
}



int BWEditLayer::tileIndexOfNpc(Point position)
{
    int allCount = m_bgSpriteArray->count();
    for(int i=0; i!=m_bgSpriteArray->count(); ++i)
	{
		Sprite* bgSprite = (Sprite*)m_bgSpriteArray->getObjectAtIndex(i);
		Rect rect = bgSprite->boundingBox();
        
        if(position.x > rect.origin.x && position.x < rect.origin.x+rect.size.width)
        {
            return i;
        }
	}
    allCount--;
	return allCount;
  
}

int BWEditLayer::computeTileCountOfNpc()
{
    std::map<int,EditNpcData*>::iterator it = m_mapNpcs.begin();
    int index=0;
    while(it != m_mapNpcs.end())
    {
        float X = it->second->npcData.pos.x;
        float Y = it->second->npcData.pos.y;
        Point position = Point(X,Y);
        int indexOfNpc = tileIndexOfNpc(position);
        if(index < indexOfNpc)
        {
            index = indexOfNpc;
        }
        ++it;
    }
    index++;
    return index;
}

#pragma mark  加npc列表
void BWEditLayer::drawNpcList()
{
    Size contentSize = getContentSize();
    
    CCScrollLayer* pScrollLayer = CCScrollLayer::scrollLayerWidthColor(Color4B(0,200,0,200), Size(contentSize.width,100));
    pScrollLayer->setAnchorPoint(Point(0,1));
    pScrollLayer->setPosition(Point(0,contentSize.height));
    addChild(pScrollLayer,BG_LISTLAYER_Z);
    
    
    float fSpaceY = 10;
    float fSpaceX = 10;
    
    float fWidth = 100;
    float fHeight = 100;
    
    float fOriginX = 10;
    float fOriginY = 10;
    
    int nIndexX =0;
    std::map<int, MonsterTabData>* pMapMonster = ResManager::shareResManager()->getMonsterMap();
    std::map<int, MonsterTabData>::iterator it = pMapMonster->begin();
    while (it != pMapMonster->end())
    {
        MonsterTabData* pMonsterTabData = &it->second;
        ++it;
        
        CCButton* pBtnNpc = CCButton::create(pMonsterTabData->pszIcon,false);
        Size BtnSignSize = pBtnNpc->getContentSize();
        Point pos = CCAPI::shareCCAPI()->getSpacePos(fOriginX,fWidth,fSpaceX,fOriginY,fHeight,fSpaceY,nIndexX,0);
        nIndexX++;
        pBtnNpc->setPosition(pos);
        pBtnNpc->addTargetWithActionForControlEvents(this, cccontrol_selector(BWEditLayer::clickNpcList), Control::EventType::TOUCH_UP_INSIDE);
        pBtnNpc->setZoomOnTouchDown(false);
        pBtnNpc->setAreaOutResponse(true);
        pBtnNpc->setTag(pMonsterTabData->nID);
        pScrollLayer->addSubChild(pBtnNpc);
        
    }
}
#pragma mark  加item列表
void BWEditLayer::drawItemList()
{
}

#pragma mark m_npcs 清空
void BWEditLayer::clearNpcInfo() 
{
	std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.begin();
	while( itNpc != m_mapNpcs.end())
	{
        EditNpcData* pNpcData = itNpc->second;
        ++itNpc;
        if(!pNpcData)
            continue;
        if(!pNpcData->pNpcSprite)
        {
            continue;
        }
        pNpcData->pNpcSprite->removeFromParentAndCleanup(true);
        pNpcData->pNpcSprite = NULL;
        
        CC_SAFE_DELETE(itNpc->second);
	}
	m_mapNpcs.clear();
}

#pragma mark   贴npc和物品
void BWEditLayer::drawNpcInfo()
{
	std::map<int,EditNpcData*>::iterator itNpc = m_mapNpcs.begin();
	while( itNpc != m_mapNpcs.end())
	{
		EditNpcData* pNpc = itNpc->second;
        ++itNpc;
		
        Point pos = pNpc->npcData.pos;
        MonsterTabData*	pNpcTemplate = ResManager::shareResManager()->getMonsterData(pNpc->npcData.nTabId);
        if(!pNpcTemplate)
        {
            log("BWEditLayer::drawNpcInfo");
            continue;
        }
        Sprite* pSprite = Sprite::create(pNpcTemplate->pszIcon);
        pSprite->setPosition(pos);
        pSprite->setRotation(pNpc->npcData.rotate);
        pSprite->setFlippedX(pNpc->npcData.flipX);
        pSprite->setFlippedY(pNpc->npcData.flipY);
        int npcZ = pNpc->npcData.zOrder;
        m_pMoveLayer->addChild(pSprite,MOVE_NPCS_Z+npcZ);
        pNpc->pNpcSprite = pSprite;
    }
}

bool sortctionEdit(const ActionIntervalData& action1, const ActionIntervalData& action2)
{
	return action1.order < action2.order;
}

#pragma mark 排序动作

void BWEditLayer::sortAction(ActionData* pActionDataStr)
{
    if(pActionDataStr == NULL) return;
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
    
    std::sort(actData->actionArray.begin(),actData->actionArray.end(), sortctionEdit);
}

void  BWEditLayer::saveActionData(ActionData* pActData, XMLElement* pElementCreate,XMLDocument* pDoc)
{
    sortAction(pActData);
    if(pActData==NULL || pActData->actionArray.size() == 0)
    {
        return ;
    }
    int repeatCount = pActData->repeatCount;
    int type = pActData->actType;
    int reverseFlag = pActData->reverseFlag;
    int repeatReverseFlag = pActData->repeatReverseFlag;
    
    pElementCreate->SetAttribute("repeatcount",repeatCount);
    pElementCreate->SetAttribute("ActionType", type);
    pElementCreate->SetAttribute("reverse", reverseFlag);
    pElementCreate->SetAttribute("repeatreverse", repeatReverseFlag);
    
    int allCount = (int)pActData->actionArray.size();
    for(int i=0; i<allCount; ++i)
    {
        XMLElement* action = pDoc->NewElement("action");
        pElementCreate->LinkEndChild(action);
        
        ActionIntervalData actInterval = pActData->actionArray[i];
        
        switch (actInterval.actType) 
        {
            case AT_MOVE:
            {
                moveData movData = pActData->movData;
                int order = movData.order;
                ActionType actType = movData.actType;
                
                float duration = movData.duration;
                Point point = movData.endPoint;
                
                int reverse = movData.reverseFlag;
                int repeatCount = movData.repeatCount;
                int repeatReverse = movData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                action->SetAttribute("endposx", point.x);
                action->SetAttribute("endposy", point.y);
                
            }
                break;
            case AT_BEZIER:
            {
                bezierData bezData = pActData->bezData;
                int order = bezData.order;
                ActionType actType = bezData.actType;
                float duration = bezData.duration;
                Point onePoint = bezData.onePoint;
                Point twoPoint = bezData.twoPoint;
                Point endPoint = bezData.endPoint;
                
                int reverse = bezData.reverseFlag;
                int repeatCount = bezData.repeatCount;
                int repeatReverse = bezData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                action->SetAttribute("bezieroneposx", onePoint.x);
                action->SetAttribute("bezieroneposy", onePoint.y);
                action->SetAttribute("beziertwoposx", twoPoint.x);
                action->SetAttribute("beziertwoposy", twoPoint.y);
                action->SetAttribute("bezierendposx", endPoint.x);
                action->SetAttribute("bezierendposy", endPoint.y);
                
            }
                break;
            case AT_JUMP:
            {
                jumpData jumData = pActData->jumData;
                int order = jumData.order;
                ActionType actType = jumData.actType;
                float duration = jumData.duration;
                int jumCount = jumData.jumCount;
                float height = jumData.height;
                Point endPoint = jumData.endPoint;
                
                int reverse = jumData.reverseFlag;
                int repeatCount = jumData.repeatCount;
                int repeatReverse = jumData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("jumpcount", jumCount);
                action->SetAttribute("duration", duration);
                action->SetAttribute("jumpendposx", endPoint.x);
                action->SetAttribute("jumpendposy", endPoint.y);
                action->SetAttribute("jumpheight", height);
                
            }
                break;
            case AT_SCALE:
            {
                scaleData scaData = pActData->scaData;
                int order = scaData.order;
                ActionType actType = scaData.actType;
                float duration = scaData.duration;
                float scaleX = scaData.sx;
                float scaleY = scaData.sy;
                
                int reverse = scaData.reverseFlag;
                int repeatCount = scaData.repeatCount;
                int repeatReverse = scaData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                action->SetAttribute("scalex", scaleX);
                action->SetAttribute("scaley", scaleY);
                
            }
                break; 
            case AT_ROTATE:
            {
                rotateData rotData = pActData->rotData;
                int order = rotData.order;
                ActionType actType = rotData.actType;
                float duration = rotData.duration;
                float angle = rotData.angle;
                
                int reverse = rotData.reverseFlag;
                int repeatCount = rotData.repeatCount;
                int repeatReverse = rotData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                action->SetAttribute("angle", angle);
                
            }
                break;
            case AT_TINT:
            {
                tintData tinData = pActData->tinData;
                int order = tinData.order;
                ActionType actType = tinData.actType;
                float duration = tinData.duration;
                float red = tinData.deltaRed;
                float green = tinData.deltaGreen;
                float blue = tinData.deltaBlue;
                
                int reverse = tinData.reverseFlag;
                int repeatCount = tinData.repeatCount;
                int repeatReverse = tinData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                action->SetAttribute("red", red);
                action->SetAttribute("green", green);
                action->SetAttribute("blue", blue);
                
            }
                break;
            case AT_FADEIN:
            {
                fadeInData fadInData = pActData->fadInData;
                int order = fadInData.order;
                ActionType actType = fadInData.actType;
                float duration = fadInData.duration;
                
                int reverse = fadInData.reverseFlag;
                int repeatCount = fadInData.repeatCount;
                int repeatReverse = fadInData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                
                
            }
                break;
            case AT_FADEOUT:
            {
                fadeOutData fadOutData = pActData->fadOutData;
                int order = fadOutData.order;
                ActionType actType = fadOutData.actType;
                float duration = fadOutData.duration;
                
                int reverse = fadOutData.reverseFlag;
                int repeatCount = fadOutData.repeatCount;
                int repeatReverse = fadOutData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                
            }
                break;
                
            case AT_BLINK:
            {
                blinkData bliData = pActData->bliData;
                int order = bliData.order;
                ActionType actType = bliData.actType;
                float duration = bliData.duration;
                int count = bliData.count;
                
                int reverse = bliData.reverseFlag;
                int repeatCount = bliData.repeatCount;
                int repeatReverse = bliData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                action->SetAttribute("count", count); 
            }
                break;
            case AT_SKEW:
            {
                skewData skeData = pActData->skeData;
                int order = skeData.order;
                ActionType actType = skeData.actType;
                float duration = skeData.duration;
                float skewX = skeData.deltaSkewX;
                float skewY = skeData.deltaSkewY;
                
                int reverse = skeData.reverseFlag;
                int repeatCount = skeData.repeatCount;
                int repeatReverse = skeData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                action->SetAttribute("skewx", skewX);
                action->SetAttribute("skewy", skewY);
            }
                break;
            case AT_DELAY:
            {
                delayTimeData delayData = pActData->delayData;
                int order = delayData.order;
                ActionType actType = delayData.actType;
                float duration = delayData.duration;
                
                
                int reverse = delayData.reverseFlag;
                int repeatCount = delayData.repeatCount;
                int repeatReverse = delayData.repeatReverseFlag;
                
                action->SetAttribute("reverse", reverse);
                action->SetAttribute("repeatcount", repeatCount);
                action->SetAttribute("repeatreverse", repeatReverse);
                
                action->SetAttribute("order", order);
                action->SetAttribute("type", actType);
                action->SetAttribute("duration", duration);
                
            }
                break;
                
            default:
                break;
        }        
    }    
}

void  BWEditLayer::saveSlotData(std::map<int,SlotData>* pMapSlotData,XMLElement* pSlots,XMLDocument* pDoc)
{
    std::map<int,SlotData>::iterator it = pMapSlotData->begin();
    while(it != pMapSlotData->end())
    {
        
        SlotData* pSlotData = &it->second;
        ++it;
        
        XMLElement* pSolt = pDoc->NewElement("slot");
        pSlots->LinkEndChild(pSolt);
        
        pSolt->SetAttribute("slot_id", pSlotData->nId);
        pSolt->SetAttribute("bullet_id", pSlotData->nBulletId);
        
        pSolt->SetAttribute("slot_pos_x",pSlotData->pos.x);
        pSolt->SetAttribute("slot_pos_y",pSlotData->pos.y);

        
        pSolt->SetAttribute("bullet_speed",pSlotData->nBulletId);
        
        pSolt->SetAttribute("fire_time",pSlotData->fFireTime);
        pSolt->SetAttribute("free_time",pSlotData->fFreeTime);

        pSolt->SetAttribute("bullet_space_time",pSlotData->fBulletSpaceTime);

        
        XMLElement* pEleCreate = pDoc->NewElement("actions");
        pSolt->LinkEndChild(pEleCreate);
        saveActionData(&pSlotData->actionData,pEleCreate,pDoc);
    }
    
}








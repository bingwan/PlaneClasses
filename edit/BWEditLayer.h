
#ifndef __BWEditLayer_H__
#define __BWEditLayer_H__

#include "cocos2d.h"
#include "CommonDef.h"
#include "external/tinyxml2/tinyxml2.h"
#include "CCCutTouchLayer.h"
using namespace tinyxml2;
#include "cocos-ext.h"

class BWMenu;
class CCScrollLayer;

USING_NS_CC;
USING_NS_CC_EXT;


struct EditNpcData
{
	EditNpcData()
	{
		guid        = npcIdGen++ ;
		pNpcSprite  = NULL;
        editNpcType = CTE_UNKNOWN;
	}
    
	int		guid;
	NpcData	npcData;
	Sprite*	pNpcSprite;
	static int npcIdGen;
    characterTypeEnum editNpcType;
    
};

class BWDetailNPCLayer;

class  BWEditLayer : public CCCutTouchLayer
{
public:
    enum editItemEnum
	{
		EIE_UNKNOWN     = 0,
		EIE_COPY        = 1,
		EIE_ACTION		= 2,
        EIE_STOP        = 3,
        EIE_DELETE      = 4,
        EIE_ROTATE_LEFT     = 5,
        EIE_ROTATE_RIGHT    = 6,
        EIE_EDIT            = 7,

	};
    
	BWEditLayer();
	virtual ~BWEditLayer();
	virtual void tick(float dt);
    
    virtual void onEnter();
    virtual void onExit();
    
    void  initUI();
    
	CREATE_FUNC(BWEditLayer);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    //virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    void                startAnalyze();
    void                analyze(CCAcceleration* pAccelerationValue);
	void		saveLevel(Object* pObject);
	void		returnToMainScene(Object* p);
	void        loadLevelOld(CCObject* pObject);
	EditNpcData*	getNpcData(int npcId);
	void		returnFromDetailNpcLayer();
	void		reDrawNpc(int npcId);
    void        selectEditLevel(int level);
    void        setEnable(bool flag);
    void        loadNpc(std::map<int,ObjectDataTemplate>& mapCurrentNpcItemMap);
    void        setNpcScale(float scale);
    float       getNpcScale();
    float       getNpcOpacity();
    void        setNpcOpacity(float npcOpacity);
    void        saveActionData(ActionData* actData, XMLElement* pEle,XMLDocument* pDoc);
    void        saveSlotData(std::map<int,SlotData>* pMapSlotData,XMLElement* pBullets,XMLDocument* pDoc);
    
protected:
	bool	isTouchNpcList(CCPoint touchPos,int& npcIndex);
	bool	isTouchNpc(CCPoint touchPos,int& npcId);
	bool	isTouchLayer(CCPoint touchPos,int& layerId);
	void	clearNpcInfo();
	void	drawNpcList();
	void	drawNpcInfo();
	void    drawItemList();
	bool	saveNpcXmlFile(const char* pNpcName);
	void	getMoveLayerPosChange(Point& change);
	bool    loadLevel(int n);  //加载关卡场景
	bool    buildLevel();
	void    clickBgList(Ref* pObject);
	void    clickNpcList(Ref* pObject,Control::EventType controlEvent);
	void    clear();
	void    clickItemList(Ref* pObject);
	void    setListMenuEnable(bool enableFlag);
	void    clickEditMenu(Ref* pObject);
	bool    startAnim(Sprite* pSprite, int animId);
	void    clickLock(Ref* pObject);
    void    clickSelectLevel(Ref* pObject);
    void    copyNpc();
    void    playAction();
    void    stopMoveAction();
    void    saveUserLevel();
    void    deleteNpc();
    void    share();
    void    rotateBy(float degree);
    //长按
	void		clickEdit();
    void        addLevelItem(int allCount);
    
    void       addBird(const char* baseName,Point position,int zOrder);
    int        computeTileCountOfNpc();
    int        tileIndexOfNpc(Point position);
    void       sortAction(ActionData* pActionDataStr);
    void       sortAllNpcActionData();
    
    void        clickModel(Ref* pObject);
    void        clickSubScreen(Ref* pObject);
    void        clickAddScreen(Ref* pObject);
    
    void        clickUpAndDown(Ref* pObject);
    void        editLevelMapData();
    void        clearAllData();
    void        clean();
    void        selectScreenCount(int screenCount);
    
    void        saveLevelMap(const char* levelfile);
    void        setLevelDataToField();
    
    void        showSaveAlert();
    void        showQuitAlert();
    void        saveAllFile();
    void        clickClose(Ref* pObj);
    void        clickLoadLevelNpc(Ref* pObj);
    void        clickSaveLevelNpc(Ref* pObj);
private:
	
	//编辑框
	EditBox*                        m_EditLoad;
    EditBox*                        m_EditSave;

    
	EditBox*                        m_LevelIdEdit;				//关卡序列（选择）
	EditBox*                        m_LevelNameEdit;			//关卡名称
    EditBox*                        m_userLevelIdEdit;
	LabelTTF*                       m_TileNumLabel;
	bool                            m_isTouchLayerFlag;
	char                            m_LevelName[COMMON_STRING_SIZE];
	char                            m_LevelBgMusic[COMMON_STRING_SIZE];
	int                             m_LevelType;
	int                             m_nLevelId;
	int                             m_LevelEnterNumPerDay;
	int                             m_TileTemplateId;
	int                             m_LevelDistance;
	std::map<int,EditNpcData*>      m_mapNpcs;
	Layer*                          m_pMoveLayer;  //移动的layer
	BWDetailNPCLayer*               m_NpcPropertyLayer;
	int                             m_SelectNpcId; 
	Point                           m_startPos;
	CCScrollLayer*                  m_BgListLayer;
	LevelInfo                       m_levelInfo;
	BgLayerData                     m_bgLayerData;
	ForeLayerData                   m_foreLayerData;
    MainLayerData                   m_mainLayerData;
    
	Array*                          m_bgSpriteArray;  //存tile图片
	BWMenu*                         m_npcListMenu;    //npc列表
	BWMenu*                         m_itemListMenu;	  //物品列表
	Sprite*                         m_circleSprite;   //选中状态的圆圈
	bool                            m_touchCircleFlag; //选中标记
	Point                           m_beginPoint;
	CCScrollLayer*                  m_bottomLayer;    //下边的layer
	BWMenu*                         m_editMenu;		  //圆圈上的菜单
	Menu*                           m_bottomMenu;     //下边的菜单
	MenuItemToggle*                 m_lockTogItem;
    CCScrollLayer*                  m_bglistLayer;
    int                             m_levelBgId;
    bool                            m_analyzeFlag;
    double                          m_startTime;
    bool                            m_startTimeFlag;
    Sprite*                         m_flagSprite;
    
    EditBox*                        m_screenCountField;
    EditBox*                        m_guidField;
    EditBox*                        m_difficultyField;
    EditBox*                        m_timeLimitField;
    EditBox*                        m_fogField;
    EditBox*                        m_fogStarTimeField;
    EditBox*                        m_fogEndTimeField;
    EditBox*                        m_fogKepTimeField;
    EditBox*                        m_agentCountField;
    EditBox*                        m_rainField;
    EditBox*                        m_snowField;
        
    Array*                          m_agentFieldArray;
    int                             m_screenCount;
    float                           m_scale;
    int                             m_oldSelSpriteId;
    int                             _nLevelScreenCount;
};

#endif // __BWEditLayer_H__


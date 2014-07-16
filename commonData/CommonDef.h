//
//  CommonDef.h
//
//  Created by wangbin on 13-1-14.
//
//

#ifndef CommonDef_h
#define CommonDef_h

#include "cocos2d.h"
#include <uuid/uuid.h>
USING_NS_CC;

#define DEBUG_VERSION  1     //bingwan test


#define TAB_READ_TO_UTF8  1

#define ACCOUNT_SERVER_IP           ""
#define ACCOUNT_SERVER_PORT         9010

#define IPHONE_WIDTH   960
#define IPHONE_HEIGHT  640

#define UI_RES_WIDTH    768
#define UI_RES_HEIGHT   1136


#define COMMON_FONT "Arial"
#define FONT_SIZE_32 32
#define FONT_SIZE_30 30

#define LANGUAGE_CN   1
#define LANGUAGE_EN   2
#define LANGUAGE_TYPE LANGUAGE_CN


#define FRONT_BG_PERCENT 2.0
#define MID_BG_PERCENT 0.6
#define FAR_BG_PERCENT 0.4

#define COMBAT_EFFECT_FRONT_Z 2000
#define COMBAT_EFFECT_AFTER_Z 1000

#define NICKNAME_LENGTH_MAX  21

#define CHAR_BUFFER_SIZE 255

#define TIPS_LAYER_Z                    10000
#define TOPUI_LAYER_Z                   1000

#define FLOAT_NONE						-65536.00

#define COMMON_STRING_SIZE 256

#define INVALID_ID -1
#define DEFAULT_FONT  COMMON_FONT


#define MOVE_LAYER_Z		    100
#define BG_LISTLAYER_Z			210
#define NPC_LISTLAYER_Z			200
#define ITEM_LISTLAYER_Z		200
#define BOTTOM_LAYER_Z			200
#define DETAIL_Z                2000

#define BG_LIST_HEIGHT     500
#define BG_LIST_WIDTH      100
#define NPC_LIST_HEIGHT    50
#define ITEM_LIST_HEIGHT	50

#define MOVE_NPCS_Z			900
#define MOVE_CIRCLE_Z		901
#define MOVE_MENU_Z			1000
#define MOVE_ME_Z           901

#define MENU_UNUSED_Z		10
#define EDIT_MOVEACTION_TAG  123
#define REPEAT_COUNT_TAG    100
#define SCALE_CHANGE        0.2f
#define OPACITY_CHANGE      10.0f
#define ROTATE_CHANGE       45.0f
#define BYTE_LENGTH         4



class BWSlot;

//=============================================================
//=============================================================
//=============================================================
static void getStrArray(std::vector<std::string>* pStrArray, std::string str,std::string& strSep)
{
    while (str.length() > 0)
    {
        size_t firstPos = str.find_first_of(strSep.c_str());
        if(firstPos != std::string::npos)
        {
            std::string oneString = str.substr(0,firstPos);
            str = str.substr(firstPos+1,str.length());
            if(oneString.compare("-1") != 0)
            pStrArray->push_back(oneString);
        }
        else
        {
            if(str.compare("-1") != 0)
            pStrArray->push_back(str);
            return;
        }
    }
}



//=============================================================
//nUpper为-1表示不转换, 为1表示转为大写, 为0表示转为小写
static void stringReplace(std::string *str, std::string strOld, std::string strNew, int nUpper=-1)
{
    std::string::size_type pos = 0;
    std::string::size_type nLenOld = strOld.length();
    std::string::size_type nLenNew = strNew.length();
    
    pos = str->find(strOld, pos);
    while(pos != std::string::npos)
    {
        str->replace(pos, nLenOld, strNew);
        pos = str->find(strOld, pos+nLenNew);
    }
    
    if(nUpper == 0)
    {
        std::transform(str->begin(), str->end(), str->begin(), std::ptr_fun<int, int>(std::tolower));
    }
    else if(nUpper == 1)
    {
        std::transform(str->begin(), str->end(), str->begin(), std::ptr_fun<int, int>(std::toupper));

    }
}

//=============================================================
//=============================================================
//=============================================================
//=============================================================
enum eUILayerId
{
    eUILayerId_Unknown      = 0,
    eUILayerId_Home         = 1,
    eUILayerId_Combat       = 2,
    eUILayerId_Shop         = 3,
    eUILayerId_Login_test        = 4,
    eUILayerId_Edit         = 5,
    eUILayerId_Sel_Group    = 6,
    eUILayerId_Sel_Dun      = 7,
    eUILayerId_SelRole      = 8,
    eUILayerId_CreateRole   = 9,
    eUILayerId_ServerList   = 10,
    eUILayerId_Register     = 11,
    eUILayerId_Login        = 12,

};

//=============================================================
//=============================================================
enum selectCircleKind
{
    selectCircle_Card,
    selectCircle_Item,
};
//=============================================================
//=============================================================
enum eGAME_CMD_ID
{
    //layer
    eGAME_CMD_ID_Unknown            ,
    eGAME_CMD_ID_ShowHome           ,
    eGAME_CMD_ID_ShowSelectLevel    ,
    eGAME_CMD_ID_ShowCombat         ,
    eGAME_CMD_ID_ShowLogin_test     ,
    eGAME_CMD_ID_ShowShop           ,
    eGAME_CMD_ID_ShowEditHome       ,
    eGAME_CMD_ID_ShowSelGroup       ,
    eGAME_CMD_ID_ShowSelDungeon     ,
    eGAME_CMD_ID_ShowSelRole        ,
    eGAME_CMD_ID_ShowCreateRole     ,
    eGAME_CMD_ID_RegisterResult     ,
    eGAME_CMD_ID_LoginASResult      ,
    eGAME_CMD_ID_reqServeListResult ,
    eGAME_CMD_ID_ShowSelServe       ,
    eGAME_CMD_ID_ShowLogin          ,
    eGAME_CMD_ID_ShowRegister       ,
    eGAME_CMD_ID_SelServerResult    ,
    eGAME_CMD_ID_CreateRole         ,

};
//=============================================================
//=============================================================
enum eDirection
{
    eDirection_UNKNOW,
    eDirection_UP,
    eDirection_DOWN,
    eDirection_LEFT,
    eDirection_RIGHT,
    eDirection_CENTER
};

enum characterTypeEnum	//人物类型
{
	CTE_UNKNOWN = 0,
	CTE_ME		= 1,	//主角
	CTE_OTHER	= 2,	//其他人
	CTE_NPC		= 3,	//NPC
	CTE_ITEM	= 4,	//物品
	//CTE_DOOR	= 5,    //传送门
    //CTE_SEA     = 6,    //海水块
    CTE_BULLET_NPC  = 7,    //子弹NPC
    CTE_BULLET_ITEM = 8,    //子弹item
    
    CTE_COUNT
};

enum eEffectType
{
    eEffectType_Unknown         =0,
    eEffectType_Anim            =1,
    eEffectType_Part            =2,
};

enum LiveState
{
    eLiveState_Unknown = 0,
    eLiveState_Living = 1,
    eLiveState_Dead = 2,
    eLiveState_Empty = 3,
};
enum LoginState
{
    eLoginState_Unknown = 0,
    eLoginState_First = 1,
    
};

enum EUnitType
{
    EUnitType_Unknown       =0,
    EUnitType_Hero          =1,
    EUnitType_Item          =2,
    EUnitType_Monster       =3,
    EUnitType_EnemyBullet   =4,
    EUnitType_HeroBullet      =5,
    
};

//enum EAssign
//{
//    EAssign_updateBarHeroHP				= 0,	//英雄HP条
//    EAssign_updateBarHeroEP,					//英雄EP条
//    EAssign_updateBarBossHP,					//BossHP条
//    EAssign_coolDownTimeSkill1,
//    EAssign_coolDownTimeSkill2,
//    EAssign_coolDownTimeSkill3,
//};

enum LevelSceneType
{
    LST_NULL   = 0,
    LST_COMMON = 1,
    LST_GRASS  = 2,  //草地关
    LST_CAVE   = 3,  //山洞
    LST_CITY   = 4,
    LST_SNOW   = 5,
    
    
    //unused...
    LST_SEA    = 11,            //海洋关
    LST_MASK   = 12,            //全黑mask
    LST_MASK_SINGLE_COLOR = 13, //半透明mask
    LST_FIRE = 14,              //火山
    LST_ICE  = 15,              //冰山
    LST_INBODY = 16,            //身体肠胃
};

enum ESShopMoneyType
{
    ESShopMoneyType_Invalide=-1,
    ESShopMoneyType_Gold = 0,
    ESShopMoneyType_Diamond =1,
    ESShopMoneyType_BattleHonor=2,
};

enum ESLotteryType
{
    ESLotteryType_Unknown =0,
    ESLotteryType_FriendCard = 1,
    ESLotteryType_FriendItem = 2,
    ESLotteryType_DiamondCard = 3,
    ESLotteryType_DiamondItem = 4,
    
};


enum WayType
{
    WayType_normal = 0,
    WayType_inflection = 1,
    WayType_end  =2,
};


enum GuideType
{
    GuideType_LightOrDark     = 0,
    GuideType_Equip           = 1,
    GuideType_Battle          = 2,
};

enum BufferType
{
    eBufferType_UNKNOWN  = 0,
    eBufferType_Dingshen = 1,
};

enum BuffStateType
{
    eBuffStateType_Unknown = 0,
    eBuffStateType_Begin   = 1,
    eBuffStateType_End     = 2,
};
enum MoveStae
{
    MoveStae_Unknown =0,
    MoveStae_Left    =1,
    MoveStae_Right   =2,
    MoveStae_Stop    =3,
};

//召唤类型
enum ESummonType
{
    ESummonType_none	 	= 0,	//非召唤物
    ESummonType_magic   	= 1,	//魔法召唤物
    ESummonType_energy		= 2,	//能量召唤物
    ESummonType_neutral 	= 3,	//中立召唤物
};

//怪物类型
enum EMonsterType
{
    EMonsterType_none 		= 0,	//无
    EMonsterType_normal		= 1,	//普通
    EMonsterType_boss		= 2,	//BOSS
    EMonsterType_summon		= 3,	//召唤怪物, 通过召唤出现
    EMonsterType_tower		= 4,	//建筑类, 不能移动
    EMonsterType_totem		= 5,	//图腾, 召唤出的, 不能移动的
};

enum WeatherType
{
    WeatherType_unknown     =0,
    WeatherType_day         =1,//白天
    BWeatherType_night      =2,//夜晚
};
enum WinType
{
    WinType_unknown         =0,
    WinType_kill_all        =1,//
    WinType_kill_fort       =2,//
    WinType_keep_time       =3,//限时
    
};


enum EInfluenceType  //阵营
{
    EInfluenceType_unknown =0,
    
	EInfluenceType_belief  =1,//信仰
    EInfluenceType_honor   =2,//荣耀
    EInfluenceType_neutral =3,//中立
};

//Tom, 敌我识别
enum EPart
{
    EPart_none				= 0,	//无
    EPart_A,						//甲方,即英雄方, 与EPart_B敌对
    EPart_B,						//已方,即怪物方, 与EPart_A敌对
    EPart_C,						//中立方, 不与任何方敌对
};

//Tom, 性别
enum ESex
{
    ESex_male		= 1,	//男
    ESex_female,			//女
};

//Tom, 职业
enum EJobType
{
    EJobType_knight_unknown =0,
    EJobType_knight,	     	//骑士
    EJobType_pastor,			//牧师
    EJobType_sacrifice,			//祭祀
    EJobType_druids,			//德鲁伊
    EJobType_dungeon,			//恶魔人
    EJobType_magician,			//术士
    EJobType_deathKnight,		//死亡骑士
    EJobType_necromancer,		//亡灵巫师
    EJobType_berserker,			//狂战士
    EJobType_battleMage,		//战斗法师
    EJobType_soldier,			//战士
    EJobType_alchemist,			//炼金术士
    EJobType_tamer,				//驯兽师
    EJobType_witch,				//女巫
    EJobType_elementalist,		//元素使
    EJobType_seer,				//预言师
    EJobType_enchanter,			//妖术师
    EJobType_hellLord,			//地狱领主
};

//Tom, 攻击属性
enum EAttackNature
{
    EAttackNature_none	= 0, 	//无
    EAttackNature_physical,		//物理
	EAttackNature_magic,		//魔法
};

//Tom, 攻击类型
enum EAttackType
{
    EAttackType_none = 0,		//无
    EAttackType_near,			//近战
    EAttackType_far,			//远战
};

//Tom, 空间属性
enum ESpaceType
{
    ESpaceType_land	= 1, 		//对地
    ESpaceType_sky,				//对空
    ESpaceType_water,			//对水
    ESpaceType_landSky,			//地空
    ESpaceType_landWater,		//地水
    ESpaceType_landSkyWater,	//水陆空
};

enum ERaceType //种族
{
    ERaceType_unknown = 0,
    
    ERaceType_human   = 1,	//人类
    ERaceType_sprite  = 2,	//精灵
    ERaceType_evil    = 3,	//恶魔
    ERaceType_soul    = 4,	//亡灵
    ERaceType_orca    = 5,	//兽人
    ERaceType_titan   = 6,	//泰坦
    ERaceType_dark    = 7,	//黑暗
    ERaceType_abaddon = 8,	//地狱
    ERaceType_abyss   = 9,	//深渊
    ERaceType_element = 10,	//元素
    ERaceType_dragon   = 11,	//龙族
};

//魔法属性
enum EMagicNature
{
    EMagicNature_unknown	= 0,	//无
    EMagicNature_light  	= 1,	//光明
    EMagicNature_dark   	= 2,	// 黑暗
    EMagicNature_soil   	= 3,	//土
    EMagicNature_water  	= 4,	//水
    EMagicNature_fire   	= 5,	//火
    EMagicNature_air    	= 6,	//气
    EMagicNature_heart  	= 7,	//心智
    EMagicNature_power  	= 8,    //能量
    
};

enum EDefeadAction
{
    EDefeadAction_joinEnemy =1,  //加入敌人
    EDefeadAction_neutralEnemy=2, //中立
    EDefeadAction_disappear =3,  //消失
    
};
//Tom, ActionType
enum EActionType
{
    EActionType_stand 		= 0,	//站立  0
    EActionType_walk ,				//行走  1
    EActionType_walkSW,				//行走，空水 2
    EActionType_attack1,			//攻击1  3
    EActionType_attack2,			//攻击2  4
    EActionType_attack3,			//攻击3   5
    EActionType_beAttacked,			//受击    6
    EActionType_beAttackedSW,		//受击，空水 7
    EActionType_down,               //倒地 8
    EActionType_skill1,				//技能1  9
    EActionType_skill2,				//技能2   10
    EActionType_skill3,				//技能3   11
    EActionType_dead,				//死亡    12
};

//Tom, 技能类型
enum ESkillType
{
    ESkillType_normal       = 0,	//普通攻击
    ESkillType_normal_big   , 		//普通攻击大招
    ESkillType_active       , 		//主动
    ESkillType_passive      , 		//被动
    ESkillType_talent       , 		//天赋
    
};

//Tom, 技能槽
enum ESkillSlot
{
    ESkillSlot_0			= 100,	//槽1
    ESkillSlot_1,					//槽2
    ESkillSlot_2,					//槽3
    ESkillSlot_3,					//槽4
    ESkillSlot_4,					//槽5
};

//攻击时施法者所处的位置
enum EAttackPosType
{
    EAttackPosType_normal 	= 0,	//不变
    EAttackPosType_land     ,
    EAttackPosType_sky      ,
    EAttackPosType_water    ,
};

//劝降后的结果
enum EInduceResult
{
    EInduceResult_none			= 0,	//无结果
    EInduceResult_accedeEnemy,			//加入敌方
    EInduceResult_accedeAnother,		//加入另一方
    EInduceResult_vanish,				//消失于战场
};

enum EBuildingType
{
    EBuildingType_unknown =0,
    EBuildingType_hall,             //大厅 1
    EBuildingType_bastion,          //堡垒 2
    EBuildingType_buildGold1,       //金矿1  3
    EBuildingType_buildGold2,       //金矿2  4
    EBuildingType_buildGold3,       //金矿3  5
    EBuildingType_buildMagic,       //魔法井  6
    EBuildingType_goldWarehouse,    //金矿仓库 7
    EBuildingType_magicWarehouse,   //魔法仓库 8
    
    EBuildingType_tavern,           //酒馆 9
    
    EBuildingType_heroAltar,        //英雄祭坛 10
    EBuildingType_barrack,          //兵营 11
    EBuildingType_warfare,          //战争学院 12
    EBuildingType_gate,             //城门 13

    
//    EBuildingType_magicsociety,     //魔法公会 13
//    EBuildingType_tradeHouse,       //交易所 14
//    EBuildingType_gate,             //城门 15
//    EBuildingType_welfareHouse,         //福利院 16
//    EBuildingType_materialWareHouse,   //物资 17
//    EBuildingType_raceTotem,   //种族图腾  18
    
    //EBuildingType_miracle,   //神迹
    //EBuildingType_miracle,     //驯养圈
};

enum ActionType
{
    AT_UNKNOWN      =0,
    AT_SPAWN        =1,
    AT_SEQ          =2,
    AT_REPEAT       =3,
    AT_REPEATEVER   =4,
    
    AT_BEZIER       =5,
    AT_JUMP         =6,
    AT_SCALE        =7,
    AT_ROTATE       =8,
    AT_TINT         =9,
    AT_FADEIN       =10,
    AT_FADEOUT      =11,
    AT_FADETO       =12,
    AT_BLINK        =13,
    AT_SKEW         =14,
    AT_MOVE         =15,
    AT_DELAY        =16,
    ActionType_sine = 17,
};

//enum moveTypeEnum	//移动类型
//{
//	MTE_UNKNOWN	= 0,
//    MTE_STATIC_OBJECT = 4, //静止物体,用于石头母体
//	MTE_DRIP_DOWN	  = 5,//落下一次性
//	MTE_FUTURE	= 6
//};

enum levelTypeEnum		//关卡类型
{
	LTE_UNKNOWN	= 0,
	LTE_COMMON		= 1,//正常
	LTE_GYROSCOPE	= 2,//陀螺仪
	LTE_CYCLE		= 3,//无限关
	LTE_MASK		= 4,//蒙版关(黑暗点灯）
	LTE_FUTURE		= 5
};
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//=============================================================
//Tom, Tween's propterty
struct TProp
{
    TProp(){clear();}
    ~TProp(){};
    void clear()
    {
        x = FLOAT_NONE;
        y = FLOAT_NONE;
        z = FLOAT_NONE;
        alpha = FLOAT_NONE;
        scaleX = FLOAT_NONE;
        scaleY = FLOAT_NONE;
    }
    float					x;			//X坐标
    float					y;			//Y坐标
    float					z;			//Z坐标
    float					alpha;		//alpha
    float					scaleX;		//
    float					scaleY;		//
};


//战斗时捡的装备是本场临时装备， 加本场生命上限的， 或其它属性上限
//Tom, 角色属性
struct TRoleProp
{
    TRoleProp(){clear();}
    ~TRoleProp(){};
    void clear()
    {
        nLimitHP = -1;
        nLimitMP = -1;
        nLimitEP = -1;
        nLimitAttackValue = -1;
        nLimitDefenseValue = -1;
        nLimitDefenseMagicValue = -1;
        fLimitSpeed = -1;
        
        nHP = -1;
        nMP = -1;
        nEP = -1;
        nAttackValue = -1;
        nDefenseValue = -1;
        nDefenseMagicValue = -1;
        fSpeed = -1;
        
        nHitAreaR = -1;
        nHitAreaL = -1;
        nBeHitAreaR = -1;
        nBeHitAreaL = -1;
    }
    
    int							nLimitHP;
    int							nLimitMP;
    int							nLimitEP;
    int							nLimitAttackValue;
    int							nLimitDefenseValue;
    int							nLimitDefenseMagicValue;
    float						fLimitSpeed;
    
    int							nHP;
    int							nMP;
    int							nEP;
    int							nAttackValue;
    int							nDefenseValue;
    int							nDefenseMagicValue;
    
	float						fSpeed;
    
    int							nHitAreaR;		//攻击面前端, 即右边right,  相对角色坐标原点的值
    int							nHitAreaL;		//攻击面后端, 即左边left,  相对角色坐标原点的值
    int							nBeHitAreaR;	//受击面前端, 即右边Right,  相对角色坐标原点的值
    int							nBeHitAreaL;	//受击面后端, 即左边Left,  相对角色坐标原点的值
};

//=============================================================

static void getPropByStr(std::string strInput, TProp *pOut)
{
    if(!pOut)
    {
        return;
    }
    
    std::string str = strInput;
    std::string strSection = "";
    std::string strProp = "";
    std::string strValue = "";
    float fValue = FLOAT_NONE;
    
    //    std::string strSpace = " ";
    //    std::string strEmpty = "";
    bool bBreak = false;
    while(str.length() > 0)
    {
        size_t pos = str.find_first_of(",");
        if(pos != std::string::npos)
        {
            strSection = str.substr(0, pos);
            str = str.substr(pos+1, str.length());
        }
        else
        {
            strSection = str;
            bBreak = true;
        }
        
        if(strSection.length() > 2)
        {
            pos = strSection.find_first_of(":");
            if(pos != std::string::npos)
            {
                strProp = strSection.substr(0, pos);
                strValue = strSection.substr(pos+1, strSection.length());
                if(strProp.length() == 0 || strValue.length() == 0)
                {
                    continue;
                }
                
                stringReplace(&strProp, " ", "", 0);
                stringReplace(&strValue, " ", "");
                fValue = atof(strValue.c_str());
                
                log("Prop=%s \tValue=%s \tfloat=%f", strProp.c_str(), strValue.c_str(), fValue);
                
                if(strProp == "x")
                {
                    pOut->x = fValue;
                }
                else if(strProp == "y")
                {
                    pOut->y = fValue;
                }
                else if(strProp == "z")
                {
                    pOut->z = fValue;
                }
                else if(strProp == "alpha")
                {
                    pOut->alpha = fValue;
                }
                else if(strProp == "scalex")
                {
                    pOut->scaleX = fValue;
                }
                else if(strProp == "scaley")
                {
                    pOut->scaleY = fValue;
                }
                
            }
        }
        
        if(bBreak)
        {
            break;
        }
    }
}
//=============================================================
//=============================================================
struct LayerCommandDta
{
    Object*                 pTarget;
    SEL_CallFuncND          pFunc;
};
//=============================================================
//=============================================================
struct CommandData
{
	eGAME_CMD_ID                             nCommandId;
    std::vector<LayerCommandDta>             vLayerCommandData;
    std::vector<std::string>                 vCommandParmData;
};
//=============================================================
//=============================================================
struct UILayerData
{
    eUILayerId  eLayerId;
    int         nZOrder;
};


struct LanguageTabData
{
    int nTabId;
    const char*  pszKey;
    const char*  pszCnString;
};


struct EDiamondTabData
{
    EDiamondTabData();
    
    int             nId;
    const char*     strProductId;
    int             nDiamondCount;
    float           fPrice;
    const char*     pszIcon;
    
    EDiamondTabData& operator=(EDiamondTabData& data)
	{
        nId = data.nId;
        strProductId = data.strProductId;
        nDiamondCount = data.nDiamondCount;
        fPrice = data.fPrice;
        pszIcon = data.pszIcon;
		return *this;
	}
};
    
struct CharacterInfo
{
    CharacterInfo(){clear();}
    ~CharacterInfo(){}
    void clear()
    {
        eType = EUnitType_Unknown;
        nMapGid = 0;
        nTabId = -1;
        nUQID = -1;
    }
    EUnitType       eType;
    int             nMapGid;
    int             nTabId;
    int				nUQID;
};
struct CharacterTabData
{
    CharacterTabData()
    {
        nTabId  = 0;
        pszName = NULL;
        pszPngName= NULL;
        eEUnitType = EUnitType_Unknown;
        fSpeed  = 0;
    }
    int                     nTabId;
    const char*             pszName;
    const char*             pszPngName;
    EUnitType           eEUnitType;
    float                   fSpeed;
    
};


struct BuffTabData
{
    BuffTabData(){clear();}
    void clear()
    {
        nId   =0;
        pszName = NULL;
        eType =eBufferType_UNKNOWN;
        nParm1=-1;
        nParm2=-1;
        nParm3=-1;
        nParm4=-1;
        nParm5=-1;
    }
    int nId;
    const char* pszName;
    BufferType eType;
    float nParm1;
    float nParm2;
    float nParm3;
    float nParm4;
    float nParm5;
};
    

    
struct CamWaveData
{
    int nCamWaveOrderId;
    int nWaveTabId;
};
    
struct DungeonTabData
{
    int                 nId;
    const char*         pszName;
    int                 nMapSceneTabId;
    int                 nEnterPos;
    const char*         pszRaceType;
    
    float               fRaceadd;
    EMagicNature        eMagicNature;
    float               fMagicAdd;
    ESpaceType          eBattleType;
    WeatherType         eWeatherType;    
    int                 nDifficult;
    float               fDiffBuff;
    
    int                 nHeroLv;
    int                 nManorLv;
    int                 nNeedKey;
    int                 nCost;    //领导力
    int                 nNeedId;
    
    int                 nHaveFort;  //堡垒
    int                 nHabeCamp; //兵营
    int                 nHaveEnemyFort;
    int                 nHabeEnemyCamp;
    WinType             eWinType;
    float               fWinConfig;
    
    const char*         pszWavesOrder;
    const char*         pszWavesTabId;
    const char*         pszWavesRand;
    
    float               fWaveSpaceTime;
    int                 nChangeSpaceTime;
    int                 nBossId;
    int                 nPreBossWaveCount;
    int                 nAfterBossWaveCount;
    float               fDropPercent;
    int                 nDropBoxId;
    int                 nExp;
    int                 nGold;
    int                 nFood;
    const char*         pszElementType;
    const char*         pszElementCount;

};
    
struct DungeonTabDataDetail
{
    int                 nId;
    const char*         pszName;
    int                 nMapSceneTabId;
    int                 nEnterPos;  // group = nEnterPos/100;  index = nEnterPos/100
    
    std::vector<ERaceType> vRaceType; //种族
    
    float               fRaceadd;
    
    EMagicNature        eMagicNature; //魔法
    float               fMagicAdd;
    
    ESpaceType          eBattleType;  //战斗空间类型
    WeatherType         eWeatherType;
    
    int                 nDifficult;  //难度
    float               fDiffBuff;
    
    int                 nHeroLv; //英雄等级限制
    int                 nManorLv; //主城等级限制
    int                 nNeedKey; //体力
    int                 nCost;    //领导力
    int                 nNeedId;  //前置关卡
    int                 nHaveFort; //堡垒
    int                 nHabeCamp; //兵营
    
    int                 nHaveEnemyFort;
    int                 nHabeEnemyCamp;
    WinType             eWinType; //胜利类型
    float               fWinConfig;  //胜利条件
    
//    const char*         pszWavesOrder;  
//    const char*         pszWavesTabId;
//    const char*         pszWavesRand;
    std::vector<CamWaveData>     vConfigWave;
    std::vector<int>             vRandWave;

    
    float               fWaveSpaceTime;
    int                 nChangeSpaceTime;
    int                 nBossId;
    int                 nPreBossWaveCount;
    int                 nAfterBossWaveCount;
    float               fDropPercent;
    int                 nDropBoxId;
    int                 nExp;
    int                 nGold;
    int                 nFood;
    
//    const char*         pszElementType;
//    const char*         pszElementCount;
    
    std::vector<int>     vElementType;
    std::vector<int>     vElementCount;
    
    
    void setData(DungeonTabData* pCamData)
    {
        
        nId                 =pCamData->nId;
        pszName             =pCamData->pszName;
        nMapSceneTabId      =pCamData->nMapSceneTabId;
        nEnterPos           =pCamData->nEnterPos;
        
        fRaceadd            =pCamData->fRaceadd;
        eMagicNature    	=pCamData->eMagicNature;
        fMagicAdd           =pCamData->fMagicAdd;
        eBattleType         =pCamData->eBattleType;
        eWeatherType        =pCamData->eWeatherType;
        nDifficult          =pCamData->nDifficult;
        fDiffBuff           =pCamData->fDiffBuff;
        nHeroLv             =pCamData->nHeroLv;
        nManorLv            =pCamData->nManorLv;
        nNeedKey            =pCamData->nNeedKey;
        nCost               =pCamData->nCost;    //领导力限制

        nNeedId             =pCamData->nNeedId;
        nHaveFort           =pCamData->nHaveFort; //堡垒
        nHabeCamp           =pCamData->nHabeCamp; //兵营
        nHaveEnemyFort      =pCamData->nHaveEnemyFort;
        nHabeEnemyCamp      =pCamData->nHabeEnemyCamp;
        eWinType            =pCamData->eWinType;
        fWinConfig          =pCamData->fWinConfig;
        
//        const char*         pszWavesOrder;
//        const char*         pszWavesTabId;
//        const char*         pszWavesRand;
        
//        std::vector<CamWaveData>     vConfigWave;
//        std::vector<int>             vRandWave;
        
        fWaveSpaceTime      =pCamData->fWaveSpaceTime;
        nChangeSpaceTime    =pCamData->nChangeSpaceTime;
        nBossId             =pCamData->nBossId;
        nPreBossWaveCount   =pCamData->nPreBossWaveCount;
        nAfterBossWaveCount =pCamData->nAfterBossWaveCount;
        fDropPercent        =pCamData->fDropPercent;
        nDropBoxId          =pCamData->nDropBoxId;
        nExp                =pCamData->nExp;
        nGold               =pCamData->nGold;
        nFood               =pCamData->nFood;
        
//        const char*         pszElementType;
//        const char*         pszElementCount;
        
        std::string strSepString = "|";
        
        std::vector<std::string> vStrWaveOrder;
        getStrArray(&vStrWaveOrder,pCamData->pszWavesOrder,strSepString);
        
        std::vector<std::string> vStrWaveTabId;
        getStrArray(&vStrWaveTabId,pCamData->pszWavesTabId,strSepString);
        
        for(int i=0;i<vStrWaveOrder.size();i++)
        {
            CamWaveData waveData;
            int nWaveOrder = atoi(vStrWaveOrder[i].c_str());
            int nWaveTabId = atoi(vStrWaveTabId[i].c_str());
            waveData.nCamWaveOrderId = nWaveOrder;
            waveData.nWaveTabId = nWaveTabId;
            vConfigWave.push_back(waveData);
        }
        //waverand
        std::vector<std::string> vStrWaveRand;
        getStrArray(&vStrWaveRand,pCamData->pszWavesRand,strSepString);
        for(int i=0;i<vStrWaveRand.size();i++)
        {
            int nWaveTabId = atoi(vStrWaveRand[i].c_str());
            vRandWave.push_back(nWaveTabId);
        }
        
        //elementtype
        std::vector<std::string> vStrElementType;
        getStrArray(&vStrElementType,pCamData->pszElementType,strSepString);
        for(int i=0;i<vStrElementType.size();i++)
        {
            int ntypeId = atoi(vStrElementType[i].c_str());
            vElementType.push_back(ntypeId);
        }
        
        //elementcount
        std::vector<std::string> vStrElementCount;
        getStrArray(&vStrElementCount,pCamData->pszElementCount,strSepString);
        for(int i=0;i<vStrElementCount.size();i++)
        {
            int ntypeId = atoi(vStrElementCount[i].c_str());
            vElementCount.push_back(ntypeId);
        }
        
        //raceType
        std::vector<std::string> vStrRaceType;
        getStrArray(&vStrRaceType,pCamData->pszRaceType,strSepString);
        for(int i=0;i<vStrRaceType.size();i++)
        {
            int ntypeId = atoi(vStrRaceType[i].c_str());
            vRaceType.push_back((ERaceType)ntypeId);
        }
    }   
};
    
struct DungeonFlagData
{
    int                                     nFlagPos;
    std::map<int , DungeonTabDataDetail*>   mapStargDun;
    
};

struct HeroTabData
{
    int                 nId;
    const char*         pszIcon;
    int nSpeed;
};
    
    
struct MonsterTabData
{
    int             	nID;
    const char*     	pszIcon;
    int                 nInitHP;
    int                 nInitSpeed;
};


    
struct TActionData
{
    int					nID;			//唯一标识, 主键
    int					nClsNo;			//角色资源编号, 与THeroData中的nResID,多对1型的映射关系
    EActionType			eActType;		//动作类型, 走，跑
    const char*			pszResName;		//资源名称前缀
    int					nMaxFrame;		//帧数， 即最大帧号
    int					nPrimaryFrame;	//关键帧，开始特效，击中减血等, 如果特效表中没有对应的数据,表示是攻击帧, 没有特效数据表示从此帧开始特效
    int					nBallisticX;	//弹道X值
    int					nBallisticY;	//弹道Y值
    int					nNonBallisticX;	//非弹道X值
    int					nNonBallisticY;	//非弹道Y值
    int					nLoopBegin;		//循环开始帧
    int					nLoopEnd;		//循环结束帧
    int                 nLoops;			//循环次数 <0 忽略, 0表示无限循环, 1表示循环一次, 2循环两次,,,100表示循环100次
    float				fFrameRate;		//帧率
};



//struct GroupTabData
//{
//    int nId;
//    const char* pszMonsterId;
//    int nRandCount;
//    
//};

//struct GroupTabDataDetail
//{
//    int nId;
//    //const char* pszMonsterId;
//    std::vector<int> vMonsterId;
//    int nRandCount;
//    
//    void setData(GroupTabData* pTabData)
//    {
//        nId = pTabData->nId;
//        nRandCount = pTabData->nRandCount;
//        std::string strSepString = "|";
//        
//        std::vector<std::string> vStr;
//        getStrArray(&vStr,pTabData->pszMonsterId,strSepString);
//        for(int i=0;i<vStr.size();i++)
//        {
//            int nParm = atoi(vStr[i].c_str());
//            vMonsterId.push_back(nParm);
//        }
//    }
//};

struct MapTabData
{
    int             nId;
    int             nScreenCount;
    int             nLeftTop;
    int             nWayMin;
    int             nWayMax;
    
    
    const char*     pszFrontPng;
    const char*     pszFrontPngPosY;
    
    const char*     pszBattlePng;
    const char*     pszBattlePngPosY;
    
    const char*     pszMyTowerPng;
    int             nMyTowerX;
    int             nMyTowerY;
    
    const char*     pszEnemyTowerPng;
    int             nEnemyTowerX;
    int             nEnemyTowerY;
    
    
    const char*     pszFrontEffectId;
    const char*     pszFrontEffectPosX;
    const char*     pszFrontEffectPosY;
    
    const char*     pszAfterEffectId;
    const char*     pszAfterEffectPosX;
    const char*     pszAfterEffectPosY;
    
    const char*     pszMidBgPng;
    const char*     pszMidBgPngPosY;

    const char*     pszMidBgEffectId;
    const char*     pszMidBgEffectPosX;
    const char*     pszMidBgEffectPosY;

    
    const char*     pszFarBgPng;
    const char*     pszFarBgPngPngPosY;
    
    const char*     pszStaticBgPng;
    int             nStaticBgPngPngPosY;
    
    int             nEnemy3PosX;
    int             nEnemy3PosY;

};
    
struct MapTabDataDetail
{
    int             nId;
    int             nScreenCount;
    int             nLeftTop;
    int             nWayMin;
    int             nWayMax;
    
    
//    const char*     pszFrontPng;
//    const char*     pszFrontPngPosY;
    
    std::vector<std::string> pszFrontPng;
    std::vector<int> pszFrontPngPosY;
    
//    const char*     pszBattlePng;
//    const char*     pszBattlePngPosY;
    
    std::vector<std::string> pszBattlePng;
    std::vector<int> pszBattlePngPosY;
    
    const char*     pszMyTowerPng;
    int             nMyTowerX;
    int             nMyTowerY;
    
    const char*     pszEnemyTowerPng;
    int             nEnemyTowerX;
    int             nEnemyTowerY;
    
//    const char*     pszFrontEffectId;
//    const char*     pszFrontEffectPosX;
//    const char*     pszFrontEffectPosY;
    
    std::vector<int> pszFrontEffectId;    //人前
    std::vector<int> pszFrontEffectPosX;
    std::vector<int> pszFrontEffectPosY;
    
//    const char*     pszAfterEffectId;
//    const char*     pszAfterEffectPosX;
//    const char*     pszAfterEffectPosY;
    
    std::vector<int> pszAfterEffectId;
    std::vector<int> pszAfterEffectPosX;
    std::vector<int> pszAfterEffectPosY;
    
//    const char*     pszMidBgPng;
//    const char*     pszMidBgPngPosY;
    
    std::vector<std::string> pszMidBgPng;
    std::vector<int> pszMidBgPngPosY;
    
//    const char*     pszMidBgEffectId;
//    const char*     pszMidBgEffectPosX;
//    const char*     pszMidBgEffectPosY;
    
    std::vector<int> pszMidBgEffectId;
    std::vector<int> pszMidBgEffectPosX;
    std::vector<int> pszMidBgEffectPosY;
    
//    const char*     pszFarBgPng;
//    const char*     pszFarBgPngPngPosY;
    
    std::vector<std::string> pszFarBgPng;
    std::vector<int> pszFarBgPngPngPosY;
    
    const char*     pszStaticBgPng;
    int             nStaticBgPngPngPosY;
    int             nEnemy3PosX;
    int             nEnemy3PosY;
    
    void  setData(MapTabData* pMapData)
    {
          nId=pMapData->nId;
          nScreenCount=pMapData->nScreenCount;
        
          nLeftTop = pMapData->nLeftTop;
          nWayMin = pMapData->nWayMin;
          nWayMax = pMapData->nWayMax;
        
          pszMyTowerPng     = pMapData->pszMyTowerPng;
          nMyTowerX         = pMapData->nMyTowerX;
          nMyTowerY         = pMapData->nMyTowerY;
          pszEnemyTowerPng  = pMapData->pszEnemyTowerPng;
          nEnemyTowerX      = pMapData->nEnemyTowerX;
          nEnemyTowerY      = pMapData->nEnemyTowerY;
        
          pszStaticBgPng=pMapData->pszStaticBgPng;
          nStaticBgPngPngPosY=pMapData->nStaticBgPngPngPosY;
          nEnemy3PosX=pMapData->nEnemy3PosX;
          nEnemy3PosY=pMapData->nEnemy3PosY;
        
        std::string strSepString = "|";
        
        std::vector<std::string> vStr;
        
        vStr.clear();
        getStrArray(&pszFrontPng,pMapData->pszFrontPng,strSepString);
        
        vStr.clear();
        getStrArray(&vStr,pMapData->pszFrontPngPosY,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszFrontPngPosY.push_back(atoi(vStr[i].c_str()));
        }
        //battle
        vStr.clear();
        getStrArray(&pszBattlePng,pMapData->pszBattlePng,strSepString);
        
        vStr.clear();
        getStrArray(&vStr,pMapData->pszBattlePngPosY,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszBattlePngPosY.push_back(atoi(vStr[i].c_str()));
        }
        
        //effect
        vStr.clear();
        getStrArray(&vStr,pMapData->pszFrontEffectId,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszFrontEffectId.push_back(atoi(vStr[i].c_str()));
        }
        vStr.clear();
        getStrArray(&vStr,pMapData->pszFrontEffectPosX,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszFrontEffectPosX.push_back(atoi(vStr[i].c_str()));
        }
        vStr.clear();
        getStrArray(&vStr,pMapData->pszFrontEffectPosY,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszFrontEffectPosY.push_back(atoi(vStr[i].c_str()));
        }
        //effect after
        vStr.clear();
        getStrArray(&vStr,pMapData->pszAfterEffectId,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszAfterEffectId.push_back(atoi(vStr[i].c_str()));
        }
        vStr.clear();
        getStrArray(&vStr,pMapData->pszAfterEffectPosX,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszAfterEffectPosX.push_back(atoi(vStr[i].c_str()));
        }
        vStr.clear();
        getStrArray(&vStr,pMapData->pszAfterEffectPosY,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszAfterEffectPosY.push_back(atoi(vStr[i].c_str()));
        }
        //mid
        vStr.clear();
        getStrArray(&pszMidBgPng,pMapData->pszMidBgPng,strSepString);
        
        vStr.clear();
        getStrArray(&vStr,pMapData->pszMidBgPngPosY,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszMidBgPngPosY.push_back(atoi(vStr[i].c_str()));
        }
        //effect 
        vStr.clear();
        getStrArray(&vStr,pMapData->pszMidBgEffectId,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszMidBgEffectId.push_back(atoi(vStr[i].c_str()));
        }
        vStr.clear();
        getStrArray(&vStr,pMapData->pszMidBgEffectPosX,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszMidBgEffectPosX.push_back(atoi(vStr[i].c_str()));
        }
        vStr.clear();
        getStrArray(&vStr,pMapData->pszMidBgEffectPosY,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszMidBgEffectPosY.push_back(atoi(vStr[i].c_str()));
        }
        //far
        vStr.clear();
        getStrArray(&pszFarBgPng,pMapData->pszFarBgPng,strSepString);
        
        vStr.clear();
        getStrArray(&vStr,pMapData->pszFarBgPngPngPosY,strSepString);
        for(int i=0;i<vStr.size();i++)
        {
            pszFarBgPngPngPosY.push_back(atoi(vStr[i].c_str()));
        }
        
    }
};
    
    


//Tom, 目标类型
enum ETargetType
{
    ETargetType_self 				= 0,	//自己
    ETargetType_enemy_hero,					//敌方英雄
    ETargetType_enemy_nonHero,				//敌方非英雄
    ETargetType_enemy_all,					//敌方全体
    ETargetType_self_hero ,					//已方英雄
    ETargetType_self_nonHero,				//已方非英雄
    ETargetType_self_all,					//已方全体
    ETargetType_all,						//敌方全体
    ETargetType_magic_summon,				//魔法召唤物
    ETargetType_neutral_summon,				//中立召唤物
};

//Tom, 使用次数限制类型
enum ELimitedTimesType
{
    ELimitedTimesType_none    	= 0,	//无限制
    ELimitedTimesType_byDungeon,		//每关, 可使用次数
    ELimitedTimesType_byDay,			//每天, 可使用次数
};

//Tom, 花费类型, 消耗类型
enum ECostType
{
    ECostType_none 				= 0,	//无任何消耗
    ECostType_mp,						//魔法值
    ECostType_hp,						//生命值
    ECostType_ep,						//能量值
    ECostType_times,					//次数
};

//施法类型
enum EConjureType
{
    
    EConjureType_unknown 		= 0,	//未知
    EConjureType_auto,					//自动, 其实是手动点击技能后,自动发招
    EConjureType_manual,				//手动选择区域, 其实是手动点击技能后,再选择施放的区域
};
    

//中断类型
enum EBreakType
{
    EBreakType_none				= 0,	//无, 不被中断
    EBreakType_beAttacked,				//受击中断
    EBreakType_beSealed,           		//封印中断
    EBreakType_all,     				//受击封印中断
};

//生效类型
enum ETakeEffectType
{
    ETakeEffectType_immediately = 0,	//立即
    ETakeEffectType_afterConjure,		//施法之后
    
};

//身体状态
enum EBodyState
{
    EBodyState_none 		= 0,	//无
    EBodyState_fall,				//倒地
    EBodyState_fly,					//飞起,被击飞,被踢飞, 被打飞
    EBodyState_all,					//倒地击飞
};

//范围类型
enum EAreaType
{
    EAreaType_line 			= 0,	//线, 点的最远距离, 如弓箭
    EAreaType_circle,				//圆
    EAreaType_rectangle,			//矩形
};

//效果类型
enum EResultType
{
    EResultType_physical	= 0,	//物理
    EResultType_magic,				//魔法
};
    
    
enum EUserType
{
    EUserType_normal 		= 0,	//无限制
    EUserType_hero,					//英雄
    EUserType_troop,				//小兵
    EUserType_territory,			//领地
    EUserType_equipment,			//装备
};

struct TSkillData
{};
    


enum EResType
{
	EResType_Frame			= 1,		//序列帧动画
    EResType_particle,					//粒子
};
    
enum EReferPos
{
    EReferPos_host			= 0,		//角色自己
    EReferPos_enemy,					//敌方目标
    EReferPos_specify,					//指定区域
    EReferPos_center,					//屏幕中心
};
    
enum ECmd
{
    ECmd_fail				= 0,		//失败
    ECmd_success,						//成功
    ECmd_createEffect,					//创建Effect
    ECmd_createHero,					//创建Hero, 副本
    ECmd_retain,						//保持
    ECmd_remove,						//删除
    ECmd_callback,						//回调
    ECmd_position,						//位置
    ECmd_suspend,						//暂停,挂起
    ECmd_resume,						//唤醒
    ECmd_forward,						//朝向
    ECmd_action,						//动作信息
    ECmd_trick,							//招
    ECmd_tween,							//
};
    
struct EffectTabData
{
    int					nID;				//特效ID, 技能表中的nEffectResID将与此关联
    EResType			eResType;			//资源类型, 来源是序列帧或粒子特效
    const char*			pszStartName;		//发动特效资源名
    int					nStartMaxFrame;		//发动特效最大帧数
    int					nStartAttackFrame;	//发动特效攻击帧, <=0表示忽略
    int					nStartBeginFrame;	//发动特效循环开始帧
    int					nStartEndFrame;		//发动特效循环结束帧
    int					nStartLoops;		//发动特效循环数, <=0表示永久循环, 直到其它条件中止, 1表示不循环,仅运行一周天, 2,表示运行两周天...
};

struct AnimateData
{
    int                             nPrimaryFrame;		//关键帧
    int                             nMaxFrame;			//最大帧
    int                             nLoopBeginFrame;	//循环开始帧
    int                             nLoopEndFrame;		//循环结束帧
    int                             nLoops;				//循环数
    std::vector<std::string>        vFrameList;	//帧列表
};





struct account_t
{
    uuid_t uuid;
    uuid_string_t uuidstr;
    
    bool operator==(const account_t& account) const
    {
        return (!uuid_compare(this->uuid, account.uuid));
    }
    account_t& operator=(const account_t& account)
    {
        uuid_copy(this->uuid, account.uuid);
        uuid_unparse(this->uuid, uuidstr);
        return *this;
    }
    account_t& operator=(const uuid_t& uuid_in)
    {
        uuid_copy(uuid, uuid_in);
        uuid_unparse(this->uuid, uuidstr);
        return *this;
    }
    char* to_string(void)
    {
        uuid_unparse(uuid, uuidstr);
        return uuidstr;
    }
};


struct HeroData
{
    int nHeroTabId;
    int nLv;
    int nStar;
};

struct TroopData
{
    int     nTabId;
    int     nHpMax;
    int     nAttack;
    int     nLv;
    int     nStar;
};
struct SkillData
{
    int nSkillSlotPos;
    int nSkillTabId;
};

enum EBulletType
{
    EBulletType_move            =1,
    EBulletType_sine            =2,
    EBulletType_bezier          =3,
    EBulletType_circle          =4,
    EBulletType_circle_move     =5,

};
enum EBulletLineType
{
    EBulletLineType_xie_mut   =1,
    EBulletLineType_v_mut     =2,
};

struct BulletTabData
{
    int             nId;
    EBulletType     eType;
    EBulletLineType eLineType;
    const char*     pszIcon;
    int             nBeginDegree;
    int             nSpaceDegree;
    int             nBeginX; //x偏移
    int             nBeginY; //y偏移
    int             nSpaceX;  //x间隔
    int             nLineCount; //
    int             nLen;
    int             nRepeat;
    int             nSineA;
};


//=======================
//=======================
struct ActionIntervalData
{
    ActionIntervalData() {	clear(); }
    void clear()
    {
        actType = AT_UNKNOWN;
        order = 0;
        reverseFlag = 0;
        repeatCount = 1;
        repeatReverseFlag = 0;
    }
    int                 order;
    ActionType          actType;
    int                 reverseFlag;
    int                 repeatCount;
    int                 repeatReverseFlag;
};

struct bezierData : ActionIntervalData
{
    bezierData() {	clear(); }
    void clear()
    {
        duration = 0;
        height = 0;
        onePoint = ccp(0,0);
        twoPoint = ccp(0,0);
        endPoint = ccp(0,0);
    }
    
    float               duration;
    float               height;
    CCPoint             onePoint;
    CCPoint             twoPoint;
    CCPoint             endPoint;
    
};

struct jumpData:ActionIntervalData
{
    jumpData() {	clear(); }
    void clear()
    {
        duration = 0;
        height = 0;
        jumCount = 0;
        endPoint = ccp(0,0);
    }
    float               height;
    float               duration;
    CCPoint             endPoint;
    int                 jumCount;
};

struct scaleData:ActionIntervalData
{
    scaleData() {	clear(); }
    void clear()
    {
        duration = 0;
        sx = 0;
        sy = 0;
    }
    float               duration;
    float               sx;
    float               sy;
};

struct rotateData : ActionIntervalData
{
    rotateData() {	clear(); }
    void clear()
    {
        duration = 0;
        angle = 0;
    }
    
    float               duration;
    float               angle;
};

struct tintData : ActionIntervalData
{
    tintData() {	clear(); }
    void clear()
    {
        duration = 0;
        deltaRed = 0;
        deltaGreen = 0;
        deltaBlue = 0;
    }
    float               duration;
    float               deltaRed;
    float               deltaGreen;
    float               deltaBlue;
};

struct fadeInData : ActionIntervalData
{
    fadeInData() {	clear(); }
    void clear()
    {
        duration = 0;
    }
    float               duration;
};

struct fadeOutData : ActionIntervalData
{
    fadeOutData() {	clear(); }
    void clear()
    {
        duration = 0;
    }
    float               duration;
};

struct fadeToData : ActionIntervalData
{
    fadeToData() {	clear(); }
    void clear()
    {
        duration = 0;
        opacity = 0;
    }
    float               duration;
    float               opacity;
};

struct blinkData : ActionIntervalData
{
    blinkData() {	clear(); }
    void clear()
    {
        duration = 0;
        count = 0;
    }
    float               duration;
    int                 count;
};

struct skewData : ActionIntervalData
{
    skewData() {	clear(); }
    void clear()
    {
        duration = 0;
        deltaSkewX = 0;
        deltaSkewY = 0;
    }
    float               duration;
    float               deltaSkewX;
    float               deltaSkewY;
};

struct moveData : ActionIntervalData
{
    moveData() {	clear(); }
    void clear()
    {
        duration = 0;
        endPoint = ccp(0,0);
    }
    
    float               duration;
    CCPoint             endPoint;
};

struct delayTimeData : ActionIntervalData
{
    delayTimeData() {	clear(); }
    void clear()
    {
        duration = 0;
    }
    
    float               duration;
};

struct SineActionData : ActionIntervalData
{
    float fDur;
    CCPoint endPos;
    int   nA;
};

struct ActionData
{
    ActionData()
    {
        clear();
    }
    void clear() 
    { 
        actionArray.clear();
        actType=AT_UNKNOWN;
        repeatCount = 1;
        reverseFlag = 0;
        repeatReverseFlag = 0;
        pCallfuncND_actionEnd = 0;
    }
   
    
    ActionType          actType;  //seq or spawn
    int                 repeatCount;
    std::vector<ActionIntervalData>    actionArray;
    int                 reverseFlag;
    int                 repeatReverseFlag;
    
    bezierData  bezData;
    jumpData    jumData;
    scaleData   scaData;
    rotateData  rotData;
    tintData    tinData;
    fadeInData  fadInData;
    fadeOutData fadOutData;
    blinkData   bliData;
    skewData    skeData;
    moveData    movData;
    delayTimeData delayData;
    
    SineActionData sineActionData;
    
    SEL_CallFuncND pCallfuncND_actionEnd;
    
};
    
class BWTileSprite;
struct BulletData;
struct npcItemIndexStr;
    //struct NpcData;
    

   
    
struct LevelInfo
{
    LevelInfo(){ clear();}
    ~LevelInfo(){}
    
    void  clear()
    {
        titleId=0;
        agent_count=0;
        vAgents.clear();
        guide=0;
        timelimit=0;
        fog=0;
        fog_time_start=0;
        fog_time_end=0;
        fog_keep_time=0;
        //nDataMatch=0;
        difficulty=0;
        rain=0;
        snow=0;
    }
    
    //std::string levelname;
    std::string bgfile;
    std::string bgimage;
    //std::string bgmusic;
    
    LevelSceneType sceneType;
    bool bUnlimitLevel;
    int titleId;
    int agent_count;
    std::vector<int> vAgents;
    std::string fight_image;
    int guide; //引导关
    int difficulty; //难度级别
    float timelimit; //时间限制
    
    int fog;
    float fog_time_start;
    float fog_time_end;
    float fog_keep_time;
    
    int rain;
    int snow;
    
};
struct GuidePoint
{
    GuidePoint(){ bProccessed = false; }
    float x;
    int guide_template_id;
    bool bProccessed; //处理过标志
};

struct GuideEvent
{
    GuideEvent(){ bProccessed = false; }
    //GuideEventType type;
    int guide_template_id;
    bool bProccessed;
};

struct LevelGuide
{
    int levelid;
    std::vector<GuidePoint> vGuidePoint;
    std::vector<GuideEvent> vGuideEvent;
};

struct GuideTemplate
{
    int id;
    std::string file;
    std::string img;
};

struct LevelTile
{
//public:
//    LevelTile():
//    tid(0),
//    pos(Vertex2F(0,0)),
//    pPrev(NULL),
//    pNext(NULL) {}
//    ~LevelTile() {}
//    
//    LevelTile* prev(){ return pPrev; }
//    LevelTile* next(){ return pNext; }
//    
//    int tid;
//    Vertex2F pos;
//    BWtTpSTileSprite* pSprite;
//    
//    LevelTile* pPrev;
//    LevelTile* pNext;
};
struct LevelTileGroup
{
    void push_back(LevelTile& lt){ vTiles.push_back(lt); }
    void clear(){ vTiles.clear(); }
    
    int zorder;
    std::vector<LevelTile> vTiles;
};
struct RandomInfo
{
    RandomInfo()
    {
        fromx = 0;
        tox = 0;
        fromy = 0;
        toy = 0;
        minspace = 0;
        maxspace = 0;
        vSpriteId.clear();
    }
    int fromx;
    int tox;
    int fromy;
    int toy;
    int minspace;
    int maxspace;
    std::vector<int> vSpriteId;
};
    //------------------------------------------
struct LevelSprite
{
    int sid;
    Vertex2F pos;
    //BWTileSprite* pSprite;
};
struct LevelSpriteGroup
{
    void push_back(LevelSprite& ls){ vSprites.push_back(ls); }
    void clear(){ vSprites.clear(); }
    
    int zorder;
    Vertex2F speed;
    CCRect aabb;
    std::vector<LevelSprite> vSprites;
    
    //random
    RandomInfo randInfo;
};
typedef struct
{
    void clear(){ vLevelSpriteGroups.clear(); }
    void push_back(LevelSpriteGroup& lsg){ vLevelSpriteGroups.push_back(lsg); }
    
    std::vector<LevelSpriteGroup> vLevelSpriteGroups;
    
} BgLayerData, ForeLayerData;
//---------------------------------------

struct BulletData
{
    BulletData()
    {
        clear();
    }
    ~BulletData(){}
    void clear()
    {
        bulletId = -1;
        bulletType = CTE_UNKNOWN;
        bulletEndId = -1;
        
    }
    int   bulletId;
    characterTypeEnum   bulletType;
    int   bulletEndId;
    ActionData bulletActionData;
    
};
class BWCharacterNPC;

struct BornSlot
{
    BornSlot()
    {
        clear();
    }
    void clear()
    {
        slot_id = 0;
        slot_pos_x =0;
        slot_pos_y = 0;
        born_interval = 0;
        slot_rotate = 0;
        rotate_pos_x =0;
        rotate_pos_y = 0;
        fire_pos_x = 0;
        fire_pos_y = 0;
        slot_visible = 0;
        cur_interval_time = 0;
        pNpcSlot = NULL;
        
        bulData.clear();
    }
    int         slot_id;
    int         slot_visible;
    float       slot_rotate;
    float       slot_pos_x, slot_pos_y;
    float       born_interval;
    float       rotate_pos_x,rotate_pos_y;
    float       fire_pos_x,fire_pos_y;
    ActionData  slotActionData;
    BulletData  bulData;
    
    
    float cur_interval_time;
    BWCharacterNPC* pNpcSlot;
    
};

struct BulletSlotData
{
    BulletSlotData()
    {
        clear();
    }
    void clear()
    {
        vBornSlot.clear();
    }
    std::vector<BornSlot> vBornSlot;
};


struct npcItemIndexStr
{
    npcItemIndexStr()
    {
        nId = INVALID_ID;
    }
    int nId;
};

    
typedef struct
{
    void clear(){ tileGroup.clear(); }
    
    LevelTileGroup tileGroup;
    
} MainLayerData;


struct SlotData
{
    int         nId;
    int         nBulletId;
    CCPoint     pos;
    ActionData  actionData; //炮筒动作
    
    int         nBulletSpeed; //子弹移动速度
    float       fFireTime; //子弹发射持续时间
    float       fFreeTime; //子弹不发射持续时间
    float       fBulletSpaceTime; //子弹发射持续时间
    
};

struct NpcData
{
    NpcData()
    {
        rotate =0;
        triggerDistance =0;
        scale = 1;
        opacity = 255;
        zOrder = 0;
        actData.clear();
        index=0;
        flipX=0;
        flipY=0;
        nTabId= 0;
        
        mapSlotData.clear();
    }
    
    int         index; //key
    int         nTabId;
    CCPoint     pos;
    int         zOrder;
    int         flipX;
    int         flipY;
    float       rotate;
    float       scale;
    float       opacity;
    float       triggerDistance;
    
    ActionData  actData;
    
    std::map<int,SlotData>  mapSlotData;
};

struct ObjectDataTemplate
{
    ObjectDataTemplate():characterType(CTE_UNKNOWN){}
    
    characterTypeEnum characterType;
    NpcData npcItemData;
};

struct UnitData
{
    UnitData(){clear();}
    void clear()
    {
        nUuid = -1;
        eType = EUnitType_Unknown;
        nId = -1;
        pos = CCPoint(0,0);
    }
    int						nUuid;		//唯一标识
    EUnitType				eType;		//所属类, 如Hero, Monster,
    int						nId;		//所在类中的ID值, 如HeroID, MonsterID
    CCPoint                 pos;
    
    int                     nBulletIndex; //子弹索引
    
    ActionData              actionData;
    
    std::map<int,SlotData>  mapSlotData;
    BWSlot*                 pSlot;
};

struct LevelData
{
    int nLevelId;
    int nScreenCount;
    std::map<int,NpcData> mapLevelNpc;
};


    
#endif

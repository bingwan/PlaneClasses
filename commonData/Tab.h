
#ifndef _TAB_H_
#define _TAB_H_

#include "cocos2d.h"
//#include "CCPlatformMacros.h"

#include <string>
#include <vector>
#include <map>
#include <set>

enum EnumTabEleType
{
	T_Int = 0,
	T_Float,
	T_String
};

typedef union   //size = 4
{
	int             nValue;
	float           fValue;
	const char*     szValue;
}
TabElementData;


class  LoadTable
{
public:
	LoadTable();
	~LoadTable();
    
	void                        Clear();
    bool                        ReadFile(std::string strFileName);
    bool                        ReadEspeciaFile(std::string strFileName);
    int                         GetElementNum()  const { return m_vEnumTabEleType.size(); }
    const TabElementData*       GetLineDataById(int nId) const;
    
    const  std::map<int,TabElementData*>* getTabMap(){return &m_mapTab;}
    
    std::set<std::string>*      getSetString(){return m_setStringValue;}
    void                        setStringSet(std::set<std::string>* pSet){m_setStringValue = pSet;}
protected:
protected:
	std::map<int,TabElementData*>	m_mapTab;
    std::set<std::string>*          m_setStringValue;
    std::vector<EnumTabEleType>     m_vEnumTabEleType;

};

#endif
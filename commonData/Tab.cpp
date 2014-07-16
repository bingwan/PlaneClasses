
#include "Tab.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "StringMethod.h"
#include "CommonDef.h"
#define INVALIDFLAGPOS (2)
const static std::string strEmptyString = "";

//=============================================================
//=============================================================
LoadTable::LoadTable()
{
}
//=============================================================
//=============================================================
LoadTable::~LoadTable()
{
   Clear();
}
//=============================================================
//=============================================================
void LoadTable::Clear()
{
    std::map<int,TabElementData*>::const_iterator it = m_mapTab.begin();
    while(it != m_mapTab.end())
    {
        delete it->second;
        it++;
    } 
   	m_mapTab.clear();
    m_vEnumTabEleType.clear();
}

//=============================================================
//=============================================================
bool LoadTable::ReadFile(std::string strFileName)
{
    
   // CCLOG("strFile is %s",strFileName.c_str());
    FILE*  pFile;
    char*  line = NULL;
    size_t len = 0;
    ssize_t readLen;
    pFile = fopen(strFileName.c_str(), "r");
    if (pFile == NULL)
        return false;
    
    std::string	strLine;
    std::string strTemp;
	bool bReadKey = true;
    

    int nLineIndex = 0;
   // while ((readLen = getline(&line, &len, pFile)) != -1)
    while ((readLen = getdelim(&line, &len, '\r', pFile)) != -1)
    {
        strLine = line;
        //printf("line=%s//.....1....\n", strLine.c_str());
        
        std::string::size_type nnPos = strLine.find_first_of("\n");
        if(nnPos != std::string::npos)
        {
            strLine.replace(nnPos,1,"");
            //printf("line=%s....2.....%ld.\n", strLine.c_str(),strLine.length());
        }

        std::string::size_type nnPos2 = strLine.find_last_not_of("\n");
        if(nnPos2 != std::string::npos)
        {
            strLine.replace(nnPos2,1,"");
            //printf("line=%s//....3.....length=%ld.\n", strLine.c_str(),strLine.length());
        }
        
        if(nLineIndex == 0)
        {
            nLineIndex ++;
            continue;
        }
        
        if(strLine.length() == 0)
            continue;

		if (strLine.find("#") < INVALIDFLAGPOS)
			continue;
        nLineIndex ++;
        
        strLine.append("\t");
        //printf("line=%s//....4.....length=%ld.\n", strLine.c_str(),strLine.length());
        
        
		int   nCurStep                          = 0;
		size_t uCharOffset                      = 0;
		TabElementData* pElementDataArray       = NULL;
         const char *szLineChars                = strLine.c_str();
		if (false == bReadKey)
		{
			pElementDataArray = new TabElementData[m_vEnumTabEleType.size()];
			memset(pElementDataArray, 0, sizeof(TabElementData)*m_vEnumTabEleType.size());
			for (int i=0; i<(int)m_vEnumTabEleType.size(); ++i)
			{
				if (T_String == m_vEnumTabEleType[i])
				{
					(pElementDataArray+i)->szValue = strEmptyString.c_str();
				}
			}
		}
		// ignore lines that containing of a '\t'
		for (size_t i=0; i<strLine.size(); i++)
		{
            if (false == bReadKey && nCurStep >= (int)m_vEnumTabEleType.size())
                break;
            
            //0x09=\t 0x0d=\r 
            if(szLineChars[i] != '\t')
            {
                continue;
            }
            
            strTemp = strLine.substr(uCharOffset, i-uCharOffset);
            //printf("%s.\n",strTemp.c_str());
            
            if (bReadKey)
            {
                //log("strTemp=key=%s",strTemp.c_str());
                if ("INT" == strTemp || "int" == strTemp)
                {
                    m_vEnumTabEleType.push_back(T_Int);
                }
                else if ("FLOAT" == strTemp || "float" == strTemp)
                {
                    m_vEnumTabEleType.push_back(T_Float);
                }
                else if ("STRING" == strTemp || "string" == strTemp || "STRING_INT" == strTemp)
                {
                    m_vEnumTabEleType.push_back(T_String);
                }
            }
            else
            {
                if (false == strTemp.empty())
                {
                    //log("strTemp=%s",strTemp.c_str());
                    
                    if (T_Int == m_vEnumTabEleType[nCurStep])
                    {
                        pElementDataArray[nCurStep].nValue = atoi(strTemp.c_str());
                    }
                    else if (T_Float == m_vEnumTabEleType[nCurStep])
                    {
                        pElementDataArray[nCurStep].fValue = (float)atof(strTemp.c_str());
                    }
                    else if (T_String == m_vEnumTabEleType[nCurStep])
                    {
                        std::string utf8Str = strTemp;
                        if(TAB_READ_TO_UTF8)
                        {
                            StringMethod::share()->mbcs_to_utf8String(strTemp, utf8Str);
                            //log("utf8Str=%s",utf8Str.c_str());
                        }
                        std::set<std::string>::iterator it = m_setStringValue->find(utf8Str);
                        if (it != m_setStringValue->end())
                        {
                            (pElementDataArray+nCurStep)->szValue = (*it).c_str();
                        }
                        else
                        {
                            m_setStringValue->insert(utf8Str);
                            it = m_setStringValue->find(utf8Str);
                            (pElementDataArray+nCurStep)->szValue = (*it).c_str();
                        }
                    }
                }
            }
            nCurStep++;
            uCharOffset = i + 1;
		}
		if (pElementDataArray)
		{
            m_mapTab.insert(std::make_pair(pElementDataArray[0].nValue, pElementDataArray));
            //printf("file :%s  m_mapTab.insert=%d\n",strFileName.c_str(), pElementDataArray[0].nValue);
		}
		bReadKey = false;
    }
    free(line);
    if(pFile)
    {
        fclose(pFile);
    }
    return true;
}
//=============================================================
//=============================================================
const TabElementData* LoadTable::GetLineDataById(int nId) const
{
    std::map<int,TabElementData*>::const_iterator it = m_mapTab.find(nId);
    if(it != m_mapTab.end())
    {
        return it->second;
    }
    return NULL;
}
//=============================================================
//=============================================================


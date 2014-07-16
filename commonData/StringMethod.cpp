



#include "StringMethod.h"
#include "iconv.h"
#include "CommonDef.h"




static char szGBK[]  = "GBK";
static char szUtf8[] = "utf-8";
static StringMethod* g_MethodImpl = NULL;

//=============================================================
//=============================================================
StringMethod* StringMethod::share()
{
	if (g_MethodImpl == NULL)
	{
		g_MethodImpl = new StringMethod();
	}
	return g_MethodImpl;
}
//=============================================================
//=============================================================
void StringMethod::purgeImpl()
{
	CC_SAFE_RELEASE_NULL(g_MethodImpl);
}
//=============================================================
//=============================================================
StringMethod::StringMethod()
{
    m_pMem_utf8 = NULL;
    m_pMem_mbcs = NULL;
    m_nSize_utf8 = 0;
    m_nSize_mbcs = 0;
}

//=============================================================
//=============================================================
StringMethod::~StringMethod()
{
	CC_SAFE_DELETE_ARRAY(m_pMem_utf8);
	CC_SAFE_DELETE_ARRAY(m_pMem_mbcs);
}

//=============================================================
//=============================================================
int StringMethod::code_convert(char* from_charset,  char* to_charset,  char* inbuf,  size_t inlen,  char* outbuf,  size_t outlen)
{    
	iconv_t cd;

	char **pin  = &inbuf; 
	char **pout = &outbuf; 

	cd = iconv_open(to_charset, from_charset); 
	if (cd == 0)
	{
		return -1; 
	}

	memset(outbuf, 0, outlen); 
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1 )  
	{
		return -1; 
	}

	iconv_close(cd); 
	return 0; 
}

//=============================================================
//=============================================================
void StringMethod::mbcs_to_utf8(const std::string& strIn, std::string& strOut)
{
    strOut = strIn;
//	if (strIn.empty())
//		return;
//
//	int nUtf8size = strIn.size() * 3 + 1;
//	if (NULL == m_pMem_utf8 || m_nSize_utf8 < nUtf8size)
//	{
//		CC_SAFE_DELETE_ARRAY(m_pMem_utf8);
//		m_nSize_utf8 = nUtf8size;
//		m_pMem_utf8 = new char[m_nSize_utf8];
//	}
//    
//    int nMbcsSize = strIn.size() + 1;
//    if (NULL == m_pMem_mbcs || m_nSize_mbcs < nMbcsSize)
//	{
//		CC_SAFE_DELETE_ARRAY(m_pMem_mbcs);        
//		m_nSize_mbcs = nMbcsSize;
//		m_pMem_mbcs = new char[m_nSize_mbcs];
//	}
//
//	memset(m_pMem_utf8, 0, sizeof(char)*m_nSize_utf8);    
//    memset(m_pMem_mbcs, 0, sizeof(char)*m_nSize_mbcs);
//    memcpy(m_pMem_mbcs, strIn.c_str(), strIn.size());
//    
//	code_convert(szGBK, szUtf8, m_pMem_mbcs, m_nSize_mbcs, m_pMem_utf8, m_nSize_utf8);
//
//	strOut = m_pMem_utf8;
}

void StringMethod::mbcs_to_utf8String(const std::string& strIn, std::string& strOut)
{
	if (strIn.empty())
		return;
    
	int nUtf8size = strIn.size() * 3 + 1;
	if (NULL == m_pMem_utf8 || m_nSize_utf8 < nUtf8size)
	{
		CC_SAFE_DELETE_ARRAY(m_pMem_utf8);
		m_nSize_utf8 = nUtf8size;
		m_pMem_utf8 = new char[m_nSize_utf8];
	}
    
    int nMbcsSize = strIn.size() + 1;
    if (NULL == m_pMem_mbcs || m_nSize_mbcs < nMbcsSize)
	{
		CC_SAFE_DELETE_ARRAY(m_pMem_mbcs);
		m_nSize_mbcs = nMbcsSize;
		m_pMem_mbcs = new char[m_nSize_mbcs];
	}
    
	memset(m_pMem_utf8, 0, sizeof(char)*m_nSize_utf8);
    memset(m_pMem_mbcs, 0, sizeof(char)*m_nSize_mbcs);
    memcpy(m_pMem_mbcs, strIn.c_str(), strIn.size());
    
	code_convert(szGBK, szUtf8, m_pMem_mbcs, m_nSize_mbcs, m_pMem_utf8, m_nSize_utf8);
    
	strOut = m_pMem_utf8;
}
//=============================================================
//=============================================================
void StringMethod::utf8_to_mbcs(const std::string& strIn, std::string& strOut)
{
	if (strIn.empty())
		return;

	int nMbcsSize = strIn.size() + 1;
	if (NULL == m_pMem_mbcs || m_nSize_mbcs < nMbcsSize)
	{
		CC_SAFE_DELETE_ARRAY(m_pMem_mbcs);
		m_nSize_mbcs = nMbcsSize;
		m_pMem_mbcs = new char[m_nSize_mbcs];
	}
    
    int nUtf8Size = strIn.size() + 1;
    if (NULL == m_pMem_utf8 || m_nSize_utf8 < nUtf8Size)
	{
		CC_SAFE_DELETE_ARRAY(m_pMem_utf8);        
		m_nSize_utf8 = nUtf8Size;
		m_pMem_utf8 = new char[m_nSize_utf8];
	}

	memset(m_pMem_mbcs, 0, sizeof(char)*m_nSize_mbcs);    
    memset(m_pMem_utf8, 0, sizeof(char)*m_nSize_utf8);
    memcpy(m_pMem_utf8, strIn.c_str(), strIn.size());

	code_convert(szUtf8, szGBK, m_pMem_utf8, m_nSize_utf8, m_pMem_mbcs, m_nSize_mbcs);

	strOut = m_pMem_mbcs;
}
//=============================================================
//=============================================================
int StringMethod::getWideCountFromUtf8(const char* szUtf8)
{
	int nWideCount = 0;
	int nBit = 1;

	char ch = 0;
	int nLen = strlen(szUtf8);

	for (int i=0; i<nLen; ++i)
	{
		ch = szUtf8[i];
		if (0 == ch)
			break;

		if (0x80 == (0xC0 & ch))
		{
			++nBit;
			if (nBit <= 2)
			{
				++nWideCount;
			}
		}
		else
		{
			nBit = 1;
			++nWideCount;
		}
	}
	return nWideCount;
}
//=============================================================
//=============================================================
void StringMethod::splitString(const std::string& strIn, std::vector<std::string>& vOut, char cCut1, char cCut2)
{
//	std::string strTemp;
//
//	int nPos = 0;
//	for (int i=0; i<(int)strIn.size(); ++i)
//	{
//		if (strIn[i] == cCut1 || 
//		   (strIn[i] == cCut2 && cCut2 != -1))
//		{
//			strTemp.clear();
//			strTemp.append(strIn, nPos, i-nPos);
//			vOut.push_back(strTemp);
//
//			nPos = i+1;
//		}
//		else if (i == (int)strIn.size()-1)
//		{
//			strTemp.clear();
//			strTemp.append(strIn, nPos, i-nPos+1);
//			vOut.push_back(strTemp);
//		}
//	}
}
//=============================================================
//=============================================================
cocos2d::Color3B StringMethod::colorFromString(const std::string& multiString)
{
	cocos2d::Color3B cRet = cocos2d::ccc3(255, 255, 255);
	
    std::string tempStr = multiString.substr(0,2);
    long tempInt = strtol(tempStr.c_str(), NULL, 16);
    cRet.r = (unsigned char)tempInt;
    
    tempStr = multiString.substr(0+2,2);
    tempInt = strtol(tempStr.c_str(), NULL, 16);
    cRet.g = (unsigned char)tempInt;
    
    tempStr = multiString.substr(0+4,2);
    tempInt = strtol(tempStr.c_str(), NULL, 16);
    cRet.b = (unsigned char)tempInt;
	
	return cRet;
}
//=============================================================
//=============================================================


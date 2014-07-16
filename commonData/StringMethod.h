
#ifndef _METHOD_H__
#define _METHOD_H__

#include "cocos2d.h"

USING_NS_CC;

class  StringMethod : public Object
{
public:
	StringMethod();
	~StringMethod();

	static StringMethod* share();
	static void	purgeImpl();
	 void				mbcs_to_utf8(const std::string& strIn, std::string& strOut);
	 void				utf8_to_mbcs(const std::string& strIn, std::string& strOut);
	 int				getWideCountFromUtf8(const char* szUtf8);
	 void				splitString(const std::string& strIn, std::vector<std::string>& vOut, char cCut1, char cCut2=-1);
     Color3B          colorFromString(const std::string& multiString);
    int                 code_convert(char* from_charset, char* to_charset, char* inbuf, size_t inlen, char* outbuf, size_t outlen);
    void                mbcs_to_utf8String(const std::string& strIn, std::string& strOut);
protected:
	 char*      m_pMem_utf8;
	 int		m_nSize_utf8;
	 char*      m_pMem_mbcs;
	 int		m_nSize_mbcs;
};
#endif
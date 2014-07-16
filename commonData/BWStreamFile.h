

#ifndef __BWStreamFile_H__
#define __BWStreamFile_H__

#include "platform/CCFileUtils.h"

#define COMMON_STRING_SIZE  256
#define LONG_STRING_SIZE    1024*5

class BWStreamFile 
{
public:
	enum FileOpeEnum
	{
		FOE_UNKNOWN = 0,
		FOE_WRITE	= 1,
		FOE_READ	= 2,
		FOE_FUTURE	= 3
	};
	enum FileFormatEnum
	{
		FFE_UNKNOWN = 0,
		FFE_BINARY	= 1,
		FFE_TEXT	= 2,
		FFE_XML		= 3,
		FFE_FUTURE	= 4
	};

	
	BWStreamFile();
	virtual ~BWStreamFile();
    
    static BWStreamFile* share();
	
	bool initStreamPath(const char* pDocumentsPathName,const char* pResourcesPathName);
	
	bool OpenDocumentsStreamFile(const char* pFileName,FileOpeEnum operation,FileFormatEnum format);
	bool OpenCacheStreamFile(const char* pFileName,FileOpeEnum operation,FileFormatEnum format);
	bool OpenTmpStreamFile(const char* pFileName,FileOpeEnum operation,FileFormatEnum format);
	
	bool CloseStreamFile();
	

	int			GetOpeFlag() const;	
	int			GetFormatFlag() const;
	FILE*		GetFileHandle() const; 
	const char* GetOpenFileName() const;

	
	bool		stream(void* buffer,size_t size,size_t count);	
	bool		stream(void* buffer,size_t size);	
	bool		stream(const char* format,void* data);	
	bool		stream(const char* format,int data);
	bool		stream(const char* format,float data);
    
    const char* GetDocumentsPath();
    const char* GetResourcesPath();
    
    const char* GetTmpPath(){ return m_TmpPathName; }
    const char* GetCachePath(){ return m_CachePathName; }
	const char*	GetFullPathFileName(const char* pFileName);
	
protected:
	bool		OpenStreamFile(const char* pFileName,const char* pFullPathFileName);

private:
	FileOpeEnum		m_OpeFlag;			
	FileFormatEnum	m_FormatFlag;		
	FILE*			m_File;				
	char			m_OpenFileName[COMMON_STRING_SIZE];
	char			m_DocumentsPathName[COMMON_STRING_SIZE];
	char			m_CachePathName[COMMON_STRING_SIZE];
	char			m_TmpPathName[COMMON_STRING_SIZE];
	char			m_ResourcesPathName[COMMON_STRING_SIZE];
	
};

//bool file_exist(const char* filename);


#endif //__BWStreamFile_H__


#include "BWStreamFile.h"
#include "string.h"
#include <string>

//bool file_exist(const char* filename)
//{
//    const char *pszPath = cocos2d::CCFileUtils::sharedFileUtils()->FullPathFileName(filename);
//    FILE* fp = fopen(pszPath, "rb");
//    if(fp)
//    {
//        fclose(fp);
//        return true;
//    }
//    return false;
//}


BWStreamFile::BWStreamFile():
m_OpeFlag(FOE_UNKNOWN),
m_FormatFlag(FFE_UNKNOWN),
m_File(NULL)
{ 
	memset(m_OpenFileName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_DocumentsPathName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_CachePathName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_TmpPathName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_ResourcesPathName,0,COMMON_STRING_SIZE*sizeof(char));
}
BWStreamFile::~BWStreamFile()
{ 
	m_OpeFlag=FOE_UNKNOWN;
	m_FormatFlag=FFE_UNKNOWN;
	if(m_File)
	{
		fclose(m_File);
		m_File=NULL;
	}
	memset(m_OpenFileName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_DocumentsPathName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_CachePathName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_TmpPathName,0,COMMON_STRING_SIZE*sizeof(char));
	memset(m_ResourcesPathName,0,COMMON_STRING_SIZE*sizeof(char));

}
static BWStreamFile* s_pStreamFile = NULL;
BWStreamFile* BWStreamFile::share()
{
    if(s_pStreamFile == NULL)
    {
        s_pStreamFile = new BWStreamFile();
    }
    return s_pStreamFile;
    
}

bool BWStreamFile::initStreamPath(const char* pDocumentsPathName,const char* pResourcesPathName)
{
	if (pDocumentsPathName) 
	{
		//---Documents----9 
		int pathLen=strlen(pDocumentsPathName) > (COMMON_STRING_SIZE-1) ? (COMMON_STRING_SIZE-1) : strlen(pDocumentsPathName);		
		strncpy(m_DocumentsPathName,pDocumentsPathName,pathLen);
		m_DocumentsPathName[pathLen+1]='\0';
		//---Library/Caches---14
		pathLen = (strlen(pDocumentsPathName)- 9 ) > (COMMON_STRING_SIZE - 1 - 14) ? (COMMON_STRING_SIZE - 1 - 14) : (strlen(pDocumentsPathName)- 9 ) ;
		strncpy(m_CachePathName,pDocumentsPathName,pathLen);
		strcat(m_CachePathName,"Library/Caches");
		m_CachePathName[pathLen+1+14]='\0';
		//---tmp---3
		pathLen = (strlen(pDocumentsPathName)- 9 ) > (COMMON_STRING_SIZE - 1 - 3) ? (COMMON_STRING_SIZE - 1 - 3) : (strlen(pDocumentsPathName)- 9 ) ;
		strncpy(m_TmpPathName,pDocumentsPathName,pathLen);
		strcat(m_TmpPathName,"tmp");
		m_CachePathName[pathLen+1+3]='\0';
	}
	if (pResourcesPathName) 
	{
		int pathLen=strlen(pResourcesPathName) > (COMMON_STRING_SIZE-1) ? (COMMON_STRING_SIZE-1) : strlen(pResourcesPathName);		
		strncpy(m_ResourcesPathName,pResourcesPathName,pathLen);
		m_ResourcesPathName[pathLen+1]='\0';
	}
	return true;	
}
const char*	BWStreamFile::GetFullPathFileName(const char* pFileName)
{
    static char fullpath[LONG_STRING_SIZE] = {0,0};
    
	//documents
	std::string DocumentsPath = m_DocumentsPathName;
    DocumentsPath.append("/");
    DocumentsPath.append(pFileName);
	FILE* pFile = fopen(DocumentsPath.c_str(),"rb");
	if (pFile)
	{
		fclose(pFile);
        strncpy(fullpath, DocumentsPath.c_str(), LONG_STRING_SIZE);
		return fullpath;
	}
	//Cache
	std::string CachePath = m_CachePathName;
    CachePath.append("/");
    CachePath.append(pFileName);
	pFile = fopen(CachePath.c_str(),"rb");
	if (pFile)
	{
		fclose(pFile);
        strncpy(fullpath, CachePath.c_str(), LONG_STRING_SIZE);
		return fullpath;
	}
	//tmp
	std::string TmpPath = m_TmpPathName;
    TmpPath.append("/");
    TmpPath.append(pFileName);
	pFile = fopen(TmpPath.c_str(),"rb");
	if (pFile)
	{
		fclose(pFile);
        strncpy(fullpath, TmpPath.c_str(), LONG_STRING_SIZE);
		return fullpath;
	}
	//Resources
	std::string ResourcesPath = m_ResourcesPathName;
	ResourcesPath.append("/");
    ResourcesPath.append(pFileName);	
	pFile = fopen(ResourcesPath.c_str(),"rb");
	if (pFile)
	{
		fclose(pFile);
        strncpy(fullpath, ResourcesPath.c_str(), LONG_STRING_SIZE);
		return fullpath;
	}
	return NULL;	
}
bool BWStreamFile::OpenDocumentsStreamFile(const char* pFileName,FileOpeEnum operation,FileFormatEnum format)
{
	if (!m_File)
	{
		m_OpeFlag = operation;
		m_FormatFlag = format;
		int fileNameLen=strlen(pFileName) > (COMMON_STRING_SIZE-1) ? (COMMON_STRING_SIZE-1) : strlen(pFileName);	
		char FullPathFileName[COMMON_STRING_SIZE*2] = {0,0};
		strncpy(FullPathFileName,m_DocumentsPathName,strlen(m_DocumentsPathName));
		strncat(FullPathFileName,pFileName,fileNameLen);
		return OpenStreamFile(pFileName,FullPathFileName);
	}
	else
	{
#ifdef DEBUG
#endif
		return false;
	}
}
bool BWStreamFile::OpenCacheStreamFile(const char* pFileName,FileOpeEnum operation,FileFormatEnum format)
{
	if (!m_File)
	{
		m_OpeFlag = operation;
		m_FormatFlag = format;
		int fileNameLen=strlen(pFileName) > (COMMON_STRING_SIZE-1) ? (COMMON_STRING_SIZE-1) : strlen(pFileName);	
		char FullPathFileName[COMMON_STRING_SIZE*2] = {0,0};
		strncpy(FullPathFileName,m_CachePathName,strlen(m_CachePathName));
		strncat(FullPathFileName,pFileName,fileNameLen);
		return OpenStreamFile(pFileName,FullPathFileName);
	}
	else
	{
#ifdef DEBUG
#endif
		return false;
	}
}
bool BWStreamFile::OpenTmpStreamFile(const char* pFileName,FileOpeEnum operation,FileFormatEnum format)
{
	if (!m_File)
	{
		m_OpeFlag = operation;
		m_FormatFlag = format;
		int fileNameLen=strlen(pFileName) > (COMMON_STRING_SIZE-1) ? (COMMON_STRING_SIZE-1) : strlen(pFileName);	
		char FullPathFileName[COMMON_STRING_SIZE*2] = {0,0};
		strncpy(FullPathFileName,m_TmpPathName,strlen(m_TmpPathName));
		strncat(FullPathFileName,pFileName,fileNameLen);
		return OpenStreamFile(pFileName,FullPathFileName);
	}
	else
	{
#ifdef DEBUG
#endif
		return false;
	}
}
bool BWStreamFile::OpenStreamFile(const char* pFileName,const char* pFullPathFileName)
{
	switch(m_OpeFlag)
	{
		case FOE_WRITE:
			switch(m_FormatFlag)
			{
			case FFE_BINARY:
				if ((m_File = fopen(pFullPathFileName, "wb")) == NULL)
				{
					#ifdef DEBUG
					#endif
					return false;
				}
				break;
			case FFE_TEXT:
				if ((m_File = fopen(pFullPathFileName, "wt")) == NULL)
				{
					#ifdef DEBUG
					#endif
					return false;
				}
				break;
			default:
				#ifdef DEBUG
				#endif
				return false;
			}
			break;
		case FOE_READ:
			switch(m_FormatFlag)
			{
			case FFE_BINARY:
				if ((m_File = fopen(pFullPathFileName, "rb")) == NULL)
				{
					#ifdef DEBUG
					#endif
					return false;
				}
				break;
			case FFE_TEXT:
				if ((m_File = fopen(pFullPathFileName, "rt")) == NULL)
				{
					#ifdef DEBUG
					#endif
					return false;
				}
				break;
			default:
				#ifdef _DEBUG
				#endif
				return false;
			}
			break;
		default:
			#ifdef DEBUG
			#endif   
			return false;
	}
	int fileNameLen=strlen(pFileName) > (COMMON_STRING_SIZE-1) ? (COMMON_STRING_SIZE-1) : strlen(pFileName);
	strncpy(m_OpenFileName,pFileName,fileNameLen);
	m_OpenFileName[fileNameLen+1]='\0';
	return true;
}
bool BWStreamFile::CloseStreamFile()
{ 
	if (m_File) 
	{
		fclose(m_File);
		m_File=NULL;
	}
	memset(m_OpenFileName,0,256*sizeof(char));
	return true;
}

int  BWStreamFile::GetOpeFlag() const 
{
	return m_OpeFlag;
}
int  BWStreamFile::GetFormatFlag() const 
{ 
	return m_FormatFlag;
}
FILE* BWStreamFile::GetFileHandle() const
{
	return m_File;
}
const char* BWStreamFile::GetOpenFileName() const
{
	return m_OpenFileName;
}
bool BWStreamFile::stream(void* buffer,size_t size,size_t count)
{
	return stream(buffer,size*count);	
}
bool BWStreamFile::stream(void* buffer,size_t size)
{
	if(m_FormatFlag!=FFE_BINARY)
	{
		#ifdef DEBUG
		#endif
		return false;
	}
	if(m_File == NULL)
	{
		#ifdef DEBUG
		#endif
		return false;
	}
	switch(m_OpeFlag)
	{
	case FOE_WRITE:
		{
			if (fwrite(buffer, 1, size, m_File) < size)
			{
				#ifdef DEBUG
				#endif
				CloseStreamFile();
				return false;
			}
			return true;
		}				
	case FOE_READ:	
		{
			if (fread(buffer,1,size,m_File) < size)
			{
				#ifdef DEBUG
				#endif
				CloseStreamFile();
				return false;        
			}
			return true;
		}
	default:
		{
			#ifdef DEBUG
			#endif
			return false;
		}
	}
}
bool BWStreamFile::stream(const char* format,void* data)
{
	if (m_FormatFlag!=FFE_TEXT)
	{
		#ifdef DEBUG
		#endif
		return false;
	}
	if(m_File == NULL)
	{
		#ifdef DEBUG
		#endif
		return false;
	}
	switch(m_OpeFlag)
	{
	case FOE_WRITE:	
		{
			if (fprintf(m_File,format, data) <0)
			{
				#ifdef DEBUG
				#endif
				CloseStreamFile();
				return false;        
			}
			return true;
		}
	case FOE_READ:
		{					
			if (fscanf(m_File,format, data) <0)
			{
				#ifdef DEBUG
				#endif
				CloseStreamFile();
				return false;        
			}
			return true; 
		}
	default:
		{
			#ifdef DEBUG
			#endif
			return false;
		}
	}	
}
bool BWStreamFile::stream(const char* format,int data)
{
	if (m_FormatFlag!=FFE_TEXT)
	{
#ifdef DEBUG
#endif
		return false;
	}
	if(m_File == NULL)
	{
#ifdef DEBUG
#endif
		return false;
	}
	if(m_OpeFlag != FOE_WRITE)
	{
#ifdef DEBUG
#endif
		return false;
	}
	
	switch(m_OpeFlag)
	{
		case FOE_WRITE:	
		{
			if (fprintf(m_File,format, data) <0)
			{
#ifdef DEBUG
#endif
				CloseStreamFile();
				return false;        
			}
			return true;
		}
		case FOE_READ:
		{					
			if (fscanf(m_File,format, data) <0)
			{
#ifdef DEBUG
#endif
				CloseStreamFile();
				return false;        
			}
			return true; 
		}
		default:
		{
#ifdef DEBUG
#endif
			return false;
		}
	}	
}
bool BWStreamFile::stream(const char* format,float data)
{
	if (m_FormatFlag!=FFE_TEXT)
	{
#ifdef DEBUG
#endif
		return false;
	}
	if(m_File == NULL)
	{
#ifdef DEBUG
#endif
		return false;
	}
	if(m_OpeFlag != FOE_WRITE)
	{
#ifdef DEBUG
#endif
		return false;
	}
	
	switch(m_OpeFlag)
	{
		case FOE_WRITE:	
		{
			if (fprintf(m_File,format, data) <0)
			{
#ifdef DEBUG
#endif
				CloseStreamFile();
				return false;        
			}
			return true;
		}
		case FOE_READ:
		{					
			if (fscanf(m_File,format, data) <0)
			{
#ifdef DEBUG
#endif
				CloseStreamFile();
				return false;        
			}
			return true; 
		}
		default:
		{
#ifdef DEBUG
#endif
			return false;
		}
	}	
}
const char* BWStreamFile::GetDocumentsPath()
{
    return m_DocumentsPathName;
}

const char* BWStreamFile::GetResourcesPath()
{
    return m_ResourcesPathName;
}


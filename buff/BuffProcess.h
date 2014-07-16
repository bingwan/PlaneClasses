
#ifndef __BuffProcess_H__
#define __BuffProcess_H__

#include "CommonDef.h"
#include "cocos2d.h"

USING_NS_CC;

class BuffObject;
class BWUnit;

class BuffProcess
{
public:
	enum 
	{
		BUFF_ID = eBufferType_UNKNOWN,
	};
	virtual	~BuffProcess();
	virtual bool	isContinued();
	virtual bool	isOnced();
	virtual bool	onInit(BWUnit* pGTUnit,BuffObject* pBuff);
	virtual	bool	onStartProcessBuff(BWUnit* pGTUnit,BuffObject* pBuff);
	virtual	bool	onTickProcessBuff(BWUnit* pGTUnit,BuffObject* pBuff,float dt);
	virtual	bool	onEndProcessBuff(BWUnit* pGTUnit,BuffObject* pBuff);
    virtual bool    canOverlap(BWUnit* pGTUnit,BuffObject* pBuff){ return false; }
    
    
protected:
	BuffProcess();
private:
};

#endif //__BuffProcess_H__
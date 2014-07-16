

#ifndef __BUFFPROCESSINHERIT_H__
#define __BUFFPROCESSINHERIT_H__

#include "BuffProcess.h"
#include "BuffObject.h"


class  Buff001 : public  BuffProcess   
{
public:
	enum 
	{
		BUFF_ID = eBufferType_Dingshen,
	};
	enum ParamEnum
	{
		eParamEnum_Dur  =0,
        eParamEnum_Speeed = 1,
		
	};
    Buff001();
	virtual	~ Buff001();
	virtual bool	isContinued();
	virtual bool	isOnced();
	virtual	bool	onStartProcessBuff(BWUnit* pBWUnit, BuffObject* pBuff);
	virtual	bool	onTickProcessBuff(BWUnit* pBWUnit, BuffObject* pBuff,float dt);
	virtual	bool	onEndProcessBuff(BWUnit* pBWUnit, BuffObject* pBuff);

protected:
private:
    
};






#endif //__BUFFPROCESSINHERIT_H__
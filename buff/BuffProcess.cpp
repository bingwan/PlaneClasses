
#include "BuffProcess.h"

BuffProcess::BuffProcess()
{
}

BuffProcess::~BuffProcess()
{	
}
bool BuffProcess::isContinued()
{
	return false;
}
bool BuffProcess::isOnced()
{
	return true;
}
bool BuffProcess::onInit(BWUnit* pGTUnit,BuffObject* pBuff)
{
	return true;
}
bool BuffProcess::onStartProcessBuff(BWUnit* pGTUnit,BuffObject* pBuff)
{
	return true;
}

bool BuffProcess::onTickProcessBuff(BWUnit* pGTUnit,BuffObject* pBuff,float dt)
{
	return true;
}
bool BuffProcess::onEndProcessBuff(BWUnit* pGTUnit,BuffObject* pBuff)
{
	return true;
}
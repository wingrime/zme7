#pragma once
#ifndef LOG_PROVIDER_DEBUG_H_
#define LOG_PROVIDER_DEBUG_H_
#include "log_stdafx.h"
#include "log_provider.h"
/*
Class - cLogProviderDebug
Description - Output log to debug output string
*/
typedef class cLogProviderDebug :public cLogProvider
{
public:
cLogProviderDebug(){}
~cLogProviderDebug(){}
LOGAPI cLogError OutputHandle(LPLOGSTR lpStrOut);
LOGAPI cLogError Init();
LOGAPI cLogError Release();
}*LPLOGPROVIDERDEBUG;
#endif

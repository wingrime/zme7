#pragma once
#ifndef LOG_PROVIDER_STDOUT_H_
#define LOG_PROVIDER_STDOUT_H_
#include "log_stdafx.h"
#include "log_provider.h"
/*
Class - cLogProviderStdout
Description - Output log to stdout
*/
typedef class cLogProviderStdout :public cLogProvider
{
public:
cLogProviderStdout(){}
~cLogProviderStdout(){}
LOGAPI cLogError OutputHandle(LPLOGSTR lpOutHandle);
LOGAPI cLogError Init();
LOGAPI cLogError Release();
}*LPLOGPROVIDERSTDOUT;
#endif

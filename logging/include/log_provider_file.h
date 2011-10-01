#pragma once
#ifndef LOG_PROVIDER_FILE_H_
#define LOG_PROVIDER_FILE_H_
#include "log_stdafx.h"
#include "log_provider.h"
/*
Class - cLogProviderFile
Description - Output log to file
*/
typedef class cLogProviderFile :public cLogProvider
{
public:
cLogProviderFile(){}
~cLogProviderFile(){}
LOGAPI cLogError OutputHandle(LPLOGSTR lpStrOut);
LOGAPI cLogError Init(LPLOGSTR OutFile);
LOGAPI cLogError Release();
private:
FILE *lpOutHandle;
}*LPLOGPROVIDERFILE;
#endif

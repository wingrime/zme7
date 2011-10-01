/*Autor shestacov alexsey*/
/*Log system core file*/
#pragma once
#ifndef __LOG_SYSTEM_H_
#define __LOG_SYSTEM_H_
#include "log_provider.h"
//#include "core_stdafx.h"
#include "log_stdafx.h"
/*
log verbose levels
LV_DEBUG - debug messages
LV_TRACE - trace messages
LV_INFO - information messages
LV_WARNING - warring messages
LV_ERROR - error messages
LV_CRITICAL - critical error messages 
*/
#define LV_TRACE 0
#define LV_DEBUG 1
#define LV_INFO 2
#define LV_WARNING 3
#define LV_ERROR 4
#define LV_CRITICAL 5
/*Quick log macro functions*/

#define LOG_TRACE TRACE()
#define ENG_LOG(a) LOG_INFO(a)
#define LOG_WARRING(a) LOG_WARNING(a)
#define TRACE() lpGlobalLog->Log(LV_TRACE,(char *)__FUNCTION__,NULL)
#define LOG_DEBUG(a) lpGlobalLog->Log(LV_DEBUG,(char *)__FUNCTION__,(char *)a)
#define LOG_INFO(a) lpGlobalLog->Log(LV_INFO,(char *)__FUNCTION__,(char *)a)
#define LOG_WARNING(a) lpGlobalLog->Log(LV_WARNING,(char *)__FUNCTION__,(char *)a)
#define LOG_CRITICAL(a) lpGlobalLog->Log(LV_CRITICAL,(char *)__FUNCTION__,(char *)a)
#define LOG_ERROR(a) lpGlobalLog->Log(LV_ERROR,(char *)__FUNCTION__,(char *)a)
#define LOG_RAW(a,b) lpGlobalLog->RawLog(a,b)
/*
Class: LogSystem
Description: this class collect all debug messages
end send them to log provider
*/
typedef class cLogSystem
{
public:
	cLogSystem(){}
	~cLogSystem(){}
LOGAPI cLogError Create();
LOGAPI cLogError Release();
LOGAPI cLogError SetProvider(LPLOGPROVIDER lpProvider);
LOGAPI cLogError SetMaxVerboseLevel(cLog_byte VerboseLevel);
LOGAPI cLogError SetMaxLogMessages(cLog_uint MaxMessages);
LOGAPI void Log(cLog_byte VerboseLevel,LPLOGSTR lpFunc,LPLOGSTR lpOutMessage);  
LOGAPI void RawLog(cLog_byte VerboseLevel,LPLOGSTR lpOutMessage);
cLog_char * DecodeLVCode(cLog_byte code);
private:
cLog_byte verbose_level;
cLog_uint max_messages;
cLog_uint current_messages;
cLog_char * tmp_buff;
LPLOGPROVIDER provider;
}*LPLOGSYSTEM;
#endif

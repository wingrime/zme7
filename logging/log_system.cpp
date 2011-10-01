#include "log_stdafx.h"
#include "log_system.h"
cLogError cLogSystem::SetProvider(LPLOGPROVIDER lpProvider)
{
if (lpProvider == NULL)
	return LOG_ERR_FAILL;
provider = lpProvider;
return LOG_ERR_SUCCESS;
}
cLogError cLogSystem::SetMaxVerboseLevel(cLog_byte VerboseLevel)
{

	cLogSystem::verbose_level = VerboseLevel;
	return LOG_ERR_SUCCESS;
}
cLogError cLogSystem::SetMaxLogMessages(cLog_uint MaxMessages)
{
max_messages = MaxMessages;
return LOG_ERR_SUCCESS; 
}
LOGAPI void cLogSystem::Log(cLog_byte VerboseLevel,LPLOGSTR lpFunc,LPLOGSTR lpOutMessage)
{
	if (provider)
	{
	//	current_messages++;
	  //	if (max_messages > current_messages)
	  //		return;
	  //	if (verbose_level < VerboseLevel)
	  //		return;
		if (lpOutMessage)
			sprintf(tmp_buff,"%i (%s)%s - %s\n",clock(),DecodeLVCode(VerboseLevel),lpFunc,lpOutMessage);
		else
			sprintf(tmp_buff,"%i (%s)%s\n",clock(),DecodeLVCode(VerboseLevel),lpFunc);
		provider->OutputHandle(tmp_buff);
	}
}
LOGAPI void cLogSystem::RawLog(cLog_byte VerboseLevel,LPLOGSTR lpOutMessage)
{
	if (provider)
	{	
		current_messages++;
		if (max_messages > current_messages)
			return;
		if (verbose_level < VerboseLevel)
			return;

		if (lpOutMessage)
			provider->OutputHandle(lpOutMessage);
	}
}
cLog_char * cLogSystem::DecodeLVCode(cLog_byte code)
{
switch (code)
{
case LV_TRACE:
	 return "Trace";
case LV_DEBUG:
	 return "Debug";
case LV_INFO:
	return "Info";
case LV_WARNING:
	return "Warning";
case LV_ERROR:
	return "Error";
case LV_CRITICAL:
	 return "Critical";
default:
	 return "Unimpl";
}
}
LOGAPI cLogError cLogSystem::Create()
{
	tmp_buff = new cLog_char [256];
	provider = NULL;
	return LOG_ERR_SUCCESS;
}

LOGAPI cLogError cLogSystem::Release()
{
	delete []tmp_buff;

	return LOG_ERR_SUCCESS;
}

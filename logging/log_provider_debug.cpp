#pragma once
#ifndef __LOG_PROVIDER_DEBUG__
#define __LOG_PROVIDER_DEBUG__
#include "windows.h"
#include "log_stdafx.h"
#include "log_provider_debug.h"
cLogError cLogProviderDebug::OutputHandle(LPLOGSTR lpStrOut)
{
OutputDebugString(lpStrOut);
OutputDebugString("\n");
return LOG_ERR_SUCCESS;
}
cLogError cLogProviderDebug::Init()
{
return LOG_ERR_SUCCESS;
}
cLogError cLogProviderDebug::Release()
{
return LOG_ERR_SUCCESS;
}
#endif
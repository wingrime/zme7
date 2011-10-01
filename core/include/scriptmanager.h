#pragma once 
#ifndef __CORE_SCRIPTMANAGER_H_
#define __CORE_SCRIPTMANAGER_H_
#include "core.h"
#include "core_lua.h"
typedef class cGameManager *LPENGGAMEMANAGER;
typedef class cScriptManager
{
public:
	cScriptManager(){}
	~cScriptManager(){}
	ENGAPI cEngError Init();
	ENGAPI cEngError Release();
	ENGAPI cEngError CreateScriptManager(HWND hwin,LPENGGAMEMANAGER lpGM);
	ENGAPI cEngError RunFile(LPENGSTR file);
	//new api
	ENGAPI cEngError LoadFile(LPENGSTR file);
	ENGAPI cEngError DoFunction(LPENGSTR name);
	ENGAPI cEngError DoString(LPENGSTR string);
	/*Debug*/
	ENGAPI cEngError BeginDebug();
	ENGAPI cEngError EndDebug();
	ENGAPI cEngError DebugBreak();
	ENGAPI cEngError DebugContine();
	ENGAPI cEngError DebugStep();
	LPENGSTR GetLuaLastErrorString();

	lua_State* luaVM;
}*LPENGSCRIPTMANAGER;
#endif 

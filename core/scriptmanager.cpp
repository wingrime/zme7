#include "core.h"
#include "scriptmanager.h"
#include "gamemanager.h"
/*LIBS */
//#include "core_luastdafx.h"
//#include "core_lualibbase.h"
//#include "core_lualibevent.h"
//#include "core_lualibreneder.h"
//#include "core_lualibinput.h"
//#include "core_lualibsound.h"
//#include "core_lualibresource.h"


static cEng_bool bTraceContine;
static cEng_bool bDebugContine;

int eng_lua_panic(lua_State *L)
{
	LOG_ERROR("Lua raise panic function");
	LOG_ERROR((LPENGSTR)lua_tostring(L,-1));
	exit(0);
	//__asm{int 03}
	return 0;
}
ENGAPI cEngError cScriptManager::Init()
{
	LOG_TRACE;	
	return ENG_ERR_SUCCESS;
}
ENGAPI cEngError cScriptManager::Release()
{
	LOG_TRACE;
	try 
	{
//		BaseLibRelease();
//		RenederLibRelease();
//		ResourceLibRelease();
//		InputLibRelease();
		if (luaVM)
			lua_close(luaVM);
		luaVM = NULL;
	}
	catch(...)
	{
		LOG_WARRING("Exception on scriptmanager release");
		return ENG_ERR_NC;
	}
	return  ENG_ERR_SUCCESS;
}
ENGAPI cEngError cScriptManager::CreateScriptManager(HWND hwin,LPENGGAMEMANAGER lpGM)
{
  LOG_TRACE;
  luaVM = lua_open();
  	cEng_int res;
	if (luaVM  == NULL)
		return ENG_ERR_FAILL;
	/*Setup panic function*/
		lua_atpanic(luaVM,eng_lua_panic);
		//	luaL_openlibs(luaVM);;
   
       
	/*Libs init*/
//	res = BaseLibRegister(luaVM,hwin,lpGM);
//	if (res < 0)
//	{
//		LOG_ERROR("Unable register base lib");
// 		return ENG_ERR_FAILL;
// 	}
// 	res = EventLibRegister(luaVM,lpGM->lpEventMgr);
// 	if (res < 0)
// 	{
// 		LOG_ERROR("Unable register event lib");
// 		return ENG_ERR_FAILL;
// 	}
// 	res = RenederLibRegister(luaVM,lpGM->lpRenederMgr);
// 	if (res < 0)
// 	{
// 		LOG_ERROR("Unable register reneder lib");
// 		return ENG_ERR_FAILL;
// 	}
// 	res = InputLibRegister(luaVM,lpGM->lpInputMgr);
// 	if (res < 0)
// 	{
// 		LOG_ERROR("Unable register input lib");
// 		return ENG_ERR_FAILL;
// 	}
// 	res = ResourceLibRegister(luaVM,lpGM->lpResourceMgr);
// 	if (res < 0)
// 	{
// 		LOG_ERROR("Unable register resource lib");
// 		return ENG_ERR_FAILL;
// 	}
// 	res = SoundLibRegister(luaVM,lpGM->lpSoundMgr);
// 	if (res < 0)
// 	{
// 		LOG_ERROR("Unable register sound lib");
// 		return ENG_ERR_FAILL;
// 	}
	return ENG_ERR_SUCCESS;
}
static int lsmReport (lua_State *L, int status) {
  const char *msg;
  if (status) {
    msg = lua_tostring(L, -1);
    if (msg == NULL) msg = "(error with no message)";
    fprintf(stderr, "status=%d, %s\n", status, msg);
    lua_pop(L, 1);
  }
  return status;
}


ENGAPI cEngError cScriptManager::RunFile(LPENGSTR file)
{
  LOG_TRACE;
	cEng_int res;
	LPENGSTR lpErr = new cEng_char [256];
	//ENGERROR_ASSEPTSTR(file,"file name 
	//luaL_openlibs(luaVM);
	//	    lua_pushcfunction(luaVM,luaopen_package;
	//  lua_pushliteral(luaVM, "baselib");
	//    lua_call(luaVM, 1, 0);
       
	LOG_INFO(file);
		if (lsmReport(luaVM, luaL_loadfile(luaVM, file) || lua_pcall(luaVM, 0,0,0))) exit(1);
	else printf("okay\n");
	//		res = luaL_dofile(luaVM,file);
	//	if (res != 0)
	//	{
	//		LOG_ERROR("Unable run script");
	//		LOG_ERROR((LPENGSTR)lua_tostring(luaVM,-1));
	//		return ENG_ERR_FAILL;
	//	}
	delete []lpErr;
	return ENG_ERR_SUCCESS;
}

//DEBUG INTERFACE
void lsmDebugHook(lua_State *L, lua_Debug *ar)
{
	while (!bDebugContine)
	{
		/*wait for NextStep*/
	}
	if (bTraceContine )
		bDebugContine  = false;
}
ENGAPI cEngError cScriptManager::BeginDebug()
{
	lua_sethook(luaVM,lsmDebugHook,LUA_MASKLINE,0);
	return  ENG_ERR_SUCCESS;
}
ENGAPI cEngError cScriptManager::EndDebug()
{
	lua_sethook(luaVM,lsmDebugHook,0,0);
	bDebugContine = true;
	bTraceContine = false;
	return  ENG_ERR_SUCCESS;
}
ENGAPI cEngError cScriptManager::DebugBreak()
{
	bDebugContine  = false;
	return  ENG_ERR_SUCCESS;
}
ENGAPI cEngError cScriptManager::DebugContine()
{
	bDebugContine = true;
	bTraceContine = false;
	return  ENG_ERR_SUCCESS;
}
ENGAPI cEngError cScriptManager::DebugStep()
{
	bTraceContine = true;
	return  ENG_ERR_SUCCESS;
}
//new api
ENGAPI cEngError cScriptManager::LoadFile(LPENGSTR file)
{
	cEng_int res;
	res = luaL_loadfile(luaVM,file);
	if (res < 0)
	{
		LOG_ERROR("Could not load file");
		return ENG_ERR_FAILL;
	}
	return ENG_ERR_SUCCESS;
}
//for void function
ENGAPI cEngError cScriptManager::DoFunction(LPENGSTR name)
{

	lua_getfield(luaVM, LUA_GLOBALSINDEX, name);
	lua_call(luaVM, 0, 0);
	return ENG_ERR_SUCCESS;
}
ENGAPI cEngError cScriptManager::DoString(LPENGSTR string)
{
	cEng_int res;
	res = luaL_dostring(luaVM,string);
	if (res != 0)
		return ENG_ERR_FAILL;
	return ENG_ERR_SUCCESS;
}
LPENGSTR cScriptManager::GetLuaLastErrorString()
{
	return (LPENGSTR)lua_tostring(luaVM,-1);
}

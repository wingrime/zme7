#include "core.h"
#include "gamemanager.h"

LPLOGSYSTEM lpGlobalLog;

ENGAPI cEngError cGameManager::Init()
{
	bGamePaused = false;
	return ENG_ERR_SUCCESS;
}
ENGAPI cEngError cGameManager::CreateGame(LPENGSTARTDATA start_struct)
{
	cEngError result;
	lpGameConfig = new cEngStartData;
	lpGlobalLog = new cLogSystem;
	lpGlobalLog->Create();
	lpGlobalLog->SetProvider(start_struct->lpGameLog);
	lpGlobalLog->SetMaxVerboseLevel(start_struct->VerboseLevel);
	lpGlobalLog->SetMaxLogMessages(start_struct->MaxMessages);
	LOG_INFO("Create Game");
	LogSystemInfo();
	LOG_TRACE;
	//memcpy(&lpGameConfig,&start_struct,sizeof(LPENGSTARTDATA));
	lpGameConfig = start_struct;

	/*Initig managers*/
//	lpResourceMgr = new cResourceManager;
//	result = lpResourceMgr->Init();
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpResourceMgr->Init Faill");
//		delete lpResourceMgr;
//	}
//	lpEventMgr = new cEventManager;
//	result = lpEventMgr->Init();
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpEventMgr->Init Faill");
//
//		delete lpResourceMgr;
//		delete lpEventMgr;
//		return result;
//	}
	lpScriptMgr = new cScriptManager;
	result = lpScriptMgr->Init();
	if (result != ENG_ERR_SUCCESS)
//	{
		LOG_ERROR("lpScriptMgr->Init Fail");
//		delete lpResourceMgr;
//		delete lpEventMgr;
		delete lpScriptMgr;
		return result;
//	}
//	lpInputMgr  = new cInputManager;
//	result = lpInputMgr->Init();
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpInputMgr->Init Faill");
//		delete lpResourceMgr;
//		delete lpScriptMgr;
//		delete lpInputMgr;
//		delete lpEventMgr;
//		return result;
//	}
//	lpSoundMgr = new cSoundManager;
//	result = lpSoundMgr->Init();
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpSoundMgr->Init Faill - start game without sound");
//		lpGameConfig->bWithSound = false; //turn of sound system
//	}
//	lpRenederMgr = new cRenederManager;
//	result = lpRenederMgr->Init();
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpRenederMgr->Init Faill");
//		delete lpResourceMgr;
//		delete lpRenederMgr;
//		delete lpScriptMgr;
//		delete lpInputMgr;
//		delete lpEventMgr;
//		return result;
//	}
	return ENG_ERR_SUCCESS;
}
ENGAPI cEngError cGameManager::GameDoStep()
{
	if (bGamePaused)
		return ENG_ERR_SUCCESS;
//	lpStepEvent->Progress(0);
//	lpRenederMgr->Draw();
//	lpInputMgr->ProgressKbdInput();
//	lpInputMgr->ProgressMouseInput();
	return ENG_ERR_SUCCESS;
}
ENGAPI cEngError cGameManager::StartGame()
{
	cEngError result;
	LOG_TRACE;
//	if ( lpResourceMgr == NULL || lpRenederMgr == NULL || lpScriptMgr == NULL)
//		return ENG_ERR_ZERO_INTERFACE;
	/*starting interfaces*/
//	result = lpResourceMgr->CreateResurceManager();
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpResourceMgr-> CreateResurceManager Faill");
//		return result;
//	}
//	result = lpEventMgr->Create();
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpEventMgr->Create Faill");
//		return result;
//	}
//	result = lpRenederMgr->CreateRenederManager(lpGameConfig->h_BaseWindow,!lpGameConfig->bFullScreen,lpGameConfig->xScreenRes,lpGameConfig->yScreenRes);
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpRenederMgr->CreateRenederManager Faill");
//		return result;
//	}
	result = lpScriptMgr->CreateScriptManager(lpGameConfig->h_BaseWindow,this);
	if (result != ENG_ERR_SUCCESS)
	{
		LOG_ERROR("lpScriptMgr->CreateScriptManager Faill");
		return result;
	}
//	result  = lpInputMgr->Create(lpGameConfig->h_BaseWindow);
//	if (result != ENG_ERR_SUCCESS)
//	{
//		LOG_ERROR("lpInputMgr->CreateInputManager Faill");
//		return result;
//	}
//	if (lpGameConfig->bWithSound)
//	{
//		result = lpSoundMgr->CreateSoundManager();
//		if (result != ENG_ERR_SUCCESS)
//		{
//			LOG_ERROR("lpSoundMgr->CreateSoundManager Faill");
//			LOG_INFO("<no sound>");
//			lpGameConfig->bWithSound = false;
//		}
//	}
	
	/*debug mode*/
	//if (lpGameConfig->bDebugStart)
	//{
	//
	//}
	/*Creating events*/
//	LOG_INFO("Register Global Events");
//	lpStartEvent = new cEvent;
//	lpStepEvent = new cEvent;
//
//	lpStartEvent->Create();
//	lpStepEvent->Create();
//	
//	/*Registring events*/
//	lpEventMgr->RegisterGlobalEvent(EV_GAME_START,lpStartEvent);
//	lpEventMgr->RegisterGlobalEvent(EV_GAME_STEP,lpStepEvent);
//	
	/*Begin Game*/
	LOG_INFO("Starting game script");
	LOG_DEBUG(lpGameConfig->lpGameInitScript);
	result = lpScriptMgr->RunFile(lpGameConfig->lpGameInitScript);
//
	if (result != ENG_ERR_SUCCESS)
	{
		LOG_ERROR("Startig Game script");
		return result;
	}
	/*Call Game start event*/
//	LOG_INFO("Progress start event");
//	lpStartEvent->Progress(0);
	return ENG_ERR_SUCCESS;
}
ENGAPI cEngError cGameManager::Release()
{
	LOG_TRACE;
	//try
	//{
		SAFE_RELEASE(lpScriptMgr);
		//		SAFE_RELEASE(lpResourceMgr);
		//		SAFE_RELEASE(lpRenederMgr);
		//SAFE_RELEASE(lpInputMgr);

		//		SAFE_RELEASE(lpStartEvent);
		//SAFE_RELEASE(lpStepEvent)
		//SAFE_RELEASE(lpEventMgr);
	//}
	//catch(...)
	//{
	//	LOG_WARRING("Exception on relasing interfaces");
	//}
	SAFE_RELEASE(lpGameConfig->lpGameLog);
	SAFE_DELETE(lpGameConfig->lpGameLog);
	SAFE_RELEASE(lpGlobalLog);
	SAFE_DELETE(lpGlobalLog);

	SAFE_DELETE(lpGameConfig);
	return ENG_ERR_SUCCESS;
}
ENGAPI cEngError cGameManager::Activate()
{
//	if (bGamePaused)
		return ENG_ERR_FAILL;
//	return lpInputMgr->ActivateControls();
//
}
ENGAPI cEngError cGameManager::Deactivate()
{
/*	if (lpInputMgr)
		return lpInputMgr->DeactivateControls();
	else*/
		return ENG_ERR_FAILL;

}
ENGAPI void cGameManager::LogSystemInfo()
{
  cEng_char *io_ptr = new cEng_char [267];
  //	OSVERSIONINFO *SysInfo = new OSVERSIONINFO;
  //	SYSTEMTIME SysTime;
  //	SysInfo->dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  //	GetLocalTime(&SysTime);
  //	if (GetVersionEx(SysInfo))
  //	{
  		sprintf(io_ptr,"====================================================================");
  		LOG_RAW(LV_INFO,io_ptr);
  		sprintf(io_ptr,"=====================================================================");
  		LOG_RAW(LV_INFO,io_ptr);
  //		sprintf(io_ptr,"Start Date: %2.2i.%2.2i.%2.2i",SysTime.wDay,SysTime.wMonth,SysTime.wYear);
  //		LOG_RAW(LV_INFO,io_ptr);
      		sprintf(io_ptr,"Starting Engine %s",ENG_VERSION_STRING);
		LOG_RAW(LV_INFO,io_ptr);
		sprintf(io_ptr,"Build Info: %s %s",__DATE__,__TIME__);
		LOG_RAW(LV_INFO,io_ptr);
		sprintf(io_ptr,"%s\n",ENG_COPYRIGHT);
		LOG_RAW(LV_INFO,io_ptr);
		//		if (SysInfo->dwPlatformId == VER_PLATFORM_WIN32_NT)
		//			sprintf(io_ptr,"Program started on Linux %i.%i.%i %s",SysInfo->dwMajorVersion,SysInfo->dwMinorVersion,SysInfo->dwBuildNumber,SysInfo->szCSDVersion);
			//		else
			//	sprintf(io_ptr,"Program started on Windows %i.%i.%i %s",SysInfo->dwMajorVersion,SysInfo->dwMinorVersion,SysInfo->dwBuildNumber,SysInfo->szCSDVersion);
		//		LOG_RAW(LV_INFO,io_ptr);
		sprintf(io_ptr,"---------------------------------------------------------------------\n");
		LOG_RAW(LV_INFO,io_ptr);
		//	}

//	delete SysInfo;
	delete io_ptr;
	
  
}

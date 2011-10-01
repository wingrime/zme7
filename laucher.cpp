#include "stdafx.h"
#define MAX_LOADSTRING 100
#define ENGINE_CLASSNAME "ENG_WND__"
#include "../core/core_gamemanager.h"
#include "../core/log_system/log_provider_file.h"
#include "tinyxml.h"
#include <dbghelp.h>
#include "resource.h"
cGameManager *cm = NULL;
//cLog *log  = NULL;
// Global Variables:
HINSTANCE hInst;								// current instance

ATOM				MyRegisterClass(HINSTANCE hInstance);

BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DebugCtrlDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    DbgCmdExec(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow)) 
		return FALSE;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}

	return (int) msg.wParam;
}
//////////////////////////////
/*Global Exception handler function*/
LONG WINAPI ErrorHook( struct _EXCEPTION_POINTERS* lpExc )
{
	char * lpLogOut = new char [256];
	if ( lpGlobalLog )
	{
		
		DWORD64  dwDisplacement;
		ULONG64 buffer[(sizeof(SYMBOL_INFO) +
			MAX_SYM_NAME*sizeof(TCHAR) + sizeof(ULONG64) - 1) /sizeof(ULONG64)];
		PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		pSymbol->MaxNameLen = MAX_SYM_NAME;
		PIMAGEHLP_MODULE64 lpImageInfo = new IMAGEHLP_MODULE64;
		ZeroMemory(lpImageInfo,sizeof(PIMAGEHLP_MODULE64));
		lpImageInfo->SizeOfStruct = sizeof(PIMAGEHLP_MODULE64);
		SymGetModuleInfo64(GetCurrentProcess(),lpExc->ContextRecord->Eip,lpImageInfo);
		if (SymFromAddr(GetCurrentProcess(), lpExc->ContextRecord->Eip, &dwDisplacement, pSymbol))
		{
			if (dwDisplacement > 0)
				sprintf(lpLogOut,"Exception in module %s on %s+0x%x",lpImageInfo->ImageName,pSymbol->Name,dwDisplacement);
			else 
				sprintf(lpLogOut,"Exception in module %s on %s0x%x",lpImageInfo->ImageName,pSymbol->Name,dwDisplacement);
		}
		else
			sprintf(lpLogOut,"Exception on 0x%8.8x",lpExc->ContextRecord->Eip,dwDisplacement);
		LOG_ERROR(lpLogOut);
		/*Registers dump*/
		LOG_ERROR("---------Registers dump---------");
		sprintf(lpLogOut,"eax=0x%8.8x ebx=0x%8.8x ecx=0x%8.8x edx=0x%8.8x",lpExc->ContextRecord->Eax,
			lpExc->ContextRecord->Ebx,lpExc->ContextRecord->Ecx,lpExc->ContextRecord->Edx);
		LOG_INFO(lpLogOut);
		sprintf(lpLogOut,"ebp=0x%8.8x esp=0x%8.8x esi=0x%8.8x edi=0x%8.8x",lpExc->ContextRecord->Ebp,lpExc->ContextRecord->Esp,
			lpExc->ContextRecord->Esi,lpExc->ContextRecord->Edi);
		LOG_INFO(lpLogOut);
		sprintf(lpLogOut,"EFlags=0x%8.8x eip=0x%8.8x",lpExc->ContextRecord->EFlags,lpExc->ContextRecord->Eip);

		LOG_ERROR(lpLogOut);

		/*Dump*/
		HANDLE hDmpFile;
		PMINIDUMP_EXCEPTION_INFORMATION lpmdEI= new MINIDUMP_EXCEPTION_INFORMATION ;
		SYSTEMTIME SysTime;
		GetLocalTime(&SysTime);
		sprintf(lpLogOut,"Dump_%i%i%i.dmp",SysTime.wSecond,SysTime.wMinute,SysTime.wDay);
		hDmpFile = CreateFile(lpLogOut,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		lpmdEI->ThreadId = GetCurrentThreadId();
		lpmdEI->ClientPointers = false;
		lpmdEI->ExceptionPointers = lpExc;
		MiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),hDmpFile,MiniDumpWithDataSegs ,lpmdEI,NULL,NULL);
		/*Stack Walking*/
		LOG_ERROR("-------------Stack Walk---------");
		LPSTACKFRAME64 StackFrame  = new STACKFRAME64;
		ZeroMemory(StackFrame,sizeof(STACKFRAME64));
		StackFrame->AddrPC.Offset = lpExc->ContextRecord->Eip;
		StackFrame->AddrPC.Mode = AddrModeFlat;
		StackFrame->AddrFrame.Offset = lpExc->ContextRecord->Ebp;
		StackFrame->AddrFrame.Mode = AddrModeFlat;
		while  (StackWalk64(IMAGE_FILE_MACHINE_I386,GetCurrentProcess(),GetCurrentThread(),StackFrame,lpExc->ContextRecord,NULL,
			SymFunctionTableAccess64,SymGetModuleBase64,NULL))
		{
			if (StackFrame->AddrReturn.Offset)
			{
				SymGetModuleInfo64(GetCurrentProcess(),StackFrame->AddrReturn.Offset,lpImageInfo);

				if (SymFromAddr(GetCurrentProcess(),StackFrame->AddrReturn.Offset, &dwDisplacement, pSymbol))
					sprintf(lpLogOut,"Stack: %s!%s+0x%x ",lpImageInfo->ImageName,pSymbol->Name,dwDisplacement);
				else
					sprintf(lpLogOut,"Stack: %s!0x%8.8x",lpImageInfo->ImageName,StackFrame->AddrReturn.Offset);
				LOG_INFO(lpLogOut);
			}
		}
	
	}
	else
	{
		sprintf(lpLogOut,"Error on EIP:0x%x",lpExc->ContextRecord->Eip);
		MessageBox(0,lpLogOut,"Error",16);
	}
		
	lpGlobalLog->Release();
	ExitProcess(12);
	return 0;
};
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			=  0;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_LAUCHER);
	wcex.hCursor		= 0;
	wcex.hbrBackground	=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= ENGINE_CLASSNAME;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd = NULL;
   char *gamefile;
   int result;
   hInst = hInstance;
   TiXmlDocument config("laucher.cfg");
   TiXmlHandle configHandle(&config);   
   /*Init debuging sysmbols*/
  
   if (!SymInitialize(GetCurrentProcess(),NULL,true))
   {
	   MessageBox(0,"Init dbghelp.dll failed - critical","Error",16);
	   exit(-1);
   }
   if (!config.LoadFile())
   {
		MessageBox(0,"config.LoadFile","Error on loading config",16);
		exit(-1);
   }
   TiXmlElement* itemElement = 0;

   itemElement = configHandle.FirstChild("game").FirstChild("config").ToElement();

   itemElement->QueryIntAttribute("globalseh",&result);
   /*Setup global exception handler */
   if  (result)
	   SetUnhandledExceptionFilter(ErrorHook);
   /*test*/

   gamefile = (char * )itemElement->Attribute("game");

   int wndxpos,wndypos,wndxsize,wndysize;
   LPENGSTARTDATA  game_config = new cEngStartData;
   itemElement->QueryIntAttribute("wndxpos",&wndxpos);
   itemElement->QueryIntAttribute("wndypos",&wndypos);
   itemElement->QueryIntAttribute("wndxsize",&wndxsize);
   itemElement->QueryIntAttribute("wndysize",&wndysize);   
   itemElement->QueryIntAttribute("wnddef",&result);
   itemElement->QueryIntAttribute("fullscreen",(int*)&game_config->bFullScreen);
	
   if (game_config->bFullScreen)
   {
	   hWnd = CreateWindow( ENGINE_CLASSNAME, itemElement->Attribute("wndtitle"), WS_OVERLAPPED,
	   0, 0,wndxsize, wndysize, 0, NULL, hInstance, NULL);
	   ShowCursor(FALSE); 
   }
   else
   if (!result)
   {
	   hWnd = CreateWindow( ENGINE_CLASSNAME, itemElement->Attribute("wndtitle"), WS_OVERLAPPEDWINDOW,
	    wndxpos, wndypos, wndxsize, wndysize, 0, NULL, hInstance, NULL);
   }
   else
   {
	   hWnd = CreateWindow( ENGINE_CLASSNAME, itemElement->Attribute("wndtitle"), WS_OVERLAPPEDWINDOW,
	    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 0, NULL, hInstance, NULL);

   }
   if (!hWnd)
   {
      return FALSE;
   }


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   /*Config reading*/

   //start game
   	cm = new cGameManager ;	
	
	itemElement->QueryIntAttribute("logging",&result);
	if (result)
	{
		LPLOGPROVIDERFILE lpFProv = new cLogProviderFile;
		lpFProv->Init(SYSTEM_LOG_FILE_NAME);
		
		game_config->lpGameLog = lpFProv;
	}
	else
		game_config->lpGameLog = NULL;
	game_config->xScreenRes = wndxsize;
	game_config->yScreenRes = wndysize;
	

	//game_config->lpResourceFile = ReadConfigString("resurcefile");
	//
	itemElement->QueryIntAttribute("sound",(int*)&game_config->bWithSound);
	itemElement->QueryIntAttribute("verboselevel",(int*)&game_config->VerboseLevel);
	itemElement->QueryIntAttribute("maxmessages",(int*)&game_config->MaxMessages);
	game_config->h_BaseWindow = hWnd;
	game_config->lpGameInitScript = (LPENGSTR)malloc(sizeof(cEng_char)*256);
	strcpy(game_config->lpGameInitScript,(char * )itemElement->Attribute("initsc"));
	//todo: here pointer loose!!!
	cm->Init();
	if (cm->CreateGame(game_config)!= ENG_ERR_SUCCESS)
	{
		ShowWindow(hWnd,SW_HIDE);
		MessageBox(hWnd,"Game creation error for more information see log file","Error",16);
		exit(10);
	}

	
	//else
	if (cm->StartGame() != ENG_ERR_SUCCESS)
	{
		ShowWindow(hWnd,SW_HIDE);
		MessageBox(hWnd,"Game start error for more information see log file","Error",16);
		exit(10);
	}



   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message) 
	{

	case WM_PAINT:		
		if (cm!= NULL)
		{
			if (cm->GameDoStep() != ENG_ERR_SUCCESS)
			{
				ShowWindow(hWnd,SW_HIDE);
				MessageBox(hWnd,"Game runtime error for more information see log files","Error",16);
				PostQuitMessage(255);
			}
		}
	break;
	case WM_LBUTTONDOWN:
		if (cm)
			cm->Activate();
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

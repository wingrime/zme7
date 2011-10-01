/*Autor shestacov alexsey*/
/*Log system standart includes*/
#pragma once

#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include <time.h>

#define cLog_int long int
#define cLog_uint unsigned long int
#define cLog_short unsigned short int
#define cLog_byte unsigned char
#define cLog_float float
#define cLog_char char
#define cLog_constchar const char
#define cLog_bool bool




//#ifdef LOG_AS_DLL
//	#define LOGAPI __declspec(dllexport)
//#else
#define LOGAPI 
//#endif 
typedef cLog_char *LPLOGSTR;
typedef cLog_constchar *LPCONSTLOGSTR;
typedef enum cLogError
	{
		LOG_ERR_SUCCESS,  
		LOG_ERR_FAILL
	}*LPLOGERROR;

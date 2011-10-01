/**
�������� �����
*/
#pragma once 
#pragma pack (1)
#ifndef __CORE_TYPES_H_
#define __CORE_TYPES_H_
#include "core_config.h"

#define cEng_int long int ///< ����� �������� 
#define cEng_uint unsigned long int ///< ����� ����������� 
#define cEng_short unsigned short int ///< ����� ������� �����������
#define  cEng_byte unsigned char ///< ���� 
#define cEng_float float ///< ����� � ��������� ������
#define cEng_char char ///< ������
#define cEng_bool bool ///< �������� ���

typedef cEng_char *LPENGSTR;///< ������ 
#ifdef ENG_AS_DLL
	#define ENGAPI __declspec(dllexport) //������� ������� ����������
#else
	#define ENGAPI 
#endif
/// ���� ������
/**
���� ������ ������������ ���������
*/
typedef enum cEngError
	{
	ENG_ERR_SUCCESS,  ///<  �������� �������
	ENG_ERR_FAILL, ///< �������� ��������� 
	ENG_ERR_FAIL, 
	ENG_ERR_IO, ///< ������ �����\������
	ENG_ERR_INVALIDIN, ///< �������� ������� ������
	ENG_ERR_ZERO_INTERFACE, ///< ��� ������ ��������� ���������
	ENG_ERR_NC, ///< ����������� ������
	}*LPENGERROR;

/*typedef enum cEngInputHandleType
{
	ENG_IHT_UP,
	ENG_IHT_DOWN
}*LPENGINPUTHANDLETYPE;*/
#ifdef ENG_USE_PACK
	#pragma pack(push,8)
#endif
///������
typedef struct cEngSize
{
	cEng_int xsize;
	cEng_int ysize;
}*LPENGSIZE;
///������������� �������
typedef struct cEngRect
{
	cEng_int xbase;
	cEng_int ybase;
	cEng_int xsize;
	cEng_int ysize;
}*LPENGRECT;

class cLogProvider;
/// ������ ����������� ��� ������ ����
/**
��� ������� ������ ���������� ��� �� ��������� ���� ��������������������
*/
//windows comportible
#define HWND int

typedef struct cEngStartData
{
	cEng_int xScreenRes;  ///<  ��������� ������ �� �����������
	cEng_int yScreenRes;  ///<  ���������� ������ �� ��������� 
	HWND h_BaseWindow;  ///<  ������ ���� �� ������� ����� ������� ������
	cEng_bool bFullScreen; ///<  ���� ������ �� ������ � ������������� ������
	cEng_bool bWithSound;  ///<  ���� ������ �� ����������� �������� ����������
	cEng_bool bDebugStart;  ///<  ���� ������ �� ������ ���� � ���������� ������
	LPENGSTR lpGameInitScript;  ///< ��� ����� �������, ������� ����� ������� ����� �������� �������������
	LPENGSTR lpResourceFile;   ///<  (�������������� ���������������)
	cLogProvider * lpGameLog;  ///<  ��������� �� ����� , ������� ����� ��������� ���������� �����������
	cEng_byte VerboseLevel;  ///<  ������� ������� 
	cEng_uint MaxMessages;  ///<  ������������ ���������� ���������� ���������, ��� ���������� �������� ���������� ��������� ����� ������������
}*LPENGSTARTDATA;

#endif
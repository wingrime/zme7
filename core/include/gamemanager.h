/**
�������� ���������� ���������� ���� cGameManager
*/
#pragma once
#ifndef __CORE_GAMEMANAGER_H_
#define __CORE_GAMEMANAGER_H_
//windows old stuff
//diable bool performance warring
//#pragma warning(disable:4800)
//srint format argument conflict 
//#pragma warning(disable:4313)
//this is core game manager class definefile
#include "core.h"

/*MANAGERS*/
//#include "renedermanager.h"
//#include "resourcemanager.h"
#include "scriptmanager.h"
//#include "inputmanager.h"
//#include "soundmanager.h"
//#include "eventmanager.h"

/// ��������� ���������� �����
/** 
����� cGameManager ������������� �� ���� ��������� ���������� �����, 
��������� ������������� ��������� ���� � �������� ���������� ���������� ����������
*/
typedef class cGameManager
{
public:
	/// ������ �����������
	cGameManager(){};
	/// ������ ����������
	~cGameManager(){};
	/*game control*/
	/// �������������
	/**
	�������������� �����
	*/
	ENGAPI cEngError Init();
	/// ������� ���� 
	/**
	������� ����,��������� ������
	\param start_struct ��������� ���������� ������ ����������� ��� ������ ����,������ ���� ��������� � �������������������
	\return ��� ������
	*/
	ENGAPI cEngError CreateGame(LPENGSTARTDATA start_struct);
	/// �������� ����
	/**
	��������� ������ ����
	
	\return ��� ������
	*/
	ENGAPI cEngError StartGame();
	/// ���������������
	/**
	����� ����� ������ ����� �� ������������
	����������� �������
	\return ��� ������
	*/
	ENGAPI cEngError Release();
	/// ��������� ������� ����
	/**
	������������� ��������� ������� ����
	\return ��� ������
	*/
	ENGAPI cEngError GameDoStep();
	/*input control*/
	/// �������� ������ ����������
	/**
	�������� ������ ������ � ����������,
	�������������� ���������� �����
	\return ��� ������
	*/
	ENGAPI cEngError Activate();  // ���������� ���� � ���� ����
	/// ���������� ������ ������ � ����������
	/**
	��������� ������ ����������� �������� ������ � ����������
	\return ��� ������
	*/
	ENGAPI cEngError Deactivate();//��������� ���� � ���� ����



	cEng_bool bGamePaused; ///< ��������������� �� ����

//	/*Managers*/
//	LPENGRENEDERMANAGER lpRenederMgr;  ///< ��������� �� �������� ��������� 
//	LPENGRESOURCEMANAGER lpResourceMgr; ///< ��������� �� �������� ��������
	LPENGSCRIPTMANAGER lpScriptMgr;  ///< ��������� �� �������� ���������� �������
//	LPENGINPUTMANAGER lpInputMgr;  ///< ��������� �� �������� �����
//	LPENGSOUNDMANAGER lpSoundMgr;  ///< ��������� �� �������� �������� ����������
//	LPENGEVENTMANAGER lpEventMgr;  ///< ��������� �� �������� �������
//	/*Events*/
//	LPENGEVENT lpStartEvent;  ///< ������� ������ ���� 
//	LPENGEVENT lpStepEvent;  ///< ������� �������� �����

	LPENGSTARTDATA lpGameConfig;  ///< ��������� �� ��������� ���������� ������ ������������� ����
private:
	/// ������� ������� � ������� � ���
	/**
	�������� � ��� ������ � ������� ����� ������� �������
	\return ��� ������
	*/
	ENGAPI void LogSystemInfo(); 
}*LPENGGAMEMANAGER;
#endif

/**
описание интерфейса управления игры cGameManager
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

/// Интерфейс управления игрой
/** 
Класс cGameManager предоставляет из себя интерфейс управления игрой, 
выполняет инициализацию подсистем игры и передает управление скриптовой подсистеме
*/
typedef class cGameManager
{
public:
	/// Пустой конструктор
	cGameManager(){};
	/// Пустой деструктор
	~cGameManager(){};
	/*game control*/
	/// Инициализатор
	/**
	Инициализирует класс
	*/
	ENGAPI cEngError Init();
	/// Создает игру 
	/**
	Создает игру,загружает данные
	\param start_struct Структура содержащая данные необходимые для старта игры,должна быть заполнена и проинициализирована
	\return Код Ошибки
	*/
	ENGAPI cEngError CreateGame(LPENGSTARTDATA start_struct);
	/// Начинает игру
	/**
	Запускает скрипт игры
	
	\return Код Ошибки
	*/
	ENGAPI cEngError StartGame();
	/// Деинициализатор
	/**
	Когда класс больше нигде не используется
	освобождает ресурсы
	\return Код Ошибки
	*/
	ENGAPI cEngError Release();
	/// Выполняет игровой цикл
	/**
	Принудительно прогоняет игровой цикл
	\return Код Ошибки
	*/
	ENGAPI cEngError GameDoStep();
	/*input control*/
	/// Начинает захват клавиатуры
	/**
	Начинает захват данных с калвиатуре,
	монополизирует Устройства ввода
	\return Код Ошибки
	*/
	ENGAPI cEngError Activate();  // активирует ввод в окно игры
	/// Прекращает захват данных с клавиатуры
	/**
	Позволяет другим приложениям получать данные с клавиатуры
	\return Код Ошибки
	*/
	ENGAPI cEngError Deactivate();//отключает ввод в окно игры



	cEng_bool bGamePaused; ///< Приостановленна ли игра

//	/*Managers*/
//	LPENGRENEDERMANAGER lpRenederMgr;  ///< Указатель на мендежер ренединга 
//	LPENGRESOURCEMANAGER lpResourceMgr; ///< Указатель на менеджер ресурсов
	LPENGSCRIPTMANAGER lpScriptMgr;  ///< Указатель на менеджер исполнения скрипта
//	LPENGINPUTMANAGER lpInputMgr;  ///< Указатель на мендежер ввода
//	LPENGSOUNDMANAGER lpSoundMgr;  ///< Указатель на менеджер звуковой подсистемы
//	LPENGEVENTMANAGER lpEventMgr;  ///< Указаетль на менеджер событий
//	/*Events*/
//	LPENGEVENT lpStartEvent;  ///< Событие старта игры 
//	LPENGEVENT lpStepEvent;  ///< Событие игрового цикла

	LPENGSTARTDATA lpGameConfig;  ///< Указаетль на структуру содержащие данные инициализации игры
private:
	/// Выводит инфацию о системе в лог
	/**
	Печатает в лог данные о системе билде времени запуска
	\return Код Ошибки
	*/
	ENGAPI void LogSystemInfo(); 
}*LPENGGAMEMANAGER;
#endif

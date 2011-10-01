/**
Описание типов
*/
#pragma once 
#pragma pack (1)
#ifndef __CORE_TYPES_H_
#define __CORE_TYPES_H_
#include "core_config.h"

#define cEng_int long int ///< целое знаковое 
#define cEng_uint unsigned long int ///< целое беззнаковое 
#define cEng_short unsigned short int ///< целое краткое беззнаковое
#define  cEng_byte unsigned char ///< байт 
#define cEng_float float ///< число с плавающей точкой
#define cEng_char char ///< символ
#define cEng_bool bool ///< буллевой тип

typedef cEng_char *LPENGSTR;///< строка 
#ifdef ENG_AS_DLL
	#define ENGAPI __declspec(dllexport) //внешние команды библиотеки
#else
	#define ENGAPI 
#endif
/// Коды ошибок
/**
Коды ошибок возвращаемые функциями
*/
typedef enum cEngError
	{
	ENG_ERR_SUCCESS,  ///<  операция успешна
	ENG_ERR_FAILL, ///< операция провалена 
	ENG_ERR_FAIL, 
	ENG_ERR_IO, ///< ошибка ввода\вывода
	ENG_ERR_INVALIDIN, ///< неверные входные данные
	ENG_ERR_ZERO_INTERFACE, ///< был предан нерабочий интерфейс
	ENG_ERR_NC, ///< критическая ошибка
	}*LPENGERROR;

/*typedef enum cEngInputHandleType
{
	ENG_IHT_UP,
	ENG_IHT_DOWN
}*LPENGINPUTHANDLETYPE;*/
#ifdef ENG_USE_PACK
	#pragma pack(push,8)
#endif
///Размер
typedef struct cEngSize
{
	cEng_int xsize;
	cEng_int ysize;
}*LPENGSIZE;
///прямоугольная область
typedef struct cEngRect
{
	cEng_int xbase;
	cEng_int ybase;
	cEng_int xsize;
	cEng_int ysize;
}*LPENGRECT;

class cLogProvider;
/// Данные необходимые для старта игры
/**
Для запуска движка необходмио что бы структурв была проинициализированна
*/
//windows comportible
#define HWND int

typedef struct cEngStartData
{
	cEng_int xScreenRes;  ///<  Разрешеие экрана по горизонтали
	cEng_int yScreenRes;  ///<  Разрешение экрана по вертикали 
	HWND h_BaseWindow;  ///<  Хэндел окна на котором будет запущен движок
	cEng_bool bFullScreen; ///<  Если ПРАВДА то запуск в полноэкранном режиме
	cEng_bool bWithSound;  ///<  Если ПРАВДА то запускается звуковая подсистема
	cEng_bool bDebugStart;  ///<  Если ПРАВДА то запуск идет в отладочном режиме
	LPENGSTR lpGameInitScript;  ///< Имя файла скрипта, который будет запущен после процесса инициализации
	LPENGSTR lpResourceFile;   ///<  (неиспользуется зарезервировано)
	cLogProvider * lpGameLog;  ///<  Указатель на класс , который будет управлять отладочной информацикй
	cEng_byte VerboseLevel;  ///<  Уровень отладки 
	cEng_uint MaxMessages;  ///<  Максимальное количество отладочный сообщении, при привышении которого исполнение программы будет остановленно
}*LPENGSTARTDATA;

#endif
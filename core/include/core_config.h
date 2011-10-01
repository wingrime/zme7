#pragma once
#ifndef __CORE_CONFIG_H_
#define __CORE_CONFIG_H_
#define ENG_VERSION 849
#define ENG_VERSION_STRING "Version 0.849"
#define ENG_COPYRIGHT "Shestacov Alexsey(C)2007-2009 with Lua, PNGlib, XML2lib, fmodEx"
//#define ENG_AS_DLL 
#define ENG_USE_PACK 
#define ENG_CACHEDEF_SIZE 24*1024*1024 //24 Mb
#define MOUSE_BUFFER_SIZE  16
#define EVENT_MAXARG 10
#define DIRECTINPUT_VERSION 0x800
#define SYSTEM_LOG_FILE_NAME "System.log"
//#define ENG_PI       3.14159265358979323846
#define ENG_PI 3.141592654f
#define ENG_MAXLOG 12000
//#define ENG_STDOUT_LOG
//#define ENG_LOG_NOCLEAN 
#define ENG_MAXSNDCHANNELS 32 

//disable bool performance warning
#pragma warning(disable:4800)
//disable format argument warning 
#pragma warning(disable:4313)

/*Lua library's names rules */
/*
 "_G" - global name space for lua objects
 "<any_name>" - library name space for lua objects
 ----------------------------------------------
 <any_name>.<any_function> -- library name space
 <any_function> -- global name space
*/
#define BASE_L_NAME "_G"
#define RENEDER_L_NAME "_G"
#define INPUT_L_NAME "_G"
#define SOUND_L_NAME "_G"
#define RESOURCE_L_NAME "_G"
#define EVENT_L_NAME "_G"
/* EVENTS */
#define EV_GAME_START "EvGameStart"
#define EV_GAME_STEP "EvGameStep"

#endif
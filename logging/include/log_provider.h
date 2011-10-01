#pragma once
#ifndef __LOG_PROVIDER_H_
#define __LOG_PROVIDER_H_
#include "log_stdafx.h"
/*
Class: cLogProvider
Description: abstract class for  system-depend log output
*/
typedef class cLogProvider
{
public:
	 virtual cLogError OutputHandle(LPLOGSTR lpStrOut) =0;
	 virtual cLogError Release()=0;

}*LPLOGPROVIDER;
#endif

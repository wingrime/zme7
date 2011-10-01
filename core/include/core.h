/**
Стандартные заголовочные файлы
*/
#pragma once

#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>

#include <time.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>


#include "core_types.h"
#include "core_macros.h"



#include "log_system.h"


LPLOGSYSTEM extern lpGlobalLog;  ///< Система логгига видимая повсеместно, используется в макросах
#pragma once 
#ifndef __CORE_MACROS_H_
#define __CORE_MACROS_H_
/*macroses for engine*/
//#ifndef ENG_STDOUT_LOG
//	#define LOG_TRACE LOG_INFO("") 
//	#define ENG_LOG(a) LOG_INFO(a) 
//	#define LOG_INFO(a) lpGlobalLog->Info(__FILE__,__FUNCTION__,a)
//	#define LOG_WARRING(a) lpGlobalLog->Warring(__FILE__,__FUNCTION__,a)
//	#define LOG_ERROR(a) lpGlobalLog->Error(__FILE__,__FUNCTION__,a)
//#else
//	#define ENG_LOG(a) printf("%s\n",a);fflush(stdout)
//#endif 
#define SAFE_RELEASE(a) if (a != NULL){a->Release();a = NULL;}
#define SAFE_DELETE(a) if (a != NULL){delete a;a = NULL;}
#define ENGFAILED(a) (a != ENG_ERR_SUCCESS)
#define ENGSUCCESSED(a) (a == ENG_ERR_SUCCESS)
#define CRITICAL_RETURN return ENG_ERR_FAILL
#define ENGERROR_TEST(a) if ENGFAILED(a){CRITICAL_RETURN;}
#define ENGERROR_TESTSTR(a,b) if  ENGFAILED(a){ENG_ERROR(b);CRITICAL_RETURN;}
#define ENGERROR_STR(a) {LOG_ERROR(a);CRITICAL_RETURN;}
#define ENGERROR_ASSEPT(a) if (a == NULL ){CRITICAL_RETURN;}
#define ENGERROR_ASSEPTSTR(a,b) if (a == NULL ){ENG_LOG(b);CRITICAL_RETURN;}
#define BP __asm{int 03}
#define ENGERROR_ASSEPTTEST(a) (a == NULL )
#endif

#include "log_stdafx.h"
#include "log_provider_stdout.h"
cLogError cLogProviderStdout::OutputHandle(LPLOGSTR lpOutHandle)
{
printf(lpOutHandle,"LOG:%s\n\n",lpOutHandle);
return LOG_ERR_SUCCESS;
}
cLogError cLogProviderStdout::Init()
{
  printf("Starting stdout logger\n");
return LOG_ERR_SUCCESS;
}
cLogError cLogProviderStdout::Release()
{
return LOG_ERR_SUCCESS;
}

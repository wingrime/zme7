#include "log_stdafx.h"
#include "log_provider_file.h"
cLogError cLogProviderFile::OutputHandle(LPLOGSTR lpStrOut)
{
if (lpOutHandle)
	{
	fprintf(lpOutHandle,"%s\n",lpStrOut);
	fflush(lpOutHandle);
	return LOG_ERR_SUCCESS;
	}
return LOG_ERR_FAILL;
}
cLogError cLogProviderFile::Init(LPLOGSTR OutFile)
{
lpOutHandle = fopen(OutFile,"wt");
if (lpOutHandle == NULL)
	return LOG_ERR_FAILL;
return LOG_ERR_SUCCESS;
}
cLogError cLogProviderFile::Release()
{
if (lpOutHandle)
	{
	fclose(lpOutHandle);
	return LOG_ERR_SUCCESS; 
	}
return LOG_ERR_FAILL;
}

/*
 *	debug.h
 *	chp[2011-11-23]
 *
 */
 
#ifndef _CHP_DEBUG_H_
#define _CHP_DEBUG_H_

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <iconv.h>

#include "DACommon.h"

#define SIG_ZERO		0

#define DELETE_FILE(File) \
{ \
	char szCmd[256]={0}; \
	snprintf(szCmd, sizeof(szCmd)-1, "rm -rf \"%s\"", File); \
	system(szCmd); \
}

int g_iDebug=1;

static inline void DEBUG(char *str, ...)
{
#ifdef CHP_DEBUG
	/*va_list va;
	char szBuff[256];
	
	memset(szBuff, 0, sizeof(szBuff));
	va_start (va, str);
	vsnprintf(szBuff, sizeof(szBuff)-1, str, va);
	va_end(va);
	printf("%s", szBuff);*/
#endif

//#ifdef CHP_DEBUG_D
	if(g_iDebug > 0)
	{
		va_list va;
		char szBuff[256];
			
		memset(szBuff, 0, sizeof(szBuff));
		va_start (va, str);
		vsnprintf(szBuff, sizeof(szBuff)-1, str, va);
		va_end(va);
		printf("%s", szBuff);
	}
//#endif
    return ;
}
/*
static inline int WritePid(char *pszPidPath)
{
	FILE *fp;
	pid_t iPid=0;
	
	fp = fopen(pszPidPath, "w+b");
	if(NULL == fp)
	{
		return -1;
	}
	
	iPid = getpid();
	
	if(fwrite(&iPid, sizeof(iPid), 1, fp) <= 0)
	{
		//Ignore
	}
	
	fclose(fp);
	
	return 0;
}

static inline BOOL IsAlreadyRun(char *pszPidPath)
{
	FILE *fp;
	pid_t iPid=0;
	
	fp = fopen(pszPidPath, "rb");
	if(NULL == fp)
	{
		return FALSE;
	}
	
	if(fread(&iPid, sizeof(iPid), 1, fp) <= 0)
	{
		//Ignore
	}
	
	fclose(fp);
	
	if(iPid <= 0)
	{
		return FALSE;
	}
	
	if(kill(iPid, SIG_ZERO) < 0)
	{
		return FALSE;
	}
	else
	{
		DEBUG("%d Pid Is Running\n", iPid);
		return TRUE;
	}
}
*/

static inline int WritePid(char *pszPidPath)
{
	FILE *fp;
	pid_t iPid=0;
	
	fp = fopen(pszPidPath, "w+b");
	if(NULL == fp)
	{
		return -1;
	}
	
	iPid = getpid();
	
	if(fwrite(&iPid, sizeof(iPid), 1, fp) <= 0)
	{
		//Ignore
	}
	
	fclose(fp);
	
	return 0;
}

static inline BOOL IsAlreadyRun(char *pszPidPath)
{
	FILE *fp;
	pid_t iPid=0;
	
	fp = fopen(pszPidPath, "rb");
	if(NULL == fp)
	{
		return FALSE;
	}
	
	if(fread(&iPid, sizeof(iPid), 1, fp) <= 0)
	{
		//Ignore
	}
	
	fclose(fp);
	
	if(iPid <= 0)
	{
		return FALSE;
	}
	
	if(kill(iPid, SIG_ZERO) < 0)
	{
		return FALSE;
	}
	else
	{
		DEBUG("%d Pid Is Running\n", iPid);
		return TRUE;
	}
}

#endif




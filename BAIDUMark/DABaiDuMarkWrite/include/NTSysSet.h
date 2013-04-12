/*
 *	NTSysSet.h
 *	
 *
 */

#ifndef _TNSYSSET_H_
#define _TNSYSSEt_H_

//#include "../../NTCommon/NTCommon.h"

//int InitKnifeLog(char cType, int iMode);
//int WrietKnifeLog(KnifeLog Log, char cType);

//int NTSysType(sSysType sysType);

#pragma pack(push, 1)

typedef struct SysType
{
	int	iNetMode; //net mode      
	int	iNetType; //net environment
	int	iIndexType;
	int	iKnifeType;
	int	iDatabaseUse;
	char	szIP[16];
	char	szDBUserName[32];
	char	szDBPass[32]; 
	
}SysType;


#pragma pack(pop)

int InitSysType(SysType *pstysType);
#endif



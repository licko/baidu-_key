
// FileName: DABaiDuMarkAnalyse.c
// Editor  : lsz
// Time    : 2013-04-11



#include "DABaiDuMarkAnalyse.h"


#define VERSION_INFO "v1.0.0.0"
#define LAST_MODIFY "2013-04-11"
#define MOULE_NAME "DABaiDuMarkAnalyse"
int Version(void)
{
	printf("---------Solib [%s]:\n\t.Version Info: %s\n\t.Last Modify: %s\n", MOULE_NAME, VERSION_INFO, LAST_MODIFY);
	return 0;
};



int DAInit(int iMode)
{
	if(OP_SUCCESS != InitBaiDuMarkDll())
	{
		DEBUG("InitBaiDuMarkDll Failed\n");
		return -1;
	}
	return 0;
};

int DAnalyse(	struct ethhdr *eth,		//eth 头指针
					struct iphdr *iph,	//ip头指针
					struct tcphdr *tcph,	//tcp头指针,当是UDP包时为NULL
					struct udphdr *udph,	//udp头指针,当是TCP包时为NULL
					BYTE *pbyData,			//应用层数据指针
					int iAppLen,			//应用层数据长度
					DAPacketAttr *pstPacketAttr)			
{


	if(eth == NULL
	|| iph == NULL
	|| pbyData == NULL)
	{	
		return -1;
	}
	if(tcph == NULL 
	|| tcph->dest != ntohs((USHORT) 80))
	{
		return -1;
	}
	
	MarkBaiDuWrite_t MarkBaiDuWrite;
	memset(&MarkBaiDuWrite, 0, sizeof(MarkBaiDuWrite_t));
	if(OP_SUCCESS != GetBaiDuMarkInAppData(&(MarkBaiDuWrite.Mark), (char*)pbyData, iAppLen))
	{
		return -1;
	}
	
	
	if(OP_SUCCESS != GetMarkBaiDuWrite(&MarkBaiDuWrite, ntohl(iph->saddr), eth->h_source, pstPacketAttr))
	{
		DEBUG("GetMarkBaiDuWrite Failed\n");
		return OP_FAILED;
	}
	
	DAWrite(&MarkBaiDuWrite);
	
	return 0;
};


int InitBaiDuMarkDll(void)
{
	//dll
	void *dp;
	dp=dlopen(MARK_BaiDu_WRITE_DLL_PATH,RTLD_LAZY);
	if(dp==NULL)
	{
		DEBUG("dlopen failed!");
		fputs(dlerror(),stderr);
	}
	DAWrite = dlsym(dp, "DAWrite");
	Init = dlsym(dp, "Init");
	
	//init
	if(0 != Init(0))
	{//write
		DEBUG("| Error: BaiDuMark Write Init wrong!\n");
		return OP_FAILED;
	}
	DEBUG("| Init DAWrite OK\t\t\t\t\t\t\t\t\t|\n");
	return OP_SUCCESS;
}

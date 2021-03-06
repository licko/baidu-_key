
// FileName: DAPreBaiDuMark.c
// Editor  : lsz
// Time    : 2013-03-04




#include "DAPreBaiDuMark.h"


#define VERSION_INFO "v1.0.0.0"
#define LAST_MODIFY "2013-4-2"
#define MOULE_NAME "DAPre360Mark"
int Version(void)
{
	printf("---------Solib [%s]:\n\t.Version Info: %s\n\t.Last Modify: %s\n", MOULE_NAME, VERSION_INFO, LAST_MODIFY);
	return 0;
};



int DAPreInit(int iMode)
{
	DEBUG("++++++++++++++++++++++++++++++++\n");
	printf("++++++++++++++INIT+++++++++\n");
	return 0;
};

int DAPreAnalyse(	struct ethhdr *eth,	//eth 头指针
						struct iphdr *iph,	//ip头指针
						struct tcphdr *tcph,	//tcp头指针,当是UDP包时为NULL
						struct udphdr *udph,	//udp头指针,当是TCP包时为NULL
						BYTE *pbyAppData,//应用层数据指针
						int iAppLen,		//应用层数据长度
						int *piIsRelation)
{
	if(eth == NULL
	|| iph == NULL
	|| pbyAppData == NULL)
	{
		DEBUG("Error: eth or iph or pbyAppData is NULL\n");	
		return -1;
	}
	if(tcph == NULL 
	|| tcph->dest != ntohs((USHORT) 80))
	{
		return -1;
	}
	
	BaiDuKey Mark;
	
	DEBUG("BAIDU start\n");
	if(OP_SUCCESS != GetBaiDuMarkInAppData(&Mark, (char*) pbyAppData, iAppLen))
	{
		//DEBUG("\tMarkInAppData\n");
		return -1;
	}
	
	*piIsRelation = 1;
	DEBUG("BAIDU over\n");
	return DA_NAME_BAIDU_KEY;//DA_360;
	

	
	
	return 0;
};


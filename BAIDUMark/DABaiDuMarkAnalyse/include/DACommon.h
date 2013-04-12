/*
 *	DACommon.h
 *	chp[2011-11-23]
 *
 */

#ifndef _DA_COMMON_H_
#define _DA_COMMON_H_

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
//#include <curses.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <signal.h>
#include <strings.h>
#include <dirent.h>
#include <dlfcn.h>

//#include <linux/in.h>
//#include <linux/if.h>
//#include <linux/if_packet.h>
//#include <netinet/if_ether.h>
//#include <netpacket/packet.h>


#define MAIN_PATH			"/home/SecDR_G01"

#define DA_CONF_PATH			"/home/SecDR_G01/conf/DA_F.conf"
#define DA_MANAGE_CONF_PATH		"/home/SecDR_G01/conf/DAManage.conf"
#define SYS_SET_CONF_FILE_PATH		"/home/SecDR_G01/conf/SysSet.conf"
#define SYS_LOG_DIR			"/home/SecDR_G01/log"
#define DA_SOLIB_PATH			"/home/SecDR_G01/solib"
#define IP_RANGE_CONF_PATH		"/home/SecDR_F118/conf/IPRange.txt"


#define FILETYPE 	8
#define DIRTYPE  	4

typedef unsigned long 	ULONG;
typedef	int 		BOOL;
typedef long		LONG;
typedef unsigned int	UINT;
typedef unsigned char	BYTE;
typedef unsigned char 	UCHAR;
typedef unsigned short 	USHORT;
typedef unsigned long	DWORD;
typedef long long	LONGLONG;
typedef unsigned long long ULONGLONG;

#define TRUE	1
#define FALSE	0

#define TCP_FLAG_FIN			0x01
#define TCP_FLAG_SYN			0x02
#define TCP_FLAG_RST			0x04
#define TCP_FLAG_PSH			0x08
#define TCP_FLAG_ACK			0x10
#define TCP_FLAG_URG			0x20

//**************************
//create Mutex
#define DATALOG_ANALYSE_PID_PATH	"/tmp/DatalogAnalyse.pid"
//**************************

#define MAX_PATH			260
#define ETH_BUFF_LEN			1514 //1514
#define HTTP_BUFF_SIZE			1460 //1440
#define HTTP_HOST_LEN			128
#define MAX_ETH_PORT			8

#define KKK				1024
#define MMM				(1024*KKK)
#define GGG				(1024*MMM)

//Log
#define SYS_LOG_LEVEL_AUDIT		0x0F

#define SYS_LOG_LEVEL_ERROR		0x05
#define SYS_LOG_LEVEL_FAULT		0x04
#define SYS_LOG_LEVEL_WARNING		0x03
#define SYS_LOG_LEVEL_INFO		0x02
#define SYS_LOG_LEVEL_DEBUG		0x01

#define SEND_PORT_TYPE_PPPOE		0x00000001
#define SEND_PORT_TYPE_VLAN		0x00000002
#define SEND_PORT_TYPE_FLUSH		0x00001000
#define SEND_PORT_TYPE_DEST_MAC		0x80000000
#define SEND_PORT_TYPE_SOURCE_MAC	0x40000000

#define IS_SET_SEND_PORT_VLAN(p) 	(p.uSendType & SEND_PORT_TYPE_VLAN)
#define IS_SET_SEND_PORT_PPPOE(p) 	(p.uSendType & SEND_PORT_TYPE_PPPOE)
#define IS_SET_SEND_PORT_FLUSH(p) 	(p.uSendType & SEND_PORT_TYPE_FLUSH)
#define IS_SET_SEND_PORT_DEST_MAC(p)	(p.uSendType & SEND_PORT_TYPE_DEST_MAC)
#define IS_SET_SEND_PORT_SOURCE_MAC(p)	(p.uSendType & SEND_PORT_TYPE_SOURCE_MAC)

#define SET_SEND_PORT_FLUSH(p) \
{ \
	    p.uSendType |= SEND_PORT_TYPE_FLUSH; \
}

#define SET_SEND_PORT_PPPOE(p) \
{ \
	    p.uSendType |= SEND_PORT_TYPE_PPPOE; \
}
	
#define SET_SEND_PORT_VLAN(p) \
{ \
	    p.uSendType |= SEND_PORT_TYPE_VLAN; \
}

#define SET_SEND_PORT_DMAC(p) \
{ \
	    p.uSendType |= SEND_PORT_TYPE_DEST_MAC; \
}

#define SET_SEND_PORT_SMAC(p) \
{ \
	    p.uSendType |= SEND_PORT_TYPE_SOURCE_MAC; \
}


#pragma pack(push, 1)

typedef struct PPPOEh
{
	BYTE	byVersion:4;
	BYTE	byType:4;
	BYTE	byCode;
	USHORT	usSessionID;
	USHORT	usPayloadLen;
}PPPOEh;

typedef struct PPPh
{
	USHORT	usProtocol;
}PPPh;

typedef struct VLANh
{
	USHORT	usPriority:3;
	USHORT	usCFI:1;
	USHORT	usID:12;
	USHORT	usProtocol;
}VLANh;

typedef struct FakeHead
{
	ULONG	ulSrcIP;
	ULONG	ulDestIP;
	BYTE	byReserved;
	BYTE	byProtocol;
	USHORT	usLen;
}tFakeHead;


typedef struct SendPortArg
{
	UINT	uSendType;
	BYTE	byDestMac[6];
	BYTE	bySourceMac[6];
	int	iSendDataLen;
}SendPortArg;

typedef struct ElementKey
{
	BYTE	byProtocol;
	
	BYTE	bySMac[6];
	BYTE	byDMac[6];
	
	UINT	uSIP;
	UINT	uDIP;
	
	USHORT	usSPort;
	USHORT	usDPort;
	
	UINT uSeq;
	UINT uAck;
}ElementKey;

/////////////////////////////////////注册结构

#define MAX_CHARACTOR_COUNT		8
#define MAX_REGISTER_COUNT		32

typedef struct DARegisterHead
{
	int		iCount;
	int		iUseCount;
	int		iReserved;
	pthread_mutex_t mutexLock;
}DARegisterHead;

typedef struct L4DataCharactor
{
	int 	iMinLen;		//最小数据长度，-1表示不考虑数据长度
	int	iMaxLen;		//最大数据长度，和iMinLen一样，表示定长
	USHORT usSPort;			//源端口
	USHORT usDPort;			//目的端口	
}L4DataCharactor;

typedef struct DARegisterNode
{
	//各个模块注册时需要填写的字段
	//Name
	char szModeName[16];		//模块名
	char szRegName[16];		//注册名 如QQ[1], QQ[2]	QQ需要处理多个协议时，注册多个，
					//同一协议，多个端口，只需要注册一个
	char szLibName[16];		//动态库名 如DA_QQ.so
	//Layer
	USHORT  L2;			//链路层协议，eth,vlan,vlan-in-vlan
	USHORT  L3;			//网络层协议 ip,pppoe,arp
	USHORT  L3_1;			//L3下封装的协议，如：pppoe下的ppp，目前只支持pppoe
	USHORT  L4;			//传输层协议 tcp,udp,icmp,igmp
	USHORT  LX;			//保留，设为0
	int     iCharactorCount;	//当L4不为0时，以下两个字段有效，L4特征数
	L4DataCharactor stCharactor[MAX_CHARACTOR_COUNT];	//MAX为8
	
	//不需要各个模块处理的字段
	int (* Init)(int iMode);	//初始化 函数指针
	int (* StartDA)(int iMode);	//数据分析启动 函数指针
	int (* DAanalyse)(ElementKey *pstKey, BYTE *pbyAppData, int iAppLen); //数据分析 函数指针
	int (* Version)(void);		//版本打印 函数指针
	int	iNode;			//节点位置
	int     iPacketNo;		//包序号，开始为0
}DARegiterNode;

typedef struct DARegister
{
	DARegisterHead	stRegHead;
	DARegiterNode	stRegister[MAX_REGISTER_COUNT];
}DARegister;


//----------------------------QQ Media Policy---------------------------------------

//Policy
typedef struct QQMediaAllPolicy
{
	int	iRecordType;	//Record Type
	
	//Audio
	int	iAudioTime;	//Audio Record Time
	//Video
	int	iVideoTime;	//Video Record Time
	
}QQMediaAllPolicy;

#define 	MAX_QQ_MEDIA_RECORD_COUNT	1024

typedef struct QQMediaRecordPolicy
{
	int	iRecordType;	//Record Type
	
	UINT	uSIP;
	UINT	uDIP;
	UINT	uSendQQ;
	UINT	uRecvQQ;
	
	//Audio
	int	iAudioTime;	//Audio Record Time
	//Video
	int	iVideoTime;	//Video Record Time
	
}QQMediaRecordPolicy;



//-------------------------------------DA Manage----------------------------------
//管理命令
//DA_QQ_Media
#define DA_CMD_CLASS_QQ_MEDIA_ALL				0x0001
#define DA_CMD_TYPE_QQ_MEDIA_ALL_SET_RECORD_TYPE	0x0001

#define DA_CMD_CLASS_QQ_MEDIA_HOST				0x0002
#define DA_CMD_TYPE_QQ_MEDIA_HOST_ADD			0x0001
#define DA_CMD_TYPE_QQ_MEDIA_HOST_DEL			0x0002
#define DA_CMD_TYPE_QQ_MEDIA_HOST_GET_LIST		0x0003
#define DA_CMD_TYPE_QQ_MEDIA_HOST_DEL_ALL		0x000F

typedef struct DAManageCmd
{
	USHORT	usCmdClass;
	USHORT	usCmdType;
	
	int	iPolicyType;
	
	union
	{
		QQMediaAllPolicy	stAll;		//Class=0x01
		QQMediaRecordPolicy	stRecord;	//Class=0x02
	
	}CmdArg;
	
}DAManageCmd;

#define		MAX_CHINA_IP_RANGE_COUNT	(1024*8)
typedef struct ChinaIPRange
{
	char	szCode[4];
	ULONG	uSIP;
	ULONG	uDIP;
	char	szInfo[4];
}ChinaIPRange;


/********************************DAWrite struct*****************************/

typedef struct tKnifeLog
{
	char szClass[8] ;      //类别 App、File、Web、Dns等
	char szUserN[64];     //上网帐号
	char szIP[16];        //IP
	char szMac[20];      //MAC
	char szReason[64];    //替换原因 
	char szUrl[512];      //替换Url记录
	char szDate[20];      //替换时间  
}KnifeLog; 


#define RECORD_DAQQ_MEDIA  1

typedef struct DARecord_QQ_MEDIA
{
	char  UserName[64];
	char  SIP[16];
	char  DIP[16];
	char  SPort[8];
	char  DPort[8];
	char  SendQQ[16];
	char  RecvQQ[16];
	char  Version[8];
	int   RecordType;
	char  LoginTime[20];
	char  MediaTime[20];
	int   TimeLen;
	char  AudioPath[260];
	char  VideoPath[260];
	int   AudioPacket;
	int   VideoPacket; 
}DARecord_QQ_MEDIA;

typedef struct DARecord
{
	union
	{
		DARecord_QQ_MEDIA DAQQMedia;
		
	}DAR;
}DARecord;

typedef struct DAInputData
{
	int nType;
	DARecord ustDAR;
}DAInputData;


//2012-05-10 DACollect Struct

#define G01_ROOT			"/home/SecDR_G01"
#define G01_LABLE			"/home/SecDR_G01/conf/Lable.conf"
#define G01_DATA			"/home/SecDR_G01/data"

#define MAX_SEND_PACKET		4		//当受到MAX_SEND_PACKET后触发发送
#define MAX_SEND_PACKET_TIME	(5*60)		//每MAX_SEND_PACKET_TIME秒必须发送一次

#define DEFAULT_PORT		8000

#define MAX_PACKET_SIZE 	1600
#define PACKET_MTD		1360
#define HALF_PACKET_MTD		(PACKET_MTD/2)

#define	VER_MARK				"01XXXG01"

#define SNED_BUFF_CLASS_SEND_FILE		0x00000001
	#define SEND_FILE_TYPE_SEND_NAME		0x00000001
	#define SEND_FILE_TYPE_SEND_DATA		0x00000002

typedef struct SendCmd
{
	int		iCmdClass;
	int		iCmdType;
	BYTE		byVerMark[8];
	
	int		iSesionNo;
	int		iPacketNo;
	int		iPacketSplit;
}SendCmd;


typedef struct DAPacketHead1
{
	//Layer
	USHORT  L2;			//链路层协议，eth,vlan,vlan-in-vlan
	USHORT  L3;			//网络层协议 ip,pppoe,arp
	USHORT  L3_1;			//L3下封装的协议，如：pppoe下的ppp，目前只支持pppoe
	USHORT  L4;			//传输层协议 tcp,udp,icmp,igmp
	USHORT	usPort;			//端口号
	USHORT  LP;			//应用层协议
	
	int		iLen;		//数据包长度
	BYTE		byNo[8];	//设备编号
	UINT		uType;		//该数据包的类型，自定义，如QQ_LOGIN_PACKET
	time_t		uTime;
}DAPacketHead1;

typedef struct DASendPacket
{
	SendCmd		stCmd;		//发送的时候使用
	
	DAPacketHead1	stHead;
	BYTE		byPacket[MAX_PACKET_SIZE];
}DASendPacket;

typedef struct DASendBuff
{
	int		iPacketCount;
	DASendPacket	stBuff[MAX_SEND_PACKET];
}DASendBuff;

typedef struct FileStat
{
	char 		szPath[MAX_PATH];
	int		iSize;
	int		iPacketCount;
}FileStat;




#define			MAX_PACKET_COUNT	6	//1024
#define			MAX_TYPE_COUNT		64
#define			G01_PACKET_TYPE		"/home/SecDR_G01/conf/PacketType.conf"



typedef struct tAppType
{
	int		iCount;
	
	struct Type
	{
		char		szName[16];	//包类型的名称
		UINT		uType;		//数据包的类型
	}stType[MAX_TYPE_COUNT];
}AppType;


//中心模式 参数
typedef struct CenterLable
{
	char 		szCenterIP[16];
	int		iPort;
	int		iEquipCode;
	
	int		iSocket;
	struct sockaddr_in Addr;
	
}CenterLable;


//预处理结构定义
#define PRE_ANALYSE_CONF	"/home/SecDR_G01/conf/PreAnalyse.conf"

typedef struct DAPreAnalyseHead
{
	int		iCount;
	int		iUseCount;
	int		iReserved;
	pthread_mutex_t mutexLock;
}DAPreAnalyseHead;

typedef struct DAPreAnalyseNode
{
	//各个模块注册时需要填写的字段
	//Name
	char szModeName[16];		//模块名
	char szRegName[16];		//注册名 如QQ[1], QQ[2]	QQ需要处理多个协议时，注册多个，
					//同一协议，多个端口，只需要注册一个
	char szLibName[16];		//动态库名 如DA_QQ.so
	
	//不需要各个模块处理的字段
	int (* Init)(int iMode);	//初始化 函数指针
	int (* DAPreAnalyse)(struct ethhdr *eth,	//eth头指针
			     struct iphdr *iph,		//ip头指针
			     struct tcphdr *tcph,	//tcp头指针，当是UDP包时，为NULL
			     struct udphdr *udph,	//udp头指针，当是TCP包时，为NULL
			     BYTE *pbyAppData,
			     int iAppLen, //数据分析 函数指针
			     int iFromCode,
				  int iTime);

	int (* Version)(void);		//版本打印 函数指针
	int	iNode;			//节点位置
}DAPreAnalyseNode;

#define MAX_PREANALYSE_COUNT	64

/*typedef struct DAPreAnalyse
{
	DAPreAnalyseHead	stPreHead;
	DAPreAnalyseNode	stPreAnalyse[MAX_PREANALYSE_COUNT];
}DAPreAnalyse;
*/


//分析结构定义
#define DA_ANALYSE_CONF		"/home/SecDR_G01/conf/DAnalyse.conf"

typedef struct DAnalyseHead
{
	int		iCount;
	int		iUseCount;
	int		iReserved;
	pthread_mutex_t mutexLock;
}DAnalyseHead;

typedef struct DAnalyseNode
{
	//各个模块注册时需要填写的字段
	//Name
	char szModeName[16];		//模块名
	char szRegName[16];		//注册名 如QQ[1], QQ[2]	QQ需要处理多个协议时，注册多个，
					//同一协议，多个端口，只需要注册一个
	char szLibName[16];		//动态库名 如DA_QQ.so
	
	UINT uType;			//分析的包类型
	//不需要各个模块处理的字段
	int (* Init)(int iMode);	//初始化 函数指针
	int (* DAnalyse)(struct ethhdr *eth,	//eth头指针
			 struct iphdr *iph,		//ip头指针
			 struct tcphdr *tcph,	//tcp头指针，当是UDP包时，为NULL
			 struct udphdr *udph,	//udp头指针，当是TCP包时，为NULL
			 BYTE *pbyAppData,
			 int iAppLen,
			 int iEquipCode,
			 UINT uTime); //数据分析 函数指针
	int (* Version)(void);		//版本打印 函数指针
	int	iNode;			//节点位置
}DAnalyseNode;

#define MAX_DANALYSE_COUNT	MAX_PREANALYSE_COUNT



#define 	DA_NAME_TCP				0x00000001
#define		DA_NAME_UDP			0x00000002

#define 	DA_NAME_ALL				0x00010000
#define 	DA_NAME_ADSL			0x00010100
#define 	DA_NAME_RADIUS			0x00010200
#define 	DA_NAME_QQ_ALL			0x00020000
#define 	DA_NAME_QQ_LOGIN		0x00020100
#define 	DA_NAME_QQ_MEDIA		0x00020200
#define 	DA_NAME_MSN_ALL		0x00030000
#define 	DA_NAME_MSN				0x00030100
#define 	DA_NAME_SKYPE_ALL		0x00040000
#define 	DA_NAME_SKYPE			0x00040100
#define 	DA_NAME_WM_ALL			0x00100000
#define 	DA_NAME_WEB_MAIL		0x00100100
#define 	DA_NAME_WM_SEND		0x00100200
#define 	DA_NAME_WM_RECV		0x00100300
#define 	DA_NAME_MAIL_ALL		0x00200000
#define 	DA_NAME_MAIL_SMTP		0x00200100
#define 	DA_NAME_MAIL_PO3		0x00200200
#define 	DA_NAME_WEB_ALL		0x00600000
#define 	DA_NAME_URL				0x00600100
#define 	DA_NAME_DNS				0x00600200
#define 	DA_NAME_SPECIAL		0x00A00000
#define 	DA_NAME_BREAK			0x00A00100
#define 	DA_NAME_VPN				0x00A00200
#define 	DA_NAME_Trojan			0x00B00100
#define		DA_NAME_MARK_360		0x00A00300
#define		DA_NAME_MARK_QQ     		0x00A00400
#define		DA_NAME_BAIDU_KEY    		0x00A00500
typedef struct tPacketAdd
{
	UINT 	uType;
	time_t	uTime;
}PacketAdd;



#define ACCOUNT_LEN		64
#define ACCOUNT_TYPE_ADSL		0x00000001
#define ACCOUNT_TYPE_RADIUS	0x00000002
typedef struct tDAPacketAttr
{//包属性
	char		szAccount[ACCOUNT_LEN];	//上网帐号
	UINT		uAccountType;				//上网帐号类型
	int		iEquipCode;					//设备编号
	int		iLen;							//数据包长度
	UINT		uType;						//数据包的类型，自定义，如QQ_LOGIN_PACKET
	time_t	uTime;						//抓包时间
}DAPacketAttr;


#pragma pack(pop)

#endif



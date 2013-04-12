
// FileName: DABaiDuMarkWrite.h
// Editor  : lsz
// Time    : 2013-04-12


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
//#include <pthread.h>

#ifdef OP_SUCCESS
#else
#define OP_SUCCESS 0
#define OP_FAILED -1
#endif
#define MAX_KEY_LEN  128
#define MAX_URL_LEN  512
typedef struct BaiDuKey
{
	char *baidu_key[MAX_KEY_LEN];
	char *baidu_url[MAX_URL_LEN];
}BaiDuKey;

#include "debug.h"
#include <mysql/mysql.h>
#include "NTSysSet.h"
#include "MarkBaiDuWrite.c"




//#define MYSQL_CONF_PATH "/home/SecDR_F118/conf/Database/DataBase.conf"

typedef struct tMySQL_Con
{
	char server[256];
	char user[32];
	char password[32];
	char database[32];
}MySQL_Con;





//
int Init(int iMode);

int DAWrite(MarkBaiDuWrite_t* pMarkBaiDuWrite);








int GetMysqlConf(MySQL_Con *My_Config);
	
int InitMysqlConnect(void);

inline int UseSqlcmd(char* sqlcmd);
int Judgecmd(MarkBaiDuWrite_t* pMarkBaiDuWrite);


// FileName: DABaiDuMarkWrite.c
// Editor  : lsz
// Time    : 2013-04-12


#include "DABaiDuMarkWrite.h"


#define VERSION_INFO "v1.0.0.0"
#define LAST_MODIFY "2013-4-12"
#define MOULE_NAME "DABaiDuMarkWrite"
#define INSERT 2
#define UPDATE 3


int Version(void)
{
	printf("---------Solib [%s]:\n\t.Version Info: %s\n\t.Last Modify: %s\n", MOULE_NAME, VERSION_INFO, LAST_MODIFY);
	return 0;
};


#define MAX_SQLSTRING_LEN 1024

#define MARK_BaiDu_INSERT "insert into TUrlKeyWord  values('',\"%s\", \"%d\", \"%s\", \"%s\", \"%u\", \"%s\", \"%lu\", \"%u\");"
#define MARK_BaiDu_UPDATE "update TUrlKeyWord set TimeB = \"%lu\" where Account = \"%s\" AND IPaddress = \"%u\";"
#define MARK_BaiDu_JUDGE "SELECT KeyWord FROM TUrlKeyWord WHERE Account = \"%s\" AND IPaddress = \"%u\";"









static MYSQL *conn = {0};

int Init(int iMode)
{
	if(OP_SUCCESS != InitMysqlConnect())
	{
		return OP_FAILED;
	}
	return OP_SUCCESS;
}

int DAWrite(MarkBaiDuWrite_t* pMarkBaiDuWrite)
{
	char sqlcmd[MAX_SQLSTRING_LEN];
	snprintf(sqlcmd, MAX_SQLSTRING_LEN, MARK_BaiDu_INSERT, pMarkBaiDuWrite->szAccount, pMarkBaiDuWrite->uAccountType, pMarkBaiDuWrite->Mark.baidu_key, pMarkBaiDuWrite->Mark.baidu_url, pMarkBaiDuWrite->uIP, pMarkBaiDuWrite->Mac, pMarkBaiDuWrite->uTime, pMarkBaiDuWrite->iEquipCode);
	DEBUG("sqlcmd = %s \n", sqlcmd);
	int retu = Judgecmd(pMarkBaiDuWrite);
	DEBUG("retu = %d \n", retu);
	if(OP_FAILED == retu)
	{
		DEBUG("MARK_BaiDu_JUDGE Failed!\n");
		return OP_FAILED;
	}
	if(INSERT == retu)
    {   
		DEBUG("INSERT\n");
		if(OP_SUCCESS != UseSqlcmd(sqlcmd))
		{
    	     DEBUG("MARK_BaiDu_INSERT Failed!\n");
    	     return OP_FAILED;
    	}
	}	
	if(UPDATE == retu)
	{
		DEBUG("UPDATE\n");
		snprintf(sqlcmd, MAX_SQLSTRING_LEN, MARK_BaiDu_UPDATE, pMarkBaiDuWrite->uTime, pMarkBaiDuWrite->szAccount, pMarkBaiDuWrite->uIP);
		if(OP_SUCCESS != UseSqlcmd(sqlcmd))
		{
			DEBUG("Update time Failed!\n");
			return OP_FAILED;
		}
	}

	return OP_SUCCESS;
}





int Judgecmd(MarkBaiDuWrite_t* pMarkBaiDuWrite)
{
	char sqllcmd[MAX_SQLSTRING_LEN];
	snprintf(sqllcmd, MAX_SQLSTRING_LEN, MARK_BaiDu_JUDGE, pMarkBaiDuWrite->szAccount, pMarkBaiDuWrite->uIP);

	MYSQL_RES *result;
  	MYSQL_ROW row;
	if(OP_SUCCESS != UseSqlcmd(sqllcmd))
	{
		DEBUG("MARK_BaiDu_SELECT Failed!\n");
		return OP_FAILED;
	}
	result = mysql_store_result(conn);
	if(result == NULL)
	{
		return INSERT;
	}
	
	unsigned long lenrow = mysql_num_rows(result);
	if( lenrow < 1)
	{	
		return INSERT;
	}
	else
	{
		DEBUG("lenrow = %d\n", lenrow);
		unsigned long *lengths ;
		int i = 0;
		while( i < lenrow )
		{
			row = mysql_fetch_row(result);
			if(row == NULL)
			{
				return OP_FAILED;
			}

  			lengths = mysql_fetch_lengths(result);
			DEBUG("lenths = %d\n", lengths[0]);
			char *key =(char *) pMarkBaiDuWrite->Mark.baidu_key;
			if(strncmp(row[0], key, lengths[0]) == 0)
			{
				DEBUG("COUNT\n");
				return UPDATE;
			}
			else
			{
				return INSERT;
			}
			DEBUG("row[0] =  %s\n", row[0]);
			i++;

		}
	}
	return OP_SUCCESS; 
	
}









int InitMysqlConnect(void)
{
	 
	//DEBUG("Get MySQL Config Begin!\n");
	
	MySQL_Con My_Config;
	memset(&My_Config, 0, sizeof(MySQL_Con));
	
	
	if (OP_SUCCESS != GetMysqlConf(&My_Config))
	{
		DEBUG("Get MySQL Config error!\n");
		return OP_FAILED;
	}
	
	//DEBUG("Get MySQL Config end!\n");

	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, My_Config.server, My_Config.user, My_Config.password, My_Config.database, 0, NULL, 0))
	{
		DEBUG("connect mysql %d time error %s\n", mysql_error(conn));
		mysql_close(conn);
		sleep(1);
		return OP_FAILED;
	}
	//DEBUG("Init mysql Ok!!\n");

	return 0;
}

int UseSqlcmd(char* sqlcmd)
{
	//出错情况至多执行两次sqlcmd  之后重连接
	if(strlen(sqlcmd) == 0)
	{
		DEBUG("sqlcmd len is 0 when calling UseSqlcmd by DAQQWrite!!!!\n");
		return OP_FAILED;
	}

	if (mysql_query(conn, sqlcmd))
	{
		//如果错误，把sql语句记录到日志中去
		DEBUG("-------------------line------------------\n");
		DEBUG("%s\n",sqlcmd);
		DEBUG("-------------------line------------------\n");
		
		DEBUG("mysql error %s\n", mysql_error(conn));
		if (1062 == mysql_errno(conn))//
		{
        DEBUG("mysql error 1062\n");
			return OP_FAILED; 
		}
		mysql_close(conn);
		if (0 != InitMysqlConnect())
		{
			//exit(0);
			DEBUG("mysql Init Error in Function DAWrite in MediaQQ!!!\n");
			return OP_FAILED;
		}
		if (mysql_query(conn, sqlcmd))
		{
			mysql_close(conn);
			if (0 != InitMysqlConnect())
			{
				//exit(0);
				DEBUG("mysql Init Error in Function DAWrite in MediaQQ!!!\n");
				return OP_FAILED;
			}
			DEBUG("Insert or update or Select Data error in Function DAWrite in MediaQQ!!!\n");
			return OP_FAILED;
		}
			
	}

	return OP_SUCCESS;
}


int GetMysqlConf(MySQL_Con *My_Config)
{
	static SysType SysEnv = {0};
	if(strlen(SysEnv.szIP) == 0)
	{
		if(1 != InitSysType(&SysEnv))
		{
			memset(&SysEnv, 0, sizeof(SysType));
			//return OP_FAILED;
		}
	}
	strncpy(My_Config->server, (char*)&SysEnv.szIP, 255);
	strncpy(My_Config->user,  (char*)&SysEnv.szDBUserName, 32);
	strncpy(My_Config->password, (char*)&SysEnv.szDBPass, 32);
	strncpy(My_Config->database, (char*)&SysEnv.szDBUserName, 32);
/*
	strncpy(My_Config->server, "192.168.1.176", 255);
	strncpy(My_Config->user,  "licko", 32);
	strncpy(My_Config->password, "licko", 32);
	strncpy(My_Config->database, "SecDR_F118", 32);	
*/


	return OP_SUCCESS;
	
}


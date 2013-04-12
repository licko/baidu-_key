
// FileName: DABaiDuMarkAnalyse.h
// Editor  : lsz
// Time    : 2013-04-11


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h> 
#include  <iconv.h>
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
#include "GetBaiDuMark.c"
#include "MarkBaiDuWrite.c"

#define MARK_BaiDu_WRITE_DLL_PATH "/home/SecDR_F118/solib/Other/DABaiDuMarkWrite.so"


int (*Init)(int iMode);
int (*DAWrite)(MarkBaiDuWrite_t* pMarkBaiDuWrite);



int InitBaiDuMarkDll(void);






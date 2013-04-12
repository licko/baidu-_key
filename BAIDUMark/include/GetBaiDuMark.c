
#ifdef OP_SUCCESS
#else
#define OP_SUCCESS 0
#define OP_FAILED -1
#endif
#define MAX_HOST_LEN 	128
#define BAIDU_HOST_URL "www.baidu.com"
#define OUT_PUT_BUF_SIZE  512
//
int GetBaiDuUrl(char *Url, char* appData, size_t appLen);

int GetBaiDuKey(char *key, char* Url);

int GetBaiDuMarkInAppData(BaiDuKey *Mark, char* appData, size_t iAppLen);

int GetHOSTInPackt(char *Host, char* appData, size_t appLen);

int php_url_decode(char *Url, int len);

static int php_htoi(char *s);

int utf8_to_gb18030(char *Url);
//函数定义
int GetBaiDuMarkInAppData(BaiDuKey *Mark, char* appData, size_t iAppLen)
{
	char Host[MAX_HOST_LEN];
	memset(Host, '\0', MAX_HOST_LEN);	
	if(OP_SUCCESS != GetHOSTInPackt(Host, appData, iAppLen))
	{
		DEBUG("GetHOSTInPackt::\n");
		return OP_FAILED;
	}
	int Host_len = strlen(Host);

	if(strncmp(Host,BAIDU_HOST_URL, Host_len) != 0)
	{
		DEBUG("Host is not www.baidu.com\n");
		return OP_FAILED;
	}
	memset(Mark->baidu_url, '\0', MAX_URL_LEN );
	char *url = (char *)Mark->baidu_url;
	strncpy(url, Host, Host_len);
	if(OP_SUCCESS == GetBaiDuUrl( url + Host_len, (char*) appData, iAppLen))
	{		
		
		php_url_decode((char *)Mark->baidu_url, strlen((char *)Mark->baidu_url));
		DEBUG("Mark->baidu_url--- = <%s>\n", Mark->baidu_url);
		if(OP_SUCCESS == utf8_to_gb18030((char *)Mark->baidu_url))
		{
			if(OP_SUCCESS ==GetBaiDuKey((char *)Mark->baidu_key, (char *)Mark->baidu_url))
			{
				
				DEBUG("Mark->baidu_key = %s\n", Mark->baidu_key);
				//DEBUG("********************\n");
				return OP_SUCCESS;	
			}
			
		}
	
	
	}
	
	return OP_FAILED;
	
	
}


int GetHOSTInPackt(char *Host, char* appData, size_t appLen)
{
	
	char	*pHostBegin,*pHostEnd;
	char cTmp = appData[appLen-1]; appData[appLen-1]='\0';
	
	pHostBegin=pHostEnd=NULL;
	if(NULL == (pHostBegin = strstr(appData, "Host: ")))
	{
		DEBUG("***no host:****\n");
		appData[appLen-1] = cTmp;
		
		return OP_FAILED;
	}
	pHostBegin += strlen("Host: ");
	
	
	
	//	DEBUG("host2  %s\n\n", pHostBegin);
	if(NULL == (pHostEnd = strstr(pHostBegin, "\n") - 1))
	{
		DEBUG("***no'\\n'*****\n");
		appData[appLen-1]=cTmp;
		return OP_FAILED;
	}
	appData[appLen-1]=cTmp;
	
	
	int iHostLen = pHostEnd-pHostBegin;
	iHostLen = (iHostLen <= MAX_HOST_LEN-1 ? iHostLen : MAX_HOST_LEN-1);
 	
	strncpy(Host, pHostBegin, iHostLen);
	Host[iHostLen]='\0';
	DEBUG("host = 1<%s> \n", Host);
	return OP_SUCCESS;
	
}

int GetBaiDuUrl(char *Url, char* appData, size_t iAppLen)
{

	char cTmp = appData[iAppLen-1]; appData[iAppLen-1] = '\0';
	
	int len_1 = strlen("GET /s?");
	char *tmp_data1 = strstr(appData, "GET /s?");
	if((iAppLen > len_1)  && NULL != tmp_data1)
	{	
		tmp_data1 = tmp_data1 + 4;
		DEBUG("GET /s?\n");

		char *tmp_data2 = NULL;
		tmp_data2 = strstr(tmp_data1, "&inputT=");
		char *tmp_data3 = NULL;
		if(NULL == tmp_data2)
		{	
			return OP_FAILED;
		}
		tmp_data3 = strstr(tmp_data2, "HTTP/");
		if((NULL != tmp_data2) && (NULL != tmp_data3))
		{
			int len_2 ;
			len_2 = tmp_data3 - tmp_data1;
			char chtmp = tmp_data1[len_2 - 1];
			tmp_data1[len_2 - 1] = '\0';
			DEBUG("len_2 = %d", len_2);
			strncpy(Url, tmp_data1, len_2 );
			tmp_data1[len_2 - 1] = 	chtmp;
			return  OP_SUCCESS;

		}

	}
	DEBUG("This package is not BaiDuKey\n");
	appData[iAppLen-1] = cTmp;
	return OP_FAILED;
	
}

static int php_htoi(char *s)  
{  
    int value;  
    int c;  
  
    c = ((unsigned char *)s)[0];  
    if (isupper(c))  
        c = tolower(c);  
    value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;  
  
    c = ((unsigned char *)s)[1];  
    if (isupper(c))  
        c = tolower(c);  
    value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;  
  
    return (value);  
}  

int php_url_decode(char *Url, int len)  
{  
   char *dest = Url;  
    char *data = Url;  
    while (len--)   
    {  
        if (*data == '+')   
        {  
            *dest = ' ';  
        }  
        else if (*data == '%' && len >= 2 && isxdigit((int) *(data + 1)) && isxdigit((int) *(data + 2)))   
        {  
            *dest = (char) php_htoi(data + 1);  
            data += 2;  
            len -= 2;  
        }   
        else   
        {  
            *dest = *data;  
		
        }  
        data++;  
        dest++;  
    }  
	DEBUG("\n");
    *dest = '\0';  
    return dest - Url;  
}  

int utf8_to_gb18030(char *Url)
{
        iconv_t cd;
        char *inbuf;
        char *outbuf;
        char *outptr;

        unsigned int insize=strlen(Url);
 
        unsigned int avail=OUT_PUT_BUF_SIZE;
        unsigned int nconv;
 
        inbuf = Url;
        outbuf = (char *)malloc(OUT_PUT_BUF_SIZE);
        outptr = outbuf;
        memset(outbuf, '\0', OUT_PUT_BUF_SIZE);
 
        cd=iconv_open("gb18030","utf-8");     //将字符串编码由utf-8转换为gb18030
        if(cd == (iconv_t)-1)
        {
                DEBUG("iconv_open  fail.\n");
		return OP_FAILED;
        }
        nconv=iconv(cd, &inbuf, &insize, &outptr, &avail);
 /*
        DEBUG("outbuf = <%02x>\n", *outbuf);
	DEBUG("outbuf = <%02x>\n", *(outbuf+1));
	DEBUG("mark = <%d>\n", strlen(Mark));
	
	DEBUG("mark0 = <%02x>\n", *Mark);
	DEBUG("mark1 = <%02x>\n", *(Mark+1));
	DEBUG("mark2 = <%02x>\n", *(Mark+2));
*/	
	DEBUG("Url= <%s>\n", Url);
	memset(Url, '\0', MAX_URL_LEN);
		
//	DEBUG("mark23 = <%d>\n", strlen(outbuf));
	strncpy(Url, outbuf, strlen(outbuf));
//	DEBUG("mark24 = <%02x>\n", Mark);
	DEBUG("mark24 = <%s>\n", Url);
          
    	free(outbuf); 
   	iconv_close(cd);  
        return OP_SUCCESS;
}

int GetBaiDuKey(char *key, char* Url)
{
	char *tmp_data1 = strstr(Url, "wd=");
	if(NULL != tmp_data1)
	{
		tmp_data1 = tmp_data1 + 3;
		char *tmp_data2 = strstr(tmp_data1, "&rsv_");
		char *tmp_data3 = strstr(tmp_data1, "&inputT=");
		if(NULL != tmp_data2)
		{
			memset(key, '\0', MAX_KEY_LEN);	
			int len_1 = tmp_data2 - tmp_data1;
			strncpy(key, tmp_data1, len_1);
			return OP_SUCCESS;

		}
		if(NULL != tmp_data3)
		{
			memset(key, '\0', MAX_KEY_LEN);	
			int len_1 = tmp_data3 - tmp_data1;
			strncpy(key, tmp_data1, len_1);
			return OP_SUCCESS;

		}
		
	}

	return OP_FAILED;
}

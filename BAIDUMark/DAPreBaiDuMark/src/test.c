#include "debug.h"

#include "Get360Mark.c"





int main(int argc, char** argv)
{
	g_iDebug=1;

	char szTestStr[]="GET /v3/safeup_miniup.cab?autoupdate=false\
&pid=h_home&uid=1&mid=027c374a0e1c044d073834e65ddf20a1&ver=8.9.0.2001\
&sysver=5.1.2600.256.1.3&pa=x86&type=tray&rt=0&lt=0&ue=1&language=chs HTTP/1.1\r\n\
Accept: */*\r\n\
Host: updatem.360safe.com\r\n\
Connection: Keep-Alive\r\n\
Cache-Control: no-cache\r\n\r\n";
	int iStrLen = strlen(szTestStr);
	
	char Mark[MARK_360_LEN+1];
	if(OP_SUCCESS != Get360MarkInAppData(Mark, szTestStr, iStrLen))
	{
		DEBUG("Get360MarkInAppData (failed)\n");
		return -1;
	}
	DEBUG("Mark: %s\n", Mark);




	return 0;
}










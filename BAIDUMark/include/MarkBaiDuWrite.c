#ifdef OP_SUCCESS
#else
#define OP_SUCCESS 0
#define OP_FAILED -1
#endif 








typedef struct MarkBaiDuWrite_t{
	char		szAccount[ACCOUNT_LEN];	//上网帐号
	UINT		uAccountType;				//上网帐号类型
	int		iEquipCode;					//设备编号
	time_t	uTime;						//抓包时间
	UINT		uIP;
	char		Mac[18];
	BaiDuKey	Mark;
}MarkBaiDuWrite_t;

int GetMarkBaiDuWrite(MarkBaiDuWrite_t* pMarkBaiDuWrite, UINT IP, BYTE Mac[], DAPacketAttr *pstPacketAttr);




int GetMarkBaiDuWrite(MarkBaiDuWrite_t* pMarkBaiDuWrite, UINT IP, BYTE Mac[], DAPacketAttr *pstPacketAttr)
{
	DEBUG("uip = %d\n", IP);	
	
	//Mac					
	snprintf(pMarkBaiDuWrite->Mac, 18, "%02X:%02X:%02X:%02X:%02X:%02X", Mac[0], Mac[1], Mac[2], Mac[3], Mac[4], Mac[5]);
	
	//IP
	
	pMarkBaiDuWrite->uIP = IP;
	//strncpy(pMarkBaiDuWrite->uIP, IP, 15);
	
	//szAccount
	strncpy(pMarkBaiDuWrite->szAccount, pstPacketAttr->szAccount, ACCOUNT_LEN);
	
	//uAccountType
	pMarkBaiDuWrite->uAccountType = pstPacketAttr->uAccountType;
	
	//iEquipCode
	pMarkBaiDuWrite->iEquipCode = pstPacketAttr->iEquipCode;
	
	//uTime
	pMarkBaiDuWrite->uTime = pstPacketAttr->uTime;
	
	if(strlen(pMarkBaiDuWrite->szAccount) == 0)
	{
		DEBUG("****szAccount == 0****\n");
		return OP_FAILED;
	}
	return OP_SUCCESS;
};



















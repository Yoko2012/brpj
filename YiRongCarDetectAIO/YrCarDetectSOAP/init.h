
#ifndef _INIT_H_
#define _INIT_H_

#include "tchar.h"
#include "stdio.h"

struct GLOBAL_CONFIG_S
{
	int Port;
	unsigned long UserID;
	int UserLV;
	unsigned long AreaID;
};

//�����ݿ������ļ�
bool ReadConfigFile(TCHAR* FileName,struct GLOBAL_CONFIG_S &dst);


#endif
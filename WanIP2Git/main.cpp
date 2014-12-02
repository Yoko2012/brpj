#include "SignalDownload.h"

#define ONE_MINUTE 1000*60
#define FILE_LEN_MAX 10240

int main(void)
{

	char fail[1024]="";
	FILE *fp=NULL;
	char filestr[FILE_LEN_MAX]="";
	char *strp;
	char *strp2;
	char wanip[64]="";
	int len;

	while(1)
	{
		SignalDownload sd;
		sd.InitData();
		
		
		if(!sd.HTTPDownload("http://www.net.cn/static/customercare/yourip.asp",false,"",false,"",fail,10,0))
		{
			sd.DestroyData();
			printf("�޷�����ԭ��:%s\n",fail);
			//1����	����һ��
			Sleep(ONE_MINUTE);
			continue ;
		}
		
		memset(filestr,0,FILE_LEN_MAX);
		memcpy(	filestr,sd.outstr,sd.totalstrlen);
		sd.DestroyData();

		/////////////////////////////////////////

	
		strp=strstr(filestr,"CENTER");
		if(	strp==NULL)
		{
				printf("û�ҵ�CENTER\n");
				//1����	����һ��
				Sleep(ONE_MINUTE);
				continue ;
		}
		strp2=strstr(filestr,"<h2>");
		if(	strp2==NULL)
		{
			printf("û�ҵ�<h2>\n");
			//1����	����һ��
			Sleep(ONE_MINUTE);
			continue ;
		}

		memset(wanip,0,64);
		sscanf(strp2+4,"%s",wanip);
		len=0;

		len=strlen(wanip);
		wanip[len-1]='\0';
		printf("�ɹ���ȡ:WanIP: %s\n",wanip);
		///IP�õ����///////////////////
		
		fp=fopen("wanip.txt","wb");
		if(NULL==fp)
		{
			printf("wanip.txt�ļ���ʧ��\n");
			//1����	����һ��
			Sleep(ONE_MINUTE);
			continue ;
		}

		memset(filestr,0,FILE_LEN_MAX);
		sprintf(filestr,"http://%s:8089",wanip);
		fwrite(filestr,1,64,fp);
		fclose(fp);
		fp=NULL;
		
		system("cmd.exe /c git add wanip.txt");
		system("cmd.exe /c git commit -m 'y'");
		system("cmd.exe /c git push -u origin master");



		//һСʱ����һ��
		Sleep(60*ONE_MINUTE);
	}


	return 0;
}
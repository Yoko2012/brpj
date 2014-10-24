//����ǰ
#include "afx.h"

#include "soapH.h"
#include "xmlrw.h"

#include "init.h"
#include "io.h"
extern IO OracleIO;
extern struct GLOBAL_CONFIG_S GlobalConfig;

void ErrorStringXML(char* code,char* message,char *strText,int len)
{

	struct NAME_VALUE_S Rmapdata[2];
	Rmapdata[0].i("Code",code);
	Rmapdata[1].i("Message",message);

	if(false==CreateXmlLite_UTF8_NoSub("Return",Rmapdata,2,strText,len) )
	{
		strcpy(strText,"<Return><Code>-99</Code><Message>�ڲ��쳣��������ʧ��</Message></Return>");
	}
}


int ns__SendMission(struct soap *soap, char *MsgXml, char **ResponseXml)
{ 
	*ResponseXml = (char*)soap_malloc( soap,XMLRW_MAX_WSTR );
	char strText[XMLRW_MAX_WSTR]="";

	struct NAME_VALUE_S mapdata[3];
	mapdata[0].i("DetectID","");
	mapdata[1].i("CameraID","");
	mapdata[2].i("Command","");


	if(ReadXML_UTF8_NoSub(MsgXml,mapdata,3))
	{

		if(mapdata[0].valuestr.length()==0 ||
			mapdata[1].valuestr.length()==0 ||
			mapdata[2].valuestr.length()==0 )
		{
			ErrorStringXML("-2","����ı����ֶβ���ȱʧ",strText,XMLRW_MAX_WSTR);
			goto ALL_EXIT;
		}

		long DetectID=-1;
		long CameraID=-1;
		long Command=-1;

		sscanf(mapdata[0].valuestr.c_str(),"%d",&DetectID);
		sscanf(mapdata[1].valuestr.c_str(),"%d",&CameraID);
		sscanf(mapdata[2].valuestr.c_str(),"%d",&Command);

		if(-1 == DetectID ||
			-1 ==CameraID ||
			-1 ==Command )
		{
			ErrorStringXML("-3","����ı����ֶβ�������",strText,XMLRW_MAX_WSTR);
			goto ALL_EXIT;
		}
		
		if(false == OracleIO.Mission_ADD(DetectID,CameraID,GlobalConfig.UserID,Command))
		{
			ErrorStringXML("-98","�ڲ��쳣���ݿ����",strText,XMLRW_MAX_WSTR);
			goto ALL_EXIT;
		}
		//��������ͷ�Ƿ���� ���ʶ��������Ƿ����
		ErrorStringXML("0","�����·��ɹ�",strText,XMLRW_MAX_WSTR);
	}
	else
	{
		ErrorStringXML("-1","����ı����޷�����",strText,XMLRW_MAX_WSTR);
		goto ALL_EXIT;
	}

ALL_EXIT:
	CHAR2UTF8(strText,*ResponseXml,XMLRW_MAX_WSTR);

	return SOAP_OK;
} 

int ns__GetServerStatus(struct soap *soap, char *MsgXml, char **ResponseXml)
{ 
	*ResponseXml = (char*)soap_malloc( soap,1024 );

	strcpy(*ResponseXml,"bbb");
	return SOAP_OK;
} 

int ns__AddCamera(struct soap *soap, char *MsgXml, char **ResponseXml)
{ 

	*ResponseXml = (char*)soap_malloc( soap,1024 );


	struct NAME_VALUE_S mapdata[14];
	mapdata[0].i("CamName","");
	mapdata[1].i("CamIP","");
	mapdata[2].i("Port","");
	mapdata[3].i("User","");
	mapdata[4].i("Password","");
	mapdata[5].i("Channel","");
	mapdata[6].i("VenderId","");
	mapdata[7].i("RtspURL","");
	mapdata[8].i("RTPMode","");
	mapdata[9].i("DecodeTAG","");
	mapdata[10].i("Longitude","");
	mapdata[11].i("Latitude","");
	mapdata[12].i("CrossIndex","");
	mapdata[13].i("LaneId","");


	if(ReadXML_UTF8_NoSub(MsgXml,mapdata,14))
		strcpy(*ResponseXml,"aaa");
	else
		strcpy(*ResponseXml,"bbb");


	return SOAP_OK;
} 

void IfCameraXML(char* code,char* message,char *flag,char *strText,int len)
{
	struct NAME_VALUE_S Rmapdata[3];
	Rmapdata[0].i("Code",code);
	Rmapdata[1].i("Message",message);
	Rmapdata[2].i("flag",flag);

	if(false==CreateXmlLite_UTF8_NoSub("Return",Rmapdata,3,strText,len) )
	{
		strcpy(strText,"<Return><Code>-99</Code><Message>�ڲ��쳣��������ʧ��</Message></Return>");
	}
}

int ns__IfCamera(struct soap *soap, char *MsgXml, char **ResponseXml)
{ 
	*ResponseXml = (char*)soap_malloc( soap,XMLRW_MAX_WSTR );
	char strText[XMLRW_MAX_WSTR]="";

	struct NAME_VALUE_S mapdata[1];
	mapdata[0].i("CameraID","");


	if(ReadXML_UTF8_NoSub(MsgXml,mapdata,3))
	{

		if(mapdata[0].valuestr.length()==0  )
		{
			ErrorStringXML("-2","����ı����ֶβ���ȱʧ",strText,XMLRW_MAX_WSTR);
			goto ALL_EXIT;
		}

		long CameraID=-1;
		sscanf(mapdata[0].valuestr.c_str(),"%d",&CameraID);

		if(-1 ==CameraID  )
		{
			ErrorStringXML("-3","����ı����ֶβ�������",strText,XMLRW_MAX_WSTR);
			goto ALL_EXIT;
		}

		if(OracleIO.DEVICE_IfCamera(CameraID))
			IfCameraXML("0","�ɹ�-��������ͷ","1",strText,XMLRW_MAX_WSTR);
		else
			IfCameraXML("0","�ɹ�-����������ͷ","0",strText,XMLRW_MAX_WSTR);
	}
	else
	{
		ErrorStringXML("-1","����ı����޷�����",strText,XMLRW_MAX_WSTR);
		goto ALL_EXIT;
	}

ALL_EXIT:
	CHAR2UTF8(strText,*ResponseXml,XMLRW_MAX_WSTR);

	return SOAP_OK;
} 

int ns__DelCamera(struct soap *soap, char *MsgXml, char **ResponseXml)
{ 
	*ResponseXml = (char*)soap_malloc( soap,XMLRW_MAX_WSTR );
	char strText[XMLRW_MAX_WSTR]="";

	struct NAME_VALUE_S mapdata[1];
	mapdata[0].i("CameraID","");


	if(ReadXML_UTF8_NoSub(MsgXml,mapdata,3))
	{
		if(mapdata[0].valuestr.length()==0  )
		{
			ErrorStringXML("-2","����ı����ֶβ���ȱʧ",strText,XMLRW_MAX_WSTR);
			goto ALL_EXIT;
		}

		long CameraID=-1;
		sscanf(mapdata[0].valuestr.c_str(),"%d",&CameraID);

		if(-1 ==CameraID  )
		{
			ErrorStringXML("-3","����ı����ֶβ�������",strText,XMLRW_MAX_WSTR);
			goto ALL_EXIT;
		}

		if(OracleIO.DEVICE_DeleteCamera(CameraID))
			ErrorStringXML("0","�ɹ�-ɾ���ɹ�",strText,XMLRW_MAX_WSTR);
		else
			ErrorStringXML("-98","�ڲ��쳣���ݿ����",strText,XMLRW_MAX_WSTR);
	}
	else
	{
		ErrorStringXML("-1","����ı����޷�����",strText,XMLRW_MAX_WSTR);
		goto ALL_EXIT;
	}

ALL_EXIT:
	CHAR2UTF8(strText,*ResponseXml,XMLRW_MAX_WSTR);

	return SOAP_OK;
} 

#include "stdafx.h"
#include "Web90server.h"

#define WEB_KAKOU_DEBUG 0

void ReadFromFile(char**data,char* pfile)
{
	FILE* fp = fopen(pfile,"rb");
	if(fp)
	{
		fseek(fp,0,SEEK_END);
		unsigned long len=ftell(fp);
		*data=(char *)calloc(len,1);
		fseek(fp,0,SEEK_SET);

		fread(*data,len,1,fp);
		fclose(fp);
	}
	else
	{
		printf("open fail--\r\n");
	}
}

void WriteToFileAB(string buffer,char* pfile)
{
	FILE* fp = fopen(pfile,"ab");
	if(fp)
	{
		fwrite(buffer.data(),1,buffer.size(),fp);
		fclose(fp);
	}
	else
	{
		printf("open fail--\r\n");
	}
}

void WriteToFileWB(string buffer,char* pfile)
{
	FILE* fp = fopen(pfile,"wb");
	if(fp)
	{
		fwrite(buffer.data(),1,buffer.size(),fp);
		fclose(fp);
	}
	else
	{
		printf("open fail--\r\n");
	}
}

/////////////////////////////////////////////////////////////////////////////

void CHAR2UTF8Lite(const char *str,char *utf8)
{
	wchar_t wbufflite[XMLRW_MAX_WSTR];
	// int buffLen = 0;  
	MultiByteToWideChar(CP_ACP, 0, str, -1, wbufflite, XMLRW_MAX_WSTR);  
	// buffLen = WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, NULL, 0, 0, 0);  
	//  utf8 = new char[buffLen+1];  
	WideCharToMultiByte(CP_UTF8, 0, wbufflite, -1, (LPSTR)utf8, XMLRW_MAX_STR, 0, 0);  
}

void UTF82CHARLite(const char *utf8,char *str)
{
	wchar_t wbufflite[XMLRW_MAX_WSTR];
	//	int buffLen = 0;  
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wbufflite, XMLRW_MAX_WSTR);  
	//	buffLen = WideCharToMultiByte(CP_ACP, 0, wbuff, -1, NULL, 0, 0, 0);  
	//	m_gb2312 = new char[buffLen+1];  
	WideCharToMultiByte(CP_ACP, 0, wbufflite, -1, (LPSTR)str, XMLRW_MAX_STR, 0, 0);  
}

void CHAR2UTF8(const char *str,char *utf8,unsigned long int len)
{
	wchar_t * wbuff=(wchar_t *)calloc(len*2+4/*+4*/,sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, -1, wbuff, len+2);  
	// buffLen = WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, NULL, 0, 0, 0);  
	//  utf8 = new char[buffLen+1];  
	WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, (LPSTR)utf8, len*2+4, 0, 0); 
	free(wbuff);
	wbuff=NULL;
}

void UTF82CHAR(const char *utf8,char *str,unsigned long int len)
{
	wchar_t * wbuff=(wchar_t *)calloc(len*2+4,sizeof(wchar_t));
	//	int buffLen = 0;  
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wbuff, len+2);  
	//	buffLen = WideCharToMultiByte(CP_ACP, 0, wbuff, -1, NULL, 0, 0, 0);  
	//	m_gb2312 = new char[buffLen+1];  
	WideCharToMultiByte(CP_ACP, 0, wbuff, -1, (LPSTR)str, len*2+4, 0, 0);  
	free(wbuff);
	wbuff=NULL;
}


/*!
*  \brief ͨ�����ڵ�ͽڵ�����ȡ�ڵ�ָ�롣
*
*  \param pRootEle   xml�ļ��ĸ��ڵ㡣
*  \param strNodeName  Ҫ��ѯ�Ľڵ���
*  \param Node      ��Ҫ��ѯ�Ľڵ�ָ��
*  \return �Ƿ��ҵ���trueΪ�ҵ���Ӧ�ڵ�ָ�룬false��ʾû���ҵ���Ӧ�ڵ�ָ�롣
*/
bool ReadGetNodePointerByName(TiXmlElement* pRootEle,string strNodeName,TiXmlElement* &Node)
{
	// ������ڸ��ڵ��������˳�
	if (strNodeName==pRootEle->Value())
	{
		Node = pRootEle;
		return true;
	}
	TiXmlElement* pEle = pRootEle;  
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())  
	{  
		//�ݹ鴦���ӽڵ㣬��ȡ�ڵ�ָ��
		if(ReadGetNodePointerByName(pEle,strNodeName,Node))
			return true;
	}  

	return false;
}
/*!
*  \brief ͨ���ڵ��ѯ��
*
*  \param XmlFile   xml�ļ�ȫ·����
*  \param strNodeName  Ҫ��ѯ�Ľڵ��� 
*  \param strText      Ҫ��ѯ�Ľڵ��ı�
*  \return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ�
//ԭʼ�ڵ�pRootEle
//�ҵ��Ľڵ�FindNode
*/
bool ReadQueryNodeText(TiXmlElement *pRootEle,TiXmlElement* &FindNode,string strNodeName,char *strText,unsigned long int len,bool utfflag)
{
	bool res=ReadGetNodePointerByName(pRootEle,strNodeName,FindNode);
	if (NULL!=FindNode && true==res)
	{
		const char* psz = FindNode->GetText(); 

		if (NULL==psz)
			strText[0] =0;
		else	//ת��
		{
			if(utfflag)
				UTF82CHAR(psz,strText,len);
			else
				strcpy(strText,psz);
		}
		return true;
	}
	else
	{
		strText[0] =0;
		return false;
	}
}


bool CreateXMLDataUTF8(TiXmlElement *prow,string attr,const char *valuedata,char *strText,unsigned long int len,bool cdataflag)
{
	// �����ӽڵ㣺data  
	TiXmlElement *pdata = new TiXmlElement(attr);  
	if (NULL==pdata)  
	{  
		return false;  
	}  
	prow->LinkEndChild(pdata);  
	//ת��
	CHAR2UTF8(valuedata,strText,len);
	//���
	TiXmlText *pdataValue = new TiXmlText(strText);  
	pdata->LinkEndChild(pdataValue); 
	//�м�CDATA���
	pdataValue->SetCDATA(cdataflag); 
	return true;
}

bool CreateXMLData(TiXmlElement *prow,string attr,const char *valuedata,bool cdataflag)
{
	// �����ӽڵ㣺data  
	TiXmlElement *pdata = new TiXmlElement(attr);  
	if (NULL==pdata)  
	{  
		return false;  
	}  
	prow->LinkEndChild(pdata);  
	//���
	TiXmlText *pdataValue = new TiXmlText(valuedata);  
	pdata->LinkEndChild(pdataValue); 
	pdataValue->SetCDATA(cdataflag); 
	return true;
}
/*
<?xml version="1.0" encoding="UTF-8"?>
<soap:Envelope xmlns:soap="http://www.w3.org/2003/05/soap-envelope" xmlns:ser="http://service.thirdBayonet.webservice.bms.hikvision.com">
<soap:Header/>
<soap:Body>
<ser:initSystem>
<ser:xml>

<![CDATA[

<loginParam> 
<cmsUrl>35.24.13.26</cmsUrl> 
<userName>admin</userName> 
<passwd>fzga12345</passwd> 
</loginParam>

]]>


</ser:xml>
</ser:initSystem>
</soap:Body>
</soap:Envelope>
*/
bool CreateXml(char *methodname,const char *valuedata,
			   char *strText,unsigned long int len)  
{  
	// ����һ��TiXmlDocument��ָ��  
	TiXmlDocument pDoc;  
/*
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0","utf-8","");  
	if (NULL==pDeclaration)  
	{  
		return false;  
	}  

	pDoc.LinkEndChild(pDeclaration);  
	*/
	// ����һ�����ڵ㣺pRootEle 
	TiXmlElement *pRootEle = new TiXmlElement("soap:Envelope");  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	pDoc.LinkEndChild(pRootEle);  
	pRootEle->SetAttribute("xmlns:soap","http://www.w3.org/2003/05/soap-envelope");
	pRootEle->SetAttribute("xmlns:ser", "http://service.thirdBayonet.webservice.bms.hikvision.com");

	// �����ӽڵ㣺pHeader
	TiXmlElement *pHeader = new TiXmlElement("soap:Header"); 
	if (NULL==pHeader)  
	{  
		return false;  
	}  
	pRootEle->LinkEndChild(pHeader);  

	// �����ӽڵ㣺pbody
	TiXmlElement *pbody = new TiXmlElement("soap:Body"); 
	if (NULL==pbody)  
	{  
		return false;  
	}  
	pRootEle->LinkEndChild(pbody);  


	// �����ӽڵ㣺row
	TiXmlElement *pmethod = new TiXmlElement(methodname);  
	if (NULL==pmethod)  
	{  
		return false;  
	}  
	pbody->LinkEndChild(pmethod);  

	//���� ���� ������ַ��Ѿ���UTF8 ���ﲻ����ת
	if(!CreateXMLData(pmethod,
		"ser:xml",
		valuedata,
		true))
		return false;

	//���浽�ַ���
	TiXmlPrinter printer;
	pDoc.Accept(&printer);
	//	strResult.Format("%s", printer.CStr());
	strcpy(strText,printer.CStr());

	if(WEB_KAKOU_DEBUG)
	{
		printf("xml=\n%s\n",strText);
		//�����ļ�
		pDoc.SaveFile("d:\\1.xml");
	}
	return true;  
}   

//����CDATA����  ��������
bool CreateXmlLite(char *name,struct NAME_VALUE_S mapdata[],int maplen,
							  char *strText,unsigned long int len)  
{  
	// ����һ��TiXmlDocument��ָ��  
	TiXmlDocument pDoc;  
/*
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0","utf-8","");  
	if (NULL==pDeclaration)  
	{  
		return false;  
	}  

	pDoc.LinkEndChild(pDeclaration);  
*/
	// ����һ�����ڵ㣺pRootEle 
	TiXmlElement *pRootEle = new TiXmlElement(name);  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	pDoc.LinkEndChild(pRootEle);  

	int it;
	for(it=0;it<maplen;it++)
	{
		
		if(!CreateXMLDataUTF8(pRootEle,
			mapdata[it].namestr.c_str(),
			mapdata[it].valuestr.c_str(),
			strText,len,
			false))
			return false;
	}

	//�����ļ�
	//pDoc.SaveFile("d:\\1.xml");

	//���浽�ַ���
	TiXmlPrinter printer;
	pDoc.Accept(&printer);
	//	strResult.Format("%s", printer.CStr());
	strcpy(strText,printer.CStr());

	if(WEB_KAKOU_DEBUG)
		printf("xml=\n%s\n",strText);

	return true;  
}   

//����CDATA����  ��һ������ ֻ�ܼ�һ�� Ϊ���뿨�ڶ���
bool CreateXmlLite_Cross(char *name,struct NAME_VALUE_S mapdata[],int maplen,
						   char *subname, char *sub2name,struct NAME_VALUE_S subdata[],int sublen,
						  char *strText,unsigned long int len)  
{  
	// ����һ��TiXmlDocument��ָ��  
	TiXmlDocument pDoc;  
/*
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0","utf-8","");  
	if (NULL==pDeclaration)  
	{  
		return false;  
	}  

	pDoc.LinkEndChild(pDeclaration);  
	*/
	// ����һ�����ڵ㣺pRootEle 
	TiXmlElement *pRootEle = new TiXmlElement(name);  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	pDoc.LinkEndChild(pRootEle);  

	int it;
	for(it=0;it<maplen;it++)
	{
		if(!CreateXMLDataUTF8(pRootEle,
			mapdata[it].namestr.c_str(),
			mapdata[it].valuestr.c_str(),
			strText,len,
			false))
			return false;
	}

	// ����һ�����ڵ㣺pRootEle 
	TiXmlElement *pSubEle = new TiXmlElement(subname);  
	if (NULL==pSubEle)  
	{  
		return false;  
	}  
	pRootEle->LinkEndChild(pSubEle);  

	// ����һ�����ڵ㣺pRootEle 
	TiXmlElement *pSub2Ele = new TiXmlElement(sub2name);  
	if (NULL==pSub2Ele)  
	{  
		return false;  
	}  
	pSubEle->LinkEndChild(pSub2Ele);  

	for(it=0;it<sublen;it++)
	{
		if(!CreateXMLDataUTF8(pSub2Ele,
			subdata[it].namestr.c_str(),
			subdata[it].valuestr.c_str(),
			strText,len,
			false))
			return false;
	}

	//�����ļ�
	//pDoc.SaveFile("d:\\1.xml");

	//���浽�ַ���
	TiXmlPrinter printer;
	pDoc.Accept(&printer);
	//	strResult.Format("%s", printer.CStr());
	strcpy(strText,printer.CStr());

	if(WEB_KAKOU_DEBUG)
		printf("xml=\n%s\n",strText);

	return true;  
}  

//����CDATA����  ��������
bool CreateXmlLite_Vehicle(char *name,bool isPicUrl,struct NAME_VALUE_S mapdata[],int maplen,
				   char *strText,unsigned long int len)  
{  
	// ����һ��TiXmlDocument��ָ��  
	TiXmlDocument pDoc;  
/*
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0","utf-8","");  
	if (NULL==pDeclaration)  
	{  
		return false;  
	}  
	pDoc.LinkEndChild(pDeclaration);  
	*/
	// ����һ�����ڵ㣺pRootEle 
	TiXmlElement *pRootEle = new TiXmlElement(name);  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	pDoc.LinkEndChild(pRootEle);  


	/*
	//��׼д��
	if(isPicUrl)
		pRootEle->SetAttribute("isPicUrl",1);
	else
		pRootEle->SetAttribute("isPicUrl",0);
*/

//���д��
//tinyxml.CPP��.H���
/*
void TiXmlElement::SetAttribute( const char * name )
{	
	TiXmlAttribute* attrib = attributeSet.FindOrCreate( name );
}
#ifdef TIXML_USE_STL
void TiXmlElement::SetAttribute( const std::string& name)
{	
	TiXmlAttribute* attrib = attributeSet.FindOrCreate( name );
}
#endif

*/
	if(isPicUrl)
		pRootEle->SetAttribute("isPicUrl=1");
	else
		pRootEle->SetAttribute("isPicUrl=0");


	int it;
	for(it=0;it<maplen;it++)
	{
		if(!CreateXMLDataUTF8(pRootEle,
			mapdata[it].namestr.c_str(),
			mapdata[it].valuestr.c_str(),
			strText,len,
			false))
			return false;
	}

	//�����ļ�
	//pDoc.SaveFile("d:\\1.xml");

	//���浽�ַ���
	TiXmlPrinter printer;
	pDoc.Accept(&printer);
	//	strResult.Format("%s", printer.CStr());
	strcpy(strText,printer.CStr());

	if(WEB_KAKOU_DEBUG)
		printf("xml=\n%s\n",strText);

	return true;  
}   
//���Ľ���
bool XMLgetReturnData(const char *utf8xmlin,char*utf8xmlout)
{
	//����ջ�� �ڴ治��й¶
	TiXmlDocument myDocument;
	myDocument.Parse(utf8xmlin);

	TiXmlElement *pRootEle = myDocument.RootElement();
	if (NULL==pRootEle)
	{
		printf("XMLgetReturnData XML����\n");
		return false;
	}

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	for(pNodeRow = pRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
	{
		pNodeData = NULL;
		if(ReadQueryNodeText(pNodeRow,pNodeData,"bms1:return",utf8xmlout,XMLRW_MAX_STR,false))
		{
			//printf("bms1:return=%s\n",returnstr);
			break ;
		}
	}
	return true;
}


bool SendSoap_InitSystem(char *wsdlUrl,char *ip,char *username,char *psw,
						 char *sessionIdstr,
					  char *failstr)
{
	Service CService;

	long xmlstrlen=5120;

	char xmlstr[5120];
	char xmllitestr[5120];

	char soapactionstr[512]="Content-Type: application/soap+xml;charset=UTF-8;action=\"urn:initSystem\"";
/*
	if(false==CreateXmlLite_initSystem(ip,username,psw,
		xmllitestr,51200))
	{
		strcpy(failstr,"SendPidPushSoap �޷�����XML lite�ļ�");
		printf("SendPidPushSoap �޷�����XML lite�ļ�\n");

		return false;
	}
*/
	/*
	map<string ,string> mapdata;
	mapdata.insert(pair<string,string>("cmsUrl",ip));
	mapdata.insert(pair<string,string>("userName",username));
	mapdata.insert(pair<string,string>("passwd",psw));
*/

 

	struct NAME_VALUE_S mapdata[3];
	mapdata[0].i("cmsUrl",ip);
	mapdata[1].i("userName",username);
	mapdata[2].i("passwd",psw);

	if(false==CreateXmlLite("loginParam",mapdata,3,
		xmllitestr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_InitSystem �޷�����XML lite�ļ�");
		//printf("SendSoap_InitSystem �޷�����XML lite�ļ�\n");

		return false;
	}

	if(false==CreateXml("ser:initSystem",
		xmllitestr,
		xmlstr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_InitSystem �޷�����XML�ļ�");
		//printf("SendSoap_InitSystem �޷�����XML�ļ�\n");

		return false;
	}

	CService.InitData();

	int nRes = CService.PostSoap(wsdlUrl,soapactionstr,xmlstr,failstr);

	if(0!=nRes)
	{
		strcat(failstr," SendInitSystemSoap POST���� ���ڷ���δ����");
	//	printf("SendInitSystemSoap POST����\n");
		CService.DestroyData();
		return false;
	}
	
	if(WEB_KAKOU_DEBUG)
		printf("\nSendInitSystemSoap resp_buffer=%s\n",CService.m_resp_buffer.c_str());

/*
	if(NULL!=strstr(CService.m_resp_buffer.c_str(),"<ns:return>"))
	{
		strcat(failstr," SendPidPushSoap ���ر��Ĳ�Ϊ0");
		CService.DestroyData();
		return false;
	}
	*/
/*
	//����Ĭ��UTF-8��
	char* charstr=(char *)calloc(CService.m_resp_buffer.length()*2+4,sizeof(char));

	UTF82CHAR(CService.m_resp_buffer.c_str(),charstr,CService.m_resp_buffer.length()*2);

	//��ֹ���Ĵ��� �������һ��<���ϴ���ȥ���н���
	const char *presp=strchr(charstr,'<');
	if(NULL== presp)
	{
		strcpy(failstr,"SendInitSystemSoap XML���� �Ҳ���<");
		printf("SendInitSystemSoap XML���� �Ҳ���<\n");
		free(charstr);
		CService.DestroyData();
		return false;
	}

	char* utf8=(char *)calloc(strlen(presp)*2+4,sizeof(char));
	
	CHAR2UTF8(presp,utf8,strlen(presp)*2);
*/
	char returnstr[XMLRW_MAX_STR]="";

	if(false == XMLgetReturnData(CService.m_resp_buffer.c_str(),returnstr))
	{
		strcat(failstr," SendInitSystemSoap XMLgetReturnDataT����");
		CService.DestroyData();
		return false;
	}
	// ���������
	CService.DestroyData();

	//����ջ�� �ڴ治��й¶
	TiXmlDocument returnDocument;
	returnDocument.Parse(returnstr);

	TiXmlElement *preturnRootEle = returnDocument.RootElement();
	if (NULL==preturnRootEle)
	{
		strcpy(failstr,"SendInitSystemSoap XMLreturn����");
		//printf("SendInitSystemSoap XMLreturn����\n");
		return false;
	}

	char codestr[32]="";
	char messagestr[256]="";
	char sessionstr[128]="";

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	for(pNodeRow = preturnRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
	{
		pNodeData = NULL;
		if(ReadQueryNodeText(pNodeRow,pNodeData,"code",codestr,XMLRW_MAX_STR,true))
		{
			//printf("code=%s\n",codestr);
			NULL;
		}
		if(ReadQueryNodeText(pNodeRow,pNodeData,"message",messagestr,XMLRW_MAX_STR,true))
		{
		//	printf("message=%s\n",messagestr);
			NULL;
		}
		if(ReadQueryNodeText(pNodeRow,pNodeData,"sessionId",sessionstr,XMLRW_MAX_STR,true))
		{
			//printf("sessionId=%s\n",sessionstr);
			if(strlen(sessionstr)>0)
			{
				strcpy(sessionIdstr,sessionstr);
			}
		}
	}

	if (0!=atol(codestr))
	{
		sprintf(failstr,"����ϵͳSendInitSystemSoap XMLmessage���� %s",messagestr);
		return false;
	}

	return true;

}




bool SendSoap_insertCrossingInfo(char *wsdlUrl,
								 char *id,char *index_code,
								 char *crossindex,char *crossname,char *longi, char *lati,
								 char *crossIdstr,
								char *failstr)
{
	Service CService;


	long xmlstrlen=5120;

	char xmlstr[5120];
	char xmllitestr[5120];

	char soapactionstr[512]="Content-Type: application/soap+xml;charset=UTF-8;action=\"urn:insertCrossingInfo\"";
	/*
	map<string ,string> mapdata;

	mapdata.insert(pair<string,string>("sessionId",id));
	mapdata.insert(pair<string,string>("crossingIndex",crossindex));
	mapdata.insert(pair<string,string>("crossingName",crossname));
	mapdata.insert(pair<string,string>("longitude",longi));
	mapdata.insert(pair<string,string>("latitude",lati));
	mapdata.insert(pair<string,string>("drivewayNum","0"));
	mapdata.insert(pair<string,string>("controlindexCode","0"));
	*/

	struct NAME_VALUE_S mapdata[7];

	mapdata[0].i("sessionId",id);
	mapdata[1].i("crossingIndex",crossindex);
	mapdata[2].i("crossingName",crossname);
	mapdata[3].i("longitude",longi);
	mapdata[4].i("latitude",lati);
	mapdata[5].i("drivewayNum","1");
	mapdata[6].i("controlindexCode",index_code);

	struct NAME_VALUE_S subdata[3];

	subdata[0].i("laneNum","1");
	subdata[1].i("laneName","����1");
	subdata[2].i("dirName","");

	if(false==CreateXmlLite_Cross(
		"crossingInfo",mapdata,7,
		"laneInfos","laneInfo",subdata,3,
		xmllitestr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_insertCrossingInfo �޷�����XML lite�ļ�");
		printf("SendSoap_insertCrossingInfo �޷�����XML lite�ļ�\n");

		return false;
	}

	if(false==CreateXml("ser:insertCrossingInfo",
		xmllitestr,
		xmlstr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_insertCrossingInfo �޷�����XML�ļ�");
		//printf("SendSoap_insertCrossingInfo �޷�����XML�ļ�\n");

		return false;
	}

	CService.InitData();

	int nRes = CService.PostSoap(wsdlUrl,soapactionstr,xmlstr,failstr);

	if(0!=nRes)
	{
		strcat(failstr," SendSoap_insertCrossingInfo POST����");
		//printf("SendSoap_insertCrossingInfo POST����\n");
		CService.DestroyData();
		return false;
	}

	if(WEB_KAKOU_DEBUG)
		printf("\nSendSoap_insertCrossingInfo resp_buffer=%s\n",CService.m_resp_buffer.c_str());
/*
	if(NULL!=strstr(CService.m_resp_buffer.c_str(),"<ns:return>"))
	{
		strcat(failstr," SendPidPushSoap ���ر��Ĳ�Ϊ0");
		CService.DestroyData();
		return false;
	}
	*/

	char returnstr[XMLRW_MAX_STR]="";

	if(false == XMLgetReturnData(CService.m_resp_buffer.c_str(),returnstr))
	{
		strcat(failstr," SendSoap_insertCrossingInfo XMLgetReturnDataT����");
		CService.DestroyData();
		return false;
	}
	// ���������
	CService.DestroyData();

	//����ջ�� �ڴ治��й¶
	TiXmlDocument returnDocument;
	returnDocument.Parse(returnstr);

	TiXmlElement *preturnRootEle = returnDocument.RootElement();
	if (NULL==preturnRootEle)
	{
		strcpy(failstr,"SendSoap_insertCrossingInfo XMLreturn����");
		//printf("SendSoap_insertCrossingInfo XMLreturn����\n");
		return false;
	}

	char codestr[32]="";
	char messagestr[256]="";

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	for(pNodeRow = preturnRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
	{
		pNodeData = NULL;
		if(ReadQueryNodeText(pNodeRow,pNodeData,"code",codestr,XMLRW_MAX_STR,true))
		{
		//	printf("code=%s\n",codestr);
			NULL;
		}
		if(ReadQueryNodeText(pNodeRow,pNodeData,"message",messagestr,XMLRW_MAX_STR,true))
		{
			//printf("message=%s\n",messagestr);
			NULL;
		}
		if(ReadQueryNodeText(pNodeRow,pNodeData,"crossId",crossIdstr,XMLRW_MAX_STR,true))
		{
			//printf("crossId=%s\n",crossIdstr);
			NULL;
		}
	}

	if (0!=atol(codestr))
	{
		sprintf(failstr,"SendSoap_insertCrossingInfo XMLmessage���� %s",messagestr);
		return false;
	}


	return true;

}



bool SendSoap_deleteCrossingInfo(char *wsdlUrl,
								 char *id,
								 char *crossindex,
								char *failstr)
{
	Service CService;

	long xmlstrlen=5120;

	char xmlstr[5120];
	char xmllitestr[5120];

	char soapactionstr[512]="Content-Type: application/soap+xml;charset=UTF-8;action=\"urn:deleteCrossingInfo\"";

	struct NAME_VALUE_S mapdata[2];
	mapdata[0].i("sessionId",id);
	mapdata[1].i("crossingIndex",crossindex);


	if(false==CreateXmlLite("crossingInfo",mapdata,2,
		xmllitestr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_deleteCrossingInfo �޷�����XML lite�ļ�");
		//printf("SendSoap_deleteCrossingInfo �޷�����XML lite�ļ�\n");

		return false;
	}

	if(false==CreateXml("ser:deleteCrossingInfo",
		xmllitestr,
		xmlstr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_deleteCrossingInfo �޷�����XML�ļ�");
		//printf("SendSoap_deleteCrossingInfo �޷�����XML�ļ�\n");

		return false;
	}

	CService.InitData();

	int nRes = CService.PostSoap(wsdlUrl,soapactionstr,xmlstr,failstr);

	if(0!=nRes)
	{
		strcat(failstr," SendSoap_deleteCrossingInfo POST���� ���ڷ���δ����");
	//	printf("SendSoap_deleteCrossingInfo POST����\n");
		CService.DestroyData();
		return false;
	}
	
	if(WEB_KAKOU_DEBUG)
		printf("SendSoap_deleteCrossingInfo resp_buffer=%s\n",CService.m_resp_buffer.c_str());

/*
	if(NULL!=strstr(CService.m_resp_buffer.c_str(),"<ns:return>"))
	{
		strcat(failstr," SendPidPushSoap ���ر��Ĳ�Ϊ0");
		CService.DestroyData();
		return false;
	}
	*/
/*
	//����Ĭ��UTF-8��
	char* charstr=(char *)calloc(CService.m_resp_buffer.length()*2+4,sizeof(char));

	UTF82CHAR(CService.m_resp_buffer.c_str(),charstr,CService.m_resp_buffer.length()*2);

	//��ֹ���Ĵ��� �������һ��<���ϴ���ȥ���н���
	const char *presp=strchr(charstr,'<');
	if(NULL== presp)
	{
		strcpy(failstr,"SendInitSystemSoap XML���� �Ҳ���<");
		printf("SendInitSystemSoap XML���� �Ҳ���<\n");
		free(charstr);
		CService.DestroyData();
		return false;
	}

	char* utf8=(char *)calloc(strlen(presp)*2+4,sizeof(char));
	
	CHAR2UTF8(presp,utf8,strlen(presp)*2);
*/
	char returnstr[XMLRW_MAX_STR]="";

	if(false == XMLgetReturnData(CService.m_resp_buffer.c_str(),returnstr))
	{
		strcat(failstr," SendSoap_deleteCrossingInfo XMLgetReturnDataT����");
		CService.DestroyData();
		return false;
	}
	// ���������
	CService.DestroyData();

# if 0 //���ܷ���ֵ

	//����ջ�� �ڴ治��й¶
	TiXmlDocument returnDocument;
	returnDocument.Parse(returnstr);


	TiXmlElement *preturnRootEle = returnDocument.RootElement();
	if (NULL==preturnRootEle)
	{
		strcpy(failstr,"SendSoap_deleteCrossingInfo XMLreturn����");
		printf("SendSoap_deleteCrossingInfo XMLreturn����\n");
		return false;
	}

	char codestr[32]="";
	char messagestr[1024]="";
	char sessionstr[128]="";

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	for(pNodeRow = preturnRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
	{
		pNodeData = NULL;
		if(ReadQueryNodeText(pNodeRow,pNodeData,"code",codestr,XMLRW_MAX_STR,true))
		{
			printf("code=%s\n",codestr);
		}
		if(ReadQueryNodeText(pNodeRow,pNodeData,"message",messagestr,XMLRW_MAX_STR,true))
		{
			printf("message=%s\n",messagestr);
		}
		
	}

	if (0!=atol(codestr))
	{
		sprintf(failstr,"����ϵͳSendSoap_deleteCrossingInfo XMLmessage���� %s",messagestr);
		return false;
	}
#endif

	return true;

}



bool SendSoap_insertVehicleInfo(char *wsdlUrl,
								 char *id,char *crossindex,char *passTime,char *plateInfo,bool isPicUrl,
								char *picPlateurl,unsigned char *picPlatedata,long picPlatelen,
								char *picVehicleurl,unsigned char *picVehicledata,long picVehiclelen,
								char *failstr)
{
	Service CService;

	long xmlstrlen=728000;
	//�����ֵ�ر��
	char *xmlstr=(char *)calloc(xmlstrlen,sizeof(char));
	char *xmllitestr=(char *)calloc(xmlstrlen,sizeof(char));

	char soapactionstr[512]="Content-Type: application/soap+xml;charset=UTF-8;action=\"urn:insertVehicleInfo\"";


	struct NAME_VALUE_S mapdata[17];

	mapdata[0].i("sessionId",id);
	mapdata[1].i("crossIndexcode",crossindex);
	mapdata[2].i("laneId","1"); //������
	mapdata[3].i("plateInfo",plateInfo); //���ƺ�
	mapdata[4].i("plateColor","6"); //������ɫ  ��ɫ
	mapdata[5].i("plateType","16"); //��������  Ħ�г�

	char Timeformat[64];
	sprintf(Timeformat,"%s.000",passTime);
	mapdata[6].i("passTime",Timeformat); //ʱ��

	mapdata[7].i("vehicleSpeed","0"); //����
	mapdata[8].i("vehicleType","7"); //�������� �綯��
	mapdata[9].i("vehColorDepth","1"); //������ɫ��ǳ
	mapdata[10].i("vehicleColor","1"); //������ɫ ����

	char *Platebase64str=NULL;
	char *Vehiclebase64str=NULL;

	if(isPicUrl)
	{
		mapdata[11].i("picPlate",picPlateurl); //����ͼ
		mapdata[12].i("picVehicle",picVehicleurl); //����ͼ
	}
	else
	{
		if(0==picPlatelen)
		{
			mapdata[11].i("picPlate",""); //����ͼ
		}
		else
		{
			//ת��BASE64����
			Platebase64str=(char *)calloc(OUT_ENBASE64_SIZE(picPlatelen)+10,sizeof(char));
			base64_encode(Platebase64str,(OUT_ENBASE64_SIZE(picPlatelen)+10)*sizeof(char),picPlatedata,picPlatelen);
			mapdata[11].i("picPlate",Platebase64str); //����ͼ
		}

		Vehiclebase64str=(char *)calloc(OUT_ENBASE64_SIZE(picVehiclelen)+10,sizeof(char));
		base64_encode(Vehiclebase64str,(OUT_ENBASE64_SIZE(picVehiclelen)+10)*sizeof(char),picVehicledata,picVehiclelen);

		//תBASE64
		mapdata[12].i("picVehicle",Vehiclebase64str); //����ͼ
	}

	mapdata[13].i("alarmAction","0"); //Υ������ ����
	mapdata[14].i("vehicleState","1"); //�г�״̬  ����
	mapdata[15].i("reserved1","");
	mapdata[16].i("reserved2","");

	if(false==CreateXmlLite_Vehicle("vehicleInfo",isPicUrl,mapdata,17,
		xmllitestr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_insertVehicleInfo �޷�����XML lite�ļ�");
		printf("SendSoap_insertVehicleInfo �޷�����XML lite�ļ�\n");
	
		//�ͷ�
		if(Platebase64str)
		{
			free(Platebase64str);
			Platebase64str=NULL;
		}
		if(Vehiclebase64str)
		{
			free(Vehiclebase64str);
			Vehiclebase64str=NULL;
		}

		if(xmlstr)
		{
			free(xmlstr);
			xmlstr=NULL;
		}
		if(xmllitestr)
		{
			free(xmllitestr);
			xmllitestr=NULL;
		}
		return false;
	}
	//�ͷ�
	if(Platebase64str)
	{
		free(Platebase64str);
		Platebase64str=NULL;
	}
	if(Vehiclebase64str)
	{
		free(Vehiclebase64str);
		Vehiclebase64str=NULL;
	}

	if(false==CreateXml("ser:insertVehicleInfo",
		xmllitestr,
		xmlstr,xmlstrlen))
	{
		strcpy(failstr,"SendSoap_insertVehicleInfo �޷�����XML�ļ�");
		printf("SendSoap_insertVehicleInfo �޷�����XML�ļ�\n");

		if(xmlstr)
		{
			free(xmlstr);
			xmlstr=NULL;
		}
		if(xmllitestr)
		{
			free(xmllitestr);
			xmllitestr=NULL;
		}
		return false;
	}

	CService.InitData();

	int nRes = CService.PostSoap(wsdlUrl,soapactionstr,xmlstr,failstr);

	if(0!=nRes)
	{
		strcat(failstr," SendSoap_insertVehicleInfo POST����");
		printf("SendSoap_insertVehicleInfo POST����\n");
		CService.DestroyData();
		
		if(xmlstr)
		{
			free(xmlstr);
			xmlstr=NULL;
		}
		if(xmllitestr)
		{
			free(xmllitestr);
			xmllitestr=NULL;
		}

		return false;
	}
	//�ͷ�
	if(xmlstr)
	{
		free(xmlstr);
		xmlstr=NULL;
	}
	if(xmllitestr)
	{
		free(xmllitestr);
		xmllitestr=NULL;
	}

	if(WEB_KAKOU_DEBUG)
		printf("\nSendSoap_insertVehicleInfo resp_buffer=%s\n",CService.m_resp_buffer.c_str());
/*
	if(NULL!=strstr(CService.m_resp_buffer.c_str(),"<ns:return>"))
	{
		strcat(failstr," SendPidPushSoap ���ر��Ĳ�Ϊ0");
		CService.DestroyData();
		return false;
	}
	*/

	char returnstr[XMLRW_MAX_STR]="";

	if(false == XMLgetReturnData(CService.m_resp_buffer.c_str(),returnstr))
		{
		strcat(failstr," SendSoap_insertVehicleInfo XMLgetReturnDataT����");
		CService.DestroyData();
		return false;
	}
	// ���������
	CService.DestroyData();

	//����ջ�� �ڴ治��й¶
	TiXmlDocument returnDocument;
	returnDocument.Parse(returnstr);


	TiXmlElement *preturnRootEle = returnDocument.RootElement();
	if (NULL==preturnRootEle)
	{
		strcpy(failstr,"SendSoap_insertVehicleInfo XMLreturn����");
		printf("SendSoap_insertVehicleInfo XMLreturn����\n");
		return false;
	}

	char codestr[32]="";
	char messagestr[1024]="";

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	for(pNodeRow = preturnRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
	{
		pNodeData = NULL;
		if(ReadQueryNodeText(pNodeRow,pNodeData,"code",codestr,XMLRW_MAX_STR,true))
		{
			printf("code=%s\n",codestr);
		}
		if(ReadQueryNodeText(pNodeRow,pNodeData,"message",messagestr,XMLRW_MAX_STR,true))
		{
			printf("message=%s\n",messagestr);
		}
	}

	if (0!=atol(codestr))
	{
		sprintf(failstr,"SendSoap_insertVehicleInfo XML���� %s",messagestr);
		return false;
	}


	return true;

}


#if 0
bool SendPidPushSoap(char *wsdlUrl,char *targetNamespace,char *methodname,
					 char *valuename,const char *valuedata,
					  char *failstr)
{
	Service CService;

	CService.InitData();

	char xmlstr[51200];
	//
	char methodnametemp[256];
	char valuenametemp[256];

	//char targetNamespace[256]="http://push.services.webService.vm.yr.com";

	char soapactionstr[256];

	//sprintf(methodnametemp,"push:%s","concentratePushSend");
	//sprintf(valuenametemp,"push:%s","args0");

	sprintf(methodnametemp,"push:%s",methodname);
	sprintf(valuenametemp,"push:%s",valuename);

	sprintf(soapactionstr,"SOAPAction: \"%s/%s\"",targetNamespace,methodname);

	//ת��BASE64����
	char *base64str=(char *)calloc(OUT_ENBASE64_SIZE(strlen(valuedata))+10,sizeof(char));
	base64_encode(base64str,(OUT_ENBASE64_SIZE(strlen(valuedata))+10)*sizeof(char),(unsigned char *)valuedata,strlen(valuedata));

	if(false==CreateXml(targetNamespace,
		methodnametemp,
		valuenametemp,
		//valuedata,
		base64str,
		xmlstr,51200))
	{
		strcpy(failstr,"SendPidPushSoap �޷�����XML�ļ�");
		printf("SendPidPushSoap �޷�����XML�ļ�\n");

		free(base64str);
		return false;
	}

	free(base64str);

//	int nRes = CService.PostSoap("http://10.142.50.20:8080/uvss/services/infoPushSend",
	//	"SOAPAction: \"http://push.services.webService.vm.yr.com/concentratePushSend\"",
	//	xmlstr);


	int nRes = CService.PostSoap(wsdlUrl,soapactionstr,xmlstr,failstr);

	if(0!=nRes)
	{
		strcat(failstr," SendPidPushSoap POST����");
		printf("SendPidPushSoap POST����\n");
		CService.DestroyData();
		return false;
	}

	if(WEB_KAKOU_DEBUG)
		printf("\nSendPidPushSoap resp_buffer=%s\n",CService.m_resp_buffer.c_str());
/*
	if(NULL!=strstr(CService.m_resp_buffer.c_str(),"<ns:return>"))
	{
		strcat(failstr," SendPidPushSoap ���ر��Ĳ�Ϊ0");
		CService.DestroyData();
		return false;
	}
	*/
	
	//����Ĭ��UTF-8��
	char* charstr=(char *)calloc(CService.m_resp_buffer.length()*2+4,sizeof(char));

	UTF82CHAR(CService.m_resp_buffer.c_str(),charstr,CService.m_resp_buffer.length()*2);

	//��ֹ���Ĵ��� �������һ��<���ϴ���ȥ���н���
	const char *presp=strchr(charstr,'<');
	if(NULL== presp)
	{
		strcpy(failstr,"SendPidPushSoap XML���� �Ҳ���<");
		printf("SendPidPushSoap XML���� �Ҳ���<\n");
		free(charstr);
		CService.DestroyData();
		return false;
	}
	
	char* utf8=(char *)calloc(strlen(presp)*2+4,sizeof(char));
	
	CHAR2UTF8(presp,utf8,strlen(presp)*2);

	//����ջ�� �ڴ治��й¶
	TiXmlDocument myDocument;
	myDocument.Parse(utf8);

	free(utf8);
	free(charstr);

	TiXmlElement *pRootEle = myDocument.RootElement();
	if (NULL==pRootEle)
	{
		strcpy(failstr,"SendPidPushSoap XML����");
		printf("SendPidPushSoap XML����\n");
		CService.DestroyData();
		return false;
	}

	char temp[XMLRW_MAX_STR]="";

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	for(pNodeRow = pRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
	{
		pNodeData = NULL;
		if(ReadQueryNodeText(pNodeRow,pNodeData,"ns:return",temp,XMLRW_MAX_STR))
		{
			printf("ns:return=%s\n",temp);
		}
	}

	if(0!=strcmp(temp,"0000"))
	{
		sprintf(failstr,"���س���:%s",temp);
		printf("%s\n",failstr);
		CService.DestroyData();
		return false;
	}

	CService.DestroyData();

	return true;

}

#endif
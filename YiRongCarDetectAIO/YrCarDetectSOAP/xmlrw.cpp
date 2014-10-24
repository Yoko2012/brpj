
#include "xmlrw.h"

#if defined( WIN32 ) && defined( TUNE )
#include <crtdbg.h>
_CrtMemState startMemState;
_CrtMemState endMemState;
#endif


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
	wchar_t * wbuff=(wchar_t *)calloc(len+4,sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, -1, wbuff, len+2);  
	// buffLen = WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, NULL, 0, 0, 0);  
	//  utf8 = new char[buffLen+1];  
	WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, (LPSTR)utf8, len*2+4, 0, 0); 
	free(wbuff);
}

void UTF82CHAR(const char *utf8,char *str,unsigned long int len)
{
	wchar_t * wbuff=(wchar_t *)calloc(len,sizeof(wchar_t));
	//	int buffLen = 0;  
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wbuff, len+2);  
	//	buffLen = WideCharToMultiByte(CP_ACP, 0, wbuff, -1, NULL, 0, 0, 0);  
	//	m_gb2312 = new char[buffLen+1];  
	WideCharToMultiByte(CP_ACP, 0, wbuff, -1, (LPSTR)str, len*2+4, 0, 0);  
	free(wbuff);
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



bool CreateXMLData(TiXmlElement *prow,string attr,const char *valuedata,char *strText,unsigned long int len,bool cdataflag,bool utf8flag)
{
	// �����ӽڵ㣺data  
	TiXmlElement *pdata = new TiXmlElement(attr);  
	if (NULL==pdata)  
	{  
		return false;  
	}  
	prow->LinkEndChild(pdata);  
	//���
	TiXmlText *pdataValue;
	if(utf8flag)
	{
		//ת��
		CHAR2UTF8(valuedata,strText,len);
		//���
		pdataValue = new TiXmlText(strText);  
	}
	else
	{
		//���
		pdataValue = new TiXmlText(valuedata);  
	}

	pdata->LinkEndChild(pdataValue); 
	//�м�CDATA���
	pdataValue->SetCDATA(cdataflag); 
	return true;
}

bool CreateXMLDataForDoc(TiXmlDocument *prow,string attr,const char *valuedata,char *strText,unsigned long int len,bool cdataflag,bool utf8flag)
{
	// �����ӽڵ㣺data  
	TiXmlElement *pdata = new TiXmlElement(attr);  
	if (NULL==pdata)  
	{  
		return false;  
	}  
	prow->LinkEndChild(pdata);  
	//���
	TiXmlText *pdataValue;
	if(utf8flag)
	{
		//ת��
		CHAR2UTF8(valuedata,strText,len);
		//���
		pdataValue = new TiXmlText(strText);  
	}
	else
	{
		//���
		pdataValue = new TiXmlText(valuedata);  
	}

	pdata->LinkEndChild(pdataValue); 
	//�м�CDATA���
	pdataValue->SetCDATA(cdataflag); 
	return true;
}



//����CDATA����  ��������
bool CreateXmlLite_UTF8_NoSub(char *name,struct NAME_VALUE_S mapdata[],int maplen,
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
		if(!CreateXMLData(pRootEle,
			mapdata[it].namestr.c_str(),
			mapdata[it].valuestr.c_str(),
			strText,len,
			false,false))
			return false;
	}

	//�����ļ�
	//pDoc.SaveFile("d:\\1.xml");

	//���浽�ַ���
	TiXmlPrinter printer;
	pDoc.Accept(&printer);
	//	strResult.Format("%s", printer.CStr());
	strcpy(strText,printer.CStr());

	//printf("xml=\n%s\n",strText);

	return true;  
}   



//����CDATA����  ��һ������ ֻ�ܼ�һ��
bool CreateXmlLite_UTF8_OneSub(char *name,struct NAME_VALUE_S mapdata[],int maplen,
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
		if(!CreateXMLData(pRootEle,
			mapdata[it].namestr.c_str(),
			mapdata[it].valuestr.c_str(),
			strText,len,
			false,false))
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
		if(!CreateXMLData(pSub2Ele,
			subdata[it].namestr.c_str(),
			subdata[it].valuestr.c_str(),
			strText,len,
			false,false))
			return false;
	}

	//�����ļ�
	//pDoc.SaveFile("d:\\1.xml");

	//���浽�ַ���
	TiXmlPrinter printer;
	pDoc.Accept(&printer);
	//	strResult.Format("%s", printer.CStr());
	strcpy(strText,printer.CStr());

	//printf("xml=\n%s\n",strText);

	return true;  
}  


//���Ľ���
bool ReadXML_UTF8_NoSub(const char *utf8xmlin,struct NAME_VALUE_S mapdata[],int maplen)
{
	//����ջ�� �ڴ治��й¶
	TiXmlDocument myDocument;
	myDocument.Parse(utf8xmlin);

	TiXmlElement *pRootEle = myDocument.RootElement();
	if (NULL==pRootEle)
	{
		printf("ReadXML_UTF8_NoSub XML����\n");
		return false;
	}

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	char tempstr[XMLRW_MAX_WSTR];

	for(int i=0;i<maplen;i++)
	{
		for(pNodeRow = pRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
		{
			pNodeData = NULL;
			if(ReadQueryNodeText(pNodeRow,pNodeData,mapdata[i].namestr,tempstr,XMLRW_MAX_WSTR,false))
			{
				mapdata[i].valuestr=tempstr;
				break ;
			}
		}
	}
	
	return true;
}

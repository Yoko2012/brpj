#include "stdafx.h"
#include "yirongcardetectaio.h"

#include "DLGBlackInOut.h"
extern CDLGBlackInOut *pDlgBlackInout;

#include "xmlrw.h"
////////////////////////////////
#include "IO.h"
extern IO OracleIO;
////////////////////////////////

#if defined( WIN32 ) && defined( TUNE )
#include <crtdbg.h>
_CrtMemState startMemState;
_CrtMemState endMemState;
#endif

XMLRW::XMLRW()
{

}

XMLRW::~XMLRW()
{

}

void XMLRW::CHAR2UTF8(const char *str,char *utf8)
{
	// int buffLen = 0;  
	MultiByteToWideChar(CP_ACP, 0, str, -1, wbuff, XMLRW_MAX_WSTR);  
	// buffLen = WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, NULL, 0, 0, 0);  
	//  utf8 = new char[buffLen+1];  
	WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, (LPSTR)utf8, XMLRW_MAX_STR, 0, 0);  
}

void XMLRW::UTF82CHAR(const char *utf8,char *str)
{
//	int buffLen = 0;  
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wbuff, XMLRW_MAX_WSTR);  
//	buffLen = WideCharToMultiByte(CP_ACP, 0, wbuff, -1, NULL, 0, 0, 0);  
//	m_gb2312 = new char[buffLen+1];  
	WideCharToMultiByte(CP_ACP, 0, wbuff, -1, (LPSTR)str, XMLRW_MAX_STR, 0, 0);  
}

bool XMLRW::CreateData(TiXmlElement *prow,string attr,char *value)
{
	// �����ӽڵ㣺data  
	TiXmlElement *pdata = new TiXmlElement(attr);  
	if (NULL==pdata)  
	{  
        return false;  
	}  
	prow->LinkEndChild(pdata);  
	//ת��
	CHAR2UTF8(value,DstStr);
	//���
	TiXmlText *pdataValue = new TiXmlText(DstStr);  
	pdata->LinkEndChild(pdataValue); 
	return true;
}

bool XMLRW::CreateRow(TiXmlElement *pRootEle,unsigned long int i)
{
	struct BLACK_DATA_ST data={0};

	//ȡһ������
#if ALLTAB_DETECT_CAR_MODE
//����
	if(OracleIO.CAR_BlackTable_ReadOne(i,data))
#else
//�綯��
	if(OracleIO.ELECAR_BlackTable_ReadOne(i,data))
#endif
	{
		// �����ӽڵ㣺row
		TiXmlElement *prow = new TiXmlElement(_T("ROW"));  
		if (NULL==prow)  
		{  
			return false;  
		}  
		pRootEle->LinkEndChild(prow);  
		
		if(!CreateData(prow,"SCARNUMBER",data.plate))
			return false;
		if(!CreateData(prow,"SBRAND",data.brand))
			return false;
		if(!CreateData(prow,"SLOSTNAME",data.name))
			return false;
		if(!CreateData(prow,"SPHONE",data.Phone))
			return false;
		if(!CreateData(prow,"SMARK",data.other))
			return false;
	}
	return true;
}

bool XMLRW::CreateXml(char* XmlFile)  
{  
	// ����һ��TiXmlDocument��ָ��  
	TiXmlDocument *pDoc = new TiXmlDocument;  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration(_T("1.0"),_T("utf-8"),_T(""));  
	if (NULL==pDeclaration)  
	{  
		return false;  
    }  

	pDoc->LinkEndChild(pDeclaration);  
	// ����һ�����ڵ㣺pRootEle 
	TiXmlElement *pRootEle = new TiXmlElement(_T("ROWDATA"));  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	pDoc->LinkEndChild(pRootEle);  

#if ALLTAB_DETECT_CAR_MODE
//����
	total=OracleIO.CAR_BlackTable_GetNum();

#else
//�綯��
	total=OracleIO.ELECAR_BlackTable_GetNum();

#endif
	if(0==total)
	{
		pDlgBlackInout->m_info.Format("���ݿ�������");
		pDlgBlackInout->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(pDlgBlackInout->m_info);
		return true;
	}

	unsigned long int i;
	//���ý�����
	pDlgBlackInout->m_progress.SetRange32(0,total);
	pDlgBlackInout->m_progress.SetStep(1);

	//��N������ ����N�����
	for(i=1; (pDlgBlackInout->ThreadFlag) && (i<=total) ;i++)
	{
		if(!CreateRow(pRootEle,i))
			break;
		//��д����
		pDlgBlackInout->m_progress.StepIt();
		pDlgBlackInout->m_info.Format("�ѵ���:%d / %d ��",i,total);
		pDlgBlackInout->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(pDlgBlackInout->m_info);
	}
	//�����ļ�
	pDoc->SaveFile(XmlFile);  
    return true;  
}   

////////////////////////////////////////////////////////


/*!
*  \brief ͨ�����ڵ�ͽڵ�����ȡ�ڵ�ָ�롣
*
*  \param pRootEle   xml�ļ��ĸ��ڵ㡣
*  \param strNodeName  Ҫ��ѯ�Ľڵ���
*  \param Node      ��Ҫ��ѯ�Ľڵ�ָ��
*  \return �Ƿ��ҵ���trueΪ�ҵ���Ӧ�ڵ�ָ�룬false��ʾû���ҵ���Ӧ�ڵ�ָ�롣
*/
bool XMLRW::ReadGetNodePointerByName(TiXmlElement* pRootEle,string strNodeName,TiXmlElement* &Node)
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
bool XMLRW::ReadQueryNodeText(TiXmlElement *pRootEle,TiXmlElement* &FindNode,string strNodeName,char *strText)
{
	ReadGetNodePointerByName(pRootEle,strNodeName,FindNode);
	if (NULL!=FindNode)
	{
        const char* psz = FindNode->GetText(); 
		if (NULL==psz)
			strText[0] =0;
		else	//ת��
			UTF82CHAR(psz,strText);
		return true;
	}
	else
	{
		strText[0] =0;
        return false;
	}
}

bool XMLRW::ReadXml(char *XmlFile)
{
   // ����һ��TiXmlDocument��ָ��
    TiXmlDocument *pDoc = new TiXmlDocument(XmlFile);
    if (NULL==pDoc)
    {
        return false;
    }
    pDoc->LoadFile(TIXML_ENCODING_UTF8);
    TiXmlElement *pRootEle = pDoc->RootElement();
    if (NULL==pRootEle)
    {
        return false;
    }

	pDlgBlackInout->GetDlgItem(IDC_STATIC_INFO)->SetWindowText("�Ѷ�ȡ: 0 ��");

	char temp[XMLRW_MAX_STR];
	struct BLACK_DATA_ST data={0};

	TiXmlElement *pNodeRow = NULL;
	TiXmlElement *pNodeData = NULL;

	unsigned long int i=1;

	for(pNodeRow = pRootEle; pNodeRow; pNodeRow = pNodeRow->NextSiblingElement())
	{
		memset(&data,0,sizeof(struct BLACK_DATA_ST));

		//��ȡ��Ϣ
		if(ReadQueryNodeText(pNodeRow,pNodeRow,"ROW",temp))
		{
			pNodeData = NULL;
			ReadQueryNodeText(pNodeRow,pNodeData,"SCARNUMBER",data.plate);
		
			pNodeData = NULL;
			ReadQueryNodeText(pNodeRow,pNodeData,"SBRAND",data.brand);
		
			pNodeData = NULL;
			ReadQueryNodeText(pNodeRow,pNodeData,"SLOSTNAME",data.name);
	
			pNodeData = NULL;
			ReadQueryNodeText(pNodeRow,pNodeData,"SPHONE",data.Phone);
	
			pNodeData = NULL;
			ReadQueryNodeText(pNodeRow,pNodeData,"SMARK",data.other);

			//���ƺ�Ϊ��
			if(0==strlen(data.plate))
				continue ;
			
			//д��һ��
#if ALLTAB_DETECT_CAR_MODE
			//����
			if(OracleIO.CAR_BlackTable_AddNew(data))
			
#else
			//�綯��
			if(OracleIO.ELECAR_BlackTable_AddNew(data))
			
#endif
			{
				pDlgBlackInout->m_info.Format("�ѵ���: %d ��",i);
				pDlgBlackInout->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(pDlgBlackInout->m_info);

				i++;
			}
		}
		
	}

	return true;

}

/*
void main()
{

XMLRW a;

a.CreateXml("a.xml");

a.ReadXml("oracle_out.xml");
}
*/
// FaceLoginOCXCtrl.cpp : Implementation of the CFaceLoginOCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "FaceLoginOCX.h"
#include "FaceLoginOCXCtrl.h"
#include "FaceLoginOCXPropPage.h"
#include "FrmFaceMatch.h"
#include "FrmFaceEnroll.h"

//�������������õ���������
CFaceLoginOCXCtrl *DlgFaceLoginOCXCtrl;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CFaceLoginOCXCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CFaceLoginOCXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CFaceLoginOCXCtrl, COleControl)
	DISP_FUNCTION_ID(CFaceLoginOCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CFaceLoginOCXCtrl, "StartFaceMacth", dispidFaceMacth, StartFaceMacth, VT_BSTR, VTS_BSTR VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CFaceLoginOCXCtrl, "StartFaceEnroll", dispidFaceEnroll, StartFaceEnroll, VT_I2, VTS_BSTR VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CFaceLoginOCXCtrl, "GetCamNum", dispidGetCamNum, GetCamNum, VT_I2, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CFaceLoginOCXCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CFaceLoginOCXCtrl, 1)
	PROPPAGEID(CFaceLoginOCXPropPage::guid)
END_PROPPAGEIDS(CFaceLoginOCXCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CFaceLoginOCXCtrl, "FACELOGINOCX.FaceLoginOCXCtrl.1",
	0xaefa1f7c, 0xf5a9, 0x44b3, 0x86, 0xb8, 0x53, 0xd5, 0x86, 0xca, 0xaf, 0xab)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CFaceLoginOCXCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DFaceLoginOCX =
		{ 0xBB80CCC6, 0x8390, 0x477C, { 0x91, 0xD5, 0x2C, 0xF3, 0x35, 0x48, 0x94, 0x2 } };
const IID BASED_CODE IID_DFaceLoginOCXEvents =
		{ 0xF73D1D70, 0x33B6, 0x4CBD, { 0xB8, 0x70, 0xA7, 0xD1, 0x43, 0xA1, 0xA9, 0xAD } };



// Control type information

static const DWORD BASED_CODE _dwFaceLoginOCXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CFaceLoginOCXCtrl, IDS_FACELOGINOCX, _dwFaceLoginOCXOleMisc)

/////////////ZOGNA//////DOWN////////��ȫ//����JSP�޷�����////////
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)
{

	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (FAILED(hr))
		return hr;

	// Make sure the HKCR\Component Categories\{..catid...}

	// key is registered

	CATEGORYINFO catinfo;
	catinfo.catid = catid;
	catinfo.lcid = 0x0409 ; // english


	// Make sure the provided description is not too long.

	// Only copy the first 127 characters if it is

	int len = wcslen(catDescription);
	if (len>127)
		len = 127;
	wcsncpy(catinfo.szDescription, catDescription, len);
	// Make sure the description is null terminated

	catinfo.szDescription[len] = '\0';

	hr = pcr->RegisterCategories(1, &catinfo);
	pcr->Release();

	return hr;
}


HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	// Register your component categories information.

	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Register this category as being "implemented" by

		// the class.

		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
	}

	if (pcr != NULL)
		pcr->Release();

	return hr;
}

HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Unregister this category as being "implemented" by

		// the class.

		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
	}

	if (pcr != NULL)
		pcr->Release();

	return hr;
}
BOOL CFaceLoginOCXCtrl::CFaceLoginOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
	{
		HRESULT hr = S_OK ;

		// register as safe for scripting

		hr = CreateComponentCategory(CATID_SafeForScripting,
			L"Controls that are safely scriptable");

		if (FAILED(hr))
			return FALSE;

		hr = RegisterCLSIDInCategory(m_clsid, CATID_SafeForScripting);

		if (FAILED(hr))
			return FALSE;

		// register as safe for initializing

		hr = CreateComponentCategory(CATID_SafeForInitializing,
			L"Controls safely initializable from persistent data");

		if (FAILED(hr))
			return FALSE;

		hr = RegisterCLSIDInCategory(m_clsid, CATID_SafeForInitializing);

		if (FAILED(hr))
			return FALSE;

		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_FACELOGINOCX,
			IDB_FACELOGINOCX,
			afxRegInsertable | afxRegApartmentThreading,
			_dwFaceLoginOCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	}
	else
	{
		HRESULT hr = S_OK ;

		hr = UnRegisterCLSIDInCategory(m_clsid, CATID_SafeForScripting);

		if (FAILED(hr))
			return FALSE;

		hr = UnRegisterCLSIDInCategory(m_clsid, CATID_SafeForInitializing);

		if (FAILED(hr))
			return FALSE;

		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
	}
}

/////////////ZOGNA////////UP//////��ȫ//����JSP�޷�����////////

//// CFaceLoginOCXCtrl::CFaceLoginOCXCtrlFactory::UpdateRegistry -
//// Adds or removes system registry entries for CFaceLoginOCXCtrl
//
//BOOL CFaceLoginOCXCtrl::CFaceLoginOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
//{
//	// TODO: Verify that your control follows apartment-model threading rules.
//	// Refer to MFC TechNote 64 for more information.
//	// If your control does not conform to the apartment-model rules, then
//	// you must modify the code below, changing the 6th parameter from
//	// afxRegApartmentThreading to 0.
//
//	if (bRegister)
//		return AfxOleRegisterControlClass(
//			AfxGetInstanceHandle(),
//			m_clsid,
//			m_lpszProgID,
//			IDS_FACELOGINOCX,
//			IDB_FACELOGINOCX,
//			afxRegApartmentThreading,
//			_dwFaceLoginOCXOleMisc,
//			_tlid,
//			_wVerMajor,
//			_wVerMinor);
//	else
//		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
//}



// CFaceLoginOCXCtrl::CFaceLoginOCXCtrl - Constructor

CFaceLoginOCXCtrl::CFaceLoginOCXCtrl()
{
	InitializeIIDs(&IID_DFaceLoginOCX, &IID_DFaceLoginOCXEvents);
	// TODO: Initialize your control's instance data here.
	DlgFaceLoginOCXCtrl = this;
}



// CFaceLoginOCXCtrl::~CFaceLoginOCXCtrl - Destructor

CFaceLoginOCXCtrl::~CFaceLoginOCXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CFaceLoginOCXCtrl::OnDraw - Drawing function

void CFaceLoginOCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CFaceLoginOCXCtrl::DoPropExchange - Persistence support

void CFaceLoginOCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CFaceLoginOCXCtrl::OnResetState - Reset control to default state

void CFaceLoginOCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CFaceLoginOCXCtrl::AboutBox - Display an "About" box to the user

void CFaceLoginOCXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_FACELOGINOCX);
	dlgAbout.DoModal();
}



// CFaceLoginOCXCtrl message handlers
/************************************
* �����ȶ�
*************************************/
BSTR CFaceLoginOCXCtrl::StartFaceMacth(LPCTSTR strFaceServer,int sysID,LPCTSTR user,LPCTSTR password)
{
	CString strlog;
	strlog.Format(_T("<TIPS><MATCH> - Start Match - User<%s>"),user);
	ShowOcxLog(strlog);

	CCommon m_Common;
	if(m_Common.GetCamNum() < 1)
	{
		CString ret;
		ret.Format(_T("%d"),OCX_ERROR_NO_ERROR);
		return ret.AllocSysString();//δ��⵽����ͷֱ�ӷ���
	}
	CString sMd5;
	CString temp = password;
	sMd5 = m_Common.EncodeMd5(temp.GetBuffer());

	MatchUser = user;
	MatchSysID = sysID;
	CFrmFaceMatch faceMatch;
	int checkReslut = faceMatch.m_Detect.CheckMatchInfo(strFaceServer,sysID,user,sMd5);
	if(checkReslut == ERR_NONEED_MATCH)		//����Ҫ����ʶ��
	{
		faceMatch.MacthResult = faceMatch.m_Detect.Token;
		return faceMatch.MacthResult.AllocSysString();;//��������
	}
	else if(checkReslut == ERR_BAD_USER)
	{
		CString ret;
		ret.Format(_T("%d"),OCX_ERROR_UNALLOW_USER);
		return ret.AllocSysString();//�Ƿ��û�ֱ�ӷ���
	}
	else if(checkReslut == ERR_NONEED_MATCH)		//����Ҫ����ʶ��
	{
		CString ret;
		ret.Format(_T("%d"),OCX_ERROR_FACESERVER_DOWN);
		return ret.AllocSysString();//ƽ̨�쳣ֱ�ӷ���
	}

	if(faceMatch.m_Detect.GetFaceCloudState())
	{
		faceMatch.DoModal();
	}
	else
	{
		faceMatch.MacthLog.Format(_T("{\
											\"ret\":\"fail\",\
											\"user\":\"%s\",\
											\"sysID\":\"%d\",\
											\"content\":\"FaceServer_Out_of_Service\"\
											}"),user,sysID);
		CString ret;
		ret.Format(_T("%d"),OCX_ERROR_FACESERVER_DOWN);
		return ret.AllocSysString();//facecloud�쳣ֱ�ӷ���
	}

	faceMatch.m_Detect.SendMatchLog(strFaceServer,faceMatch.MacthLog);

	return faceMatch.MacthResult.AllocSysString();
}

/************************************
* ����ע��
* strFaceServer -- ƽ̨�����ַ ��ʽΪ"http://10.142.50.125:9080"
* sysID			-- ����ϵͳID
* user			-- ��ע���û���
* password		-- ��ע���û�����
* return		-- �ɹ�����ʧ��
*************************************/
int CFaceLoginOCXCtrl::StartFaceEnroll(LPCTSTR strFaceServer,int sysID,LPCTSTR user,LPCTSTR password)
{
strFaceServer="http://10.142.50.248:8087/frcs";

	sysID = 13;
	user="linhp";
	password="96E79218965EB72C92A549DD5A330112";
	CString strlog;
	strlog.Format(_T("<TIPS><ENROLL> - Start Enroll - User<%s>"),user);
	ShowOcxLog(strlog);

	//CString result = _T("");
	CCommon m_Common;
	if(m_Common.GetCamNum() < 1)
	{
		return OCX_ERROR_NO_CAMERA;
	}
	int ret = 0;
	//CString sMd5;
	//CString temp = password;
	//sMd5 = m_Common.EncodeMd5(temp.GetBuffer());
	EnrollUser = user;
	EnrollSysID = sysID;
	CFrmFaceEnroll faceEnroll;
	int result = faceEnroll.m_Detect.CheckRegInfo(strFaceServer,sysID,user,password);
	if(result == ERR_BAD_USER)
	{
		ret =  OCX_ERROR_UNALLOW_USER;
		return ret;//�Ƿ��û�ֱ�ӷ���
	}
	else if(result == ERR_SER_REEOR)
	{
		ret =  OCX_ERROR_FACESERVER_DOWN;
		return ret;//ƽ̨�쳣ֱ�ӷ���
	}

	if(faceEnroll.m_Detect.GetFaceCloudState())
	{
		faceEnroll.DoModal();
		ret = faceEnroll.EnrollResult;
	}
	else
	{
		faceEnroll.EnrollLog.Format(_T("{\
											\"ret\":\"fail\",\
											\"user\":\"%s\",\
											\"sysID\":\"%d\",\
											\"content\":\"FaceServer_Out_of_Service\"\
											}"),user,sysID);
		ret =  OCX_ERROR_FACESERVER_DOWN;
	}

	faceEnroll.m_Detect.SendEnrollLog(strFaceServer,faceEnroll.EnrollLog);

	return ret;
}

/************************************
* ��ȡ����ͷ����
*************************************/
int CFaceLoginOCXCtrl::GetCamNum(void)
{
	CCommon m_Common;
	return m_Common.GetCamNum();
}

/************************************
* ��ӡocx��־
*************************************/
void CFaceLoginOCXCtrl::ShowOcxLog(CString log)
{
	CString strInfo;
	CTime tm = CTime::GetTickCount();

	strInfo.Format(_T("%04d-%02d-%02d %02d:%02d:%02d  :  %s\n"),tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																tm.GetHour(),tm.GetMinute(),tm.GetSecond(),log);
	FILE *fp = NULL;
	fp = fopen(OCX_LOG_PATH,"a+");
	if(fp)
	{
		fprintf(fp,strInfo);
		fclose(fp);
	}
}


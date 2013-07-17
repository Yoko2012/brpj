#if !defined(AFX_DLGPLANRECORD_H__309F611A_A249_48EF_9CD6_37E214A55BD9__INCLUDED_)
#define AFX_DLGPLANRECORD_H__309F611A_A249_48EF_9CD6_37E214A55BD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlanRecord.h : header file
//
#include "IOoracle.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPlanRecord dialog
#define LISTMAX_NUM 10
#define FTPMAX_NUM 100

//�������ӿ�
typedef struct 
{
//	char policeID[64];
	long int camID;
//	char sername[64];                    //server name
//	char username[32];                   //user name
//	char password[32];                   //password
//	char url[64];                       //url
//	WORD port;

}RECORD_CLIENTINFO;

/*
starthhmm����ʼСʱ���ӣ�
stophhmm������Сʱ���ӣ�
maskweek��
0�������죻
1������һ��
2�����ڶ���
3����������
4�������ģ�
5�������壻
6����������
7������һ���������壻
8�����������������죻
9��ÿ�죻
10���رգ���ʹ�ø�ʱ��Σ�
*/
typedef struct 
{
	int starthhmm;
	int stophhmm;
	unsigned char maskweek;
}RECORD_WEEKPLAN;

/*
startyyyymmdd����ʼ������
starthhmm����ʼСʱ���ӣ�
stopyyyymmdd:����������
stophhmm������Сʱ���ӣ�
maskday:
0���رգ���ʹ�ø�ʱ���
1��������ʹ�ø�ʱ���
*/
typedef struct 
{
	unsigned long int startyyyymmdd;
	int  starthhmm;
	unsigned long int stopyyyymmdd;
	int  stophhmm;
	BOOL maskday;
}RECORD_DAYPLAN;

// DIR �ļ�Ŀ¼ ��Ҫ�������ġ�\\������ ����C:TEMP
// CutTime ÿ�μ�����ٷ��Ӿͷָ�һ���ļ� ��� 60*23����
typedef struct 
{
	unsigned char CutTime;
	TCHAR DIR[MAX_PATH]; 
}RECORD_FILE;

//¼��״̬
//0 δ��ʼ¼��
//1 ����¼��
//2 �ź��жϻ�ʧ��  
//3 ��ͣ¼��
//4 ��ʱ׼��¼�� ����ֹ����������¼�ƣ�
//unsigned char Status;
enum 
{
	RECORD_STOP=0,
	RECORD_START=1,
	RECORD_LOST=2,
	RECORD_PAUSE=3,
	RECORD_PLANSTART=4,
	RECORD_UNKOWN=100
};

typedef struct 
{
	//���ر�����ļ�·��
	TCHAR localpath[MAX_PATH]; 
	//�ļ���
	TCHAR filename[MAX_PATH]; 
	//��Ա���·��
	TCHAR ftppath[MAX_PATH];
	TCHAR netpath[MAX_PATH]; 

	//���ر�����ļ�·��
	TCHAR localAVIpath[MAX_PATH]; 
	//�ļ���
	TCHAR AVIfilename[MAX_PATH]; 
	//��Ա���·��
	TCHAR AVIftppath[MAX_PATH];
	TCHAR AVInetpath[MAX_PATH]; 

	//��Ƶ��ʼʱ��
	CTime stime;
	//��Ƶ����ʱ��
	CTime etime;
	//Ԥ��ֹͣ��¼��ʱ��
	int hour;
	int min;
	unsigned char status;
	unsigned char planweek; //����1 �ر�0
	unsigned char planday;  //����1 �ر�0

}RECORD_STATUS;

typedef struct
{
	//���ر���ľ����ļ�·�� D:\40\1.mp4
	TCHAR localpath[MAX_PATH]; 
	//�ļ���
	TCHAR filename[MAX_PATH]; 
	//FTP��Ա���·�� /40/1.mp4
	TCHAR ftppath[MAX_PATH]; 
	//����ӳ����Ա���·�� \40\1.mp4
	TCHAR netpath[MAX_PATH]; 

	//���ر���ľ����ļ�·�� D:\40\1.avi
	TCHAR localAVIpath[MAX_PATH]; 
	//�ļ���
	TCHAR AVIfilename[MAX_PATH]; 
	//��Ա���·��
	TCHAR AVIftppath[MAX_PATH];
	TCHAR AVInetpath[MAX_PATH]; 


	//��Ƶ��ʼʱ��
	CTime stime;
	//��Ƶ����ʱ��
	CTime etime;
	//����ͷID
	long camid;
	//�߳̾��
	HANDLE pthread;
	//�߳�����=false  �߳�δ��=ture
	bool ThreadFlag;
	//�̲߳���=false  �߳�ǿ��=ture
//	bool forceout;

}FTP_RECORD;

class CDlgPlanRecord : public CDialog
{
	// Construction
public:
	CDlgPlanRecord(CWnd* pParent = NULL);   // standard constructor

	void Lost(long int handle);
	void CheckTime(BOOL link,long int handle,
		 int year,int mon,int day,int hour, int min,int week);
	// Dialog Data
	//{{AFX_DATA(CDlgPlanRecord)
	enum { IDD = IDD_PLANRECORD };
	CListCtrl	m_listAlarm;
	int		m_PlanDayList;
	BOOL	m_PlanDayMask;
	int		m_PlanWeekList;
	int		m_PlanWeekMask;
	CTime	m_PlanDayYMDS;
	CTime	m_PlanDayYMDE;
	CTime	m_PlanDayHME;
	CTime	m_PlanDayHMS;
	CTime	m_PlanWeekHME;
	CTime	m_PlanWeekHMS;
	BYTE	m_Cuttime;
	CString	m_PlanDir;
	int		m_planmode;
	//}}AFX_DATA
	RECORD_WEEKPLAN weekplan[LISTMAX_NUM];
	RECORD_DAYPLAN dayplan[LISTMAX_NUM];
	RECORD_FILE FileDir;
	RECORD_CLIENTINFO info;
	RECORD_STATUS RecordStatus;
	long int m_hHandle;


	int modeflag; //0=��ģ�� 1=ģ��
	int modeexec;//ִ�б����info.camid ��ִ�б���=10

	CTime	Disp_PlanDayYMDS[LISTMAX_NUM];
	CTime	Disp_PlanDayYMDE[LISTMAX_NUM];
	CTime	Disp_PlanDayHME[LISTMAX_NUM];
	CTime	Disp_PlanDayHMS[LISTMAX_NUM];
	CTime	Disp_PlanWeekHME[LISTMAX_NUM];
	CTime	Disp_PlanWeekHMS[LISTMAX_NUM];

	// Overrides
	FTP_RECORD FtpRecord[FTPMAX_NUM];

	//����������ȡ������
	
	BOOL PlanReadALLC(long int id) ;
	void PlanSaveALLC();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlanRecord)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL



	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlanRecord)
	afx_msg void OnBUTTONPlanDaySave();
	afx_msg void OnBUTTONPlanWeekSave();
	afx_msg void OnBUTTONPlanSetSave();
	afx_msg void OnBUTTONPlanDayStart();
	afx_msg void OnBUTTONPlanWeekStart();
	afx_msg void OnBUTTONPlanDir();
	afx_msg void OnCHECKPlanDayMask();
	afx_msg void OnCloseupCOMBOPlanWeekList();
	afx_msg void OnCloseupCOMBOPlanDayList();
	afx_msg void OnCloseupCOMBOPlanWeekMask();
	afx_msg void OnBUTTONPlanDayRead();
	afx_msg void OnBUTTONPlanWeekRead();
	afx_msg void OnBUTTONsaveall();
	afx_msg void OnCloseupCOMBOMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	void DialogDisplayDay();
	void DialogDisplayWeek();
	void PlanWeekSaveList(int list);
	void PlanDaySaveList(int list);

	BOOL PlanWeekRecordTimeRange(int weekplan_total,int  hour, int min,int week);

	BOOL PlanDayRecordTimeRange(int dayplan_total,int year,int mon,int day,int hour, int min);

	BOOL LocalRecordCheckTime(int  hour, int min);
	void LocalRecordStart(BOOL link);
	void LocalRecordStop();

	void AlarmMassage(int status,int type,int num,int flag,const char *stime,const char *etime);
	void AlarmMassageSet(void);

	void PlanReadALL() ;
	//void PlanSetRead();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLANRECORD_H__309F611A_A249_48EF_9CD6_37E214A55BD9__INCLUDED_)

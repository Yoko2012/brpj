// VideoChannel.h: interface for the CVideoChannel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOCHANNEL_H__D1736789_C3E0_4E20_88A2_304B89946F22__INCLUDED_)
#define AFX_VIDEOCHANNEL_H__D1736789_C3E0_4E20_88A2_304B89946F22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct RECORD_INFO_ST
{
	HANDLE pthread;
	int ThreadFlag;

	char RunningNumber[256];	
	char tag[256];
	char HmNum[256];
	char Description[2560];		

	//��ʼʱ��
	char stime[32];
	//����ʱ��
	char etime[32];

	unsigned long int size;	//�ļ���С
	char MP4path[260];		//�ļ�·��
	char AVIpath[260];		//�ļ�·��
};

class CYaanCamera  
{
public:
	CYaanCamera();
	virtual ~CYaanCamera();
public:
	int         m_playhandle[MAX_PLAYWIN];  //���ž��
	BOOL        m_bplay[MAX_PLAYWIN];
	BOOL        m_brecord[MAX_PLAYWIN];
	struct RECORD_INFO_ST record[MAX_PLAYWIN];	//����¼����Ϣ
public:
	void		SDKinit();
	bool		StartPlay(int nCuWinID,char *name,char *sip,WORD port,char *user,char *psw,HWND hWnd);
	void        StopPlay(int nCuWinID);

	void        CapturePic(int nCuWinID,char *filename);
	int         StartRecord(int nCuWinID,LPCSTR filename);
	int         StopRecord(int nCuWinID);
	void		ConvertMp4ToAvi(struct RECORD_INFO_ST file);
};

#endif // !defined(AFX_VIDEOCHANNEL_H__D1736789_C3E0_4E20_88A2_304B89946F22__INCLUDED_)

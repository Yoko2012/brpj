// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DA1368DB_F92F_4AAE_86E3_70C4BF842BE0__INCLUDED_)
#define AFX_STDAFX_H__DA1368DB_F92F_4AAE_86E3_70C4BF842BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

	////�Ĳ˵�����ɫҪ�Ķ��� �ŵ�STDAFX.H
	//#ifndef WINVER
	//#define WINVER 0x0501 
	//#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxdisp.h>        // MFC Automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxtempl.h>
#endif // _AFX_NO_AFXCMN_SUPPORT



// ��̨��������
typedef enum _PTZ_Command
{
	PTZ_CONTROL_UP = 0,							//��
	PTZ_CONTROL_DOWN = 1,								// ��
	PTZ_CONTROL_LEFT = 2,								// ��
	PTZ_CONTROL_RIGHT = 3,								// ��
	PTZ_CONTROL_ZOOM_ADD = 4,							// �䱶+
	PTZ_CONTROL_ZOOM_SUB = 5,						// �䱶-
	PTZ_CONTROL_FOCUS_ADD = 6,							// ����+
	PTZ_CONTROL_FOCUS_SUB = 7,						// ����-
	PTZ_CONTROL_IRIS_ADD = 8,							// ��Ȧ+
	PTZ_CONTROL_IRIS_SUB = 9,							// ��Ȧ-
	PTZ_CONTROL_POINT_MOVE = 10,						// ��ת��Ԥ���
	PTZ_CONTROL_POINT_SET = 11,						// Ԥ�������
	PTZ_CONTROL_UPLEFT = 12,							// ����
	PTZ_CONTROL_UPRIGHT = 13,							// ����
	PTZ_CONTROL_DOWNLEFT = 14,							// ����
	PTZ_CONTROL_DOWNRIGHT = 15,							// ����
	PTZ_CONTROL_SPEED_ADD = 16,						// ��̨�ٶ�+
	PTZ_CONTROL_SPEED_SUB = 17,							// ��̨�ٶ�-
	PTZ_CONTROL_AUTO = 18,							// �Զ�
} PTZ_Command;

//0---����,1---��
enum DEVICE_VENDERID_ENUM
{
	VENDER_TYPE_HAIKANG=0, 
	VENDER_TYPE_DAHUA=1, 
	VENDER_TYPE_YAAN=2, 
	VENDER_TYPE_YAAN_NEW=3, 
	VENDER_TYPE_STREAM=4, 
};

enum DEVICE_DECODETAG_ENUM
{
	DECODETAG_PS=0, //HAIKANG
	DECODETAG_SRC=1, //DAHUA
};


//����ͷ����
#define OPEN_YAAN_NEW_SDK 0
#define OPEN_YAAN_SDK 0
#define OPEN_DAHUA_SDK 1
#define OPEN_HAIKANG_SDK 1

#define DB33_PLAYCTRL
#define OPEN_STREAM_CLIENT_SDK 1

//�� SystemTransform.dll ��ͻ ʹ��StreamClientSDK�ĸ���HAIKANSDK��



//���� ʹ��ushow2�Ŀ�
/*************************************
//����ָ�ϣ�Ŀǰ��5��

//����������
ALLTAB_DETECT_CAR_MODE=1
YRVM_PINGTAI_MODE=0

//������YRVMƽ̨��
ALLTAB_DETECT_CAR_MODE=1
YRVM_PINGTAI_MODE=1

//�綯��������
ALLTAB_DETECT_CAR_MODE=0
YRVM_PINGTAI_MODE=0

//�綯��YRVMƽ̨ д��綯���� ��
ALLTAB_DETECT_CAR_MODE=0
YRVM_PINGTAI_MODE=1
YRVM_PINGTAI_ELECAR_MIX_MODE=0

//�綯��YRVMƽ̨ д��������� ��
ALLTAB_DETECT_CAR_MODE=0
YRVM_PINGTAI_MODE=1
YRVM_PINGTAI_ELECAR_MIX_MODE=1

*************************************/

//�ͻ���ģʽ ������ ����ʶ�����Ϊ OPEN_CARDETECT_CODE 0
#define ALLTAB_CLIENT_MODE 0
//����ģʽ 1 �綯��ģʽ 0
//�л��綯����������
//A.�ǵû���IDD�������ﻻLOGO�� �綯���� IDB_LOGO_ELECAR �������� IDB_LOGO
//B.��rc�ļ�������IDR_MAINFRAME��·�� �޸�·�� IDR_MAINFRAME           ICON    DISCARDABLE     "res\\YiRongCarDetectAIO3.ico"
//C.��RES�ļ����� �� YiRongCarDetectAIO.ico �ļ��ö�Ӧ��ͼ���滻��
#define ALLTAB_DETECT_CAR_MODE 0

//��������ʶ�����=1 �ر�=0  �رվͿ��Բ���KEYҲ����DEBUG
#define OPEN_CARDETECT_CODE 0

//���� �о��豸��
#define IVMS_ORACLE_DEVICETREE 1

//���� ����ϵͳ ��Ҫ�����豸��
#define IVMS_KAKOU_SOAP 1


//�������¼ 1 ����������¼0 //Ԥ�� �����Ϊ1
//���½�Ѿ���������� 
//��Ϊ	DlgLogin.SilentMode
#define ALLTAB_LOGIN_WIN_MODE 1

//����POCO-FTP���� ��Ҫ2008����
#define OPEN_VS2008_POCO_FTP	0

//TOMCAT ģʽ
#define OPEN_TOMCAT_MODE 1


//����+�ͻ��� ģʽ
#define OPEN_CS_MODE 1

//////////////////////////////////////////////////////

//��������YRVMƽ̨ �綯��д��������� =1  �綯��д��綯����=0 
#define YRVM_PINGTAI_ELECAR_MIX_MODE	0

//��������ʶ�����=1 �ر�=0  �رվͿ��Բ���KEYҲ����DEBUG
#define OPEN_FACEDETECT_CODE 0

//��������YRVMƽ̨ ģʽ =1  ������=0 
#define YRVM_PINGTAI_MODE	0
///////////////////////////
//�޸����� �ǵð����ݿ����ó��������Ҳ����
//�Լ� ���� �����ַ�
// ���� ������Ƶ���Ʒ���������� δ��������־��
/*
#if OPEN_CARDETECT_CODE
	#if ALLTAB_DETECT_CAR_MODE
		//��������Ŀ
		#define MESSAGEBOX_TITLE "������Ƶ���������Ʒ���������� 2.0��"
	#else
		//��������Ŀ
		#define MESSAGEBOX_TITLE "������Ƶ�綯�����Ʒ���������� 2.0��"
	#endif
#else
	#define MESSAGEBOX_TITLE "������Ƶ���Ʒ���������� 2.0��"
#endif
*/

#if OPEN_CARDETECT_CODE
	#if ALLTAB_DETECT_CAR_MODE
		//��������Ŀ
		#define MESSAGEBOX_TITLE "�������Ż���������ʶ�����Ӧ����� 2.0��"
	#else
		//��������Ŀ
		#define MESSAGEBOX_TITLE "�������ŵ綯������ʶ�����Ӧ����� 2.0��"
	#endif
#else
	#define MESSAGEBOX_TITLE "�������ų���ʶ�����Ӧ����� 2.0��"
#endif

//�����������
#define MAX_AREA 2048

//�����ʾ���ٸ�����ͷ����
#define MAX_DEVICE_NUM 16

//�ǰ���RTSP��ַ rtsp://10.142.50.249:554/0/888888:888888/main

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DA1368DB_F92F_4AAE_86E3_70C4BF842BE0__INCLUDED_)

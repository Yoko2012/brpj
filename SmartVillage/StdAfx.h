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

#define ZOG_MAX_PATH_STR 260

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
	VENDER_TYPE_STREAM=2, 
	VENDER_TYPE_VLC_RTSP=3, 
};

enum DEVICE_DECODETAG_ENUM
{
	DECODETAG_PS=0, //HAIKANG
	DECODETAG_SRC=1, //DAHUA
};


//����ͷ����
//-----------------------------------
//�󻪵�SDKֻ�ܿ�������һ��
#define OPEN_DAHUA_SDK 0
#define OPEN_DAHUA_SDK_NEW 1
//-----------------------------------
#define OPEN_HAIKANG_SDK 1

#define DB33_PLAYCTRL
#define OPEN_STREAM_CLIENT_SDK 1

#define OPEN_VLC_RTSP_SDK 1

///////
#define VIDEO_FORMAT_YV12 1
#define VIDEO_FORMAT_I420 2
#define VIDEO_FORMAT_RGB888 3
#define VIDEO_FORMAT_BGR888 4
//�� SystemTransform.dll ��ͻ ʹ��StreamClientSDK�ĸ���HAIKANSDK��
////////////////////////////////////////////////////////////
//����ģʽ 
#define TEST_DEBUG 1
//���� ��ѭ���汾 ��ֹͣʱ�Ῠ����
#define DEAD_WHILE 0
//������ �������� �Զ���������=1
#define AUTO_OPENALL (!TEST_DEBUG)


//��������ģʽ �ð汾��֧�ֵ綯��
//����ģʽ 1 �綯��ģʽ 0
//�л��綯����������
//A.�ǵû���IDD�������ﻻLOGO�� �綯���� IDB_LOGO_ELECAR �������� IDB_LOGO
//B.��rc�ļ�������IDR_MAINFRAME��·�� �޸�·�� IDR_MAINFRAME           ICON    DISCARDABLE     "res\\YiRongCarDetectAIO3.ico"
//C.��RES�ļ����� �� YiRongCarDetectAIO.ico �ļ��ö�Ӧ��ͼ���滻��
#define ALLTAB_DETECT_CAR_MODE 1

//-----------------------------------
//����ʶ���SDKֻ�ܿ�������һ��
//�����ɳ۳���ʶ�����=1 �ر�=0  �رվͿ��Բ���KEYҲ����DEBUG
#define OPEN_LC_CARDETECT_CODE 1

//���������龦����ʶ�����=1 �ر�=0  �رվͿ��Բ���KEYҲ����DEBUG
#define OPEN_HYZJ_CARDETECT_CODE 0
//-----------------------------------

//����¼����� 1 �ر�¼����� 0
#define OPEN_RECORD 0

//��������ʶ�����
#define OPEN_FACEDETECT_CODE 0

//����ʶ�� ��֡���һ��
//��Ϊ2���ǲ����ˣ���Ҫ���0
#define FACE_JUMP_NUM 5
//��Ϊ2���ǲ����ˣ���Ҫ���0
#define CAR_JUMP_NUM 3
//�����ϴ������·���Ľӿ�
#define JING_AO_UPLOAD 1
//////////////////////////////////////////////////////
//ʹ���¿���Ϊ1 �ɿ�Ϊ0
#if 1

//�¿�
#include "recolibC\\recoCommon.h"
#include "recolibC\\recoFaceMng.h"
#include "recolibC\\recoVideoAnalyse.h"

#if OPEN_FACEDETECT_CODE
//#pragma comment�����ͷ�ļ�  ��ȻCRT δ��ʼ�� R6030
#pragma comment(lib, "recolibC\\recoCommon.lib")
#pragma comment(lib, "recolibC\\recoFaceMng.lib")
#pragma comment(lib, "recolibC\\recoVideoAnalyse.lib")

#endif

#else

//�ɿ�
#include "recolibA\\recoCommon.h"
#include "recolibA\\recoFaceMng.h"
#include "recolibA\\recoVideoAnalyse.h"

#if OPEN_FACEDETECT_CODE
//#pragma comment�����ͷ�ļ�  ��ȻCRT δ��ʼ�� R6030
#pragma comment(lib, "recolibA\\recoCommon.lib")
#pragma comment(lib, "recolibA\\recoFaceMng.lib")
#pragma comment(lib, "recolibA\\recoVideoAnalyse.lib")

#endif

#endif


typedef struct
{
	HTREEITEM item;						//��ָ��
	long nid;
	long ncamera;					//��ץ����ʱ����Ч
	long RWdb_nid;
}DBLIST;

///////////////////////////
//�޸����� �ǵð����ݿ����ó��������Ҳ����
//�Լ� ���� �����ַ�
// ���� ������Ƶ���Ʒ���������� δ��������־��

#define MESSAGEBOX_TITLE "��������С������ڹ���ϵͳ"


//�����������+����ͷ������
#define MAX_AREA_ADD_CAM 16
//�����������
#define MAX_AREA 4

//�����ʾ���ٸ�����ͷ����
#define MAX_DEVICE_NUM 16
//��󲥷�·�� �Լ����Ӷ�������ͷ
#define MAX_CAMERA 4

//�ǰ���RTSP��ַ rtsp://10.142.50.249:554/0/888888:888888/main

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DA1368DB_F92F_4AAE_86E3_70C4BF842BE0__INCLUDED_)
